#ifndef WAVEIO_H
#define WAVEIO_H

#include "mymath.h"
#include "config.h"
#include "wfsAudioRun.h"

  
  // load buffers "inputSignals" from file-names given in the Configuration
  int wav_load(Configuration *conf, real** inputSignals);

  int wav_store(AudioRunParams* runParams);

#endif
