# Makefile.in generated automatically by automake 1.5 from Makefile.am.

# Copyright 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001
# Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



SHELL = /bin/sh

srcdir = .
top_srcdir = .

prefix = ./Toppler.app/Contents/Resources/toppler
exec_prefix = ./Toppler.app/Contents/MacOS

bindir = ./Toppler.app/Contents/MacOS
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include
pkgdatadir = $(datadir)/toppler
pkglibdir = $(libdir)/toppler
pkgincludedir = $(includedir)/toppler
top_builddir = .

ACLOCAL = ${SHELL} /Users/jasonk/projects/toppler-1.1.1-macosx/missing --run aclocal
AUTOCONF = ${SHELL} /Users/jasonk/projects/toppler-1.1.1-macosx/missing --run autoconf
AUTOMAKE = ${SHELL} /Users/jasonk/projects/toppler-1.1.1-macosx/missing --run automake
AUTOHEADER = ${SHELL} /Users/jasonk/projects/toppler-1.1.1-macosx/missing --run autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
INSTALL_HEADER = $(INSTALL_DATA)
transform = s,x,x,
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = 
host_triplet = i386-apple-darwin8.10.1
AMTAR = ${SHELL} /Users/jasonk/projects/toppler-1.1.1-macosx/missing --run tar
AWK = awk
BUILD_INCLUDED_LIBINTL = @BUILD_INCLUDED_LIBINTL@
CATOBJEXT = @CATOBJEXT@
CC = gcc
CXX = g++
DATADIRNAME = @DATADIRNAME@
DEPDIR = .deps
EXEEXT = 
GENCAT = @GENCAT@
GLIBC21 = @GLIBC21@
GMSGFMT = /usr/local/bin/msgfmt
HAVE_LIB = @HAVE_LIB@
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
INSTOBJEXT = @INSTOBJEXT@
INTLBISON = @INTLBISON@
INTLLIBS = -lintl
INTLOBJS = @INTLOBJS@
INTL_LIBTOOL_SUFFIX_PREFIX = @INTL_LIBTOOL_SUFFIX_PREFIX@
LIB = @LIB@
LIBICONV = -liconv
LIBINTL = -lintl
LN_S = ln -s
LTLIB = @LTLIB@
LTLIBICONV = -liconv
LTLIBINTL = -lintl
MAINT = #
MKINSTALLDIRS = $(top_builddir)/./mkinstalldirs
OBJEXT = o
PACKAGE = toppler
POSUB = po
RANLIB = @RANLIB@
SDL_CFLAGS = -I/usr/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE
SDL_CONFIG = /usr/local/bin/sdl-config
SDL_LIBS = -L/usr/local/lib -lSDLmain -lSDL -framework Cocoa -framework OpenGL
USE_INCLUDED_LIBINTL = @USE_INCLUDED_LIBINTL@
USE_NLS = yes
VERSION = 1.1.1
am__include = include
am__quote = 
install_sh = /Users/jasonk/projects/toppler-1.1.1-macosx/install-sh

CPPFLAGS = -Wall -I/usr/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -DTOP_DATADIR=\"$(pkgdatadir)\" -DHISCOREDIR=\"$(scoredir)\" -DLOCALEDIR=\"$(datadir)\"

bin_PROGRAMS = toppler

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
  main.cc          config.h        \
  points.cc        points.h        \
  robots.cc        robots.h        \
  screen.cc        screen.h        \
  snowball.cc      snowball.h      \
  sound.cc         sound.h         \
  soundsys.cc      soundsys.h      \
  sprites.cc       sprites.h       \
  stars.cc         stars.h         \
  toppler.cc       toppler.h       \
  txtsys.cc        txtsys.h


pkgdata_DATA = \
  toppler.dat \
  m1.ttm m2.ttm ball1.ttm ball2.ttm ball3.ttm abc.ttm pasi2.ttm \
  toppler.xpm


man_MANS = toppler.6

EXTRA_DIST = config.rpath  $(man_MANS) $(pkgdata_DATA) VERSION toppler.spec toppler.xpm

