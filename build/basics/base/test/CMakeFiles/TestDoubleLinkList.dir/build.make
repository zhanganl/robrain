# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /srv/robrain

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /srv/robrain/output

# Include any dependencies generated for this target.
include ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/depend.make

# Include the progress variables for this target.
include ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/progress.make

# Include the compile flags for this target's objects.
include ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/flags.make

../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o: ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/flags.make
../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o: ../basics/base/test/TestDoubleLinkList.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/srv/robrain/output/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o"
	cd /srv/robrain/build/basics/base/test && g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o -c /srv/robrain/basics/base/test/TestDoubleLinkList.cpp

../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.i"
	cd /srv/robrain/build/basics/base/test && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /srv/robrain/basics/base/test/TestDoubleLinkList.cpp > CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.i

../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.s"
	cd /srv/robrain/build/basics/base/test && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /srv/robrain/basics/base/test/TestDoubleLinkList.cpp -o CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.s

../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o.requires:

.PHONY : ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o.requires

../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o.provides: ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o.requires
	$(MAKE) -f ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/build.make ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o.provides.build
.PHONY : ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o.provides

../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o.provides.build: ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o


# Object files for target TestDoubleLinkList
TestDoubleLinkList_OBJECTS = \
"CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o"

# External object files for target TestDoubleLinkList
TestDoubleLinkList_EXTERNAL_OBJECTS =

../out/basics/base/test/TestDoubleLinkList: ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o
../out/basics/base/test/TestDoubleLinkList: ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/build.make
../out/basics/base/test/TestDoubleLinkList: ../build/basics/base/src/libbase.a
../out/basics/base/test/TestDoubleLinkList: ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/srv/robrain/output/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../../out/basics/base/test/TestDoubleLinkList"
	cd /srv/robrain/build/basics/base/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestDoubleLinkList.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/build: ../out/basics/base/test/TestDoubleLinkList

.PHONY : ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/build

../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/requires: ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/TestDoubleLinkList.cpp.o.requires

.PHONY : ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/requires

../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/clean:
	cd /srv/robrain/build/basics/base/test && $(CMAKE_COMMAND) -P CMakeFiles/TestDoubleLinkList.dir/cmake_clean.cmake
.PHONY : ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/clean

../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/depend:
	cd /srv/robrain/output && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /srv/robrain /srv/robrain/basics/base/test /srv/robrain/output /srv/robrain/build/basics/base/test /srv/robrain/build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ../build/basics/base/test/CMakeFiles/TestDoubleLinkList.dir/depend
