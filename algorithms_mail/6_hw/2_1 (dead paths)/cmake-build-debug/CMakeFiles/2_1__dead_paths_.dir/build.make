# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\1\Documents\EVM\algorithms_mail\6_hw\2_1 (dead paths)"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\1\Documents\EVM\algorithms_mail\6_hw\2_1 (dead paths)\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/2_1__dead_paths_.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/2_1__dead_paths_.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2_1__dead_paths_.dir/flags.make

CMakeFiles/2_1__dead_paths_.dir/main.cpp.obj: CMakeFiles/2_1__dead_paths_.dir/flags.make
CMakeFiles/2_1__dead_paths_.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\1\Documents\EVM\algorithms_mail\6_hw\2_1 (dead paths)\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2_1__dead_paths_.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\2_1__dead_paths_.dir\main.cpp.obj -c "C:\Users\1\Documents\EVM\algorithms_mail\6_hw\2_1 (dead paths)\main.cpp"

CMakeFiles/2_1__dead_paths_.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2_1__dead_paths_.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\1\Documents\EVM\algorithms_mail\6_hw\2_1 (dead paths)\main.cpp" > CMakeFiles\2_1__dead_paths_.dir\main.cpp.i

CMakeFiles/2_1__dead_paths_.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2_1__dead_paths_.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\1\Documents\EVM\algorithms_mail\6_hw\2_1 (dead paths)\main.cpp" -o CMakeFiles\2_1__dead_paths_.dir\main.cpp.s

# Object files for target 2_1__dead_paths_
2_1__dead_paths__OBJECTS = \
"CMakeFiles/2_1__dead_paths_.dir/main.cpp.obj"

# External object files for target 2_1__dead_paths_
2_1__dead_paths__EXTERNAL_OBJECTS =

2_1__dead_paths_.exe: CMakeFiles/2_1__dead_paths_.dir/main.cpp.obj
2_1__dead_paths_.exe: CMakeFiles/2_1__dead_paths_.dir/build.make
2_1__dead_paths_.exe: CMakeFiles/2_1__dead_paths_.dir/linklibs.rsp
2_1__dead_paths_.exe: CMakeFiles/2_1__dead_paths_.dir/objects1.rsp
2_1__dead_paths_.exe: CMakeFiles/2_1__dead_paths_.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\1\Documents\EVM\algorithms_mail\6_hw\2_1 (dead paths)\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 2_1__dead_paths_.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\2_1__dead_paths_.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2_1__dead_paths_.dir/build: 2_1__dead_paths_.exe

.PHONY : CMakeFiles/2_1__dead_paths_.dir/build

CMakeFiles/2_1__dead_paths_.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\2_1__dead_paths_.dir\cmake_clean.cmake
.PHONY : CMakeFiles/2_1__dead_paths_.dir/clean

CMakeFiles/2_1__dead_paths_.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\1\Documents\EVM\algorithms_mail\6_hw\2_1 (dead paths)" "C:\Users\1\Documents\EVM\algorithms_mail\6_hw\2_1 (dead paths)" "C:\Users\1\Documents\EVM\algorithms_mail\6_hw\2_1 (dead paths)\cmake-build-debug" "C:\Users\1\Documents\EVM\algorithms_mail\6_hw\2_1 (dead paths)\cmake-build-debug" "C:\Users\1\Documents\EVM\algorithms_mail\6_hw\2_1 (dead paths)\cmake-build-debug\CMakeFiles\2_1__dead_paths_.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/2_1__dead_paths_.dir/depend

