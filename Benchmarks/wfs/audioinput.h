/*
 *
 * "hArtes Reference/Benchmarking Application implementing a MIMO delay line (Delaytoy)"
 *
 */
/**
 * @author        Gregor Heinrich (Arbylon) for<br>
 *                Fraunhofer Institute for Computer Graphics Research IGD<br>
 *                Cognitive Computing & Medical Imaging (A7)<br>
 *                Fraunhoferstr. 5, 64283 Darmstadt, Germany.
 *
 * @copyright     Copyright (c) 1997 - 2007 by Fraunhofer IGD and Gregor Heinrich.<br>
 *                All rights reserved.<br>
 *                Fraunhofer IGD provides this product without warranty of
 *                any kind and shall not be liable for any damages caused by
 *                the use of this product.
 *
 * @filename      audioinput.h
 *
 * @file          audioinput.h
 *
 *                Input data required for the application.
 *
 *
 */
#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

//
// Audio Data include file. (generated from within MATLAB)

#include "mymath.h"

/**
 * sampling frequency (Hertz)
 */
// static const long samplingFrequency  = 48000;

/**
 * speed of sound (meters / second)
 */
//static const real speedSound = 340.0;

/**
 * samples per frame
 */
// static const int N = 8; 


/**
 * no. of input channels = no. of virtual sources
 */
// static const int P = 1; // obsolete

/**
 * no. of loudspeakers
 */
// static const int Q = 4; // obsolete

// determine the length of the input stream
// static const long long channelLength = 512;

//length = (channelLength + maxDelay) * Q
//#define OUTLEN (2048 + 20) * 4

/**
 * output data vectors, all frames channel1, all frames channel2, etc.
 */
//static real outputData[OUTLEN];



#endif // AUDIOINPUT_H
