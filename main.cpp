#include <iostream>
#include <vector>
#include <string>
#include <future>
#include <unordered_map>
#include "airdrop_policy.hpp"
#include "preTGE_rewards.hpp"
#include "simulation.hpp"
#include "user_pool.hpp"
#include "users.hpp"
#include "postTGE_rewards.hpp"
// Include our jthread wrapper if needed
#include "jthread.h"

using namespace Airdrop;
using namespace PreTGE;
using namespace Simulation;

int main() {
    // Define airdrop policies
    std::vector<std::pair<std::string, std::shared_ptr<AirdropPolicy>>> airdropPolicies = {
        {"Linear", std::make_shared<LinearAirdropPolicy>()},
        {"Exponential", std::make_shared<ExponentialAirdropPolicy>()},
        {"Tiered Linear", std::make_shared<TieredLinearAirdropPolicy>()},
        {"Tiered Constant", std::make_shared<TieredConstantAirdropPolicy>()},
        {"Tiered Exponential", std::make_shared<TieredExponentialAirdropPolicy>()}
    };

    // Define preTGE policies
    std::vector<std::pair<std::string, std::shared_ptr<PreTGERewardsPolicy>>> preTGEPolicies = {
        {"dYdX Retro", std::make_shared<DydxRetroTieredRewardPolicy>()},
        {"Vertex Maker/Taker", std::make_shared<VertexMakerTakerRewardPolicy>()},
        {"Jupiter Volume Tier", std::make_shared<JupiterVolumeTierRewardPolicy>()},
        {"Aevo Boosted Volume", std::make_shared<AevoBoostedVolumeRewardPolicy>()},
        {"Helix Loyalty", std::make_shared<HelixLoyaltyPointsRewardPolicy>()},
        {"Game-like MMR", std::make_shared<GameLikeMMRRewardPolicy>()}
    };

    // Simulation parameters
    int numUsers = 100000;
    double totalSupply = 1e9;
    int preTGESteps = 50;
    int simulationHorizon = 60;
    double basePrice = 10.0;
    double elasticity = 1.0;
    double buybackRate = 0.2;

    // Run simulations concurrently using std::async
    std::vector<std::future<std::pair<std::string, SimulationResult>>> futures;
    for (const auto& prePolicyPair : preTGEPolicies) {
        for (const auto& adPolicyPair : airdropPolicies) {
            std::string comboName = prePolicyPair.first + " + " + adPolicyPair.first;
            std::cout << "Submitting simulation for: " << comboName << std::endl;
            futures.push_back(std::async(std::launch::async, [=]() -> std::pair<std::string, SimulationResult> {
                MonteCarloSimulation sim(numUsers, totalSupply, preTGESteps, simulationHorizon, adPolicyPair.second, prePolicyPair.second, 0.15);
                SimulationResult res = sim.run();
                return std::make_pair(comboName, res);
            }));
        }
    }

    // Collect results
    std::unordered_map<std::string, SimulationResult> results;
    for (auto& fut : futures) {
        auto [comboName, res] = fut.get();
        results[comboName] = res;
        std::cout << "Completed simulation for: " << comboName << std::endl;
    }

    // For example, print one result:
    std::string chosen = "dYdX Retro + Linear";
    if (results.find(chosen) != results.end()) {
        auto& res = results[chosen];
        std::cout << "TGE Total Tokens for " << chosen << ": " << res.TGETotal << std::endl;
    }
    std::cout << "Simulation complete." << std::endl;
    return 0;
}
