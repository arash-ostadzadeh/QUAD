#include <stdio.h>
#include <stdlib.h>

#include "delayline.h"
#include "waveprop.h"
//#include "audioinput.h"
#include "audioio.h"
#include "config.h"

// windows: supress insecure warnings
//#pragma warning( disable : 4996 )
//#pragma warning( disable : 4244 )

Configuration *Configuration_init(char *configFile) {
	Configuration *conf;
	FILE *pFile;
	char temp[100];
	int i, aux = 1;
	real *x, *y;
	// declare temporary variable for second-to-samples-conversion
	real *timeInstant;

	char** wavNames;
	// temporary variables for type-casting (real = (float or double))
	float aux1, aux2, aux3, aux4;

	// READING INPUT VALUES
	pFile = fopen(configFile, "r");
	
	if (pFile == NULL) {
		printf("File %s not found. Exiting...\n", configFile);
		return NULL;
	}

	fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}

	conf = (Configuration *) malloc (sizeof(Configuration));
	
	// - for int16 input to int16-output, wavScaleFactor is unity
	// - for int16 input to float32 output, wavScaleFactor is 32768
	// since float32-wav-files are normalized to 1
	//; this is just an initialisation; wavscalefactor will be set according to wav-file resolution
	conf->wavScaleFactor = 1.;

	if ((aux != 0) || (sscanf(temp, "AsioStreamInput=%d ", &conf->AsioStreamInput) != 1)) {
		printf("File config.txt corrupt, type of Audio-Input.\n");
		return NULL;
	}

	fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}

	if ((aux != 0) || (sscanf(temp, "clientSourceTrackingMode=%d ", &conf->clientSourceTrackingMode) != 1)) {
		printf("File config.txt corrupt, clientSourceTrackingMode.\n");
		return NULL;
	}

	fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}

	if ((aux != 0) || (sscanf(temp, "teleConferenceUpdateConvertingMode=%d ", &conf->teleConferenceUpdateConvertingMode) != 1)) {
		printf("File config.txt corrupt, teleConferenceUpdateConvertingMode.\n");
		return NULL;
	}

	fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}

	if ((aux != 0) || (sscanf(temp, "filterEngage=%d ", &conf->filterEngage) != 1)) {
		printf("File config.txt corrupt, filterEngage.\n");
		return NULL;
	}

	fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}

	if ((aux != 0) || (sscanf(temp, "useExternUpdates=%d ", &conf->useExternUpdates) != 1)) {
		printf("File config.txt corrupt, useExternUpdates.\n");
		return NULL;
	}
	
	fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}

	// %lf-format identifier in case that (real = double)
	if ((aux != 0) || (sscanf(temp, "Q=%d r=%f type=%d", &conf->Q, &aux1, &conf->type) != 3)) {
		printf("File config.txt corrupt, speaker array.\n");
		return NULL;
	}
	conf->r = (real)aux1;

	//; determine the distance between two speakers
	//; PI is approx. 3.1416
	if( (conf->type) == 0 ) {
		conf->speakerDistance = (2 * 3.1416) * conf->r / conf->Q ;
	} else {
		conf->speakerDistance = (2 * conf->r) / ( conf->Q -1 ) ;
		
	} 

	fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}
	if ((aux != 0) || (sscanf(temp, "xmin=%f xmax=%f ymin=%f ymax=%f", 
	        &aux1, &aux2, &aux3, &aux4) != 4)) {
		free(conf);
		printf("File config.txt corrupt, room size.\n");
		return NULL;
	}	
	conf->xmin = (real)aux1;
	conf->xmax = (real)aux2;
	conf->ymin = (real)aux3;
	conf->ymax = (real)aux4;
	
	if ((conf->xmax <= conf->xmin) || (conf->ymax <= conf->ymin)) {
		free(conf);
		printf("File config.txt corrupt, room lengths don't match.\n");
		return NULL;
	}

	fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}
	if ((aux != 0) || (sscanf(temp, "P=%d", &conf->P) != 1)) {
		free(conf);
		printf("File config.txt corrupt, number of primary sources.\n");
		return NULL;
	}	
	
	x = (real *) malloc (conf->P * sizeof(real));
	y = (real *) malloc (conf->P * sizeof(real));

	fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}
	for (i = 0; i < conf->P; i++) {
		while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
			fgets(temp, 100, pFile);
		}
        
        if ( (sscanf(temp, "p=%d x=%f y=%f", &aux, &aux1, &aux2) != 3)) {
			free(x);
			free(y);
			free(conf);
			printf("File config.txt corrupt, primary sources parameters.\n");
			return NULL;
		}
		x[i]=(real)aux1;
		y[i]=(real)aux2;

		fgets(temp, 100, pFile);
	}
	conf->priSources = PrimarySourceArray_init(x, y, conf->P, conf->r, conf->type);
	free(x);
	free(y);
	aux = 0;

	fgets(temp, 100, pFile);	
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}
	if ( (sscanf(temp, "gainReference=%f", &conf->gainReference) != 1) ) {
		PrimarySourceArray_free(conf->priSources);		
		free(conf);
		printf("File config.txt corrupt, gainReference.\n");
		return NULL;
	}
	
	fgets(temp, 100, pFile);
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}
	if ((aux != 0) || (sscanf(temp, "nupdates=%d", &conf->updates) != 1)) {
		PrimarySourceArray_free(conf->priSources);		
		free(conf);
		printf("File config.txt corrupt, number of updates.\n");
		return NULL;
	}

	fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}
	if ((aux != 0) != (sscanf(temp, "dt=%d", &conf->deltaT) != 1)) {
		PrimarySourceArray_free(conf->priSources);		
		free(conf);
		printf("File config.txt corrupt, deltaT.\n");
		return NULL;
	}

	conf->updatesArray = (Update *) malloc (conf->updates * sizeof(Update));
	timeInstant = (real*) calloc (conf->updates, sizeof(real));

	for (i = 0; i < conf->updates; i++)	{

		fgets(temp, 100, pFile);
		while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
			if (fgets(temp, 100, pFile) == NULL) {
				if (i != conf->updates - 1) {
					free(conf->updatesArray);
					PrimarySourceArray_free(conf->priSources);										
					free(conf);
					free(timeInstant);
					printf("File config.txt corrupt, updates parameters.\n");
					return NULL;
				}
			}
		}
		 
		if ((aux != 0) || (sscanf(temp, "t=%f p=%d x=%f y=%f v=%f",&aux1, &conf->updatesArray[i].p, 
							&aux2, &aux3, &aux4) != 5)) {
			free(conf->updatesArray);
			PrimarySourceArray_free(conf->priSources);						
			free(conf);
			free(timeInstant);
			printf("File config.txt corrupt, updates parameters.\n");
			return NULL;
		}		
		timeInstant[i] =(real)aux1;
		conf->updatesArray[i].x =(real)aux2;
		conf->updatesArray[i].y =(real)aux3;
		conf->updatesArray[i].speed =(real)aux4;
		//; TODO: by now, ID-changes are not yet implemented;
		//; therefore the chosen ID in the update matches the initialized value of all sources;
		conf->updatesArray[i].id = -1;
	} // for (i = 0; i < conf->updates; i++)

	
    fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}
	if ((aux != 0) || (sscanf(temp, "samplingFreq=%d", &conf->samplingFreq) != 1)) {
		free(conf->updatesArray);
		free(timeInstant);
		PrimarySourceArray_free(conf->priSources);
		free(conf);
		printf("File config.txt corrupt, sampling frequency.\n");
		return NULL;
	}

	fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}
	if ((aux != 0) || (sscanf(temp, "quantBits=%d", &conf->quantBits) != 1)) {
		free(conf->updatesArray);
		free(timeInstant);
		PrimarySourceArray_free(conf->priSources);
		free(conf);
		printf("File config.txt corrupt, Quantization Bit Depth.\n");
		return NULL;
	}


	

    fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}
	if ((aux != 0) || (sscanf(temp, "frameLength=%d", &conf->frameLength) != 1)) {
		free(conf->updatesArray);
		PrimarySourceArray_free(conf->priSources);
		free(timeInstant);
		free(conf);
		printf("File config.txt corrupt, frame length.\n");
		return NULL;
	}

    fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}
	if ((aux != 0) || (sscanf(temp, "inputChannelLength=%ld", &conf->inputChannelLength) != 1)) {
		free(conf->updatesArray);
		PrimarySourceArray_free(conf->priSources);
		free(timeInstant);
		free(conf);
		printf("File config.txt corrupt, input channel length.\n");
		return NULL;
	}

    fgets(temp, 100, pFile);
	// Comments start with #
	while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
		fgets(temp, 100, pFile);		
	}
	if ((aux != 0) || (sscanf(temp, "speedSound=%f", &aux1) != 1)) {
		free(conf->updatesArray);
		PrimarySourceArray_free(conf->priSources);
		free(conf);
		free(timeInstant);
		printf("File config.txt corrupt, speed of sound.\n");
		return NULL;
	}
	conf->speedSound = (real)aux1; 

	if(conf->AsioStreamInput == 0){

	// get the source file names to read from
	// names should have less than 20 characters before the ".wav"
		wavNames = (char**) malloc (conf->P * sizeof(char*));
		for (i = 0; i < conf->P; i++){
			wavNames[i] = (char*) malloc (35 * sizeof(char));
		}
		conf->wavNames = wavNames;

		fgets(temp, 100, pFile);
		while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
			fgets(temp, 100, pFile);		
		}
		for (i = 0; i < conf->P; i++) {
			while (((temp[0] == '#') || (temp[0] == '\n')) && (!(aux = feof(pFile)))) {
				fgets(temp, 100, pFile);
			}
			
			if ( (sscanf(temp, "p=%d name=%s", &aux, wavNames[i]) != 2)) {
				free(conf->updatesArray);
				free(wavNames);
				PrimarySourceArray_free(conf->priSources);
				free(conf);
				free(timeInstant);
				printf("File config.txt corrupt, source file names.\n");
				return NULL;
			}
						
			fgets(temp, 100, pFile);
		}
	}else{ //; if(conf->AsioStreamInput)
		printf("Config in ASIO-streaming mode, no WAV-input read.\n");
	}
    
	// convert time of updates from seconds to samples
	for(i = 0; i < conf->updates; i++){
		conf->updatesArray[i].instant = (int) (timeInstant[i] * conf->samplingFreq); 
	}

	fclose(pFile);
	free(timeInstant);
	return conf;
}

