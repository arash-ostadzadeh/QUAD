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
 * @filename    filter.h
 *
 * @file        filter.h
 *
 *              Time-partitioned overlap-save algorithm with framewise access
 *              intended for realtime operation.
 *
 */
#ifndef FILTER_H
#define FILTER_H

#include "mymath.h"
#ifndef __CYGWIN__
#include <omp.h>
#endif


#define HANDLE void*

///////////////// debug constants ////////////////////////

// enable debug output for filter operation
//#define RTOLS_DEBUGOUT_FILTER

// allow time-domain operation to track indices
//#define RTOLS_CONV_TIMEDOM

//////////////////////////////////////////////////////////

#ifdef RTOLS_DEBUGOUT_MATRIX
// suppress warnings for pointer address printing (VC2005)
#pragma warning(disable:4313)
#endif

/**
 * represents the fft (size defined as 2^m)
 */
// @hartes-library: this in place of the fftplan (as in fftw) etc.
typedef struct _FftPlan {
    /** weights of forward fft */
    complex *wfwd;
    /** weights of inverse fft */
    complex *winv;
    /** log order for radix-2 fft */
    int m;
} FftPlan;

/** structure that collects data for updating filter coefficients */
typedef struct _FilterUpdate {
    /** steps to update, 1 for instant update*/
    // TODO:
    //=> has to match the time span needed for an updated source to reach it's new destination,
    // counted in frames
    int steps;
    /** current step, 0 for inactive updater */
    int step;
    /** keep after finish */
    int keep;
    /** do update frame by frame, i.e., old signals are not affected
     * any more by the update.
     */
    int framewise;
    /** differential spectrum */
    complex** HHdiff;
    /** new spectrum */
    complex** HHnew;
    /** number of frames */
    int R;
} FilterUpdate;

/**
 * summons information needed to Filter the signal.
 */
typedef struct _Filter {
    /** input and output buffers (externally allocated) */
    real *xframe, *yframe;
    /** saved previous input frame, size L */
    complex* xsave;
    /** length of buffers */
    int buflen;
    /** IR frame spectra (shared when irshare is used) */
    complex **HH;
    /** input frame spectra (shared when inshare is used) */
    complex **XX;
    /** frame-wise spectral product buffer */
    complex *Y;
    /** shared frame-wise spectral product buffer (shared when outshare is used) */
    complex *Ysh;
    /** sharing mode (bitmasks: RTOLS_SHARED_*) */
    int sharemode;
    /** frame count */
    unsigned long i;
    /** frame samples sizes (L = 2K, S = K) */
    int K, L, R, hlen;
    /** number of trailing frames that are zero */
    int predelay;
    /** whether the filter output is muted, i.e., yields zeros */
    int muted;
    /** finishing status (no further input) */
    int finishing;
    /** number of samples expected in the output (when finishing) */
    int tail;
    /** fft stuff */
    FftPlan* ww;
    /** to update filter coefficients */
    FilterUpdate* updater;
    /** synchronisation between filter updates and audio processing*/
    HANDLE updatemutex;
    /** synchronisation between shared outputs (or unnecessary) */
    HANDLE outputmutex;
    #ifdef RTOLS_CONV_TIMEDOM
    /** use time-domain partial convolution */
    complex* xhconv;
    #endif
    #ifdef RTOLS_DEBUGOUT_MATRIX
    /** track filter in matrix */
    int p, q;
    #endif
} Filter;

/**
 * defines the last error (singlethreaded only)
 */
typedef struct _status {
    /** status error number */
    int numeric;
    /** error message (optional for debugging) */
    char message[128];
} status;

// some error codes
#define RTOLS_NO_ERROR 0
#define RTOLS_ERROR_GENERAL -1
#define RTOLS_ERROR_RESTART_FAILED -2
#define RTOLS_ERROR_SHARE_MODE -4
#define RTOLS_ERROR_SHARE_BUFFERS -8

