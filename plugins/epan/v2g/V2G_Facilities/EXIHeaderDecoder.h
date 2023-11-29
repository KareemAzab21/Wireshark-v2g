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
 * File Name: EXIHeaderDecoder.h
 *
 * Description: Header file for EXI Header Decoder
 *
************************************************************************************/
#ifndef EXI_HEADER_DECODER_H
#define EXI_HEADER_DECODER_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------- File Includes ------------------------------------- */
#include "EXITypes.h"

/*---------------------------------- APIs declarations -----------------------------------*/

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
int readEXIHeader(bitstream_t* stream);

#ifdef __cplusplus
}
#endif

#endif
