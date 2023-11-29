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
 * File Name: BitOutputStream.h
 *
 * Description: header file for Bit Output Stream
 * 				Write bits and bytes to an underlying output stream.
 *
************************************************************************************/



#ifndef BIT_OUTPUT_STREAM_H
#define BIT_OUTPUT_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------- File Includes ------------------------------------- */
#include <stdint.h>
#include "EXITypes.h"


/*---------------------------------- APIs declarations -----------------------------------*/

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
int writeBits(bitstream_t* stream, size_t nbits, uint32_t bits);


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
int flush(bitstream_t* stream);


#ifdef __cplusplus
}
#endif

#endif

