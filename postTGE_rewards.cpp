#include "postTGE_rewards.hpp"
#include <algorithm>
#include <limits>

namespace PostTGE {

    VestingSchedule::VestingSchedule(double allocation, double unlockAtTGE, int lockupDuration,
                                     double initialCliffUnlock, int unlockDuration, int initialCliffDelay)
        : allocation_(allocation), unlockAtTGE_(unlockAtTGE), lockupDuration_(lockupDuration),
          initialCliffUnlock_(initialCliffUnlock), unlockDuration_(unlockDuration), initialCliffDelay_(initialCliffDelay) {}

    double VestingSchedule::getUnlockedFraction(int monthsElapsed) const {
        if (monthsElapsed < 0)
            return 0.0;
        if (lockupDuration_ > 0) {
            if (monthsElapsed < lockupDuration_)
                return unlockAtTGE_;
            else if (monthsElapsed < lockupDuration_ + unlockDuration_) {
                double linearProgress = static_cast<double>(monthsElapsed - lockupDuration_) / unlockDuration_;
                return unlockAtTGE_ + initialCliffUnlock_ + (1.0 - unlockAtTGE_ - initialCliffUnlock_) * linearProgress;
            } else {
                return 1.0;
            }
        } else {
            if (monthsElapsed < initialCliffDelay_)
                return unlockAtTGE_;
            else if (monthsElapsed < initialCliffDelay_ + unlockDuration_) {
                double linearProgress = static_cast<double>(monthsElapsed - initialCliffDelay_) / unlockDuration_;
                return unlockAtTGE_ + initialCliffUnlock_ + (1.0 - unlockAtTGE_ - initialCliffUnlock_) * linearProgress;
            } else {
                return 1.0;
            }
        }
    }

    double VestingSchedule::getUnlockedTokens(int monthsElapsed) const {
        double fraction = getUnlockedFraction(monthsElapsed);
        return allocation_ * fraction;
    }

    PostTGERewardsManager::PostTGERewardsManager(double totalSupply)
        : totalSupply_(totalSupply) {
        initializeSchedules();
    }

    void PostTGERewardsManager::initializeSchedules() {
        schedules_["Team"] = std::make_shared<VestingSchedule>(totalSupply_ * 0.20, 0.20, 12, 0.20, 36);
        schedules_["TGE Airdrop"] = std::make_shared<VestingSchedule>(totalSupply_ * 0.15, 1.0, 0, 0.0, 0);
        schedules_["Future Investors"] = std::make_shared<VestingSchedule>(totalSupply_ * 0.17, 0.0, 0, 0.0, 48);
        schedules_["Strategic Reserve/Treasury"] = std::make_shared<VestingSchedule>(totalSupply_ * 0.20, 0.0, 0, 0.0, 48);
        schedules_["Investors"] = std::make_shared<VestingSchedule>(totalSupply_ * 0.08, 0.20, 0, 0.20, 36, 1);
        schedules_["Rewards"] = std::make_shared<VestingSchedule>(totalSupply_ * 0.05, 1.0, 0, 0.0, 0);
        schedules_["Promotion"] = std::make_shared<VestingSchedule>(totalSupply_ * 0.03, 0.20, 0, 0.20, 24, 1);
        schedules_["Advisors"] = std::make_shared<VestingSchedule>(totalSupply_ * 0.02, 0.20, 12, 0.20, 36);
    }

    std::unordered_map<std::string, double> PostTGERewardsManager::getUnlockedAllocations(int monthsElapsed) const {
        std::unordered_map<std::string, double> unlocked;
        for (const auto& [group, schedule] : schedules_) {
            unlocked[group] = schedule->getUnlockedTokens(monthsElapsed);
        }
        return unlocked;
    }

} // namespace PostTGE
