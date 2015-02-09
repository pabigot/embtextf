# If creating a fresh development area from a repository checkout, do:
#   autoreconf -Im4 --force --install
# For most subsequent changes it is sufficient to run:
#   autoreconf

AC_INIT([embtextf],[20130609],[https://github.com/pabigot/embtextf/issues],[],[http://pabigot.github.com/embtextf/])
AC_CONFIG_SRCDIR([include/embtextf/version.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CANONICAL_HOST
AC_CANONICAL_BUILD

AM_INIT_AUTOMAKE([-Wall -Werror foreign no-define])

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

AC_PROG_SED

AC_ARG_WITH([ccs-target],
            [AS_HELP_STRING([--with-ccs-target],[select target for TI Code Composer Studio toolchain (msp430,tms470,...)])],
	    [cross_compiling=yes     dnl force cross-compile
	     host_os=none            dnl stop libtool from trying to do anything
	     ccs_target=$withval],
	    [])

AM_CONDITIONAL([WITH_CCS], [test -n "${ccs_target+set}"])

if test -z "${WITH_CCS_TRUE}" ; then
  case "$ccs_target" in
  msp430)
    ccs_suffix=430
    ;;
  tms470)
    ccs_suffix=470
    ;;
  *)
    AC_MSG_ERROR([unrecogized --with-ccs-target=$with_ccs_target])
    ;;
  esac
  AC_MSG_NOTICE(ccs target is $ccs_target with suffix $ccs_suffix)
  CCS_INSTALL_ROOT=${CCS_INSTALL_ROOT:-${with_ccs}}
  AC_MSG_NOTICE(CCS set ${with_ccs} at ${CCS_INSTALL_ROOT})
  AC_ARG_VAR([CCS_INSTALL_ROOT],[Root for TI Code Composer Studio installation (for --with-ccs-target)])
  AC_ARG_VAR([CG_TOOL_ROOT],[Where target-specific CCS code generator tools are installed (for --with-ccs-target)])
  if test -z "${CG_TOOL_ROOT+set}" ; then
    tool_root=${CCS_INSTALL_ROOT}/tools/compiler
    AC_MSG_CHECKING([for ${ccs_target} in ${tool_root}])
    CG_TOOL_ROOT=`ls -rd ${tool_root}/${ccs_target}_* | ${SED} -e 1q` \
      || AC_MSG_ERROR([no support for ${ccs_target} in ${CCS_INSTALL_ROOT}])
    AC_MSG_RESULT([${CG_TOOL_ROOT}])
  fi

  # Define ${host}-${tool} where a CC substitute exists, and prevent
  # discovery of the wrong toolchain when it doesn't.
  CC="${CG_TOOL_ROOT}/bin/cl$ccs_suffix"
  CPP="${CC} --preproc_only"
  LD="${CG_TOOL_ROOT}/bin/ld$ccs_suffix"
  AR="${CG_TOOL_ROOT}/bin/ar$ccs_suffix"
  OBJDUMP=false
  RANLIB=false
  ac_cv_prog_STRIP=false
  NM=false

  # CCS does not know where to find its include files unless you tell it
  CPPFLAGS=${CPPFLAGS:--I${CG_TOOL_ROOT}/include}

  # Match GCC default of optimized debug, plus flags that support the
  # ABI that correctly initializes static variables.  DO NOT add
  # --relaxed_ansi: the TI compiler lies and claims it's GCC when that
  # flag is used.
  CFLAGS=${CFLAGS:---abi=eabi -g -o}
fi

# Need a C compiler.  We're building a library, and for some targets
# we may not be providing the options (like -mmcu= on msp430) that are
# required to be able to do a non-relocatable link.  So don't ask
# AC_PROG_CC to check whether executables can be built.
AC_LANG(C)
if test -z "${WITH_CCS_TRUE}" ; then
  # Override how-to-build commands for the TI compiler toolchain
  ac_compile='$CC -c $CFLAGS $CPPFLAGS -z -o conftest.$ac_ext >&AS_MESSAGE_LOG_FD'
  ac_link='$CC -z -o conftest$ac_exeext $CFLAGS $CPPFLAGS $LDFLAGS conftest.$ac_ext $LIBS >&AS_MESSAGE_LOG_FD'
fi
AC_NO_EXECUTABLES
AC_PROG_CC
AM_CONDITIONAL([WITH_GCC], [test "${GCC}" = "yes"])

# TARGET_CFLAGS is placed in AM_CFLAGS allowing special flags to be
# provided without affecting the toolchain default flags.
AC_ARG_VAR([TARGET_CFLAGS],
           [Target-specific flags added before standard CFLAGS variable])

# Need AM_PROG_AR for libtool
AM_PROG_AR

# Use libtool; no shared libraries for embedded platforms
LT_INIT([disable-shared])

# Non-GNU toolchains probably don't really use libtool
AM_CONDITIONAL([WITH_LIBTOOL], [test -z "$WITH_GCC_TRUE"])

# Feature capabilities
if test -z "${WITH_GCC_TRUE}" ; then
  # gcc always supports long long.  Set that explicitly because
  # AC_NO_EXECUTABLES prevents msp430 from successfully running the
  # test below.
  ac_cv_type_long_long_int=yes
elif test -z "${WITH_CCS_TRUE}" ; then
  # CCS 5.3 supports long long.  Maybe earlier versions too.  Not
  # going to try to figure out which version we have.
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

# OPT_ARG_ENABLE(section,flag,help,default,prefix)
#   section -- section in which option appears, lower case with underscore separators
#   feature -- feature within section, lower case with underscore separators
#   help -- contents of help string
#   default -- value to use as default (defaults to yes)
#   help for default -- string to emit as default
#   prefix -- CPP prefix for flag, defaults to EMBTEXTF_ENABLE_{section}
#
# Given section and feature this will create an enable option
# --enable-(section)-(feature).  It will also create a substitution
# value EMBTEXTF_(SECTION)_ENABLE_(FEATURE) with a value 0 if disabled
# and 1 if enabled.  That substitution is excluded from Makefile
# substitution, thus affects only other files like headers.
AC_DEFUN([OPT_ARG_ENABLE],[
  define([_SECTION],[$1])dnl
  define([_FEATURE],[$2])dnl
  define([_HELP],[$3])dnl
  define([_DEFAULT],m4_default([$4],yes))dnl
  define([_DEFAULT_HELP],m4_default([$5],[_DEFAULT]))dnl
  define([_FLAG],[_SECTION[_]_FEATURE])dnl
  define([_FLAG_],[--enable-][m4_translit(_FLAG, [_], [-])])dnl
  define([_PREFIX],m4_default([$6],[EMBTEXTF_ENABLE_[]m4_translit(_SECTION, [-a-z], [_A-Z])]))dnl
  define([_CPPFLAG],[_PREFIX[_]m4_translit(_FEATURE,[-a-z],[_A-Z])])dnl
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
OPT_ARG_ENABLE(provide, libc, [Provide libc-compatible wrappers for *printf], [], [], [EMBTEXTF_PROVIDE])
OPT_ARG_ENABLE(libc, setvbuf, [Provide setvbuf() stub in libc-compatible wrappers], [no])

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
