#include "Q.h"

// Quantize() quantizes an input matrix and puts the output in matrix.
void Quantize(int *matrix, int* qmatrix)
{
	int *mptr;
	for(mptr=matrix;mptr<matrix+BLOCKSIZE;mptr++) {
		if (*mptr > 0) {
			// Rounding is different for +/- coeffs
			*mptr = (*mptr + *qmatrix/2)/ (*qmatrix);
			qmatrix++;
		} else {
			*mptr = (*mptr - *qmatrix/2)/ (*qmatrix);
			qmatrix++;
		}
	}
}

/*
ZigzagMatrix() performs a zig-zag translation on the input imatrix
and puts the output in omatrix.
*/
void ZigzagMatrix(int *imatrix, int *matrix)
{
	int omatrix[BLOCKSIZE];
        int i;
	int *tptr;

	for(tptr=zigzag_index;tptr<zigzag_index+BLOCKSIZE;tptr++) {
		omatrix[*tptr] = *(imatrix++);
	}

	for(i = 0; i < BLOCKSIZE; i++) {
		matrix[i] = omatrix[i];
	}
}

void mainQ(const TBlocks  *input, TBlocks *output)
{

	// Y1
	Quantize((int*)(*input).Y1.pixel, LuminanceQTable.QCoef);
	ZigzagMatrix((int*)(*input).Y1.pixel, (*output).Y1.pixel);

	// Y2
	Quantize((int*)(*input).Y2.pixel, LuminanceQTable.QCoef);
	ZigzagMatrix((int*)(*input).Y2.pixel, (*output).Y2.pixel);

	// U1
	Quantize((int*)(*input).U1.pixel, ChrominanceQTable.QCoef);
	ZigzagMatrix((int*)(*input).U1.pixel, (*output).U1.pixel);

	// V1
	Quantize((int*)(*input).V1.pixel, ChrominanceQTable.QCoef);
	ZigzagMatrix((int*)(*input).V1.pixel, (*output).V1.pixel);

}


