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
include test/CMakeFiles/test-alt-string.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test-alt-string.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test-alt-string.dir/flags.make

test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o: test/CMakeFiles/test-alt-string.dir/flags.make
test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o: test/src/unit-alt-string.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bachmann/Downloads/json-develop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o"
	cd /home/bachmann/Downloads/json-develop/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o -c /home/bachmann/Downloads/json-develop/test/src/unit-alt-string.cpp

test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.i"
	cd /home/bachmann/Downloads/json-develop/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bachmann/Downloads/json-develop/test/src/unit-alt-string.cpp > CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.i

test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.s"
	cd /home/bachmann/Downloads/json-develop/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bachmann/Downloads/json-develop/test/src/unit-alt-string.cpp -o CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.s

test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o.requires:

.PHONY : test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o.requires

test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o.provides: test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/test-alt-string.dir/build.make test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o.provides.build
.PHONY : test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o.provides

test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o.provides.build: test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o


# Object files for target test-alt-string
test__alt__string_OBJECTS = \
"CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o"

# External object files for target test-alt-string
test__alt__string_EXTERNAL_OBJECTS = \
"/home/bachmann/Downloads/json-develop/test/CMakeFiles/catch_main.dir/src/unit.cpp.o"

test/test-alt-string: test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o
test/test-alt-string: test/CMakeFiles/catch_main.dir/src/unit.cpp.o
test/test-alt-string: test/CMakeFiles/test-alt-string.dir/build.make
test/test-alt-string: test/CMakeFiles/test-alt-string.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bachmann/Downloads/json-develop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-alt-string"
	cd /home/bachmann/Downloads/json-develop/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-alt-string.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test-alt-string.dir/build: test/test-alt-string

.PHONY : test/CMakeFiles/test-alt-string.dir/build

test/CMakeFiles/test-alt-string.dir/requires: test/CMakeFiles/test-alt-string.dir/src/unit-alt-string.cpp.o.requires

.PHONY : test/CMakeFiles/test-alt-string.dir/requires

test/CMakeFiles/test-alt-string.dir/clean:
	cd /home/bachmann/Downloads/json-develop/test && $(CMAKE_COMMAND) -P CMakeFiles/test-alt-string.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test-alt-string.dir/clean

test/CMakeFiles/test-alt-string.dir/depend:
	cd /home/bachmann/Downloads/json-develop && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bachmann/Downloads/json-develop /home/bachmann/Downloads/json-develop/test /home/bachmann/Downloads/json-develop /home/bachmann/Downloads/json-develop/test /home/bachmann/Downloads/json-develop/test/CMakeFiles/test-alt-string.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test-alt-string.dir/depend

