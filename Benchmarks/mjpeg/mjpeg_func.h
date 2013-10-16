#ifndef MJPEG_FUNC_H
#define MJPEG_FUNC_H

#include "types.h"

#define NumFrames  8
#define VNumBlocks  60
#define HNumBlocks  40

void initVideoIn(THeaderInfo *HeaderInfo);
void mainVideoIn(TBlocks *out);

void mainDCT(const TBlocks *input, TBlocks *output);
void intArith(const TBlocks *input, TBlocks *output);

void mainQ(const TBlocks *input, TBlocks *output);

void mainVLE(const TBlocks *blocks, TPackets *stream);

void mainVideoOut(const THeaderInfo *HeaderInfo, const TPackets *stream);

#endif