// share modes
// unshared
#define RTOLS_SHARED_NONE 0
// shared input, perform group's frame fft (first filter in group)
#define RTOLS_SHARED_INPUT_MAIN 1
// shared input except first filter
#define RTOLS_SHARED_INPUT 2
// shared input, any filter
#define RTOLS_SHARED_INPUT_ANY 3
// output shared, replacing Y (first filter in group)
#define RTOLS_SHARED_OUTPUT_MAIN 4
// output shared, added to Y
#define RTOLS_SHARED_OUTPUT 8
// output shared, any filter
#define RTOLS_SHARED_OUTPUT_ANY 12
// shared filter impulse response (first filter in group)
#define RTOLS_SHARED_IR_MAIN 16
// shared filter impulse response
#define RTOLS_SHARED_IR 32
// shared filter impulse response, any filter
#define RTOLS_SHARED_IR_ANY 48

// debug of input/output shares:   1    2    3     4    5     6     7      8
static char* sharemodes[] = {"0", "X", "x", "Xx", "Y", "XY", "xY", "XxY", "y", 
//                           9     10    11     12    13     14     15
                            "Xy", "xy", "Xxy", "Yy", "XYy", "xYy", "XxYy" };

/**
 * time-partitioned OLS convolution.
 *
 * Prepares the filtering by allocating internal memory of a Filter.
 *
 * @param inbuf real input buffer where frames are read from (size 2^(m-1) = fftsize/2 expected). After calling
 *        Filter_finish and the returned number of frames, inbuf is ignored (as there is no signal left).
 * @param outbuf real output buffer where the result are written to (size 2^(m-1) expected). If not the full
 *        buffer is filled with signal, it is zero-padded.
 * @param h impulse response (time domain!)
 * @param hlen length of h
 * @param ww FFT plan
 * @param stat status reporting structure (ignored if 0)
 */
Filter* Filter_init(real* x, real* y,
                    real* h, int hlen,
                    FftPlan* ww);

/**
 * time-partitioned OLS convolution with shared resources. This way, it is possible to
 * drastically reduce the number of ffts. There are three possibilities for sharing,
 * (1) input, i.e., XX is shared, (2) impulse response, i.e., HH is shared, and (3)
 * output, i.e., Y is shared. These methods can be combined. In a group of shared filters,
 * there must be exactly one filter that is the main filter in the sharing relation. For
 * filter groups shared in several ways, for each sharing there must be a main filter. In
 * these main filters, the shared resources are allocated. In loops, these main filters need
 * to be called first. It is up to the caller method to connect shared buffers:
 * 
 * <ul>
 * <li>Input sharing: XX and xsave of the input main filter must be assigned to each filter in
 *     an input group; inbuf must be identical when calling Filter_init_shared.
 * <li>Output sharing: Y and outputmutex of the output main filter must be assigned to each
 *     filter in an output group; outbuf must be identical when calling Filter_init_shared.
 * <li>Impulse response sharing: HH and updatemutex of the IR main filter must be assigned to 
 *     each filter in an IR group; h is ignored for shared IR filters except for the main filter.
 * </ul>
 *
 * For convenience, the method Filter_connect_shared can be used with the main filter of the group
 * as the argument.
 *
 * @param inbuf real input buffer where frames are read from (size 2^(m-1) = fftsize/2 expected). After calling
 *        Filter_finish and the returned number of frames, inbuf is ignored (as there is no signal left). In shared
 *        input filters, the input buffer is ignored and that of the main filter used.
 * @param outbuf real output buffer where the result are written to (size 2^(m-1) expected). If not the full
 *        buffer is filled with signal, it is zero-padded. In shared
 *        output filters, the output buffer is ignored and that of the main filter used.
 * @param h impulse response (time domain!)
 * @param hlen length of h
 * @param sharemode controls what parts of the filter are shared, input, IR and/or output, use RTOLS_SHARED_* flags.
 * @param ww FFT plan
 * @param stat status reporting structure (ignored if 0)
 */