scoredir = $(localstatedir)/toppler
scorefile = $(scoredir)/toppler.hsc

SUBDIRS = po
subdir = .
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = config.h
CONFIG_CLEAN_FILES = toppler.spec toppler.desktop
bin_PROGRAMS = toppler$(EXEEXT)
PROGRAMS = $(bin_PROGRAMS)

am_toppler_OBJECTS = archi.$(OBJEXT) bonus.$(OBJEXT) \
	configuration.$(OBJEXT) decl.$(OBJEXT) elevators.$(OBJEXT) \
	game.$(OBJEXT) highscore.$(OBJEXT) keyb.$(OBJEXT) \
	level.$(OBJEXT) leveledit.$(OBJEXT) menu.$(OBJEXT) \
	menusys.$(OBJEXT) main.$(OBJEXT) points.$(OBJEXT) \
	robots.$(OBJEXT) screen.$(OBJEXT) snowball.$(OBJEXT) \
	sound.$(OBJEXT) soundsys.$(OBJEXT) sprites.$(OBJEXT) \
	stars.$(OBJEXT) toppler.$(OBJEXT) txtsys.$(OBJEXT)
toppler_OBJECTS = $(am_toppler_OBJECTS)
toppler_LDADD = $(LDADD)
toppler_DEPENDENCIES =
toppler_LDFLAGS =

DEFS = -DHAVE_CONFIG_H
DEFAULT_INCLUDES =  -I. -I$(srcdir) -I.
LDFLAGS = -arch i386 -arch ppc
LIBS = -lz -lSDL_mixer -lintl -L/usr/local/lib -lSDLmain -lSDL -framework Cocoa -framework OpenGL
depcomp = $(SHELL) $(top_srcdir)/depcomp
#DEP_FILES = $(DEPDIR)/archi.Po $(DEPDIR)/bonus.Po \
#	$(DEPDIR)/configuration.Po $(DEPDIR)/decl.Po \
#	$(DEPDIR)/elevators.Po $(DEPDIR)/game.Po \
#	$(DEPDIR)/highscore.Po $(DEPDIR)/keyb.Po \
#	$(DEPDIR)/level.Po $(DEPDIR)/leveledit.Po \
#	$(DEPDIR)/main.Po $(DEPDIR)/menu.Po \
#	$(DEPDIR)/menusys.Po $(DEPDIR)/points.Po \
#	$(DEPDIR)/robots.Po $(DEPDIR)/screen.Po \
#	$(DEPDIR)/snowball.Po $(DEPDIR)/sound.Po \
#	$(DEPDIR)/soundsys.Po $(DEPDIR)/sprites.Po \
#	$(DEPDIR)/stars.Po $(DEPDIR)/toppler.Po \
#	$(DEPDIR)/txtsys.Po
CXXCOMPILE = $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
CXXLD = $(CXX)
CXXLINK = $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
	-o $@
CXXFLAGS = -arch i386 -arch ppc
CFLAGS = -arch ppc -arch i386
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
DIST_SOURCES = $(toppler_SOURCES)

NROFF = nroff
MANS = $(man_MANS)
DATA = $(pkgdata_DATA)


RECURSIVE_TARGETS = info-recursive dvi-recursive install-info-recursive \
	uninstall-info-recursive all-recursive install-data-recursive \
	install-exec-recursive installdirs-recursive install-recursive \
	uninstall-recursive check-recursive installcheck-recursive
DIST_COMMON = README ./stamp-h.in ABOUT-NLS AUTHORS COPYING ChangeLog \
	INSTALL Makefile.am Makefile.in NEWS aclocal.m4 config.guess \
	config.h.in config.sub configure configure.ac depcomp \
	install-sh missing mkinstalldirs toppler.desktop.in \
	toppler.spec.in
DIST_SUBDIRS = $(SUBDIRS)
SOURCES = $(toppler_SOURCES)

all: config.h
	$(MAKE) $(AM_MAKEFLAGS) all-recursive

