# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/local/cmake/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/workspace/kyubi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/workspace/kyubi/build

# Include any dependencies generated for this target.
include CMakeFiles/kyubi.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kyubi.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kyubi.dir/flags.make

CMakeFiles/kyubi.dir/kyubi/log.cc.o: CMakeFiles/kyubi.dir/flags.make
CMakeFiles/kyubi.dir/kyubi/log.cc.o: ../kyubi/log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/kyubi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/kyubi.dir/kyubi/log.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"kyubi/log.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kyubi.dir/kyubi/log.cc.o -c /root/workspace/kyubi/kyubi/log.cc

CMakeFiles/kyubi.dir/kyubi/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kyubi.dir/kyubi/log.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"kyubi/log.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/kyubi/kyubi/log.cc > CMakeFiles/kyubi.dir/kyubi/log.cc.i

CMakeFiles/kyubi.dir/kyubi/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kyubi.dir/kyubi/log.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"kyubi/log.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/kyubi/kyubi/log.cc -o CMakeFiles/kyubi.dir/kyubi/log.cc.s

CMakeFiles/kyubi.dir/kyubi/util.cc.o: CMakeFiles/kyubi.dir/flags.make
CMakeFiles/kyubi.dir/kyubi/util.cc.o: ../kyubi/util.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/kyubi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/kyubi.dir/kyubi/util.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"kyubi/util.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kyubi.dir/kyubi/util.cc.o -c /root/workspace/kyubi/kyubi/util.cc

CMakeFiles/kyubi.dir/kyubi/util.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kyubi.dir/kyubi/util.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"kyubi/util.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/kyubi/kyubi/util.cc > CMakeFiles/kyubi.dir/kyubi/util.cc.i

CMakeFiles/kyubi.dir/kyubi/util.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kyubi.dir/kyubi/util.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"kyubi/util.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/kyubi/kyubi/util.cc -o CMakeFiles/kyubi.dir/kyubi/util.cc.s

CMakeFiles/kyubi.dir/kyubi/config.cc.o: CMakeFiles/kyubi.dir/flags.make
CMakeFiles/kyubi.dir/kyubi/config.cc.o: ../kyubi/config.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/kyubi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/kyubi.dir/kyubi/config.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"kyubi/config.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kyubi.dir/kyubi/config.cc.o -c /root/workspace/kyubi/kyubi/config.cc

CMakeFiles/kyubi.dir/kyubi/config.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kyubi.dir/kyubi/config.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"kyubi/config.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/kyubi/kyubi/config.cc > CMakeFiles/kyubi.dir/kyubi/config.cc.i

CMakeFiles/kyubi.dir/kyubi/config.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kyubi.dir/kyubi/config.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"kyubi/config.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/kyubi/kyubi/config.cc -o CMakeFiles/kyubi.dir/kyubi/config.cc.s

CMakeFiles/kyubi.dir/kyubi/thread.cc.o: CMakeFiles/kyubi.dir/flags.make
CMakeFiles/kyubi.dir/kyubi/thread.cc.o: ../kyubi/thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/kyubi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/kyubi.dir/kyubi/thread.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"kyubi/thread.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kyubi.dir/kyubi/thread.cc.o -c /root/workspace/kyubi/kyubi/thread.cc

CMakeFiles/kyubi.dir/kyubi/thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kyubi.dir/kyubi/thread.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"kyubi/thread.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/kyubi/kyubi/thread.cc > CMakeFiles/kyubi.dir/kyubi/thread.cc.i

CMakeFiles/kyubi.dir/kyubi/thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kyubi.dir/kyubi/thread.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"kyubi/thread.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/kyubi/kyubi/thread.cc -o CMakeFiles/kyubi.dir/kyubi/thread.cc.s

CMakeFiles/kyubi.dir/kyubi/fiber.cc.o: CMakeFiles/kyubi.dir/flags.make
CMakeFiles/kyubi.dir/kyubi/fiber.cc.o: ../kyubi/fiber.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/kyubi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/kyubi.dir/kyubi/fiber.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"kyubi/fiber.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kyubi.dir/kyubi/fiber.cc.o -c /root/workspace/kyubi/kyubi/fiber.cc

CMakeFiles/kyubi.dir/kyubi/fiber.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kyubi.dir/kyubi/fiber.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"kyubi/fiber.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/kyubi/kyubi/fiber.cc > CMakeFiles/kyubi.dir/kyubi/fiber.cc.i

CMakeFiles/kyubi.dir/kyubi/fiber.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kyubi.dir/kyubi/fiber.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"kyubi/fiber.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/kyubi/kyubi/fiber.cc -o CMakeFiles/kyubi.dir/kyubi/fiber.cc.s

CMakeFiles/kyubi.dir/kyubi/scheduler.cc.o: CMakeFiles/kyubi.dir/flags.make
CMakeFiles/kyubi.dir/kyubi/scheduler.cc.o: ../kyubi/scheduler.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/kyubi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/kyubi.dir/kyubi/scheduler.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"kyubi/scheduler.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kyubi.dir/kyubi/scheduler.cc.o -c /root/workspace/kyubi/kyubi/scheduler.cc

CMakeFiles/kyubi.dir/kyubi/scheduler.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kyubi.dir/kyubi/scheduler.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"kyubi/scheduler.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/kyubi/kyubi/scheduler.cc > CMakeFiles/kyubi.dir/kyubi/scheduler.cc.i

CMakeFiles/kyubi.dir/kyubi/scheduler.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kyubi.dir/kyubi/scheduler.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"kyubi/scheduler.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/kyubi/kyubi/scheduler.cc -o CMakeFiles/kyubi.dir/kyubi/scheduler.cc.s

# Object files for target kyubi
kyubi_OBJECTS = \
"CMakeFiles/kyubi.dir/kyubi/log.cc.o" \
"CMakeFiles/kyubi.dir/kyubi/util.cc.o" \
"CMakeFiles/kyubi.dir/kyubi/config.cc.o" \
"CMakeFiles/kyubi.dir/kyubi/thread.cc.o" \
"CMakeFiles/kyubi.dir/kyubi/fiber.cc.o" \
"CMakeFiles/kyubi.dir/kyubi/scheduler.cc.o"

# External object files for target kyubi
kyubi_EXTERNAL_OBJECTS =

../lib/libkyubi.so: CMakeFiles/kyubi.dir/kyubi/log.cc.o
../lib/libkyubi.so: CMakeFiles/kyubi.dir/kyubi/util.cc.o
../lib/libkyubi.so: CMakeFiles/kyubi.dir/kyubi/config.cc.o
../lib/libkyubi.so: CMakeFiles/kyubi.dir/kyubi/thread.cc.o
../lib/libkyubi.so: CMakeFiles/kyubi.dir/kyubi/fiber.cc.o
../lib/libkyubi.so: CMakeFiles/kyubi.dir/kyubi/scheduler.cc.o
../lib/libkyubi.so: CMakeFiles/kyubi.dir/build.make
../lib/libkyubi.so: CMakeFiles/kyubi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/workspace/kyubi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX shared library ../lib/libkyubi.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kyubi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kyubi.dir/build: ../lib/libkyubi.so

.PHONY : CMakeFiles/kyubi.dir/build

CMakeFiles/kyubi.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kyubi.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kyubi.dir/clean

CMakeFiles/kyubi.dir/depend:
	cd /root/workspace/kyubi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/workspace/kyubi /root/workspace/kyubi /root/workspace/kyubi/build /root/workspace/kyubi/build /root/workspace/kyubi/build/CMakeFiles/kyubi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kyubi.dir/depend