Filter* Filter_init_shared(real* x, real* y,
                           real* h, int hlen, int sharemode,
                           FftPlan* ww);
                           
/**
 * Set the fields of the main filter in this filter, according to its share mode.
 *
 * @param main main filter for the share
 * @param sharemode share mode of this filter (if several share modes are enabled, this chooses the 
 * appropriate one for the filter, otherwise, consistency is checked).
 * @param stat status field
 */
void Filter_connect_shared(Filter* filt, Filter* main, int sharemode);

/**
 * segment and transform the impulse response into ceil(hlen/K) frames,
 * where K is half the length of the FFT used.
 *
 * @param h real impulse response
 * @param hlen length of impulse response
 * @param HH array of IR segment spectra, input must be zeroed
 * @param R number of segments
 * @param ww fft plan
 */
void Filter_segmentir(real* h, int hlen, complex** HH, int R, FftPlan* ww);

/** local function called by process (symbol needed by multirtols) */
void Filter_process_pre_(Filter* filt);
/** local function called by process (symbol needed by multirtols) */
void Filter_process_post_(Filter* filt);

/**
 * time-partitioned OLS convolution, streaming mode.
 *
 * Triggers the algorithm that a new frame has been written into the input buffer of
 * the filter (xframe) and that the last result will be read from output buffer (yframe).
 *
 * @param filters the filters to be triggered.
 * @return whether there are more nonzero samples (always 1 before call to Filter_finish())
 */
int Filter_process(Filter* filt);

/**
 * Sets the Filter coefficients for updating. Update is prepared only, for the next
 * steps, the Filter_update_step_ method is internally called in Filter_process. When a shared
 * IR is used, the update can be called from any sharing filter but only the main filter is
 * recommended to ensure that no concurrent updates occur.
 *
 * @param h new impulse response (must have the same number of frames as the original
 *          impulse response
 * @param hlen length of new IR
 * @param transition number of frames that the IR will be crossfaded from the old one
 *        (frequency-domain interpolation)
 * @param framewise whether to use framewise transition that only updates signal parts that
 *        enter the filter after the update started
 * @param keep whether to keep the updating structure (mempry vs. allocation)
 */
void Filter_update(Filter* filt, real* h, int hlen, int steps, int framewise, int keep);

/**
 * Initialise a filter update object for R frames of size L
 *
 * @param number of frames
 * @param samples per frame
 */
FilterUpdate* FilterUpdate_init(int R, int L);

/**
 * Destroy the filter update struct
 */
void FilterUpdate_free(FilterUpdate* up);

/**
 * Perform one update step.
 *
 * @return 1 if there are more steps for the update, 0 if finished / inactive.
 */
int Filter_update_step_(Filter* filt);

/**
 * time-partitioned OLS convolution, streaming mode.
 *
 * finishes the Filter operation. Afterwards, the Filter can be reused by calling Filter_restart.
 * If the Filter is shared by its input, finishes all filters that belong to the signal.
 *
 * @param Filter Filter to be finished
 */
void Filter_finish(Filter* filt);

/**
 * after a call to Filter_finish, the Filter is restarted by a new signal at its input buffer.
 *
 * @param Filter the Filter to be reinitialised
 * @return error code <0 or 0, -1 is returned if the signal is still finishing and the restart is ignored
 */
void Filter_restart(Filter* filt);

/**
 * deallocates the internal Filter memory (inbuf and outbuf must be freed).
 *
 * Note: shared Filter members are allocated outside of prepare_* calls, therefore they must be deallocated
 * separately.
 *
 * @param Filter to be destoyed
 * @return error code <0 or 0
 */
int Filter_free(Filter* filt);

/**
 * creates a set of fft weights
 *
 * @param m size of fft = 2^m
 */
FftPlan* FftPlan_init(int m);

/**
 * cleans up the fft weights in the argument
 *
 * @param weights to clean up
 */
void FftPlan_free(FftPlan* ww);

int filter();

#endif // FILTER_H