.SUFFIXES:
.SUFFIXES: .cc .o .obj
$(srcdir)/Makefile.in: # Makefile.am  $(top_srcdir)/configure.ac $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  Makefile
Makefile: # $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && \
	  CONFIG_HEADERS= CONFIG_LINKS= \
	  CONFIG_FILES=$@ $(SHELL) ./config.status

$(top_builddir)/config.status: $(srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	$(SHELL) ./config.status --recheck
$(srcdir)/configure: # $(srcdir)/configure.ac $(ACLOCAL_M4) $(CONFIGURE_DEPENDENCIES)
	cd $(srcdir) && $(AUTOCONF)

$(ACLOCAL_M4): # configure.ac 
	cd $(srcdir) && $(ACLOCAL) $(ACLOCAL_AMFLAGS)
config.h: stamp-h
	@if test ! -f $@; then \
		rm -f stamp-h; \
		$(MAKE) stamp-h; \
	else :; fi
stamp-h: $(srcdir)/config.h.in $(top_builddir)/config.status
	@rm -f stamp-h stamp-hT
	@echo timestamp > stamp-hT 2> /dev/null
	cd $(top_builddir) \
	  && CONFIG_FILES= CONFIG_HEADERS=config.h \
	     $(SHELL) ./config.status
	@mv stamp-hT stamp-h
$(srcdir)/config.h.in: # $(srcdir)/./stamp-h.in
	@if test ! -f $@; then \
		rm -f $(srcdir)/./stamp-h.in; \
		$(MAKE) $(srcdir)/./stamp-h.in; \
	else :; fi
$(srcdir)/./stamp-h.in: $(top_srcdir)/configure.ac $(ACLOCAL_M4) 
	@rm -f $(srcdir)/./stamp-h.in $(srcdir)/./stamp-h.inT
	@echo timestamp > $(srcdir)/./stamp-h.inT 2> /dev/null
	cd $(top_srcdir) && $(AUTOHEADER)
	@mv $(srcdir)/./stamp-h.inT $(srcdir)/./stamp-h.in

distclean-hdr:
	-rm -f config.h
toppler.spec: $(top_builddir)/config.status toppler.spec.in
	cd $(top_builddir) && CONFIG_FILES=$@ CONFIG_HEADERS= CONFIG_LINKS= $(SHELL) ./config.status
toppler.desktop: $(top_builddir)/config.status toppler.desktop.in
	cd $(top_builddir) && CONFIG_FILES=$@ CONFIG_HEADERS= CONFIG_LINKS= $(SHELL) ./config.status
install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  p1=`echo $$p|sed 's/$(EXEEXT)$$//'`; \
	  if test -f $$p \
	  ; then \
	    f=`echo $$p1|sed '$(transform);s/$$/$(EXEEXT)/'`; \
	   echo " $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/$$f"; \
	   $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/$$f; \
	  else :; fi; \
	done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  f=`echo $$p|sed 's/$(EXEEXT)$$//;$(transform);s/$$/$(EXEEXT)/'`; \
	  echo " rm -f $(DESTDIR)$(bindir)/$$f"; \
	  rm -f $(DESTDIR)$(bindir)/$$f; \
	done

clean-binPROGRAMS:
	-test -z "$(bin_PROGRAMS)" || rm -f $(bin_PROGRAMS)
toppler$(EXEEXT): $(toppler_OBJECTS) $(toppler_DEPENDENCIES) 
	@rm -f toppler$(EXEEXT)
	$(CXXLINK) $(toppler_LDFLAGS) $(toppler_OBJECTS) $(toppler_LDADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT) core *.core

distclean-compile:
	-rm -f *.tab.c

#include $(DEPDIR)/archi.Po
#include $(DEPDIR)/bonus.Po
#include $(DEPDIR)/configuration.Po
#include $(DEPDIR)/decl.Po
#include $(DEPDIR)/elevators.Po
#include $(DEPDIR)/game.Po
#include $(DEPDIR)/highscore.Po
#include $(DEPDIR)/keyb.Po
#include $(DEPDIR)/level.Po
#include $(DEPDIR)/leveledit.Po
#include $(DEPDIR)/main.Po
#include $(DEPDIR)/menu.Po
#include $(DEPDIR)/menusys.Po
#include $(DEPDIR)/points.Po
#include $(DEPDIR)/robots.Po
#include $(DEPDIR)/screen.Po
#include $(DEPDIR)/snowball.Po
#include $(DEPDIR)/sound.Po
#include $(DEPDIR)/soundsys.Po
#include $(DEPDIR)/sprites.Po
#include $(DEPDIR)/stars.Po
#include $(DEPDIR)/toppler.Po
#include $(DEPDIR)/txtsys.Po

distclean-depend:
	-rm -rf $(DEPDIR)

.cc.o:
#	source='$<' object='$@' libtool=no 
#	depfile='$(DEPDIR)/$*.Po' tmpdepfile='$(DEPDIR)/$*.TPo' 
#	$(CXXDEPMODE) $(depcomp) 
	$(CXXCOMPILE) -c -o $@ `test -f $< || echo '$(srcdir)/'`$<

.cc.obj:
#	source='$<' object='$@' libtool=no 
#	depfile='$(DEPDIR)/$*.Po' tmpdepfile='$(DEPDIR)/$*.TPo' 
#	$(CXXDEPMODE) $(depcomp) 
	$(CXXCOMPILE) -c -o $@ `cygpath -w $<`
CXXDEPMODE = depmode=none
uninstall-info-am:

man6dir = $(mandir)/man6
install-man6: $(man6_MANS) $(man_MANS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(man6dir)
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
	  inst=`echo $$i | sed -e 's/\\.[0-9a-z]*$$//'`; \
	  inst=`echo $$inst | sed -e 's/^.*\///'`; \
	  inst=`echo $$inst | sed '$(transform)'`.$$ext; \
	  echo " $(INSTALL_DATA) $$file $(DESTDIR)$(man6dir)/$$inst"; \
	  $(INSTALL_DATA) $$file $(DESTDIR)$(man6dir)/$$inst; \
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
	  inst=`echo $$i | sed -e 's/\\.[0-9a-z]*$$//'`; \
	  inst=`echo $$inst | sed -e 's/^.*\///'`; \
	  inst=`echo $$inst | sed '$(transform)'`.$$ext; \
	  echo " rm -f $(DESTDIR)$(man6dir)/$$inst"; \
	  rm -f $(DESTDIR)$(man6dir)/$$inst; \
	done
install-pkgdataDATA: $(pkgdata_DATA)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)
	@list='$(pkgdata_DATA)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$d$$p $(DESTDIR)$(pkgdatadir)/$$f"; \
	  $(INSTALL_DATA) $$d$$p $(DESTDIR)$(pkgdatadir)/$$f; \
	done

uninstall-pkgdataDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(pkgdata_DATA)'; for p in $$list; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(pkgdatadir)/$$f"; \
	  rm -f $(DESTDIR)$(pkgdatadir)/$$f; \
	done

# This directory's subdirectories are mostly independent; you can cd
# into them and run `make' without going through this Makefile.
# To change the values of `make' variables: instead of editing Makefiles,
# (1) if the variable is set in `config.status', edit `config.status'
#     (which will cause the Makefiles to be regenerated when you run `make');
# (2) otherwise, pass the desired values on the `make' command line.
$(RECURSIVE_TARGETS):
	@set fnord $(MAKEFLAGS); amf=$$2; \
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
	   || case "$$amf" in *=*) exit 1;; *k*) fail=yes;; *) exit 1;; esac; \
	done; \
	if test "$$dot_seen" = "no"; then \
	  $(MAKE) $(AM_MAKEFLAGS) "$$target-am" || exit 1; \
	fi; test -z "$$fail"

