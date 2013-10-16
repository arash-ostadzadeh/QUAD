/*
*
* "hArtes Reference/Benchmarking Application implementing a MIMO delay line (Delaytoy)"
*
*/
/**
* @author        Gregor Heinrich (Arbylon) & Fabian Logemann for<br>
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
* @filename      main.c
*
* @file          main.c
*
*                Main driving functions to run the application.
*
*                Note: This is a skeleton of the final code as a preview of the
*                concurrency structure.
*/

#define _USE_MATH_DEFINES
#include <math.h>

#ifndef __CYGWIN__
#include <omp.h>
#endif

#include <stdio.h>
#include <time.h>

#if defined __LINUX__ || __APPLE__
// omit any sleep (real-time simulation)
//#include <stdlib.h>
#define sleep(x) //sleep(x)
#else
#include <windows.h>
#define sleep(x) Sleep(x)
#endif

// use open mp pragmas
// #define USE_OMP

//indicate that allocated memory has been free'd
//#define MEM_FREE_REPORT

// save output to output.txt
//#define OUTPUT_TO_TXT

// choose kind of input:
// ifdef WAV_INPUT = load wav from file (all channels);
// otherwise = get input from signalRamp.txt and load it to all channels
#define WAV_INPUT

// save the results in a multichannel .wav-file
#define WAV_OUTPUT

// print current values to the console
//#define DEBUG_OUTPUT

// set all gains to unity for testing
//#define UNITY_GAINS

#include "delayline.h"
#include "mymath.h"
#include "waveprop.h"
#include "audioinput.h"
#include "audioio.h"
#include "config.h"
#include "filter.h"
#include "waveIO.h"
#include "wfsAudioRun.h"

#define round(a) floor( a + 0.5 )

// windows: supress insecure warnings
#pragma warning( disable : 4996 )
#pragma warning( disable : 4244 )

// defined if filter processing is desired
#define USE_FILTER
// defined if delayline / wave propagation processing is desired
#define USE_DELAY

// report on calculation requirements
//#define STATS

int waveprop();

/**
* Test driver for the delay line.
*/
int main(char** argv, int argc) {

	printf("hArtes Wave Field Synthesis Application\nRunning in offline-mode...\n");
     return waveprop(); // waveprop represents the actual system
}




