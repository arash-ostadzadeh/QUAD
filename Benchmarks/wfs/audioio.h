/*
 *
 * "hArtes Reference/Benchmarking Application implementing matrix filtering (Tolstoy2)"
 *
 */
/**
 * @author      Gregor Heinrich (Arbylon) for<br>
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
 * @filename    audioio.h
 *
 * @file        audioio.h
 *
 *              Provides framewise multichannel input from memory.
 */


#ifndef AUDIOIO_H
#define AUDIOIO_H

#include "mymath.h"

/** 
 * @deplib: in hArtes, audio i/o should be done by the hardware, with audio i/o library functions
 * that performs a similar operation as the functions here.
 */

typedef struct {
    /** root of input/output signal channels (all of ch1, all of ch2, etc. */
    real** sigs;
    /** number of channels */
    int nch;
    /** total length of available signals */
    long totalLength;
    /** total length of one channel */
    long chLength;
    /** length of one frame */
    int frameLength;
    /** number of samples processed */
    long long nsamples;
    
} AudioIo;

/**
 * create an audio input/output structure that allows to extract all channels for one frame after
 * the other from the audio input/output that has all signals in a row.
 *
 * @param sigs signal vector with interleaved channels
 * @param nch number of channels
 * @param channelLength length of each channel
 * @param frameLength length of one frame (per channel)
 */
AudioIo* AudioIo_init(real** sigs, int nch, long channelLength, int frameLength);

/** free local buffers */
void AudioIo_free(AudioIo* io);

/**
 * get one frame of the input
 * @param in audio input/output struct
 * @param frame current frame (ch1, ch2, ch3 ...)
 * @return 1 = more frames to process, 0 = finished (incomplete frames ignored)
 */
int AudioIo_getFrame(AudioIo* io, real** frames);

/**
 * set one frame of the output
 * @param in audio input/output struct
 * @param frame current frame (ch1, ch2, ch3 ...)
 * @return 1 = more frames to process, 0 = finished (incomplete frames ignored)
 */
int AudioIo_setFrame(AudioIo* io, real** frames);

/**
 * get one frame of the input
 * @param in audio input/output struct
 * @param frames array of current frame channels
 * @return 1 = more frames to process, 0 = finished (incomplete frames ignored)
 */
int AudioIo_getFrames(AudioIo* io, real** frames);

/**
 * set one frame of the output
 * @param in audio input/output struct
 * @param frames array current frame channels
 * @return 1 = more frames to process, 0 = finished (incomplete frames ignored)
 */
int AudioIo_setFrames(AudioIo* io, real** frames);

/**
 * get one sample of the input
 * @param in audio input/output struct
 * @param samp array of samples of each channel
 * @return 1 = more frames to process, 0 = finished (incomplete frames ignored)
 */
int AudioIo_getSample(AudioIo* io, real* samples);

#endif // AUDIOIO_H
