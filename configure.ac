# Process this file with autoconf to produce a configure script.
AC_INIT
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
#AC_CHECK_TOOL
AM_INIT_AUTOMAKE([toppler],[`cat VERSION`])
AC_CONFIG_SRCDIR([toppler.cc])
AM_CONFIG_HEADER(config.h)
AM_MAINTAINER_MODE
CPPFLAGS="-Wall"

# To be removed in the future
AC_DEFINE_UNQUOTED(SYS_LINUX,0,Linux)
AC_DEFINE_UNQUOTED(SYS_WINDOWS,1,Windows)
AC_DEFINE_UNQUOTED(SYS_BEOS,2,BeOs)
AC_DEFINE_UNQUOTED(SYS_MACOSX,3,MacOSX)
AC_DEFINE_UNQUOTED(SYSTEM,SYS_LINUX,System)

# Checks for programs.
AC_PROG_AWK
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

# Checks for libraries.
SDL_VERSION=1.2.0
AM_PATH_SDL($SDL_VERSION, :,
            AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))
CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

AC_CHECK_LIB(SDL_mixer, main, ,
  AC_MSG_WARN([can not find SDL_mixer tower toppler will have no sound]))

AC_CHECK_LIB(z, uncompress, ,
  AC_MSG_ERROR([can not find libz toppler needs it to uncompress the data tile]))

# Checks for header files.
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_UID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([atexit memmove memset mkdir strcasecmp strchr strstr])

AM_GNU_GETTEXT([external])

# Output.
AC_CONFIG_FILES([Makefile toppler.spec toppler.desktop po/Makefile.in])
AC_OUTPUT
