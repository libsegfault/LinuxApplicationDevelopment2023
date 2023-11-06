#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [1.0])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign subdir-objects])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

AC_CHECK_LIB([rhash], [rhash_library_init, rhash_msg, rhash_file, rhash_print_bytes], [], [AC_MSG_ERROR([Failed to find rhash])])
AC_CHECK_LIB([rhash], [rhash_library_init, rhash_msg, rhash_file, rhash_print_bytes], [], [enable_readline="no"])

# Checks for header files.
AC_CHECK_HEADERS([rhash.h], [], [AC_MSG_ERROR([Failed to find rhash.h])])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp strerror])

AC_ARG_ENABLE([readline], AS_HELP_STRING([--disable-readline or --enable-readline], [force enable or disable readline]), [enable_readline="$enable_readline"], [enable_readline="yes"])

AM_CONDITIONAL([READLINE_WRAPPER], [test "$enable_readline" = "yes"])
AS_IF([test "$enable_readline" = "yes"], [AC_DEFINE([USE_READLINE], [], [Use readline or not])])

AM_COND_IF([READLINE_WRAPPER], [AC_SUBST(LIBS, ["-lrhash -lreadline"])], [AC_SUBST(LIBS, ["-lrhash"])])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
