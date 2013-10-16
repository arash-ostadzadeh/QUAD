

// avoid error message of identifier redefinition
#ifndef WFSAUDIORUN_H
#define WFSAUDIORUN_H


#define _USE_MATH_DEFINES

#if defined __LINUX__ || defined __APPLE__
// omit any sleep (real-time simulation)
//#include <stdlib.h>
#define sleep(x) //sleep(x)
#else
#include <windows.h>
#define sleep(x) Sleep(x)
#endif

// use open mp pragmas
// #define USE_OMP

// print current values to the console
// #define DEBUG_OUTPUT

// set all gains to unity for testing
// #define UNITY_GAINS

// windows: supress insecure warnings
//#pragma warning( disable : 4996 )

#include <math.h>
#include <stdio.h>
#include <time.h>
#include "delayline.h"
#include "mymath.h"
#include "waveprop.h"
#include "audioio.h"
#include "config.h"
#include "filter.h"

#ifndef __CYGWIN__
#include <omp.h>
#endif


typedef struct {
    // Delay Line
    WavePropagation* waveProp;
	// Updates
	Update *update;
} UpdateAudioRunParams;

typedef struct {
    //filters
    Filter** filters;
    // buffer pointers
    real** inbufs;
    real** filtbufs;
    real** outbufs;

    //just for testing, update-filter-IR -->
    real** hhInner;
    real** hhOuter;
    //just for testing <--

    // Delay Line
    WavePropagation* waveProp;
    // Input Signals (P channels)
    real** inputSignals;
	// Length of each input channel
	long inputChannelLength;
	// Length of each frame
	int frameLength;
    // Output Signals (Q channels)
    real** outputSignals;
	// Maximum value of the delay matrix
	long maxDelay;
	// length of the filter's IR
    int hlen;
	// global audio time in samples
	long time;
	// configuration read from "config.txt"
	Configuration* conf;
    // current update number
    int updateNr;
} AudioRunParams;

// forward declarations
void wfsCaudiorun(AudioRunParams* runParams);
void wfsCcontrolrun(AudioRunParams* runParams);
void wfsClocalizeSources(AudioRunParams* runParams);
void wfsCdo_update(UpdateAudioRunParams* updateParams, real r, int type, real speakerDistance);

AudioRunParams* audioRunParams_init();


#endif // WFSAUDIORUN_H
