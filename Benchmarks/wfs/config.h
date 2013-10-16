#ifndef CONFIG_H
#define CONFIG_H

#include "mymath.h"
#include "waveprop.h"


// type definitions 
typedef struct 
{
	// Time instant when the update must be done, counted in samples
	int instant;
	// Source to be updated
	int p;
	// Server-ID of the source
	int id;
	// New position
	real x, y;
	// Speed in m/s
	real speed;
} Update;

typedef struct {

	// Type of Audio-Input:
	// "1"=> AudioData is loaded from Asio-Buffers;
	// "0"=> AudioData is read from wav-files
	int AsioStreamInput;
	//; if this flag is set, the client is supposed to track the position of each source and thus...
	//; every update of a channel is neglecting the sourceID and instantiates a new source once per frame
	int clientSourceTrackingMode;
	//; if this flag is set, the incoming positioning updates from acquisition-client are converted from 
	//; cylindrical into cartesian coordinates before being applied to repositioning any sources.
	//; leave this flag set to '0' if no live telepresence is required
	int teleConferenceUpdateConvertingMode;
	//; determines, whether filter processing is done or omitted
	//; "1"=>use filter processing; "0"=>omit filter processing
	int filterEngage;
	//; determines, whether updates are read from the config or transmitted via network
	//; "1"=>get from network; "0"=>get from config
	int useExternUpdates;
	// Number of secondary sources
	int Q;
	// Radius of the cylinder
	real r;
    // Type of array: 0=circular; 1=linear
    // if(type=0)=> r=radius; if(type=1)=> r=length to either side of origin
    int type;
	// dimensions of the virtual room in meters
	real xmin, xmax, ymin, ymax;	
	// Number of primary sources
	int P;
	// Primary sources positions
	PrimarySourceArray *priSources;
	// Number of updates
	int updates;
	// Updates
	Update *updatesArray;
	// time step
	int deltaT;
    //sampling frequency
    int samplingFreq;
    //Frame length
    int frameLength;
    //Input channel length
    //(signalRamp.txt provides a maximum of 48000 samples, but fractions of this length
    // are possible as well)
    long inputChannelLength;
    // Speed of sound
    real speedSound;
	//names of the input-wav-files
	char** wavNames;
	//wave-scaling-factor
	// 16bit-.wav is coded as full-range int
	// 32bit-float is scaled to [-1;+1]
	//...in order to get a decent float-output, 
	//the int-input has to be scaled to float-range
	real wavScaleFactor;
	//quantization bit depth of the input
	int quantBits;
	// gainReference
	// determines the gain of a source which is located exactly on the speaker-array
	real gainReference;
	// distance between two adjacent speakers
	real speakerDistance;
} Configuration;


Configuration *Configuration_init(char *configFile);
void Configuration_free(Configuration *conf);
void Configuration_printConfig(Configuration *conf);

#endif // CONFIG_H
