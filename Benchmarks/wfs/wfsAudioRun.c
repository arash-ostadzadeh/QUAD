
#include <math.h>

#include <stdio.h>
#include <time.h>

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

// choose kind of input:
// ifdef WAV_INPUT => load wav from file (all channels);
// otherwise => get input from signalRamp.txt and load it to all channels
#define WAV_INPUT

// save the results in a multichannel .wav-file
#define WAV_OUTPUT

// print current values to the console
//#define DEBUG_OUTPUT

// set all gains to unity for testing
//#define UNITY_GAINS

// - include time measurement and print-outs
// - uses windows.h functionality
// - measures the time required to process one frame
// for the filter and delay-line separately
// - reports the total required time at the end of all calculations
//#define TIME_MEASUREMENT

// test setup for framewise updates:
// a new update occurs each frame; see controlrun for hard-coded parameters
//#define FRAMEWISE_UPDATES

//; for statistics: count math-operations
//#define STATS

#define round(a) floor( a + 0.5 )

// windows: supress insecure warnings
#pragma warning( disable : 4996 )
#pragma warning( disable : 4244 )

// defined if filter processing is desired
#define USE_FILTER
// defined if delayline / wave propagation processing is desired
#define USE_DELAY

//statistics
// this flag must be equal in ALL source-files!!!
//#define STATS

#include "delayline.h"
#include "mymath.h"
#include "waveprop.h"
//#include "audioinput.h"
#include "audioio.h"
#include "config.h"
#include "filter.h"
#include "waveIO.h"
#include "wfsAudioRun.h"

#ifdef TIME_MEASUREMENT
	#include "CtimeMeasurement.h"
#endif

