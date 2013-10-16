#include "Video_in.h"

//mropen() opens a given filename as the input read stream.
FILE *mropen(char *filename)
{
	FILE *fh;
	if ((fh = fopen(filename,"rb"))==NULL) {
		printf("\nCannot read input file: %s\n", filename);
	}
	return(fh);
}

//mrclose() closes the input read stream.
void mrclose(FILE *fh)
{
	fclose(fh);
}

//bgetc() gets a character from the stream.
int bgetc(FILE *fh)
{
	return(getc(fh));
}

void initVideoIn(THeaderInfo *HeaderInfo)
{
	// Header of the frame
	(*HeaderInfo).FrameSize.Ver = 8*numBlocksV;
	(*HeaderInfo).FrameSize.Hor = 8*numBlocksH;
	(*HeaderInfo).NumOfBlocks   = numBlocksH*numBlocksV;
	(*HeaderInfo).BlockType     = YUV;

}


void mainVideoIn(TBlocks *blocks)
{

	int IMAX = numBlocksV-1;
	int JMAX = (numBlocksH>>1)-1;
	int n, k, l, m, p;

        int ch;
	int  c;

        // open image files only the first time when mainVideoIn is called 
        // and put them in arrays
        if ( isFirst == 1 ) {
           isFirst = 0;     

           if(fh1 == NULL) {
		fh1 = mropen("laxmi2.Y");
		c = 0;
                while ((ch = bgetc(fh1)) != EOF) {
		   compY[c] = ch;
		   c++;
		}
	   }

	   if(fh2 == NULL) {
		fh2 = mropen("laxmi2.U");
	        c = 0;
                while ((ch = bgetc(fh2)) != EOF) {
		   compU[c] = ch;
		   c++;
		}
	   }

	   if(fh3 == NULL) {
		fh3 = mropen("laxmi2.V");
	        c = 0;
	        while ((ch = bgetc(fh3)) != EOF) {
		   compV[c] = ch;
		   c++;
		}
	   }
        }

	if(i<0) {i=0;}

	if(j<0) {

		j=0;

	} else if(j<JMAX) {
		j+=1;
	} else {
		if(i<IMAX) {
			++i; j=0;
		} else {
            j = 0; i = 0;
		}
	}


	p = 0;
	for (n = 0; n < 8; n++) {
		for (k = 0; k <8 ; k++) {

			(*blocks).Y1.pixel[p] =  compY[i*8*(8*numBlocksH) + j*16 + (8*numBlocksH)*n + k];
 			(*blocks).U1.pixel[p] =  compU[i*8*(4*numBlocksH) + j*8  + (4*numBlocksH)*n + k]-128;
			(*blocks).V1.pixel[p] =  compV[i*8*(4*numBlocksH) + j*8  + (4*numBlocksH)*n + k]-128;

			p++;
		}
	}

	p=0;
	for (l = 0; l < 8; l++) {
		for (m = 0; m < 8; m++) {
			(*blocks).Y2.pixel[p++] = compY[i*8*(8*numBlocksH) +j*16+8 + (8*numBlocksH)*l + m];
		}
	}

}

