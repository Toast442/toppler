#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.13)
AC_INIT([toppler],[1.1.3])
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([toppler.cc])
AM_CONFIG_HEADER([config.h])
AM_MAINTAINER_MODE

# General information.
AC_SUBST(FULLNAME,"Tower Toppler")
AC_SUBST(URL,"http://toppler.sourceforge.net/")
AC_DEFINE_UNQUOTED([FULLNAME],["$FULLNAME"],[Define to the full name of this package.])
AC_DEFINE_UNQUOTED([URL],["$URL"],[Define to the URL of this package's homepage.])

# Compiler options.

# Additional variables.

# I18n.
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION(0.11.5)
LIBS="$LIBS $LIBINTL"

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.
SDL_VERSION=1.2.0
AM_PATH_SDL($SDL_VERSION,
	AC_DEFINE_UNQUOTED(HAVE_SDL,[1],[Define to 1 if you have SDL.]),
	AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))
CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

AC_CHECK_LIB(SDL_mixer, main, ,
	AC_MSG_WARN([Can't find SDL_mixer. Toppler will have no sound.]))

AC_CHECK_LIB(z, uncompress, ,
	AC_MSG_ERROR([Can't find libz. Toppler needs it to uncompress the data file!]))

# Checks for header files.
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h langinfo.h libintl.h stdlib.h string.h unistd.h wchar.h sys/types.h dirent.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_UID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([atexit malloc realloc memmove memset mkdir setlocale strcasecmp strchr strstr])

# Output.
AC_CONFIG_FILES([Makefile toppler.spec toppler.nsi toppler.desktop po/Makefile.in m4/Makefile toppler.qpg])
AC_OUTPUT
