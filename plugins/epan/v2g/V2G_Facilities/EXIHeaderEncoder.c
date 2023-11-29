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
 * File Name: EXIHeaderEncoder.c
 *
 * Description: Source file for EXI Header Encoder
 *
************************************************************************************/

/*------------------------------------- File Includes ------------------------------------- */
#include "EXIHeaderEncoder.h"
#include "BitOutputStream.h"
#include "EncoderChannel.h"

#ifndef EXI_HEADER_ENCODER_C
#define EXI_HEADER_ENCODER_C


/*---------------------------------- APIs Implementation -----------------------------------*/

/************************************************************************************
 * Service Name: writeEXIHeader
 * Service ID[hex]: 0x20
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): stream - Pointer to Output Stream container
 * Parameters (inout): None
 * Parameters (out): errn (Error code in case of failure)
 * Return value: int
 * Description: Function to Write EXI header
 * Available via: EXIHeaderEncoder.h
 * Requirement:
************************************************************************************/
int writeEXIHeader(bitstream_t* stream) {
	/* init stream */

	/*Buffer is empty */
	stream->buffer = 0;

	/*Full Capacity is available to use */
	stream->capacity = 8;

	/*
	 * 128 complies the ISO-2 Requirement
	 * 1 0 Distinguishing bits(Two bit field, The first bit contains the value 1 and
	 *						   the second bit contains the value 0)
	 * + 0 Presence Bit(Shall always be false)
	 * + 00000 Final Version (EXI processors conforming with the final version
	 * 						 of this specification MUST use the 5-bit value 0 0000
	 * 						 as the version number)
	 * 128 -> 10 0 00000
	 */
	return writeBits(stream, 8, 128);
}


#endif


