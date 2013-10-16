#ifndef TYPES_DONE
#define TYPES_DONE

#include "param.h"
  
typedef int  TNumOfBlocks;
typedef int  TPixel;

enum _TBlockType   {RGB,YUV};
typedef enum _TBlockType TBlockType;

typedef struct TBlockData 
{
  TPixel pixel[BLOCKSIZE];
} TBlockData;


typedef struct TBlocks
{
  TBlockData Y1;
  TBlockData Y2;
  TBlockData U1;
  TBlockData V1;
} TBlocks;

typedef struct TBitStreamPacket
{
  int marker;
  int byte[PACKETSIZE];
} TBitStreamPacket;

typedef struct TPackets
{
  TBitStreamPacket packet[64];
} TPackets;

typedef struct TFrameSize
{
  int Hor;
  int Ver;
} TFrameSize;

typedef struct THeaderInfo
{
  TFrameSize   FrameSize;
  TNumOfBlocks NumOfBlocks;
  TBlockType   BlockType;
} THeaderInfo;

typedef struct TQTables
{
  int QCoef[BLOCKSIZE];
} TQTables;

typedef struct THuffTablesAC
{
  int ACcode[257];
  int ACsize[257];
} THuffTablesAC;

typedef struct THuffTablesDC
{
  int DCcode[257];
  int DCsize[257];
} THuffTablesDC;


typedef struct TTablesInfo
{
  TQTables    QTable;
  int DCHuffBits[17];
  int DCHuffVal[257];
  int ACHuffBits[17];
  int ACHuffVal[257];

} TTablesInfo;

#endif
