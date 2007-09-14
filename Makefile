# Makefile.in generated by automake 1.10 from Makefile.am.
# Makefile.  Generated from Makefile.in by configure.

# Copyright (C) 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
# 2003, 2004, 2005, 2006  Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.





pkgdatadir = $(datadir)/toppler
pkglibdir = $(libdir)/toppler
pkgincludedir = $(includedir)/toppler
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = i386-apple-darwin8.10.1
host_triplet = i386-apple-darwin8.10.1
target_triplet = i386-apple-darwin8.10.1
bin_PROGRAMS = toppler$(EXEEXT)
subdir = .
DIST_COMMON = README $(am__configure_deps) $(dist_man_MANS) \
	$(dist_pixmaps_DATA) $(dist_pkgdata_DATA) $(dist_pkgdoc_DATA) \
	$(dist_pkglocalstate_DATA) $(srcdir)/Makefile.am \
	$(srcdir)/Makefile.in $(srcdir)/config.h.in \
	$(srcdir)/toppler.desktop.in $(srcdir)/toppler.nsi.in \
	$(srcdir)/toppler.qpg.in $(srcdir)/toppler.spec.in \
	$(top_srcdir)/configure ABOUT-NLS AUTHORS COPYING ChangeLog \
	INSTALL NEWS config.guess config.rpath config.sub depcomp \
	install-sh ltmain.sh missing mkinstalldirs
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/configure.ac
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
am__CONFIG_DISTCLEAN_FILES = config.status config.cache config.log \
 configure.lineno config.status.lineno
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = config.h
CONFIG_CLEAN_FILES = toppler.spec toppler.nsi toppler.desktop \
	toppler.qpg
am__installdirs = "$(DESTDIR)$(bindir)" "$(DESTDIR)$(man6dir)" \
	"$(DESTDIR)$(applicationsdir)" "$(DESTDIR)$(pixmapsdir)" \
	"$(DESTDIR)$(pkgdatadir)" "$(DESTDIR)$(pkgdocdir)" \
	"$(DESTDIR)$(pkglocalstatedir)"
binPROGRAMS_INSTALL = $(INSTALL_PROGRAM)
PROGRAMS = $(bin_PROGRAMS)
am_toppler_OBJECTS = archi.$(OBJEXT) bonus.$(OBJEXT) \
	configuration.$(OBJEXT) decl.$(OBJEXT) elevators.$(OBJEXT) \
	game.$(OBJEXT) highscore.$(OBJEXT) keyb.$(OBJEXT) \
	level.$(OBJEXT) leveledit.$(OBJEXT) menu.$(OBJEXT) \
	menusys.$(OBJEXT) main.$(OBJEXT) points.$(OBJEXT) \
	robots.$(OBJEXT) screen.$(OBJEXT) snowball.$(OBJEXT) \
	sound.$(OBJEXT) soundsys.$(OBJEXT) sprites.$(OBJEXT) \
	stars.$(OBJEXT) toppler.$(OBJEXT) txtsys.$(OBJEXT) \
	qnxicon.$(OBJEXT)
toppler_OBJECTS = $(am_toppler_OBJECTS)
toppler_LDADD = $(LDADD)
toppler_LINK = $(LIBTOOL) --tag=CXX $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=link $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) \
	$(toppler_LDFLAGS) $(LDFLAGS) -o $@
DEFAULT_INCLUDES = -I.
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__depfiles_maybe = depfiles
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=compile $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(LIBTOOL) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
CXXCOMPILE = $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
LTCXXCOMPILE = $(LIBTOOL) --tag=CXX $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=compile $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
CXXLD = $(CXX)
CXXLINK = $(LIBTOOL) --tag=CXX $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=link $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
SOURCES = $(toppler_SOURCES)
DIST_SOURCES = $(toppler_SOURCES)
RECURSIVE_TARGETS = all-recursive check-recursive dvi-recursive \
	html-recursive info-recursive install-data-recursive \
	install-dvi-recursive install-exec-recursive \
	install-html-recursive install-info-recursive \
	install-pdf-recursive install-ps-recursive install-recursive \
	installcheck-recursive installdirs-recursive pdf-recursive \
	ps-recursive uninstall-recursive
man6dir = $(mandir)/man6
NROFF = nroff
MANS = $(dist_man_MANS)
am__vpath_adj_setup = srcdirstrip=`echo "$(srcdir)" | sed 's|.|.|g'`;
am__vpath_adj = case $$p in \
    $(srcdir)/*) f=`echo "$$p" | sed "s|^$$srcdirstrip/||"`;; \
    *) f=$$p;; \
  esac;
am__strip_dir = `echo $$p | sed -e 's|^.*/||'`;
applicationsDATA_INSTALL = $(INSTALL_DATA)
dist_pixmapsDATA_INSTALL = $(INSTALL_DATA)
dist_pkgdataDATA_INSTALL = $(INSTALL_DATA)
dist_pkgdocDATA_INSTALL = $(INSTALL_DATA)
dist_pkglocalstateDATA_INSTALL = $(INSTALL_DATA)
DATA = $(applications_DATA) $(dist_pixmaps_DATA) $(dist_pkgdata_DATA) \
	$(dist_pkgdoc_DATA) $(dist_pkglocalstate_DATA)
RECURSIVE_CLEAN_TARGETS = mostlyclean-recursive clean-recursive	\
  distclean-recursive maintainer-clean-recursive
