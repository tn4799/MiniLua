# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild

# Utility rule file for tree-sitter-populate.

# Include the progress variables for this target.
include CMakeFiles/tree-sitter-populate.dir/progress.make

CMakeFiles/tree-sitter-populate: CMakeFiles/tree-sitter-populate-complete


CMakeFiles/tree-sitter-populate-complete: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-install
CMakeFiles/tree-sitter-populate-complete: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-mkdir
CMakeFiles/tree-sitter-populate-complete: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-download
CMakeFiles/tree-sitter-populate-complete: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-update
CMakeFiles/tree-sitter-populate-complete: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-patch
CMakeFiles/tree-sitter-populate-complete: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-configure
CMakeFiles/tree-sitter-populate-complete: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-build
CMakeFiles/tree-sitter-populate-complete: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-install
CMakeFiles/tree-sitter-populate-complete: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'tree-sitter-populate'"
	/usr/bin/cmake -E make_directory /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/CMakeFiles
	/usr/bin/cmake -E touch /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/CMakeFiles/tree-sitter-populate-complete
	/usr/bin/cmake -E touch /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-done

tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-install: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No install step for 'tree-sitter-populate'"
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-build && /usr/bin/cmake -E echo_append
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-build && /usr/bin/cmake -E touch /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-install

tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'tree-sitter-populate'"
	/usr/bin/cmake -E make_directory /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-src
	/usr/bin/cmake -E make_directory /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-build
	/usr/bin/cmake -E make_directory /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix
	/usr/bin/cmake -E make_directory /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/tmp
	/usr/bin/cmake -E make_directory /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/src/tree-sitter-populate-stamp
	/usr/bin/cmake -E make_directory /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/src
	/usr/bin/cmake -E make_directory /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/src/tree-sitter-populate-stamp
	/usr/bin/cmake -E touch /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-mkdir

tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-download: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-gitinfo.txt
tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-download: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'tree-sitter-populate'"
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps && /usr/bin/cmake -P /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/tmp/tree-sitter-populate-gitclone.cmake
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps && /usr/bin/cmake -E touch /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-download

tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-update: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Performing update step for 'tree-sitter-populate'"
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-src && /usr/bin/cmake -P /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/tmp/tree-sitter-populate-gitupdate.cmake

tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-patch: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No patch step for 'tree-sitter-populate'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-patch

tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-configure: tree-sitter-populate-prefix/tmp/tree-sitter-populate-cfgcmd.txt
tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-configure: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No configure step for 'tree-sitter-populate'"
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-build && /usr/bin/cmake -E echo_append
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-build && /usr/bin/cmake -E touch /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-configure

tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-build: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No build step for 'tree-sitter-populate'"
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-build && /usr/bin/cmake -E echo_append
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-build && /usr/bin/cmake -E touch /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-build

tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-test: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "No test step for 'tree-sitter-populate'"
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-build && /usr/bin/cmake -E echo_append
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-build && /usr/bin/cmake -E touch /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-test

tree-sitter-populate: CMakeFiles/tree-sitter-populate
tree-sitter-populate: CMakeFiles/tree-sitter-populate-complete
tree-sitter-populate: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-install
tree-sitter-populate: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-mkdir
tree-sitter-populate: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-download
tree-sitter-populate: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-update
tree-sitter-populate: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-patch
tree-sitter-populate: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-configure
tree-sitter-populate: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-build
tree-sitter-populate: tree-sitter-populate-prefix/src/tree-sitter-populate-stamp/tree-sitter-populate-test
tree-sitter-populate: CMakeFiles/tree-sitter-populate.dir/build.make

.PHONY : tree-sitter-populate

# Rule to build all files generated by this target.
CMakeFiles/tree-sitter-populate.dir/build: tree-sitter-populate

.PHONY : CMakeFiles/tree-sitter-populate.dir/build

CMakeFiles/tree-sitter-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tree-sitter-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tree-sitter-populate.dir/clean

CMakeFiles/tree-sitter-populate.dir/depend:
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/_deps/tree-sitter-subbuild/CMakeFiles/tree-sitter-populate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tree-sitter-populate.dir/depend
