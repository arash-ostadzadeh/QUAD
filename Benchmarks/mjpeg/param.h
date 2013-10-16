/*
***********************************************************
param.h

The basic system parameters of M_JPEG* are kept here.

***********************************************************
*/

#ifndef PARAM_DONE
#define PARAM_DONE

/*
 This is the general definition for the size and width of the
 M_JPEG* blocks.
*/
#define BLOCKSIZE  64
#define BLOCKWIDTH  8
#define BLOCKHEIGHT 8
#define PACKETSIZE  1    // The size of the packet in bits is 8*PACKETSIZE

// This is the minimum compression ratio the M_JPEG* application should support
#define THRESHOLD 100

// Q value is used to rescale quantization matrices.
#define Q_PRECISION 50

// Definitions for M_JPEG* and internal compatibility.
#define MAXIMUM_MJPEG_HORIZONTAL_FREQUENCY 4
#define MAXIMUM_MJPEG_VERTICAL_FREQUENCY 4
#define MAXIMUM_IMAGE_HEIGHT 65535
#define MAXIMUM_IMAGE_WIDTH 65535

/*
 Components: Number of color components that can be active per frame.
 A component consists of one complete plane of the image.
*/
#define MAXIMUM_COMPONENTS 256

/*
 Scan component threshold is the maximum number of color components put
 in per scan
*/
#define SCAN_COMPONENT_THRESHOLD 4

/*
 Number of streams is the number of active read/write streams possible.
 For all M_JPEG* operations, this value is 1.
*/
#define NUMBER_OF_STREAMS 1

#endif

