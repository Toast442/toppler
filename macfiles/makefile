OBJS=archi.o bonus.o configuration.o decl.o elevators.o game.o highscore.o keyb.o level.o leveledit.o main.o menu.o menusys.o points.o robots.o screen.o snowball.o sound.o soundsys.o sprites.o stars.o toppler.o txtsys.o
XCODE=$(shell xcode-select -p)
SDK=$(XCODE)/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.13.sdk 
FRAMEWORKS=$(HOME)/projects/root/Library/Frameworks/SDL_2.0
INCPATH=-I ./ -F $(FRAMEWORKS)
GCC=$(shell xcodebuild -find-executable gcc)
GPP=$(shell xcodebuild -find-executable g++)
CFLAGS=-g -DTOP_DATADIR=\".\" -DHISCOREDIR=\".\" -D__MACOSX__=1 -mmacosx-version-min=10.9
LDFLAGS=-g -F $(FRAMEWORKS) -framework SDL2 -framework SDL2_mixer -framework Cocoa -lz

all: toppler

bundle: toppler
	./macfiles/make-bundle.sh

toppler: $(OBJS)
	$(GPP) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

.cc.o:
	$(GPP) $(CFLAGS) $(INCPATH) -c $<

.c.o:
	$(GCC) $(CFLAGS) $(INCPATH) -c $<

.m.o:
	$(GCC) $(CFLAGS) $(INCPATH) -c $<

clean:
	rm -f *.o toppler
	rm -rf Toppler.app
