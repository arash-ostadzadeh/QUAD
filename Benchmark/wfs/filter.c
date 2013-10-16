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
 * @filename    rtols.c
 *
 * @file        rtols.c
 *
 *              Time-partitioned overlap-save algorithm with framewise access
 *              intended for realtime operation.
 *
 */
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "filter.h"
#include "mymath.h"

#define STATUS_OK if (stat != NULL) stat->numeric = RTOLS_NO_ERROR;

//statistics
// this flag must be equal in ALL source-files!!!
//#define STATS

#ifdef RTOLS_CONV_TIMEDOM
// disable ffts for time-domain operation
#define fft //fft
#define ifft //ifft
#endif

// openMP
// #define USE_OMP

// TODO: implement zero-frames handling, group delay and fractional delays

/*****************************************************************************/

// create basic Filter structure
Filter* Filter_create_(real* h, int hlen, int m) {
    Filter *filt;

    filt = (Filter*) malloc(sizeof(Filter));
    
    // L = 2^m
    filt->L = 1 << m;
    filt->K = filt->L / 2;
    filt->hlen = hlen;
    //filt->R = (int) ceil(hlen/(double)filt->K);
	filt->R = (int) ceil(hlen/(real)filt->K);
    filt->finishing = 0;
    filt->i = 0;
    filt->updater = NULL;
    filt->XX = NULL;
    filt->Y = NULL;
    filt->Ysh = NULL;
    filt->xsave = NULL;
    
    // status report
    return filt;
} // Filter_create_

/*****************************************************************************/

Filter* Filter_init(real* x, real* y, real* h, int hlen, FftPlan* ww) {
    Filter* filt;

    filt = Filter_init_shared(x, y, h, hlen, RTOLS_SHARED_NONE, ww);

    return filt;
} // Filter_init

/*****************************************************************************/

Filter* Filter_init_shared(real* x, real* y, real* h, int hlen, 
                           int sharemode, FftPlan* ww) {
    Filter* filt;
    
    filt = Filter_create_(h, hlen, ww->m);

    filt->xframe = x;
    filt->yframe = y;
    filt->ww = ww;
    filt->predelay = 0;
    filt->sharemode = sharemode;
    filt->muted = 0;
    // don't use output mutex if not that of a group
    filt->outputmutex = NULL;
    filt->updatemutex = NULL;

    // only unshared and main filters initialise local fields
    if (!(sharemode & RTOLS_SHARED_INPUT)) {
        // calloc for implicit zero-padding
        filt->XX = callocCplxArr(filt->R, filt->L);
        filt->xsave = (complex*) calloc(filt->L, sizeof(complex));
    }
    if (!(sharemode & RTOLS_SHARED_IR)) {
        // calloc for implicit zero-padding
        filt->HH = callocCplxArr(filt->R, filt->L);
        Filter_segmentir(h, hlen, filt->HH, filt->R, ww);
        //filt->updatemutex = CreateMutex(NULL, FALSE, NULL);
    }
    if (sharemode & RTOLS_SHARED_OUTPUT_MAIN) {
        // calloc for implicit zero-padding
        filt->Ysh = (complex*) calloc(filt->L, sizeof(complex));
        //filt->outputmutex = CreateMutex(NULL, FALSE, NULL);
    }
    // calloc for implicit zero-padding
    filt->Y = (complex*) calloc(filt->L, sizeof(complex));
        
    
    #ifdef RTOLS_CONV_TIMEDOM
    filt->xhconv = (complex*) calloc(filt->L * 2, sizeof(complex));
    #endif

    return filt;
} // Filter_init_shared

/*****************************************************************************/

void Filter_connect_shared(Filter* filt, Filter* main, 
                           int sharemode) {
    
    // check if filter and main filter have correct share modes
    if (((sharemode & filt->sharemode) == 0) 
        || ((sharemode & (main->sharemode * 2)) == 0)) {
        return;
    }
    if (sharemode & RTOLS_SHARED_INPUT) {
        filt->XX = main->XX;
        filt->xsave = main->xsave;
    } else if (sharemode & RTOLS_SHARED_OUTPUT) {
        filt->Ysh = main->Ysh;
        filt->outputmutex = main->outputmutex;
    } else if (sharemode & RTOLS_SHARED_IR) {
        filt->HH = main->HH;
        filt->updatemutex = main->updatemutex;
        filt->updater = main->updater;
    }

} // Filter_connect_shared

