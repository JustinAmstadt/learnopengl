# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/justin/learnopengl/learnopengl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/justin/learnopengl/learnopengl/build

# Include any dependencies generated for this target.
include CMakeFiles/learnopengl.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/learnopengl.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/learnopengl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/learnopengl.dir/flags.make

CMakeFiles/learnopengl.dir/Main.cpp.o: CMakeFiles/learnopengl.dir/flags.make
CMakeFiles/learnopengl.dir/Main.cpp.o: ../Main.cpp
CMakeFiles/learnopengl.dir/Main.cpp.o: CMakeFiles/learnopengl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/justin/learnopengl/learnopengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/learnopengl.dir/Main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/learnopengl.dir/Main.cpp.o -MF CMakeFiles/learnopengl.dir/Main.cpp.o.d -o CMakeFiles/learnopengl.dir/Main.cpp.o -c /home/justin/learnopengl/learnopengl/Main.cpp

CMakeFiles/learnopengl.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/learnopengl.dir/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/justin/learnopengl/learnopengl/Main.cpp > CMakeFiles/learnopengl.dir/Main.cpp.i

CMakeFiles/learnopengl.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/learnopengl.dir/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/justin/learnopengl/learnopengl/Main.cpp -o CMakeFiles/learnopengl.dir/Main.cpp.s

CMakeFiles/learnopengl.dir/Scene.cpp.o: CMakeFiles/learnopengl.dir/flags.make
CMakeFiles/learnopengl.dir/Scene.cpp.o: ../Scene.cpp
CMakeFiles/learnopengl.dir/Scene.cpp.o: CMakeFiles/learnopengl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/justin/learnopengl/learnopengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/learnopengl.dir/Scene.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/learnopengl.dir/Scene.cpp.o -MF CMakeFiles/learnopengl.dir/Scene.cpp.o.d -o CMakeFiles/learnopengl.dir/Scene.cpp.o -c /home/justin/learnopengl/learnopengl/Scene.cpp

CMakeFiles/learnopengl.dir/Scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/learnopengl.dir/Scene.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/justin/learnopengl/learnopengl/Scene.cpp > CMakeFiles/learnopengl.dir/Scene.cpp.i

CMakeFiles/learnopengl.dir/Scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/learnopengl.dir/Scene.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/justin/learnopengl/learnopengl/Scene.cpp -o CMakeFiles/learnopengl.dir/Scene.cpp.s

CMakeFiles/learnopengl.dir/Shader.cpp.o: CMakeFiles/learnopengl.dir/flags.make
CMakeFiles/learnopengl.dir/Shader.cpp.o: ../Shader.cpp
CMakeFiles/learnopengl.dir/Shader.cpp.o: CMakeFiles/learnopengl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/justin/learnopengl/learnopengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/learnopengl.dir/Shader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/learnopengl.dir/Shader.cpp.o -MF CMakeFiles/learnopengl.dir/Shader.cpp.o.d -o CMakeFiles/learnopengl.dir/Shader.cpp.o -c /home/justin/learnopengl/learnopengl/Shader.cpp

CMakeFiles/learnopengl.dir/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/learnopengl.dir/Shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/justin/learnopengl/learnopengl/Shader.cpp > CMakeFiles/learnopengl.dir/Shader.cpp.i

CMakeFiles/learnopengl.dir/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/learnopengl.dir/Shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/justin/learnopengl/learnopengl/Shader.cpp -o CMakeFiles/learnopengl.dir/Shader.cpp.s

CMakeFiles/learnopengl.dir/ObjectData.cpp.o: CMakeFiles/learnopengl.dir/flags.make
CMakeFiles/learnopengl.dir/ObjectData.cpp.o: ../ObjectData.cpp
CMakeFiles/learnopengl.dir/ObjectData.cpp.o: CMakeFiles/learnopengl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/justin/learnopengl/learnopengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/learnopengl.dir/ObjectData.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/learnopengl.dir/ObjectData.cpp.o -MF CMakeFiles/learnopengl.dir/ObjectData.cpp.o.d -o CMakeFiles/learnopengl.dir/ObjectData.cpp.o -c /home/justin/learnopengl/learnopengl/ObjectData.cpp

