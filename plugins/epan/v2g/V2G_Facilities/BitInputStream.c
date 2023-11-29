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
 * File Name: BitInputStream.c
 *
 * Description: Source file for Bit Input Stream
 * 				Read bits and bytes from an underlying input stream.
 *
************************************************************************************/

/*------------------------------------- File Includes ------------------------------------- */
#include "BitInputStream.h"
#include "EXIConfig.h"
#include "EXITypes.h"
#include "ErrorCodes.h"

#ifndef BIT_INPUT_STREAM_C
#define BIT_INPUT_STREAM_C

/*---------------------------------- APIs Implementation -----------------------------------*/

/************************************************************************************
 * Service Name: readBuffer
 * Service ID[hex]: 0x18
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream - Pointer to Input Stream container
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: internal method to (re)fill buffer
 * Available via: BitInputStream.h
 * Requirement:
************************************************************************************/
static int readBuffer(bitstream_t* stream)
{
	/*errn variable to hold the error value in case of any failure*/
	int errn = 0;

    /*Here if Capacity = 0, it means buffer is empty so read byte*/
	if(stream->capacity==0)
	{
#if EXI_STREAM == BYTE_ARRAY

		/*Checking if it reached end of Input stream*/
		if ( (*stream->pos) < stream->size ) {

			/* Read another byte from the data array */
			stream->buffer = stream->data[(*stream->pos)++];

			/* Now Buffer is full so it has no capacity left
			 * Capacity = 8 here means buffer is Full */
			stream->capacity = BITS_IN_BYTE;

		} else {
			errn = EXI_ERROR_INPUT_STREAM_EOF;
		}
#endif
#if EXI_STREAM == FILE_STREAM
		stream->buffer = (uint8_t)(getc(stream->file));
		/* EOF cannot be used, 0xFF valid value */
		if ( feof(stream->file) || ferror(stream->file) ) {
			errn = EXI_ERROR_INPUT_STREAM_EOF;
		} else {
			stream->capacity = BITS_IN_BYTE;
		}
#endif
	}
	return errn;
}

/************************************************************************************
 * Service Name: readBits
 * Service ID[hex]: 0x19
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream   - Pointer to Input Stream container
 	 	 	 	 	num_bits - Number of bits to read
 	 	 	 	 	b		 - Integer value (out)
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Read the next num_bits bits and returns result an integer.
 * Available via: BitInputStream.h
 * Requirement:
************************************************************************************/

int readBits(bitstream_t* stream, size_t num_bits, uint32_t* b)
{
	/*Read byte from input stream into the buffer then read from buffer on demand*/
	int errn = readBuffer(stream);

	/*capacity means: there is x bits in buffer to read*/
	if (errn == 0) {

		/* read the bits in one step */
		if(num_bits <= stream->capacity)
		{
			/* Updating capacity after reading the number of bits from buffer  */
			stream->capacity = (uint8_t)(stream->capacity - num_bits);

			/*Reading into out variable*/
			*b = (uint32_t)((stream->buffer >> stream->capacity) & (0xff >> (BITS_IN_BYTE - num_bits)));
		}
		else
		{
			/* read bits as much as possible */
			*b = (uint32_t)(stream->buffer & (0xff >> (BITS_IN_BYTE - stream->capacity)));

			/* Calculate remaining bits */
			num_bits = (num_bits - stream->capacity);

			/* No bits left in buffer to read */
			stream->capacity = 0;

			/* read whole bytes */
			while(errn == 0 && num_bits >= 8)
			{
				errn = readBuffer(stream);
				*b = ((*b) << BITS_IN_BYTE) | stream->buffer;
				num_bits = (num_bits - BITS_IN_BYTE);
				stream->capacity = 0;
			}

			/* read the spare bits in the buffer */
			if(errn == 0 && num_bits > 0)
			{
				errn = readBuffer(stream);
				if (errn == 0) {
					*b = ( (*b) << num_bits) | (uint8_t)(stream->buffer  >> (BITS_IN_BYTE - num_bits));

				    /*Subtracting the Consumed bits from capacity*/
					stream->capacity = (uint8_t)(BITS_IN_BYTE - num_bits);
				}
			}
		}
	}

	return errn;
}

#endif
