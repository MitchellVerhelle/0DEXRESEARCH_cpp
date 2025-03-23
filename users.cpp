#include "users.hpp"
#include <random>

namespace Users {

    User::User(double wealth, int userId, AirdropPolicyPtr policy)
        : wealth_(wealth), userId_(userId), airdropPoints_(0.0), tokens_(0.0), active_(true), airdropPolicy_(policy) {}

    RegularUser::RegularUser(double wealth, int userId, const std::string& userSize, AirdropPolicyPtr policy)
        : User(wealth, userId, policy), userSize_(userSize) {
        std::random_device rd;
        std::mt19937 gen(rd());
        if (userSize == "small") {
            std::poisson_distribution<int> d(1);
            interactionRate_ = d(gen);
        } else if (userSize == "medium") {
            std::poisson_distribution<int> d(3);
            interactionRate_ = d(gen);
        } else if (userSize == "large") {
            std::poisson_distribution<int> d(5);
            interactionRate_ = d(gen);
        } else {
            interactionRate_ = 1;
        }
    }

    void RegularUser::step(const std::string& phase) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(0.5, 1.5);
        if (phase == "PreTGE") {
            double delta = interactionRate_ * dist(gen);
            airdropPoints_ += delta;
        } else if (phase == "TGE") {
            tokens_ = airdropPolicy_->calculateTokens(airdropPoints_, userId_);
        } else if (phase == "PostTGE") {
            double prob = (userSize_ == "small") ? 0.4 :
                          (userSize_ == "medium") ? 0.8 :
                          (userSize_ == "large") ? 0.9 : 0.5;
            std::uniform_real_distribution<double> probDist(0.0, 1.0);
            active_ = (probDist(gen) < prob);
        }
    }

    SybilUser::SybilUser(double wealth, int userId, AirdropPolicyPtr policy)
        : User(wealth, userId, policy) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::poisson_distribution<int> d(0.5);
        interactionRate_ = d(gen);
    }

    void SybilUser::step(const std::string& phase) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(0.5, 1.0);
        if (phase == "PreTGE") {
            double delta = interactionRate_ * dist(gen);
            airdropPoints_ += delta;
        } else if (phase == "TGE") {
            tokens_ = airdropPolicy_->calculateTokens(airdropPoints_, userId_);
        } else if (phase == "PostTGE") {
            active_ = false;
        }
    }

} // namespace Users
