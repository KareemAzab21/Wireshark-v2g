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
 * File Name: BitInputStream.h
 *
 * Description: Header file for Bit Input Stream
 * 				Read bits and bytes from an underlying input stream.
 *
************************************************************************************/



/**
 * \file 	BitInputStream.h
 * \brief 	Bit Input Stream
 *
 * 			Read bits and bytes from an underlying input stream.
 *
 */

#ifndef BIT_INPUT_STREAM_H
#define BIT_INPUT_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------- File Includes ------------------------------------- */
#include "EXITypes.h"

/*---------------------------------- APIs declarations -----------------------------------*/
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

int readBits(bitstream_t* stream, size_t num_bits, uint32_t* b);


#ifdef __cplusplus
}
#endif

#endif
