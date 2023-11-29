#ifndef FAC_H
#define FAC_H
/**********************************************************************************************
 *
 * Module: Facilities
 *
 * File Name: Fac.h
 *
 * Description: Header file of Facilities module
 *
 * Author: Omar Reda - Aly Maamoun - Youssef Hussein - Tasneem Essamt
 **********************************************************************************************/

/*******************************************************************************
 *                               Files includes                                *
 *******************************************************************************/

#include "iso2EXIDatatypes.h"
#include "appHandEXIDatatypes.h"
#include "ErrorCodes.h"
#include "appHandEXIDatatypesDecoder.h"
#include "appHandEXIDatatypesEncoder.h"
#include "iso2EXIDatatypesEncoder.h"
#include "iso2EXIDatatypesDecoder.h"
#include "EncoderChannel.h"
#include "EXIHeaderEncoder.h"
#include "DecoderChannel.h"
#include "EXIHeaderDecoder.h"

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
typedef struct
{

	appHandEXIDocument *HandshakeDoc;
	iso2EXIDocument *iso2Doc;

	unsigned int HandshakeDoc_isUsed : 1;
	unsigned int iso2Doc_isUsed : 1;
} V2gFac_Message;

// typedef struct {
//	appHandAnonType_supportedAppProtocolReq  supportedAppProtocolReq;
//	iso2SessionSetupReqType SessionSetupReq;
//	iso2ServiceDiscoveryReqType ServiceDiscoveryReq;
//	iso2PaymentServiceSelectionReqType ServiceSelectionReq;
//	iso2PaymentDetailsReqType PaymentDetailsReq;
//	iso2ChargeParameterDiscoveryReqType ChargeParameterDiscoveryReq;
//	iso2PreChargeReqType PreChargeReq;
//	iso2SessionStopReqType SessionStopReqType;
//}Fac_ConfigType;

typedef struct
{
	appHandAnonType_supportedAppProtocolReq supportedAppProtocol;
	iso2SessionSetupResType EVSEID;
	iso2ServiceListType ServiceIDList;
	iso2PaymentOptionListType PaymentOptionList;
} SE_Fac_ConfigType;

typedef struct
{
	V2gFac_Message *Req_Msg;
	V2gFac_Message *Res_Msg;
	appHandEXIDocument *Req_HandshakeDoc;
	iso2EXIDocument *Req_iso2Doc;
	appHandEXIDocument *Res_HandshakeDoc;
	iso2EXIDocument *Res_iso2Doc;
} Fac_InitConfigType;

typedef struct
{
	int8_t ProtocolIndex;
	int8_t PaymentOptionSelected;
	int8_t ServiceSelected;
	int8_t ParameterServiceSelected;
	uint8_t SessionIdArrayPtr[8];
	int8_t SessionIdLen;
	uint8_t GenChallenge[8];
	int8_t GenChallengeLen;

} Fac_RunTimeSelectedOptions;

typedef struct
{
	iso2DC_EVSEChargeParameterType GridParameters;
} Fac_SuppliedParameters;

/*******************************************************************************
 *                              Variable declaration                            *
 *******************************************************************************/

extern const SE_Fac_ConfigType SE_Fac_Configuration;
// extern const Fac_ConfigType Fac_Configuration;

extern uint8_t mated_init;

extern V2gFac_Message V2g_EVReqMessage;
extern appHandEXIDocument ReqHandshakeDoc;
extern iso2EXIDocument ReqIso2Doc;

extern V2gFac_Message V2g_EVResMessage;
extern appHandEXIDocument ResHandshakeDoc;
extern iso2EXIDocument ResIso2Doc;
extern Fac_RunTimeSelectedOptions RunTimeVaribales;
extern Fac_InitConfigType initConfig;
extern Fac_SuppliedParameters StubbedParameters;

int V2gFac_decode_Message(bitstream_t *stream, V2gFac_Message *msg);
int V2gFac_encode_Message(bitstream_t *stream, V2gFac_Message *msg);
void V2gFac_Message_Init(V2gFac_Message *Msg);
void V2gFac_init(Fac_InitConfigType *initConfig);
void Fac_RunTimeSelectedOptionsInit(Fac_RunTimeSelectedOptions *RunTime);
void Fac_SuppliedParametersInit(Fac_SuppliedParameters *StubbedParameters);
#endif
