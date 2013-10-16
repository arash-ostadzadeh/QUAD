/*
 *
 * "hArtes Reference/Benchmarking Application implementing matrix filtering (Tolstoy2)"
 *
 */
/**
 * @author	    Gregor Heinrich (Arbylon) for<br>
 *              Fraunhofer Institute for Computer Graphics Research IGD<br>
 *              Cognitive Computing & Medical Imaging (A7)<br>
 *              Fraunhoferstr. 5, 64283 Darmstadt, Germany.
 *
 * @copyright   Copyright (c) 2006/2007 by Gregor Heinrich and Fraunhofer IGD.<br>
 *              All rights reserved.<br>
 *              Fraunhofer IGD provides this product without warranty of
 *              any kind and shall not be liable for any damages caused by
 *              the use of this product.
 *
 * @filename    audioio.c
 *
 * @file        audioio.c
 *
 *              Provides framewise multichannel input from memory.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "audioio.h"

AudioIo* AudioIo_init(real** sigs, int nch, long channelLength, int frameLength) {
    AudioIo* io;
    io = (AudioIo*) malloc(sizeof(AudioIo));
    io->sigs = sigs;
    io->nch = nch;
    io->totalLength = channelLength ;
    io->chLength = channelLength;
    io->frameLength = frameLength;
    io->nsamples = 0;
    
    return io;
}

void AudioIo_free(AudioIo* io) {
    free(io);
}

int AudioIo_getFrame(AudioIo* io, real** frames) {
    int i;
    real* ptr;

    // copy interleaved signal parts to frame
    for (i = 0; i < io->nch; i++) {
        ptr = io->sigs[i] + io->nsamples ;
        memcpy(frames[i] , ptr, io->frameLength * sizeof(real));
        printRealVec(frames[i], io->frameLength);
    }
    // more samples to process?
    io->nsamples += io->frameLength;
    //if ((io->nframes + 1) * io->frameLength + (io->nch - 1) * io->chLength > io->totalLength) {
	if (io->nsamples >= io->totalLength) {
        return 0;
    } else {
        return 1;
    }
}

int AudioIo_setFrame(AudioIo* io, real** frames) {
    int i;
    real* ptr;

    // copy interleaved signal parts to frame
    for (i = 0; i < io->nch; i++) {
        ptr = io->sigs[i] + io->nsamples ;
        memcpy(ptr, frames[i] , io->frameLength * sizeof(real));
    }
    // more samples to process?
    io->nsamples += io->frameLength;    
    
	if (io->nsamples >= io->totalLength) {
        return 0;
    } else {
        return 1;
    }
}

int AudioIo_getFrames(AudioIo* io, real** frames) {
    int i;
    // long long offset;

    // copy interleaved signal parts to frame
    for (i = 0; i < io->nch; i++) {
        
        // offset = io->nsamples + i * io->chLength;
         memcpy(frames[i], io->sigs[i] + io->nsamples , io->frameLength * sizeof(real));

        //********* begin debug-test-print (works) -->
        // printf("frames loaded from AudioIO: \n");
        //for (j = 0; j < io->frameLength; j++) {
        // printf("frames[%i][%i]: %f \n",i,j, frames[i][j] );
        // printf("from: io->sigs[%i][%i]: %f \n",i,j, io->sigs[i][io->nsamples + j] );
        //}
        //*******end debug-test-print <--
     }

    // more samples to process?
    io->nsamples += io->frameLength;    
    
	if (io->nsamples >= io->totalLength) {
        return 0;
    } else {
        return 1;
    }
}

int AudioIo_setFrames(AudioIo* io, real** frames) {
    int i;
    real* ptr;

    // copy interleaved signal parts to frame
    for (i = 0; i < io->nch; i++) {
        ptr = io->sigs[i] + io->nsamples ;
        memcpy(ptr, frames[i], io->frameLength * sizeof(real));
     }
    // more samples to process?
    io->nsamples += io->frameLength;    
    
	if (io->nsamples >= io->totalLength) {
        return 0;
    } 
    else {
        return 1;
    }
}

int AudioIo_getSample(AudioIo* io, real* samples) {
    int i;
    real* ptr;

    // copy interleaved signal parts to frame
    for (i = 0; i < io->nch; i++) {
        ptr = io->sigs[i] + io->nsamples ;
		samples[i] = *ptr;
    }
    // more samples to process?
    io->nsamples++;
    
	if (io->nsamples >= io->totalLength) {
        return 0;
    } else {
        return 1;
    }
}
