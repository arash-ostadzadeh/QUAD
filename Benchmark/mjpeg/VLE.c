#include "VLE.h"
/*
EncodeAC() takes the matrix and encodes it by passing the values
of the codes found to the Huffman package.
*/
void EncodeAC(int *matrix)
{
	int i,k,r,ssss,cofac;

	for(k=r=0;++k<BLOCKSIZE;)
	{
		cofac = abs(matrix[k]);            // Find absolute size
		if (cofac < 256)
		{
			ssss = csize[cofac];
		} else {
			cofac = cofac >> 8;
			ssss = csize[cofac] + 8;
		}
		if (matrix[k] == 0)                // Check for zeroes
		{
			if (k == BLOCKSIZE-1)
			{
				EncodeHuffman(0);
				break;
			}
			r++;                           // Increment run-length of zeroes
		} else {
			while(r > 15)                  // If run-length > 15, time for
			{                            // Run-length extension
				EncodeHuffman(240);
				r -= 16;
			}
			i = 16*r + ssss;               // Now we can find code byte
			r = 0;
			EncodeHuffman(i);
						// Encode RLE code
			if (matrix[k]< 0)              // Follow by significant bits
			{
				fputv(ssss,matrix[k]-1);

			} else {
				fputv(ssss,matrix[k]);
			}
		}
	}
}

/*
EncodeDC() encodes the input coefficient to the stream using the
currently installed DC Huffman table.
*/
void EncodeDC(int coef, int *LastDC)
{
	int s,diff,cofac;

	diff = coef - *LastDC;
	*LastDC = coef;                // Do DPCM
	cofac = abs(diff);
	if (cofac < 256)
	{
		s = csize[cofac];          // Find true size
	} else {
		cofac = cofac >> 8;
		s = csize[cofac] + 8;
	}
	EncodeHuffman(s);             
					// Encode size
	if (diff < 0)                  // Encode difference
	{
		diff--;
	}
	fputv(s,diff);
}

// EncodeHuffman() places the Huffman code for the value onto the stream.
void EncodeHuffman(int value)
{
	fputv(ehufsi[value],ehufco[value]);
}

// fputv() puts n bits from b onto the writer stream.
void fputv(int n,int b)
{

    int p, icnt, i;

	n--;
	b &= lmask[n];
	p = n - write_position;
	if (!p)                            // Can do parallel save immediately
	{
		current_write_byte |= b;
		if (byte_index < PACKETSIZE-1)  // put the byte in the packet
		{
			current_packet.byte[byte_index] = current_write_byte;
			byte_index++;
			current_write_byte = 0;
			write_position = 7;
		}                             // put the byte in the packet and send it
		else {
			current_packet.byte[byte_index] = current_write_byte;

			for(icnt = 0; icnt < PACKETSIZE; icnt++) {
                             out_BitStream.packet[NPackets].byte[icnt] = current_packet.byte[icnt];
			}
                        out_BitStream.packet[NPackets++].marker = 1;

			for(i = 0; i < PACKETSIZE; i++) {
				current_packet.byte[i] = 0;
			}
			byte_index = 0;
			current_write_byte = 0;
			write_position = 7;
		}
		return;
	} else if (p < 0)                   // if can fit, we have to shift byte
 	{
		p = -p;
		current_write_byte |= (b << p);
		write_position = p-1;
		return;
	}
	current_write_byte |= (b >> p);  // cannot fit. we must do putc's
	if (byte_index < PACKETSIZE-1)    // put the byte in the packet
	{
		current_packet.byte[byte_index] = current_write_byte;
		byte_index++;
	}                              // put the byte in the packet and send it
	else {
		current_packet.byte[byte_index] = current_write_byte;

		for(icnt = 0; icnt < PACKETSIZE; icnt++) {
                        out_BitStream.packet[NPackets].byte[icnt] = current_packet.byte[icnt];
		}
                out_BitStream.packet[NPackets++].marker = 1;


		for(i = 0; i < PACKETSIZE; i++) {
			current_packet.byte[i] = 0;
		}
		byte_index = 0;
	}
                                   // Save off  remainder
	while(p > 7)                     // Save off bytes while remaining > 7
	{
		p -= 8;
		current_write_byte = (b >> p) & lmask[7];
		if (byte_index < PACKETSIZE-1)   // put the byte in the packet
		{
			current_packet.byte[byte_index] = current_write_byte;
			byte_index++;
		}
		else                            // put the byte in the packet and send it
		{
			current_packet.byte[byte_index] = current_write_byte;

			for(icnt = 0; icnt < PACKETSIZE; icnt++) {
                            out_BitStream.packet[NPackets].byte[icnt] = current_packet.byte[icnt];
			}
                        out_BitStream.packet[NPackets++].marker = 1;

			for(i = 0; i < PACKETSIZE; i++) {
				current_packet.byte[i] = 0;
			}
			byte_index = 0;
		}
	}
	if (!p)                          // If zero then reset position
	{
		write_position = 7;
		current_write_byte = 0;
	}
	else                             // Otherwise reset write byte buffer
	{
		write_position = 8-p;
		current_write_byte = (b << write_position) & lmask[7];
		write_position--;
	}
}