ETAGS = etags
CTAGS = ctags
DIST_SUBDIRS = $(SUBDIRS)
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
distdir = $(PACKAGE)-$(VERSION)
top_distdir = $(distdir)
am__remove_distdir = \
  { test ! -d $(distdir) \
    || { find $(distdir) -type d ! -perm -200 -exec chmod u+w {} ';' \
         && rm -fr $(distdir); }; }
DIST_ARCHIVES = $(distdir).tar.gz
GZIP_ENV = --best
distuninstallcheck_listfiles = find . -type f -print
distcleancheck_listfiles = find . -type f -print
ACLOCAL = ${SHELL} /Users/jasonk/projects/toppler-1.1.1-2-macosx/missing --run aclocal-1.10
AMTAR = ${SHELL} /Users/jasonk/projects/toppler-1.1.1-2-macosx/missing --run tar
AR = ar
AUTOCONF = ${SHELL} /Users/jasonk/projects/toppler-1.1.1-2-macosx/missing --run autoconf
AUTOHEADER = ${SHELL} /Users/jasonk/projects/toppler-1.1.1-2-macosx/missing --run autoheader
AUTOMAKE = ${SHELL} /Users/jasonk/projects/toppler-1.1.1-2-macosx/missing --run automake-1.10
AWK = awk
CC = gcc
CCDEPMODE = depmode=none
CFLAGS = -arch ppc -arch i386
CPP = gcc -E
CPPFLAGS =  -I/usr/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE
CXX = g++
CXXCPP = g++ -E
CXXDEPMODE = depmode=none
CXXFLAGS = -arch i386 -arch ppc
CYGPATH_W = echo
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
ECHO = echo
ECHO_C = 
ECHO_N = -n
ECHO_T = 
EGREP = /usr/bin/grep -E
EXEEXT = 
F77 = 
FFLAGS = 
FULLNAME = Tower Toppler
GMSGFMT = /usr/local/bin/msgfmt
GMSGFMT_015 = /usr/local/bin/msgfmt
GREP = /usr/bin/grep
INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = $(install_sh) -c -s
INTLLIBS = -lintl -Wl,-framework -Wl,CoreFoundation
INTL_MACOSX_LIBS = -Wl,-framework -Wl,CoreFoundation
LDFLAGS = -arch i386 -arch ppc
LIBICONV = -liconv
LIBINTL = -lintl -Wl,-framework -Wl,CoreFoundation
LIBOBJS = 
LIBS = -lz -lSDL_mixer -lintl -lintl -Wl,-framework -Wl,CoreFoundation -L/usr/local/lib -lSDLmain -lSDL -framework Cocoa -framework OpenGL
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
LTLIBICONV = -liconv
LTLIBINTL = -lintl -Wl,-framework -Wl,CoreFoundation
LTLIBOBJS = 
MAINT = #
MAKEINFO = ${SHELL} /Users/jasonk/projects/toppler-1.1.1-2-macosx/missing --run makeinfo
MKDIR_P = ./install-sh -c -d
MSGFMT = /usr/local/bin/msgfmt
MSGFMT_015 = /usr/local/bin/msgfmt
MSGMERGE = /usr/local/bin/msgmerge
OBJEXT = o
PACKAGE = toppler
PACKAGE_BUGREPORT = 
PACKAGE_NAME = toppler
PACKAGE_STRING = toppler 1.1.3
PACKAGE_TARNAME = toppler
PACKAGE_VERSION = 1.1.3
PATH_SEPARATOR = :
POSUB = po
RANLIB = ranlib
SDL_CFLAGS = -I/usr/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE
SDL_CONFIG = /usr/local/bin/sdl-config
SDL_LIBS = -L/usr/local/lib -lSDLmain -lSDL -framework Cocoa -framework OpenGL
SED = /usr/bin/sed
SET_MAKE = 
SHELL = /bin/sh
STRIP = strip
URL = http://toppler.sourceforge.net/
USE_NLS = yes
VERSION = 1.1.3
XGETTEXT = /usr/local/bin/xgettext
XGETTEXT_015 = /usr/local/bin/xgettext
abs_builddir = /Users/jasonk/projects/toppler-1.1.1-2-macosx
abs_srcdir = /Users/jasonk/projects/toppler-1.1.1-2-macosx
abs_top_builddir = /Users/jasonk/projects/toppler-1.1.1-2-macosx
abs_top_srcdir = /Users/jasonk/projects/toppler-1.1.1-2-macosx
ac_ct_CC = gcc
ac_ct_CXX = g++
ac_ct_F77 = 
am__include = include
am__leading_dot = .
am__quote = 
am__tar = ${AMTAR} chof - "$$tardir"
am__untar = ${AMTAR} xf -
bindir = /Users/jasonk/projects/toppler-1.1.1-2-macosx/Toppler.app/Contents/MacOS
build = i386-apple-darwin8.10.1
build_alias = 
build_cpu = i386
build_os = darwin8.10.1
build_vendor = apple
builddir = .
datadir = ${datarootdir}
datarootdir = ${prefix}/share
docdir = $(datadir)/doc
dvidir = ${docdir}
exec_prefix = /Users/jasonk/projects/toppler-1.1.1-2-macosx/Toppler.app/Contents/MacOS
host = i386-apple-darwin8.10.1
host_alias = 
host_cpu = i386
host_os = darwin8.10.1
host_vendor = apple
htmldir = ${docdir}
includedir = ${prefix}/include
infodir = ${datarootdir}/info
install_sh = $(SHELL) /Users/jasonk/projects/toppler-1.1.1-2-macosx/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localedir = ${datarootdir}/locale
localstatedir = ${prefix}/var
mandir = ${datarootdir}/man
mkdir_p = $(top_builddir)/./install-sh -c -d
oldincludedir = /usr/include
pdfdir = ${docdir}
prefix = /Users/jasonk/projects/toppler-1.1.1-2-macosx/Toppler.app/Contents/Resources/toppler
program_transform_name = s,x,x,
psdir = ${docdir}
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
srcdir = .
sysconfdir = ${prefix}/etc
target = i386-apple-darwin8.10.1
target_alias = 
target_cpu = i386
target_os = darwin8.10.1
target_vendor = apple
top_builddir = .
top_srcdir = .
AM_CXXFLAGS = -Wall -DTOP_DATADIR=\"./Toppler.app/Content/Resources/toppler/share/\" -DHISCOREDIR=\"~/.toppler\" -DLOCALEDIR=\"./Toppler.app/Content/Resources/toppler/share/locale\"
SUBDIRS = po m4
ACLOCAL_AMFLAGS = -I m4
toppler_LDFLAGS = $(LIBINTL)
toppler_SOURCES = \
  archi.cc         archi.h         \
  bonus.cc         bonus.h         \
  configuration.cc configuration.h \
  decl.cc          decl.h          \
  elevators.cc     elevators.h     \
  game.cc          game.h          \
  highscore.cc     highscore.h     \
  keyb.cc          keyb.h          \
  level.cc         level.h         \
  leveledit.cc     leveledit.h     \
  menu.cc          menu.h          \
  menusys.cc       menusys.h       \
  main.cc                          \
  points.cc        points.h        \
  robots.cc        robots.h        \
  screen.cc        screen.h        \
  snowball.cc      snowball.h      \
  sound.cc         sound.h         \
  soundsys.cc      soundsys.h      \
  sprites.cc       sprites.h       \
  stars.cc         stars.h         \
  toppler.cc       toppler.h       \
  txtsys.cc        txtsys.h        \
  qnxicon.c

