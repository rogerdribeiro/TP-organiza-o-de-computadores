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
CMAKE_COMMAND = /home/rogerd/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.5087.36/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/rogerd/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.5087.36/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/TP3_versao2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TP3_versao2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TP3_versao2.dir/flags.make

CMakeFiles/TP3_versao2.dir/main.cpp.o: CMakeFiles/TP3_versao2.dir/flags.make
CMakeFiles/TP3_versao2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TP3_versao2.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP3_versao2.dir/main.cpp.o -c "/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2/main.cpp"

CMakeFiles/TP3_versao2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP3_versao2.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2/main.cpp" > CMakeFiles/TP3_versao2.dir/main.cpp.i

CMakeFiles/TP3_versao2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP3_versao2.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2/main.cpp" -o CMakeFiles/TP3_versao2.dir/main.cpp.s

CMakeFiles/TP3_versao2.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/TP3_versao2.dir/main.cpp.o.requires

CMakeFiles/TP3_versao2.dir/main.cpp.o.provides: CMakeFiles/TP3_versao2.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/TP3_versao2.dir/build.make CMakeFiles/TP3_versao2.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/TP3_versao2.dir/main.cpp.o.provides

CMakeFiles/TP3_versao2.dir/main.cpp.o.provides.build: CMakeFiles/TP3_versao2.dir/main.cpp.o


# Object files for target TP3_versao2
TP3_versao2_OBJECTS = \
"CMakeFiles/TP3_versao2.dir/main.cpp.o"

# External object files for target TP3_versao2
TP3_versao2_EXTERNAL_OBJECTS =

TP3_versao2: CMakeFiles/TP3_versao2.dir/main.cpp.o
TP3_versao2: CMakeFiles/TP3_versao2.dir/build.make
TP3_versao2: CMakeFiles/TP3_versao2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP3_versao2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP3_versao2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TP3_versao2.dir/build: TP3_versao2

.PHONY : CMakeFiles/TP3_versao2.dir/build

CMakeFiles/TP3_versao2.dir/requires: CMakeFiles/TP3_versao2.dir/main.cpp.o.requires

.PHONY : CMakeFiles/TP3_versao2.dir/requires

CMakeFiles/TP3_versao2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TP3_versao2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TP3_versao2.dir/clean

CMakeFiles/TP3_versao2.dir/depend:
	cd "/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2" "/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2" "/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2/cmake-build-debug" "/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2/cmake-build-debug" "/media/rogerd/OS/Program Files (x86)/Atalho para Rogerd/Computer Science/5 PERIODO/Org.Computadores/TP3/TP3_versao2/cmake-build-debug/CMakeFiles/TP3_versao2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/TP3_versao2.dir/depend

