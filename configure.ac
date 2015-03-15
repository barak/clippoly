#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([polygon clipping library],[0.11],[klamer@mi.el.utwente.nl],[clippoly],[//http://clippoly.sourceforge.net])
AM_INIT_AUTOMAKE([subdir-objects foreign -Wall])
AC_CONFIG_SRCDIR([poly_io.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL

LT_INIT

PKG_INSTALLDIR

# Checks for header files.
AC_CHECK_HEADERS([float.h malloc.h stdlib.h string.h])

AC_CONFIG_MACRO_DIR([m4])

AC_LANG([C++])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_SEARCH_LIBS([hypot],[m])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