pixmapsdir = $(datadir)/pixmaps
applicationsdir = $(datadir)/applications
pkgdocdir = $(docdir)/$(PACKAGE)
pkglocalstatedir = $(localstatedir)/$(PACKAGE)
dist_pixmaps_DATA = $(PACKAGE).xpm
applications_DATA = $(PACKAGE).desktop
dist_man_MANS = toppler.6
dist_pkgdoc_DATA = AUTHORS COPYING ChangeLog NEWS README
dist_pkgdata_DATA = \
  toppler.dat toppler.ogg \
  m1.ttm m2.ttm ball1.ttm ball2.ttm ball3.ttm abc.ttm pasi2.ttm david1.ttm

dist_pkglocalstate_DATA = $(PACKAGE).hsc
EXTRA_DIST = \
  config.rpath mkinstalldirs \
  $(PACKAGE).spec \
  VERSION levelnames.txt \
  toppler.qpg

win32dir = $(PACKAGE)-$(VERSION)-win32
all: config.h
	$(MAKE) $(AM_MAKEFLAGS) all-recursive

.SUFFIXES:
.SUFFIXES: .c .cc .lo .o .obj
am--refresh:
	@:
$(srcdir)/Makefile.in: # $(srcdir)/Makefile.am  $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      echo ' cd $(srcdir) && $(AUTOMAKE) --gnu '; \
	      cd $(srcdir) && $(AUTOMAKE) --gnu  \
		&& exit 0; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --gnu  Makefile'; \
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  Makefile
.PRECIOUS: Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    echo ' $(SHELL) ./config.status'; \
	    $(SHELL) ./config.status;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $@ $(am__depfiles_maybe)'; \
	    cd $(top_builddir) && $(SHELL) ./config.status $@ $(am__depfiles_maybe);; \
	esac;

$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	$(SHELL) ./config.status --recheck

$(top_srcdir)/configure: # $(am__configure_deps)
	cd $(srcdir) && $(AUTOCONF)
$(ACLOCAL_M4): # $(am__aclocal_m4_deps)
	cd $(srcdir) && $(ACLOCAL) $(ACLOCAL_AMFLAGS)

config.h: stamp-h1
	@if test ! -f $@; then \
	  rm -f stamp-h1; \
	  $(MAKE) $(AM_MAKEFLAGS) stamp-h1; \
	else :; fi

stamp-h1: $(srcdir)/config.h.in $(top_builddir)/config.status
	@rm -f stamp-h1
	cd $(top_builddir) && $(SHELL) ./config.status config.h
$(srcdir)/config.h.in: # $(am__configure_deps) 
	cd $(top_srcdir) && $(AUTOHEADER)
	rm -f stamp-h1
	touch $@

distclean-hdr:
	-rm -f config.h stamp-h1
toppler.spec: $(top_builddir)/config.status $(srcdir)/toppler.spec.in
	cd $(top_builddir) && $(SHELL) ./config.status $@
toppler.nsi: $(top_builddir)/config.status $(srcdir)/toppler.nsi.in
	cd $(top_builddir) && $(SHELL) ./config.status $@
toppler.desktop: $(top_builddir)/config.status $(srcdir)/toppler.desktop.in
	cd $(top_builddir) && $(SHELL) ./config.status $@
toppler.qpg: $(top_builddir)/config.status $(srcdir)/toppler.qpg.in
	cd $(top_builddir) && $(SHELL) ./config.status $@
