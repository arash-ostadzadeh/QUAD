/*
************************************************************
marker.h

Some basic definitions of commonly occurring markers.

************************************************************
*/

#ifndef MARKER_DONE
#define MARKER_DONE

#define END_QUANTIZATION_TABLE 0xFF
#define END_CODE_TABLE 0xFF

#define MARKER_MARKER 0xff
#define MARKER_FIL 0xff

#define MARKER_SOI 0xd8
#define MARKER_EOI 0xd9
#define MARKER_SOS 0xda
#define MARKER_DQT 0xdb
#define MARKER_DNL 0xdc
#define MARKER_DRI 0xdd
#define MARKER_DHP 0xde
#define MARKER_EXP 0xdf

#define MARKER_DHT 0xc4

#define MARKER_SOF 0xc0
#define MARKER_RSC 0xd0
#define MARKER_APP 0xe0
#define MARKER_JPG 0xf0

#define MARKER_RSC_MASK 0xf8

#endif