/**
* represents the audio i/o thread
* \param obj a DelayLine object
*/
void wfsCaudiorun(AudioRunParams* runParams) {

    int more = 1;
	long inputIndex = 0, outputIndex;
    AudioIo* ain, *aout;
	long time = 0;
	int frameLength;
    int restLength = 1;
	// loop variables
	int p;

	// framecounter
	long frameCount;

	// for debugging -->>
	/*
	real var1, var2;
	int i_debug;
	*/
	// for debugging --<<

#ifdef TIME_MEASUREMENT
	//time variables
	double t;
	double t_min_filter, t_max_filter, t_min_delayLine, t_max_delayLine;
	double t_min_total, t_max_total;

	int violations;
	int q, k, r;
	float frameTime;
	float sumPerRun;
#endif

	//; for statistics evaluation
	//; reset all stats-values
#ifdef STATS
	initflops();
#endif

    // connect to memory based audio
	if (runParams->conf->AsioStreamInput == 0) {
		ain = AudioIo_init(runParams->inputSignals, runParams->conf->P, (long) runParams->inputChannelLength, runParams->frameLength);
	}
	aout = AudioIo_init(runParams->outputSignals, runParams->conf->Q, (long) (runParams->inputChannelLength + runParams->maxDelay + runParams->hlen), runParams->frameLength);


	///////////////////////////////////////////////////////////////
	// main audio and update loop
    printf("\n\nAudio I/O started...\n");
    more = 1;

	frameCount = 0;

#ifdef TIME_MEASUREMENT
	//time variables
	t_min_delayLine = 100.; //init to value likely to be replaced
	t_max_delayLine = 0.; //init to value likely to be replaced
	t_min_filter = 100.; //init to value likely to be replaced
	t_max_filter = 0.; //init to value likely to be replaced
	t_min_total = 100.; //init to value likely to be replaced
	t_max_total = 0.; //init to value likely to be replaced

	violations = 0;
	frameTime = (float)(1000.*(float)runParams->frameLength / ((float)runParams->conf->samplingFreq) );
	sumPerRun = 0;

	//time print-out
	printf("Frame-time : %f ms", frameTime );
	printf("\nTime required to process one frame: \n\n");
#endif

	//; MAIN-LOOP counting the input-index until end of input-file
	for ( inputIndex = 0; inputIndex < (runParams->inputChannelLength); inputIndex += runParams->frameLength ) {

#ifdef TIME_MEASUREMENT
			//time measurement for controlrun, getFrames and filter starts here
			CTimeMeasurement_start();
#endif


			//; debug-test-printout
			/*
			if( (frameCount == 238) || (frameCount == 237)){
				printf("\n---controlrun ahead---%i\n", frameCount);
			}
			*/


#ifdef STATS
			flops.addsSoFar = flops.adds;
			flops.multsSoFar = flops.mults;
			flops.tfunsSoFar = flops.tfuns;
#endif
			//; update calls
		    wfsCcontrolrun(runParams);

#ifdef STATS
			printf("\n---------------------\nFrame # : %i\n", frameCount);
			printf("\nControlrun-STATS:\nadds: %i\nmults: %i\ntfuns: %i\n",
					flops.adds-flops.addsSoFar,
					flops.mults-flops.multsSoFar,
					flops.tfuns-flops.tfunsSoFar
					);
#endif
			//; debug-test-printout
			/*
			if(frameCount == 480){
				printf("\n---controlrun passed---%i\n", frameCount);
			}
			*/


			if (runParams->conf->AsioStreamInput == 0) {
				//; if(conf->AsioStreamInput == 1) it is assumed, that the imput-ASIO-buffers are filled from an
				//; extern entity and no data from WAV-files is required;
				//;@params: more=1 indicates, that there are frames left in the source-file
				more = AudioIo_getFrames(ain, runParams->inbufs);
			}

			//; debug-test-printout
			/*
			if(frameCount == 480){
				printf("\n---getFrames passed---%i\n", frameCount);
			}
            */

#ifdef DEBUG_OUTPUT
                //;********* begin debug-test-print-->
                printf("\n\n------------------------------------------------------\n");
                printf("input-buffers loaded...\n");
                printf("input-buffers channels: \n " );
                for (p = 0; p < runParams->conf->P ; p += 4  ){
                        printf("\n\n");
                        for (r = 0; (r < 4) && (p+r) < runParams->conf->P; r++){
                            printf(" [%i]\t\t  ", p + r );
                        }

                        for (k = 0; k < runParams->frameLength; k++){
                               printf("\n");
                               for (r = 0; (r < 4) && (p+r) < runParams->conf->P; r++){
                                   printf("%i->%4.2f \t",k, runParams->inbufs[p+r][k]);
                               }
                        }
                }
                printf("\n\n");
                //;*******end debug-test-print<--
#endif

#ifdef USE_OMP
#pragma omp parallel for
#endif


#ifdef STATS
			flops.addsSoFar = flops.adds;
			flops.multsSoFar = flops.mults;
			flops.tfunsSoFar = flops.tfuns;
			flops.numberOfCmultsSoFar = flops.numberOfCmults;
#endif
			//; #pragma omp parallel saves some time here
			if ( runParams->conf->filterEngage == 1 ) {

			  //; OMP-parallel-pragma saves lots of time here
			  #pragma omp parallel for
				for (p = 0; p < runParams->conf->P; p++){
					//runParams->filters[p]->xframe = runParams->inbufs[p];
					Filter_process(runParams->filters[p]);

				}
			}

#ifdef STATS
			printf("\nFilter-STATS:\nadds: %i\nmults: %i\ntfuns: %i\nnumber of complex mults: %i\n",
					flops.adds-flops.addsSoFar,
					flops.mults-flops.multsSoFar,
					flops.tfuns-flops.tfunsSoFar,
					flops.numberOfCmults - flops.numberOfCmultsSoFar
					);
#endif

			//; debug-test-printout
			/*
			if(frameCount == 481){
				printf("\n---filterProcess passed---%i\n", frameCount);
			}
			*/

#ifdef TIME_MEASUREMENT
			//;time measurement stops here and evaluates results
			CTimeMeasurement_stop();
			t = CTimeMeasurement_getMilliseconds();
			sumPerRun = t;
			if (t > t_max_filter) t_max_filter = t;
			if (t < t_min_filter) t_min_filter = t;

			// at times report performance results
			/*
			if((frameCount%50) == 0){
				//printf("time required to process one frame: %lf ms\n", t);
				printf("\ncontrolrun, getFrames, filter:\n");
				printf("min: %2.12lf ms\n", t_min_filter);
				printf("max: %2.12lf ms\n", t_max_filter);
				t_min_total = t_min_filter;
				t_max_total = t_max_filter;
				// re-init min & max
				t_min_filter = 100.; //init to value likely to be replaced
				t_max_filter = 0.; //init to value likely to be replaced
			}
			*/

#endif

#ifdef DEBUG_OUTPUT
                //********* begin debug-test-print-->
                printf("\n\n filtbufs-buffers loaded...\n");
                printf("filtbufs channels:\n " );
                for (p = 0; p < runParams->conf->P ; p += 4  ){
                        printf("\n\n");
                        for (r = 0; (r < 4) && (p+r) < runParams->conf->P; r++){
                            printf(" [%i]\t\t  ", p + r );
                        }

                        for (k = 0; k < runParams->frameLength; k++){
                               printf("\n");
                               for (r = 0; (r < 4) && (p+r) < runParams->conf->P; r++){
                                   printf("%i->%4.2f \t",k, runParams->filtbufs[p+r][k]);
                               }
                        }
                }
                printf("\n\n");
                //*******end debug-test-print<--
#endif

#ifdef TIME_MEASUREMENT
			//time measurement for delayLine starts here
			CTimeMeasurement_start();
#endif


#ifdef STATS
			flops.addsSoFar = flops.adds;
			flops.multsSoFar = flops.mults;
			flops.tfunsSoFar = flops.tfuns;
#endif
            // WaveProp process one frame
			WavePropagation_processFrame(runParams->waveProp);

#ifdef STATS
			printf("\nDelayLine-STATS:\nadds: %i\nmults: %i\ntfuns: %i\n",
					flops.adds-flops.addsSoFar,
					flops.mults-flops.multsSoFar,
					flops.tfuns-flops.tfunsSoFar
					);
#endif
			// debug-crash-testprintout
			/*
			if(frameCount == 104){
				printf("\n---delayLine process passed---%i\n", frameCount);
			}
			*/

#ifdef TIME_MEASUREMENT
			//time measurement stops here and evaluates
			CTimeMeasurement_stop();
			t = CTimeMeasurement_getMilliseconds();

			//; debug-test-printout:
			//printf("updatesActive: %i ", runParams->waveProp->dl->updatesActive);

			if (t > t_max_delayLine) t_max_delayLine = t;
			if (t < t_min_delayLine) t_min_delayLine = t;

			sumPerRun += t;

			//------------------debug-test-printout:--------------------------->>
			//; debug-test-printout:

			//-----------show aa and dd for every frame------------>>>
			/*
			printf("\nframe:%i updatesActive: %i position: ( %f , %f )\n", frameCount,
																			runParams->waveProp->dl->updatesActive,
																			runParams->waveProp->sources->sourceArray[0].source.x,
																			runParams->waveProp->sources->sourceArray[0].source.y);
			printf("\naa:\n");
			for (p=0; p<runParams->conf->P; p++){
				for(q=0; q<runParams->conf->Q; q++){
					printf("%1.2f ", runParams->waveProp->dl->aa[p][q]);
					//printf("%1.2f ", runParams->waveProp->dl->dd[p][q]);
				}
			}
			printf("\ndd:\n");
			for (p=0; p<runParams->conf->P; p++){
				for(q=0; q<runParams->conf->Q; q++){
					printf("%04.0f ", runParams->waveProp->dl->dd[p][q]);
				}
			}
			printf("\n");
			 */
			//-----------show aa and dd for every frame------------<<<


			//; This is ONLY for debugging and renders the output unusable!------>>>
			//; check for glitches in ouput-frame
			/*
			for(q = 0; q < runParams->conf->Q; q++) {
				real z;
				int r;
				z=runParams->outbufs[q][0] ;
				for( r = 1; r < runParams->frameLength; r++) {

					z += runParams->outbufs[q][r];

					if( (r%100) == 0 ){
						if(z == 0.) {
							printf("\n\n _*_ WARNING: too many zeros in output-frame [%i][%i] _*_\n\n", q,r);
							runParams->outbufs[q][r] = 32000. ;
						}
						z = 0. ;
					}

				}

			}
			*/
			//; This is ONLY for debugging and renders the output unusable!------<<<

			// */
			//--------------------debug-test-printout:-------------------------<<

/*
			printf("\n%i \t %f ", frameCount, sumPerRun);
			if(sumPerRun >= frameTime){
				violations++;
				printf("\t****");
				printf("\nviolation in frame: %i\n", frameCount);
			}
*/
				sumPerRun = 0;

			// at times report performance
			/*
			if((frameCount%50) == 0){
				//printf("time required to process one frame: %lf ms\n", t);
				printf("\nDelayLine:\n");
				printf("min: %2.12lf ms\n", t_min_delayLine);
				printf("max: %2.12lf ms\n", t_max_delayLine);

				t_min_total += t_min_delayLine;
				t_max_total += t_max_delayLine;

				printf("Total:\n");
				printf("min: %2.12lf ms\n", t_min_total);
				printf("max: %2.12lf ms\n", t_max_total);

				printf("Frame-Time-Violations so far: %i \n\n", violations);
				// re-init min & max
				t_min_total = 100.; //init to value likely to be replaced
				t_max_total = 0.; //init to value likely to be replaced
				t_min_delayLine = 100.; //init to value likely to be replaced
				t_max_delayLine = 0.; //init to value likely to be replaced
			}
			*/

			//increment frame counter
			//frameCount++;
#endif
			// only for debugging
			frameCount++;

		    AudioIo_setFrames(aout, runParams->outbufs); // write output-frames to output

			// debug printout -->>
			/*
			if( (frameCount == 239) || (frameCount == 238) || (frameCount == 240)){
				var1 = 0;
				var2 = 0;
				for( i_debug = 0; i_debug < runParams->frameLength -1; i_debug++ ) {
					if ( (runParams->outbufs[0][i_debug +1] - runParams->outbufs[0][i_debug]) > 3000. ) {
						var1++;
						printf("\nglitch at: frame %i\nsample %i\n samples: %f , previous was %f\n", frameCount-1, i_debug, runParams->outbufs[0][i_debug +1], runParams->outbufs[0][i_debug]);

					}
				}
				printf("\ndelayLine pointer: pin:%i; ppout: %i\n", runParams->waveProp->dl->pin, runParams->waveProp->dl->ppout[0][0] );
				system("pause");
			}
			*/
			// debug printout -->>

#ifdef DEBUG_OUTPUT
                //********* debug-test-print begin -->
                    printf("\n\n outbufs-buffer loaded...\n");
                    printf("outbufs channels:\n " );
                    //for (i = 0; i < runParams->conf->Q; i++)
                    //{
                    //    printf("\t [%i]: \n",i );
                    //    printRealVec(runParams->outbufs[i], runParams->frameLength);
                    // }

                    for (q = 0; q < runParams->conf->Q ; q += 4  ){
                        printf("\n\n");
                        for (r = 0; (r < 4) && (q+r) < runParams->conf->Q; r++){
                            printf(" [%i]\t\t  ", q + r );
                        }

                        for (k = 0; k < runParams->frameLength; k++){
                               printf("\n");
                               for (r = 0; (r < 4) && (q+r) < runParams->conf->Q; r++){
                                   printf("%i->%4.2f \t",k, runParams->outbufs[q+r][k]);
                               }
                        }
                    }
                    printf("\n\n");
                 //*********  debug-test-print end <--

                //********* begin debug-test-print-->
                printf("\nactual delays:\n");
                for (p = 0; p < runParams->conf->P; p++)
                {
                    for (q = 0; q < runParams->conf->Q; q++)
                    printf("\t dd[%i][%i]: %2.3f \n",p, q, runParams->waveProp->dl->dd[p][q] );

                 }
                //*******end debug-test-print<--
#endif

		time += runParams->frameLength;

#ifdef DEBUG_OUTPUT
        printf("\n -------->time: %i\n",time);
#endif

	} //  for (inputIndex) <--

#ifdef TIME_MEASUREMENT
	//; debug-test-printout
	printf("Frame-Time-Violations so far: %i \n\n", violations);
#endif

	/////////////////////////////////////////////////////////////
	// shutdown sequence (processes remaining samples in delayline etc.)
	if ( runParams->conf->filterEngage == 1 ) {
		for (p = 0; p < runParams->conf->P; p++){
			Filter_finish(runParams->filters[p]);
			//; set the filter-inputs to zero; they will not be overwritten while the system is finishing;
			zeroRealVec(runParams->filters[p]->xframe, runParams->frameLength);
		}
	}
	// No more inputs
	outputIndex = inputIndex;

	frameLength = runParams->frameLength;

    for (more = 1; more > 0; more = more){

		// initialize more to Zero
        more = 0;

        // get frame from each channel
		if (runParams->conf->filterEngage == 1) {
			for (p = 0; p < runParams->conf->P; p++){

					// if any of the filter-channels still has outputs...
					more = more + Filter_process(runParams->filters[p]);
			}
		}

#ifdef DEBUG_OUTPUT
                    //********* begin debug-test-print-->
                        printf("\n\n filtbufs-buffers loaded...\n");
                        printf("filtbufs channels:\n " );
                        //for (i = 0; i < runParams->conf->P; i++) {
                        //    printf("\t [%i]: \n",i );
                        //    printRealVec(runParams->filtbufs[i], runParams->frameLength);
                        //}

                        for (p = 0; p < runParams->conf->P; p++){
                            printf("[%i]\t\t",p );
                          }
                            for (k = 0; k < runParams->frameLength; k++){
                                printf("\n");
                                for (p = 0; p < runParams->conf->P; p++){
                                    printf("%i->%4.2f \t ",k, runParams->filtbufs[p][k]);
                                }
                            }
                    //*******end debug-test-print<--
#endif

        // if all the filter-channels are finished -> finish delayline
        if ((more == 0) && !runParams->waveProp->dl->finishing){

            DelayLine_finish(runParams->waveProp->dl);

#ifdef DEBUG_OUTPUT
            printf("\n Delay-Line finishing... \n");
#endif
        }


        more = WavePropagation_processFrame(runParams->waveProp);

 #ifdef DEBUG_OUTPUT
                //********* debug-test-print begin -->
                    printf("\n\n outbufs-buffer loaded...\n");
                    printf("outbufs channels:\n " );
                    //for (i = 0; i < runParams->conf->Q; i++)
                    //{
                    //    printf("\t [%i]: \n",i );
                    //    printRealVec(runParams->outbufs[i], runParams->frameLength);
                    // }

                    for (q = 0; q < runParams->conf->Q ; q += 4  ){
                        printf("\n\n");
                        for (r = 0; (r < 4) && (q+r) < runParams->conf->Q; r++){
                            printf(" [%i]\t\t  ", q + r );
                        }

                        for (k = 0; k < runParams->frameLength; k++){
                               printf("\n");
                               for (r = 0; (r < 4) && (q+r) < runParams->conf->Q; r++){
                                   printf("%i->%4.2f \t",k, runParams->outbufs[q+r][k]);
                               }
                        }
                    }
                 //*********  debug-test-print end <--
#endif

        AudioIo_setFrames(aout, runParams->outbufs);

		outputIndex = outputIndex + runParams->frameLength;

		// sleep(runParams->conf->deltaT);
		//printf("\nAudioRun Thread: Sleep finished!\n");
		time += runParams->frameLength;

    } // for (more > 0) <--

	printf("\nAudio I/O stopped.\nTime = %ld samples (%i Frames)\n", time, frameCount);

#ifdef STATS
	printf("\nPerformance statistics (global):\nadds: %i\nmults: %i\ntfuns: %i\nffts: %i\n",
			flops.adds,
			flops.mults,
			flops.tfuns,
			flops.ffts
			);
	printf("\nPerformance statistics (per source, per speaker, per frame):\nadds: %i\nmults: %i\ntfuns: %i\nffts: %i\n",
			(int)flops.adds/(frameCount*runParams->conf->P*runParams->conf->Q),
			(int)flops.mults/(frameCount*runParams->conf->P*runParams->conf->Q),
			(int)flops.tfuns/(frameCount*runParams->conf->P*runParams->conf->Q),
			(int)flops.ffts/(frameCount*runParams->conf->P)
			);
#endif

	//; debug-test-printout:
	/*
	for(p = 0; p < runParams->conf->P; p++){
		for(q = 0; q < runParams->conf->Q; q++){
			if( runParams->waveProp->dl->updater[p][q].active ){
				printf("\nupdates still active: [%i][%i] ", p, q);
			}
		}
	}
	*/

    AudioIo_free(ain);
	AudioIo_free(aout);
}

