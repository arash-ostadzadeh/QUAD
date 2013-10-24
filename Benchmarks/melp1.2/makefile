#------------------------------------------------------------------------------
#
#   Commands:  
#      make OSTYPE=xxx  [opt]         Create optimized executable melp
#      make OSTYPE=xxx  debug         Create debugging executable melp
#      make clean         	      Remove existing object files

#------------------------------------------------------------------------------
#   Turn on dependency tracking (for include files).
#------------------------------------------------------------------------------
.KEEP_STATE:

#------------------------------------------------------------------------------
#   Specify names of source files and executable.
#------------------------------------------------------------------------------
OBJS 	 = melp.o melp_ana.o melp_syn.o melp_chn.o coeff.o\
fsvq_cb.o msvq_cb.o fec_code.o dsp_sub.o melp_sub.o\
mat_lib.o lpc_lib.o vq_lib.o fs_lib.o pit_lib.o

EXE     =       melp

#------------------------------------------------------------------------------
#   Specify options for compiling, linking, and archiving.  
#------------------------------------------------------------------------------
CC         = gcc 
CFLAGS     = -O3 -D$(OSTYPE) -Wall
LIBS	   = -lm
COMPILE.c  = $(CC) $(CFLAGS) -c
LINK.c     = $(CC) $(CFLAGS) 

#------------------------------------------------------------------------------
#   Specify conditional settings.
#------------------------------------------------------------------------------
debug 		:= CFLAGS = -g -D$(OSTYPE) -Wall

#------------------------------------------------------------------------------
#   Compile and link command.
#------------------------------------------------------------------------------
opt debug         :  $(OBJS)
	$(LINK.c) -o $(EXE) $(OBJS) $(LIBS)

#
# purify
#
purify          :  $(OBJS)
	purify $(LINK.c) -o $(EXE) $(OBJS) $(LIBS)

#------------------------------------------------------------------------------
#   Define clean (remove temporary files).
#------------------------------------------------------------------------------
clean:
	/bin/rm $(OBJS) 

#------------------------------------------------------------------------------
#   End of Makefile.
#------------------------------------------------------------------------------