CMakeFiles/learnopengl.dir/ObjectData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/learnopengl.dir/ObjectData.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/justin/learnopengl/learnopengl/ObjectData.cpp > CMakeFiles/learnopengl.dir/ObjectData.cpp.i

CMakeFiles/learnopengl.dir/ObjectData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/learnopengl.dir/ObjectData.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/justin/learnopengl/learnopengl/ObjectData.cpp -o CMakeFiles/learnopengl.dir/ObjectData.cpp.s

CMakeFiles/learnopengl.dir/GeometricObject.cpp.o: CMakeFiles/learnopengl.dir/flags.make
CMakeFiles/learnopengl.dir/GeometricObject.cpp.o: ../GeometricObject.cpp
CMakeFiles/learnopengl.dir/GeometricObject.cpp.o: CMakeFiles/learnopengl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/justin/learnopengl/learnopengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/learnopengl.dir/GeometricObject.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/learnopengl.dir/GeometricObject.cpp.o -MF CMakeFiles/learnopengl.dir/GeometricObject.cpp.o.d -o CMakeFiles/learnopengl.dir/GeometricObject.cpp.o -c /home/justin/learnopengl/learnopengl/GeometricObject.cpp

CMakeFiles/learnopengl.dir/GeometricObject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/learnopengl.dir/GeometricObject.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/justin/learnopengl/learnopengl/GeometricObject.cpp > CMakeFiles/learnopengl.dir/GeometricObject.cpp.i

CMakeFiles/learnopengl.dir/GeometricObject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/learnopengl.dir/GeometricObject.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/justin/learnopengl/learnopengl/GeometricObject.cpp -o CMakeFiles/learnopengl.dir/GeometricObject.cpp.s

CMakeFiles/learnopengl.dir/CircularParabola.cpp.o: CMakeFiles/learnopengl.dir/flags.make
CMakeFiles/learnopengl.dir/CircularParabola.cpp.o: ../CircularParabola.cpp
CMakeFiles/learnopengl.dir/CircularParabola.cpp.o: CMakeFiles/learnopengl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/justin/learnopengl/learnopengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/learnopengl.dir/CircularParabola.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/learnopengl.dir/CircularParabola.cpp.o -MF CMakeFiles/learnopengl.dir/CircularParabola.cpp.o.d -o CMakeFiles/learnopengl.dir/CircularParabola.cpp.o -c /home/justin/learnopengl/learnopengl/CircularParabola.cpp

CMakeFiles/learnopengl.dir/CircularParabola.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/learnopengl.dir/CircularParabola.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/justin/learnopengl/learnopengl/CircularParabola.cpp > CMakeFiles/learnopengl.dir/CircularParabola.cpp.i

CMakeFiles/learnopengl.dir/CircularParabola.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/learnopengl.dir/CircularParabola.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/justin/learnopengl/learnopengl/CircularParabola.cpp -o CMakeFiles/learnopengl.dir/CircularParabola.cpp.s

CMakeFiles/learnopengl.dir/Pipe.cpp.o: CMakeFiles/learnopengl.dir/flags.make
CMakeFiles/learnopengl.dir/Pipe.cpp.o: ../Pipe.cpp
CMakeFiles/learnopengl.dir/Pipe.cpp.o: CMakeFiles/learnopengl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/justin/learnopengl/learnopengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/learnopengl.dir/Pipe.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/learnopengl.dir/Pipe.cpp.o -MF CMakeFiles/learnopengl.dir/Pipe.cpp.o.d -o CMakeFiles/learnopengl.dir/Pipe.cpp.o -c /home/justin/learnopengl/learnopengl/Pipe.cpp

CMakeFiles/learnopengl.dir/Pipe.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/learnopengl.dir/Pipe.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/justin/learnopengl/learnopengl/Pipe.cpp > CMakeFiles/learnopengl.dir/Pipe.cpp.i

CMakeFiles/learnopengl.dir/Pipe.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/learnopengl.dir/Pipe.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/justin/learnopengl/learnopengl/Pipe.cpp -o CMakeFiles/learnopengl.dir/Pipe.cpp.s

