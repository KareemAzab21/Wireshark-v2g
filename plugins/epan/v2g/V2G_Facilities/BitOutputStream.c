/************************************************************************************
 *
 * @author : Youssef Hussien and Tasneem Essmat
 *
 * @version 22-10-2022
 *
 * @contact ysfhussien@gmail.com
 *			tasneemessmat@gmail.com
 *
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 *
 * File Name: BitOutputStream.c
 *
 * Description: Source file for Bit Output Stream
 * 				Write bits and bytes to an underlying output stream.
 *
************************************************************************************/

/*------------------------------------- File Includes ------------------------------------- */

#include "BitOutputStream.h"
#include "EXIConfig.h"
#include "EXITypes.h"
#include "ErrorCodes.h"

#ifndef BIT_OUTPUT_STREAM_C
#define BIT_OUTPUT_STREAM_C

/*---------------------------------- APIs Implementation -----------------------------------*/

/************************************************************************************
 * Service Name: writeBits
 * Service ID[hex]: 0x16
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream - Pointer to Output Stream container
 	 	 	 	 	nbits  - Number of bits
 	 	 	 	 	val    - Value to be written
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Write the n least significant bits of parameter b starting
 				with the most significant, i.e. from left to right.
 * Available via: BitOutputStream.h
 * Requirement:
************************************************************************************/
int writeBits(bitstream_t* stream, size_t nbits, uint32_t val) {
	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;

	/* Check if there is enough space in the buffer */
	if (nbits <= stream->capacity) {

		/* all bits fit into the current buffer */
		stream->buffer = (uint8_t)(stream->buffer << (nbits)) | (uint8_t)(val & (uint32_t)(0xff >> (uint32_t)(BITS_IN_BYTE - nbits)));

		/*Updating capacity by subtracting the number of bits written in buffer*/
		stream->capacity = (uint8_t)(stream->capacity - nbits);

		/*Here if Capacity = 0, it means buffer is full so write byte into data array
		 * if the buffer is full write byte */
		if (stream->capacity == 0) {

#if EXI_STREAM == BYTE_ARRAY

			/*Checking if it reached end of Output stream*/
			if ((*stream->pos) >= stream->size) {

				errn = EXI_ERROR_OUTPUT_STREAM_EOF;
			} else {
				/*Copy current byte of buffer into array of data*/
				stream->data[(*stream->pos)] = stream->buffer;

				(*stream->pos)++;
			}
#endif
#if EXI_STREAM == FILE_STREAM
			if ( putc(stream->buffer, stream->file) == EOF ) {
				errn = EXI_ERROR_OUTPUT_STREAM_EOF;
			}
#endif
			/* Capacity = 8 again after writing
			 * Capacity = 8 here means buffer is empty*/
			stream->capacity = BITS_IN_BYTE;

			/*Buffer is empty again*/
			stream->buffer = 0;
		}


	}


	else {
		/* the buffer is not enough
		 * fill the buffer */
		stream->buffer = (uint8_t)(stream->buffer << stream->capacity) |
				( (uint8_t)(val >> (nbits - stream->capacity)) & (uint8_t)(0xff >> (BITS_IN_BYTE - stream->capacity)) );

		/* Calculate how many bits left to be written in buffer next*/
		nbits = (nbits - stream->capacity);

#if EXI_STREAM == BYTE_ARRAY

		/*Checking if it reached end of Output stream*/
		if ((*stream->pos) >= stream->size) {

			errn = EXI_ERROR_OUTPUT_STREAM_EOF;
		} else {

			/*Copy current byte of buffer into array of data*/
			stream->data[(*stream->pos)++] = stream->buffer;
		}
#endif
#if EXI_STREAM == FILE_STREAM
		if ( putc(stream->buffer, stream->file) == EOF ) {
			errn = EXI_ERROR_OUTPUT_STREAM_EOF;
		}
#endif
		/*Buffer is empty again*/
		stream->buffer = 0;

		/* write whole bytes */
		while (errn == 0 && nbits >= BITS_IN_BYTE) {

			/* Calculate how many bits left to be written in buffer next*/
			nbits = (nbits - BITS_IN_BYTE);

#if EXI_STREAM == BYTE_ARRAY

			/*Checking if it reached end of Output stream*/
			if ((*stream->pos) >= stream->size) {

				errn = EXI_ERROR_OUTPUT_STREAM_EOF;
			} else {
				/*Copy current byte of buffer into array of data*/
				stream->data[(*stream->pos)++] = (uint8_t)(val >> (nbits));
			}
#endif
#if EXI_STREAM == FILE_STREAM
			if ( putc((int)(val >> (nbits)), stream->file) == EOF ) {
				errn = EXI_ERROR_OUTPUT_STREAM_EOF;
			}
#endif
		}

		/* spared bits are kept in the buffer */
		/* Note: the high bits will be shifted out during further filling */
		stream->buffer = (uint8_t)val;
		stream->capacity = (uint8_t)(BITS_IN_BYTE - (nbits));
	}

	return errn;
}

/************************************************************************************
 * Service Name: flush
 * Service ID[hex]: 0x17
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream - Pointer to Output Stream container
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: If there are some unwritten bits, pad them if necessary and
 				write them out. Note that this method does flush the
				underlying stream.
 * Available via: BitOutputStream.h
 * Requirement:
************************************************************************************/
int flush(bitstream_t* stream) {
	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;

	if (stream->capacity == BITS_IN_BYTE) {

		/* nothing to do, no bits in buffer */

	} else {
		errn = writeBits(stream, stream->capacity, 0);
	}
	return errn;
}

#endif

