#include "user_pool.hpp"
#include "users.hpp"
#include <random>
#include <algorithm>

namespace UserPoolNS {

    UserPool::UserPool(int numUsers, std::shared_ptr<Airdrop::AirdropPolicy> policy)
        : numUsers_(numUsers), airdropPolicy_(policy) {
        generateUsers();
    }

    void UserPool::generateUsers() {
        double sybilPercentage = 0.3;
        int numSybil = static_cast<int>(numUsers_ * sybilPercentage);
        int numRegular = numUsers_ - numSybil;

        double smallPercentage = 0.6;
        double mediumPercentage = 0.3;
        double largePercentage = 0.1;

        int numSmall = static_cast<int>(numRegular * smallPercentage);
        int numMedium = static_cast<int>(numRegular * mediumPercentage);
        int numLarge = numRegular - numSmall - numMedium;

        int userId = 0;
        std::random_device rd;
        std::mt19937 gen(rd());
        // Create wealth distributions using lognormal distributions
        std::lognormal_distribution<double> distSmall(6, 1.5);
        for (int i = 0; i < numSmall; ++i) {
            double wealth = distSmall(gen);
            users_.push_back(std::make_shared<Users::RegularUser>(wealth, userId++, "small", airdropPolicy_));
        }
        std::lognormal_distribution<double> distMedium(7, 1.2);
        for (int i = 0; i < numMedium; ++i) {
            double wealth = distMedium(gen);
            users_.push_back(std::make_shared<Users::RegularUser>(wealth, userId++, "medium", airdropPolicy_));
        }
        std::lognormal_distribution<double> distLarge(8, 1.0);
        for (int i = 0; i < numLarge; ++i) {
            double wealth = distLarge(gen);
            users_.push_back(std::make_shared<Users::RegularUser>(wealth, userId++, "large", airdropPolicy_));
        }
        std::lognormal_distribution<double> distSybil(5, 1.0);
        for (int i = 0; i < numSybil; ++i) {
            double wealth = distSybil(gen);
            users_.push_back(std::make_shared<Users::SybilUser>(wealth, userId++, airdropPolicy_));
        }
        shuffleUsers();
    }

    void UserPool::shuffleUsers() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(users_.begin(), users_.end(), g);
    }

    void UserPool::stepAll(const std::string& phase) {
        for (auto& user : users_) {
            user->step(phase);
        }
    }

} // namespace UserPoolNS
