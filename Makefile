##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile for c++23
##

# DEBUG_MAKEFILE	:=	true
ERRORFILE			:=	true
USE_COVERAGE		:=	true

ARGV			:=
NAME			:=	xrnEcs
TNAME			:=	unit

ERROR_FILE		:=	errorFile

BINDIR			:=	binaries
SRCDIR			:=	sources
INCDIR			:=	includes
TSTDIR			:=	tests
LIBDIR			:=	libraries
EXTERNDIR		:=	externs
EXTERNBINDIR	:=	$(BINDIR)/$(EXTERNDIR)

BUILDDIR		:=	.build
OBJDIR			:=	objects
DEPDIR			:=	dependencies
OBJEXTERNDIR	:=	$(EXTERNDIR)/$(OBJDIR)
DEPEXTERNDIR	:=	$(EXTERNDIR)/$(DEPDIR)

C_SRCEXT		:=	.c
CPP_SRCEXT		:=	.cpp
CPPM_SRCEXT		:=	.cppm

C_HDREXT		:=	.h
CPP_HDREXT		:=	.hpp

OBJEXT			:=	.o
DEPEXT			:=	.d
PCMEXT			:=	.pcm
PCHEXT			:=	.gch

## wflags
COMMON_WFLAGS	:=	pedantic all extra effc++
C_WFLAGS		:=	
CPP_WFLAGS		:=	no-unused-variable no-unused-parameter
CPPM_WFLAGS		:=

## flags
ifdef hide_color
COMMON_FLAGS	:=	-fmax-errors=10 -fdiagnostics-color=never
else
COMMON_FLAGS	:=	-fmax-errors=10 -fdiagnostics-color=always
endif
C_FLAGS			:=	
CPP_FLAGS		:=	-std=c++2b
CPPM_FLAGS		:=	-std=c++2b
PCH_FLAGS		:=	-std=c++2b

## -I
COMMON_CPPFLAGS	:=	$(INCDIR) $(SRCDIR) $(EXTERNDIR) $(EXTERNDIR)/HdrOnly $(LIBDIR)
C_CPPFLAGS		:=
CXX_CPPFLAGS	:=

## -L
LIBLOCATION		:=

## -l
LIBBIN			:=


# ============================================================================= Mode debug
ifeq (debug,$(findstring debug,$(MAKECMDGOALS)))

MODE_EXT		:=	_debug
MODE_FLAGS		:=	-g3 -Og -pipe -DDEBUG=2
MOD_BUILDDIR	:=	$(addsuffix /debug,$(BUILDDIR))


# ============================================================================= Mode valgrind
else ifeq (auto_valgrind,$(findstring auto_valgrind,$(MAKECMDGOALS)))

MODE_EXT		:=	_valgrind
MODE_FLAGS		:=	-g3 -Og -pipe -DDEBUG=1
MOD_BUILDDIR	:=	$(addsuffix /valgrind,$(BUILDDIR))


# ============================================================================= Mode gdb
else ifeq (auto_gdb,$(findstring auto_gdb,$(MAKECMDGOALS)))

MODE_EXT		:=	_gdb
MODE_FLAGS		:=	-g3 -Og -pipe
MOD_BUILDDIR	:=	$(addsuffix /gdb,$(BUILDDIR))


# ============================================================================= Mode test
else ifeq (tests,$(findstring tests,$(MAKECMDGOALS)))

MODE_EXT		:=	_tests
MODE_FLAGS		:=	-g3 -O0 -DTEST=1
ifeq "$(USE_COVERAGE)" "true"
COVERAGE_FLAG	:=	-fprofile-arcs -ftest-coverage -fPIC --coverage
endif
MOD_BUILDDIR	:=	$(addsuffix /tests,$(BUILDDIR))
NAME			:=	$(TNAME)
ifeq "$(USE_COVERAGE)" "true"
LIBBIN			+=	gcov
endif



# ============================================================================= Mode release
else

MODE_EXT		:=
MODE_FLAGS		:=	-Ofast -pipe
MOD_BUILDDIR	:=	$(addsuffix /release,$(BUILDDIR))