CMakeFiles/learnopengl.dir/Dragonfly.cpp.o: CMakeFiles/learnopengl.dir/flags.make
CMakeFiles/learnopengl.dir/Dragonfly.cpp.o: ../Dragonfly.cpp
CMakeFiles/learnopengl.dir/Dragonfly.cpp.o: CMakeFiles/learnopengl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/justin/learnopengl/learnopengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/learnopengl.dir/Dragonfly.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/learnopengl.dir/Dragonfly.cpp.o -MF CMakeFiles/learnopengl.dir/Dragonfly.cpp.o.d -o CMakeFiles/learnopengl.dir/Dragonfly.cpp.o -c /home/justin/learnopengl/learnopengl/Dragonfly.cpp

CMakeFiles/learnopengl.dir/Dragonfly.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/learnopengl.dir/Dragonfly.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/justin/learnopengl/learnopengl/Dragonfly.cpp > CMakeFiles/learnopengl.dir/Dragonfly.cpp.i

CMakeFiles/learnopengl.dir/Dragonfly.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/learnopengl.dir/Dragonfly.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/justin/learnopengl/learnopengl/Dragonfly.cpp -o CMakeFiles/learnopengl.dir/Dragonfly.cpp.s

# Object files for target learnopengl
learnopengl_OBJECTS = \
"CMakeFiles/learnopengl.dir/Main.cpp.o" \
"CMakeFiles/learnopengl.dir/Scene.cpp.o" \
"CMakeFiles/learnopengl.dir/Shader.cpp.o" \
"CMakeFiles/learnopengl.dir/ObjectData.cpp.o" \
"CMakeFiles/learnopengl.dir/GeometricObject.cpp.o" \
"CMakeFiles/learnopengl.dir/CircularParabola.cpp.o" \
"CMakeFiles/learnopengl.dir/Pipe.cpp.o" \
"CMakeFiles/learnopengl.dir/Dragonfly.cpp.o"

# External object files for target learnopengl
learnopengl_EXTERNAL_OBJECTS =

learnopengl: CMakeFiles/learnopengl.dir/Main.cpp.o
learnopengl: CMakeFiles/learnopengl.dir/Scene.cpp.o
learnopengl: CMakeFiles/learnopengl.dir/Shader.cpp.o
learnopengl: CMakeFiles/learnopengl.dir/ObjectData.cpp.o
learnopengl: CMakeFiles/learnopengl.dir/GeometricObject.cpp.o
learnopengl: CMakeFiles/learnopengl.dir/CircularParabola.cpp.o
learnopengl: CMakeFiles/learnopengl.dir/Pipe.cpp.o
learnopengl: CMakeFiles/learnopengl.dir/Dragonfly.cpp.o
learnopengl: CMakeFiles/learnopengl.dir/build.make
learnopengl: /usr/lib/x86_64-linux-gnu/libOpenGL.so
learnopengl: /usr/lib/x86_64-linux-gnu/libGLX.so
learnopengl: /usr/lib/x86_64-linux-gnu/libGLU.so
learnopengl: /usr/local/lib/libglfw3.a
learnopengl: libglad.a
learnopengl: /usr/lib/x86_64-linux-gnu/libassimp.so.5.2.0
learnopengl: /usr/lib/x86_64-linux-gnu/libm.so
learnopengl: /usr/lib/x86_64-linux-gnu/libz.so
learnopengl: /usr/lib/x86_64-linux-gnu/libdraco.so.4.0.0
learnopengl: /usr/lib/x86_64-linux-gnu/librt.a
learnopengl: CMakeFiles/learnopengl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/justin/learnopengl/learnopengl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable learnopengl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/learnopengl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/learnopengl.dir/build: learnopengl
.PHONY : CMakeFiles/learnopengl.dir/build

CMakeFiles/learnopengl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/learnopengl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/learnopengl.dir/clean

CMakeFiles/learnopengl.dir/depend:
	cd /home/justin/learnopengl/learnopengl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/justin/learnopengl/learnopengl /home/justin/learnopengl/learnopengl /home/justin/learnopengl/learnopengl/build /home/justin/learnopengl/learnopengl/build /home/justin/learnopengl/learnopengl/build/CMakeFiles/learnopengl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/learnopengl.dir/depend

