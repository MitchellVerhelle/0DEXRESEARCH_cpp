#ifndef USERS_HPP
#define USERS_HPP

#include <memory>
#include <string>
#include "airdrop_policy.hpp"

namespace Users {

    using AirdropPolicyPtr = std::shared_ptr<Airdrop::AirdropPolicy>;

    class User {
    public:
        User(double wealth, int userId, AirdropPolicyPtr policy);
        virtual ~User() = default;
        virtual void step(const std::string& phase) = 0;
        double getAirdropPoints() const { return airdropPoints_; }
        double getTokens() const { return tokens_; }
        bool isActive() const { return active_; }
        int getUserId() const { return userId_; }
    protected:
        int userId_;
        double wealth_;
        double airdropPoints_;
        double tokens_;
        bool active_;
        AirdropPolicyPtr airdropPolicy_;
        alignas(64) char padding[64];
    };

    class RegularUser : public User {
    public:
        RegularUser(double wealth, int userId, const std::string& userSize, AirdropPolicyPtr policy);
        void step(const std::string& phase) override;
        std::string getUserSize() const { return userSize_; }
    private:
        std::string userSize_;
        int interactionRate_;
    };

    class SybilUser : public User {
    public:
        SybilUser(double wealth, int userId, AirdropPolicyPtr policy);
        void step(const std::string& phase) override;
    private:
        int interactionRate_;
    };

} // namespace Users

#endif // USERS_HPP
