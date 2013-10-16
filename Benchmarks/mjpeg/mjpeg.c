#include "mjpeg_func.h"

int main(int argc, char **argv)
{
        int t, j, i;

	THeaderInfo     hi;
	TPackets        stream;
	TBlocks block;


	for (t = 0; t < NumFrames; t++) {

		initVideoIn (&hi);

		for (j = 0; j < VNumBlocks; j++) {

			for (i = 0; i < HNumBlocks; i++) {

				mainVideoIn(&block);

				mainDCT(&block, &block);
				//intArith(&block, &block);

				mainQ(&block, &block);

				mainVLE(&block, &stream);

				mainVideoOut(&hi, &stream);
			}
		}

	}
	
	return (0);
}