void UseHuffman(int *code, int *size)
{
        int i;
	for (i = 0; i < 257; i++)
	{
		ehufsi[i] = size[i];
		ehufco[i] = code[i];
	}
}

void mainVLE(const TBlocks *blocks, TPackets *stream) {

        int i, icnt, j;

	NPackets = 0;

	for (i = 0; i < 64; i++){
	    out_BitStream.packet[i].marker = 0;
	}


	//Y1
	// make Huffman encoding of current 8x8block and put the code into a bitstream
	UseHuffman(LuminanceHuffTablesDC.DCcode, LuminanceHuffTablesDC.DCsize);
	EncodeDC(*(*blocks).Y1.pixel, &LastDC_Y);
	UseHuffman(LuminanceHuffTablesAC.ACcode, LuminanceHuffTablesAC.ACsize);
	EncodeAC((int*)(*blocks).Y1.pixel);


	//Y2
	// make Huffman encoding of current 8x8block and put the code into a bitstream
	UseHuffman(LuminanceHuffTablesDC.DCcode, LuminanceHuffTablesDC.DCsize);
	EncodeDC(*(*blocks).Y2.pixel, &LastDC_Y);
	UseHuffman(LuminanceHuffTablesAC.ACcode, LuminanceHuffTablesAC.ACsize);
	EncodeAC((int*)(*blocks).Y2.pixel);

	//U1
    // make Huffman encoding of current 8x8block and put the code into a bitstream
	UseHuffman(ChrominanceHuffTablesDC.DCcode, ChrominanceHuffTablesDC.DCsize);
	EncodeDC(*(*blocks).U1.pixel, &LastDC_U);
	UseHuffman(ChrominanceHuffTablesAC.ACcode, ChrominanceHuffTablesAC.ACsize);
	EncodeAC((int*)(*blocks).U1.pixel);

	//V1
	// make Huffman encoding of current 8x8block and put the code into a bitstream
	UseHuffman(ChrominanceHuffTablesDC.DCcode, ChrominanceHuffTablesDC.DCsize);
	EncodeDC(*(*blocks).V1.pixel, &LastDC_V);
	UseHuffman(ChrominanceHuffTablesAC.ACcode, ChrominanceHuffTablesAC.ACsize);
	EncodeAC((int*)(*blocks).V1.pixel);


	if ( (nbCounter--) == 1) {
		current_packet.byte[byte_index] = current_write_byte;

	for(icnt = 0; icnt < PACKETSIZE; icnt++) {
           out_BitStream.packet[NPackets].byte[icnt] = current_packet.byte[icnt];
	}
        out_BitStream.packet[NPackets++].marker = 1;

		current_write_byte = 0;
		write_position     = 7;
		for(i = 0; i < PACKETSIZE; i++)
			current_packet.byte[i] = 0;
		byte_index         = 0;
		LastDC_Y           = 0;
		LastDC_U           = 0;
		LastDC_V           = 0;
		LastDC_sY          = 0;
		LastDC_sU          = 0;
		LastDC_sV          = 0;

		nbCounter = numBlocks;
	}

    for (j = 0; j < 64; j++){
      for(icnt = 0; icnt < PACKETSIZE; icnt++) {
          (*stream).packet[j].byte[icnt] = out_BitStream.packet[j].byte[icnt];
      }
      (*stream).packet[j].marker = out_BitStream.packet[j].marker;
	}

}

