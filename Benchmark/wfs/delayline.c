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
 * @filename      delayline.c
 *
 * @file          delayline.c
 *
 *                Multichannel delay line with integer delays.
 *
 *                Note: This is a skeleton of the final code as a preview of the
 *                concurrency structure.
 *
 */
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "delayline.h"
#include "mymath.h"

#ifndef __CYGWIN__
#include <omp.h>
#endif

// windows: supress insecure warnings
#pragma warning( disable : 4305 )

static const real eps = 1e-6;

#define round(a) floor( a + 0.5 )
#define STATUS_OK if (stat != NULL) stat->numeric = RTOLS_NO_ERROR;
#define RAND  ((real) rand() / RAND_MAX);

//statistics
// this flag must be equal in ALL source-files considered!!!
//#define STATS

// for openMP application
// #define USE_OMP

// for time measurement in order to find bottle-necks
//#define STOPWATCH

#ifdef STOPWATCH
	#include "CtimeMeasurement.h"
#endif

// for delay-line interpolation between samples due to delay of fractional samples
//#define USE_FRACTIONAL_DELAYS

// if only chunk-processing is required
#define PROCESS_CHUNK_ONLY

//function delay = makedelayline(aa, dd, dmax)
DelayLine* DelayLine_init(real** aa, real** dd, int dmax, int P, int Q, int samplingFreq, int frameLength) {

	DelayLine *dl;
	int i, j;

	dl = (DelayLine *) malloc (sizeof(DelayLine));

	dl->P = P;
	dl->Q = Q;	
	dl->pin = 0;
	dl->aa = aa;
	dl->dmax = dmax;
	dl->dd = dd;
	dl->rr = (real **) malloc (P * sizeof(real *));

	// Ring buffers initialized with zeros
	for (i = 0; i < P; i++)
	{
		dl->rr[i] = (real *) calloc (dmax, sizeof(real));
	}
	
	dl->finishing = 0;
	dl->more = 0;
    dl->samplingFreq = samplingFreq;
    dl->frameLength = frameLength;

	dl->ppout = (int **) malloc (P * sizeof(int *));
	for (i = 0; i < P; i++)
	{
		dl->ppout[i] = (int *) malloc (Q * sizeof(P));
    }

    dl->outputSamplesWrapped = (int **) malloc (P * sizeof(int *));
	for (i = 0; i < P; i++)
	{
		dl->outputSamplesWrapped[i] = (int *) calloc (Q, sizeof(P));
    }
#ifdef USE_OMP
#pragma omp parallel for
#endif
	for (i = 0; i < P; i++)
	{
		for (j = 0; j < Q; j++)
		{
			dl->ppout[i][j] = (int) ceil(dmax - dd[i][j] - 1);
		}
	}
	dl->updater = (DelayUpdate **) malloc (P * sizeof(DelayUpdate *));
	for (i = 0; i < P; i++)
	{
		dl->updater[i] = (DelayUpdate *) calloc (Q, sizeof(DelayUpdate));
	}
	cycinc(dl->ppout, dmax, P, Q);
	dl->updatesActive = 0;
	//dl->mutex = CreateMutex(NULL, FALSE, NULL);
	return (dl);
}

//function delay = freedelayline(delay)
void DelayLine_free(DelayLine* dl) {

	int i;

	for (i = 0; i < dl->P; i++)
	{
		free(dl->rr[i]);
	}
	free(dl->rr);

	for (i = 0; i < dl->P; i++)
	{
		free (dl->ppout[i]);
	}
	free(dl->ppout);

    for (i = 0; i < dl->P; i++)
	{
		free (dl->outputSamplesWrapped[i]);
	}
	free(dl->outputSamplesWrapped);

    
	
	for (i = 0; i < dl->P; i++)
	{
		free(dl->updater[i]);
	}
	free(dl->updater);
	// CloseHandle(dl->mutex);
	free(dl);	
}

//function n = cycinc(n, nmax)
void cycinc(int** indices, int cycle, int P, int Q) {
    int i, j;
	
	// only matrix case needed as 0-based module = a % b
#ifdef USE_OMP
	#pragma omp parallel for
#endif
    for (i = 0; i < P; ++i) {
        for (j = 0; j < Q; ++j) {
            indices[i][j] = indices[i][j] % cycle;
			indices[i][j]++;
        }
    }
}


