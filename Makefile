# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Projects\MIB2DOC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Projects\MIB2DOC

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"C:\Program Files\CMake\bin\cmake.exe" -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	"C:\Program Files\CMake\bin\cmake-gui.exe" -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start D:\Projects\MIB2DOC\CMakeFiles D:\Projects\MIB2DOC\CMakeFiles\progress.marks
	$(MAKE) -f CMakeFiles\Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start D:\Projects\MIB2DOC\CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles\Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Mib2Doc

# Build rule for target.
Mib2Doc: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 Mib2Doc
.PHONY : Mib2Doc

# fast build rule for target.
Mib2Doc/fast:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/build
.PHONY : Mib2Doc/fast

#=============================================================================
# Target rules for targets named UNIT_TEST

# Build rule for target.
UNIT_TEST: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 UNIT_TEST
.PHONY : UNIT_TEST

# fast build rule for target.
UNIT_TEST/fast:
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/build
.PHONY : UNIT_TEST/fast

#=============================================================================
# Target rules for targets named lexBison

# Build rule for target.
lexBison: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 lexBison
.PHONY : lexBison

# fast build rule for target.
lexBison/fast:
	$(MAKE) -f CMakeFiles\lexBison.dir\build.make CMakeFiles/lexBison.dir/build
.PHONY : lexBison/fast

#=============================================================================
# Target rules for targets named lexBison_H

# Build rule for target.
lexBison_H: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 lexBison_H
.PHONY : lexBison_H

# fast build rule for target.
lexBison_H/fast:
	$(MAKE) -f CMakeFiles\lexBison_H.dir\build.make CMakeFiles/lexBison_H.dir/build
.PHONY : lexBison_H/fast

src/dispatcher.obj: src/dispatcher.c.obj

.PHONY : src/dispatcher.obj

# target to build an object file
src/dispatcher.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/dispatcher.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/dispatcher.c.obj
.PHONY : src/dispatcher.c.obj

src/dispatcher.i: src/dispatcher.c.i

.PHONY : src/dispatcher.i

# target to preprocess a source file
src/dispatcher.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/dispatcher.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/dispatcher.c.i
.PHONY : src/dispatcher.c.i

src/dispatcher.s: src/dispatcher.c.s

.PHONY : src/dispatcher.s

# target to generate assembly for a file
src/dispatcher.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/dispatcher.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/dispatcher.c.s
.PHONY : src/dispatcher.c.s

src/docGenerate.obj: src/docGenerate.c.obj

.PHONY : src/docGenerate.obj

# target to build an object file
src/docGenerate.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/docGenerate.c.obj
.PHONY : src/docGenerate.c.obj

src/docGenerate.i: src/docGenerate.c.i

.PHONY : src/docGenerate.i

# target to preprocess a source file
src/docGenerate.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/docGenerate.c.i
.PHONY : src/docGenerate.c.i

src/docGenerate.s: src/docGenerate.c.s

.PHONY : src/docGenerate.s

# target to generate assembly for a file
src/docGenerate.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/docGenerate.c.s
.PHONY : src/docGenerate.c.s

src/hash.obj: src/hash.c.obj

.PHONY : src/hash.obj

# target to build an object file
src/hash.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/hash.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/hash.c.obj
.PHONY : src/hash.c.obj

src/hash.i: src/hash.c.i

.PHONY : src/hash.i

# target to preprocess a source file
src/hash.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/hash.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/hash.c.i
.PHONY : src/hash.c.i

src/hash.s: src/hash.c.s

.PHONY : src/hash.s

# target to generate assembly for a file
src/hash.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/hash.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/hash.c.s
.PHONY : src/hash.c.s

src/lexDeal.obj: src/lexDeal.c.obj

.PHONY : src/lexDeal.obj

# target to build an object file
src/lexDeal.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/lexDeal.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/lexDeal.c.obj
.PHONY : src/lexDeal.c.obj

src/lexDeal.i: src/lexDeal.c.i

.PHONY : src/lexDeal.i

# target to preprocess a source file
src/lexDeal.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/lexDeal.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/lexDeal.c.i
.PHONY : src/lexDeal.c.i

src/lexDeal.s: src/lexDeal.c.s

.PHONY : src/lexDeal.s

# target to generate assembly for a file
src/lexDeal.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/lexDeal.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/lexDeal.c.s
.PHONY : src/lexDeal.c.s

src/lexer.obj: src/lexer.c.obj

.PHONY : src/lexer.obj

# target to build an object file
src/lexer.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/lexer.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/lexer.c.obj
.PHONY : src/lexer.c.obj

src/lexer.i: src/lexer.c.i

.PHONY : src/lexer.i

# target to preprocess a source file
src/lexer.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/lexer.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/lexer.c.i
.PHONY : src/lexer.c.i

src/lexer.s: src/lexer.c.s

.PHONY : src/lexer.s

# target to generate assembly for a file
src/lexer.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/lexer.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/lexer.c.s
.PHONY : src/lexer.c.s

