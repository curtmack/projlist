AC_INIT([projlist], [1.1.1], [curtis@mackie.ninja],
        [projlist], [https://github.com/curtmack/projlist])

AC_PREREQ([2.69])
AC_CONFIG_SRCDIR([src/projlist.cpp])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([subdir-objects foreign -Wall -Werror])
AC_CONFIG_FILES([Makefile])

# Check for C++11 compiler
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

# Check for Boost
AX_BOOST_BASE([1.65], AC_MSG_ERROR([*** Boost >= 1.65 is required, but was not found.]), )
AX_BOOST_SYSTEM([1.65], AC_MSG_ERROR([*** Boost System >= 1.65 is required, but was not found.]), )
AX_BOOST_FILESYSTEM([1.65], AC_MSG_ERROR([*** Boost Filesystem >= 1.65 is required, but was not found.]), )

AC_OUTPUT