endif

## ============================================================================

## DIR
OBJDIR			:=	$(MOD_BUILDDIR)/$(OBJDIR)
DEPDIR			:=	$(MOD_BUILDDIR)/$(DEPDIR)
OBJEXTERNDIR	:=	$(BUILDDIR)/$(OBJEXTERNDIR)
DEPEXTERNDIR	:=	$(BUILDDIR)/$(DEPEXTERNDIR)

CC				:=	gcc
CXX				:=	g++

MAIN			:=	$(SRCDIR)/main$(CPP_SRCEXT)

# find
C_SRC			!=	find $(SRCDIR) -type f -name \*$(C_SRCEXT) ! -path $(MAIN)
CPP_SRC			!=	find $(SRCDIR) -type f -name \*$(CPP_SRCEXT) ! -path $(MAIN)
# CPPM_SRC		!=	find $(SRCDIR) -type f -name \*$(CPPM_SRCEXT) ! -path $(MAIN)

TST_C_SRC			!=	find $(TSTDIR) -type f -name \*$(C_SRCEXT)
TST_CPP_SRC		!=	find $(TSTDIR) -type f -name \*$(CPP_SRCEXT)
# TEST_CPPM_SRC		!=	find $(TSTDIR) -type f -name \*$(CPPM_SRCEXT)

FOUNDLIBS		!=	find $(LIBDIR) -maxdepth 1 -type d ! -path $(LIBDIR)
FOUNDEXTERN		!=	find $(EXTERNDIR) -maxdepth 1 -type d ! -path $(EXTERNDIR) ! -path $(EXTERNDIR)/HdrOnly

CPP_PCH			:=	$(INCDIR)/pch$(CPP_HDREXT)

# .x=.o

ifeq (tests,$(findstring tests,$(MAKECMDGOALS)))
C_OBJ			:=	$(patsubst %$(C_SRCEXT),$(OBJDIR)/%$(OBJEXT),$(C_SRC) $(TST_C_SRC))
CPP_OBJ			:=	$(patsubst %$(CPP_SRCEXT),$(OBJDIR)/%$(OBJEXT),$(CPP_SRC) $(TST_CPP_SRC))
CPPM_OBJ		+=	$(patsubst %$(CPPM_SRCEXT),$(OBJDIR)/%$(OBJEXT),$(CPPM_SRC) $(TST_CPPM_SRC))
else
C_OBJ			:=	$(patsubst %$(C_SRCEXT),$(OBJDIR)/%$(OBJEXT),$(C_SRC))
CPP_OBJ			:=	$(patsubst %$(CPP_SRCEXT),$(OBJDIR)/%$(OBJEXT),$(CPP_SRC) $(MAIN))
CPPM_OBJ		+=	$(patsubst %$(CPPM_SRCEXT),$(OBJDIR)/%$(OBJEXT),$(CPPM_SRC))
endif

# .x=.x.gch
C_PCH_OBJ		+=	$(patsubst %,%$(PCHEXT),$(C_HDR))
CPP_PCH_OBJ		+=	$(patsubst %,%$(PCHEXT),$(CPP_PCH))

## c flags
CFLAGS			+=	$(foreach flag, $(COMMON_WFLAGS),$(addprefix -W,$(flag)))
CFLAGS			+=	$(foreach flag, $(C_WFLAGS),$(addprefix -W,$(flag)))
CFLAGS			+=	$(C_FLAGS) $(COMMON_FLAGS)

## cpp flags
CXXFLAGS		+=	$(foreach flag, $(COMMON_WFLAGS),$(addprefix -W,$(flag)))
CXXFLAGS		+=	$(foreach flag, $(CPP_WFLAGS),$(addprefix -W,$(flag)))
CXXFLAGS		+=	$(CPP_FLAGS) $(COMMON_FLAGS)
# CXXFLAGS		+=	-fmodules-ts $(foreach objdir, $(dir $(CPPM_OBJ)),-fprebuilt-module-path=$(objdir))

