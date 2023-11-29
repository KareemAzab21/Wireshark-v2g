/*******************************************************************
 *
 * @author : Youssef Hussien and Tasneem Essmat
 * @version 20-10-2022
 * @contact: ysfhussien@gmail.com
 *			 tasneemessmat@gmail.com
 * <p>Schema: V2G_CI_AppProtocol.xsd</p>
 * File Name: appHandEXIDataTypesDecoder.c
 * Description: This is an Decoder file for application handshake request and response
 ********************************************************************/




#ifndef EXI_appHand_DATATYPES_DECODER_H
#define EXI_appHand_DATATYPES_DECODER_H

#ifdef __cplusplus
extern "C" {
#endif



/*------------------------------------- File Includes ------------------------------------- */
#include <stdint.h>
#include "EXITypes.h"
#include "appHandEXIDatatypes.h"


/************************************************************************************
* Service Name: decode_appHandExiDocument
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to appHandEXIdocument struct
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this is a general decoding function of handshake, where internally,
			   another decoding functions is called based on the type.
* Available via: DecoderChannel.h
* Requirement:
************************************************************************************/
int V2gFac_decode_appHandExiDocument(bitstream_t* stream,  appHandEXIDocument* exiDoc);

#ifdef __cplusplus
}
#endif

#endif
