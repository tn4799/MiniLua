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
CMAKE_SOURCE_DIR = /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua

# Utility rule file for TreeSitter_PRIVATE.

# Include the progress variables for this target.
include CMakeFiles/TreeSitter_PRIVATE.dir/progress.make

CMakeFiles/TreeSitter_PRIVATE: libtree-sitter.a


libtree-sitter.a:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building Tree-Sitter"
	make -C /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/extern/tree-sitter libtree-sitter.a

TreeSitter_PRIVATE: CMakeFiles/TreeSitter_PRIVATE
TreeSitter_PRIVATE: libtree-sitter.a
TreeSitter_PRIVATE: CMakeFiles/TreeSitter_PRIVATE.dir/build.make

.PHONY : TreeSitter_PRIVATE

# Rule to build all files generated by this target.
CMakeFiles/TreeSitter_PRIVATE.dir/build: TreeSitter_PRIVATE

.PHONY : CMakeFiles/TreeSitter_PRIVATE.dir/build

CMakeFiles/TreeSitter_PRIVATE.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TreeSitter_PRIVATE.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TreeSitter_PRIVATE.dir/clean

CMakeFiles/TreeSitter_PRIVATE.dir/depend:
	cd /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua /home/tim/Documents/Anwendungsprojekt/Bachelor/MiniLua/CMakeFiles/TreeSitter_PRIVATE.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TreeSitter_PRIVATE.dir/depend