/*****************************************************************************/

int Filter_free(Filter* filt) {

    if (!(filt->sharemode & RTOLS_SHARED_INPUT)) {
        freeCplxArr(filt->XX, filt->R);
        free(filt->xsave);
    }
    if (!(filt->sharemode & RTOLS_SHARED_IR)) {
        freeCplxArr(filt->HH, filt->R);
        //CloseHandle(filt->updatemutex);
    }
    if (!(filt->sharemode & RTOLS_SHARED_OUTPUT)) {
        free(filt->Ysh);
        //CloseHandle(filt->outputmutex);
    }
    free(filt->Y);
            
    if (filt->updater != NULL) {
        FilterUpdate_free(filt->updater);
    }
    
    #ifdef RTOLS_CONV_TIMEDOM
    free(filt->xhconv);
    #endif

    free(filt);
    return 0;
} // Filter_free

/*****************************************************************************/

void Filter_segmentir(real* h, int hlen, complex** HH, int R, FftPlan* ww) {
    int K, r;

    // (this method does not use the filter structure because it is used
    // for the updater structure as well)

    K = 1 << (ww->m-1);
    //R = (int) ceil(hlen/(double)K);
	R = (int) ceil(hlen/(real)K);

    // @hartes-toolchain: collect frames in HH (must be synchronised
#ifdef USE_OMP
#pragma omp parallel for
#endif
    for (r = 0; r < R; r++) {

        // if this is a complete frame
        if (hlen >= (r + 1) * K) {
            // only first IR half frame is nonzero in time domain
            r2c(h + K * r, HH[r], K);
        } else {
            // implicit zero padding due to calloc / zeroing
            r2c(h + K * r, HH[r], hlen - r * K);
        }
        // @hartes-library: in-place transform
        fft(HH[r], ww->wfwd, ww->m);
                
    } // for r
// barrier parallel for r

} // Filter_segmentir

/*****************************************************************************/

// prepare input
void Filter_process_pre_(Filter* filt) {
    int icirc;

    // regular preprocess frame if shared or unmuted filter
    if (!filt->muted || (filt->sharemode & RTOLS_SHARED_INPUT_ANY)) {

        // circular index for input frames and spectra
		icirc = filt->i % filt->R;

		// at signal start, XX frames are zero by initialisation, therefore no special case
		// for starting signals, but zero multiplications.

        // determine the range of frame spectra XX to be processed.
        if (filt->finishing == 0) {
        
            // create signal spectrum with saved last frame
			// first half of the signal comes from the saved frame
			memcpy(filt->XX[icirc], filt->xsave, filt->K * sizeof(complex));

            // convert real input to complex vector and save for next frame,
            // (with r2c fft this is not necessary and real xsave can be used, that's
			// why we keep this somewhat memory-inefficient approach)
			r2c(filt->xframe, filt->xsave, filt->K);
			
			// second half is current frame (we use xsave because it is converted)
			memcpy(filt->XX[icirc] + filt->K, filt->xsave, filt->K * sizeof(complex));
			
            // fft assembled input frame
            // @hartes-library: in-place transform
			fft(filt->XX[icirc], filt->ww->wfwd, filt->ww->m);
			
        } else if (filt->finishing == 1) {
            // first frame after finishing the input signal:
            // still a saved previous frame, but no new samples
            
            // create signal spectrum with saved last frame, new input frame set to zero
            memcpy(filt->XX[icirc], filt->xsave, filt->K * sizeof(complex));
            // zero out second half of input frame
            zeroCplxVec(filt->XX[icirc] + filt->K, filt->K);
            // fft assembled input frame
            // @hartes-library: in-place transform
			fft(filt->XX[icirc], filt->ww->wfwd, filt->ww->m);
			
        } else if (filt->finishing <= filt->R + 1) {
            // no input and no saved previous frame
            // zero input frame
            zeroCplxVec(filt->XX[icirc], filt->L);
            // no fft necessary   
        } else {
            // input and output already zero
        } // if finishing
    } else {
    
        // save this for next frame (might be unmuted later)
		r2c(filt->xframe, filt->xsave, filt->K);
		
    } // if !muted
    
    #ifdef RTOLS_DEBUGOUT_FILTER
	printf("XX:\n");
	for (r = 0; r < filt->R; r++) {
	    int j;
		printf("%i:%s\t", r, r == icirc ? ">": " ");
		for (j = 0; j < filt->K * 2; j++) {
			printf("%i ", (int) filt->XX[r][j].re);
			if (j == filt->K - 1) {
			    printf("| ");
			}
		}
		printf("\n");
	}
	#endif

} // Filter_process_pre_

