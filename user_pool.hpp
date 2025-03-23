#ifndef USER_POOL_HPP
#define USER_POOL_HPP

#include <vector>
#include <memory>
#include "users.hpp"

namespace UserPoolNS {

    class UserPool {
    public:
        UserPool(int numUsers, std::shared_ptr<Airdrop::AirdropPolicy> policy = std::make_shared<Airdrop::AirdropPolicy>());
        void generateUsers();
        void stepAll(const std::string& phase);
        std::vector<std::shared_ptr<Users::User>> getUsers() const { return users_; }
    private:
        int numUsers_;
        std::shared_ptr<Airdrop::AirdropPolicy> airdropPolicy_;
        std::vector<std::shared_ptr<Users::User>> users_;
        void shuffleUsers();
        alignas(64) char padding[64];
    };

} // namespace UserPoolNS

#endif // USER_POOL_HPP
