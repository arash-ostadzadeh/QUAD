  /* ********Wav-Loader for the WFS-system *********
  * - takes a configuration and buffer-pointers as arguments
  * - reads the .wav-files given in the configuration
  * - stores the wav-content into the buffers
  * - preferred format is 16bit, 44.1kHz, mono
  *
  */

#include <math.h>
#include <stdio.h>
#include "config.h"
#include "wfsAudioRun.h"
#include "waveIO.h"

// return status
//#define WAV_REPORT

// windows: supress insecure warnings
#pragma warning( disable : 4996 )

/*#ifdef __LINUX__
// omit any sleep (real-time simulation)
//#include <stdlib.h>
#define sleep(x) //sleep(x)
#else
#include <windows.h>
#define sleep(x) Sleep(x)
#endif
*/

#define round(a) floor( a + 0.5 )
  
int wav_load(Configuration *conf, real** inputSignals){
	
      int wavSamplingFreq;
	  short int wavNumChannels;
	  short int wavBitsPerSample;
	  int wavByteRate;
	  short int wavFormatTag;	  
	  short int wavBlockAlign;
	  char wavKeyword[4];
	  int wavDataLength;
	  int wavChannelLength;
	  //int p, j;
	  int wavBytesPerSample;
	  short int wavTempSampleInt;
	  real wavTempSampleReal;      
	  // wav-input-file	  
	  FILE *wavSrc ;
      
	  int i ;
	  int j ;
	  // int p ;	
	
	  //; report status
	  printf("\nLoading local input Wav-files ... \n");
		// if input-specs are being read from multichannel-wav-file-header
		// this loop is obsolete
	for (i = 0; i < conf->P; i++){

	  wavSrc = fopen(conf->wavNames[i], "rb"); // file names from config.txt
	  
	  //; report status
	  printf("\nchannel: %i", i);

	  if (wavSrc == NULL) {
			printf("Input-file not found. Exiting...\n");
			return 0;
	    }
	 	
	  // wavKeyWord is an array, so it returns it's address automatically
	  //should be "RIFF"
	  fread(wavKeyword,4,1,wavSrc);
	  fread(wavKeyword,4,1,wavSrc);
	  
	  //should be "WAVE"
	  fread(wavKeyword,4,1,wavSrc);
	  
	  //should be "fmt "
	  fread(wavKeyword,4,1,wavSrc);
	  fread(wavKeyword,4,1,wavSrc);
	  
	  // read actual parameters
	  fread(&wavFormatTag,2,1,wavSrc);
	  fread(&wavNumChannels,2,1,wavSrc);
	  // exit, if wav-file is not mono
	  if(wavNumChannels != 1){
		printf("Input-file has more than one channel. Exiting...\n");
		return 0;
	  }

	  fread(&wavSamplingFreq,4,1,wavSrc);
	  fread(&wavByteRate,4,1,wavSrc);
	  fread(&wavBlockAlign,2,1,wavSrc);
	  fread(&wavBitsPerSample,2,1,wavSrc);
	  
	  //should be "data"
	  fread(wavKeyword,4,1,wavSrc);
	  // data-chunk-length
	  fread(&wavDataLength,4,1,wavSrc);
	  
	  // length of one channel in [samples]
	  wavChannelLength = (wavDataLength / wavBlockAlign);
	  wavBytesPerSample = wavBitsPerSample / 8;


	  if (conf->quantBits != wavBitsPerSample) {
			  printf("\nWARNING: WAV-file quantization differs from config setting...\n");
		  }

	  if ( wavBitsPerSample == 16 ) {
		  //wavScaleFactor = 1. ; // TODO: set this back to 32768. when 32bit is supported!
		  conf->wavScaleFactor = 32768. ;		  
		  //wavScaleFactor = 32768. ;
	  } else if ( wavBitsPerSample == 32 ) {
		//wavScaleFactor = 1. ;
		  conf->wavScaleFactor = 1. ;
	  } else {
		  printf("WARNING: this system can not process quantization other than 16bit or 32bit! \n");
		  return 0;
	  }	    

	  // for compressed wave-files
	  // TODO: to be implemented yet
	  if(wavFormatTag == 3){

		  for (j = 0; j < conf->inputChannelLength; j++){
			  
			fread(&wavTempSampleReal, wavBytesPerSample, 1, wavSrc );
			inputSignals[i][j] = (real) (wavTempSampleReal);
			  
		  }

	  }
	  // for uncompressed wave-files
	  else if(wavFormatTag == 1){
          
		  if ( wavBitsPerSample == 16 ) {
			  for (j = 0; j < conf->inputChannelLength; j++){
				  
				fread(&wavTempSampleInt, wavBytesPerSample, 1, wavSrc );
				inputSignals[i][j] = (real) (wavTempSampleInt / conf->wavScaleFactor );			    
				  
			  }
		  } else if ( wavBitsPerSample == 32) {
				for (j = 0; j < conf->inputChannelLength; j++){
				  
				fread(&wavTempSampleReal, wavBytesPerSample, 1, wavSrc );
				inputSignals[i][j] = (real) (wavTempSampleReal / conf->wavScaleFactor );			    
				  
			  }
		  }
	  }
	  
	  else{
		printf("Format-Tag invalid. Exiting...\n");
		return 0;
	  }
	  
	  fclose(wavSrc);

#ifdef WAV_REPORT
	  printf(".wav-file read: %s\n", conf->wavNames[i]);
#endif
	  

	}	// for (i=0; i<conf->P, i++) 
		
	return 1;
//--------------------------------------------end of wav-input<--

}

