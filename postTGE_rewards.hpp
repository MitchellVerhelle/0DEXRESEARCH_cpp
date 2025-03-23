#ifndef POSTTGE_REWARDS_HPP
#define POSTTGE_REWARDS_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace PostTGE {

    class VestingSchedule {
    public:
        VestingSchedule(double allocation, double unlockAtTGE, int lockupDuration,
                        double initialCliffUnlock, int unlockDuration, int initialCliffDelay = 0);
        double getUnlockedFraction(int monthsElapsed) const;
        double getUnlockedTokens(int monthsElapsed) const;
    private:
        double allocation_;
        double unlockAtTGE_;
        int lockupDuration_;
        double initialCliffUnlock_;
        int unlockDuration_;
        int initialCliffDelay_;
        alignas(64) char padding[64];
    };

    class PostTGERewardsManager {
    public:
        explicit PostTGERewardsManager(double totalSupply);
        std::unordered_map<std::string, double> getUnlockedAllocations(int monthsElapsed) const;
        const std::unordered_map<std::string, std::shared_ptr<VestingSchedule>>& getSchedules() const { return schedules_; }
    private:
        double totalSupply_;
        std::unordered_map<std::string, std::shared_ptr<VestingSchedule>> schedules_;
        void initializeSchedules();
        alignas(64) char padding[64];
    };

} // namespace PostTGE

#endif // POSTTGE_REWARDS_HPP
