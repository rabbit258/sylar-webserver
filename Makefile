# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fyx/sylar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fyx/sylar

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/fyx/sylar/CMakeFiles /home/fyx/sylar//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/fyx/sylar/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named sylar

# Build rule for target.
sylar: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 sylar
.PHONY : sylar

# fast build rule for target.
sylar/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/build
.PHONY : sylar/fast

#=============================================================================
# Target rules for targets named test

# Build rule for target.
test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test
.PHONY : test

# fast build rule for target.
test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/build
.PHONY : test/fast

#=============================================================================
# Target rules for targets named test_config

# Build rule for target.
test_config: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_config
.PHONY : test_config

# fast build rule for target.
test_config/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/build
.PHONY : test_config/fast

#=============================================================================
# Target rules for targets named test_thread

# Build rule for target.
test_thread: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_thread
.PHONY : test_thread

# fast build rule for target.
test_thread/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/build
.PHONY : test_thread/fast

#=============================================================================
# Target rules for targets named test_util

# Build rule for target.
test_util: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test_util
.PHONY : test_util

# fast build rule for target.
test_util/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/build
.PHONY : test_util/fast

sylar/config.o: sylar/config.cpp.o
.PHONY : sylar/config.o

# target to build an object file
sylar/config.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/config.cpp.o
.PHONY : sylar/config.cpp.o

sylar/config.i: sylar/config.cpp.i
.PHONY : sylar/config.i

# target to preprocess a source file
sylar/config.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/config.cpp.i
.PHONY : sylar/config.cpp.i

sylar/config.s: sylar/config.cpp.s
.PHONY : sylar/config.s

# target to generate assembly for a file
sylar/config.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/config.cpp.s
.PHONY : sylar/config.cpp.s

sylar/log.o: sylar/log.cpp.o
.PHONY : sylar/log.o

# target to build an object file
sylar/log.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/log.cpp.o
.PHONY : sylar/log.cpp.o

sylar/log.i: sylar/log.cpp.i
.PHONY : sylar/log.i

# target to preprocess a source file
sylar/log.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/log.cpp.i
.PHONY : sylar/log.cpp.i

sylar/log.s: sylar/log.cpp.s
.PHONY : sylar/log.s

# target to generate assembly for a file
sylar/log.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/log.cpp.s
.PHONY : sylar/log.cpp.s

sylar/thread.o: sylar/thread.cpp.o
.PHONY : sylar/thread.o

# target to build an object file
sylar/thread.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/thread.cpp.o
.PHONY : sylar/thread.cpp.o

sylar/thread.i: sylar/thread.cpp.i
.PHONY : sylar/thread.i

# target to preprocess a source file
sylar/thread.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/thread.cpp.i
.PHONY : sylar/thread.cpp.i

sylar/thread.s: sylar/thread.cpp.s
.PHONY : sylar/thread.s

# target to generate assembly for a file
sylar/thread.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/thread.cpp.s
.PHONY : sylar/thread.cpp.s

sylar/util.o: sylar/util.cpp.o
.PHONY : sylar/util.o

# target to build an object file
sylar/util.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/util.cpp.o
.PHONY : sylar/util.cpp.o

sylar/util.i: sylar/util.cpp.i
.PHONY : sylar/util.i

# target to preprocess a source file
sylar/util.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/util.cpp.i
.PHONY : sylar/util.cpp.i

sylar/util.s: sylar/util.cpp.s
.PHONY : sylar/util.s

# target to generate assembly for a file
sylar/util.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/sylar.dir/build.make CMakeFiles/sylar.dir/sylar/util.cpp.s
.PHONY : sylar/util.cpp.s

tests/test.o: tests/test.cpp.o
.PHONY : tests/test.o

# target to build an object file
tests/test.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cpp.o
.PHONY : tests/test.cpp.o

tests/test.i: tests/test.cpp.i
.PHONY : tests/test.i

# target to preprocess a source file
tests/test.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cpp.i
.PHONY : tests/test.cpp.i

tests/test.s: tests/test.cpp.s
.PHONY : tests/test.s

# target to generate assembly for a file
tests/test.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tests/test.cpp.s
.PHONY : tests/test.cpp.s

tests/test_config.o: tests/test_config.cpp.o
.PHONY : tests/test_config.o

# target to build an object file
tests/test_config.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cpp.o
.PHONY : tests/test_config.cpp.o

tests/test_config.i: tests/test_config.cpp.i
.PHONY : tests/test_config.i

# target to preprocess a source file
tests/test_config.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cpp.i
.PHONY : tests/test_config.cpp.i

tests/test_config.s: tests/test_config.cpp.s
.PHONY : tests/test_config.s

# target to generate assembly for a file
tests/test_config.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_config.dir/build.make CMakeFiles/test_config.dir/tests/test_config.cpp.s
.PHONY : tests/test_config.cpp.s

tests/test_thread.o: tests/test_thread.cpp.o
.PHONY : tests/test_thread.o

# target to build an object file
tests/test_thread.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cpp.o
.PHONY : tests/test_thread.cpp.o

tests/test_thread.i: tests/test_thread.cpp.i
.PHONY : tests/test_thread.i

# target to preprocess a source file
tests/test_thread.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cpp.i
.PHONY : tests/test_thread.cpp.i

tests/test_thread.s: tests/test_thread.cpp.s
.PHONY : tests/test_thread.s

# target to generate assembly for a file
tests/test_thread.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_thread.dir/build.make CMakeFiles/test_thread.dir/tests/test_thread.cpp.s
.PHONY : tests/test_thread.cpp.s

tests/test_util.o: tests/test_util.cpp.o
.PHONY : tests/test_util.o

# target to build an object file
tests/test_util.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cpp.o
.PHONY : tests/test_util.cpp.o

tests/test_util.i: tests/test_util.cpp.i
.PHONY : tests/test_util.i

# target to preprocess a source file
tests/test_util.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cpp.i
.PHONY : tests/test_util.cpp.i

tests/test_util.s: tests/test_util.cpp.s
.PHONY : tests/test_util.s

# target to generate assembly for a file
tests/test_util.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test_util.dir/build.make CMakeFiles/test_util.dir/tests/test_util.cpp.s
.PHONY : tests/test_util.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... sylar"
	@echo "... test"
	@echo "... test_config"
	@echo "... test_thread"
	@echo "... test_util"
	@echo "... sylar/config.o"
	@echo "... sylar/config.i"
	@echo "... sylar/config.s"
	@echo "... sylar/log.o"
	@echo "... sylar/log.i"
	@echo "... sylar/log.s"
	@echo "... sylar/thread.o"
	@echo "... sylar/thread.i"
	@echo "... sylar/thread.s"
	@echo "... sylar/util.o"
	@echo "... sylar/util.i"
	@echo "... sylar/util.s"
	@echo "... tests/test.o"
	@echo "... tests/test.i"
	@echo "... tests/test.s"
	@echo "... tests/test_config.o"
	@echo "... tests/test_config.i"
	@echo "... tests/test_config.s"
	@echo "... tests/test_thread.o"
	@echo "... tests/test_thread.i"
	@echo "... tests/test_thread.s"
	@echo "... tests/test_util.o"
	@echo "... tests/test_util.i"
	@echo "... tests/test_util.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