mostlyclean-recursive clean-recursive distclean-recursive \
maintainer-clean-recursive:
	@set fnord $(MAKEFLAGS); amf=$$2; \
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
	   || case "$$amf" in *=*) exit 1;; *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"
tags-recursive:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  test "$$subdir" = . || (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) tags); \
	done

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	mkid -fID $$unique $(LISP)

TAGS: tags-recursive $(HEADERS) $(SOURCES) config.h.in $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test "$$subdir" = .; then :; else \
	    test -f $$subdir/TAGS && tags="$$tags -i $$here/$$subdir/TAGS"; \
	  fi; \
	done; \
	list='$(SOURCES) $(HEADERS) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)config.h.in$$unique$(LISP)$$tags" \
	  || etags $(ETAGS_ARGS) $$tags config.h.in $$unique $(LISP)

GTAGS:
	here=`CDPATH=: && cd $(top_builddir) && pwd` \
	  && cd $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) $$here

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH

DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = .
# Avoid unsightly `./'.
distdir = $(PACKAGE)-$(VERSION)

GZIP_ENV = --best

distdir: $(DISTFILES)
	-chmod -R a+w $(distdir) >/dev/null 2>&1; rm -rf $(distdir)
	mkdir $(distdir)
	$(mkinstalldirs) $(distdir)/. $(distdir)/po
	@for file in $(DISTFILES); do \
	  if test -f $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    $(mkinstalldirs) "$(distdir)/$$dir"; \
	  fi; \
	  if test -d $$d/$$file; then \
	    cp -pR $$d/$$file $(distdir) \
	    || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
	for subdir in $(SUBDIRS); do \
	  if test "$$subdir" = .; then :; else \
	    test -d $(distdir)/$$subdir \
	    || mkdir $(distdir)/$$subdir \
	    || exit 1; \
	    (cd $$subdir && \
	      $(MAKE) $(AM_MAKEFLAGS) \
	        top_distdir="$(top_distdir)" \
	        distdir=../$(distdir)/$$subdir \
	        distdir) \
	      || exit 1; \
	  fi; \
	done
	-find $(distdir) -type d ! -perm -777 -exec chmod a+rwx {} \; -o \
	  ! -type d ! -perm -444 -links 1 -exec chmod a+r {} \; -o \
	  ! -type d ! -perm -400 -exec chmod a+r {} \; -o \
	  ! -type d ! -perm -444 -exec $(SHELL) $(install_sh) -c -m a+r {} {} \; \
	|| chmod -R a+r $(distdir)