int wav_store(AudioRunParams* runParams){

	//variables for wave-file output:
    float wavSample;
    short int wavSampleInt;
    FILE *wavFile;
    // variable holding wave-file specifications for output
    int wavTempInt;
	int j, q;
    short int wavTempShort;

	wavFile = fopen("WfsOutputChannels.wav", "wb");
    //init variables
    wavTempInt = 0;
    wavTempShort = 0;
    wavSample =0.0;
    wavSampleInt = 0;
    
    // wave-header
    fputs("RIFF", wavFile);
    // chunk-size total    
	wavTempInt = (int) runParams->conf->Q * (runParams->conf->quantBits / 8) * (runParams->inputChannelLength + runParams->maxDelay + runParams->hlen) + 36; // 
    fwrite(&wavTempInt, sizeof(int),1, wavFile);
    //
    fputs("WAVE", wavFile);
    fputs("fmt ", wavFile);
    // subchunk1 size
    wavTempInt = 16;
	
    fwrite(&wavTempInt, sizeof(int),1, wavFile);
    // audio-format (PCM)
    // 1=pcm; 3=ieee-float
	wavTempShort = ( runParams->conf->quantBits == 32 ) ? 3 : 1 ;
    fwrite(&wavTempShort, sizeof(short int),1, wavFile);
    // number of channels
    wavTempShort = (short int) runParams->conf->Q;
    fwrite(&wavTempShort, sizeof(short int),1, wavFile);
    // sampling rate
    wavTempInt = (int) runParams->conf->samplingFreq;
    fwrite(&wavTempInt, sizeof(int),1, wavFile);
    // byte-rate: samplingFreq * 4 * channels; 4 means 4*8=32bit resolution    
	wavTempInt = (int) (runParams->conf->samplingFreq * ( runParams->conf->quantBits / 8 ) * runParams->conf->Q); 
    fwrite(&wavTempInt, sizeof(int),1, wavFile);
    // block align
    //wavTempShort = (short int) conf->Q * sizeof(wavSample); // 32 bit
    //wavTempShort = (short int) (runParams->conf->Q * sizeof(wavSampleInt)); // 16 bit
	wavTempShort = (short int) ( runParams->conf->Q * ( runParams->conf->quantBits / 8 ) ); 
    fwrite(&wavTempShort, sizeof(short int),1, wavFile);
    // bits per sample:
    //wavTempShort = (short int) sizeof(wavSample) * 8; // for 32 bit
    //wavTempShort = (short int) sizeof(wavSampleInt) * 8; // for 16 bit
	wavTempShort = (short int) runParams->conf->quantBits; 
    fwrite(&wavTempShort, sizeof(short int),1, wavFile);
    //data chunk
    fputs("data", wavFile);
    // subchunk2 size
    //wavTempInt = (int) runParams->conf->Q * sizeof(wavSampleInt) * (runParams->inputChannelLength + runParams->maxDelay + runParams->hlen);
	wavTempInt = (int) runParams->conf->Q * ( runParams->conf->quantBits / 8 ) * (runParams->inputChannelLength + runParams->maxDelay + runParams->hlen);
    fwrite(&wavTempInt, sizeof(int),1, wavFile);
        
    for (j = 0; j < (runParams->inputChannelLength + runParams->maxDelay + runParams->hlen); j++){
			
		if ( runParams->conf->quantBits == 16 ) {	

			for (q = 0; q < runParams->conf->Q; q++){
	                
					//write to wave as 32bit-float
					//wavSample = (float) (round(runParams->outputSignals[q][j]));
					//fwrite(&wavSample, sizeof(wavSample),1, wavFile);

					// this version works for 64-bit-float-values
					//fwrite(runParams->outputSignals[q]+j, sizeof(real),1, wavFile);

					// simple alternative for testing: works
					//fprintf(wavFile, "%3.0f ", runParams->outputSignals[q][j]);	                
					//write to wave as 16bit-int
					wavSampleInt = (short int) round(runParams->outputSignals[q][j] * runParams->conf->wavScaleFactor);
					fwrite(&wavSampleInt, sizeof(wavSampleInt),1, wavFile);
			}

		} else if ( runParams->conf->quantBits == 32 ) {

			for (q = 0; q < runParams->conf->Q; q++){
	                
					//write to wave as 32bit-float
					wavSample = (float) (runParams->outputSignals[q][j]);
					fwrite(&wavSample, sizeof(wavSample),1, wavFile);

					// this version works for 64-bit-float-values
					//fwrite(runParams->outputSignals[q]+j, sizeof(real),1, wavFile);

					// simple alternative for testing: works
					//fprintf(wavFile, "%3.0f ", runParams->outputSignals[q][j]);
	                
					//write to wave as 16bit-int
					//wavSampleInt = (short int) round(runParams->outputSignals[q][j]);
					//fwrite(&wavSampleInt, sizeof(wavSampleInt),1, wavFile);
			}

		} else {
			printf("\nOutput-format is incompatible to system!\n");
		}
    }
    fclose(wavFile);
#ifdef WAV_REPORT
	  printf("output-.wav-file written\n");
#endif
	return 1;
    // wav-output end <--
	
}