install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	test -z "$(bindir)" || $(MKDIR_P) "$(DESTDIR)$(bindir)"
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  p1=`echo $$p|sed 's/$(EXEEXT)$$//'`; \
	  if test -f $$p \
	     || test -f $$p1 \
	  ; then \
	    f=`echo "$$p1" | sed 's,^.*/,,;$(transform);s/$$/$(EXEEXT)/'`; \
	   echo " $(INSTALL_PROGRAM_ENV) $(LIBTOOL) --mode=install $(binPROGRAMS_INSTALL) '$$p' '$(DESTDIR)$(bindir)/$$f'"; \
	   $(INSTALL_PROGRAM_ENV) $(LIBTOOL) --mode=install $(binPROGRAMS_INSTALL) "$$p" "$(DESTDIR)$(bindir)/$$f" || exit 1; \
	  else :; fi; \
	done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  f=`echo "$$p" | sed 's,^.*/,,;s/$(EXEEXT)$$//;$(transform);s/$$/$(EXEEXT)/'`; \
	  echo " rm -f '$(DESTDIR)$(bindir)/$$f'"; \
	  rm -f "$(DESTDIR)$(bindir)/$$f"; \
	done

clean-binPROGRAMS:
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  f=`echo $$p|sed 's/$(EXEEXT)$$//'`; \
	  echo " rm -f $$p $$f"; \
	  rm -f $$p $$f ; \
	done
toppler$(EXEEXT): $(toppler_OBJECTS) $(toppler_DEPENDENCIES) 
	@rm -f toppler$(EXEEXT)
	$(toppler_LINK) $(toppler_OBJECTS) $(toppler_LDADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT)

distclean-compile:
	-rm -f *.tab.c

#include ./$(DEPDIR)/archi.Po
#include ./$(DEPDIR)/bonus.Po
#include ./$(DEPDIR)/configuration.Po
#include ./$(DEPDIR)/decl.Po
#include ./$(DEPDIR)/elevators.Po
#include ./$(DEPDIR)/game.Po
#include ./$(DEPDIR)/highscore.Po
#include ./$(DEPDIR)/keyb.Po
#include ./$(DEPDIR)/level.Po
#include ./$(DEPDIR)/leveledit.Po
#include ./$(DEPDIR)/main.Po
#include ./$(DEPDIR)/menu.Po
#include ./$(DEPDIR)/menusys.Po
#include ./$(DEPDIR)/points.Po
#include ./$(DEPDIR)/qnxicon.Po
#include ./$(DEPDIR)/robots.Po
#include ./$(DEPDIR)/screen.Po
#include ./$(DEPDIR)/snowball.Po
#include ./$(DEPDIR)/sound.Po
#include ./$(DEPDIR)/soundsys.Po
#include ./$(DEPDIR)/sprites.Po
#include ./$(DEPDIR)/stars.Po
#include ./$(DEPDIR)/toppler.Po
#include ./$(DEPDIR)/txtsys.Po

.c.o:
#	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
#	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	source='$<' object='$@' libtool=no 
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) 
	$(COMPILE) -c $<

.c.obj:
#	$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `$(CYGPATH_W) '$<'`
#	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	source='$<' object='$@' libtool=no 
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) 
	$(COMPILE) -c `$(CYGPATH_W) '$<'`

.c.lo:
#	$(LTCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
#	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Plo
#	source='$<' object='$@' libtool=yes 
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) 
	$(LTCOMPILE) -c -o $@ $<

.cc.o:
#	$(CXXCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
#	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	source='$<' object='$@' libtool=no 
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) 
	$(CXXCOMPILE) -c -o $@ $<

.cc.obj:
#	$(CXXCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `$(CYGPATH_W) '$<'`
#	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	source='$<' object='$@' libtool=no 
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) 
	$(CXXCOMPILE) -c -o $@ `$(CYGPATH_W) '$<'`

.cc.lo:
#	$(LTCXXCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
#	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Plo
#	source='$<' object='$@' libtool=yes 
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) 
	$(LTCXXCOMPILE) -c -o $@ $<

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:
	-rm -f libtool
install-man6: $(man6_MANS) $(man_MANS)
	@$(NORMAL_INSTALL)
	test -z "$(man6dir)" || $(MKDIR_P) "$(DESTDIR)$(man6dir)"
	@list='$(man6_MANS) $(dist_man6_MANS) $(nodist_man6_MANS)'; \
	l2='$(man_MANS) $(dist_man_MANS) $(nodist_man_MANS)'; \
	for i in $$l2; do \
	  case "$$i" in \
	    *.6*) list="$$list $$i" ;; \
	  esac; \
	done; \
	for i in $$list; do \
	  if test -f $(srcdir)/$$i; then file=$(srcdir)/$$i; \
	  else file=$$i; fi; \
	  ext=`echo $$i | sed -e 's/^.*\\.//'`; \
	  case "$$ext" in \
	    6*) ;; \
	    *) ext='6' ;; \
	  esac; \
	  inst=`echo $$i | sed -e 's/\\.[0-9a-z]*$$//'`; \
	  inst=`echo $$inst | sed -e 's/^.*\///'`; \
	  inst=`echo $$inst | sed '$(transform)'`.$$ext; \
	  echo " $(INSTALL_DATA) '$$file' '$(DESTDIR)$(man6dir)/$$inst'"; \
	  $(INSTALL_DATA) "$$file" "$(DESTDIR)$(man6dir)/$$inst"; \
	done
