/*
 *
 * "hArtes Reference/Benchmarking Application implementing a Wave Propagation WFS (WavePropToy)"
 *
 */
/**
 * @author        Gregor Heinrich (Arbylon) & Andres Perez for<br>
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
 * @filename      waveprop.c
 *
 * @file          waveprop.c
 *
 *                Provides wavepropagation background.
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "waveprop.h"
//#include "audioinput.h"
//#include <omp.h>

#include "mymath.h"

// windows: supress insecure warnings
#pragma warning( disable : 4996 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )

#define RAND  ((real) rand() / RAND_MAX)
#define round(a) floor( a + 0.5 )

//statistics
// this flag must be equal in ALL source-files!!!
//#define STATS

// set all gains to unity for testing
//#define UNITY_GAINS

//#define DEBUG_OUTPUT

static const real eps = 1e-6;

PrimarySource PrimarySource_init(real x, real y, real r, int type, int serverID)
{
	PrimarySource primarySource;

	primarySource.source.x = x;
	primarySource.source.y = y;
    primarySource.diffSource.x = 0;
    primarySource.diffSource.y = 0;
    primarySource.tUpdate = 0;
	if(type == 1){
		//; linear-array
		primarySource.innerSource = (primarySource.source.y < 0) ? 1:0;
	}else{
		//; ring-array
		primarySource.innerSource = ( vmag2d(primarySource.source) < r) ? 1:0;
	}
	
	//; init the source-server-ID;
	//; this is NOT used or accessed, except for within an audio-server-environment
	//; where sources can be instantiated and destroyed on a channel;
	//; initialize to -1, which will be overwritten, as soon as a source is created 
	//; on this channel by the server
	primarySource.serverID = serverID;

	return primarySource;
}

PrimarySource PrimarySource_deriveTransitionProperties( real r, real speakerDistance, int arrayType, PrimarySource primSource ) {

			if(primSource.innerSource == 1){
			
				//; for inner sources
				if( arrayType == 0 ){
					//; for circular array
					
					primSource.sourceArrayDistance = fabs( vmag2d(primSource.source) - r );					
					primSource.rActive = sqrt( (r*r) - vmag2d(primSource.source)*vmag2d(primSource.source) ) ;
#ifdef STATS
	flops.tfuns += 1;
	flops.adds += 2;
	flops.mults += 2;
#endif
				}else{
					//; for linear array
					primSource.sourceArrayDistance = fabs( primSource.source.y );					
					primSource.rActive = sqrt( (primSource.sourceArrayDistance)*(primSource.sourceArrayDistance) + 2.25*(speakerDistance)*(speakerDistance) );
#ifdef STATS
	flops.tfuns += 1;
	flops.adds += 2;
	flops.mults += 3;
#endif
				}
			} else {
				//; for outer sources

				//; transition smoothing
				if( arrayType == 0 ){
					//; for circular array
					primSource.sourceArrayDistance = fabs( vmag2d(primSource.source) - r );
					primSource.rActive = 0.1 + sqrt( (primSource.sourceArrayDistance)*(primSource.sourceArrayDistance) + 2.25*(speakerDistance)*(speakerDistance)  );
#ifdef STATS
	flops.tfuns += 1;
	flops.adds += 4;
	flops.mults += 3;
#endif
				} else {
					//; for linear array
					primSource.sourceArrayDistance = fabs( primSource.source.y );
					primSource.rActive = sqrt( (primSource.sourceArrayDistance)*(primSource.sourceArrayDistance) + 2.25*(speakerDistance)*(speakerDistance) );
#ifdef STATS
	flops.tfuns += 1;
	flops.adds += 1;
	flops.mults += 3;
#endif
				}
			}

			return primSource;
}

PrimarySourceArray* PrimarySourceArray_init(real *x, real *y, int sourceNumber, real r, int type)
{
	PrimarySourceArray* sources;
	int i;

	sources = (PrimarySourceArray *) malloc (sizeof(PrimarySourceArray));
	sources->sourceArray = (PrimarySource *) malloc (sourceNumber * sizeof(PrimarySource));
	sources->numberOfSources = sourceNumber;

	for (i = 0; i < sourceNumber; i++)
	{
		sources->sourceArray[i] = PrimarySource_init(x[i], y[i], r, type, -1);
	}
	return sources;
}

void PrimarySourceArray_free(PrimarySourceArray *sources)
{
	free(sources->sourceArray);
	free(sources);
}

SecondarySource SecondarySource_init(real x, real y, real nx, real ny)
{
	SecondarySource secSource;

	secSource.source.x = x;
	secSource.source.y = y;
	secSource.normal.x = nx;
	secSource.normal.y = ny;
	return secSource;
}

CircularSpeakerArray* CircularSpeakerArray_init(real *x, real *y, real *nx, real *ny, int speakerNumber)
{
	CircularSpeakerArray* speakers;
	int i;

	speakers = (CircularSpeakerArray*) malloc (sizeof(CircularSpeakerArray));
	speakers->speakerArray = (SecondarySource *) malloc (speakerNumber * sizeof(SecondarySource));
	speakers->numberOfSpeakers = speakerNumber;

	for (i = 0; i < speakerNumber; i++)
	{
		speakers->speakerArray[i] = SecondarySource_init(x[i], y[i], nx[i], ny[i]);
	}
	return speakers;
}

void CircularSpeakerArray_free(CircularSpeakerArray* speakers)
{
	free(speakers->speakerArray);
	free(speakers);
}

WavePropagation* WavePropagation_init(PrimarySourceArray *sources, CircularSpeakerArray *speakers, DelayLine *dl, real speedSound, int causalityDelay, real gainReference)
{
	WavePropagation* waveProp;

	waveProp = (WavePropagation*) malloc (sizeof(WavePropagation));
	waveProp->sources = sources;
	waveProp->speakers = speakers;
	waveProp->dl = dl;   
    waveProp->speedSound = speedSound;
	waveProp->causalityDelay = causalityDelay;
	waveProp->gainReference = gainReference;
	return waveProp;
}

void WavePropagation_free(WavePropagation* waveProp)
{
	free(waveProp);
}

void WavePropagation_update(WavePropagation *waveProp, real x, real y, real speed, int id, real speedSound, real r, int type, real speakerDistance)
{	

	//; this version combines the functionality of "WavePropagation_update" AND "delayLine_update"
	//; in order to simplify the code and make parallelization eventually more efficient (OMP)

	int q, numberOfSpeakers;	

	// "distance" is the distance between new and old source positions
	real distance;
	// "time" is the time it takes the source to get to its new position
	real time;
	//; "timeInSamples" is the amount of samples, the update takes
	real timeInSamples;
	//; "causalityDelay" is the fixed in-built delay for inner sources 
	real causalityDelay;

	//; BEGIN ALGORITHM------------------------------------->>>>>
	
	//; local variables 
	int samplingFreq;
	Vector2d newSource, oldSource;	
	
	PrimarySource primSource;	

	//; local variable representing the destination-source, only for calculation of a2; 
	PrimarySource tempSourceFinal;	

	samplingFreq = waveProp->dl->samplingFreq;
		
	//; assign local copy for Primary Source
	primSource = waveProp->sources->sourceArray[id];
	//;save old source-position-vector	 
	oldSource = primSource.source;
    //;get new source-position coordinates from arguments
	
	//;assign new coordinates to position-vector
	newSource.x = x;
    newSource.y = y;

	//; initialize local variable for source;
	//; if no update takes place because (distance == 0), this will be a static source;
	primSource.tUpdate = 0;
	primSource.diffSource.x = 0;
	primSource.diffSource.y = 0;
	//;assign destination for moving source
	primSource.destSource = newSource;
		
	distance = vmag2d(vsub2d(newSource, oldSource));
	
	//; assign causality delay
	causalityDelay = waveProp->causalityDelay;

    if (distance > 0){
        // time it takes for the update to finish
	    time = distance / speed; //[seconds]
		timeInSamples = time * samplingFreq; //;[fractional samples]
#ifdef STATS
		flops.mults += 2;
#endif

	    numberOfSpeakers = waveProp->speakers->numberOfSpeakers;	
        
        // determine the duration of the update [samples]
        primSource.tUpdate = (int) round(timeInSamples); //; [entire samples]
        // determine differential vector per sample of the moving source for localisation
        primSource.diffSource.x = (newSource.x - oldSource.x)/(primSource.tUpdate); 
        primSource.diffSource.y = (newSource.y - oldSource.y)/(primSource.tUpdate);
#ifdef STATS
	flops.adds += 2;
	flops.mults += 2;
#endif

		//; source holding the destination properties of the update
		tempSourceFinal = PrimarySource_init(newSource.x, newSource.y, r, type, -1);
		tempSourceFinal = PrimarySource_deriveTransitionProperties( r, speakerDistance, type, tempSourceFinal );

	//#pragma omp parallel for shared(waveProp) firstprivate(newSource, primSource, samplingFreq, oldSource, causalityDelay, time, timeInSamples)
	    for (q = 0; q < numberOfSpeakers; q++){

			//-------------test-->>>>>>>>>>>>>>>>
			real a1, a2, d1, d2, diffd1, diffd2, tDopFrac, rDopMin, vMagVectorPq;	
			SecondarySource speaker;

			//; local variable representing the source with minimum speaker-dsitance, only for calculation of a1;
			PrimarySource tempSourceNonMon;

			Vector2d vectorpq, normalpq, pt;
			// nonMonTrue = if there is a non-monotonic Doppler-shift to be 
			// considered, this is set to "1", "0" otherwise
			int nonMonDopTrue;			

			// "distance" is the distance between new and old source positions
			// "time" is the time it takes the source to get to its new position	
			
			real updateChunkCarry;			
			
			DelayUpdate up;
			real dd;
			int outputSamplesWrapped;
			int dropSampleOld;			
			
			//-------------test--<<<<<<<<<<<<<<<<
			//; init diffd
			diffd1 = 0;
			diffd2 = 0;

			//; assign local variables!!!! (write back at the very end of the routine)
			up = waveProp->dl->updater[id][q];
			dd = waveProp->dl->dd[id][q];
			outputSamplesWrapped = waveProp->dl->outputSamplesWrapped[id][q];			
			
            //----in case of new update while still updating-->

            // check if an unfinished update is still active and determine its progress
            updateChunkCarry = -1;
            if(up.active){
                updateChunkCarry = ( (real)(up.chunkSize - outputSamplesWrapped)
                                        / (real)up.chunkSize ) ;
            }
            //-------in case of new update while still updating<--

		    speaker = waveProp->speakers->speakerArray[q];
		    vectorpq = vsub2d(speaker.source, newSource);
			// calculate only once
			vMagVectorPq = vmag2d(vectorpq);

		    normalpq = vsmult2d(vectorpq, 1.0 / vMagVectorPq);
		            
            // DOPPLER begin -->

            // tDopFrac = element of [0,1], equals the fraction of update-trajectory after which
            // minimum distance to speaker is reached
            tDopFrac = ((speaker.source.y - oldSource.y)*(newSource.y -oldSource.y)+(speaker.source.x - oldSource.x)*(newSource.x -oldSource.x))
                            /
                            ((newSource.y -oldSource.y)*(newSource.y -oldSource.y)+(newSource.x -oldSource.x)*(newSource.x -oldSource.x));
#ifdef STATS
	flops.adds += 10;
	flops.mults += 5;
#endif
                       
            
            // round to reasonably accurate values
            if ( tDopFrac < eps) tDopFrac = 0;
            if ( (tDopFrac > (1-eps))) tDopFrac =1;

			//; flag which indicates whether there is an non-monotonic Doppler-Shift occurring	
			nonMonDopTrue = ( (tDopFrac > 0) && (tDopFrac < 1)) ? 1:0;
			up.nonMon = nonMonDopTrue;

			// d2 = delay at end of update
			
			if( type == 0){ //; for circular array
				if( vmag2d(newSource) < r ){
					//; for inner source
					d2 = round( (vMagVectorPq / speedSound ) * samplingFreq ) ;
					d2 = causalityDelay - d2;					
				}else{
					//; for outer sources
					d2 = round( (vMagVectorPq / speedSound ) * samplingFreq ) ;
					d2 += causalityDelay;
				}	
			}else{ //; for linear array
				if( newSource.y < 0 ){
					//; for inner source
					d2 = round( (vMagVectorPq / speedSound ) * samplingFreq ) ;
					d2 = causalityDelay - d2;
				}else{
					//; for outer sources
					d2 = round( (vMagVectorPq / speedSound ) * samplingFreq ) ;
					d2 += causalityDelay;	
				
				}
			}

            //; pt = position on update-trajectory of minimum distance to speaker
			//; d1 = delay at minimum distance to speaker				
			if ( nonMonDopTrue == 1 ){
				pt.x = oldSource.x + (newSource.x - oldSource.x)*tDopFrac;
				pt.y = oldSource.y + (newSource.y - oldSource.y)*tDopFrac;

				//rDopMin = minimum distance of trajectory to speaker
				rDopMin = vmag2d(vsub2d(pt, speaker.source)); 
				
				if( type == 0){ //; for circular array
					if( vmag2d(pt) < r ){
						//; for inner source
						d1 = round( (rDopMin / speedSound ) * samplingFreq ) ;
						d1 = causalityDelay - d1;				
					}else{
						//; for outer sources
						d1 = round( (rDopMin / speedSound ) * samplingFreq ) ;
						d1 += causalityDelay;
					}	
				}else{ //; for linear array
					if( pt.y < 0 ){
						//; for inner source
						d1 = round( (rDopMin / speedSound ) * samplingFreq ) ;
						d1 = causalityDelay - d1;
					}else{
						//; for outer sources 
						//;(a source exactly on the array is treated as an outer source)
						d1 = round( (rDopMin / speedSound ) * samplingFreq ) ;
						d1 += causalityDelay;					
					}
				}
            }else{ //( nonMonDopTrue == 1 )
                d1 = d2;
			} //if ( nonMonDopTrue == 1 )
			

            // time in [samples], the fractions of the update take			
            up.timeOfUpdate1 = (int) round( primSource.tUpdate * tDopFrac );
            up.timeOfUpdate2 = (int) round( primSource.tUpdate * (1 - tDopFrac) );

            
#ifdef DEBUG_OUTPUT
            //********test print-out begin -->
            printf("\n---------------------\n");
            printf("\n doppler-shift for [%i][%i] ->tDopFrac: %1.4f ",id, q, tDopFrac);
            printf("\n doppler-shift for [%i][%i] ->rDopMin: %1.4f  \n",id, q, rDopMin);
            if( (tDopFrac > 0) && (tDopFrac < 1)){
                printf("...non-monotonic doppler-shift: YES\n");
            }else{
                printf("...non-monotonic doppler-shift: NO\n");
            }
            //********test print-out end <--
#endif
        // DOPPLER end <--          
            
            
#ifdef DEBUG_OUTPUT
                //********test print-out begin -->
                printf("\nNew delay from source[%d] to speaker[%d]: %1.1f samples \n",id, q, d);
                //********test print-out end <--
#endif
		    
		    if ( (d2 > waveProp->dl->dmax) || (d2 < 0) )
		    {
			    printf("Warning, new delay bigger than dmax!\n");
		    }            

#ifdef UNITY_GAINS

            a2=1; // test-case for debug
            if( (tDopFrac > 0) && (tDopFrac < 1)){
                a1=1;
            }else{
                a1 = -1;
            }
            
#else

			a2 = calculateGainPQ(	tempSourceFinal, 
									waveProp->speakers->speakerArray[q],
									type, 
									r, 
									speakerDistance, 
									waveProp->gainReference);
			//; check, whether non-monotonic doppler-shift occurs;
			//; the nonMon-flag "a1" is set accordingly:
            if( nonMonDopTrue == 1){
				
				tempSourceNonMon = PrimarySource_init(pt.x, pt.y, r, type, -1);
				tempSourceNonMon = PrimarySource_deriveTransitionProperties( r, speakerDistance, type, tempSourceNonMon ); 

				a1 = calculateGainPQ(	tempSourceNonMon, 
										waveProp->speakers->speakerArray[q], 
										type, 
										r, 
										speakerDistance, 
										waveProp->gainReference);

            } else{ // if( nonMonDopTrue == 1)
                // a1 = -1 => if no non-monotonic doppler-shift occurs
                //a1 = -1; 
				nonMonDopTrue = 0;
				up.nonMon = 0;
            } // if ( nonMonDopTrue == 1)
#endif
                        
            // diffd is the delay-step-width ([samples]) taken per processed sample during
            // the update from dd[p][q] to the derived new source-speaker-delay [samples]
           
		    // diffd = 0.5; // diffd static for testing
            
            // diffd dynamically derived [samples] new
            // diffd1 = diffdelay from start to point of minimum distance
			
			if( nonMonDopTrue == 1 ){
				//; if start and point of least distance are not distinguishable
				//; in terms of delay-samples
				if( (d1 == dd) ){

					//; this case means that start and end of trajectory are not distinguishable
					//; in terms of delay-samples; only the amplitude aa[id][q] is to be updated
					if((d2 == d1)){
						if(up.active == 0){
							waveProp->dl->updatesActive++;
						}
						up.active = 1;
						up.chunkBasedUpdate = 0;
						up.nonMon = 1;
						up.a = a1;
						up.a2 = a2;
						diffd2 =  0;
						diffd1 = diffd2;
						//; in case a non-chunkbased update runs, steps and timeofupdate a counted in samples
						up.steps = up.timeOfUpdate1;
						up.steps2 = up.timeOfUpdate2;

					}else{
						if(up.active == 0){
							waveProp->dl->updatesActive++;
						}
						up.active = 1;
						up.chunkBasedUpdate = 1;
						diffd2 =  ((d2 - dd) / (timeInSamples));
						diffd1 = 0;
						//d1 = d2;
						up.d = d2;
						up.d2 = d2;
						up.nonMon = 0;
						up.a = a2;
						up.a2 = a2;
						up.steps = fabs(d2 - dd);
						up.steps2 = fabs(d2 - dd);
					}
				}else{ // if(d1==dd)
					//; if point of least distance and end are not distinguishable
					//; in terms of delay-samples
					if( d2 == d1 ){
						if(up.active == 0){
							waveProp->dl->updatesActive++;
						}
						up.active = 1;
						up.chunkBasedUpdate = 1;
						diffd1 =  ((d1 - dd) / (timeInSamples)); 
						// diffd2 = diffdelay from point of minimum distance to final position of update
						diffd2 =  diffd1 ;
						up.nonMon = 0;
						up.a = a2;
						up.a2 = a2;
						up.d = d2;
						up.d2 = d2;
						up.steps = fabs(d2 - dd);
						up.steps2 = fabs(d2 - dd);

					//; this case means the "normal case" where start, middle and end of a non-monotonic
					//; update are distinguishable					
 					}else{ // if( d2 == d1 )
						diffd1 =  ((d1 - dd) / (up.timeOfUpdate1 )) ;
						// diffd2 = diffdelay from point of minimum distance to final position of update
						diffd2 =  ((d2 - d1) / (up.timeOfUpdate2 )) ;

						if(up.active == 0){
							waveProp->dl->updatesActive++;
						}
						up.active = 1;
						up.chunkBasedUpdate = 1;
						up.nonMon = 1;
						up.a = a1;
						up.a2 = a2;
						up.d = d1;
						up.d2 = d2;
						up.steps =  fabs(d1 - dd);
						up.steps2 =  fabs(d2 - d1);
					}
				} // if( (d1 == dd) )                
                
            }else{
				// if no non-monotonic doppler-shift occurs
					//if old and target delay differ
				if(d2 != dd){
					diffd2 =  ((d2 - dd) / (timeInSamples));
					diffd1 = diffd2;
					//d1 = d2;					
					if(up.active == 0){
							waveProp->dl->updatesActive++;
					}
					up.active = 1;
					up.chunkBasedUpdate = 1;
					up.nonMon = 0;
					up.a = a2;
					up.a2 = a2;
					up.d = d2;
					up.d2 = d2;
					up.steps2 = fabs(d2 - dd);
					up.steps = up.steps2;
					
				}else{
					//start- and end-position are too close together;
					// ->just update position and gain 
					if(up.active == 0){
							waveProp->dl->updatesActive++;
						}
						up.active = 1;
						up.chunkBasedUpdate = 0;	
						up.nonMon = 0;
						up.a = a2;
						//; for this case, steps is counted in samples
						up.steps = primSource.tUpdate;
				}
			} // if( nonMonDopTrue == 1 )
#ifdef DEBUG_OUTPUT
		    printf("\nControl Thread: Doing update...\n");
		    printf("Control Thread: Params 1st Source: %d, 2nd Source: %d\n", id, q);
		    printf("Control Thread: Gain: %2.5lf, Delay : %2.5lf, Differential delay: %2.5lf\n", a, d, diffd);
#endif
	//;-----------------------taken from delayLine_update----------------------------->>		
						
			up.diffd = diffd1;
			up.diffd2 = diffd2;
			
			//; calculate only, when chunkbased update is occurring 
			if(up.chunkBasedUpdate == 1){	
				if (fabs(diffd1) > 0){
					up.chunkSize = (int) round( fabs(1.0 / diffd1) );
				}else{
					up.chunkSize =0;
				}
				if (fabs(diffd2) > 0){
					up.chunkSize2 = (int) round( fabs(1.0 / diffd2) );
					if(up.nonMon == 0){
						up.chunkSize = up.chunkSize2;
					}
				}else{
					up.chunkSize2 =0;
				}
			
				// Doppler-effect: incoming or outgoing source				
				
				//; insert inverse Dopplereffect from here on; use distance instead of delay to determine dropSample
				//; because for inner sources distance and delay are inversely correlated
				dropSampleOld = up.dropSample;
				
				if(up.nonMon == 1) {					
					up.dropSample = (up.d < dd) ? 1 : 0;
				} else {					
					up.dropSample = (up.d2 < dd) ? 1 : 0;
				}

				//; so that outputSamplesWrapped is already initialized in the first while-loop of processChunk()
				
				if ( (updateChunkCarry < 0) || (updateChunkCarry >= 1)){
					outputSamplesWrapped = up.chunkSize; 
				}else{
					if(dropSampleOld == up.dropSample){
						outputSamplesWrapped = (int) round(up.chunkSize / (1.0 + updateChunkCarry));
					}else{
						outputSamplesWrapped = (int) round(up.chunkSize / (1 - updateChunkCarry));
					}
				}				

				//; init step-index
				up.step = 0;
				//; init nrFrameWrap
				up.nrFrameWrap = 1;

			}else{				
				//; init step-index
				up.step = 0;
				//; init nrFrameWrap
				up.nrFrameWrap = 1;
			
			
			
			} // if(dl->updater[p][q].chunkBasedUpdate == 1)
		


	//; write back local variables to global struct!
	waveProp->dl->updater[id][q] = up;
	waveProp->dl->outputSamplesWrapped[id][q] = outputSamplesWrapped;
//;-----------------------taken from delayLine_update-----------------------------<<			


#ifdef DEBUG_OUTPUT
                //********* begin debug-test-print-->
                printf("\nSteps: %i\n", waveProp->dl->updater[id][q].steps);
                printf("\nChunkSize: %i\n\n", waveProp->dl->updater[id][q].chunkSize);
                //*******end debug-test-print<--
#endif
            	
		} // for q<--

		//; write back local variable to global struct
		waveProp->sources->sourceArray[id] = primSource;
	} // if (distance > 0) <--


    else {

		//; do nothing
#ifdef DEBUG_OUTPUT
        printf("\nNo update necessary, update matches current position\n");
#endif
    } // if (distance > 0) <--
}


real calculateGainPQ(PrimarySource sourceIn, SecondarySource speakerIn, int type, real r, real speakerDistance, real gainReference){			
			
			real aa;
			PrimarySource source;
			SecondarySource speaker;
			Vector2d vectorpq;
			Vector2d normalpq;
			real vMagVectorPQ;
			real PQcos;

			//; additional gain for the speakers inside activation-radius of 
			//; source while crossing the array
			real transitionCompensationGain;
			//; additional blending factor for the speakers inside activation-radius 
			//; of source while crossing the array; dependent on sourceArrayDistance
			//real sourceArrayDistanceBlender;

			transitionCompensationGain = 6. ;

			speaker = speakerIn;
			source = sourceIn;

			//; handling special case of source being at the exact same position as a speaker
			if( (source.source.x == speaker.source.x) && (source.source.y == speaker.source.y) ) {
				aa = 1. ;	
				aa += transitionCompensationGain; 

				aa *= gainReference;
#ifdef STATS	
	flops.adds += 1;
	flops.mults += 1;
#endif
				return aa;
			}

            // vector from source to speaker
			vectorpq = vsub2d(speaker.source, source.source);
            // normalized vector from source to speaker
			normalpq = vsmult2d(vectorpq, 1.0 / vmag2d(vectorpq));
#ifdef STATS	
	flops.mults += 1;
#endif
			vMagVectorPQ = vmag2d(vectorpq);        

            // dynamic gains, derived from the normal angles of source and speaker
            // and the source's position relative to the array            
            
            PQcos = vcos2d(normalpq, speaker.normal);
			//; including offset of r			
			if(source.innerSource == 0){	
				
				//; innerSource-parameter is still the one derived in the last frame

				if(type == 0){
					//; for circular array, outer source

					if (PQcos >= 0){
		                
						real windowFactor;
						
						//; activation-angle in combination with rActive;
						//; purpose: only window the speakers that are just entering the rActive-zone;
						real PQcosActive;
						//; cosPhiPQ is to be( (r-vmag2d(source.source)) / vMagVectorPQ ) 
						real sinPhiPQ;
												
						//; the term compared to this reference will be cosPhiPQ ;
						//; cos(PI/6) = approx. 0.866;
						//PQcosActive = 0.866;
						//; cos(PI/3) = approx. 0.866;
						PQcosActive = 0.3;

						sinPhiPQ = vsin2d(source.source, vectorpq);

						//; 3 alternatives to test for gain-factors
						aa = ( 1. / (vMagVectorPQ + 1.)) ;
						//aa = ( 1. / (sqrt(vMagVectorPQ) + 1.)) ;
						//aa = sqrt( 1. / (vMagVectorPQ + 1.)) ;

						aa *= PQcos;
#ifdef STATS	
	flops.adds += 1;
	flops.mults += 2;
#endif

						//; transition smoothing
						//; PI/2 is approx. 1.5708
						
						if( ( source.sourceArrayDistance <= ( 2.* speakerDistance) ) && ( vMagVectorPQ <= source.rActive ) ) {
							//windowFactor = cos( (vMagVectorPQ / source.rActive  )  * 1.5708 ) ;
							windowFactor = cos( ( fabs(vMagVectorPQ * sinPhiPQ) / (1.5 * speakerDistance) ) * 1.5708) ;
							windowFactor *= windowFactor;							
							
							aa += (1 - PQcos) * windowFactor ;	
#ifdef STATS
	flops.tfuns += 1;
	flops.adds += 1;
	flops.mults += 5;
#endif
						} 

						//; TODO: test & verify
						//; apply fixed gain from config
						aa *= gainReference; 
#ifdef STATS	
	flops.mults += 1;
#endif

					} else {
						   aa = 0. ;
					} //; if (PQcos > 0)
				} else {
					//; for linear array, outer source
					if (PQcos >= 0){
		                
						real windowFactor;

						//; 3 alternatives to test for gain-factors
						aa = ( 1. / (vMagVectorPQ + 1.)) ;
						//aa = ( 1. / (sqrt(vMagVectorPQ) + 1.)) ;
						//aa = sqrt( 1. / (vMagVectorPQ + 1.)) ;

						aa *= PQcos;
#ifdef STATS	
	flops.adds += 1;
	flops.mults += 2;
#endif

						//; transition smoothing
						//; PI/2 is approx. 1.5708
						
						//if( ( source.sourceArrayDistance <= (2.5 * speakerDistance) ) && ( vMagVectorPQ <= source.rActive ) ) {
						if( ( vMagVectorPQ <= source.rActive ) ) {
							//; simple version
							//aa += (1 - PQcos) * windowFactor ;
	
							//; with sourceArrayDistance-dependent blending

							/* // taken out for testing-->>
							if ( PQcos == 1) { //; special case of source being located exactly above/beneath speaker
								
								//; linear dependency version
								//sourceArrayDistanceBlender = (1 - (source.sourceArrayDistance / (2. * speakerDistance) ) );
								//; cosine dependency version
								sourceArrayDistanceBlender = ( cos ( (source.sourceArrayDistance / (2 * speakerDistance)) * 1.5708 ) );
								sourceArrayDistanceBlender *= sourceArrayDistanceBlender;

								aa += transitionCompensationGain * sourceArrayDistanceBlender ;
#ifdef STATS
	flops.tfuns += 1;
	flops.adds += 1;
	flops.mults += 5;
#endif
							} else { //; normal case
							*/  // taken out for testing--<<

								//; in case of (PQcos != 1) -> windowfactor is dependent on vectorpq.x
								//windowFactor = cos( ( fabs(vectorpq.x) / (1.5 * speakerDistance) ) * 1.5708) ;
								//windowFactor *= windowFactor;

								//aa += transitionCompensationGain * (1. - PQcos) * windowFactor ;
								windowFactor = (1. - (vMagVectorPQ / source.rActive) );
								windowFactor *= windowFactor;
								aa += transitionCompensationGain * windowFactor ;
