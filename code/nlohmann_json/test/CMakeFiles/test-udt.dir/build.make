# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/bachmann/Downloads/json-develop

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bachmann/Downloads/json-develop

# Include any dependencies generated for this target.
include test/CMakeFiles/test-udt.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test-udt.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test-udt.dir/flags.make

test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o: test/CMakeFiles/test-udt.dir/flags.make
test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o: test/src/unit-udt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bachmann/Downloads/json-develop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o"
	cd /home/bachmann/Downloads/json-develop/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-udt.dir/src/unit-udt.cpp.o -c /home/bachmann/Downloads/json-develop/test/src/unit-udt.cpp

test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-udt.dir/src/unit-udt.cpp.i"
	cd /home/bachmann/Downloads/json-develop/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bachmann/Downloads/json-develop/test/src/unit-udt.cpp > CMakeFiles/test-udt.dir/src/unit-udt.cpp.i

test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-udt.dir/src/unit-udt.cpp.s"
	cd /home/bachmann/Downloads/json-develop/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bachmann/Downloads/json-develop/test/src/unit-udt.cpp -o CMakeFiles/test-udt.dir/src/unit-udt.cpp.s

test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o.requires:

.PHONY : test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o.requires

test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o.provides: test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/test-udt.dir/build.make test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o.provides.build
.PHONY : test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o.provides

test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o.provides.build: test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o


# Object files for target test-udt
test__udt_OBJECTS = \
"CMakeFiles/test-udt.dir/src/unit-udt.cpp.o"

# External object files for target test-udt
test__udt_EXTERNAL_OBJECTS = \
"/home/bachmann/Downloads/json-develop/test/CMakeFiles/catch_main.dir/src/unit.cpp.o"

test/test-udt: test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o
test/test-udt: test/CMakeFiles/catch_main.dir/src/unit.cpp.o
test/test-udt: test/CMakeFiles/test-udt.dir/build.make
test/test-udt: test/CMakeFiles/test-udt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bachmann/Downloads/json-develop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-udt"
	cd /home/bachmann/Downloads/json-develop/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-udt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test-udt.dir/build: test/test-udt

.PHONY : test/CMakeFiles/test-udt.dir/build

test/CMakeFiles/test-udt.dir/requires: test/CMakeFiles/test-udt.dir/src/unit-udt.cpp.o.requires

.PHONY : test/CMakeFiles/test-udt.dir/requires

test/CMakeFiles/test-udt.dir/clean:
	cd /home/bachmann/Downloads/json-develop/test && $(CMAKE_COMMAND) -P CMakeFiles/test-udt.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test-udt.dir/clean

test/CMakeFiles/test-udt.dir/depend:
	cd /home/bachmann/Downloads/json-develop && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bachmann/Downloads/json-develop /home/bachmann/Downloads/json-develop/test /home/bachmann/Downloads/json-develop /home/bachmann/Downloads/json-develop/test /home/bachmann/Downloads/json-develop/test/CMakeFiles/test-udt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test-udt.dir/depend