/*****************************************************************************/

// prepare output
void Filter_process_post_(Filter* filt) {
    complex* Yf;

    // regular postprocessing if unmuted or shared
    if (!filt->muted || (filt->sharemode & RTOLS_SHARED_OUTPUT_MAIN)) {
    
        // use appropriate buffer (either shared or local)
        Yf = (filt->sharemode & RTOLS_SHARED_OUTPUT_MAIN) ? filt->Ysh : filt->Y;
    
        // transform back accumulated spectrum
        // @hartes-library: in-place transform
		ifft(Yf, filt->ww->winv, filt->ww->m);
        // select last L-K points (starting at K)
        // @hartes-library: a c2r ifft outputs real already
		c2r(Yf + filt->K, filt->yframe, filt->K, 0);
		
    } else {
        // zero output
        zeroRealVec(filt->yframe, filt->K);
    }
} // Filter_process_post_

/*****************************************************************************/

int Filter_process(Filter* filt) {
    // index variables
    int r, rcirc, j;

    // strategy (arrays are specified with sizes in brackets):
    //
    // - previous frame needs to be recovered from the complex buffer xsave[K]
    // - previous and current frame are copied into complex buffer XX[R][L], using
    //   a circular indexing scheme with icirc as base index
    // - XX[r] is transformed using an in-place FFT
    // - R multiplications are performed over the different parts HH[R][L], for
    //   which again the circular indexing of XX is used, the result adds to Y[L].
    // - Y is transformed back into time domain
    // - in shared filters, the buffer Y is not overwritten but can be added to, and
    //   the accumulated contributions of several signals are transformed back using
    //   an in-place IFFT
    // - The second half of the resulting time-domain representation of Y is copied
    //   to the output buffer
    //
    //   Note that with half-complex r2hc fft as in fftw, it is possible to use
    //   arrays Y, XX, HH of L x real instead of L x complex elements that require
    //   half as much memory.
    //
    //   When signal sharing is used, copying and transformation actions are
    //   "outsourced" to the caller function to allow synchronisation across processors.


    // shared input is handled in FilterGroup_process() to allow synchronisation of parallel loop
    if (!(filt->sharemode & RTOLS_SHARED_INPUT_ANY)) {
        // assemble and transform (unshared) frame
        Filter_process_pre_(filt);
    } // if !shared input
    
    // handle filter update step (which is ignored for shared IRs)
    Filter_update_step_(filt);

    // set output spectrum to zero
    // (don't touch shared output).
    if (!(filt->sharemode & RTOLS_SHARED_OUTPUT_ANY)) {
        // zero output buffer
        zeroCplxVec(filt->Y, filt->L);
    }

    if (!filt->muted) {
    
        // perform processing over R current and previous signal / IR parts
        // @hartes-toolchain: access to buffer Y must be synchronised
#ifdef USE_OMP
#pragma omp parallel for
#endif
        for (r = 0; r < filt->R; r++) {

            // TODO: full-frameLength predelay can be handled here
            
            // zero-based circular indexing into XX
			// caution with mod of neg. numbers in C vs. matlab: 
			// C: -5 % 3 = -(5 % 3) = -2 (3), matlab: = 1 (-6)
            rcirc = (filt->i - r + filt->R) % filt->R;
#ifdef STATS
	flops.adds += 2;	
#endif

            // do time-domain partial convolution
            #ifdef RTOLS_CONV_TIMEDOM
                // actually only the second half of xhconv is needed for overlap save
                // we use full xhconv for simpler (debug) code
                tconv(filt->XX[rcirc], filt->L, filt->HH[r], filt->K, filt->xhconv);
            #endif
                        
            // calculate partial convolutions
            for(j = 0; j < filt->L; j++) {
                
                // multiply spectra and add to Y
                #ifdef RTOLS_CONV_TIMEDOM
                    filt->Y[j] = cadd(filt->Y[j], filt->xhconv[j]);
                #else
                    // @hartes-library: use SIMD
                    filt->Y[j] = cadd(filt->Y[j], cmult(filt->XX[rcirc][j], filt->HH[r][j]));
                #endif
                                
            } // for j
            
            #ifdef RTOLS_DEBUGOUT_FILTER
            //********test-print-out begin -->
			//printf("convolve XX[%i] ** HH[%i]\n", rcirc, r);
			//printCplxVec(filt->XX[rcirc], filt->L);
			//printCplxVec(filt->HH[r], filt->L);
			//printf("filt->Y\n");
			//printCplxVec(filt->Y, filt->L);
            //********test-print-out end <--
			#endif

        } // for r
// barrier parallel for r


        // @hartes-toolchain: writing parallel to Ysh must be synchronised between all filters
        // that share the output channel buffer Ysh. (Explicit mutex only needed for standard threading, as 
        // OpenMP should use a lock for access to Ysh if nested parallel loops are supported.)
        if (filt->outputmutex != NULL) {
// enter synchronised section
//WaitForSingleObject(filt->outputmutex, INFINITE);
            // @hartes-library: SIMD 
            for (j = 0; j < filt->L; j++) {
                filt->Ysh[j] = cadd(filt->Ysh[j], filt->Y[j]);
            }
// leave synchronised section
//ReleaseMutex(filt->outputmutex);
        }


    } // if !muted

    // ifft of shared output is handled in FilterGroup_process() to allow a barrier
    if (!(filt->sharemode & (RTOLS_SHARED_OUTPUT_ANY))) {
        Filter_process_post_(filt);
    }

    filt->i ++;

    if (filt->finishing) {
        filt->tail = filt->tail - filt->K;
        filt->finishing = filt->finishing + 1;
        if (filt->tail <= 0) {
            return 0;
        }
    }
    return 1;
} // Filter_process

