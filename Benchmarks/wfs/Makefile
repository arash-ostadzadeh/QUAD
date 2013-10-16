##################################################
#
# make file for hArtes wfs benchmarking application
#
# @author gregor heinrich gregor :: arbylon.net
#
##################################################

CC	= gcc -D__LINUX__
CFLAGS = -Wall -g -pg
#CFLAGS	= -O3
#-g means the debug info available - remove -pg if not intending to use gprof
SRCS	= audioio.c config.c delayline.c filter.c waveIO.c wfsAudioRun.c main.c \
	  mymath.c waveprop.c
OBJS	= $(SRCS:.c=.o)
HEADERS	= *.h
#HEADERS	= $(SRCS:.c=.h)
LDFLAGS	= -lm
VERSION	= 0.1
PKGNAME	= wfs1-benchapp-GCC-$(VERSION)
DISTDIR	= .
DISTFILES = $(SRCS) $(HEADERS) Makefile *.vcproj *.txt

all: depend wfs

wfs: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
.c.o:
	$(CC) $(CFLAGS) -c $<

depend:
	@$(CC) -MM $(SRCS) > .depend
clean:
	@rm -f .depend $(OBJS)
pkg:
	@[ -d $(PKGNAME) ] || mkdir $(PKGNAME)
	@cp -p $(DISTFILES) $(PKGNAME)
	@tar cvfz $(DISTDIR)/$(PKGNAME).tar.gz $(PKGNAME)
	@rm -r $(PKGNAME)

-include .depend
