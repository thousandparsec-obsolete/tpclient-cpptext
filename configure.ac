AC_INIT([tpclient-cpptext],[0.0.1],[lee@thousandparsec.net])
AC_CONFIG_SRCDIR(src/main.cpp)

AC_CANONICAL_TARGET([])

AM_INIT_AUTOMAKE(tpclient-cpptext, 0.0.1)
AM_CONFIG_HEADER(config.h)

AM_MAINTAINER_MODE

CXXFLAGS="-g -Wall"


AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET

AC_LANG_CPLUSPLUS
AC_REQUIRE_CPP

AC_HEADER_STDC


PKG_CHECK_MODULES(TP, libtpproto,
	[
        CXXFLAGS="$CXXFLAGS $TP_CFLAGS"
        LDFLAGS="$LDFLAGS $TP_LIBS"
	],
	AC_MSG_ERROR(Couldn't find libtpproto-cpp. Please install it before trying again)
)



AC_CONFIG_FILES([
Makefile
src/Makefile
]) 

AC_OUTPUT