/***************************begin-waveprop-function****************************************/
int waveprop() {

	AudioRunParams* runParams;
	real **inputSignals;
    real **outputSignals;
	DelayLine *dl;
    // input and output frame buffers P, Q
    real **inbufs, **filtbufs, **outbufs;
    // filter structures for each input channel
    Filter** filters;
    // fft structure
    FftPlan* ww;
    // filter IR
    real** hhInner, **hhOuter;
    int hlen;
    // frameLength
    int frameLength;
	// array of delay times in samples
	real **dd;
	// array of delay gains (linear)
	real **aa;
	int i, j, k, p, q, delayLineP, delayLineQ, maxDelay;
    long inputChannelLength;
	WavePropagation *waveProp;
	CircularSpeakerArray *circSpeakerArray;
	real *xSecSources, *ySecSources;
	real *nxSecSources, *nySecSources;
	Configuration *conf;
	SecondarySource speaker;
	Vector2d vectorpq, source;
	//variable holding the distance between speaker and source at initialisation
	real vMagVectorPQ;
	// causalityDelay calculated according to the spatial environment
	real causalityDelay;

    //output-txt-file
#ifdef OUTPUT_TO_TXT
    FILE *pFile;
#endif

#ifdef TIME_MEASUREMENT
	//time measurement
	clock_t start, end;
#endif

#ifdef DEBUG_OUTPUT
	int r;
#endif


    ////////////////////// configuration ///////////////////
	// READ VALUES FROM INPUT
#ifdef DEBUG
	conf = Configuration_init("config_debug.txt");
#else
	conf = Configuration_init("config.txt");
#endif
	if (conf == NULL)
	{
		printf("Error reading configuration file. Exiting...\n");
		return -1;
	}
    hlen = 20; // IR-length of filters; static to this point

    frameLength = conf->frameLength; // frame-length

    // create impulse responses
    hhInner = (real**)callocRealArr(conf->P, hlen);
    hhOuter = (real**)callocRealArr(conf->P, hlen);

    // create P times the same IR

    for (p = 0; p < conf->P; p++) {
        for (i = 0; i < hlen; i++) {
            hhInner[p][i] = 0.;
            hhOuter[p][i] = 0.;
        }
		hhInner[p][0] = 1.0;
		hhOuter[p][0] = 1.0;
    }

#ifdef DEBUG_OUTPUT

        //**********debug print-out for filterIR -->
        printf("IR's of hhInner: \n");
                for (p = 0; p < conf->P ; p += 4  ){
                        printf("\n\n");
                        for (r = 0; (r < 4) && (p+r) < conf->P; r++){
                            printf(" [%i]\t\t  ", p + r );
                        }

                        for (k = 0; k < hlen; k++){
                               printf("\n");
                               for (r = 0; (r < 4) && (p+r) < conf->P; r++){
                                   printf("%i->%4.2f \t",k, hhInner[p+r][k]);
                               }
                        }
                }
                printf("\n");

        printf("IR's of hhOuter: \n");
                for (p = 0; p < conf->P ; p += 4  ){
                        printf("\n\n");
                        for (r = 0; (r < 4) && (p+r) < conf->P; r++){
                            printf(" [%i]\t\t  ", p + r );
                        }

                        for (k = 0; k < hlen; k++){
                               printf("\n");
                               for (r = 0; (r < 4) && (p+r) < conf->P; r++){
                                   printf("%i->%4.2f \t",k, hhOuter[p+r][k]);
                               }
                        }
                }
                printf("\n");
        //**********debug print-out for filterIR <--


    Configuration_printConfig(conf);
#endif

    ////////////////// buffer setup ///////////////////////
    // inbufs represents P input frames
    inbufs = (real**) malloc(conf->P * sizeof(real*));
	for (p = 0; p < conf->P; p++){
        inbufs[p] = (real*) calloc (frameLength,  sizeof(real));
    }

    // filtbufs represents P filter output frames
	if ( conf->filterEngage == 1) {
		filtbufs = (real**) malloc(conf->P * sizeof(real*));
		for (p = 0; p < conf->P; p++){
			filtbufs[p] = (real*) calloc (frameLength,  sizeof(real));
		}
	}

    // outbufs represents Q output frames
    outbufs = (real**) malloc(conf->Q * sizeof(real*));
    for (q = 0; q < conf->Q; q++){
        outbufs[q] = (real*) calloc (frameLength , sizeof(real));
    }

    //////////////////// filter setup ///////////////////////////
    ww = FftPlan_init(ldint(2*frameLength));

    // filter-bank-init, assumes that all sources are outer sources initially
	if ( conf->filterEngage == 1) {
		filters = (Filter**) malloc(conf->P * sizeof(Filter*));
		for (p = 0; p < conf->P; p++)
		{
			filters[p] = (Filter*) malloc ( (size_t) sizeof(Filter) );
			filters[p] = Filter_init(inbufs[p], filtbufs[p], hhOuter[p], hlen, ww);
		}
	}

	//////////////////// speaker array setup ////////////////////

	delayLineP = conf->P;
	delayLineQ = conf->Q;

    // to be set by config.txt: number of samples to be fed into the system
    // conf->inputChannelLength = number of input samples

    inputChannelLength = (long) ((conf->inputChannelLength / frameLength) + 1 ) * frameLength ;

	xSecSources = (real *) malloc (conf->Q * sizeof(real));
	ySecSources = (real *) malloc (conf->Q * sizeof(real));
	nxSecSources = (real *) malloc (conf->Q * sizeof(real));
	nySecSources = (real *) malloc (conf->Q * sizeof(real));

    if(conf->type == 0){
        for (q = 0; q < conf->Q; q++){
            // circular speaker-array:
		    // 0 radians position corresponds to a right x axis speaker (x > 0, y = 0)
		    // pi / 2 radians position corresponds to a forward y axis speaker (x = 0, y > 0)
		    // pi radians position corresponds to a left x axis speaker (x < 0, y = 0)
		    // pi * 3 / 2 radians position corresponds to a backward y axis speaker (x = 0, y < 0)
		    // All the speakers are equidistantly spaced.
		    xSecSources[q] = conf->r * cos (2 * M_PI / conf->Q * q);
		    ySecSources[q] = conf->r * sin (2 * M_PI / conf->Q * q);
		    // Normal vector is oriented to the origin (with unity norm)
		    nxSecSources[q] = - cos (2 * M_PI / conf->Q * q);
		    nySecSources[q] = - sin (2 * M_PI / conf->Q * q);
	    }
    }else if(conf->type == 1){

        if(conf->Q == 1){
                xSecSources[0] = 0;
		        ySecSources[0] = 0;
		        // Normal vector is oriented towards negative y
		        nxSecSources[0] = 0;
		        nySecSources[0] = -1;
        }else{
                for (q = 0; q < conf->Q; q++){
		            // linear speaker-array:
		            // All the speakers are equispaced.
		            xSecSources[q] = (2*conf->r*q)/(conf->Q -1) - conf->r;
		            ySecSources[q] = 0;
		            // Normal vector is oriented towards negative y
		            nxSecSources[q] = 0;
		            nySecSources[q] = -1;
	            }
        } //if(conf->Q == 1)

    }else{

		printf("Speaker-Array geometry invalid. Exiting...\n");
		return -1;

    } //if(conf->type == 0)

	circSpeakerArray = CircularSpeakerArray_init(xSecSources, ySecSources, nxSecSources, nySecSources, conf->Q);
		
	// derive causality delay in order to describe inner sources
	//; TODO: evtl. embed into WavePropagation_init(conf, circSpeakerArray, dl)
	if(conf->type == 0) {
		// derive maximum possibly occurring delay [samples]
		//; TODO: by now, it is assumed, that (xmin=xmax) and (ymin=ymax)
		maxDelay = (int) ceil( (( sqrt( (conf->xmax * conf->xmax) 
				+ (conf->ymax * conf->ymax) ) + conf->r ) / conf->speedSound ) * conf->samplingFreq );

		causalityDelay = (real) round( (2.5 * conf->r / conf->speedSound) * conf->samplingFreq );
		
		//; causality-delay added to maxDelay for deriving the total actual length of delayLine
		maxDelay += causalityDelay;
		
	} else {

		// derive maximum possibly occurring delay [samples]
		//; TODO: by now, it is assumed, that (xmin=xmax) and (ymin=ymax)
		maxDelay = (int) ceil( (( sqrt( ( (conf->xmax + conf->r) * (conf->xmax + conf->r) ) 
				+ (conf->ymax * conf->ymax) ) ) / conf->speedSound ) * conf->samplingFreq );

		//; TODO: the distance (2*r) is yet chosen arbitrarily;
		//; it should be derived according to the spatial environment in which the audience resides 
		//causalityDelay = (int) round( ( (3 * conf->r) / conf->speedSound) * conf->samplingFreq );
		
		//; it is by now assumed that inner sources do not reach more than 10m into
		//; the listening space
		causalityDelay = (int) ceil( ( sqrt( (10. * 10.) + (10. * 10.) ) / conf->speedSound ) * conf->samplingFreq );

		//; causality-delay added to maxDelay for deriving the total actual length of delayLine
		maxDelay += causalityDelay;
	}

#ifdef DEBUG_OUTPUT

            //********test print-out begin -->
            printf("\nmaxDelay: %d samples \n", maxDelay);
            //********test print-out end <--
#endif

	// (PxQ)-matrix bearing the delays from sources to speakers
	dd = (real **) malloc (conf->P * sizeof(real *));

    // (PxQ)-matrix bearing the gains from sources to speakers
	aa = (real **) malloc (conf->P * sizeof(real *));

	for (i = 0; i < conf->P; i++)
	{

		dd[i] = (real *) malloc (conf->Q * sizeof(real));
		aa[i] = (real *) malloc (conf->Q * sizeof(real));

		source = conf->priSources->sourceArray[i].source;

		//; assign speakerDistance and rActive to the source for transition smoothing
		conf->priSources->sourceArray[i] = PrimarySource_deriveTransitionProperties( conf->r, conf->speakerDistance, conf->type, conf->priSources->sourceArray[i] );

		for (j = 0; j < conf->Q; j++){

			aa[i][j] = calculateGainPQ(	conf->priSources->sourceArray[i],
										circSpeakerArray->speakerArray[j],
										conf->type,
										conf->r,
										conf->speakerDistance,
										conf->gainReference);

			speaker = circSpeakerArray->speakerArray[j];
			vectorpq = vsub2d(speaker.source, source);
			vMagVectorPQ = vmag2d(vectorpq);

			 ///////////////////////// derive source-speaker-delays /////////////////////////

            // [begin case 1] -->
            // => dd = ( |P2Q|/speedSound ) / SamplingPeriod = P2Qdelaytime * (conf->SamplingFreq) ,=> counted in samples
            // ...for the delayLine to interpolate between adjacent samples, use this variant ([fractional samples])
            //dd[i][j] = ( vmag2d(vsub2d(speaker.source, source)) / conf->speedSound ) * conf->samplingFreq ; // [fractional samples]
            // [end case 1] <--

            // [begin case 2] -->
            //... for the delayLine to use entire samples without interpolation, use this variant ([whole samples])
		if(conf->priSources->sourceArray[i].innerSource == 0){
			//; for outer sources
            dd[i][j] = ( causalityDelay + ( vMagVectorPQ / conf->speedSound )* conf->samplingFreq ); // [samples]
			dd[i][j] = round(dd[i][j]);
		} else {
			//; for inner sources
			dd[i][j] = ( causalityDelay - ( vMagVectorPQ / conf->speedSound )* conf->samplingFreq ); // [samples]
			dd[i][j] = round(dd[i][j]);
		}
            // [end case 2] <--

            // [begin case 3] -->
            // dd[i][j] = 0; // test for debugging
            // [end case 3] <--

#ifdef DEBUG_OUTPUT
                //********test print-out begin -->
                printf("\n d[%d][%d]: %f samples \n",i,j, dd[i][j]);
                //********test print-out end <--
#endif

            if ( (dd[i][j] > maxDelay) || (dd[i][j] <= 0) ){
				printf("Error calculating delay, input channel = %d, output channel = %d\n", i, j);
			    return -1;
            }

		} // for (j<Q)<--

    }	// for (i<P)<--



	dl = DelayLine_init(aa, dd, maxDelay, conf->P, conf->Q, conf->samplingFreq, conf->frameLength);

	//; set signal-buffers according to config
	//; --> if no filter is applied, feed the delayLine directly from the input
	if ( conf->filterEngage == 1) {
		dl->xxframe = filtbufs;
		dl->yyframe = outbufs;
	} else {
		dl->xxframe = inbufs;
		dl->yyframe = outbufs;
	}


	waveProp = WavePropagation_init(conf->priSources, circSpeakerArray, dl, conf->speedSound, causalityDelay, conf->gainReference);

	//; report status
	printf("\nNumber of primary sources: %i\nNumber of secondary sources: %i\n", conf->P, conf->Q);

    ///////////////////// load input ///////////////////////////

    //---------------------------------------------begin wave-input-->     

	if (conf->AsioStreamInput == 0) {
		// get memory requirements from config.txt
		  
		  inputSignals = (real**) calloc(conf->P, sizeof(real*));
		  for (p = 0; p < conf->P; p++){
			inputSignals[p] = (real*) calloc (inputChannelLength , sizeof(real));
		  }
		  
		// load input-buffers from the wav-files given in config.txt
		  if( wav_load(conf, inputSignals) != 1){
			return 0;
		  }
	}
    
	outputSignals = (real**) calloc (conf->Q , sizeof(real*));
	for (q = 0; q < conf->Q; q++){
		outputSignals[q] = (real*) calloc ( (int)(inputChannelLength + (maxDelay) + (hlen) + conf->frameLength), sizeof(real));
    }
	

    //////////////////// prepare audio runner "thread" //////////////////////////
	
	runParams = (AudioRunParams *) malloc (sizeof(AudioRunParams));   

	if ( conf->filterEngage == 1) {
		runParams->filters = filters;
		runParams->filtbufs = filtbufs;
	}
    runParams->inbufs = inbufs;    
    runParams->outbufs = outbufs;
	runParams->waveProp = waveProp;
	runParams->inputSignals = inputSignals;
	runParams->inputChannelLength = inputChannelLength;
	runParams->outputSignals = outputSignals;
	runParams->maxDelay = maxDelay;
    runParams->hlen = hlen;
	// frame-based
	runParams->frameLength = conf->frameLength;
	runParams->conf = conf;
	runParams->time = 0;
    runParams->updateNr = 0;

    //just for testing: new filter-IR -->
    runParams->hhOuter = hhOuter;
    runParams->hhInner = hhInner;
    //just for testing <--

#ifdef DEBUG_OUTPUT
        //********* begin debug-test-print -->
        //for (i=0; i<runParams->conf->P; i++){
        // printf("inputSignals[%d]\n",i);
        //   printRealVec(inputSignals[i], runParams->frameLength);
        //}
        //*******end debug-test-print <--
#endif

#ifdef TIME_MEASUREMENT
	//start time measurement
		start = clock();
#endif

	// start audio i/o processing
	wfsCaudiorun (runParams); 

#ifdef TIME_MEASUREMENT
	//;stop time measurement
	end = clock();			
	printf("Elapsed total time : %lf seconds \n", (double)(end-start)/CLOCKS_PER_SEC);
#endif						

	////////////////////////// Writing output to a file ////////////////////
 
#ifdef WAV_OUTPUT    
    
    //TODO: get parameters from input wave-file or config

	printf("\nWriting output to WAV-file...");
	if( wav_store(runParams) != 1) {
		printf("\nWriting output to file failed!\n");
		return -1;
	} else {
		printf("\nWriting output to file succeeded!\n");
	}    

#endif

#ifdef OUTPUT_TO_TXT 

	pFile = fopen("output.txt", "w");

	if (pFile == NULL){

		perror("Error creating file, closing...\n");		
	}
	else{

		printf("\nWriting output to .txt ...");
		for (q = 0; q < conf->Q; q++)
		{
			// write each channel in groups of 4 values, but last one
			for (j = 0; j < floor((runParams->inputChannelLength + runParams->maxDelay + runParams->hlen)/ 4.0); j++)
			{
				fprintf(pFile, "%2.5f %2.5f %2.5f %2.5f\n", runParams->outputSignals[q][j * 4], runParams->outputSignals[q][j * 4 + 1], runParams->outputSignals[q][j * 4 + 2], runParams->outputSignals[q][j * 4 + 3]);
                
#ifdef DEBUG_OUTPUT
                //********* begin debug-test-print -->
                // printf("\nOutput signals written to file: \n");
                // printf("%2.5f %2.5f %2.5f %2.5f\n", runParams->outputSignals[q][j * 4], runParams->outputSignals[q][j * 4 + 1], runParams->outputSignals[q][j * 4 + 2], runParams->outputSignals[q][j * 4 + 3]);
                //*******end debug-test-print <--
#endif
			}

			// Last one, 0 to 4 values
			for (k = 0; j * 4 + k < runParams->inputChannelLength; k++)
			{
				fprintf(pFile, "%2.5f ", runParams->outputSignals[q][j * 4 + k]);
			}

			//If a value or more were added, add a cr+lf
			if (k != 0)
			{
				fprintf(pFile, "\n");
			}

		} // for (q) <--

		fclose(pFile);
		printf("\nWriting output to .txt succeeded\n");

    } // if (pFile == NULL) <--	
#endif

    /////////////////// uninitialise fields //////////////////////

    //  free filter structures
	if ( conf->filterEngage == 1) {
		for (i = 0; i < conf->P; i++){
			free( filters[i] );
		}
		free(filters);
	}

#ifdef MEM_FREE_REPORT
	printf("freed: filters\n");
#endif

	for (i = 0; i < conf->Q; i++){
        free( outbufs[i] );
	}
    free(outbufs);
#ifdef MEM_FREE_REPORT
	printf("freed: outbufs\n");
#endif

	if ( conf->filterEngage == 1) {
		for (i = 0; i < conf->P; i++){
			free( filtbufs[i] );
		}
		free(filtbufs);
	}	
	
#ifdef MEM_FREE_REPORT
	printf("freed: filtbufs\n");
#endif

    //  free buffers (new structure)

    for (i = 0; i < conf->P; i++){
		free( inbufs[i] );
    }

	free(inbufs);
#ifdef MEM_FREE_REPORT
	printf("freed: inbufs\n");
#endif

	//  free impulse responses

    for (i = 0; i < conf->P; i++){
		free( hhInner[i] );
        free( hhOuter[i] );
    }
	free(hhInner);
    free(hhOuter);
#ifdef MEM_FREE_REPORT
	printf("freed: filter-IRs\n");
#endif    
   	for (i = 0; i < conf->P; i++){
		free(aa[i]);
	}
	free(aa);
#ifdef MEM_FREE_REPORT
	printf("freed: aa\n");
#endif
	if (conf->AsioStreamInput == 0) {
		for (i = 0; i < conf->P; i++){
			free(inputSignals[i]);
		}
		free(inputSignals);
	}
#ifdef MEM_FREE_REPORT
	printf("freed: inputSignals\n");
#endif

	for (i = 0; i < conf->Q; i++){
        free( outputSignals[i] ); 

#ifdef DEBUG_OUTPUT
        //printf("outputSignals[%d]: %d\n",i, outputSignals[i]);
#endif
    }
	free(outputSignals);

#ifdef MEM_FREE_REPORT
	printf("freed: outputSignals\n");
#endif
	
	for (i = 0; i < conf->P; i++){
		free(dd[i]);
	}
	free(dd);
#ifdef MEM_FREE_REPORT
	printf("freed: dd\n");
#endif

	free(xSecSources);
	free(ySecSources);
	free(nxSecSources);
	free(nySecSources);
	Configuration_free(conf);
	CircularSpeakerArray_free(waveProp->speakers);
	DelayLine_free(waveProp->dl);
	WavePropagation_free(waveProp);	
	free(runParams);
    free(ww);

	return 0;
}
/***************************endof-waveprop-function****************************************/
