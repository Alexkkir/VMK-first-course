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
CMAKE_SOURCE_DIR = C:\Users\1\Documents\EVM\algorithms_mail\8_hw\2_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\1\Documents\EVM\algorithms_mail\8_hw\2_3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/2_3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/2_3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2_3.dir/flags.make

CMakeFiles/2_3.dir/main.cpp.obj: CMakeFiles/2_3.dir/flags.make
CMakeFiles/2_3.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\1\Documents\EVM\algorithms_mail\8_hw\2_3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2_3.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\2_3.dir\main.cpp.obj -c C:\Users\1\Documents\EVM\algorithms_mail\8_hw\2_3\main.cpp

CMakeFiles/2_3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2_3.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\1\Documents\EVM\algorithms_mail\8_hw\2_3\main.cpp > CMakeFiles\2_3.dir\main.cpp.i

CMakeFiles/2_3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2_3.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\1\Documents\EVM\algorithms_mail\8_hw\2_3\main.cpp -o CMakeFiles\2_3.dir\main.cpp.s

# Object files for target 2_3
2_3_OBJECTS = \
"CMakeFiles/2_3.dir/main.cpp.obj"

# External object files for target 2_3
2_3_EXTERNAL_OBJECTS =

2_3.exe: CMakeFiles/2_3.dir/main.cpp.obj
2_3.exe: CMakeFiles/2_3.dir/build.make
2_3.exe: CMakeFiles/2_3.dir/linklibs.rsp
2_3.exe: CMakeFiles/2_3.dir/objects1.rsp
2_3.exe: CMakeFiles/2_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\1\Documents\EVM\algorithms_mail\8_hw\2_3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 2_3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\2_3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2_3.dir/build: 2_3.exe

.PHONY : CMakeFiles/2_3.dir/build

CMakeFiles/2_3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\2_3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/2_3.dir/clean

CMakeFiles/2_3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\1\Documents\EVM\algorithms_mail\8_hw\2_3 C:\Users\1\Documents\EVM\algorithms_mail\8_hw\2_3 C:\Users\1\Documents\EVM\algorithms_mail\8_hw\2_3\cmake-build-debug C:\Users\1\Documents\EVM\algorithms_mail\8_hw\2_3\cmake-build-debug C:\Users\1\Documents\EVM\algorithms_mail\8_hw\2_3\cmake-build-debug\CMakeFiles\2_3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2_3.dir/depend