## cppm flags
CXXMFLAGS		+=	$(foreach flag, $(COMMON_WFLAGS),$(addprefix -W,$(flag)))
CXXMFLAGS		+=	$(foreach flag, $(CPPM_WFLAGS),$(addprefix -W,$(flag)))
# CXXMFLAGS		+=	$(CPPM_FLAGS) -fmodules-ts --precompile $(COMMON_FLAGS)

## c.gch flags
C_PCHFLAGS		+=	-x c-header
# C_PCHFLAGS		+=	$(foreach flag, $(COMMON_WFLAGS),$(addprefix -W,$(flag)))
# C_PCHFLAGS		+=	$(foreach flag, $(C_WFLAGS),$(addprefix -W,$(flag)))
# C_PCHFLAGS		+=	$(CPP_FLAGS)

## cpp.gch flags
CPP_PCHFLAGS	+=	-x c++-header
# CPP_PCHFLAGS	+=	$(foreach flag, $(COMMON_WFLAGS),$(addprefix -W,$(flag)))
# CPP_PCHFLAGS	+=	$(foreach flag, $(CPP_WFLAGS),$(addprefix -W,$(flag)))
# CPP_PCHFLAGS	+=	$(CPP_FLAGS)

## mode flags
CFLAGS			+=	$(MODE_FLAGS)
CXXFLAGS		+=	$(MODE_FLAGS)
CXXMFLAGS		+=	$(MODE_FLAGS)
C_PCHFLAGS		+=	$(MODE_FLAGS)
CPP_PCHFLAGS	+=	$(MODE_FLAGS)

## includes
CPPFLAGS		+=	$(foreach inc, $(COMMON_CPPFLAGS),$(addprefix -I,$(inc)))
CPPFLAGS		+=	$(foreach inc, $(C_CPPFLAGS),$(addprefix -I,$(inc)))
CPPFLAGS		+=	$(foreach inc, $(CXX_CPPFLAGS),$(addprefix -I,$(inc)))

## libraries
FOUNDLIBS		:=	$(patsubst $(LIBDIR)/%,%,$(FOUNDLIBS))
FOUNDLIBSBIN	:=	$(patsubst %,./$(BINDIR)/lib%.a,$(FOUNDLIBS))

## externs
FOUNDEXTERN		:=	$(patsubst $(EXTERNDIR)/%,%,$(FOUNDEXTERN))
FOUNDEXTERNBIN	:=	$(patsubst %,./$(EXTERNBINDIR)/lib%.a,$(FOUNDEXTERN))

## -L
LDFLAGS			:=	$(foreach lib, $(LIBLOCATION),$(addprefix -L,$(lib)))
LDFLAGS			+=	$(addprefix -L,$(BINDIR))
LDFLAGS			+=	$(addprefix -L,$(EXTERNBINDIR))

## -l
LDLIBS			:=	$(foreach lib, $(LIBBIN),$(addprefix -l,$(lib)))
LDLIBS			+=	$(foreach lib, $(FOUNDLIBS),$(addprefix -l,$(lib)$(MODE_EXT)))
LDLIBS			+=	$(foreach lib, $(FOUNDEXTERN),$(addprefix -l,$(lib)))

## BINDIR
BINDIR			:=	$(patsubst /%,,$(BINDIR))
BINDIR			:=	$(patsubst ~%,,$(BINDIR))
ifeq "$(BINDIR)" ""
$(error invalid bindir)
endif
NAME			:=	$(BINDIR)/$(NAME)

## ============================================================================

PRINTF				:=	@printf

