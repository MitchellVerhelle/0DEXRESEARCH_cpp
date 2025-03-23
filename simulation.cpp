#include "simulation.hpp"
#include <random>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <iostream>

namespace Simulation {

    MonteCarloSimulation::MonteCarloSimulation(int numUsers, double totalSupply, int preTGESteps, int simulationHorizon,
                                               std::shared_ptr<Airdrop::AirdropPolicy> airdropPolicy,
                                               std::shared_ptr<PreTGE::PreTGERewardsPolicy> preTGEPolicy,
                                               double airdropAllocationFraction)
        : numUsers_(numUsers), totalSupply_(totalSupply), preTGESteps_(preTGESteps),
          simulationHorizon_(simulationHorizon), airdropAllocationFraction_(airdropAllocationFraction),
          airdropPolicy_(airdropPolicy), preTGEPolicy_(preTGEPolicy) {
        userPool_ = std::make_shared<UserPoolNS::UserPool>(numUsers_, airdropPolicy_);
        postTGEManager_ = std::make_unique<PostTGE::PostTGERewardsManager>(totalSupply_);
    }

    void MonteCarloSimulation::simulatePreTGE() {
        for (int i = 0; i < preTGESteps_; ++i) {
            userPool_->stepAll("PreTGE");
        }
        if (preTGEPolicy_) {
            for (auto& user : userPool_->getUsers()) {
                std::unordered_map<std::string, double> stats;
                stats["trading_volume"] = (user->getAirdropPoints() + 1) * 100; // dummy activity stat
                double points = preTGEPolicy_->calculatePoints(stats, user->getUserId());
                // For simplicity, assume the extra points are added to the user’s airdropPoints.
                // (In production code, you’d encapsulate this in a setter.)
            }
            // Optionally normalize points here.
        }
    }

    void MonteCarloSimulation::simulateTGE() {
        userPool_->stepAll("TGE");
    }

    std::tuple<std::vector<int>, std::vector<double>, std::unordered_map<std::string, std::vector<double>>>
    MonteCarloSimulation::simulatePostTGE() {
        std::vector<int> months;
        std::vector<double> totalUnlockedHistory;
        std::unordered_map<std::string, std::vector<double>> unlockedHistory;
        for (int month = 0; month <= simulationHorizon_; ++month) {
            months.push_back(month);
            auto allocations = postTGEManager_->getUnlockedAllocations(month);
            double totalUnlocked = 0;
            for (const auto& [group, tokens] : allocations) {
                totalUnlocked += tokens;
                unlockedHistory[group].push_back(tokens);
            }
            totalUnlockedHistory.push_back(totalUnlocked);
        }
        return { months, totalUnlockedHistory, unlockedHistory };
    }

    SimulationResult MonteCarloSimulation::run() {
        simulatePreTGE();
        simulateTGE();
        double rawTGETotal = 0;
        for (auto& user : userPool_->getUsers()) {
            rawTGETotal += user->getTokens();
        }
        double scaledTGETotal = airdropAllocationFraction_ * totalSupply_;
        if (rawTGETotal > 0) {
            // Scale tokens for each user (in production code, add a setter in User)
        }
        std::unordered_map<std::string, double> distribution = { {"small",0}, {"medium",0}, {"large",0}, {"sybil",0} };
        for (auto& user : userPool_->getUsers()) {
            if (dynamic_cast<Users::SybilUser*>(user.get()))
                distribution["sybil"] += user->getTokens();
            else if (auto ru = dynamic_cast<Users::RegularUser*>(user.get()))
                distribution[ru->getUserSize()] += user->getTokens();
        }
        double totalTokens = 0;
        for (auto& [key, val] : distribution)
            totalTokens += val;
        if (totalTokens > 0) {
            for (auto& [key, val] : distribution)
                val = (val / totalTokens) * 100.0;
        }
        auto [months, totalUnlockedHistory, unlockedHistory] = simulatePostTGE();
        SimulationResult result;
        result.TGETotal = scaledTGETotal;
        result.months = months;
        result.totalUnlockedHistory = totalUnlockedHistory;
        result.unlockedHistory = unlockedHistory;
        for (auto& user : userPool_->getUsers())
            result.TGETokens.push_back(user->getTokens());
        result.prices = computeTokenPrice(result.TGETotal, totalUnlockedHistory, userPool_->getUsers());
        return result;
    }

