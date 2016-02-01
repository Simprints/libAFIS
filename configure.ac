# -*- autoconf -*-
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

AC_PREREQ([2.69])
AC_INIT([libAFIS],
	[m4_esyscmd_s([sed s/\#// VERSION])],
	[jordan@teddy-net.com],
	[afis])

AC_CONFIG_HEADERS([conf/config.h])
AC_CONFIG_SRCDIR([acinclude.m4])
AC_CONFIG_INIT([2015-@YEAR@ SimPrints Ltd, Cambridge, UK])
AC_CONFIG_MACRO_DIR([m4lib])

AC_LANG(C)
dnl # Enable ISO features if possible. On Linux, setting _XOPEN_SOURCE
dnl # includes POSIX and XPG things.  Set to 500 if Single Unix
dnl # conformance is wanted, to 600 for the upcoming sixth revision.
dnl # AC_DEFINE([_XOPEN_SOURCE],[600],[set minimum standard conformance])

# Libtool
LT_PREREQ([2.4.2])
LT_INIT
AC_SUBST([LIBTOOL_DEPS])
AC_PROG_LIBTOOL

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CC_C99
AC_C_RESTRICT
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m],[main])

# Checks for header files.
AC_CHECK_HEADERS([limits.h stddef.h stdint.h stdlib.h])
AC_CHECK_HEADERS([string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([gettimeofday memset strstr])

# Makefile path support
AC_SUBST_BASEDIR(boot)
AC_SUBST_BASEDIR(Sources)

AC_CONFIG_FILES([Makefile
		 Sources/Extraction/Filters/Makefile
		 Sources/Extraction/MinutiaeDetection/Makefile
		 Sources/Extraction/Model/Makefile
		 Sources/Extraction/Makefile
		 Sources/General/Makefile
		 Sources/Matcher/Minutia/Makefile
		 Sources/Matcher/Makefile
		 Sources/Utils/IO/Makefile
		 Sources/Utils/Misc/Makefile
		 Sources/Utils/Unity/Makefile
		 Sources/Utils/Makefile
		 Sources/Makefile

		 Sources/Tests/DataStructures/Makefile
		 Sources/Tests/Extraction/Filters/runners/Makefile
		 Sources/Tests/Extraction/Filters/Makefile
		 Sources/Tests/Extraction/Model/runners/Makefile
		 Sources/Tests/Extraction/Model/Makefile
		 Sources/Tests/Extraction/Makefile
		 Sources/Tests/General/runners/Makefile
		 Sources/Tests/General/Makefile
		 Sources/Tests/Matcher/runners/Makefile
		 Sources/Tests/Matcher/Makefile
		 Sources/Tests/Makefile
		 ])

# Output, write configs
AC_OUTPUT

# End
