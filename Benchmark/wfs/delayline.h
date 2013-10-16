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
 * @copyright     Copyright (c) 2006/2007 by Gregor Heinrich and Fraunhofer IGD.<br>
 *                All rights reserved.<br>
 *                Fraunhofer IGD provides this product without warranty of
 *                any kind and shall not be liable for any damages caused by
 *                the use of this product.
 *
 * @filename      delayline.h
 *
 * @file          delayline.h
 *
 *                Multichannel delay line with integer delays.
 *
 */
#ifndef DELAYLINE_H
#define DELAYLINE_H

#include "mymath.h"

#ifndef __CYGWIN__
#include <omp.h>
#endif

// globally comment fft to track signal element positions through algorithm
//#define DEBUG

/** structure that collects data for updating the delay */
typedef struct {
    // new delay
    real d; 
    real d2; // in case of non-monotonic doppler-effect   
    // new gain
    real a;
    real a2; // in case of non-monotonic doppler-effect  
    // transition steps
    int steps;
    // second set of transition steps, 
    // in case of a source passing by the speaker and 
    // thus inducing a doppler-effect
    int steps2; // in case of non-monotonic doppler-effect

    // time in [samples], the update takes
    int timeOfUpdate1;
    // time in [samples], the update takes; non-monotonic
    int timeOfUpdate2;

    // flag for non-monotonic doppler-shift
    int nonMon;

	// flag for chunk-based update
	int chunkBasedUpdate;

    // transition step
    int step;
	// activation flag
	int active;
	// differential delay
	real diffd;
    real diffd2; // in case of non-monotonic doppler-effect 
	// flag for the Doppler-effect
    int dropSample;
    // Chunksize
    int chunkSize;
    int chunkSize2; // in case of non-monotonic doppler-effect 
    // nrFrameWrap
    int nrFrameWrap;

	// actual delay (can be a real number)
    //real dfloat;
} DelayUpdate;

//% implements a MIMO delay line based on time-domain buffering. Although
//% very efficient from a computational point of view, for high quality audio
//% processing, this might not have enough spatial resolution, as at a
//% sampling frequency of 48kHz, one sample corresponds to about 7mm
//% displacement. The implementation is based on a set of P=size(xx,2) ring
//% buffers that are tapped to create Q=size(yy,2) output signals.
/**
 * summons information needed to Filter the signal.
 */
typedef struct {
    // TODO: put in and out bufs here
    real **xxframe, **yyframe;
	//% number of input signals
    int P;
    //% number of output signals (cimpl)
    int Q;
    //% pointer for all inputs
    int pin;
    //% amplification factors
    real** aa;
    //% maximum delay
    int dmax;
    //% ring buffers
    real** rr;
    //% update data
    DelayUpdate** updater;
    //% for finishing the delay
    int finishing;
    //% status
    int more;
    //% matrix of pointers for every output:
    //% since the output comes "after" the input, zero delay becomes 1, delay
    //% higher than zero counts down from dmax
    int** ppout;
	//  Delay matrix (P x Q)
	real **dd;
	// Updates Active at the moment
	int updatesActive;
    // sampling frequency
    int samplingFreq;
    // frameLength
    int frameLength;

    // matrix of number of output samples wrapped
    // needed if the chunk-block overlaps the output buffer
	int** outputSamplesWrapped;

} DelayLine;

/**
 * create a delay structure with the necessary coefficients
 *
 * @param xx pointer to the array where the input samples exist (each channel
 * one sample in a row
 * @param yy pointer to the array where the output samples exist
 * @param aa gains (matrix of gain factors, col = input, row = output index)
 * @param dd delays (matrix of integer delays, col = input, row = output index)
 * @param dmax maximum delay (= ring buffer size)
 * @return delay line struct
 *
 */
//TODO: add input and output buffers (see Filter_init)
//DelayLine* DelayLine_init(real **xx, real **yy, int frameLength, real** aa, real** dd, int dmax, int P, int Q);
DelayLine* DelayLine_init(real** aa, real** dd, int dmax, int P, int Q, int samplingFreq, int frameLength);

/**
 * free the delay structure (placeholder for cimpl)
 * @param delay -- delay line to be freed
 */
void DelayLine_free(DelayLine* dl);

/**
 * cyclical increment of n with cycle (in matlab, nmax = cycle + 1)
 *
 * @param n -- integer number
 * @param cycle -- largest allowed integer (wrap to n=0)
 */
void cycinc(int** indices, int cycle, int P, int Q);

/**
 * perform one time step with the input samples xxsamp and output the
 * resulting output samples
 * @param dl -- delay structure
 * @param xx -- input signal
 * @param inputIndex -- Index for the input signal
 * @param yysamp -- Q output samples
 * @return -- No return
 */

/**
 * perform a block of time steps corresponding to a frame (of arbitrary
 * length and return the respective audio output. If the filter is
 * finishing and runs to the end of the buffer, the function returns less
 * samples and zero-pads.
 * @param dl -- delay structure
 * @param frameLength -- number of samples to be returned
 * @return number of samples to read out (when finishing)
 */

/**
 * perform the update of the delay and gain matrix
 * @param dl -- delay structure to be updated
 */
void DelayLine_updateStep(DelayLine* dl);

/**
 * delay = updatedelay(delay, p, q, d, a, steps):
 *
 * @param dl -- delay structure to be updated
 * @param p -- input channel to be updated
 * @param q -- output channel to be updated
 * @param a -- new gain factor
 * @param d -- new delay
 * @param diffd -- differential delay (speed) to update to the new delay
 */
void DelayLine_update(DelayLine* dl, int p, int q, real a1, real a2, real d1, real d2, real diffd1, real diffd2, real chunkCarry); 


/**
 * delay = finishdelay(delay):
 *
 * @param dl -- delay structure to be updated
 */
void DelayLine_finish(DelayLine* dl);

/**
 * delay = process_frame(delay):
 *
 * @param dl -- delay structure
 * @param frameLength -- size of the frame
 * @param xxframe -- input frame (one for each channel)
 * @param yyframe -- output frame (one for each channel)
 * @return number of samples to read out (when finishing)
 */
int DelayLine_processFrame(DelayLine *dl);

/**
 * delay = process_sample(delay):
 *
 * @param dl -- delay structure
 * @param frameLength -- size of the frame
 * @param xxsamp-- input sample (one for each channel)
 * @param yysamp -- output (one for each channel)
 * @return number of samples to read out (when finishing)
 */
int DelayLine_processSample(DelayLine *dl, real *xxsamp, real *yysamp); //TODO: to be substituted by chunk

int DelayLine_processChunk(DelayLine *dl);

//int DelayLine_updateChunk(DelayLine *dl, int p, int q);

int DelayLine_updateChunk(DelayLine *dl, DelayUpdate *updaterIn, real *dd, real *aa, int p, int q);

#endif // DELAYLINE_H
