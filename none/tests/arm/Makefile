# Makefile.in generated by automake 1.11.1 from Makefile.am.
# none/tests/arm/Makefile.  Generated from Makefile.in by configure.

# Copyright (C) 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
# 2003, 2004, 2005, 2006, 2007, 2008, 2009  Free Software Foundation,
# Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



# This file is used for tool tests, and also in perf/Makefile.am.

# This file should be included (directly or indirectly) by every
# Makefile.am that builds programs.  And also the top-level Makefile.am.

#----------------------------------------------------------------------------
# Global stuff
#----------------------------------------------------------------------------


pkgdatadir = $(datadir)/valgrind
pkgincludedir = $(includedir)/valgrind
pkglibdir = $(libdir)/valgrind
pkglibexecdir = $(libexecdir)/valgrind
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = i686-pc-linux-gnu
host_triplet = i686-pc-linux-gnu
DIST_COMMON = $(dist_noinst_SCRIPTS) $(srcdir)/Makefile.am \
	$(srcdir)/Makefile.in $(top_srcdir)/Makefile.all.am \
	$(top_srcdir)/Makefile.tool-tests.am
check_PROGRAMS = neon128$(EXEEXT) neon64$(EXEEXT) v6intARM$(EXEEXT) \
	v6intThumb$(EXEEXT) v6media$(EXEEXT) vfp$(EXEEXT)
