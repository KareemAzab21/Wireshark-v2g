/*
 * Fac.c
 *
 *  Created on: Nov 6, 2022
 *      Author: Youssef
 */


// Fac.c



#include <stdio.h>
#include <stdlib.h>
#include "Fac.h"

uint8_t mated_init = 0; /* Check if its already mated or not */
static int errn;
static uint32_t eventCode;



/*        variable defs     */

V2gFac_Message V2g_EVReqMessage;

V2gFac_Message V2g_EVResMessage;

appHandEXIDocument ReqHandshakeDoc;
appHandEXIDocument ResHandshakeDoc;
iso2EXIDocument ReqIso2Doc;
iso2EXIDocument ResIso2Doc;
Fac_RunTimeSelectedOptions RunTimeVaribales;
Fac_SuppliedParameters StubbedParameters;




Fac_InitConfigType initConfig =
{
	&V2g_EVReqMessage,
	&V2g_EVResMessage,
	&ReqHandshakeDoc,
	&ReqIso2Doc,
	&ResHandshakeDoc,
	&ResIso2Doc,
};

/**********************************/




void V2gFac_RxIndication (){

	// decode

	// raise a flag


}

void V2gFac_MainFun(){

	// flag is raised in rx indication
	//if (flag== raised){

		//Call RTE or Fac Service SWcomp --> rte
	//}
	//flag =0;

}

// Called by FacServices SWC
void V2g_FacSend(){


	//encode
	// Sockets
	// v2gTransmit() --> v2gTP ammar



}

int V2gFac_decode_Message(bitstream_t* stream,  V2gFac_Message* msg){

	/* read the EXI header */
	errn = readEXIHeader(stream);


	if(errn == 0) {




		errn = decodeNBitUnsignedInteger(stream, 1, &eventCode);

		if(errn == 0){

			switch(eventCode) {

			/* case 0 : handshake  */
			case 0:


				errn = V2gFac_decode_appHandExiDocument(stream, msg->HandshakeDoc);

				/* assign 1 to request is used */
				msg->HandshakeDoc_isUsed = 1u;
				break;

			/* case 1 : iso2 doc */
			case 1:


				errn = V2gFac_decode_iso2ExiDocument(stream, msg->iso2Doc);

				msg->iso2Doc_isUsed = 1u;
				break;


			default:

				/* if non of the cases, report error due to unexpected event in level 1 decoding */
				errn = EXI_ERROR_UNEXPECTED_EVENT_LEVEL1;
				break;
			}
		}

	}




	return errn;
}

void V2gFac_Message_Init(V2gFac_Message *Msg)
{
	Msg->HandshakeDoc_isUsed=0u;
	Msg->iso2Doc_isUsed=0u;
}
void V2gFac_init(Fac_InitConfigType* initConfig)
{
	initConfig->Req_Msg->HandshakeDoc = initConfig->Req_HandshakeDoc;
	initConfig->Req_Msg->iso2Doc = initConfig->Req_iso2Doc;
	initConfig->Res_Msg->HandshakeDoc = initConfig->Res_HandshakeDoc;
	initConfig->Res_Msg->iso2Doc = initConfig->Res_iso2Doc;
}
void Fac_RunTimeSelectedOptionsInit(Fac_RunTimeSelectedOptions *RunTime)
{
	RunTime->PaymentOptionSelected=-1;
	RunTime->ProtocolIndex=-1;
	RunTime->ServiceSelected=-1;
	for(int i=0;i<8;i++)
	{
		RunTime->SessionIdArrayPtr[i]=0;
	}
	RunTime->SessionIdLen=-1;
	RunTime->ParameterServiceSelected=-1;
	for(int i=0;i<8;i++)
	{
		RunTime->GenChallenge[i]=0;
	}
	RunTime->GenChallengeLen=8;
}
void Fac_SuppliedParametersInit(Fac_SuppliedParameters* StubbedParameters)
{


	StubbedParameters->GridParameters.EVSEMaximumChargeCurrent.Value=600;
	StubbedParameters->GridParameters.EVSEMaximumChargePower.Value=200;
	StubbedParameters->GridParameters.EVSEMaximumVoltage.Value=800;
	StubbedParameters->GridParameters.EVSEMinimumChargeCurrent.Value=0;
	StubbedParameters->GridParameters.EVSEMinimumVoltage.Value=0;
	StubbedParameters->GridParameters.EVSEPeakCurrentRipple.Value=0;
	StubbedParameters->GridParameters.EVSEEnergyToBeDelivered.Value=1000;


	StubbedParameters->GridParameters.EVSEMaximumChargeCurrent.Exponent=0;
	StubbedParameters->GridParameters.EVSEMaximumChargePower.Exponent=0;
	StubbedParameters->GridParameters.EVSEMaximumVoltage.Exponent=0;
	StubbedParameters->GridParameters.EVSEMinimumChargeCurrent.Exponent=0;
	StubbedParameters->GridParameters.EVSEMinimumVoltage.Exponent=0;
	StubbedParameters->GridParameters.EVSEPeakCurrentRipple.Exponent=0;
	StubbedParameters->GridParameters.EVSEEnergyToBeDelivered.Exponent=2;






}
