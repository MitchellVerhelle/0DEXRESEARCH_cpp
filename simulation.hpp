#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <tuple>
#include "user_pool.hpp"
#include "postTGE_rewards.hpp"
#include "preTGE_rewards.hpp"
#include "users.hpp"

namespace Simulation {

    struct SimulationResult {
        double TGETotal;
        std::vector<int> months;
        std::vector<double> totalUnlockedHistory;
        std::unordered_map<std::string, std::vector<double>> unlockedHistory;
        std::unordered_map<std::string, double> distribution;
        std::vector<double> TGETokens;
        std::vector<double> prices;
    };

    class MonteCarloSimulation {
    public:
        MonteCarloSimulation(int numUsers, double totalSupply, int preTGESteps, int simulationHorizon,
                             std::shared_ptr<Airdrop::AirdropPolicy> airdropPolicy,
                             std::shared_ptr<PreTGE::PreTGERewardsPolicy> preTGEPolicy = nullptr,
                             double airdropAllocationFraction = 0.15);
        void simulatePreTGE();
        void simulateTGE();
        std::tuple<std::vector<int>, std::vector<double>, std::unordered_map<std::string, std::vector<double>>>
            simulatePostTGE();
        SimulationResult run();
        std::shared_ptr<UserPoolNS::UserPool> getUserPool() const { return userPool_; }
    private:
        int numUsers_;
        double totalSupply_;
        int preTGESteps_;
        int simulationHorizon_;
        double airdropAllocationFraction_;
        std::shared_ptr<Airdrop::AirdropPolicy> airdropPolicy_;
        std::shared_ptr<PreTGE::PreTGERewardsPolicy> preTGEPolicy_;
        std::shared_ptr<UserPoolNS::UserPool> userPool_;
        std::unique_ptr<PostTGE::PostTGERewardsManager> postTGEManager_;
        alignas(64) char padding[64];
    };

    // Pricing functions
    std::vector<double> computeTokenPrice(double TGETotal,
                                            const std::vector<double>& totalUnlockedHistory,
                                            const std::vector<std::shared_ptr<Users::User>>& users,
                                            double basePrice = 10.0,
                                            double elasticity = 1.0,
                                            double buybackRate = 0.2,
                                            double alpha = 0.5,
                                            const std::unordered_map<std::string, double>* distribution = nullptr);

    std::vector<double> simulatePriceEvolutionDynamic(double TGETotal,
                                                        const std::vector<double>& totalUnlockedHistory,
                                                        const std::vector<std::shared_ptr<Users::User>>& users,
                                                        double basePrice = 10.0,
                                                        double elasticity = 1.0,
                                                        double buybackRate = 0.2,
                                                        double alpha = 0.5,
                                                        double mu = 0.0,
                                                        double sigma = 0.05,
                                                        double jumpIntensity = 0.1,
                                                        double jumpMean = -0.05,
                                                        double jumpStd = 0.1,
                                                        const std::unordered_map<std::string, double>* distribution = nullptr);

} // namespace Simulation

#endif // SIMULATION_HPP
