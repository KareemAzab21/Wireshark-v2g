/*******************************************************************
 *
 * @author : Youssef Hussien and Tasneem Essmat
 * @version 20-10-2022
 * @contact: ysfhussien@gmail.com
 *			 tasneemessmat@gmail.com
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 * File Name: appHandEXIDataTypesEncoder.h
 * Description: This is an Encoder file for iso2 messages
 ********************************************************************/



/**
 * \file 	EXIDatatypesEncoder.h
 * \brief 	Encoder for datatype definitions
 *
 */

#ifndef EXI_iso2_DATATYPES_ENCODER_H
#define EXI_iso2_DATATYPES_ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------- File Includes ------------------------------------- */
#include "iso2EXIDatatypes.h"
#if DEPLOY_ISO2_CODEC == SUPPORT_YES
#include <stdint.h>
#include "EXITypes.h"

/************************************************************************************
* Service Name: encode_iso2ExiDocument
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to iso2EXIdocument struct
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this is a general encoding function of iso2 messagees, where internally,
			   another encoding functions is called based on the message type.
* Available via: iso2EXIDatatypesEncoder.h
* Requirement:
************************************************************************************/
int V2gFac_encode_iso2ExiDocument(bitstream_t* stream, iso2EXIDocument* exiDoc);


/************************************************************************************
* Service Name: encode_iso2ExiFragment
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): Pointer to stream, Pointer to iso2EXIFragment struct
* Parameters (inout): None
* Parameters (out): errn, Error Code in case of exception.
* Return value: int
* Description: this is a general encoding function of iso2 messages, where internally,
			   another encoding functions is called based on the message type.
* Available via: iso2EXIDatatypesEncoder.h
* Requirement:
************************************************************************************/
#if DEPLOY_ISO2_CODEC_FRAGMENT == SUPPORT_YES
int encode_iso2ExiFragment(bitstream_t* stream, iso2EXIFragment* exiFrag);
#endif /* DEPLOY_ISO2_CODEC_FRAGMENT */


#endif /* DEPLOY_ISO2_CODEC */

#ifdef __cplusplus
}
#endif

#endif
