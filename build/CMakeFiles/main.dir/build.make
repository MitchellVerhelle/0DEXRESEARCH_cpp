# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mitchellverhelle/0DEXRESEARCH_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mitchellverhelle/0DEXRESEARCH_cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/codegen:
.PHONY : CMakeFiles/main.dir/codegen

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: /Users/mitchellverhelle/0DEXRESEARCH_cpp/main.cpp
CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mitchellverhelle/0DEXRESEARCH_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c /Users/mitchellverhelle/0DEXRESEARCH_cpp/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mitchellverhelle/0DEXRESEARCH_cpp/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mitchellverhelle/0DEXRESEARCH_cpp/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/airdrop_policy.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/airdrop_policy.cpp.o: /Users/mitchellverhelle/0DEXRESEARCH_cpp/airdrop_policy.cpp
CMakeFiles/main.dir/airdrop_policy.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mitchellverhelle/0DEXRESEARCH_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/airdrop_policy.cpp.o"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/airdrop_policy.cpp.o -MF CMakeFiles/main.dir/airdrop_policy.cpp.o.d -o CMakeFiles/main.dir/airdrop_policy.cpp.o -c /Users/mitchellverhelle/0DEXRESEARCH_cpp/airdrop_policy.cpp

CMakeFiles/main.dir/airdrop_policy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/airdrop_policy.cpp.i"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mitchellverhelle/0DEXRESEARCH_cpp/airdrop_policy.cpp > CMakeFiles/main.dir/airdrop_policy.cpp.i

CMakeFiles/main.dir/airdrop_policy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/airdrop_policy.cpp.s"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mitchellverhelle/0DEXRESEARCH_cpp/airdrop_policy.cpp -o CMakeFiles/main.dir/airdrop_policy.cpp.s

CMakeFiles/main.dir/postTGE_rewards.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/postTGE_rewards.cpp.o: /Users/mitchellverhelle/0DEXRESEARCH_cpp/postTGE_rewards.cpp
CMakeFiles/main.dir/postTGE_rewards.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mitchellverhelle/0DEXRESEARCH_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/postTGE_rewards.cpp.o"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/postTGE_rewards.cpp.o -MF CMakeFiles/main.dir/postTGE_rewards.cpp.o.d -o CMakeFiles/main.dir/postTGE_rewards.cpp.o -c /Users/mitchellverhelle/0DEXRESEARCH_cpp/postTGE_rewards.cpp

CMakeFiles/main.dir/postTGE_rewards.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/postTGE_rewards.cpp.i"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mitchellverhelle/0DEXRESEARCH_cpp/postTGE_rewards.cpp > CMakeFiles/main.dir/postTGE_rewards.cpp.i

CMakeFiles/main.dir/postTGE_rewards.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/postTGE_rewards.cpp.s"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mitchellverhelle/0DEXRESEARCH_cpp/postTGE_rewards.cpp -o CMakeFiles/main.dir/postTGE_rewards.cpp.s

CMakeFiles/main.dir/preTGE_rewards.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/preTGE_rewards.cpp.o: /Users/mitchellverhelle/0DEXRESEARCH_cpp/preTGE_rewards.cpp
CMakeFiles/main.dir/preTGE_rewards.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mitchellverhelle/0DEXRESEARCH_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/preTGE_rewards.cpp.o"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/preTGE_rewards.cpp.o -MF CMakeFiles/main.dir/preTGE_rewards.cpp.o.d -o CMakeFiles/main.dir/preTGE_rewards.cpp.o -c /Users/mitchellverhelle/0DEXRESEARCH_cpp/preTGE_rewards.cpp

CMakeFiles/main.dir/preTGE_rewards.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/preTGE_rewards.cpp.i"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mitchellverhelle/0DEXRESEARCH_cpp/preTGE_rewards.cpp > CMakeFiles/main.dir/preTGE_rewards.cpp.i

CMakeFiles/main.dir/preTGE_rewards.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/preTGE_rewards.cpp.s"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mitchellverhelle/0DEXRESEARCH_cpp/preTGE_rewards.cpp -o CMakeFiles/main.dir/preTGE_rewards.cpp.s

