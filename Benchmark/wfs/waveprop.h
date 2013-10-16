/*
 *
 * "hArtes Reference/Benchmarking Application implementing a MIMO delay line with geometry (Delaytoy)"
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
 * @filename      wavepropagation.h
 *
 * @file          wavepropagation.h
 *
 *                Provides geometry background with a delayline.
 */

#ifndef WAVEPROP_H
#define WAVEPROP_H

#include "mymath.h"
#include "delayline.h"

typedef struct
{	
	// Position vector (meters)
	Vector2d source;
    // Differential vector per sample (meters)
    Vector2d diffSource;
	// destination of moving source
	Vector2d destSource;
    // duration of update in samples
    int tUpdate;
	// indicator, whether the primary source is an inner or outer source;
	// if(inner)->innerSource=1; else innerSource=0;
	int innerSource;
	// if the system is used within an Audio-server-environment, each source has a unique server-ID
	int serverID;
	// distance between the source and the speaker-array
	real sourceArrayDistance;
	// radius around the source, within which speakers are active
	real rActive;
} PrimarySource;

typedef struct
{
	// Source Array
	PrimarySource *sourceArray;
	// Number of primary sources (P)
	int numberOfSources;
} PrimarySourceArray;

typedef struct
{
	// Position vector (meters)
	Vector2d source;	
	// Normal vector, origin is the center of the cylinder
	Vector2d normal;
} SecondarySource;

typedef struct
{
	// Array of speakers
	SecondarySource* speakerArray;
	// Number of speakers (Q)
	int numberOfSpeakers;
} CircularSpeakerArray;

typedef struct
{
	/** active sources */
	PrimarySourceArray* sources;
    /** loudspeaker array */
	CircularSpeakerArray* speakers;
	/** delay line */
	DelayLine *dl;
    /** Speed of Sound */
    real speedSound;
	// causality delay necessary for the representation of inner sources
	int causalityDelay;
	// reference gain of the system;
	// equals the gain of a primary source which is located exactly on the array
	real gainReference;
} WavePropagation;

PrimarySource PrimarySource_init(real x, real y, real r, int type, int serverID);

PrimarySource PrimarySource_deriveTransitionProperties( real r, real speakerDistance, int arrayType, PrimarySource primSource );

real calculateGainPQ(PrimarySource sourceIn, SecondarySource speakerIn, int type, real r, real speakerDistance, real gainReference);

PrimarySourceArray* PrimarySourceArray_init(real *x, real *y, int sourceNumber, real r, int type);

void PrimarySourceArray_free(PrimarySourceArray *sources);

SecondarySource SecondarySource_init(real x, real y, real nx, real ny);

CircularSpeakerArray* CircularSpeakerArray_init(real *x, real *y, real *nx, real *ny, int speakerNumber);

void CircularSpeakerArray_free(CircularSpeakerArray *speakers);

WavePropagation* WavePropagation_init(PrimarySourceArray *sources, CircularSpeakerArray *speakers, DelayLine *dl, real speedSound, int causalityDelay, real gainReference);

void WavePropagation_free(WavePropagation *waveProp);

void WavePropagation_update(WavePropagation *waveProp, real x, real y, real speed, int id, real speedSound, real r, int type, real speakerDistance);

void WavePropagation_updateStep(WavePropagation *waveProp);

int WavePropagation_processFrame(WavePropagation *waveProp);

int WavePropagation_processSample(WavePropagation *waveProp, real *xxsamp, real *yysamp);



#endif // WAVEPROP_H
