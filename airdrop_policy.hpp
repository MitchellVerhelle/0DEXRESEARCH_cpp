#ifndef AIRDROP_POLICY_HPP
#define AIRDROP_POLICY_HPP

#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>

namespace Airdrop {

    class AirdropPolicy {
    public:
        virtual ~AirdropPolicy() = default;
        virtual double calculateTokens(double airdropPoints, int /*user*/) const {
            return airdropPoints;
        }
    protected:
        alignas(64) char padding[64]; // padding to reduce false sharing
    };

    class LinearAirdropPolicy : public AirdropPolicy {
    public:
        explicit LinearAirdropPolicy(double factor = 1.0) : factor_(factor) {}
        double calculateTokens(double airdropPoints, int /*user*/) const override {
            return factor_ * airdropPoints;
        }
    private:
        double factor_;
        alignas(64) char padding[64];
    };

    class ExponentialAirdropPolicy : public AirdropPolicy {
    public:
        ExponentialAirdropPolicy(double factor = 1.0, double scaling = 1.0)
            : factor_(factor), scaling_(scaling) {}
        double calculateTokens(double airdropPoints, int /*user*/) const override {
            double points = std::min(airdropPoints, 1.0);
            return factor_ * (std::exp(points / scaling_) - 1.0);
        }
    private:
        double factor_;
        double scaling_;
        alignas(64) char padding[64];
    };

    class TieredConstantAirdropPolicy : public AirdropPolicy {
    public:
        using Tier = std::pair<double, double>;
        explicit TieredConstantAirdropPolicy(const std::vector<Tier>& tiers = {}) {
            if (tiers.empty()) {
                tiers_ = { {0.2, 0.1}, {0.6, 0.4}, {std::numeric_limits<double>::infinity(), 1.0} };
            } else {
                tiers_ = tiers;
            }
        }
        double calculateTokens(double airdropPoints, int /*user*/) const override {
            for (const auto& [threshold, tokenAmt] : tiers_) {
                if (airdropPoints < threshold)
                    return tokenAmt;
            }
            return tiers_.back().second;
        }
    private:
        std::vector<Tier> tiers_;
        alignas(64) char padding[64];
    };

    class TieredLinearAirdropPolicy : public AirdropPolicy {
    public:
        using Tier = std::pair<double, double>;
        explicit TieredLinearAirdropPolicy(const std::vector<Tier>& tiers = {}) {
            if (tiers.empty()) {
                tiers_ = { {0.2, 1.0}, {0.6, 1.5}, {std::numeric_limits<double>::infinity(), 2.0} };
            } else {
                tiers_ = tiers;
            }
        }
        double calculateTokens(double airdropPoints, int /*user*/) const override {
            double tokens = 0.0;
            double prevThreshold = 0.0;
            for (const auto& [threshold, factor] : tiers_) {
                if (airdropPoints <= threshold) {
                    tokens += (airdropPoints - prevThreshold) * factor;
                    return tokens;
                } else {
                    tokens += (threshold - prevThreshold) * factor;
                    prevThreshold = threshold;
                }
            }
            return tokens;
        }
    private:
        std::vector<Tier> tiers_;
        alignas(64) char padding[64];
    };

    class TieredExponentialAirdropPolicy : public AirdropPolicy {
    public:
        struct TierParams { double factor; double scaling; };
        using Tier = std::pair<double, TierParams>;
        explicit TieredExponentialAirdropPolicy(const std::vector<Tier>& tiers = {}) {
            if (tiers.empty()) {
                tiers_ = {
                    {0.2, {1.0, 0.2}},
                    {0.6, {1.5, 0.4}},
                    {std::numeric_limits<double>::infinity(), {2.0, 0.4}}
                };
            } else {
                tiers_ = tiers;
            }
        }
        double calculateTokens(double airdropPoints, int /*user*/) const override {
            double tokens = 0.0;
            double prevThreshold = 0.0;
            for (const auto& [threshold, params] : tiers_) {
                if (airdropPoints <= threshold) {
                    tokens += params.factor * (std::exp((airdropPoints - prevThreshold) / params.scaling) - 1.0);
                    return tokens;
                } else {
                    tokens += params.factor * (std::exp((threshold - prevThreshold) / params.scaling) - 1.0);
                    prevThreshold = threshold;
                }
            }
            return tokens;
        }
    private:
        std::vector<Tier> tiers_;
        alignas(64) char padding[64];
    };

} // namespace Airdrop

#endif // AIRDROP_POLICY_HPP
