hArtes benchmark application implementing wave field synthesis

@author fabian logemann (fraunhofer), gregor heinrich (fraunhofer & arbylon), andres perez (fraunhofer)
@date 20080130

This is version 0.1 of the WFS1 benchmark application, a C-based, self-contained wave-field 
synthesis system. Algorithmic explanations are given in hArtes Deliverable D3.1. 

Quickstart 

Files. 

 * A Visual Studio 2005 project file: tolstoy2.vcproj

 * Source files and headers: 

  - wfs1-c.vcproj (Visual Studio 2005 project file; replace with appropriate Makefile if necessary)

  - wfs1-host.vcproj (Visual Studio 2005 project file; contains the former main.c of wfs1-c.vcproj and therefor calls wfs1-c.vcproj)

  - signalRamp.txt, signalSine.txt (samples of one channel for the sine and ramp inputs; are duplicated for each input)

  - outputRamp.txt (reference output for the ramp input signal, which can be compared to output.txt written by the programm)

  - main.c (main program and main functions)

  - audioinput.h (memory-based input of parameters and audio)

  - config.h, config.c (file-based configuration, will be replaced by memory-based configuration if necessary)

  - audioio.h, audioio.c (define and implement audio input/output interface)

  - mymath.h, mymath.c (define and implement mathematical functions required)

  - filter.h, filter.c (define and implement a frequency-domain FIR filter)

  - delayline.h, delayline.c (define and implement a multichannel delayline with updating)

  - waveprop.h, waveprop.c (define and implement a wave propagation model, based on the delay line)


Build + run. 

If you don’t want to go into the details of the implementation, but want to simply run the application, you can proceed as follows:

 1. Open the project file with Visual Studio 2005.

 2. Compile the project either with Debug or Release Configuration.

 3. Run the application.


Next steps:

 - Improved delayline algorithm

 - More complete documentation

 - OpenMP annotations

 - hArtes toolchain optimisations


Feedback and questions: 

 - Gregor Heinrich, gregor.heinrich@igd.fraunhofer.de: Algorithms, Implementation

 - Fabian Logemann, fabian.logemann@igd.fraunhofer.de: Implementation