dist: distdir
	$(AMTAR) chof - $(distdir) | GZIP=$(GZIP_ENV) gzip -c >$(distdir).tar.gz
	-chmod -R a+w $(distdir) >/dev/null 2>&1; rm -rf $(distdir)

# This target untars the dist file and tries a VPATH configuration.  Then
# it guarantees that the distribution is self-contained by making another
# tarfile.
distcheck: dist
	-chmod -R a+w $(distdir) > /dev/null 2>&1; rm -rf $(distdir)
	GZIP=$(GZIP_ENV) gunzip -c $(distdir).tar.gz | $(AMTAR) xf -
	chmod -R a-w $(distdir); chmod a+w $(distdir)
	mkdir $(distdir)/=build
	mkdir $(distdir)/=inst
	chmod a-w $(distdir)
	dc_install_base=`CDPATH=: && cd $(distdir)/=inst && pwd` \
	  && cd $(distdir)/=build \
	  && ../configure --srcdir=.. --prefix=$$dc_install_base \
	    --with-included-gettext \
	  && $(MAKE) $(AM_MAKEFLAGS) \
	  && $(MAKE) $(AM_MAKEFLAGS) dvi \
	  && $(MAKE) $(AM_MAKEFLAGS) check \
	  && $(MAKE) $(AM_MAKEFLAGS) install \
	  && $(MAKE) $(AM_MAKEFLAGS) installcheck \
	  && $(MAKE) $(AM_MAKEFLAGS) uninstall \
	  && (test `find $$dc_install_base -type f -print | wc -l` -le 1 \
	     || (echo "Error: files left after uninstall" 1>&2; \
	         exit 1) ) \
	  && $(MAKE) $(AM_MAKEFLAGS) dist \
	  && $(MAKE) $(AM_MAKEFLAGS) distclean \
	  && rm -f $(distdir).tar.gz \
	  && (test `find . -type f -print | wc -l` -eq 0 \
	     || (echo "Error: files left after distclean" 1>&2; \
	         exit 1) )
	-chmod -R a+w $(distdir) > /dev/null 2>&1; rm -rf $(distdir)
	@echo "$(distdir).tar.gz is ready for distribution" | \
	  sed 'h;s/./=/g;p;x;p;x'
