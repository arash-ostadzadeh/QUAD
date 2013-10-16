#ifndef MJPEG_VIDEO_IN_H
#define MJPEG_VIDEO_IN_H

#include <stdio.h>
#include "mjpeg_func.h"

#define picsize (8*VNumBlocks)*(8*(2*HNumBlocks))

FILE *mropen(char *filename);
void mrclose(FILE *fh);
int  bgetc(FILE *fh);

//variables
static FILE *fh1 = NULL;
static FILE *fh2 = NULL;
static FILE *fh3 = NULL;

static int i = -1;
static int j = -1;
static int isFirst = 1;
static int numBlocksH = 2*HNumBlocks;
static int numBlocksV = VNumBlocks;

static int compY[picsize];
static int compU[picsize/2];
static int compV[picsize/2];

#endif
