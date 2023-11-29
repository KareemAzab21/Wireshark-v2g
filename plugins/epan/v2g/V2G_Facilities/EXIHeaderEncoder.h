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
 * File Name: EXIHeaderEncoder.h
 *
 * Description: Header file for EXI Header Encoder
 *
************************************************************************************/

#ifndef EXI_HEADER_ENCODER_H
#define EXI_HEADER_ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------- File Includes ------------------------------------- */
#include "EXITypes.h"

/*---------------------------------- APIs declarations -----------------------------------*/

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
int writeEXIHeader(bitstream_t* stream);

#ifdef __cplusplus
}
#endif

#endif
