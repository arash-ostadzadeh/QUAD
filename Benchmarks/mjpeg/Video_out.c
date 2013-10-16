#include "Video_out.h"

//mwopen() opens a given filename as the output write stream.
FILE *mwopen(char *filename)
{
	FILE *fh;
	if ((fh = fopen(filename,"wb"))==NULL) {
		printf("\nCannot write output file: %s\n", filename);
	}
	return(fh);
}

//mwclose() closes the output write stream.
void mwclose(FILE *fh)
{
	fclose(fh);
}

//bputc() puts a character to the stream.
void bputc(int c)
{
    compImage[imageIndex++] = c;
}

// WriteSoi() puts an SOI marker onto the stream.
void WriteSoi()
{
	bputc(MARKER_MARKER);
	bputc(MARKER_SOI);
}

// WriteEoi() puts an EOI marker onto the stream.
void WriteEoi()
{
	bputc(MARKER_MARKER);
	bputc(MARKER_EOI);
}

/*
WriteJfif() puts an JFIF APP0 marker onto the stream.  This is a
generic 1x1 aspect ratio, no thumbnail specification.
*/
void WriteJfif()
{
	bputc(MARKER_MARKER);
	bputc(MARKER_APP);
	bputw(16);
	bputc(0x4a); bputc(0x46); bputc(0x49); bputc(0x46); bputc(0x00);
	bputc(0x01); bputc(0x02);   //Version 1.02
	bputc(0x00);                // No absolute DPI
	bputw(1);                   // Aspect ratio
	bputw(1);
	bputc(0x00);                // No thumbnails
	bputc(0x00);
}

// WriteSof() puts an SOF marker onto the stream.
void WriteSof()
{
        int i;

	bputc(MARKER_MARKER);
	bputc(MARKER_SOF|(0x1&0xf));       // Type of encoding = Extended Sequential DCT = 0xC1
	bputw((8+(3*GlobalNumberComponents))); // Frame header length
	bputc(0x08);                       // Sampel precision = 8-bits, 12-bits or 16-bits
	bputw(V_size);                     // Number of lines
	bputw(H_size);                     // Number of samples per line
	bputc(GlobalNumberComponents);     // Number of the components in the frame (Color reprezentation)
	for(i = 0; i < GlobalNumberComponents; i++) {
		bputc(i+1);                    // Store off in index
		bputn(hf[i],vf[i]);            // sub-sampling format
		bputc(tq[i]);                  // Q-table destination selector
	}
}


// WriteSos() writes a start of scan marker.
void WriteSos()
{
        int i;

	bputc(MARKER_MARKER);
	bputc(MARKER_SOS);
	bputw((6+(2*NumberComponents)));
	bputc(NumberComponents);          // Number of components in the scan
	for( i = 0; i<NumberComponents; i++) {
		bputc(ci[i]);                 // Scan component selector
		bputn(td[i],ta[i]);           // DC and AC table destination selectors
	}
	bputc(SSS);                       // Start of spectral or predictor selection
	bputc(SSE);                       // End of spectral selection
	bputn(SAH,SAL);                   // Successive approximation bit position high/low
}

// WriteDqt() writes out the Quantization tables
void WriteDqt(int *QLumMatrix, int *QChromMatrix)
{
        int i, j;

	bputc(MARKER_MARKER);
	bputc(MARKER_DQT);
	bputw((2+2*(65+64)));
	bputc((0x10|tq[0])); // Precision defined for big numbers
	for(j = 0; j < 64; j++) bputw(QLumMatrix[Zigzag(j)]);
	bputc((0x10|tq[1])); // Precision defined for big numbers
	for(i = 0; i < 64; i++) bputw(QChromMatrix[Zigzag(i)]);
}

//WriteDht() writes out the Huffman tables
void WriteDht(TTablesInfo *Lum, TTablesInfo *Chrom)
{
	int Start,End;

	bputc(MARKER_MARKER);
	bputc(MARKER_DHT);
//	Start = ftell(fh);
	Start = imageIndex;
	bputw(0);
// write Luminance Huffman tables
	bputc(td[0]);
	WriteHuffman((*Lum).DCHuffBits,(*Lum).DCHuffVal);
	bputc(ta[0]|0x10);
	WriteHuffman((*Lum).ACHuffBits,(*Lum).ACHuffVal);
//write Chrominance Huffman tables
	bputc(td[1]);
	WriteHuffman((*Chrom).DCHuffBits,(*Chrom).DCHuffVal);
	bputc(ta[1]|0x10);
	WriteHuffman((*Chrom).ACHuffBits,(*Chrom).ACHuffVal);

//	End = ftell(fh);
	End = imageIndex;
//	fseek(fh,Start,SEEK_SET);
	imageIndex = Start;
	bputw((End-Start));
//	fseek(fh,End,SEEK_SET);
	imageIndex = End;
}

void WriteHuffman(int *bits, int *huffval)
{
	int i, accum;

	for(accum = 0, i = 0; i<16; i++) {
		bputc(bits[i]);
		accum += bits[i];
	}
	for(i = 0; i < accum; i++) {
		bputc(huffval[i]);
	}
}

void init(THeaderInfo *HeaderInfo,
		     TTablesInfo *LuminanceInfoTables,
		     TTablesInfo *ChrominanceInfoTables)
{

	++t;
	imageIndex = 0;
	fh = mwopen(strcat(jpgoutfilename[t],".jpg"));

	V_size = (*HeaderInfo).FrameSize.Ver; H_size = (*HeaderInfo).FrameSize.Hor;

	WriteSoi();
	WriteJfif();
	WriteDqt((*LuminanceInfoTables).QTable.QCoef,
			(*ChrominanceInfoTables).QTable.QCoef);
	WriteSof();
	WriteDht(LuminanceInfoTables, ChrominanceInfoTables);
	WriteSos();
}

void mainVideoOut(const THeaderInfo *HeaderInfo, const TPackets *stream)
{
        int i, icnt;

	if(c==-1) {
		init((THeaderInfo*)HeaderInfo,
		     &LuminanceInfoTables,
		     &ChrominanceInfoTables);
	}
	++c;

        for (i = 0; i < 64; i++){
          if ( (*stream).packet[i].marker == 1 ) {
            for(icnt = 0; icnt<PACKETSIZE; icnt++) {
                pputc( (*stream).packet[i].byte[icnt] );
            }
          }
        }

	if(c==(((int)((*HeaderInfo).NumOfBlocks/2))-1)) {
	   c=-1;
           WriteEoi();

           for (i = 0; i < imageIndex; i++) {
              putc(compImage[i],fh);
           }
           mwclose(fh);
	}
}