//no matlab function yet
void DelayLine_updateStep(DelayLine* dl) {
	
	int i, j;
	real auxDelay;
	DelayUpdate up;	

#ifdef USE_OMP
	#pragma omp parallel for
#endif
	for (i = 0; i < dl->P; i++)
	{
		for (j = 0; j < dl->Q; j++)
		{
			// enter synchronised section

			// WaitForSingleObject(dl->mutex, INFINITE);
			if (dl->updater[i][j].active)
			{
				up = dl->updater[i][j];
				auxDelay = dl->dd[i][j];
				up.step++;
				// end of transition reached?
				if (up.step >= up.steps)
				{
					// inactive update
					up.step = -1;
					dl->dd[i][j] = up.d2;
					// set gain to target size
					dl->aa[i][j] = up.a2;
					up.active = 0;
					dl->updatesActive--;
				}
				else
				{
					// increment delay					
					dl->dd[i][j] = dl->dd[i][j] + up.diffd;
					// int truncates to integer, so to round, just add 0.5 before truncating
				}
				// if integer change in delay
				if (floor(auxDelay) == floor(dl->dd[i][j] + 1))
				{
					dl->ppout[i][j] = dl->ppout[i][j] % dl->dmax;
					dl->ppout[i][j]++;
				}
				else if (floor(auxDelay) == floor(dl->dd[i][j] - 1))
				{
					// TODO: this could be combined with the cycinc step in nextsample
					// by "neutralising" it.
					dl->ppout[i][j] = (dl->ppout[i][j] - 1 + dl->dmax) % dl->dmax;
				}				
				dl->updater[i][j] = up;
				// leave synchronised section
				// ReleaseMutex(dl->mutex);				
			}
		}
	}
}

//function delay = updatedelay(delay, p, q, a, d, steps)
void DelayLine_update(DelayLine* dl, int p, int q, real a, real a2, real d, real d2, real diffd, real diffd2, real chunkCarry) {

	//; (!!!) the functionality of DelayLine_update has been inserted into the Wavepropagation_update-method for 
	//; parallelization-issues (OMP);
	//; be sure to verify in case of reactivation of this method, that all modifications, made in Wavepropagation_update 
	//; are applied in here as well; the Wavepropagation_update-method is the up-to-date version!

    int dropSampleOld;
    dl->updater[p][q].d2 = d2;
	dl->updater[p][q].d = d;
	dl->updater[p][q].a2 = a2;
	dl->updater[p][q].a = a;
	  
    //; when treated samplewise, number of steps was rounded up => chunkSize has to be rounded up
    
    //dl->updater[p][q].chunkSize = (int) round(fabs(1.0 / (diffd + eps))); // old, worked 

	//; calculate only, when chunkbased update is occurring 
	if(dl->updater[p][q].chunkBasedUpdate == 1){	
		if (fabs(diffd) > 0){
			dl->updater[p][q].chunkSize = (int) round( fabs(1.0 / diffd) );
		}else{
			dl->updater[p][q].chunkSize =0;
		}
		if (fabs(diffd2) > 0){
			dl->updater[p][q].chunkSize2 = (int) round( fabs(1.0 / diffd2) );
			if(dl->updater[p][q].nonMon == 0){
				dl->updater[p][q].chunkSize = dl->updater[p][q].chunkSize2;
			}
		}else{
			dl->updater[p][q].chunkSize2 =0;
		}
	
		// Doppler-effect: incoming or outgoing source
		dropSampleOld = dl->updater[p][q].dropSample;
		dl->updater[p][q].dropSample = (d < dl->dd[p][q]) ? 1 : 0;

		//so that outputSamplesWrapped is already initialized in the first while-loop of processChunk()		
		if ( (chunkCarry < 0) || (chunkCarry >= 1)){
			dl->outputSamplesWrapped[p][q] = dl->updater[p][q].chunkSize; 
		}else{
			if(dropSampleOld == dl->updater[p][q].dropSample){
				dl->outputSamplesWrapped[p][q] = (int) round(dl->updater[p][q].chunkSize / (1.0 + chunkCarry));
			}else{
				dl->outputSamplesWrapped[p][q] = (int) round(dl->updater[p][q].chunkSize / (1 - chunkCarry));
			}
		}

		// determine the delay-difference between start and end-point of update		
		dl->updater[p][q].steps = (int) round(fabs(d - dl->dd[p][q]));
		dl->updater[p][q].steps2 = (int) round(fabs(d2 - d));

		//; init step-index
		dl->updater[p][q].step = 0;
		//; init nrFrameWrap
		dl->updater[p][q].nrFrameWrap = 1;

	}else{
		//; TODO: check if this is necessary;
		//; when not chunkbased, steps indicates the length of the update in samples!		
		//; init step-index
		dl->updater[p][q].step = 0;
		//; init nrFrameWrap
		dl->updater[p][q].nrFrameWrap = 1;
	
	
	
	} // if(dl->updater[p][q].chunkBasedUpdate == 1)
	
}