src/list.obj: src/list.c.obj

.PHONY : src/list.obj

# target to build an object file
src/list.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/list.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/list.c.obj
.PHONY : src/list.c.obj

src/list.i: src/list.c.i

.PHONY : src/list.i

# target to preprocess a source file
src/list.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/list.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/list.c.i
.PHONY : src/list.c.i

src/list.s: src/list.c.s

.PHONY : src/list.s

# target to generate assembly for a file
src/list.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/list.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/list.c.s
.PHONY : src/list.c.s

src/main.obj: src/main.c.obj

.PHONY : src/main.obj

# target to build an object file
src/main.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/main.c.obj
.PHONY : src/main.c.obj

src/main.i: src/main.c.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/main.c.s
.PHONY : src/main.c.s

src/mibTreeGen.obj: src/mibTreeGen.c.obj

.PHONY : src/mibTreeGen.obj

# target to build an object file
src/mibTreeGen.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/mibTreeGen.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/mibTreeGen.c.obj
.PHONY : src/mibTreeGen.c.obj

src/mibTreeGen.i: src/mibTreeGen.c.i

.PHONY : src/mibTreeGen.i

# target to preprocess a source file
src/mibTreeGen.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/mibTreeGen.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/mibTreeGen.c.i
.PHONY : src/mibTreeGen.c.i

src/mibTreeGen.s: src/mibTreeGen.c.s

.PHONY : src/mibTreeGen.s

# target to generate assembly for a file
src/mibTreeGen.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/mibTreeGen.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/mibTreeGen.c.s
.PHONY : src/mibTreeGen.c.s

src/mibTreeObjTree.obj: src/mibTreeObjTree.c.obj

.PHONY : src/mibTreeObjTree.obj

# target to build an object file
src/mibTreeObjTree.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/mibTreeObjTree.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/mibTreeObjTree.c.obj
.PHONY : src/mibTreeObjTree.c.obj

src/mibTreeObjTree.i: src/mibTreeObjTree.c.i

.PHONY : src/mibTreeObjTree.i

# target to preprocess a source file
src/mibTreeObjTree.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/mibTreeObjTree.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/mibTreeObjTree.c.i
.PHONY : src/mibTreeObjTree.c.i

src/mibTreeObjTree.s: src/mibTreeObjTree.c.s

.PHONY : src/mibTreeObjTree.s

# target to generate assembly for a file
src/mibTreeObjTree.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/mibTreeObjTree.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/mibTreeObjTree.c.s
.PHONY : src/mibTreeObjTree.c.s

src/misc.obj: src/misc.c.obj

.PHONY : src/misc.obj

# target to build an object file
src/misc.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/misc.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/misc.c.obj
.PHONY : src/misc.c.obj

src/misc.i: src/misc.c.i

.PHONY : src/misc.i

# target to preprocess a source file
src/misc.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/misc.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/misc.c.i
.PHONY : src/misc.c.i

src/misc.s: src/misc.c.s

.PHONY : src/misc.s

# target to generate assembly for a file
src/misc.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/misc.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/misc.c.s
.PHONY : src/misc.c.s

src/options.obj: src/options.c.obj

.PHONY : src/options.obj

# target to build an object file
src/options.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/options.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/options.c.obj
.PHONY : src/options.c.obj

src/options.i: src/options.c.i

.PHONY : src/options.i

# target to preprocess a source file
src/options.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/options.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/options.c.i
.PHONY : src/options.c.i

src/options.s: src/options.c.s

.PHONY : src/options.s

# target to generate assembly for a file
src/options.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/options.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/options.c.s
.PHONY : src/options.c.s

src/queue.obj: src/queue.c.obj

.PHONY : src/queue.obj

# target to build an object file
src/queue.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/queue.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/queue.c.obj
.PHONY : src/queue.c.obj

src/queue.i: src/queue.c.i

.PHONY : src/queue.i

# target to preprocess a source file
src/queue.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/queue.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/queue.c.i
.PHONY : src/queue.c.i

src/queue.s: src/queue.c.s

.PHONY : src/queue.s

# target to generate assembly for a file
src/queue.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/queue.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/queue.c.s
.PHONY : src/queue.c.s

src/stack.obj: src/stack.c.obj

.PHONY : src/stack.obj

# target to build an object file
src/stack.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/stack.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/stack.c.obj
.PHONY : src/stack.c.obj

src/stack.i: src/stack.c.i

.PHONY : src/stack.i

# target to preprocess a source file
src/stack.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/stack.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/stack.c.i
.PHONY : src/stack.c.i

src/stack.s: src/stack.c.s

.PHONY : src/stack.s

# target to generate assembly for a file
src/stack.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/stack.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/stack.c.s
.PHONY : src/stack.c.s

src/unitTest/basicDataStruct_Test.obj: src/unitTest/basicDataStruct_Test.c.obj

.PHONY : src/unitTest/basicDataStruct_Test.obj