ifndef hide_color
NORMAL				:=	\e[0m
BLACK				:=	\e[0;30m
DARKGRAY			:=	\e[1;30m
RED					:=	\e[0;31m
LRED				:=	\e[1;31m
GREEN				:=	\e[0;32m
LGREEN				:=	\e[1;32m
BROWN				:=	\e[0;33m
YELLOW				:=	\e[1;33m
BLUE				:=	\e[0;34m
LBLUE				:=	\e[1;34m
PURPLE				:=	\e[0;35m
LPURPLE				:=	\e[1;35m
CYAN				:=	\e[0;36m
LCYAN				:=	\e[1;36m
LIGHT				:=	\e[0;37m
WHITE				:=	\e[1;37m
endif

ifneq "$(DEBUG_MAKEFILE)" "true"
MAKEFLAGS		+=	--silent --no-print-directory
else
.NOTPARALLEL:
endif

## ============================================================================

all: linkage | emptyErrorFile

emptyErrorFile :
	mkdir -p $(BUILDDIR)
	touch $(BUILDDIR)/$(ERROR_FILE)
	> $(BUILDDIR)/$(ERROR_FILE)

precompilation : $(C_PCH_OBJ) $(CPP_PCH_OBJ)
	$(PRINTF) "$(LCYAN)[Precompilation]$(NORMAL) done\n"

libraries : $(FOUNDLIBSBIN)
	$(PRINTF) "$(LCYAN)[Libraries]$(NORMAL) done\n"

externs : $(FOUNDEXTERNBIN)
	$(PRINTF) "$(LCYAN)[Externs]$(NORMAL) done\n"

compilation : $(C_OBJ) $(CPP_OBJ)
	$(PRINTF) "$(LCYAN)[Compilation]$(NORMAL) done\n"

linkage : $(NAME)$(MODE_EXT)
	$(PRINTF) "$(LCYAN)[Linkage]$(NORMAL) done\n"

test_linkage : $(TEST_NAME)$(MODE_EXT)
	$(PRINTF) "$(LCYAN)[Linkage]$(NORMAL) done\n"

## ============================================================================

$(NAME)$(MODE_EXT): compilation | libraries externs $(BINDIR)
ifdef ERRORFILE
	$(CXX) $(OUTPUT_OPTION) $(CPP_OBJ) $(CPPM_OBJ) $(LDFLAGS) $(LDLIBS) 2>&1 | tee -a $(BUILDDIR)/$(ERROR_FILE)
	sed -i 's/\x1b\[[0-9;]*[a-zA-Z]//g' $(BUILDDIR)/$(ERROR_FILE)
else
	$(CXX) $(OUTPUT_OPTION) $(CPP_OBJ) $(CPPM_OBJ) $(LDFLAGS) $(LDLIBS) 2>&1
endif

$(TEST_NAME)$(MODE_EXT): compilation | libraries externs $(BINDIR)
	$(CXX) $(OUTPUT_OPTION) $(CPP_OBJ) $(CPPM_OBJ) $(LDFLAGS) $(LDLIBS)

force :;
# libX.a
./$(BINDIR)/lib%.a : force
	$(eval DIRNAME = $(patsubst $(BINDIR)/lib%.a,%,$(patsubst ./%,%,$@)))
ifneq "$(DEBUG_MAKEFILE)" "true"
	$(MAKE) -C $(LIBDIR)/$(DIRNAME) \
		BINDIR=../../$(BINDIR) \
		NAME=$(DIRNAME)$(MODE_EXT) \
		OBJDIR=../../$(OBJDIR)/$(LIBDIR)/$(DIRNAME) \
		DEPDIR=../../$(DEPDIR)/$(LIBDIR)/$(DIRNAME) \
		CFLAGS="$(CFLAGS)" \
		CXXFLAGS="$(CXXFLAGS)" \
		CXXMFLAGS="$(CXXMFLAGS)" \
		CPPFLAGS="-I.." \
		--silent --no-print-directory
else
	$(MAKE) -C $(LIBDIR)/$(DIRNAME) \
		BINDIR=../../$(BINDIR) \
		NAME=$(DIRNAME)$(MODE_EXT) \
		OBJDIR=../../$(OBJDIR)/$(LIBDIR)/$(DIRNAME) \
		DEPDIR=../../$(DEPDIR)/$(LIBDIR)/$(DIRNAME) \
		CFLAGS="$(CFLAGS)" \
		CXXFLAGS="$(CXXFLAGS)" \
		CXXMFLAGS="$(CXXMFLAGS)" \
		CPPFLAGS="-I.."
endif

# externs/libX.a
./$(EXTERNBINDIR)/lib%.a : force
	$(eval DIRNAME = $(patsubst $(EXTERNBINDIR)/lib%.a,%,$(patsubst ./%,%,$@)))
ifneq "$(DEBUG_MAKEFILE)" "true"
	$(MAKE) -C $(EXTERNDIR)/$(DIRNAME) \
		BINDIR=../../$(EXTERNBINDIR) \
		NAME=$(DIRNAME) \
		OBJDIR=../../$(OBJEXTERNDIR)/$(DIRNAME) \
		DEPDIR=../../$(DEPEXTERNDIR)/$(DIRNAME) \
		CFLAGS="$(CFLAGS)" \
		CXXFLAGS="$(CXXFLAGS)" \
		CXXMFLAGS="$(CXXMFLAGS)" \
		CPPFLAGS="-I.." \
		--silent --no-print-directory
else
	$(MAKE) -C $(EXTERNDIR)/$(DIRNAME) \
		BINDIR=../../$(EXTERNBINDIR) \
		NAME=$(DIRNAME) \
		OBJDIR=../../$(OBJEXTERNDIR)/$(DIRNAME) \
		DEPDIR=../../$(DEPEXTERNDIR)/$(DIRNAME) \
		CFLAGS="$(CFLAGS)" \
		CXXFLAGS="$(CXXFLAGS)" \
		CXXMFLAGS="$(CXXMFLAGS)" \
		CPPFLAGS="-I.."
endif

# .c
$(OBJDIR)/%$(OBJEXT): %$(C_SRCEXT) | $(C_PCH_OBJ)
	mkdir -p $(@D) $(patsubst $(OBJDIR)%,./$(DEPDIR)%,$(@D))
	$(CC) -c $(OUTPUT_OPTION) -c $(CPPFLAGS) $(CFLAGS) $(COVERAGE_FLAG) $< \
		-MT $@ -MMD -MP -MF $(patsubst $(OBJDIR)%$(OBJEXT),$(DEPDIR)/%$(DEPEXT),$(patsubst ./%,%,$@))
	$(PRINTF) "$(LCYAN)[Compilation]$(NORMAL) $<\n"

# .cpp
$(OBJDIR)/%$(OBJEXT): %$(CPP_SRCEXT) | $(CPPM_OBJ) precompilation
	mkdir -p $(@D) $(patsubst $(OBJDIR)%,./$(DEPDIR)%,$(@D))
ifdef ERRORFILE
	$(CXX) -c $(OUTPUT_OPTION) $(CPPFLAGS) $(CXXFLAGS) $(COVERAGE_FLAG) $< \
		-MT $@ -MMD -MP -MF $(patsubst $(OBJDIR)%$(OBJEXT),$(DEPDIR)/%$(DEPEXT),$(patsubst ./%,%,$@)) 2>&1 | tee -a $(BUILDDIR)/$(ERROR_FILE)
	sed -i 's/\x1b\[[0-9;]*[a-zA-Z]//g' $(BUILDDIR)/$(ERROR_FILE)
else
	$(CXX) -c $(OUTPUT_OPTION) $(CPPFLAGS) $(CXXFLAGS) $(COVERAGE_FLAG) $< \
		-MT $@ -MMD -MP -MF $(patsubst $(OBJDIR)%$(OBJEXT),$(DEPDIR)/%$(DEPEXT),$(patsubst ./%,%,$@))
endif
	$(PRINTF) "$(LCYAN)[Compilation]$(NORMAL) $<\n"

# .cppm
$(OBJDIR)/%$(OBJEXT): %$(CPPM_SRCEXT) | precompilation
	mkdir -p $(@D) $(patsubst $(OBJDIR)%,./$(DEPDIR)%,$(@D))
	$(CXX) -o $(patsubst %$(OBJEXT),%$(PCMEXT),$@) $(CPPFLAGS) $(CXXMFLAGS) $< \
		-MT $(patsubst %$(OBJEXT),%$(PCMEXT),$@) -MMD -MP -MF $(patsubst $(OBJDIR)%$(OBJEXT),$(DEPDIR)/%$(DEPEXT),$(patsubst ./%,%,$@))
	$(CXX) $(OUTPUT_OPTION) -c $(CXXFLAGS) $(patsubst %$(OBJEXT),%$(PCMEXT),$@)
	$(PRINTF) "$(LCYAN)[Compilation][Module]$(NORMAL) $<\n"

# .h

%$(C_HDREXT)$(PCHEXT): %$(C_HDREXT)
	$(CC) $(C_PCHFLAGS) $(OUTPUT_OPTION) $(CPPFLAGS) $<
	$(PRINTF) "$(LCYAN)[Precompilation]$(NORMAL) $<\n"
.PRECIOUS: %$(C_HDREXT)$(PCHEXT)


%$(CPP_HDREXT)$(PCHEXT): %$(CPP_HDREXT)
	$(CXX) $(CPP_PCHFLAGS) $(OUTPUT_OPTION) $(CPPFLAGS) $<
	$(PRINTF) "$(LCYAN)[Precompilation]$(NORMAL) $<\n"
.PRECIOUS: %$(CPP_HDREXT)$(PCHEXT)

$(BINDIR) :; mkdir -p $(BINDIR)

ifneq "$(wildcard $(DEPDIR))" ""
include $(shell find $(DEPDIR) -type f -name \*$(DEPEXT))
endif

## clean

re :
	$(MAKE) ffclean
	$(MAKE) auto

clean :
	rm -rf $(OBJDIR) $(DEPDIR)
	rm -f $(BUILDDIR)/$(ERROR_FILE)
	rm -f vgcore.*
	$(PRINTF) "$(DARKGRAY)[Clean]$(NORMAL) done\n"

fclean : clean
	rm -f $(NAME) $(NAME)_debug $(NAME)_valgrind $(NAME)_gdb
	$(foreach libbin, $(FOUNDLIBS),rm -f $(BINDIR)/lib$(libbin).a $(BINDIR)/lib$(libbin)_debug.a $(BINDIR)/lib$(libbin)_valgrind.a $(BINDIR)/lib$(libbin)_gdb.a)
	$(PRINTF) "$(DARKGRAY)[FClean]$(NORMAL) done\n"

ffclean : fclean
	find . -name \*.gch -delete
	$(PRINTF) "$(DARKGRAY)[FFClean]$(NORMAL) done\n"

fffclean : ffclean
	rm -rf $(BUILDDIR)
	rm -rf $(BINDIR)
	$(PRINTF) "$(DARKGRAY)[FFFClean]$(NORMAL) done\n"

## auto

auto:all
	$(PRINTF) "$(YELLOW)[Binary]$(NORMAL) auto $(ARGV)\n"
	./$(NAME)$(MODE_EXT) $(ARGV)

debug : all
	$(PRINTF) "$(YELLOW)[Binary]$(NORMAL) debug $(ARGV)\n"
	./$(NAME)$(MODE_EXT) $(ARGV)

auto_valgrind : all
	$(PRINTF) "$(YELLOW)[Binary]$(NORMAL) auto_valgrind $(ARGV)\n"
	valgrind ./$(NAME)$(MODE_EXT) $(ARGV)

auto_gdb : all
	$(PRINTF) "$(YELLOW)[Binary]$(NORMAL) auto_gdb $(ARGV)\n"
	gdb --args $(NAME)$(MODE_EXT) $(ARGV)

tests : all

auto_tests : tests
	$(PRINTF) "$(YELLOW)[Binary]$(NORMAL) auto_tests $(ARGV)\n"
	./$(NAME)$(MODE_EXT)
ifeq "$(USE_COVERAGE)" "true"
	gcovr --exclude='tests' --exclude='externs' -j8
endif

## phony

.PHONY: all clean fclean re auto debug auto_valgrind auto_gdb tests auto_tests