//function delay = finishdelay(delay)
void DelayLine_finish(DelayLine* dl) {

	dl->finishing = 1;
	dl->more = dl->dmax - 1;   	
}


int DelayLine_processFrame(DelayLine *dl)
{

#ifndef PROCESS_CHUNK_ONLY
    int k, p, q;	
	int samplesToBufEnd, samplesWrapped;
	real frac = 0;
#endif

	int more = 1;
    
	

	// debug-print-out
	// printf("Updates active: %i \n", dl->updatesActive);

#ifndef PROCESS_CHUNK_ONLY
	if (dl->updatesActive)
    {	
#endif
        // DelayLine_processSample sets the read-/write-indexes (pin,ppout) by itself
		DelayLine_processChunk(dl); // new

					
        //TODO: eventually put to end of function
        if (dl->finishing) {
            dl->more = dl->more - dl->frameLength;
	        more = dl->more;
        }
   
#ifndef PROCESS_CHUNK_ONLY

     } else { // updatesActive

	    samplesToBufEnd = dl->dmax - dl->pin;

	    if (samplesToBufEnd > dl->frameLength){
		    samplesToBufEnd = dl->frameLength;
	    }	
	    samplesWrapped = dl->frameLength - samplesToBufEnd;

	    //Fill the ring buffer (input)
	    if (dl->finishing){
#ifdef USE_OMP
#pragma omp parallel for shared(dl->rr)
#endif
		    for (p = 0; p < dl->P; p++){
                zeroRealVec(dl->rr[p] + dl->pin, samplesToBufEnd);

			    if (samplesWrapped > 0){
				    zeroRealVec(dl->rr[p], samplesWrapped);
			    }			
		    }
		    dl->more = dl->more - dl->frameLength;
		    more = dl->more;
	    } else {
#ifdef USE_OMP
#pragma omp parallel for 
#endif
		    for (p = 0; p < dl->P; p++){			
			    memcpy(dl->rr[p] + dl->pin, dl->xxframe[p], samplesToBufEnd * sizeof(real));

			    if (samplesWrapped > 0) {
				    memcpy(dl->rr[p], dl->xxframe[p] + samplesToBufEnd, samplesWrapped * sizeof(real));
			    }
		    } // for p

	    } // if (finishing)

#ifdef USE_OMP
#pragma omp parallel for
#endif

        for (q = 0; q < dl->Q; q++){
	            zeroRealVec(dl->yyframe[q], dl->frameLength);  // init output-frame-buffer to zero
        }

//; openMP_test
//#ifdef USE_OMP
#pragma omp parallel for private(k)
//#endif
	    for (p = 0; p < dl->P; p++)
	    {
		    for (q = 0; q < dl->Q; q++)
		    {
			    for (k = 0; k < dl->frameLength; k++)
			    {
                    // dd[][] is counted in samples, respectively fractions of samples
                    // (depending on the calculation of dd in main.c)
#ifdef USE_FRACTIONAL_DELAYS
					// begin [case 1]: fractional samples in the delay are considered -->
					frac = dl->dd[p][q] - (int) dl->dd[p][q];
				    dl->yyframe[q][k] = dl->yyframe[q][k] + ( dl->rr[p][(dl->ppout[p][q] - 1 + k + dl->dmax) % dl->dmax] * frac +
												     dl->rr[p][(dl->ppout[p][q]     + k + dl->dmax) % dl->dmax] * (1 - frac) )
											      *  dl->aa[p][q];
										// end [case 1]: fractional samples in the delay are considered <--
#else
					// begin [case 2]: fractional samples in the delay are neglected -->
					dl->yyframe[q][k] = dl->yyframe[q][k] + 
										( dl->rr[p][(dl->ppout[p][q] + k + dl->dmax) % dl->dmax] )  *  dl->aa[p][q];
					
					// end [case 2]: fractional samples in the delay are neglected <--
#endif

				    // TODO: All-pass filter
			    } // for k
		    } // for q
	    } // for p

	    for (k = 0; k < dl->frameLength; k++)
	    {
		    cycinc(dl->ppout, dl->dmax, dl->P, dl->Q);
	    }

	    // @matlab unidimensional cycinc
	    dl->pin = (dl->pin + dl->frameLength) % dl->dmax;

    	
    } // else updatesActive
#endif
    return more;
} 

