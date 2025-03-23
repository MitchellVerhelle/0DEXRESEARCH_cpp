#include "preTGE_rewards.hpp"
#include <unordered_map>
#include <algorithm>
#include <limits>

namespace PreTGE {

    using Tier = std::pair<double, double>;

    DydxRetroTieredRewardPolicy::DydxRetroTieredRewardPolicy(const std::vector<Tier>& tiers) {
        if (tiers.empty()) {
            tiers_ = { {1000, 310}, {10000, 1163}, {100000, 2500}, {1000000, 6414}, {std::numeric_limits<double>::infinity(), 9530} };
        } else {
            tiers_ = tiers;
        }
    }

    double DydxRetroTieredRewardPolicy::calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const {
        double volume = activityStats.count("trading_volume") ? activityStats.at("trading_volume") : 0;
        for (const auto& [threshold, points] : tiers_) {
            if (volume < threshold)
                return points;
        }
        return tiers_.back().second;
    }

    VertexMakerTakerRewardPolicy::VertexMakerTakerRewardPolicy(double makerWeight, double takerWeight, double qscoreWeight, double referralRate)
        : makerWeight_(makerWeight), takerWeight_(takerWeight), qscoreWeight_(qscoreWeight), referralRate_(referralRate) {}

    double VertexMakerTakerRewardPolicy::calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const {
        double maker = activityStats.count("maker_volume") ? activityStats.at("maker_volume") : 0;
        double taker = activityStats.count("taker_volume") ? activityStats.at("taker_volume") : 0;
        double qscore = activityStats.count("qscore") ? activityStats.at("qscore") : 0;
        double basePoints = maker * makerWeight_ + taker * takerWeight_ + qscore * qscoreWeight_;
        double referral = activityStats.count("referral_points") ? activityStats.at("referral_points") : 0;
        return basePoints + referral * referralRate_;
    }

    JupiterVolumeTierRewardPolicy::JupiterVolumeTierRewardPolicy(const std::vector<Tier>& tiers) {
        if (tiers.empty()) {
            tiers_ = { {1000, 50}, {29000, 250}, {500000, 3000}, {3000000, 10000}, {14000000, 20000} };
        } else {
            tiers_ = tiers;
        }
    }

    double JupiterVolumeTierRewardPolicy::calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const {
        double volume = activityStats.count("swap_volume") ? activityStats.at("swap_volume") : 0;
        double reward = 0;
        for (const auto& [threshold, points] : tiers_) {
            if (volume >= threshold)
                reward = points;
            else
                break;
        }
        return reward;
    }

    AevoBoostedVolumeRewardPolicy::AevoBoostedVolumeRewardPolicy(double baseMax, const std::unordered_map<int, double>& luckyProbs)
        : baseMax_(baseMax), rng_(std::random_device{}()) {
        if (luckyProbs.empty()) {
            luckyProbs_ = { {10, 0.10}, {50, 0.025}, {100, 0.01} };
        } else {
            luckyProbs_ = luckyProbs;
        }
    }

    double AevoBoostedVolumeRewardPolicy::calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const {
        double tradeVolume = activityStats.count("trade_volume") ? activityStats.at("trade_volume") : 0;
        double trailingVolume = activityStats.count("trailing_volume") ? activityStats.at("trailing_volume") : 0;
        double threshold = 5000000;
        double baseMultiplier = 1 + (baseMax_ - 1) * std::min(trailingVolume / threshold, 1.0);
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        double rnd = dist(rng_);
        double cumulative = 0.0;
        int luckyMultiplier = 1;
        std::vector<std::pair<int, double>> sortedProbs(luckyProbs_.begin(), luckyProbs_.end());
        std::sort(sortedProbs.begin(), sortedProbs.end(), [](auto a, auto b){ return a.second < b.second; });
        for (const auto& [multiplier, prob] : sortedProbs) {
            cumulative += prob;
            if (rnd < cumulative) {
                luckyMultiplier = multiplier;
                break;
            }
        }
        return tradeVolume * (baseMultiplier + luckyMultiplier - 1);
    }

    HelixLoyaltyPointsRewardPolicy::HelixLoyaltyPointsRewardPolicy(double volumeWeight, double diversityBonus, double loyaltyBonus)
        : volumeWeight_(volumeWeight), diversityBonus_(diversityBonus), loyaltyBonus_(loyaltyBonus) {}

    double HelixLoyaltyPointsRewardPolicy::calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const {
        double volume = activityStats.count("trading_volume") ? activityStats.at("trading_volume") : 0;
        double activeDays = activityStats.count("active_days") ? activityStats.at("active_days") : 0;
        double uniqueMarkets = activityStats.count("unique_markets") ? activityStats.at("unique_markets") : 0;
        return volumeWeight_ * volume + diversityBonus_ * uniqueMarkets + loyaltyBonus_ * activeDays * volume;
    }

    GameLikeMMRRewardPolicy::GameLikeMMRRewardPolicy(double basePoints, double winRateWeight, double consistencyBonus)
        : basePoints_(basePoints), winRateWeight_(winRateWeight), consistencyBonus_(consistencyBonus) {}

    double GameLikeMMRRewardPolicy::calculatePoints(const std::unordered_map<std::string, double>& activityStats, int /*user*/) const {
        double wins = activityStats.count("wins") ? activityStats.at("wins") : 0;
        double losses = activityStats.count("losses") ? activityStats.at("losses") : 0;
        double consecutiveDays = activityStats.count("consecutive_days") ? activityStats.at("consecutive_days") : 0;
        double totalGames = wins + losses;
        double winRate = totalGames > 0 ? wins / totalGames : 0;
        return basePoints_ + winRateWeight_ * winRate + consistencyBonus_ * consecutiveDays;
    }

    CustomPreTGERewardPolicy::CustomPreTGERewardPolicy(std::function<double(const std::unordered_map<std::string, double>&, int)> customFunction)
        : customFunction_(customFunction) {}

    double CustomPreTGERewardPolicy::calculatePoints(const std::unordered_map<std::string, double>& activityStats, int user) const {
        return customFunction_(activityStats, user);
    }

} // namespace PreTGE
