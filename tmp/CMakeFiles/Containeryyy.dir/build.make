# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Rasul/CLionProjects/Containeryyy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Rasul/CLionProjects/Containeryyy/tmp

# Include any dependencies generated for this target.
include CMakeFiles/Containeryyy.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Containeryyy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Containeryyy.dir/flags.make

CMakeFiles/Containeryyy.dir/main.cpp.o: CMakeFiles/Containeryyy.dir/flags.make
CMakeFiles/Containeryyy.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Rasul/CLionProjects/Containeryyy/tmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Containeryyy.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Containeryyy.dir/main.cpp.o -c /mnt/c/Users/Rasul/CLionProjects/Containeryyy/main.cpp

CMakeFiles/Containeryyy.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Containeryyy.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Rasul/CLionProjects/Containeryyy/main.cpp > CMakeFiles/Containeryyy.dir/main.cpp.i

CMakeFiles/Containeryyy.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Containeryyy.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Rasul/CLionProjects/Containeryyy/main.cpp -o CMakeFiles/Containeryyy.dir/main.cpp.s

# Object files for target Containeryyy
Containeryyy_OBJECTS = \
"CMakeFiles/Containeryyy.dir/main.cpp.o"

# External object files for target Containeryyy
Containeryyy_EXTERNAL_OBJECTS =

Containeryyy: CMakeFiles/Containeryyy.dir/main.cpp.o
Containeryyy: CMakeFiles/Containeryyy.dir/build.make
Containeryyy: CMakeFiles/Containeryyy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Rasul/CLionProjects/Containeryyy/tmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Containeryyy"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Containeryyy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Containeryyy.dir/build: Containeryyy

.PHONY : CMakeFiles/Containeryyy.dir/build

CMakeFiles/Containeryyy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Containeryyy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Containeryyy.dir/clean

CMakeFiles/Containeryyy.dir/depend:
	cd /mnt/c/Users/Rasul/CLionProjects/Containeryyy/tmp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Rasul/CLionProjects/Containeryyy /mnt/c/Users/Rasul/CLionProjects/Containeryyy /mnt/c/Users/Rasul/CLionProjects/Containeryyy/tmp /mnt/c/Users/Rasul/CLionProjects/Containeryyy/tmp /mnt/c/Users/Rasul/CLionProjects/Containeryyy/tmp/CMakeFiles/Containeryyy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Containeryyy.dir/depend