uninstall-man6:
	@$(NORMAL_UNINSTALL)
	@list='$(man6_MANS) $(dist_man6_MANS) $(nodist_man6_MANS)'; \
	l2='$(man_MANS) $(dist_man_MANS) $(nodist_man_MANS)'; \
	for i in $$l2; do \
	  case "$$i" in \
	    *.6*) list="$$list $$i" ;; \
	  esac; \
	done; \
	for i in $$list; do \
	  ext=`echo $$i | sed -e 's/^.*\\.//'`; \
	  case "$$ext" in \
	    6*) ;; \
	    *) ext='6' ;; \
	  esac; \
	  inst=`echo $$i | sed -e 's/\\.[0-9a-z]*$$//'`; \
	  inst=`echo $$inst | sed -e 's/^.*\///'`; \
	  inst=`echo $$inst | sed '$(transform)'`.$$ext; \
	  echo " rm -f '$(DESTDIR)$(man6dir)/$$inst'"; \
	  rm -f "$(DESTDIR)$(man6dir)/$$inst"; \
	done
install-applicationsDATA: $(applications_DATA)
	@$(NORMAL_INSTALL)
	test -z "$(applicationsdir)" || $(MKDIR_P) "$(DESTDIR)$(applicationsdir)"
	@list='$(applications_DATA)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f=$(am__strip_dir) \
	  echo " $(applicationsDATA_INSTALL) '$$d$$p' '$(DESTDIR)$(applicationsdir)/$$f'"; \
	  $(applicationsDATA_INSTALL) "$$d$$p" "$(DESTDIR)$(applicationsdir)/$$f"; \
	done

uninstall-applicationsDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(applications_DATA)'; for p in $$list; do \
	  f=$(am__strip_dir) \
	  echo " rm -f '$(DESTDIR)$(applicationsdir)/$$f'"; \
	  rm -f "$(DESTDIR)$(applicationsdir)/$$f"; \
	done
install-dist_pixmapsDATA: $(dist_pixmaps_DATA)
	@$(NORMAL_INSTALL)
	test -z "$(pixmapsdir)" || $(MKDIR_P) "$(DESTDIR)$(pixmapsdir)"
	@list='$(dist_pixmaps_DATA)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f=$(am__strip_dir) \
	  echo " $(dist_pixmapsDATA_INSTALL) '$$d$$p' '$(DESTDIR)$(pixmapsdir)/$$f'"; \
	  $(dist_pixmapsDATA_INSTALL) "$$d$$p" "$(DESTDIR)$(pixmapsdir)/$$f"; \
	done

uninstall-dist_pixmapsDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(dist_pixmaps_DATA)'; for p in $$list; do \
	  f=$(am__strip_dir) \
	  echo " rm -f '$(DESTDIR)$(pixmapsdir)/$$f'"; \
	  rm -f "$(DESTDIR)$(pixmapsdir)/$$f"; \
	done
install-dist_pkgdataDATA: $(dist_pkgdata_DATA)
	@$(NORMAL_INSTALL)
	test -z "$(pkgdatadir)" || $(MKDIR_P) "$(DESTDIR)$(pkgdatadir)"
	@list='$(dist_pkgdata_DATA)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f=$(am__strip_dir) \
	  echo " $(dist_pkgdataDATA_INSTALL) '$$d$$p' '$(DESTDIR)$(pkgdatadir)/$$f'"; \
	  $(dist_pkgdataDATA_INSTALL) "$$d$$p" "$(DESTDIR)$(pkgdatadir)/$$f"; \
	done

uninstall-dist_pkgdataDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(dist_pkgdata_DATA)'; for p in $$list; do \
	  f=$(am__strip_dir) \
	  echo " rm -f '$(DESTDIR)$(pkgdatadir)/$$f'"; \
	  rm -f "$(DESTDIR)$(pkgdatadir)/$$f"; \
	done
install-dist_pkgdocDATA: $(dist_pkgdoc_DATA)
	@$(NORMAL_INSTALL)
	test -z "$(pkgdocdir)" || $(MKDIR_P) "$(DESTDIR)$(pkgdocdir)"
	@list='$(dist_pkgdoc_DATA)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f=$(am__strip_dir) \
	  echo " $(dist_pkgdocDATA_INSTALL) '$$d$$p' '$(DESTDIR)$(pkgdocdir)/$$f'"; \
	  $(dist_pkgdocDATA_INSTALL) "$$d$$p" "$(DESTDIR)$(pkgdocdir)/$$f"; \
	done

uninstall-dist_pkgdocDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(dist_pkgdoc_DATA)'; for p in $$list; do \
	  f=$(am__strip_dir) \
	  echo " rm -f '$(DESTDIR)$(pkgdocdir)/$$f'"; \
	  rm -f "$(DESTDIR)$(pkgdocdir)/$$f"; \
	done
install-dist_pkglocalstateDATA: $(dist_pkglocalstate_DATA)
	@$(NORMAL_INSTALL)
	test -z "$(pkglocalstatedir)" || $(MKDIR_P) "$(DESTDIR)$(pkglocalstatedir)"
	@list='$(dist_pkglocalstate_DATA)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f=$(am__strip_dir) \
	  echo " $(dist_pkglocalstateDATA_INSTALL) '$$d$$p' '$(DESTDIR)$(pkglocalstatedir)/$$f'"; \
	  $(dist_pkglocalstateDATA_INSTALL) "$$d$$p" "$(DESTDIR)$(pkglocalstatedir)/$$f"; \
	done

uninstall-dist_pkglocalstateDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(dist_pkglocalstate_DATA)'; for p in $$list; do \
	  f=$(am__strip_dir) \
	  echo " rm -f '$(DESTDIR)$(pkglocalstatedir)/$$f'"; \
	  rm -f "$(DESTDIR)$(pkglocalstatedir)/$$f"; \
	done

