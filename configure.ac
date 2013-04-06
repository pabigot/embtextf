# If creating a fresh development area from a repository checkout, do:
#   autoreconf -Im4 --force --install
# For most subsequent changes it is sufficient to run:
#   autoreconf

AC_INIT([embtextf],[20130326],[https://github.com/pabigot/embtextf/issues],[],[http://pabigot.github.com/embtextf/])
AC_CONFIG_SRCDIR([include/embtextf/version.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CANONICAL_HOST
AC_CANONICAL_BUILD

AM_INIT_AUTOMAKE([-Wall -Werror foreign no-define no-dist])

# Doxygen
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN(embtextf, [\$\(top_builddir\)/doc/doxygen.cfg], [generated])

# Need a C compiler.  We're building a library, and for some targets
# we may not be providing the options (like -mmcu= on msp430) that are
# required to be able to do a non-relocatable link.  So don't ask
# AC_PROG_CC to check whether executables can be built.
AC_LANG(C)
AC_NO_EXECUTABLES
AC_PROG_CC
AM_CONDITIONAL([WITH_GCC], [test "${GCC}" = "yes"])

# TARGET_CFLAGS is placed in AM_CFLAGS allowing special flags to be
# provided without affecting the toolchain default flags.
AC_ARG_VAR([TARGET_CFLAGS],
           [Target-specific flags added before standard CFLAGS variable])

AC_PROG_SED

# Use libtool; no shared libraries for embedded platforms
LT_INIT([disable-shared])

# Feature capabilities
if test -z "${WITH_GCC_TRUE}" ; then
  # gcc always supports long long.  Set that explicitly because
  # AC_NO_EXECUTABLES prevents msp430 from successfully running the
  # test below.
  ac_cv_type_long_long_int=yes
fi
AC_TYPE_LONG_LONG_INT
if test ${ac_cv_type_long_long_int} = yes; then
  app_have_longlong=1
  opt_longlong="yes"
else
  app_have_longlong=0
  opt_longlong="no"
fi
AC_SUBST([EMBTEXTF_XTOA_ENABLE_LONGLONG],[${app_have_longlong}])
AM_SUBST_NOTMAKE(EMBTEXTF_XTOA_ENABLE_LONGLONG)

# Environment capabilities
# CUnit -- stub to permit non-standard path, but not used
AC_ARG_WITH([cunit], [AS_HELP_STRING([--with-cunit=<path>],[where cunit is installed])])
AC_LANG_COMPILER_REQUIRE
if test "$cross_compiling" = "no" ; then
  AC_CHECK_HEADERS([CUnit/Basic.h],[AC_CHECK_LIB([cunit], [CU_initialize_registry], [env_have_cunit=yes], [])])
fi
AM_CONDITIONAL([WITH_CUNIT], [test -n "${env_have_cunit}"])
# Coverage testing
AC_ARG_ENABLE([gcov], [AS_HELP_STRING([--enable-gcov], [add flags for coverage testing (native+gcc only)])], [], [enable_gcov=no])
AM_CONDITIONAL([WITH_GCOV], [test "$cross_compiling" = "no" -a -z "${WITH_GCC_TRUE}" -a "${enable_gcov}" = "yes"])
if test -z "${WITH_GCOV_TRUE}" ; then
  CFLAGS=`AS_ECHO(${CFLAGS}) | ${SED} -e 's/-O[[0-9]]*//g'`
fi

# OPT_ARG_ENABLE(flag,help,default)
#   section -- section in which option appears, lower case with underscore separators
#   feature -- feature within section, lower case with underscore separators
#   help -- contents of help string
#   default -- value to use as default (defaults to yes)
#   help for default -- string to emit as default
#
# Given section and feature this will create an enable option
# --enable-(section)-(feature).  It will also create a substitution
# value EMBTEXTF_(SECTION)_ENABLE_(FEATURE) with a value 0 if disabled
# and 1 if enabled.  That substitution is excluded from Makefile
# substitution, thus affects only other files like headers.
AC_DEFUN([OPT_ARG_ENABLE],[
  define([_SECTION],[$1])dnl
  define([_FEATURE],[$2])dnl
  define([_FLAG],[_SECTION[_]_FEATURE])dnl
  define([_FLAG_],[--enable-][m4_translit(_FLAG, [_], [-])])dnl
  define([_CPPFLAG],[EMBTEXTF_ENABLE_[]m4_translit(_SECTION, [-a-z], [_A-Z])[_]m4_translit(_FEATURE,[-a-z],[_A-Z])])dnl
  define([_HELP],[$3])dnl
  define([_DEFAULT],m4_default([$4],yes))dnl
  define([_DEFAULT_HELP],m4_default([$5],[_DEFAULT]))dnl
  AC_REQUIRE([AC_PROG_FGREP])
  AC_MSG_CHECKING(_FLAG)
  AC_ARG_ENABLE(_FLAG,
                AS_HELP_STRING(_FLAG_, _HELP[ @<:@default=]_DEFAULT_HELP[@:>@]),
		[ use_]_FLAG[=$enableval],
		[ use_]_FLAG[=]_DEFAULT)
  [ if test "$use_]_FLAG[" = "yes" ; then
      opt_]_FLAG[=1
    else
      opt_]_FLAG[=0
    fi ]
  AC_MSG_RESULT([$use_]_FLAG)
  AC_SUBST(_CPPFLAG, [$opt_]_FLAG)
  AM_SUBST_NOTMAKE(_CPPFLAG)
  undefine([_DEFAULT_HELP])dnl
  undefine([_DEFAULT])dnl
  undefine([_HELP])dnl
  undefine([_CPPFLAG])dnl
  undefine([_FLAG_])dnl
  undefine([_FLAG])dnl
  undefine([_FEATURE])dnl
  undefine([_SECTION])dnl
])		
		
OPT_ARG_ENABLE(vuprintf, intptr, [Support "%p" pointer conversion specifier])
OPT_ARG_ENABLE(vuprintf, octal, [Support "%o" octal conversion specifier])
OPT_ARG_ENABLE(vuprintf, long, [Support long length modifier as with "%ld"])
OPT_ARG_ENABLE(vuprintf, longlong, [Support long long length modifier as with "%lld"],[${opt_longlong}],[yes iff long long supported])
if test "$use_vuprintf_longlong" = "yes" -a "$use_vuprintf_long" != "yes" ; then
  AC_MSG_ERROR([Cannot combine --disable-vuprintf-long with --enable-vuprintf-longlong])
fi
OPT_ARG_ENABLE(vuprintf, precision, [Support field precision as with "%.4d"])
OPT_ARG_ENABLE(vuprintf, alternate_form, [Support alternate form flag as with "%@%:@x"])
OPT_ARG_ENABLE(provide, libc, [Provide libc-compatible wrappers for *printf])

AM_CONDITIONAL([EMBTEXTF_PROVIDE_LIBC], [test "$use_provide_libc" = "yes"])

# Makefiles
AC_CONFIG_FILES([Makefile \
                 include/embtextf/Makefile \
		 src/Makefile \
		 tests/Makefile \
		 doc/Makefile ])

# Feature files
AC_CONFIG_FILES([include/embtextf/config.h])

# Other files
AC_CONFIG_FILES([doc/doxygen.cfg
		 embtextf.pc ])

AC_OUTPUT
