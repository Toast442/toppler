OBJS=archi.o bonus.o configuration.o decl.o elevators.o game.o highscore.o keyb.o level.o leveledit.o main.o menu.o menusys.o points.o robots.o screen.o snowball.o sound.o soundsys.o sprites.o stars.o toppler.o txtsys.o
HOME=/Users/jasonk
FRAMEWORKS=$(HOME)/projects/root/Library/Frameworks/SDL_2.0
INCPATH=-I ./ -I $(FRAMEWORKS)/SDL2.framework/Headers -I $(FRAMEWORKS)/SDL2_image.framework/Headers -I $(FRAMEWORKS)/SDL2_mixer.framework/Headers
GCC=gcc
GPP=g++
CFLAGS=-g -isysroot /Applications/Xcode7.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk -DTOP_DATADIR=\".\" -DHISCOREDIR=\".\" -D__MACOSX__=1
LDFLAGS=-g -F $(FRAMEWORKS) -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework Cocoa -lz

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