    std::vector<double> computeTokenPrice(double TGETotal,
                                            const std::vector<double>& totalUnlockedHistory,
                                            const std::vector<std::shared_ptr<Users::User>>& users,
                                            double basePrice,
                                            double elasticity,
                                            double buybackRate,
                                            double alpha,
                                            const std::unordered_map<std::string, double>* distribution) {
        double avgSellWeight = 0.0;
        if (distribution) {
            avgSellWeight = ((*distribution).at("small") * 1.0 +
                             (*distribution).at("medium") * 0.8 +
                             (*distribution).at("large") * 0.3 +
                             (*distribution).at("sybil") * 1.0) / 100.0;
        } else {
            double sumWeights = 0;
            for (const auto& user : users) {
                if (dynamic_cast<Users::SybilUser*>(user.get()))
                    sumWeights += 1.0;
                else if (auto ru = dynamic_cast<Users::RegularUser*>(user.get())) {
                    std::string size = ru->getUserSize();
                    sumWeights += (size == "small") ? 1.0 : (size == "medium") ? 0.8 : (size == "large") ? 0.3 : 1.0;
                } else {
                    sumWeights += 1.0;
                }
            }
            avgSellWeight = sumWeights / users.size();
        }
        std::vector<double> prices;
        double initialAdditional = totalUnlockedHistory.empty() ? 0 : totalUnlockedHistory[0];
        for (double unlocked : totalUnlockedHistory) {
            double circulatingSupply = TGETotal + (unlocked - initialAdditional) * avgSellWeight;
            double effectiveSupply = TGETotal + (unlocked - initialAdditional) * (avgSellWeight * (1 - buybackRate));
            effectiveSupply = std::max(effectiveSupply, 1.0);
            double combinedSupply = alpha * circulatingSupply + (1 - alpha) * effectiveSupply;
            double price = basePrice * std::pow(TGETotal / combinedSupply, elasticity);
            prices.push_back(price);
        }
        return prices;
    }

    std::vector<double> simulatePriceEvolutionDynamic(double TGETotal,
                                                        const std::vector<double>& totalUnlockedHistory,
                                                        const std::vector<std::shared_ptr<Users::User>>& users,
                                                        double basePrice,
                                                        double elasticity,
                                                        double buybackRate,
                                                        double alpha,
                                                        double mu,
                                                        double sigma,
                                                        double jumpIntensity,
                                                        double jumpMean,
                                                        double jumpStd,
                                                        const std::unordered_map<std::string, double>* distribution) {
        auto supplyPrice = computeTokenPrice(TGETotal, totalUnlockedHistory, users, basePrice, elasticity, buybackRate, alpha, distribution);
        size_t n = totalUnlockedHistory.size();
        std::vector<double> P_jump(n, 1.0);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> normalDist(0.0, 1.0);
        std::normal_distribution<double> jumpDist(jumpMean, jumpStd);
        std::uniform_real_distribution<double> uniformDist(0.0, 1.0);
        double dt = 1.0;
        for (size_t t = 1; t < n; ++t) {
            double diffusion = std::exp((mu - 0.5 * sigma * sigma) * dt + sigma * std::sqrt(dt) * normalDist(gen));
            double jump = (uniformDist(gen) < jumpIntensity * dt) ? 1.0 + jumpDist(gen) : 1.0;
            P_jump[t] = P_jump[t - 1] * diffusion * jump;
        }
        std::vector<double> prices;
        for (size_t i = 0; i < n; ++i)
            prices.push_back(supplyPrice[i] * P_jump[i]);
        return prices;
    }

} // namespace Simulation
