# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/richardgermond/cdms/daq

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/richardgermond/cdms/daq/build

# Include any dependencies generated for this target.
include CMakeFiles/CUTE_DAQ.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CUTE_DAQ.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CUTE_DAQ.dir/flags.make

CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o: CMakeFiles/CUTE_DAQ.dir/flags.make
CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o: ../src/daq.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/richardgermond/cdms/daq/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o -c /home/richardgermond/cdms/daq/src/daq.cpp

CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/richardgermond/cdms/daq/src/daq.cpp > CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.i

CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/richardgermond/cdms/daq/src/daq.cpp -o CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.s

CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o.requires:

.PHONY : CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o.requires

CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o.provides: CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o.requires
	$(MAKE) -f CMakeFiles/CUTE_DAQ.dir/build.make CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o.provides.build
.PHONY : CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o.provides

CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o.provides.build: CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o


# Object files for target CUTE_DAQ
CUTE_DAQ_OBJECTS = \
"CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o"

# External object files for target CUTE_DAQ
CUTE_DAQ_EXTERNAL_OBJECTS =

../bin/CUTE_DAQ: CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o
../bin/CUTE_DAQ: CMakeFiles/CUTE_DAQ.dir/build.make
../bin/CUTE_DAQ: CMakeFiles/CUTE_DAQ.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/richardgermond/cdms/daq/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/CUTE_DAQ"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CUTE_DAQ.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CUTE_DAQ.dir/build: ../bin/CUTE_DAQ

.PHONY : CMakeFiles/CUTE_DAQ.dir/build

CMakeFiles/CUTE_DAQ.dir/requires: CMakeFiles/CUTE_DAQ.dir/src/daq.cpp.o.requires

.PHONY : CMakeFiles/CUTE_DAQ.dir/requires

CMakeFiles/CUTE_DAQ.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CUTE_DAQ.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CUTE_DAQ.dir/clean

CMakeFiles/CUTE_DAQ.dir/depend:
	cd /home/richardgermond/cdms/daq/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/richardgermond/cdms/daq /home/richardgermond/cdms/daq /home/richardgermond/cdms/daq/build /home/richardgermond/cdms/daq/build /home/richardgermond/cdms/daq/build/CMakeFiles/CUTE_DAQ.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CUTE_DAQ.dir/depend

