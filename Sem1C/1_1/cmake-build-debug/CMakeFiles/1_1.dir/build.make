# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\adaml\CLionProjects\1_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\adaml\CLionProjects\1_1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\1_1.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\1_1.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\1_1.dir\flags.make

CMakeFiles\1_1.dir\main.c.obj: CMakeFiles\1_1.dir\flags.make
CMakeFiles\1_1.dir\main.c.obj: ..\main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\adaml\CLionProjects\1_1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/1_1.dir/main.c.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\1_1.dir\main.c.obj /FdCMakeFiles\1_1.dir\ /FS -c C:\Users\adaml\CLionProjects\1_1\main.c
<<

CMakeFiles\1_1.dir\main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/1_1.dir/main.c.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe > CMakeFiles\1_1.dir\main.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\adaml\CLionProjects\1_1\main.c
<<

CMakeFiles\1_1.dir\main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/1_1.dir/main.c.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\1_1.dir\main.c.s /c C:\Users\adaml\CLionProjects\1_1\main.c
<<

# Object files for target 1_1
1_1_OBJECTS = \
"CMakeFiles\1_1.dir\main.c.obj"

# External object files for target 1_1
1_1_EXTERNAL_OBJECTS =

1_1.exe: CMakeFiles\1_1.dir\main.c.obj
1_1.exe: CMakeFiles\1_1.dir\build.make
1_1.exe: CMakeFiles\1_1.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\adaml\CLionProjects\1_1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 1_1.exe"
	"C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\1_1.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\1_1.dir\objects1.rsp @<<
 /out:1_1.exe /implib:1_1.lib /pdb:C:\Users\adaml\CLionProjects\1_1\cmake-build-debug\1_1.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\1_1.dir\build: 1_1.exe

.PHONY : CMakeFiles\1_1.dir\build

CMakeFiles\1_1.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\1_1.dir\cmake_clean.cmake
.PHONY : CMakeFiles\1_1.dir\clean

CMakeFiles\1_1.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\adaml\CLionProjects\1_1 C:\Users\adaml\CLionProjects\1_1 C:\Users\adaml\CLionProjects\1_1\cmake-build-debug C:\Users\adaml\CLionProjects\1_1\cmake-build-debug C:\Users\adaml\CLionProjects\1_1\cmake-build-debug\CMakeFiles\1_1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\1_1.dir\depend
