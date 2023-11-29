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
 * File Name: EXIHeaderDecoder.c
 *
 * Description: Source file for EXI Header Decoder
 *
************************************************************************************/


/*------------------------------------- File Includes ------------------------------------- */
#include "EXIHeaderDecoder.h"
#include "BitInputStream.h"
#include "DecoderChannel.h"
#include "ErrorCodes.h"

#ifndef EXI_HEADER_DECODER_C
#define EXI_HEADER_DECODER_C


/*---------------------------------- APIs Implementation -----------------------------------*/

/************************************************************************************
 * Service Name: readEXIHeader
 * Service ID[hex]: 0x21
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream - Pointer to Input Stream container
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Read EXI header
 * Available via: EXIHeaderDecoder.h
 * Requirement:
************************************************************************************/
int readEXIHeader(bitstream_t* stream) {
	/*errn variable to hold the error value in case of any failure*/
	int errn;

	/*integer to hold header value*/
	uint32_t header = 0;

	/* init stream
	 * Buffer is empty */
	stream->buffer = 0;

	/* Zero Bits in Buffer to read */
	stream->capacity = 0;

	/*Read Header -> EXI Header 128 (10 , 0 , 00000 )*/
	errn = readBits(stream, 8, &header);

	if (errn == 0) {
		if(header == '$') {
			/*	we do not support "EXI Cookie" */
			errn = EXI_UNSUPPORTED_HEADER_COOKIE;

		} else if ( header & 0x20 ) {

			/* we do not support "Presence Bit for EXI Options" */
			errn = EXI_UNSUPPORTED_HEADER_OPTIONS;

		} else {
			/* Yes, a *simple* header */
			errn = 0;
		}
	}

	return errn;
}


#endif