#ifdef STATS	
	flops.adds += 2;
	flops.mults += 3;
#endif
							 // } // taken out for testing
						} 
					
						/*
						//; This is just for channel-testing!!!
						//; remove this for normal application!!!
						//; only the nearest speaker plays, all others are muted
						if( fabs( vectorpq.x ) < (speakerDistance/2)  ) {
							aa = aa;
						} else {
							aa = 0. ;
						}
						*/
						
						aa *= gainReference; 
#ifdef STATS	
	flops.mults += 1;
#endif

					} else {
						   aa = 0. ;
					} //; if (PQcos > 0)
				}
				
			} else {	//; if source is INSIDE the listening-space

				if(type == 0){				
				
					if( vMagVectorPQ >= source.rActive ){
						aa = 0. ;
					}else{ //; if speaker is located on the same side of the origin as the source
						real windowFactor;						
						//; activation-angle in combination with rActive;
						//; purpose: only window the speakers that are just entering the rActive-zone;
						real PQcosActive;
						//; for cosine-compensation
						real PQcosCompActive;
						//; cosPhiPQ is to be( (r-vmag2d(source.source)) / vMagVectorPQ ) 
						real cosPhiPQ;

						real sinPhiPQ;												
						//; the term compared to this reference will be cosPhiPQ ;
						//; cos(PI/6) = approx. 0.866;
						//PQcosActive = 0.866;
						//; cos(PI/3) = approx. 0.866;
						PQcosActive = 0.3;
						PQcosCompActive = 0.7;

						cosPhiPQ = vcos2d(source.source, vectorpq);
						sinPhiPQ = vsin2d(source.source, vectorpq);
						
						//aa[p][q] = ( 0.5 + conf->r / ( vmag2d(source) + conf->r) ) * (fabs(PQcos)) * (1. / ( vMagVectorPQ + 1) );
																		
						aa = ( 0.5 + r / ( vmag2d(source.source) + r) );
						aa *= (fabs(PQcos)) ;
#ifdef STATS	
	flops.adds += 2;
	flops.mults += 2;
#endif
						//; windowing of the activated speakers for smooting the transient onset;
						//; PI is approx. by 3.1416, so PI/2 = 1.5708
						//windowFactor = cos( ( vMagVectorPQ / source.rActive ) * 1.5708);
						

						//; for even smoother transition;
						//; this should be the best expression for windowFactor dur to it's smooth onset;
						//windowFactor = windowFactor*windowFactor;
						
						if( cosPhiPQ < PQcosActive) {
							windowFactor = sin( (cosPhiPQ / PQcosActive) * 1.5708 );
							windowFactor = windowFactor*windowFactor;
							//windowFactor *= windowFactor;
							aa *=  windowFactor;
#ifdef STATS
	flops.tfuns += 1;	
	flops.mults += 4;
#endif
							
						}	

						//; transition smoothing (compensate the vanishing cos-term);						
						if( source.sourceArrayDistance <= (2. * speakerDistance) ) {
							//windowFactor = cos( ( vMagVectorPQ / source.rActive ) * 1.5708);
							//aa += (1 - fabs(PQcos) ) * windowFactor ;
							//PQcosActive *= 0.05 + 0.95 * (source.sourceArrayDistance / (2. * speakerDistance));
							//windowFactor = cos( fabs( sinPhiPQ * vMagVectorPQ ) / ( 1.5 * speakerDistance ) * 1.5708 );

							if( ( fabs(sinPhiPQ * vMagVectorPQ) > speakerDistance ) ) {
								windowFactor = sin( (cosPhiPQ / PQcosCompActive) * 1.5708 );
								windowFactor *= windowFactor;
#ifdef STATS
	flops.tfuns += 1;	
	flops.mults += 3;
#endif
							} else {
								windowFactor = 1;
							}
							
							aa += (1 - fabs(PQcos) ) * windowFactor ;
#ifdef STATS	
	flops.adds += 2;
	flops.mults += 1;
#endif
						} 

						//; apply fixed gain from config
						aa *= gainReference; 
#ifdef STATS	
	flops.mults += 1;
#endif
						
					}
				} else {
					//; for linear array, inner sources

					real windowFactor;					
					
					//aa = ( 1.0 +  sqrt( vMagVectorPQ ) ) * (fabs(PQcos)) ;
					//aa = ( 1.0 +  sqrt( fabs(source.source.y) ) );
					aa = sqrt( 1.0 +   fabs(source.source.y)  );
					aa *= (fabs(PQcos)) ;
#ifdef STATS
	flops.tfuns += 1;
	flops.adds += 1;
	flops.mults += 1;
#endif
					
					if( ( vMagVectorPQ <= source.rActive ) ) {
													
						//; with sourceArrayDistance-dependent blending
							/* // taken out for testing -->>
							if ( fabs(PQcos) == 1 ) { //; special case of source being located exactly above/beneath speaker
								
								//; in case of (PQcos == 1) -> windowfactor is dependent on sourceArrayDistance
								//sourceArrayDistanceBlender = (1 - (source.sourceArrayDistance / (2. * speakerDistance) ) );
								sourceArrayDistanceBlender = ( cos ( (source.sourceArrayDistance / (2 * speakerDistance)) * 1.5708 ) );								
								sourceArrayDistanceBlender *= sourceArrayDistanceBlender;
								aa += transitionCompensationGain * sourceArrayDistanceBlender ;
#ifdef STATS
	flops.tfuns += 1;
	flops.adds += 1;
	flops.mults += 5;
#endif

							} else { //; normal case								

								//; in case of (PQcos != 1) -> windowfactor is dependent on vectorpq.x
								windowFactor = cos( ( fabs(vectorpq.x) / (1.5 * speakerDistance) ) * 1.5708) ;
								windowFactor *= windowFactor;
								sourceArrayDistanceBlender = ( cos ( (source.sourceArrayDistance / (2 * speakerDistance)) * 1.5708 ) );								
								sourceArrayDistanceBlender *= sourceArrayDistanceBlender;
								//aa += transitionCompensationGain * (1. - fabs(PQcos)) * windowFactor * sourceArrayDistanceBlender ;
								//aa += transitionCompensationGain * (1. - (vMagVectorPQ / source.rActive) ) * windowFactor * sourceArrayDistanceBlender ;
							*/ // taken out for testing --<<
								windowFactor = (1. - (vMagVectorPQ / source.rActive) );
								windowFactor *= windowFactor;
								aa += transitionCompensationGain * windowFactor ;
								
#ifdef STATS	
	flops.adds += 2;
	flops.mults += 3;
#endif
							// } // taken out for testing --						
						
					} // if( ( vMagVectorPQ <= source.rActive ) ) { ....
					
					//; apply fixed gain from config
					aa *= gainReference;
#ifdef STATS	
	flops.mults += 1;
#endif

				} // if(conf->type == 0)
			}	// if (conf->priSources->sourceArray[i].innerSource == 0)

			return aa;
}			

void WavePropagation_updateStep(WavePropagation *waveProp)
{
	DelayLine_updateStep(waveProp->dl);
}

int WavePropagation_processFrame(WavePropagation *waveProp)
{   
	return DelayLine_processFrame(waveProp->dl); 
}

int WavePropagation_processSample(WavePropagation *waveProp, real *xxsamp, real *yysamp)
{
	return DelayLine_processSample(waveProp->dl, xxsamp, yysamp);
}