/**
* represents the update/control procedure
* \param obj an audiorun params object
*/
void wfsCcontrolrun(AudioRunParams* runParams) {

    //long millis;
    UpdateAudioRunParams updateParams;


#ifdef FRAMEWISE_UPDATES

	int i;

	// let the source move once to the right and back to the left...
	//WavePropagation_update(WavePropagation *waveProp, real x, real y, real speed, int id, real speedSound)
	for(i=0;i<runParams->waveProp->dl->P;i++){
		if ( (runParams->time > 5000) && (runParams->time < 400000) ){
			WavePropagation_update(runParams->waveProp, -5.0, 2.0, 3.0, 0, 340.0, runParams->conf->r, runParams->conf->type);
		}else if ( (runParams->time > 550000) && (runParams->time < 1000000) ){
			WavePropagation_update(runParams->waveProp, 0.5, 5.0, 0.2, i, 340.0, runParams->conf->r, runParams->conf->type);
		}
		else if( (runParams->time > 1100000) && (runParams->time < 1350000) ){
			WavePropagation_update(runParams->waveProp, 5.0, 5.0, 3.2, i, 340.0, runParams->conf->r, runParams->conf->type);
		}
		else if( (runParams->time > 1400000) && (runParams->time < 1450000) ){
			WavePropagation_update(runParams->waveProp, -5.0, 5.0, 5.0, i, 340.0, runParams->conf->r, runParams->conf->type);
		}
		else if( (runParams->time > 1500000) ){
			WavePropagation_update(runParams->waveProp, 5.0, 5.0, 15.0, i, 340.0, runParams->conf->r, runParams->conf->type);
		}
	}

#else
	// if time exceeds the scheduled instant for the next update AND there are
    // more updates in the queue --> do update
    for ( runParams->updateNr;
            (runParams->updateNr < runParams->conf->updates) &&
                (runParams->time >= runParams->conf->updatesArray[runParams->updateNr].instant);
				runParams->updateNr ++){

		// get all necessary data from obj
	    // WaveProp-control:
		updateParams.waveProp = runParams->waveProp;
		updateParams.update = &runParams->conf->updatesArray[runParams->updateNr];

		if ( (runParams->conf->clientSourceTrackingMode == 0)
			  &&
			  ( (runParams->waveProp->sources->sourceArray[updateParams.update->p].serverID ) == (updateParams.update->id) )
			) {
			//; normal update of an existing and persisting source
			wfsCdo_update(&updateParams, runParams->conf->r, runParams->conf->type, runParams->conf->speakerDistance);

		} else {
			//; every update is done by reinstantiating the source
			real dd;
			real aa;
			real vMagVectorPQ;
			int p;
			int q;

			p = updateParams.update->p;

			//; init a new source with ID=(-1)
			runParams->waveProp->sources->sourceArray[p] = PrimarySource_init(	updateParams.update->x,
																				updateParams.update->y,
																				runParams->conf->r,
																				runParams->conf->type,
																				-1
																				);
			//; assign rActive and sourceSpeakerDistance
			runParams->waveProp->sources->sourceArray[p] = PrimarySource_deriveTransitionProperties( runParams->conf->r,
																										runParams->conf->speakerDistance,
																										runParams->conf->type,
																										runParams->waveProp->sources->sourceArray[updateParams.update->p]
																										);
			//; assign new filter for the source
			if ( runParams->conf->filterEngage == 1 ){
				runParams->filters[p] = Filter_init(runParams->inbufs[p],
														runParams->filtbufs[p],
														runParams->hhOuter[p],
														runParams->hlen,
														runParams->filters[p]->ww);
			}

			for (q = 0; q < runParams->conf->Q; q++) {
				aa = calculateGainPQ(runParams->waveProp->sources->sourceArray[p],
											runParams->waveProp->speakers->speakerArray[q],
											runParams->conf->type,
											runParams->conf->r,
											runParams->conf->speakerDistance,
											runParams->conf->gainReference );

				vMagVectorPQ = vmag2d( vsub2d(runParams->waveProp->speakers->speakerArray[q].source,
										runParams->waveProp->sources->sourceArray[p].source) );

				if(runParams->waveProp->sources->sourceArray[p].innerSource == 0){
					//; for outer sources
					dd = round( runParams->waveProp->causalityDelay +
								( vMagVectorPQ / runParams->conf->speedSound )* runParams->conf->samplingFreq ); // [samples]
				} else {
					//; for inner sources
					dd = round( runParams->waveProp->causalityDelay -
								( vMagVectorPQ / runParams->conf->speedSound )* runParams->conf->samplingFreq ); // [samples]
				}

				//; check for legal values of delay
				if ( (dd > (real)runParams->maxDelay) || (dd <= 0) ){
					printf("Error calculating delay, input channel = %d, output channel = %d\n", p, q);
					return ;
				}

				//; write back to delayLine
				runParams->waveProp->dl->aa[p][q] = aa;
				runParams->waveProp->dl->dd[p][q] = dd;
			}




		}

        //Filter-control: now done inside "wfsClocalizeSources"

	} // for (runParams->updateNr;...)

#endif

	wfsClocalizeSources(runParams);

	// sleep(runParams->conf->deltaT);
	runParams->time += runParams->frameLength; // update time [samples]
}

