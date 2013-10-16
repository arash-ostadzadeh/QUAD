#include "DCT.h"

// ReferenceDct() does a reference DCT on the input (matrix) and output(new matrix).
void ReferenceDct(int *matrix,int *newmatrix)
{
	int *mptr;
	double *sptr,*dptr;
	double sourcematrix[BLOCKSIZE],destmatrix[BLOCKSIZE];

	for(sptr=sourcematrix,mptr=matrix;mptr<matrix+BLOCKSIZE;mptr++) {
		// Convert to doubles
		*(sptr++) = (double) *mptr;
	}
	for(dptr = destmatrix,sptr=sourcematrix;
		sptr<sourcematrix+BLOCKSIZE;sptr+=BLOCKWIDTH) {
		// Do DCT on rows
		DoubleReferenceDct1D(sptr,dptr);
		dptr+=BLOCKWIDTH;
	}
	DoubleTransposeMatrix(destmatrix,sourcematrix);  // Transpose
	for(dptr = destmatrix,sptr=sourcematrix;
		sptr<sourcematrix+BLOCKSIZE;sptr+=BLOCKWIDTH) {
		// Do DCT on columns
		DoubleReferenceDct1D(sptr,dptr);
		dptr+=BLOCKWIDTH;
	}
	DoubleTransposeMatrix(destmatrix,sourcematrix);  // Transpose
	for(sptr = sourcematrix,mptr=newmatrix;mptr<newmatrix+BLOCKSIZE;sptr++) {
		// NB: Inversion on counter
		*(mptr++) = (int) (*sptr > 0 ? (*(sptr)+0.5):(*(sptr)-0.5));
	}
}

/*
DoubleReferenceDCT1D() does a 8 point dct on an array of double
input and places the result in a double output.
*/
#pragma to_dfg
void DoubleReferenceDct1D(double *ivect, double *ovect)
{
	double *iptr,*optr, *mptr;

	for(mptr=DctMatrix,optr=ovect;optr<ovect+BLOCKWIDTH;optr++) {
		// 1d dct is just matrix multiply
		for(*optr=0,iptr=ivect;iptr<ivect+BLOCKWIDTH;iptr++) {
			*optr += *iptr*(*(mptr++));
		}

	}

}

/*
DoubleTransposeMatrix transposes a double input matrix and puts the
double output in newmatrix.
*/
#pragma to_dfg
void DoubleTransposeMatrix(double *matrix, double *newmatrix)
{
	int *tptr;

	for(tptr=transpose_index;tptr<transpose_index+BLOCKSIZE;tptr++) {
		*(newmatrix++) = matrix[*tptr];
	}
}

/*
PreshiftDctMatrix() subtracts 128 (2048) from all 64 elements of an 8x8
matrix.  This results in a balanced DCT without any DC bias.
*/
void PreshiftDctMatrix(int *matrix, int shift)
{
        int *mptr;

	for(mptr=matrix;mptr<matrix+BLOCKSIZE;mptr++)
	{*mptr -= shift;}
}

/*
BoundDctMatrix() clips the Dct matrix such that it is no larger than
a 10 (1023) bit word or 14 bit word (4095).
*/
void BoundDctMatrix(int *matrix, int Bound)
{
        int *mptr;

	for(mptr=matrix;mptr<matrix+BLOCKSIZE;mptr++) {
		if (*mptr+Bound < 0)
			*mptr = -Bound;
		else if (*mptr-Bound > 0)
			*mptr = Bound;
	}
}

void mainDCT(const TBlocks *input, TBlocks *output)
{
	int	DCTBound,DCTShift;
	DCTBound = ((DataPrecision)?16383:1024);
	DCTShift = ((DataPrecision)?2048:128);

	//Y1
	PreshiftDctMatrix((int*)(*input).Y1.pixel, DCTShift);     // Shift
	ReferenceDct((int*)(*input).Y1.pixel, (*output).Y1.pixel);      // DCT
	BoundDctMatrix((*output).Y1.pixel, DCTBound);       // Bound, limit

	//Y2
	PreshiftDctMatrix((int*)(*input).Y2.pixel, DCTShift);     // Shift
	ReferenceDct((int*)(*input).Y2.pixel, (*output).Y2.pixel);      // DCT
	BoundDctMatrix((*output).Y2.pixel, DCTBound);       // Bound, limit

	//U1
	ReferenceDct((int*)(*input).U1.pixel, (*output).U1.pixel);      // DCT
	BoundDctMatrix((*output).U1.pixel, DCTBound);       // Bound, limit

	// V1
	ReferenceDct((int*)(*input).V1.pixel, (*output).V1.pixel);      // DCT
	BoundDctMatrix((*output).V1.pixel, DCTBound);       // Bound, limit

	return;
}

/**************************/
/* Intiger Arithmetic DCT */
/**************************/
void IntArithDct (int *block, int *outdata)
{
  int i,j,k;
  long s;
  long tmp[64];

  for (i=0; i<8; i++) {
     for (j=0; j<8; j++) {
        s = 0;
        for (k=0; k<8; k++) {
           s += (block[8*i+k])*(c[j][k]>>16);
        }
        tmp[8*i+j] = s >> 8;
	 }
  }


  for (i=0; i<8; i++) {
     for (j=0; j<8; j++) {
        s = 0;
        for (k=0; k<8; k++) {
          s += (c[i][k]>>16) * tmp[8*k+j];
        }                                                                                                                                                                                                                                                        ;
          outdata[8*i+j] = s >> 8;
     }
  }

  return;
}


void intArith(const TBlocks *input, TBlocks *output)
{

	int	DCTBound,DCTShift;
	DCTBound = ((DataPrecision)?16383:1024);
	DCTShift = ((DataPrecision)?2048:128);

	//Y1
	PreshiftDctMatrix((int*)(*input).Y1.pixel, DCTShift);     // Shift
	IntArithDct((int*)(*input).Y1.pixel, (*output).Y1.pixel);      // DCT
	BoundDctMatrix((*output).Y1.pixel, DCTBound);       // Bound, limit

	//Y2
	PreshiftDctMatrix((int*)(*input).Y2.pixel, DCTShift);     // Shift
	IntArithDct((int*)(*input).Y2.pixel, (*output).Y2.pixel);      // DCT
	BoundDctMatrix((*output).Y2.pixel, DCTBound);       // Bound, limit

	//U1
	IntArithDct((int*)(*input).U1.pixel, (*output).U1.pixel);      // DCT
	BoundDctMatrix((*output).U1.pixel, DCTBound);       // Bound, limit

	// V1
	IntArithDct((int*)(*input).V1.pixel, (*output).V1.pixel);      // DCT
	BoundDctMatrix((*output).V1.pixel, DCTBound);       // Bound, limit

	return;
}