# This directory's subdirectories are mostly independent; you can cd
# into them and run `make' without going through this Makefile.
# To change the values of `make' variables: instead of editing Makefiles,
# (1) if the variable is set in `config.status', edit `config.status'
#     (which will cause the Makefiles to be regenerated when you run `make');
# (2) otherwise, pass the desired values on the `make' command line.
$(RECURSIVE_TARGETS):
	@failcom='exit 1'; \
	for f in x $$MAKEFLAGS; do \
	  case $$f in \
	    *=* | --[!k]*);; \
	    *k*) failcom='fail=yes';; \
	  esac; \
	done; \
	dot_seen=no; \
	target=`echo $@ | sed s/-recursive//`; \
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  echo "Making $$target in $$subdir"; \
	  if test "$$subdir" = "."; then \
	    dot_seen=yes; \
	    local_target="$$target-am"; \
	  else \
	    local_target="$$target"; \
	  fi; \
	  (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$local_target) \
	  || eval $$failcom; \
	done; \
	if test "$$dot_seen" = "no"; then \
	  $(MAKE) $(AM_MAKEFLAGS) "$$target-am" || exit 1; \
	fi; test -z "$$fail"

$(RECURSIVE_CLEAN_TARGETS):
	@failcom='exit 1'; \
	for f in x $$MAKEFLAGS; do \
	  case $$f in \
	    *=* | --[!k]*);; \
	    *k*) failcom='fail=yes';; \
	  esac; \
	done; \
	dot_seen=no; \
	case "$@" in \
	  distclean-* | maintainer-clean-*) list='$(DIST_SUBDIRS)' ;; \
	  *) list='$(SUBDIRS)' ;; \
	esac; \
	rev=''; for subdir in $$list; do \
	  if test "$$subdir" = "."; then :; else \
	    rev="$$subdir $$rev"; \
	  fi; \
	done; \
	rev="$$rev ."; \
	target=`echo $@ | sed s/-recursive//`; \
	for subdir in $$rev; do \
	  echo "Making $$target in $$subdir"; \
	  if test "$$subdir" = "."; then \
	    local_target="$$target-am"; \
	  else \
	    local_target="$$target"; \
	  fi; \
	  (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$local_target) \
	  || eval $$failcom; \
	done && test -z "$$fail"
tags-recursive:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  test "$$subdir" = . || (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) tags); \
	done
ctags-recursive:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  test "$$subdir" = . || (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) ctags); \
	done

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	mkid -fID $$unique
tags: TAGS

TAGS: tags-recursive $(HEADERS) $(SOURCES) config.h.in $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	if ($(ETAGS) --etags-include --version) >/dev/null 2>&1; then \
	  include_option=--etags-include; \
	  empty_fix=.; \
	else \
	  include_option=--include; \
	  empty_fix=; \
	fi; \
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test "$$subdir" = .; then :; else \
	    test ! -f $$subdir/TAGS || \
	      tags="$$tags $$include_option=$$here/$$subdir/TAGS"; \
	  fi; \
	done; \
	list='$(SOURCES) $(HEADERS) config.h.in $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	if test -z "$(ETAGS_ARGS)$$tags$$unique"; then :; else \
	  test -n "$$unique" || unique=$$empty_fix; \
	  $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	    $$tags $$unique; \
	fi
ctags: CTAGS
CTAGS: ctags-recursive $(HEADERS) $(SOURCES) config.h.in $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS) config.h.in $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(CTAGS_ARGS)$$tags$$unique" \
	  || $(CTAGS) $(CTAGSFLAGS) $(AM_CTAGSFLAGS) $(CTAGS_ARGS) \
	     $$tags $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && cd $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) $$here

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH tags