int DelayLine_processSample(DelayLine *dl, real *xxsamp, real *yysamp)
{
	int i, j, more = 1;
	real frac;		

	//Fill the ring buffer (input)
	if (dl->finishing)
	{
#ifdef USE_OMP
#pragma omp parallel for
#endif
		for (i = 0; i < dl->P; i++)
		{
			dl->rr[i][dl->pin] = 0;			
		}
		
	} //if (dl->finishing)
	else
	{
#ifdef USE_OMP
#pragma omp parallel for
#endif
		for (i = 0; i < dl->P; i++)
		{
			dl->rr[i][dl->pin] = xxsamp[i];			
		}
	}
	
#ifdef USE_OMP
#pragma omp parallel for
#endif
	for (i = 0; i < dl->P; i++)
	{
		for (j = 0; j < dl->Q; j++)
		{
			frac = dl->dd[i][j] - (int) dl->dd[i][j];
			yysamp[j] = yysamp[j] + (dl->rr[i][(dl->ppout[i][j] - 1 + dl->dmax) % dl->dmax] * frac +
									 dl->rr[i][(dl->ppout[i][j]     + dl->dmax) % dl->dmax] * (1 - frac))
								  *  dl->aa[i][j];
			// TODO: All-pass filter		
		}
	}

	cycinc(dl->ppout, dl->dmax, dl->P, dl->Q);

	// @matlab unidimensional cycinc
	dl->pin = (dl->pin + 1) % dl->dmax;

	return more;
}


 int DelayLine_processChunk(DelayLine *dl) {

	int k, p, q, l, more = 1;
	int samplesToBufEnd, samplesWrapped, samplesToOutputBufEnd;	

#ifdef USE_FRACTIONAL_DELAYS
	real frac;
#endif	

//; time-measurement begin------>>>
#ifdef STOPWATCH
	//time variables
	double t;
	double t_min_delayLine, t_max_delayLine;
	double t_min_total, t_max_total;
	
	
#endif	


#ifdef STOPWATCH
	//;time variables
	t_min_delayLine = 100.; //init to value likely to be replaced
	t_max_delayLine = 0.; //init to value likely to be replaced
	
	t_min_total = 100.; //init to value likely to be replaced
	t_max_total = 0.; //init to value likely to be replaced
	

	//;time print-out
	//printf("Frame-time : %f ms", (float)(1000.*(float)runParams->frameLength / ((float)runParams->conf->samplingFreq) ) );
	printf("\n NEW FRAME------------------------------------------: \n\n");
#endif
//; time-measurement ends------<<<

	//; debug-test-printout
	//printf("||++||");

	// @param: samplesToBufEnd = samples left to delay-line ring-buffer-end
	samplesToBufEnd = dl->dmax - dl->pin; 
    
	if (samplesToBufEnd > dl->frameLength) {
		samplesToBufEnd = dl->frameLength;
	}	
	samplesWrapped = dl->frameLength - samplesToBufEnd;
    
		///////////////////////////////////////
		//////Fill it from wave buffers////////
		///////////////////////////////////////
		
       
        if (dl->finishing){
#ifdef USE_OMP
#pragma omp parallel for 
#endif
			
		    for (p = 0; p < dl->P; p++){
                zeroRealVec(dl->rr[p] + dl->pin, samplesToBufEnd);

			    if (samplesWrapped > 0){
				    zeroRealVec(dl->rr[p], samplesWrapped);
			    }			
		    }
		    dl->more = dl->more - dl->frameLength;
		    more = dl->more;
	    } else {
#ifdef USE_OMP
#pragma omp parallel for 
#endif
			
		    for (p = 0; p < dl->P; p++)
		    {	
				memcpy(dl->rr[p] + dl->pin, dl->xxframe[p], samplesToBufEnd * sizeof(real));
			    
				if (samplesWrapped > 0) {
				    memcpy(dl->rr[p], dl->xxframe[p] + samplesToBufEnd, samplesWrapped * sizeof(real));
				} 					
				
		    } // for p
	    } // if finishing

		///////////////////////////////////////
		//////Fill it from wave buffers////////
		///////////////////////////////////////	

#ifdef USE_OMP
#pragma omp parallel for 
#endif      
		
		//#pragma omp parallel for shared(dl)
        for (q = 0; q < dl->Q; q++){
	        zeroRealVec(dl->yyframe[q], dl->frameLength);  // init output-frame-buffer to zero     
        }

		dl->pin = (dl->pin + dl->frameLength + dl->dmax) % dl->dmax;

#ifdef USE_OMP
	#pragma omp parallel for 
#endif	

#ifdef STOPWATCH
			//time measurement for delayLine starts here
			CTimeMeasurement_start();
#endif	
			//; #pragma omp parallel saves lots of time here
			for (p = 0; p < dl->P; p++) {

				#pragma omp parallel for shared(dl) private(l,k)

				for (q = 0; q < dl->Q; q++) {

					//; for OMP each thread has to have it's own copy of variables,...
					//; ...so that no congestion due to memory-accesses occurs 
					DelayUpdate up;
					int outputSamplesWrapped;
					int frameLength;
					int ppout;
					int dmax;
					real aa;
					real dd;
					real *yyframe;
					real *rr;								

					up = dl->updater[p][q];
					outputSamplesWrapped = dl->outputSamplesWrapped[p][q];
					frameLength = dl->frameLength;
					ppout = dl->ppout[p][q];
					dmax = dl->dmax;
					aa = dl->aa[p][q];
					dd = dl->dd[p][q];
					yyframe = dl->yyframe[q];
					rr = dl->rr[p];					

					if ( (up.active == 1) && (up.chunkBasedUpdate == 1 ) ) {
						
						int ppOutBuf = 0; // has to be reset when processing the next output frame
						//at the beginning: outputSamplesWrapped = chunkSize						
                        while (ppOutBuf + outputSamplesWrapped < frameLength) { 
							
							// transfer of one chunk from the delayLine to the output-buffer
							for ( l = 0; l < outputSamplesWrapped; l++) {							

								yyframe[ppOutBuf + l] = yyframe[ppOutBuf + l] + rr[(ppout + l) % dmax] * aa;								
								
							}
#ifdef STATS	
	flops.adds += 3*l;
	flops.mults += l;
#endif							

							// reassign the pointers according to doppler-shift
                            if ( up.active){

                                if (up.dropSample ) { // for the case that source is coming nearer: drop one sample
								    ppout = (ppout + outputSamplesWrapped + 1) % dmax;	
									dd-- ;
#ifdef STATS	
	flops.adds += 3;	
#endif
							    }
							    else { //for the case that source is moving away: repeat one sample
								    ppout = (ppout + outputSamplesWrapped - 1) % dmax;
									dd++ ;
#ifdef STATS	
	flops.adds += 3;	
#endif
							    }

								//; after dropping or repeating a sample, increase the step-counter
								up.step++;
#ifdef STATS	
	flops.adds += 1;	
#endif

								//; critical section for parallelization
								//; this must be executed by only one thread at a time
								//; in order to keep "dl->updatesActive" consistent
								
								#pragma omp critical

								{ 
								
                                DelayLine_updateChunk(dl, &up, &dd, &aa, p, q); 
								
								}
								

                            } else{
                                ppout = (ppout + outputSamplesWrapped) % dmax;							

                            } //if (up.active)

							ppOutBuf = ppOutBuf + outputSamplesWrapped;
							
                            outputSamplesWrapped = up.chunkSize; // now the loop continues with chunkSize!
						} // while
                        
                        // exception for d-dd[p][q] = 0
                        // TODO: functionality substituted by non-monotonic Doppler-shift, but left for testing 
                        if(up.steps == 0){
							//; critical section for parallelization
							//; this must be executed by only one thread at a time
							//; in order to keep "dl->updatesActive" consistent

							
                            #pragma omp critical

								{ 
								
                                DelayLine_updateChunk(dl, &up, &dd, &aa, p, q); 
								
								}
								

							//DelayLine *dl, DelayUpdate *updaterIn, real *aa, int p, int q
                        }

						//nrFrameWrap needed if chunkSize > 2 * frameLength						
						//outputSamplesWrapped = ppOutBuf + outputSamplesWrapped - up.nrFrameWrap * frameLength;
						outputSamplesWrapped = ppOutBuf + outputSamplesWrapped - frameLength;
						samplesToOutputBufEnd = frameLength - ppOutBuf; //TODO: framelength-1 better ?!
#ifdef STATS	
	flops.adds += 3;	
#endif
						
						// write the rest of the results to the output-buffer
						for (l = 0; l < samplesToOutputBufEnd; l++) {
							yyframe[ppOutBuf + l] = yyframe[ppOutBuf + l] + rr[(ppout + l) % dmax] * aa;
						}
#ifdef STATS	
	flops.adds += l;	
	flops.mults += l;
#endif
	
						ppout = (ppout + samplesToOutputBufEnd) % dmax;						

                    } //if (up.active && chunkBased)
					else{
						// same as in processFrame()
						for (k = 0; k < frameLength; k++) {
                            
#ifdef USE_FRACTIONAL_DELAYS							
							frac = dl->dd[p][q] - (int) dl->dd[p][q];
							yyframe[k] = yyframe[k] + (frac      * rr[(ppout - 1 + k + dmax) % dmax] +
																					(1 - frac) * rr[(ppout + k + dmax) % dmax]) * aa;
#else
							yyframe[k] = yyframe[k] + (rr[(ppout + k + dmax) % dmax]) * aa;
														
#endif //USE_FRACTIONAL_DELAYS	
								
						}// for (k = 0; k < frameLength; k++)
#ifdef STATS	
	flops.adds += 3*k;
	flops.mults += k;
#endif

						//; if a non-chunkBased update is active, decrease step-counter
							if(up.active == 1){
								//; TODO: insert an own version of DelayLine_update here;
								//; account for nonMonotonic, non-chunkbased updates as well 
								up.step += frameLength;
#ifdef STATS	
	flops.adds += 1;	
#endif
								if(up.step > up.steps){
									up.active = 0;
									dl->updatesActive--;
								}
																
							}

						ppout = (ppout + frameLength + dmax) % dmax;
					} // if (updater.active)
				
#ifdef DEBUG_OUTPUT                        
                        // test-print-out: begin -->
                         printf("\n\nnew dd[%i][%i]: %2.4f\n", p,q, dl->dd[p][q]);
                         printf("new aa[%i][%i]: %2.4f", p,q, aa);
                        // test-print-out: end <-- 

#endif

				dl->updater[p][q] = up ;
				dl->outputSamplesWrapped[p][q] = outputSamplesWrapped;
				dl->ppout[p][q] = ppout;
				dl->dd[p][q] = dd;
								
			} // q

        } // p ,parallel for
		

#ifdef STOPWATCH
			//time measurement stops here and evaluates
			CTimeMeasurement_stop();
			t = CTimeMeasurement_getMilliseconds();
			if (t > t_max_delayLine) t_max_delayLine = t;
			if (t < t_min_delayLine) t_min_delayLine = t;

			// at times report performance
			
				printf("processChunk:\n");
				printf("min: %2.12lf ms\n", t_min_delayLine);
				printf("max: %2.12lf ms\n", t_max_delayLine);				
				// re-init min & max
				t_min_delayLine = 100.; //init to value likely to be replaced
				t_max_delayLine = 0.; //init to value likely to be replaced				
			
#endif
		
    return more;
}


int DelayLine_updateChunk(DelayLine *dl, DelayUpdate *updaterIn, real *dd, real *aa, int p, int q) {
	
	DelayUpdate up;
	up = *updaterIn;

	if ( up.step >= up.steps ) { // if ending conditions reached (plural s of chunkSteps!)
		up.step = 0;
		
		*dd = up.d;
		
		*aa = up.a;
        // up.a2 is (-1) in case there is no non-monotonic doppler-shift
        if ( up.nonMon <= 0 ){
            up.active = 0;
            dl->updatesActive--;
        }else{ 
			//; start second phase of non-monotonic update
            up.chunkSize = up.chunkSize2;
            up.steps = up.steps2;
			//; set dropsample-flag according to target-delays
			up.dropSample = (up.d2 < up.d) ? 1:0;
            up.d = up.d2;
            up.a = up.a2;			
			
			// set nonMon-flag to zero
            up.nonMon --;

			up.diffd = up.diffd2;
            
        }                
	}

	up.nrFrameWrap = 1; // nrFrameWrap has to be reset after having processed one complete chunk	
	*updaterIn = up;

    return 1;
}

