#ifndef PRETGE_REWARDS_HPP
#define PRETGE_REWARDS_HPP

#include <vector>
#include <limits>
#include <cmath>
#include <random>
#include <functional>
#include <unordered_map>
#include <string>

namespace PreTGE {

    // Abstract base class
    class PreTGERewardsPolicy {
    public:
        virtual ~PreTGERewardsPolicy() = default;
        virtual double calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const = 0;
    protected:
        alignas(64) char padding[64];
    };

    // dYdX Retro Tiered Reward Policy
    class DydxRetroTieredRewardPolicy : public PreTGERewardsPolicy {
    public:
        using Tier = std::pair<double, double>;
        explicit DydxRetroTieredRewardPolicy(const std::vector<Tier>& tiers = {});
        double calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const override;
    private:
        std::vector<Tier> tiers_;
        alignas(64) char padding[64];
    };

    // Vertex Maker/Taker Reward Policy
    class VertexMakerTakerRewardPolicy : public PreTGERewardsPolicy {
    public:
        VertexMakerTakerRewardPolicy(double makerWeight = 0.375, double takerWeight = 0.375, double qscoreWeight = 0.25, double referralRate = 0.25);
        double calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const override;
    private:
        double makerWeight_;
        double takerWeight_;
        double qscoreWeight_;
        double referralRate_;
        alignas(64) char padding[64];
    };

    // Jupiter Volume Tier Reward Policy
    class JupiterVolumeTierRewardPolicy : public PreTGERewardsPolicy {
    public:
        using Tier = std::pair<double, double>;
        explicit JupiterVolumeTierRewardPolicy(const std::vector<Tier>& tiers = {});
        double calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const override;
    private:
        std::vector<Tier> tiers_;
        alignas(64) char padding[64];
    };

    // Aevo Boosted Volume Reward Policy
    class AevoBoostedVolumeRewardPolicy : public PreTGERewardsPolicy {
    public:
        explicit AevoBoostedVolumeRewardPolicy(double baseMax = 4.0, const std::unordered_map<int, double>& luckyProbs = {});
        double calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const override;
    private:
        double baseMax_;
        std::unordered_map<int, double> luckyProbs_;
        mutable std::mt19937 rng_;
        alignas(64) char padding[64];
    };

    // Helix Loyalty Points Reward Policy
    class HelixLoyaltyPointsRewardPolicy : public PreTGERewardsPolicy {
    public:
        HelixLoyaltyPointsRewardPolicy(double volumeWeight = 1.0, double diversityBonus = 100, double loyaltyBonus = 0.1);
        double calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const override;
    private:
        double volumeWeight_;
        double diversityBonus_;
        double loyaltyBonus_;
        alignas(64) char padding[64];
    };

    // Game-like MMR Reward Policy
    class GameLikeMMRRewardPolicy : public PreTGERewardsPolicy {
    public:
        GameLikeMMRRewardPolicy(double basePoints = 1000, double winRateWeight = 500, double consistencyBonus = 300);
        double calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const override;
    private:
        double basePoints_;
        double winRateWeight_;
        double consistencyBonus_;
        alignas(64) char padding[64];
    };

    // Custom / Generic Reward Policy
    class CustomPreTGERewardPolicy : public PreTGERewardsPolicy {
    public:
        explicit CustomPreTGERewardPolicy(std::function<double(const std::unordered_map<std::string, double>&, int)> customFunction);
        double calculatePoints(const std::unordered_map<std::string, double>& activityStats, int user) const override;
    private:
        std::function<double(const std::unordered_map<std::string, double>&, int)> customFunction_;
        alignas(64) char padding[64];
    };

} // namespace PreTGE

#endif // PRETGE_REWARDS_HPP