distdir: $(DISTFILES)
	$(am__remove_distdir)
	test -d $(distdir) || mkdir $(distdir)
	@srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	list='$(DISTFILES)'; \
	  dist_files=`for file in $$list; do echo $$file; done | \
	  sed -e "s|^$$srcdirstrip/||;t" \
	      -e "s|^$$topsrcdirstrip/|$(top_builddir)/|;t"`; \
	case $$dist_files in \
	  */*) $(MKDIR_P) `echo "$$dist_files" | \
			   sed '/\//!d;s|^|$(distdir)/|;s,/[^/]*$$,,' | \
			   sort -u` ;; \
	esac; \
	for file in $$dist_files; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`; \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -pR $(srcdir)/$$file $(distdir)$$dir || exit 1; \
	    fi; \
	    cp -pR $$d/$$file $(distdir)$$dir || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
	list='$(DIST_SUBDIRS)'; for subdir in $$list; do \
	  if test "$$subdir" = .; then :; else \
	    test -d "$(distdir)/$$subdir" \
	    || $(MKDIR_P) "$(distdir)/$$subdir" \
	    || exit 1; \
	    distdir=`$(am__cd) $(distdir) && pwd`; \
	    top_distdir=`$(am__cd) $(top_distdir) && pwd`; \
	    (cd $$subdir && \
	      $(MAKE) $(AM_MAKEFLAGS) \
	        top_distdir="$$top_distdir" \
	        distdir="$$distdir/$$subdir" \
		am__remove_distdir=: \
		am__skip_length_check=: \
	        distdir) \
	      || exit 1; \
	  fi; \
	done
	-find $(distdir) -type d ! -perm -777 -exec chmod a+rwx {} \; -o \
	  ! -type d ! -perm -444 -links 1 -exec chmod a+r {} \; -o \
	  ! -type d ! -perm -400 -exec chmod a+r {} \; -o \
	  ! -type d ! -perm -444 -exec $(install_sh) -c -m a+r {} {} \; \
	|| chmod -R a+r $(distdir)
dist-gzip: distdir
	tardir=$(distdir) && $(am__tar) | GZIP=$(GZIP_ENV) gzip -c >$(distdir).tar.gz
	$(am__remove_distdir)

dist-bzip2: distdir
	tardir=$(distdir) && $(am__tar) | bzip2 -9 -c >$(distdir).tar.bz2
	$(am__remove_distdir)

dist-tarZ: distdir
	tardir=$(distdir) && $(am__tar) | compress -c >$(distdir).tar.Z
	$(am__remove_distdir)

dist-shar: distdir
	shar $(distdir) | GZIP=$(GZIP_ENV) gzip -c >$(distdir).shar.gz
	$(am__remove_distdir)

dist-zip: distdir
	-rm -f $(distdir).zip
	zip -rq $(distdir).zip $(distdir)
	$(am__remove_distdir)

dist dist-all: distdir
	tardir=$(distdir) && $(am__tar) | GZIP=$(GZIP_ENV) gzip -c >$(distdir).tar.gz
	$(am__remove_distdir)

# This target untars the dist file and tries a VPATH configuration.  Then
# it guarantees that the distribution is self-contained by making another
# tarfile.
distcheck: dist
	case '$(DIST_ARCHIVES)' in \
	*.tar.gz*) \
	  GZIP=$(GZIP_ENV) gunzip -c $(distdir).tar.gz | $(am__untar) ;;\
	*.tar.bz2*) \
	  bunzip2 -c $(distdir).tar.bz2 | $(am__untar) ;;\
	*.tar.Z*) \
	  uncompress -c $(distdir).tar.Z | $(am__untar) ;;\
	*.shar.gz*) \
	  GZIP=$(GZIP_ENV) gunzip -c $(distdir).shar.gz | unshar ;;\
	*.zip*) \
	  unzip $(distdir).zip ;;\
	esac
	chmod -R a-w $(distdir); chmod a+w $(distdir)
	mkdir $(distdir)/_build
	mkdir $(distdir)/_inst
	chmod a-w $(distdir)
	dc_install_base=`$(am__cd) $(distdir)/_inst && pwd | sed -e 's,^[^:\\/]:[\\/],/,'` \
	  && dc_destdir="$${TMPDIR-/tmp}/am-dc-$$$$/" \
	  && cd $(distdir)/_build \
	  && ../configure --srcdir=.. --prefix="$$dc_install_base" \
	    $(DISTCHECK_CONFIGURE_FLAGS) \
	  && $(MAKE) $(AM_MAKEFLAGS) \
	  && $(MAKE) $(AM_MAKEFLAGS) dvi \
	  && $(MAKE) $(AM_MAKEFLAGS) check \
	  && $(MAKE) $(AM_MAKEFLAGS) install \
	  && $(MAKE) $(AM_MAKEFLAGS) installcheck \
	  && $(MAKE) $(AM_MAKEFLAGS) uninstall \
	  && $(MAKE) $(AM_MAKEFLAGS) distuninstallcheck_dir="$$dc_install_base" \
	        distuninstallcheck \
	  && chmod -R a-w "$$dc_install_base" \
	  && ({ \
	       (cd ../.. && umask 077 && mkdir "$$dc_destdir") \
	       && $(MAKE) $(AM_MAKEFLAGS) DESTDIR="$$dc_destdir" install \
	       && $(MAKE) $(AM_MAKEFLAGS) DESTDIR="$$dc_destdir" uninstall \
	       && $(MAKE) $(AM_MAKEFLAGS) DESTDIR="$$dc_destdir" \
	            distuninstallcheck_dir="$$dc_destdir" distuninstallcheck; \
	      } || { rm -rf "$$dc_destdir"; exit 1; }) \
	  && rm -rf "$$dc_destdir" \
	  && $(MAKE) $(AM_MAKEFLAGS) dist \
	  && rm -rf $(DIST_ARCHIVES) \
	  && $(MAKE) $(AM_MAKEFLAGS) distcleancheck
	$(am__remove_distdir)
	@(echo "$(distdir) archives ready for distribution: "; \
	  list='$(DIST_ARCHIVES)'; for i in $$list; do echo $$i; done) | \
	  sed -e 1h -e 1s/./=/g -e 1p -e 1x -e '$$p' -e '$$x'
distuninstallcheck:
	@cd $(distuninstallcheck_dir) \
	&& test `$(distuninstallcheck_listfiles) | wc -l` -le 1 \
	   || { echo "ERROR: files left after uninstall:" ; \
	        if test -n "$(DESTDIR)"; then \
	          echo "  (check DESTDIR support)"; \
	        fi ; \
	        $(distuninstallcheck_listfiles) ; \
	        exit 1; } >&2
distcleancheck: distclean
	@if test '$(srcdir)' = . ; then \
	  echo "ERROR: distcleancheck can only run from a VPATH build" ; \
	  exit 1 ; \
	fi
	@test `$(distcleancheck_listfiles) | wc -l` -eq 0 \
	  || { echo "ERROR: files left in build directory after distclean:" ; \
	       $(distcleancheck_listfiles) ; \
	       exit 1; } >&2
check-am: all-am
check: check-recursive
all-am: Makefile $(PROGRAMS) $(MANS) $(DATA) config.h
installdirs: installdirs-recursive
installdirs-am:
	for dir in "$(DESTDIR)$(bindir)" "$(DESTDIR)$(man6dir)" "$(DESTDIR)$(applicationsdir)" "$(DESTDIR)$(pixmapsdir)" "$(DESTDIR)$(pkgdatadir)" "$(DESTDIR)$(pkgdocdir)" "$(DESTDIR)$(pkglocalstatedir)"; do \
	  test -z "$$dir" || $(MKDIR_P) "$$dir"; \
	done
install: install-recursive
install-exec: install-exec-recursive
install-data: install-data-recursive
uninstall: uninstall-recursive

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-recursive
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-recursive

clean-am: clean-binPROGRAMS clean-generic clean-libtool mostlyclean-am

distclean: distclean-recursive
	-rm -f $(am__CONFIG_DISTCLEAN_FILES)
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
distclean-am: clean-am distclean-compile distclean-generic \
	distclean-hdr distclean-libtool distclean-tags

dvi: dvi-recursive

dvi-am:

html: html-recursive

info: info-recursive

info-am:

install-data-am: install-applicationsDATA install-dist_pixmapsDATA \
	install-dist_pkgdataDATA install-dist_pkgdocDATA \
	install-dist_pkglocalstateDATA install-man
	@$(NORMAL_INSTALL)
	$(MAKE) $(AM_MAKEFLAGS) install-data-hook

install-dvi: install-dvi-recursive

install-exec-am: install-binPROGRAMS
	@$(NORMAL_INSTALL)
	$(MAKE) $(AM_MAKEFLAGS) install-exec-hook

install-html: install-html-recursive

install-info: install-info-recursive

install-man: install-man6

install-pdf: install-pdf-recursive

install-ps: install-ps-recursive

installcheck-am:

maintainer-clean: maintainer-clean-recursive
	-rm -f $(am__CONFIG_DISTCLEAN_FILES)
	-rm -rf $(top_srcdir)/autom4te.cache
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-recursive

mostlyclean-am: mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool

pdf: pdf-recursive

pdf-am:

ps: ps-recursive

ps-am:

uninstall-am: uninstall-applicationsDATA uninstall-binPROGRAMS \
	uninstall-dist_pixmapsDATA uninstall-dist_pkgdataDATA \
	uninstall-dist_pkgdocDATA uninstall-dist_pkglocalstateDATA \
	uninstall-man

uninstall-man: uninstall-man6

.MAKE: $(RECURSIVE_CLEAN_TARGETS) $(RECURSIVE_TARGETS) install-am \
	install-data-am install-exec-am install-strip

.PHONY: $(RECURSIVE_CLEAN_TARGETS) $(RECURSIVE_TARGETS) CTAGS GTAGS \
	all all-am am--refresh check check-am clean clean-binPROGRAMS \
	clean-generic clean-libtool ctags ctags-recursive dist \
	dist-all dist-bzip2 dist-gzip dist-shar dist-tarZ dist-zip \
	distcheck distclean distclean-compile distclean-generic \
	distclean-hdr distclean-libtool distclean-tags distcleancheck \
	distdir distuninstallcheck dvi dvi-am html html-am info \
	info-am install install-am install-applicationsDATA \
	install-binPROGRAMS install-data install-data-am \
	install-data-hook install-dist_pixmapsDATA \
	install-dist_pkgdataDATA install-dist_pkgdocDATA \
	install-dist_pkglocalstateDATA install-dvi install-dvi-am \
	install-exec install-exec-am install-exec-hook install-html \
	install-html-am install-info install-info-am install-man \
	install-man6 install-pdf install-pdf-am install-ps \
	install-ps-am install-strip installcheck installcheck-am \
	installdirs installdirs-am maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-compile \
	mostlyclean-generic mostlyclean-libtool pdf pdf-am ps ps-am \
	tags tags-recursive uninstall uninstall-am \
	uninstall-applicationsDATA uninstall-binPROGRAMS \
	uninstall-dist_pixmapsDATA uninstall-dist_pkgdataDATA \
	uninstall-dist_pkgdocDATA uninstall-dist_pkglocalstateDATA \
	uninstall-man uninstall-man6


install-exec-hook:
	-chgrp games $(DESTDIR)$(bindir)/toppler
	-chmod 2755 $(DESTDIR)$(bindir)/toppler

install-data-hook:
	-chgrp games $(DESTDIR)$(pkglocalstatedir)/$(PACKAGE).hsc
	-chmod 0664 $(DESTDIR)$(pkglocalstatedir)/$(PACKAGE).hsc

dist-win32: $(PACKAGE).exe
	$(RM) -r $(win32dir)
	$(INSTALL)                   -d $(win32dir)
	$(INSTALL) -m755 $(PACKAGE).exe $(win32dir)/
	$(STRIP) $(win32dir)/$(PACKAGE).exe
	upx      $(win32dir)/$(PACKAGE).exe
	cd $(srcdir) && $(INSTALL) -m644 \
	    $(dist_pkgdata_DATA) $(dist_pkglocalstate_DATA) \
	    $(abs_builddir)/$(win32dir)/
	cd $(srcdir) && for FILE in $(dist_pkgdoc_DATA); do \
	    sed 's,$$,\r,' < $$FILE > $(abs_builddir)/$(win32dir)/$$FILE.txt; \
	    done
	xpmtoppm --alphaout=$(PACKAGE)-alpha.pbm $(srcdir)/$(PACKAGE).xpm > $(PACKAGE).ppm
	ppmtowinicon -andpgms $(PACKAGE).ppm $(PACKAGE)-alpha.pbm > $(win32dir)/$(PACKAGE).ico
	$(RM)                 $(PACKAGE).ppm $(PACKAGE)-alpha.pbm
	$(MAKE) -C po install localedir=$(abs_builddir)/$(win32dir)/locale
	$(RM)   $(win32dir).zip
	zip -r9 $(win32dir).zip $(win32dir)
	makensis $(PACKAGE).nsi
	$(RM) -r $(win32dir)
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT: