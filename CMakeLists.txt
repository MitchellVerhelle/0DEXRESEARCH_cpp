cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_COMPILER "/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++")

project(DEXResearch)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

# ========== Executable ==========
add_executable(main main.cpp 
    airdrop_policy.cpp 
    postTGE_rewards.cpp 
    preTGE_rewards.cpp 
    users.cpp 
    user_pool.cpp 
    simulation.cpp
)./
target_link_libraries(main PRIVATE Threads::Threads)

# cmake -S . -B ./build
# cmake --build ./build