subdir = none/tests/arm
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/configure.in
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
mkinstalldirs = $(install_sh) -d
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
CONFIG_CLEAN_VPATH_FILES =
neon128_SOURCES = neon128.c
neon128_OBJECTS = neon128-neon128.$(OBJEXT)
neon128_LDADD = $(LDADD)
neon128_LINK = $(CCLD) $(neon128_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
neon64_SOURCES = neon64.c
neon64_OBJECTS = neon64-neon64.$(OBJEXT)
neon64_LDADD = $(LDADD)
neon64_LINK = $(CCLD) $(neon64_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
v6intARM_SOURCES = v6intARM.c
v6intARM_OBJECTS = v6intARM-v6intARM.$(OBJEXT)
v6intARM_LDADD = $(LDADD)
v6intARM_LINK = $(CCLD) $(v6intARM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
v6intThumb_SOURCES = v6intThumb.c
v6intThumb_OBJECTS = v6intThumb-v6intThumb.$(OBJEXT)
v6intThumb_LDADD = $(LDADD)
v6intThumb_LINK = $(CCLD) $(v6intThumb_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
v6media_SOURCES = v6media.c
v6media_OBJECTS = v6media-v6media.$(OBJEXT)
v6media_LDADD = $(LDADD)
v6media_LINK = $(CCLD) $(v6media_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
vfp_SOURCES = vfp.c
vfp_OBJECTS = vfp-vfp.$(OBJEXT)
vfp_LDADD = $(LDADD)
vfp_LINK = $(CCLD) $(vfp_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o \
	$@
SCRIPTS = $(dist_noinst_SCRIPTS)
DEFAULT_INCLUDES = -I. -I$(top_builddir)
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__depfiles_maybe = depfiles
am__mv = mv -f
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
SOURCES = neon128.c neon64.c v6intARM.c v6intThumb.c v6media.c vfp.c
DIST_SOURCES = neon128.c neon64.c v6intARM.c v6intThumb.c v6media.c \
	vfp.c
ETAGS = etags
CTAGS = ctags
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
ACLOCAL = ${SHELL} /home/chris/Projects/memorymap/missing --run aclocal-1.11
AMTAR = ${SHELL} /home/chris/Projects/memorymap/missing --run tar
AR = /usr/bin/ar
AUTOCONF = ${SHELL} /home/chris/Projects/memorymap/missing --run autoconf
AUTOHEADER = ${SHELL} /home/chris/Projects/memorymap/missing --run autoheader
AUTOMAKE = ${SHELL} /home/chris/Projects/memorymap/missing --run automake-1.11
AWK = mawk
BOOST_CFLAGS = 
BOOST_LIBS = 
CC = gcc
CCAS = gcc
CCASDEPMODE = depmode=gcc3
CCASFLAGS = -Wno-long-long 
CCDEPMODE = depmode=gcc3
CFLAGS = -Wno-long-long  -Wno-pointer-sign -fno-stack-protector
CPP = gcc -E
CPPFLAGS = 
CXX = g++
CXXDEPMODE = depmode=gcc3
CXXFLAGS = -g -O2
CYGPATH_W = echo
DEFAULT_SUPP = exp-sgcheck.supp xfree-3.supp xfree-4.supp glibc-2.X-drd.supp glibc-2.34567-NPTL-helgrind.supp glibc-2.X.supp 
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
DIFF = diff -u
ECHO_C = 
ECHO_N = -n
ECHO_T = 
EGREP = /bin/grep -E
EXEEXT = 
FLAG_FNO_STACK_PROTECTOR = -fno-stack-protector
FLAG_M32 = -m32
FLAG_M64 = -m64
FLAG_MAIX32 = 
FLAG_MAIX64 = 
FLAG_MMMX = -mmmx
FLAG_MSSE = -msse
FLAG_NO_BUILD_ID = -Wl,--build-id=none
FLAG_UNLIMITED_INLINE_UNIT_GROWTH = --param inline-unit-growth=900
FLAG_W_EXTRA = -Wextra
FLAG_W_NO_EMPTY_BODY = -Wno-empty-body
FLAG_W_NO_FORMAT_ZERO_LENGTH = -Wno-format-zero-length
FLAG_W_NO_NONNULL = -Wno-nonnull
FLAG_W_NO_OVERFLOW = -Wno-overflow
FLAG_W_NO_UNINITIALIZED = -Wno-uninitialized
GDB = /usr/bin/gdb
GLIBC_VERSION = 2.13
GREP = /bin/grep
INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = $(install_sh) -c -s
LDFLAGS = 
LIBOBJS = 
LIBS = 
LN_S = ln -s
LTLIBOBJS = 
MAINT = #
MAKEINFO = ${SHELL} /home/chris/Projects/memorymap/missing --run makeinfo
MKDIR_P = /bin/mkdir -p
MPI_CC = mpicc
OBJEXT = o
PACKAGE = valgrind
PACKAGE_BUGREPORT = valgrind-users@lists.sourceforge.net
PACKAGE_NAME = Valgrind
PACKAGE_STRING = Valgrind 3.7.0.SVN
PACKAGE_TARNAME = valgrind
PACKAGE_URL = 
PACKAGE_VERSION = 3.7.0.SVN
PATH_SEPARATOR = :
PERL = /usr/bin/perl
PREFERRED_STACK_BOUNDARY = -mpreferred-stack-boundary=2
RANLIB = ranlib
SED = /bin/sed
SET_MAKE = 
SHELL = /bin/bash
STRIP = 
VALT_LOAD_ADDRESS_PRI = 0x38000000
VALT_LOAD_ADDRESS_SEC = 0xUNSET
VERSION = 3.7.0.SVN
VGCONF_ARCH_PRI = x86
VGCONF_ARCH_SEC = 
VGCONF_OS = linux
VGCONF_PLATFORM_PRI_CAPS = X86_LINUX
VGCONF_PLATFORM_SEC_CAPS = 
abs_builddir = /home/chris/Projects/memorymap/none/tests/arm
abs_srcdir = /home/chris/Projects/memorymap/none/tests/arm
abs_top_builddir = /home/chris/Projects/memorymap
abs_top_srcdir = /home/chris/Projects/memorymap
ac_ct_CC = gcc
ac_ct_CXX = g++
am__include = include
am__leading_dot = .
am__quote = 
am__tar = ${AMTAR} chof - "$$tardir"
am__untar = ${AMTAR} xf -
bindir = ${exec_prefix}/bin
build = i686-pc-linux-gnu
build_alias = 
build_cpu = i686
build_os = linux-gnu
build_vendor = pc
builddir = .
datadir = ${datarootdir}
datarootdir = ${prefix}/share
docdir = ${datarootdir}/doc/${PACKAGE_TARNAME}
dvidir = ${docdir}
exec_prefix = ${prefix}
host = i686-pc-linux-gnu
host_alias = 
host_cpu = i686
host_os = linux-gnu
host_vendor = pc
htmldir = ${docdir}
includedir = ${prefix}/include
infodir = ${datarootdir}/info
install_sh = ${SHELL} /home/chris/Projects/memorymap/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localedir = ${datarootdir}/locale
localstatedir = ${prefix}/var
mandir = ${datarootdir}/man
mkdir_p = /bin/mkdir -p
oldincludedir = /usr/include
pdfdir = ${docdir}
prefix = /usr/local
program_transform_name = s,x,x,
psdir = ${docdir}
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
srcdir = .
sysconfdir = ${prefix}/etc
target_alias = 
top_build_prefix = ../../../
top_builddir = ../../..
top_srcdir = ../../..
inplacedir = $(top_builddir)/.in_place

#----------------------------------------------------------------------------
# Flags
#----------------------------------------------------------------------------

# Baseline flags for all compilations.  Aim here is to maximise
# performance and get whatever useful warnings we can out of gcc.
AM_CFLAGS_BASE = \
	-O2 -g \
	-Wall \
	-Wmissing-prototypes \
	-Wshadow \
	-Wpointer-arith \
	-Wstrict-prototypes \
	-Wmissing-declarations \
	-Wno-format-zero-length \
	-fno-strict-aliasing

AM_CFLAGS_PIC = -fpic -O -g -fno-omit-frame-pointer -fno-strict-aliasing

# These flags are used for building the preload shared objects.
# The aim is to give reasonable performance but also to have good
# stack traces, since users often see stack traces extending 
# into (and through) the preloads.
#AM_CFLAGS_PIC = -dynamic -O -g -fno-omit-frame-pointer -fno-strict-aliasing \
#		-mno-dynamic-no-pic -fpic -fPIC


# Flags for specific targets.
#
# Nb: the AM_CPPFLAGS_* values are suitable for building tools and auxprogs.
# For building the core, coregrind/Makefile.am files add some extra things.
#
# Also: in newer versions of automake (1.10 onwards?) asm files ending with
# '.S' are considered "pre-processed" (as opposed to those ending in '.s')
# and so the CPPFLAGS are passed to the assembler.  But this is not true for
# older automakes (e.g. 1.8.5, 1.9.6), sigh.  So we include
# AM_CPPFLAGS_<PLATFORM> in each AM_CCASFLAGS_<PLATFORM> variable.  This
# means some of the flags are duplicated on systems with newer versions of
# automake, but this does not really matter and seems hard to avoid.
AM_CPPFLAGS_X86_LINUX = \
	-I$(top_srcdir) \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/VEX/pub \
	-DVGA_x86=1 \
	-DVGO_linux=1 \
	-DVGP_x86_linux=1

#AM_CPPFLAGS_ = \
#	-I$(top_srcdir) \
#	-I$(top_srcdir)/include \
#	-I$(top_srcdir)/VEX/pub \
#	-DVGA_=1 \
#	-DVGO_linux=1 \
#	-DVGP__linux=1

AM_FLAG_M3264_X86_LINUX = -m32
AM_CFLAGS_X86_LINUX = -m32 -mpreferred-stack-boundary=2 \
			 	$(AM_CFLAGS_BASE)

AM_CCASFLAGS_X86_LINUX = $(AM_CPPFLAGS_X86_LINUX) -m32 -g
AM_FLAG_M3264_AMD64_LINUX = -m64
AM_CFLAGS_AMD64_LINUX = -m64 -fomit-frame-pointer \
				-mpreferred-stack-boundary=2 $(AM_CFLAGS_BASE)

AM_CCASFLAGS_AMD64_LINUX = $(AM_CPPFLAGS_AMD64_LINUX) -m64 -g
AM_FLAG_M3264_PPC32_LINUX = -m32
AM_CFLAGS_PPC32_LINUX = -m32 $(AM_CFLAGS_BASE)
AM_CCASFLAGS_PPC32_LINUX = $(AM_CPPFLAGS_PPC32_LINUX) -m32 -g
AM_FLAG_M3264_PPC64_LINUX = -m64
AM_CFLAGS_PPC64_LINUX = -m64 $(AM_CFLAGS_BASE)
AM_CCASFLAGS_PPC64_LINUX = $(AM_CPPFLAGS_PPC64_LINUX) -m64 -g
AM_FLAG_M3264_ARM_LINUX = -m32
AM_CFLAGS_ARM_LINUX = -m32 -mpreferred-stack-boundary=2 \
			 	$(AM_CFLAGS_BASE) -marm

AM_CCASFLAGS_ARM_LINUX = $(AM_CPPFLAGS_ARM_LINUX) -m32 -marm -g
AM_FLAG_M3264_PPC32_AIX5 = 
AM_CFLAGS_PPC32_AIX5 =  -mcpu=powerpc $(AM_CFLAGS_BASE)
AM_CCASFLAGS_PPC32_AIX5 = $(AM_CPPFLAGS_PPC32_AIX5) \
			     -mcpu=powerpc -g

AM_FLAG_M3264_PPC64_AIX5 = 
AM_CFLAGS_PPC64_AIX5 =  -mcpu=powerpc64 $(AM_CFLAGS_BASE)
AM_CCASFLAGS_PPC64_AIX5 = $(AM_CPPFLAGS_PPC64_AIX5) \
			     -mcpu=powerpc64 -g

AM_FLAG_M3264_X86_DARWIN = -arch i386
AM_CFLAGS_X86_DARWIN = $(WERROR) -arch i386 $(AM_CFLAGS_BASE) \
				-mmacosx-version-min=10.5 \
				-fno-stack-protector -fno-pic -fno-PIC

AM_CCASFLAGS_X86_DARWIN = $(AM_CPPFLAGS_X86_DARWIN) -arch i386 -g
AM_FLAG_M3264_AMD64_DARWIN = -arch x86_64
AM_CFLAGS_AMD64_DARWIN = $(WERROR) -arch x86_64 $(AM_CFLAGS_BASE) \
			    -mmacosx-version-min=10.5 -fno-stack-protector

AM_CCASFLAGS_AMD64_DARWIN = $(AM_CPPFLAGS_AMD64_DARWIN) -arch x86_64 -g
AM_FLAG_M3264_S390X_LINUX = -m64
AM_CFLAGS_S390X_LINUX = -m64 $(AM_CFLAGS_BASE)
AM_CCASFLAGS_S390X_LINUX = $(AM_CPPFLAGS_S390X_LINUX) -mzarch -march=z900 \
                            -m64 -g


# Flags for the primary target.  These must be used to build the
# regtests and performance tests.  In fact, these must be used to
# build anything which is built only once on a dual-arch build.
#
AM_FLAG_M3264_PRI = $(AM_FLAG_M3264_X86_LINUX)
AM_CPPFLAGS_PRI = $(AM_CPPFLAGS_X86_LINUX)
AM_CFLAGS_PRI = $(AM_CFLAGS_X86_LINUX)
AM_CCASFLAGS_PRI = $(AM_CCASFLAGS_X86_LINUX)
AM_FLAG_M3264_SEC = 
#AM_FLAG_M3264_SEC = $(AM_FLAG_M3264_)

# Baseline link flags for making vgpreload shared objects.
#
PRELOAD_LDFLAGS_COMMON_LINUX = -nodefaultlibs -shared -Wl,-z,interpose,-z,initfirst
PRELOAD_LDFLAGS_COMMON_AIX5 = -nodefaultlibs -shared -Wl,-G -Wl,-bnogc
PRELOAD_LDFLAGS_COMMON_DARWIN = -dynamic -dynamiclib -all_load
PRELOAD_LDFLAGS_X86_LINUX = $(PRELOAD_LDFLAGS_COMMON_LINUX) -m32
PRELOAD_LDFLAGS_AMD64_LINUX = $(PRELOAD_LDFLAGS_COMMON_LINUX) -m64
PRELOAD_LDFLAGS_PPC32_LINUX = $(PRELOAD_LDFLAGS_COMMON_LINUX) -m32
PRELOAD_LDFLAGS_PPC64_LINUX = $(PRELOAD_LDFLAGS_COMMON_LINUX) -m64
PRELOAD_LDFLAGS_ARM_LINUX = $(PRELOAD_LDFLAGS_COMMON_LINUX) -m32
PRELOAD_LDFLAGS_PPC32_AIX5 = $(PRELOAD_LDFLAGS_COMMON_AIX5)  
PRELOAD_LDFLAGS_PPC64_AIX5 = $(PRELOAD_LDFLAGS_COMMON_AIX5)  
PRELOAD_LDFLAGS_X86_DARWIN = $(PRELOAD_LDFLAGS_COMMON_DARWIN) -arch i386
PRELOAD_LDFLAGS_AMD64_DARWIN = $(PRELOAD_LDFLAGS_COMMON_DARWIN) -arch x86_64
PRELOAD_LDFLAGS_S390X_LINUX = $(PRELOAD_LDFLAGS_COMMON_LINUX) -m64
AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/include \
		-I$(top_srcdir)/coregrind -I$(top_builddir)/include \
		-I$(top_srcdir)/VEX/pub \
		-DVGA_$(VGCONF_ARCH_PRI)=1 \
		-DVGO_$(VGCONF_OS)=1 \
		-DVGP_$(VGCONF_ARCH_PRI)_$(VGCONF_OS)=1

# Nb: Tools need to augment these flags with an arch-selection option, such
# as $(AM_FLAG_M3264_PRI).
AM_CFLAGS = -Winline -Wall -Wshadow -g -m32
AM_CXXFLAGS = -Winline -Wall -Wshadow -g -m32
# Include AM_CPPFLAGS in AM_CCASFLAGS to allow for older versions of
# automake;  see comments in Makefile.all.am for more detail.
AM_CCASFLAGS = $(AM_CPPFLAGS) -m32
#noinst_DSYMS = $(check_PROGRAMS)
dist_noinst_SCRIPTS = filter_stderr
EXTRA_DIST = \
	neon128.stdout.exp neon128.stderr.exp neon128.vgtest \
	neon64.stdout.exp neon64.stderr.exp neon64.vgtest \
	v6intARM.stdout.exp v6intARM.stderr.exp v6intARM.vgtest \
	v6intThumb.stdout.exp v6intThumb.stderr.exp v6intThumb.vgtest \
	v6media.stdout.exp v6media.stderr.exp v6media.vgtest \
	vfp.stdout.exp vfp.stderr.exp vfp.vgtest


# These two are specific to their ARM/Thumb respectively and so we
# hardwire -marm/-mthumb.  neon64 and neon128 are compilable on both,
# however, ask for them to be compiled on thumb, as that looks
# like that's going to be the more common use case.  They also
# need special helping w.r.t -mfpu and -mfloat-abi, though.
# Also force -O0 since -O takes hundreds of MB of memory 
# for v6intThumb.c.
v6intARM_CFLAGS = $(AM_CFLAGS) -g -O0 -mcpu=cortex-a8 -marm
v6intThumb_CFLAGS = $(AM_CFLAGS) -g -O0 -mcpu=cortex-a8 -mthumb
v6media_CFLAGS = $(AM_CFLAGS) -g -O0 -mcpu=cortex-a8 -mthumb
vfp_CFLAGS = $(AM_CFLAGS) -g -O0 -mcpu=cortex-a8 \
			-mfpu=neon -mfloat-abi=softfp \
			-mthumb

neon128_CFLAGS = $(AM_CFLAGS) -g -O0 -mcpu=cortex-a8 \
			-mfpu=neon -mfloat-abi=softfp \
			-mthumb

neon64_CFLAGS = $(AM_CFLAGS) -g -O0 -mcpu=cortex-a8 \
			-mfpu=neon -mfloat-abi=softfp \
			-mthumb

all: all-am

.SUFFIXES:
.SUFFIXES: .c .o .obj
$(srcdir)/Makefile.in: # $(srcdir)/Makefile.am $(top_srcdir)/Makefile.tool-tests.am $(top_srcdir)/Makefile.all.am $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      ( cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh ) \
	        && { if test -f $@; then exit 0; else break; fi; }; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --foreign none/tests/arm/Makefile'; \
	$(am__cd) $(top_srcdir) && \
	  $(AUTOMAKE) --foreign none/tests/arm/Makefile
.PRECIOUS: Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)'; \
	    cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe);; \
	esac;

$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh

$(top_srcdir)/configure: # $(am__configure_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(ACLOCAL_M4): # $(am__aclocal_m4_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(am__aclocal_m4_deps):

clean-checkPROGRAMS:
	-test -z "$(check_PROGRAMS)" || rm -f $(check_PROGRAMS)
neon128$(EXEEXT): $(neon128_OBJECTS) $(neon128_DEPENDENCIES) 
	@rm -f neon128$(EXEEXT)
	$(neon128_LINK) $(neon128_OBJECTS) $(neon128_LDADD) $(LIBS)
neon64$(EXEEXT): $(neon64_OBJECTS) $(neon64_DEPENDENCIES) 
	@rm -f neon64$(EXEEXT)
	$(neon64_LINK) $(neon64_OBJECTS) $(neon64_LDADD) $(LIBS)
v6intARM$(EXEEXT): $(v6intARM_OBJECTS) $(v6intARM_DEPENDENCIES) 
	@rm -f v6intARM$(EXEEXT)
	$(v6intARM_LINK) $(v6intARM_OBJECTS) $(v6intARM_LDADD) $(LIBS)
v6intThumb$(EXEEXT): $(v6intThumb_OBJECTS) $(v6intThumb_DEPENDENCIES) 
	@rm -f v6intThumb$(EXEEXT)
	$(v6intThumb_LINK) $(v6intThumb_OBJECTS) $(v6intThumb_LDADD) $(LIBS)
v6media$(EXEEXT): $(v6media_OBJECTS) $(v6media_DEPENDENCIES) 
	@rm -f v6media$(EXEEXT)
	$(v6media_LINK) $(v6media_OBJECTS) $(v6media_LDADD) $(LIBS)
vfp$(EXEEXT): $(vfp_OBJECTS) $(vfp_DEPENDENCIES) 
	@rm -f vfp$(EXEEXT)
	$(vfp_LINK) $(vfp_OBJECTS) $(vfp_LDADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT)

distclean-compile:
	-rm -f *.tab.c

include ./$(DEPDIR)/neon128-neon128.Po
include ./$(DEPDIR)/neon64-neon64.Po
include ./$(DEPDIR)/v6intARM-v6intARM.Po
include ./$(DEPDIR)/v6intThumb-v6intThumb.Po
include ./$(DEPDIR)/v6media-v6media.Po
include ./$(DEPDIR)/vfp-vfp.Po

.c.o:
	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(COMPILE) -c $<

.c.obj:
	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `$(CYGPATH_W) '$<'`
	$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(COMPILE) -c `$(CYGPATH_W) '$<'`

neon128-neon128.o: neon128.c
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(neon128_CFLAGS) $(CFLAGS) -MT neon128-neon128.o -MD -MP -MF $(DEPDIR)/neon128-neon128.Tpo -c -o neon128-neon128.o `test -f 'neon128.c' || echo '$(srcdir)/'`neon128.c
	$(am__mv) $(DEPDIR)/neon128-neon128.Tpo $(DEPDIR)/neon128-neon128.Po
#	source='neon128.c' object='neon128-neon128.o' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(neon128_CFLAGS) $(CFLAGS) -c -o neon128-neon128.o `test -f 'neon128.c' || echo '$(srcdir)/'`neon128.c

neon128-neon128.obj: neon128.c
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(neon128_CFLAGS) $(CFLAGS) -MT neon128-neon128.obj -MD -MP -MF $(DEPDIR)/neon128-neon128.Tpo -c -o neon128-neon128.obj `if test -f 'neon128.c'; then $(CYGPATH_W) 'neon128.c'; else $(CYGPATH_W) '$(srcdir)/neon128.c'; fi`
	$(am__mv) $(DEPDIR)/neon128-neon128.Tpo $(DEPDIR)/neon128-neon128.Po
#	source='neon128.c' object='neon128-neon128.obj' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(neon128_CFLAGS) $(CFLAGS) -c -o neon128-neon128.obj `if test -f 'neon128.c'; then $(CYGPATH_W) 'neon128.c'; else $(CYGPATH_W) '$(srcdir)/neon128.c'; fi`

neon64-neon64.o: neon64.c
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(neon64_CFLAGS) $(CFLAGS) -MT neon64-neon64.o -MD -MP -MF $(DEPDIR)/neon64-neon64.Tpo -c -o neon64-neon64.o `test -f 'neon64.c' || echo '$(srcdir)/'`neon64.c
	$(am__mv) $(DEPDIR)/neon64-neon64.Tpo $(DEPDIR)/neon64-neon64.Po
#	source='neon64.c' object='neon64-neon64.o' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(neon64_CFLAGS) $(CFLAGS) -c -o neon64-neon64.o `test -f 'neon64.c' || echo '$(srcdir)/'`neon64.c

neon64-neon64.obj: neon64.c
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(neon64_CFLAGS) $(CFLAGS) -MT neon64-neon64.obj -MD -MP -MF $(DEPDIR)/neon64-neon64.Tpo -c -o neon64-neon64.obj `if test -f 'neon64.c'; then $(CYGPATH_W) 'neon64.c'; else $(CYGPATH_W) '$(srcdir)/neon64.c'; fi`
	$(am__mv) $(DEPDIR)/neon64-neon64.Tpo $(DEPDIR)/neon64-neon64.Po
#	source='neon64.c' object='neon64-neon64.obj' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(neon64_CFLAGS) $(CFLAGS) -c -o neon64-neon64.obj `if test -f 'neon64.c'; then $(CYGPATH_W) 'neon64.c'; else $(CYGPATH_W) '$(srcdir)/neon64.c'; fi`

v6intARM-v6intARM.o: v6intARM.c
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(v6intARM_CFLAGS) $(CFLAGS) -MT v6intARM-v6intARM.o -MD -MP -MF $(DEPDIR)/v6intARM-v6intARM.Tpo -c -o v6intARM-v6intARM.o `test -f 'v6intARM.c' || echo '$(srcdir)/'`v6intARM.c
	$(am__mv) $(DEPDIR)/v6intARM-v6intARM.Tpo $(DEPDIR)/v6intARM-v6intARM.Po
#	source='v6intARM.c' object='v6intARM-v6intARM.o' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(v6intARM_CFLAGS) $(CFLAGS) -c -o v6intARM-v6intARM.o `test -f 'v6intARM.c' || echo '$(srcdir)/'`v6intARM.c

v6intARM-v6intARM.obj: v6intARM.c
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(v6intARM_CFLAGS) $(CFLAGS) -MT v6intARM-v6intARM.obj -MD -MP -MF $(DEPDIR)/v6intARM-v6intARM.Tpo -c -o v6intARM-v6intARM.obj `if test -f 'v6intARM.c'; then $(CYGPATH_W) 'v6intARM.c'; else $(CYGPATH_W) '$(srcdir)/v6intARM.c'; fi`
	$(am__mv) $(DEPDIR)/v6intARM-v6intARM.Tpo $(DEPDIR)/v6intARM-v6intARM.Po
#	source='v6intARM.c' object='v6intARM-v6intARM.obj' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(v6intARM_CFLAGS) $(CFLAGS) -c -o v6intARM-v6intARM.obj `if test -f 'v6intARM.c'; then $(CYGPATH_W) 'v6intARM.c'; else $(CYGPATH_W) '$(srcdir)/v6intARM.c'; fi`

v6intThumb-v6intThumb.o: v6intThumb.c
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(v6intThumb_CFLAGS) $(CFLAGS) -MT v6intThumb-v6intThumb.o -MD -MP -MF $(DEPDIR)/v6intThumb-v6intThumb.Tpo -c -o v6intThumb-v6intThumb.o `test -f 'v6intThumb.c' || echo '$(srcdir)/'`v6intThumb.c
	$(am__mv) $(DEPDIR)/v6intThumb-v6intThumb.Tpo $(DEPDIR)/v6intThumb-v6intThumb.Po
#	source='v6intThumb.c' object='v6intThumb-v6intThumb.o' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(v6intThumb_CFLAGS) $(CFLAGS) -c -o v6intThumb-v6intThumb.o `test -f 'v6intThumb.c' || echo '$(srcdir)/'`v6intThumb.c

v6intThumb-v6intThumb.obj: v6intThumb.c
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(v6intThumb_CFLAGS) $(CFLAGS) -MT v6intThumb-v6intThumb.obj -MD -MP -MF $(DEPDIR)/v6intThumb-v6intThumb.Tpo -c -o v6intThumb-v6intThumb.obj `if test -f 'v6intThumb.c'; then $(CYGPATH_W) 'v6intThumb.c'; else $(CYGPATH_W) '$(srcdir)/v6intThumb.c'; fi`
	$(am__mv) $(DEPDIR)/v6intThumb-v6intThumb.Tpo $(DEPDIR)/v6intThumb-v6intThumb.Po
#	source='v6intThumb.c' object='v6intThumb-v6intThumb.obj' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(v6intThumb_CFLAGS) $(CFLAGS) -c -o v6intThumb-v6intThumb.obj `if test -f 'v6intThumb.c'; then $(CYGPATH_W) 'v6intThumb.c'; else $(CYGPATH_W) '$(srcdir)/v6intThumb.c'; fi`

v6media-v6media.o: v6media.c
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(v6media_CFLAGS) $(CFLAGS) -MT v6media-v6media.o -MD -MP -MF $(DEPDIR)/v6media-v6media.Tpo -c -o v6media-v6media.o `test -f 'v6media.c' || echo '$(srcdir)/'`v6media.c
	$(am__mv) $(DEPDIR)/v6media-v6media.Tpo $(DEPDIR)/v6media-v6media.Po
#	source='v6media.c' object='v6media-v6media.o' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(v6media_CFLAGS) $(CFLAGS) -c -o v6media-v6media.o `test -f 'v6media.c' || echo '$(srcdir)/'`v6media.c

v6media-v6media.obj: v6media.c
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(v6media_CFLAGS) $(CFLAGS) -MT v6media-v6media.obj -MD -MP -MF $(DEPDIR)/v6media-v6media.Tpo -c -o v6media-v6media.obj `if test -f 'v6media.c'; then $(CYGPATH_W) 'v6media.c'; else $(CYGPATH_W) '$(srcdir)/v6media.c'; fi`
	$(am__mv) $(DEPDIR)/v6media-v6media.Tpo $(DEPDIR)/v6media-v6media.Po
#	source='v6media.c' object='v6media-v6media.obj' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(v6media_CFLAGS) $(CFLAGS) -c -o v6media-v6media.obj `if test -f 'v6media.c'; then $(CYGPATH_W) 'v6media.c'; else $(CYGPATH_W) '$(srcdir)/v6media.c'; fi`

vfp-vfp.o: vfp.c
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(vfp_CFLAGS) $(CFLAGS) -MT vfp-vfp.o -MD -MP -MF $(DEPDIR)/vfp-vfp.Tpo -c -o vfp-vfp.o `test -f 'vfp.c' || echo '$(srcdir)/'`vfp.c
	$(am__mv) $(DEPDIR)/vfp-vfp.Tpo $(DEPDIR)/vfp-vfp.Po
#	source='vfp.c' object='vfp-vfp.o' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(vfp_CFLAGS) $(CFLAGS) -c -o vfp-vfp.o `test -f 'vfp.c' || echo '$(srcdir)/'`vfp.c

vfp-vfp.obj: vfp.c
	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(vfp_CFLAGS) $(CFLAGS) -MT vfp-vfp.obj -MD -MP -MF $(DEPDIR)/vfp-vfp.Tpo -c -o vfp-vfp.obj `if test -f 'vfp.c'; then $(CYGPATH_W) 'vfp.c'; else $(CYGPATH_W) '$(srcdir)/vfp.c'; fi`
	$(am__mv) $(DEPDIR)/vfp-vfp.Tpo $(DEPDIR)/vfp-vfp.Po
#	source='vfp.c' object='vfp-vfp.obj' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(vfp_CFLAGS) $(CFLAGS) -c -o vfp-vfp.obj `if test -f 'vfp.c'; then $(CYGPATH_W) 'vfp.c'; else $(CYGPATH_W) '$(srcdir)/vfp.c'; fi`

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	mkid -fID $$unique
tags: TAGS

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	set x; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)  $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	shift; \
	if test -z "$(ETAGS_ARGS)$$*$$unique"; then :; else \
	  test -n "$$unique" || unique=$$empty_fix; \
	  if test $$# -gt 0; then \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      "$$@" $$unique; \
	  else \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      $$unique; \
	  fi; \
	fi
ctags: CTAGS
CTAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	list='$(SOURCES) $(HEADERS)  $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	test -z "$(CTAGS_ARGS)$$unique" \
	  || $(CTAGS) $(CTAGSFLAGS) $(AM_CTAGSFLAGS) $(CTAGS_ARGS) \
	     $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && $(am__cd) $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) "$$here"

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH tags

distdir: $(DISTFILES)
	@srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	list='$(DISTFILES)'; \
	  dist_files=`for file in $$list; do echo $$file; done | \
	  sed -e "s|^$$srcdirstrip/||;t" \
	      -e "s|^$$topsrcdirstrip/|$(top_builddir)/|;t"`; \
	case $$dist_files in \
	  */*) $(MKDIR_P) `echo "$$dist_files" | \
			   sed '/\//!d;s|^|$(distdir)/|;s,/[^/]*$$,,' | \
			   sort -u` ;; \
	esac; \
	for file in $$dist_files; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`; \
	    if test -d "$(distdir)/$$file"; then \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -fpR $(srcdir)/$$file "$(distdir)$$dir" || exit 1; \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    cp -fpR $$d/$$file "$(distdir)$$dir" || exit 1; \
	  else \
	    test -f "$(distdir)/$$file" \
	    || cp -p $$d/$$file "$(distdir)/$$file" \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
	$(MAKE) $(AM_MAKEFLAGS) $(check_PROGRAMS)
	$(MAKE) $(AM_MAKEFLAGS) check-local
check: check-am
all-am: Makefile $(SCRIPTS)
installdirs:
install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)
	-test . = "$(srcdir)" || test -z "$(CONFIG_CLEAN_VPATH_FILES)" || rm -f $(CONFIG_CLEAN_VPATH_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-checkPROGRAMS clean-generic clean-local mostlyclean-am

distclean: distclean-am
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
distclean-am: clean-am distclean-compile distclean-generic \
	distclean-tags

dvi: dvi-am

dvi-am:

html: html-am

html-am:

info: info-am

info-am:

install-data-am:

install-dvi: install-dvi-am

install-dvi-am:

install-exec-am:

install-html: install-html-am

install-html-am:

install-info: install-info-am

install-info-am:

install-man:

install-pdf: install-pdf-am

install-pdf-am:

install-ps: install-ps-am

install-ps-am:

installcheck-am:

maintainer-clean: maintainer-clean-am
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic

pdf: pdf-am

pdf-am:

ps: ps-am

ps-am:

uninstall-am:

.MAKE: check-am install-am install-strip

.PHONY: CTAGS GTAGS all all-am check check-am check-local clean \
	clean-checkPROGRAMS clean-generic clean-local ctags distclean \
	distclean-compile distclean-generic distclean-tags distdir dvi \
	dvi-am html html-am info info-am install install-am \
	install-data install-data-am install-dvi install-dvi-am \
	install-exec install-exec-am install-html install-html-am \
	install-info install-info-am install-man install-pdf \
	install-pdf-am install-ps install-ps-am install-strip \
	installcheck installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-compile \
	mostlyclean-generic pdf pdf-am ps ps-am tags uninstall \
	uninstall-am


# This used to be required when Vex had a handwritten Makefile.  It
# shouldn't be needed any more, though.

#----------------------------------------------------------------------------
# noinst_PROGRAMS and noinst_DSYMS targets
#----------------------------------------------------------------------------

# On Darwin, for a program 'p', the DWARF debug info is stored in the
# directory 'p.dSYM'.  This must be generated after the executable is
# created, with 'dsymutil p'.  We could redefine LINK with a script that
# executes 'dsymutil' after linking, but that's a pain.  Instead we use this
# hook so that every time "make check" is run, we subsequently invoke
# 'dsymutil' on all the executables that lack a .dSYM directory, or that are
# newer than their corresponding .dSYM directory.
build-noinst_DSYMS: $(noinst_DSYMS)
	for f in $(noinst_DSYMS); do \
	  if [ ! -e $$f.dSYM  -o  $$f -nt $$f.dSYM ] ; then \
	      echo "dsymutil $$f"; \
	      dsymutil $$f; \
	  fi; \
	done

# This is used by coregrind/Makefile.am and Makefile.tool.am for doing
# "in-place" installs.  It copies $(noinst_PROGRAMS) into $inplacedir.
# It needs to be depended on by an 'all-local' rule.
inplace-noinst_PROGRAMS: $(noinst_PROGRAMS)
	mkdir -p $(inplacedir); \
	for f in $(noinst_PROGRAMS) ; do \
	  rm -f $(inplacedir)/$$f; \
	  ln -f -s ../$(subdir)/$$f $(inplacedir); \
	done

# Similar to inplace-noinst_PROGRAMS
inplace-noinst_DSYMS: build-noinst_DSYMS
	mkdir -p $(inplacedir); \
	for f in $(noinst_DSYMS); do \
	  rm -f $(inplacedir)/$$f.dSYM; \
	  ln -f -s ../$(subdir)/$$f.dSYM $(inplacedir); \
	done

# This is used by coregrind/Makefile.am and by <tool>/Makefile.am for doing
# "make install".  It copies $(noinst_PROGRAMS) into $prefix/lib/valgrind/.
# It needs to be depended on by an 'install-exec-local' rule.
install-noinst_PROGRAMS: $(noinst_PROGRAMS)
	$(mkinstalldirs) $(DESTDIR)$(pkglibdir); \
	for f in $(noinst_PROGRAMS); do \
	  $(INSTALL_PROGRAM) $$f $(DESTDIR)$(pkglibdir); \
	done

# Similar to install-noinst_PROGRAMS.
# Nb: we don't use $(INSTALL_PROGRAM) here because it doesn't work with
# directories.  XXX: not sure whether the resulting permissions will be
# correct when using 'cp -R'...
install-noinst_DSYMS: build-noinst_DSYMS
	$(mkinstalldirs) $(DESTDIR)$(pkglibdir); \
	for f in $(noinst_DSYMS); do \
	  cp -R $$f.dSYM $(DESTDIR)$(pkglibdir); \
	done

# This needs to be depended on by a 'clean-local' rule.
clean-noinst_DSYMS:
	for f in $(noinst_DSYMS); do \
	  rm -rf $$f.dSYM; \
	done

check-local: build-noinst_DSYMS

clean-local: clean-noinst_DSYMS

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