/*****************************************************************************/

void Filter_update(Filter* filt, real* h, int hlen, int steps, int framewise, int keep) {
    int r, i;
    real invsteps;

    // allocate memory
    if (filt->updater == NULL) {
		// create filter updater
		filt->updater = FilterUpdate_init(filt->R, filt->L);
	} else {
	    // zero HHnew (required by segment_ir)
	    for (r = 0; r < filt->R; r++) {
	        zeroCplxVec(filt->updater->HHnew[r], filt->L);
	    }
	}

// synchronised, so atomic read/write in Filter_update_step and read in 
// Filter_process
	
    // calculate new spectral coefficients with Filter_segmentir
    Filter_segmentir(h, hlen, filt->updater->HHnew, filt->R, filt->ww);
        
// enter synchronised section
//WaitForSingleObject(filt->updatemutex, INFINITE);

    // calculate differential spectrum
    invsteps = 1/(real) steps;
    for (r = 0; r < filt->R; r++) {
        for (i = 0; i < filt->L; i++) {        
            // hdiff = (hnew - hold) / steps
            filt->updater->HHdiff[r][i] = csmult(csub(filt->updater->HHnew[r][i], filt->HH[r][i]), invsteps);
        }
	}
    filt->updater->step = 1;
    filt->updater->steps = steps;
    filt->updater->framewise = framewise;
    filt->updater->keep = keep;
    
// leave synchronised section
//ReleaseMutex(filt->updatemutex);

} // Filter_update

/*****************************************************************************/

FilterUpdate* FilterUpdate_init(int R, int L) {
    FilterUpdate* up;
    
    // allocate memory
    up = (FilterUpdate*) malloc(sizeof(FilterUpdate));
    up->HHdiff = callocCplxArr(R, L);
    // (for framewise update updates, actually need up to R HHnew arrays
    // since effect of update should be propagated to r-th IR frame causally,
    // therefore update updates now not framewise)
    up->HHnew = callocCplxArr(R, L);
    // standard settings
    up->steps = 0;
    up->step = 1;
    up->keep = 0;
    up->R = R;
    return up;
    
} // FilterUpdate_init