CMakeFiles/main.dir/users.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/users.cpp.o: /Users/mitchellverhelle/0DEXRESEARCH_cpp/users.cpp
CMakeFiles/main.dir/users.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mitchellverhelle/0DEXRESEARCH_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/users.cpp.o"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/users.cpp.o -MF CMakeFiles/main.dir/users.cpp.o.d -o CMakeFiles/main.dir/users.cpp.o -c /Users/mitchellverhelle/0DEXRESEARCH_cpp/users.cpp

CMakeFiles/main.dir/users.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/users.cpp.i"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mitchellverhelle/0DEXRESEARCH_cpp/users.cpp > CMakeFiles/main.dir/users.cpp.i

CMakeFiles/main.dir/users.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/users.cpp.s"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mitchellverhelle/0DEXRESEARCH_cpp/users.cpp -o CMakeFiles/main.dir/users.cpp.s

CMakeFiles/main.dir/user_pool.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/user_pool.cpp.o: /Users/mitchellverhelle/0DEXRESEARCH_cpp/user_pool.cpp
CMakeFiles/main.dir/user_pool.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mitchellverhelle/0DEXRESEARCH_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/user_pool.cpp.o"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/user_pool.cpp.o -MF CMakeFiles/main.dir/user_pool.cpp.o.d -o CMakeFiles/main.dir/user_pool.cpp.o -c /Users/mitchellverhelle/0DEXRESEARCH_cpp/user_pool.cpp

CMakeFiles/main.dir/user_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/user_pool.cpp.i"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mitchellverhelle/0DEXRESEARCH_cpp/user_pool.cpp > CMakeFiles/main.dir/user_pool.cpp.i

CMakeFiles/main.dir/user_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/user_pool.cpp.s"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mitchellverhelle/0DEXRESEARCH_cpp/user_pool.cpp -o CMakeFiles/main.dir/user_pool.cpp.s

CMakeFiles/main.dir/simulation.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/simulation.cpp.o: /Users/mitchellverhelle/0DEXRESEARCH_cpp/simulation.cpp
CMakeFiles/main.dir/simulation.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mitchellverhelle/0DEXRESEARCH_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/main.dir/simulation.cpp.o"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/simulation.cpp.o -MF CMakeFiles/main.dir/simulation.cpp.o.d -o CMakeFiles/main.dir/simulation.cpp.o -c /Users/mitchellverhelle/0DEXRESEARCH_cpp/simulation.cpp

CMakeFiles/main.dir/simulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/simulation.cpp.i"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mitchellverhelle/0DEXRESEARCH_cpp/simulation.cpp > CMakeFiles/main.dir/simulation.cpp.i

CMakeFiles/main.dir/simulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/simulation.cpp.s"
	/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mitchellverhelle/0DEXRESEARCH_cpp/simulation.cpp -o CMakeFiles/main.dir/simulation.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/airdrop_policy.cpp.o" \
"CMakeFiles/main.dir/postTGE_rewards.cpp.o" \
"CMakeFiles/main.dir/preTGE_rewards.cpp.o" \
"CMakeFiles/main.dir/users.cpp.o" \
"CMakeFiles/main.dir/user_pool.cpp.o" \
"CMakeFiles/main.dir/simulation.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.cpp.o
main: CMakeFiles/main.dir/airdrop_policy.cpp.o
main: CMakeFiles/main.dir/postTGE_rewards.cpp.o
main: CMakeFiles/main.dir/preTGE_rewards.cpp.o
main: CMakeFiles/main.dir/users.cpp.o
main: CMakeFiles/main.dir/user_pool.cpp.o
main: CMakeFiles/main.dir/simulation.cpp.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/mitchellverhelle/0DEXRESEARCH_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /Users/mitchellverhelle/0DEXRESEARCH_cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mitchellverhelle/0DEXRESEARCH_cpp /Users/mitchellverhelle/0DEXRESEARCH_cpp /Users/mitchellverhelle/0DEXRESEARCH_cpp/build /Users/mitchellverhelle/0DEXRESEARCH_cpp/build /Users/mitchellverhelle/0DEXRESEARCH_cpp/build/CMakeFiles/main.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/main.dir/depend

