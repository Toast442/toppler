AM_CXXFLAGS = -Wall -DTOP_DATADIR=\"$(pkgdatadir)\" -DHISCOREDIR=\"$(pkglocalstatedir)\" -DLOCALEDIR=\"$(localedir)\"
SUBDIRS = po m4
ACLOCAL_AMFLAGS = -I m4

PACKAGE = toppler

bin_PROGRAMS = toppler

toppler_LDFLAGS = $(LIBINTL)
toppler_SOURCES =                  \
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

docdir = $(datadir)/doc
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

install-exec-hook:
	-chgrp games $(DESTDIR)$(bindir)/toppler
	-chmod 2755 $(DESTDIR)$(bindir)/toppler

install-data-hook:
	-chgrp games $(DESTDIR)$(pkglocalstatedir)/$(PACKAGE).hsc
	-chmod 0664 $(DESTDIR)$(pkglocalstatedir)/$(PACKAGE).hsc

abs_builddir = @abs_builddir@
win32dir = $(PACKAGE)-$(VERSION)-win32

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