/*****************************************************************************/

void FilterUpdate_free(FilterUpdate* up) {

    freeCplxArr(up->HHdiff, up->R);
    freeCplxArr(up->HHnew, up->R);
    up = NULL;
    
} // FilterUpdate_free

/*****************************************************************************/

int Filter_update_step_(Filter* filt) {
    int i, r;
    
    if (filt->updater == NULL || filt->updater->step <= 0) {
        return 0;
    }
    // if shared filters, only do update in main filter RTOLS_SHARED_IR_MAIN
    if (!(filt->sharemode & RTOLS_SHARED_IR)) {

// enter synchronised section
//WaitForSingleObject(filt->updatemutex, INFINITE);

        if (filt->updater->steps > 0) {

#ifdef USE_OMP
#pragma omp parallel for
#endif
            for (r = 0; r < filt->R; r++) {
                // exclude old (signal already in air): r>=step
                if (filt->updater->framewise && (r >= filt->updater->step - 1)) {
                    continue;
                }
                // exclude the finished updates: steps > r
                if (filt->updater->framewise && (filt->updater->step > r + filt->updater->steps + 1)) {
                    // Note: case step > r + steps could be used to memcpy target HH (updater->HHnew) to HH.
                    continue;
                }
                for (i = 0; i < filt->L; i++) {
                    // crossfade coefficients
                    // @hartes-library: SIMD operation here
                    filt->HH[r][i].re += filt->updater->HHdiff[r][i].re;
					filt->HH[r][i].im += filt->updater->HHdiff[r][i].im;
#ifdef STATS
	flops.adds += 2;	
#endif
                }
            } // for r
// barrier parallel for r

        } else if (filt->updater->framewise) {
            // framewise && steps = 0
            // no transition -> directly copy new coefficients for frame 
            r = filt->updater->step-1;
            memcpy(filt->HH[r], filt->updater->HHnew[r], filt->L * sizeof(complex));
        } else {
            // !framewise && steps = 0
            for (r = 0; r < filt->R; r++) {
                // no transition -> directly copy new coefficients.
                memcpy(filt->HH[r], filt->updater->HHnew[r], filt->L * sizeof(complex));
            }
        }
        
        filt->updater->step++;

// leave synchronised section
//ReleaseMutex(filt->updatemutex);

        // check if the update is completed
        if (filt->updater->step > filt->updater->steps + (filt->updater->framewise ? filt->R : 0)) {
            if (!filt->updater->keep) {
                free(filt->updater);
                filt->updater = NULL;
            } else {
                filt->updater->step = 0;
            }
            // update finished
            return 0;
        }      

    } // if !shared ir
    
    // more update steps
    return 1;
    
} // Filter_update_step

/*****************************************************************************/

void Filter_finish(Filter* filt) {
    filt->finishing = 1;
    filt->tail = filt->hlen - 1;
    #ifdef RTOLS_DEBUGOUT_FILTER
    printf("\n*** finishing filter, tail = %i\n", filt->tail);
    #endif

} // Filter_finish

/*****************************************************************************/

void Filter_restart(Filter* filt) {
    int r;

    filt->finishing = 0;
    filt->tail = 0;
    zeroCplxVec(filt->xsave, filt->K);
    for (r = 0; r < filt->R; r++) {
        zeroCplxVec(filt->XX[r], filt->L);
    }
} // Filter_restart

/*****************************************************************************/

FftPlan* FftPlan_init(int m) {
    int L;
    FftPlan* ww;

    L = 1 << m;
    ww = (FftPlan*) malloc(sizeof(FftPlan));
    ww->m = m;

    // make fft / ifft weights
    // @hartes-library: fft initialisation method
    ww->wfwd = (complex*) malloc(L * sizeof(complex));
    ww->winv = (complex*) malloc(L * sizeof(complex));
    ffw(ww->wfwd, 1, L);
    ffw(ww->winv, -1, L);
    return ww;
} // FftPlan_init

/*****************************************************************************/

void FftPlan_free(FftPlan* ww) {
    free(ww->wfwd);
    free(ww->winv);
    free(ww);
} // FftPlan_free

/*****************************************************************************/