void wfsClocalizeSources(AudioRunParams* runParams){

	int p,q;
    Vector2d oldPos, newPos;
	int frameLength;
	PrimarySource tempSource;
	int arrayType;
	real r;
	//; spatial windowing for inner sources in order to smoothen transients of activated speakers
	// real windowFactor;
	//; transition smoothing
	//; distance between two speakers
	real speakerDistance;

	arrayType = runParams->conf->type;
	r = runParams->conf->r;

	speakerDistance = runParams->conf->speakerDistance;

	frameLength = runParams->frameLength;

	// get / determine position of sources once per frame
	// this routine determines the position of each source for the END of the frame...
	// the current positions have been derived in the last frame

		for(p = 0; p < runParams->conf->P; p++) {

				//; testvariable for signal debugging
				// real z;

                // if there is any source moving, detecting one speaker-source-pair is sufficient

				//if(runParams->waveProp->dl->updater[p][0].active > 0){
				if(runParams->waveProp->sources->sourceArray[p].tUpdate > 0){

					tempSource = runParams->waveProp->sources->sourceArray[p];
                    oldPos = tempSource.source;

				//; begin positioning for the next frame ----------------------->>>>
					if(tempSource.tUpdate > frameLength ){

                        newPos.x = oldPos.x +(frameLength * tempSource.diffSource.x);
                        newPos.y = oldPos.y +(frameLength * tempSource.diffSource.y);

                        tempSource.tUpdate -= frameLength;
#ifdef STATS
	flops.adds += 2;
	flops.mults += 2;
#endif

                    }else{

						newPos = tempSource.destSource;

                        tempSource.tUpdate = 0;
                        tempSource.diffSource.x = 0;
                        tempSource.diffSource.y = 0;
                    }

                    tempSource.source.x = newPos.x;
                    tempSource.source.y = newPos.y;


				//; debug-test-printout
				/*
						for (z = 0; z < runParams->conf->Q ; z++){
							printf("a[%i] ", z);
						}
						printf("\n");
				*/


				// determine gains at current position, which has been derived in the last frame
				 //#pragma omp parallel for shared(runParams) //private(speaker, vectorpq, normalpq, vMagVectorPq, PQcos, arrayType, r)
					for (q = 0; q < runParams->conf->Q; q++){

					//; Only for debugging!
					//z = runParams->waveProp->dl->aa[p][q];

					runParams->waveProp->dl->aa[p][q] = calculateGainPQ(	runParams->waveProp->sources->sourceArray[p],
																			runParams->waveProp->speakers->speakerArray[q],
																			runParams->conf->type,
																			runParams->conf->r,
																			runParams->conf->speakerDistance,
																			runParams->conf->gainReference);

						//; debug-test-printout --->>>
						/*
						if(abs( z - runParams->waveProp->dl->aa[p][q] ) > 0.03 ) {
							printf("\n\n -*- WARNING: glitch in gain-factor for a[%i][%i] -*- \n\n", p, q);
						}

						*/

						/*
							printf("%1.2f ", runParams->waveProp->dl->aa[p][q]);
						*/
						//; debug-test-printout ---<<<

					} // for q

                    //; debug-test-printout
					//printf("\n");
					//printf("x=%1.2f, y=%1.2f \n", oldPos.x, oldPos.y);

//#endif


				//-----------filter-updates---------------------------->>>>
					// cases for filter-updates;
					// determine for the next frame, whether the source will be an inner or outer source
                    if(arrayType == 0){ // for circular speaker-array

                        if( (vmag2d(oldPos) >= r) && (vmag2d(newPos) < r) ){
							if ( runParams->conf->filterEngage == 1) {
								Filter_update(runParams->filters[p], runParams->hhInner[p], runParams->filters[p]->hlen, 1, 1, 1); //
							}
							// set the innerSource-indicator accordingly
							tempSource.innerSource = 1;
                        }
                        if( (vmag2d(oldPos) < r) && (vmag2d(newPos) >= r) ){
							if ( runParams->conf->filterEngage == 1) {
								Filter_update(runParams->filters[p], runParams->hhOuter[p], runParams->filters[p]->hlen, 1, 1, 1); //
							}
							tempSource.innerSource = 0;
                        }

                    }else{ // in case of linear speaker-array
                        if( (oldPos.y >= 0) && (newPos.y < 0) ){
							if ( runParams->conf->filterEngage == 1) {
								Filter_update(runParams->filters[p], runParams->hhInner[p], runParams->filters[p]->hlen, 1, 1, 1); //
							}
							tempSource.innerSource = 1;
                        }
                        if( (oldPos.y < 0) && (newPos.y >= 0) ){
							if ( runParams->conf->filterEngage == 1) {
								Filter_update(runParams->filters[p], runParams->hhOuter[p], runParams->filters[p]->hlen, 1, 1, 1); //
							}
							tempSource.innerSource = 0;
                        }
                    } // if(runParams->conf->type
				//-----------filter-updates---------------------------<<<<

					//; TODO: combine the next two assignments into one by writing directly back to sourceArray
					tempSource = PrimarySource_deriveTransitionProperties( runParams->conf->r, runParams->conf->speakerDistance, runParams->conf->type, tempSource );
					//; write back local variable to global struct
					runParams->waveProp->sources->sourceArray[p] = tempSource ;

                } //if(runParams->waveProp->dl->updater[p][0].active > 0)

			} //for(p = 0; p < runParams->conf->P; p++)
}

void wfsCdo_update(UpdateAudioRunParams* updateParams, real r, int type, real speakerDistance) {

	WavePropagation_update(	updateParams->waveProp,
							updateParams->update->x,
							updateParams->update->y,
							updateParams->update->speed,
							updateParams->update->p,
							updateParams->waveProp->speedSound,
							r,
							type,
							speakerDistance);
}
