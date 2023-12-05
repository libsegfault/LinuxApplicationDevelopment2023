#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([guess], [1.0], [])
AM_INIT_AUTOMAKE([foreign ])
DX_INIT_DOXYGEN([guess])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)
GETTEXT_PACKAGE=guess
AC_SUBST(GETTEXT_PACKAGE)
ALL_LINGUAS="ru"
AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
IT_PROG_INTLTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([realpath setlocale])

AC_CONFIG_FILES([Makefile src/Makefile po/Makefile.in Doxyfile])
AC_OUTPUT