void Configuration_free(Configuration *conf) {
	int i;

	PrimarySourceArray_free(conf->priSources);	
	free(conf->updatesArray);

	if(conf->AsioStreamInput == 0){
		for (i = 0; i < conf->P; i++){
			free(conf->wavNames[i]) ;
		}
		free(conf->wavNames);
	}

	free(conf);
	
}

void Configuration_printConfig(Configuration *conf) {
	int i;

	printf("\nConfiguration");
	printf("\n=============");
	printf("\n\nTime step = %d\n", conf->deltaT);
	if (conf->type == 0) {
		printf("Cylinder Radius : %2.5lf\n", conf->r);
	} else {
		printf("Length of Speaker Array : %2.5lf\n", 2. * conf->r);
	}
	printf("xmin = %2.5lf, xmax = %2.5lf, ymin = %2.5lf, ymax = %2.5lf\n", conf->xmin, conf->xmax, conf->ymin, conf->ymax);
	printf("Primary sources = %d, Secondary sources = %d\n", conf->P, conf->Q);
	for (i = 0; i < conf->P; i++) {
		printf("Source number: %d, x = %2.5lf, y = %2.5lf\n", i + 1, conf->priSources->sourceArray[i].source.x, conf->priSources->sourceArray[i].source.y);
	}
	for (i = 0; i < conf->P; i++){
			printf("source-file [%i]: %s\n", i, conf->wavNames[i]);
		}
	printf("Number of updates: %i\n", conf->updates);
	for (i = 0; i < conf->updates; i++)	{
		printf("Update number: %d, instant = %ld, source = %d, speed = %2.5lf, x = %2.5lf, y = %2.5lf\n", i + 1, conf->updatesArray[i].instant, conf->updatesArray[i].p, conf->updatesArray[i].speed, conf->updatesArray[i].x, conf->updatesArray[i].y);
	}
    printf("Sampling frequency: %d \n", conf->samplingFreq);
    printf("Frame length: %d \n", conf->frameLength);
    printf("Input-Channel length: %ld samples\n", conf->inputChannelLength);
    printf("Speed of sound: %5.2f m/s \n", conf->speedSound);
	printf("\n");
}

