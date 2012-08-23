#
# configure.ac
#
# (C) 2012 Francesco Salvestrini <salvestrini AT gmail DOT com>
#

AC_INIT([iod],
        m4_esyscmd([build-aux/git-version-gen .tarball-version]),
        [salvestrini@gmail.com],
        [iod],
        [github.com/salvestrini/iod])

AC_PREREQ([2.68])

AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE([1.11.1 foreign std-options no-installman no-installinfo -Wall])

AC_PROG_SED
AC_PROG_GREP
AC_PROG_MKDIR_P
AC_PROG_LN_S

AC_PATH_PROG([SORT], [sort], [/bin/false])
AC_PATH_PROG([UNIQ], [uniq], [/bin/false])
AC_PATH_PROG([GIT],  [git],  [/bin/false])

AC_PATH_PROG([DIFF], [diff], [/bin/false])
AC_PATH_PROG([CUT],  [cut],  [/bin/false])
AC_PATH_PROG([HEAD], [head], [/bin/false])
AC_PATH_PROG([TAIL], [tail], [/bin/false])

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_CXXCPP
AC_PROG_CXX
AC_PROG_CXX_C_O
AC_PROG_RANLIB

AC_CHECK_HEADER([getopt.h],[
    AC_DEFINE([HAVE_GETOPT_H], 1,
              [Define to 1 if you have <getopt.h>.])
],[
    AC_MSG_ERROR([Your system seems to be missing of getopt.h header])
])

AC_CHECK_HEADER([regex.h],[
    AC_DEFINE([HAVE_REGEX_H], 1,
              [Define to 1 if you have <regex.h>.])
],[
    AC_MSG_ERROR([Your system seems to be missing of regex.h header])
])

AC_CHECK_HEADER([execinfo.h],[
    AC_DEFINE([HAVE_EXECINFO_H], 1,
              [Define to 1 if you have <execinfo.h>.])
    AC_CHECK_FUNCS([backtrace backtrace_symbols])
],[
    AC_MSG_NOTICE([Your system seems to be missing of execinfo.h header, you will not have debugging backtraces"])
])

AC_CONFIG_FILES([
    Makefile

    src/Makefile
])

AC_OUTPUT