check-am: all-am
check: check-recursive
all-am: Makefile $(PROGRAMS) $(MANS) $(DATA) config.h
installdirs: installdirs-recursive
installdirs-am:
	$(mkinstalldirs) $(DESTDIR)$(bindir) $(DESTDIR)$(man6dir) $(DESTDIR)$(pkgdatadir)

install: install-recursive install-mac
install-exec: install-exec-recursive
install-data: install-data-recursive
uninstall: uninstall-recursive

install-mac:
	./macfiles/make-bundle.sh

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-recursive
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES) stamp-h stamp-h[0-9]*

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-recursive

clean-am: clean-binPROGRAMS clean-generic mostlyclean-am

dist-all: distdir
	$(AMTAR) chof - $(distdir) | GZIP=$(GZIP_ENV) gzip -c >$(distdir).tar.gz
	-chmod -R a+w $(distdir) >/dev/null 2>&1; rm -rf $(distdir)
distclean: distclean-recursive
	-rm -f config.status config.cache config.log
distclean-am: clean-am distclean-compile distclean-depend \
	distclean-generic distclean-hdr distclean-tags

dvi: dvi-recursive

dvi-am:

info: info-recursive

info-am:

install-data-am: install-man install-pkgdataDATA

install-exec-am: install-binPROGRAMS

install-info: install-info-recursive

install-man: install-man6

installcheck-am:

maintainer-clean: maintainer-clean-recursive

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-recursive

mostlyclean-am: mostlyclean-compile mostlyclean-generic

uninstall-am: uninstall-binPROGRAMS uninstall-info-am uninstall-man \
	uninstall-pkgdataDATA

uninstall-info: uninstall-info-recursive

uninstall-man: uninstall-man6

.PHONY: $(RECURSIVE_TARGETS) GTAGS all all-am check check-am clean \
	clean-binPROGRAMS clean-generic clean-recursive dist dist-all \
	distcheck distclean distclean-compile distclean-depend \
	distclean-generic distclean-hdr distclean-recursive \
	distclean-tags distdir dvi dvi-am dvi-recursive info info-am \
	info-recursive install install-am install-binPROGRAMS \
	install-data install-data-am install-data-recursive \
	install-exec install-exec-am install-exec-recursive \
	install-info install-info-am install-info-recursive install-man \
	install-man6 install-pkgdataDATA install-recursive \
	install-strip installcheck installcheck-am installdirs \
	installdirs-am installdirs-recursive maintainer-clean \
	maintainer-clean-generic maintainer-clean-recursive mostlyclean \
	mostlyclean-compile mostlyclean-generic mostlyclean-recursive \
	tags tags-recursive uninstall uninstall-am \
	uninstall-binPROGRAMS uninstall-info-am \
	uninstall-info-recursive uninstall-man uninstall-man6 \
	uninstall-pkgdataDATA uninstall-recursive


install_exec_local:
	-(chgrp games $(DESTDIR)$(bindir)/toppler; chmod g+s $(DESTDIR)$(bindir)/toppler)
	$(INSTALL) -d -g games -m 664 $(DESTDIR)$(scoredir)
	touch $(DESTDIR)$(scorefile)
	-(chgrp games $(DESTDIR)$(scorefile); chmod g+rw $(DESTDIR)$(scorefile))
	-(chgrp games $(DESTDIR)$(scoredir); chmod g+rw $(DESTDIR)$(scoredir))

uninstall_local:
	rm $(scoredir)/toppler.hsc
	rmdir $(scoredir)
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