# target to build an object file
src/unitTest/basicDataStruct_Test.c.obj:
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/unitTest/basicDataStruct_Test.c.obj
.PHONY : src/unitTest/basicDataStruct_Test.c.obj

src/unitTest/basicDataStruct_Test.i: src/unitTest/basicDataStruct_Test.c.i

.PHONY : src/unitTest/basicDataStruct_Test.i

# target to preprocess a source file
src/unitTest/basicDataStruct_Test.c.i:
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/unitTest/basicDataStruct_Test.c.i
.PHONY : src/unitTest/basicDataStruct_Test.c.i

src/unitTest/basicDataStruct_Test.s: src/unitTest/basicDataStruct_Test.c.s

.PHONY : src/unitTest/basicDataStruct_Test.s

# target to generate assembly for a file
src/unitTest/basicDataStruct_Test.c.s:
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/unitTest/basicDataStruct_Test.c.s
.PHONY : src/unitTest/basicDataStruct_Test.c.s

src/util.obj: src/util.c.obj

.PHONY : src/util.obj

# target to build an object file
src/util.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/util.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/util.c.obj
.PHONY : src/util.c.obj

src/util.i: src/util.c.i

.PHONY : src/util.i

# target to preprocess a source file
src/util.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/util.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/util.c.i
.PHONY : src/util.c.i

src/util.s: src/util.c.s

.PHONY : src/util.s

# target to generate assembly for a file
src/util.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/util.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/util.c.s
.PHONY : src/util.c.s

src/yy_syn.tab.obj: src/yy_syn.tab.c.obj

.PHONY : src/yy_syn.tab.obj

# target to build an object file
src/yy_syn.tab.c.obj:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/yy_syn.tab.c.obj
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/yy_syn.tab.c.obj
.PHONY : src/yy_syn.tab.c.obj

src/yy_syn.tab.i: src/yy_syn.tab.c.i

.PHONY : src/yy_syn.tab.i

# target to preprocess a source file
src/yy_syn.tab.c.i:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/yy_syn.tab.c.i
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/yy_syn.tab.c.i
.PHONY : src/yy_syn.tab.c.i

src/yy_syn.tab.s: src/yy_syn.tab.c.s

.PHONY : src/yy_syn.tab.s

# target to generate assembly for a file
src/yy_syn.tab.c.s:
	$(MAKE) -f CMakeFiles\Mib2Doc.dir\build.make CMakeFiles/Mib2Doc.dir/src/yy_syn.tab.c.s
	$(MAKE) -f CMakeFiles\UNIT_TEST.dir\build.make CMakeFiles/UNIT_TEST.dir/src/yy_syn.tab.c.s
.PHONY : src/yy_syn.tab.c.s

# Help Target
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all (the default if no target is provided)
	@echo ... clean
	@echo ... depend
	@echo ... Mib2Doc
	@echo ... UNIT_TEST
	@echo ... rebuild_cache
	@echo ... lexBison
	@echo ... lexBison_H
	@echo ... edit_cache
	@echo ... src/dispatcher.obj
	@echo ... src/dispatcher.i
	@echo ... src/dispatcher.s
	@echo ... src/docGenerate.obj
	@echo ... src/docGenerate.i
	@echo ... src/docGenerate.s
	@echo ... src/hash.obj
	@echo ... src/hash.i
	@echo ... src/hash.s
	@echo ... src/lexDeal.obj
	@echo ... src/lexDeal.i
	@echo ... src/lexDeal.s
	@echo ... src/lexer.obj
	@echo ... src/lexer.i
	@echo ... src/lexer.s
	@echo ... src/list.obj
	@echo ... src/list.i
	@echo ... src/list.s
	@echo ... src/main.obj
	@echo ... src/main.i
	@echo ... src/main.s
	@echo ... src/mibTreeGen.obj
	@echo ... src/mibTreeGen.i
	@echo ... src/mibTreeGen.s
	@echo ... src/mibTreeObjTree.obj
	@echo ... src/mibTreeObjTree.i
	@echo ... src/mibTreeObjTree.s
	@echo ... src/misc.obj
	@echo ... src/misc.i
	@echo ... src/misc.s
	@echo ... src/options.obj
	@echo ... src/options.i
	@echo ... src/options.s
	@echo ... src/queue.obj
	@echo ... src/queue.i
	@echo ... src/queue.s
	@echo ... src/stack.obj
	@echo ... src/stack.i
	@echo ... src/stack.s
	@echo ... src/unitTest/basicDataStruct_Test.obj
	@echo ... src/unitTest/basicDataStruct_Test.i
	@echo ... src/unitTest/basicDataStruct_Test.s
	@echo ... src/util.obj
	@echo ... src/util.i
	@echo ... src/util.s
	@echo ... src/yy_syn.tab.obj
	@echo ... src/yy_syn.tab.i
	@echo ... src/yy_syn.tab.s
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 0
.PHONY : cmake_check_build_system

