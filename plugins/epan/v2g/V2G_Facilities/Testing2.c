/*
 ============================================================================
 Name        : Testing2.c
 Author      : Aly maamoun - Tasneem esmat - Omar reda - Yousef hussien
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "State_Machine_SWC.h"
#include "Charging_Status_State_Machine_SWC.h"
#include "ByteStream.h"


#define BUFFER_SIZE 256

void Isused_init(){
	V2gFac_init_appHandEXIDocument(V2g_EVReqMessage.HandshakeDoc);
	V2gFac_init_iso2EXIDocument(V2g_EVReqMessage.iso2Doc);
}



void MessageTesting(const char * inputfile,const char * outputfile){


	/* Local for this Function */
	int error=0;

	/* Declaring Buffer for Input Message */
	size_t posDecode = 0 ;
	uint8_t buffer_In[BUFFER_SIZE];


	/* Read Input File Stream */
	error = readBytesFromFile(inputfile, buffer_In , BUFFER_SIZE, &posDecode);
	if (error == 0){
		printf("1- File Is read Successfully!!\n");
	}else{
		printf("File is NOT Read!!");
	}

	/* ************Declaring Input Stream************* */
	bitstream_t Stream_In;
	posDecode = 0;
	Stream_In.size 		= BUFFER_SIZE;
	Stream_In.data 		= buffer_In;
	Stream_In.pos 		= &posDecode;  /* Check */
	Stream_In.buffer  	= 0;
	Stream_In.capacity	= 0;
	/* ********************************************** */

	/************ Decode the Input Stream ************/
	Isused_init();
	error = V2gFac_decode_Message(&Stream_In, &V2g_EVReqMessage);
	if (error == 0){
		printf("2- Message Is Decoded Successfully\n");
	}else{
		printf("Message Decoding FAILED!!\n");
	}

	/************** Message Arrived and Decoded *****************/

	StateMachine_Runnable(); /* To go To next State Based on Message Received */
	ChargingStatus_StateMachine_Runnable();


	/************* Declaring Output Stream ***********/
	uint8_t buffer_Out[BUFFER_SIZE];
	bitstream_t Stream_Out;
	size_t pos = 0;
	Stream_Out.size = BUFFER_SIZE;
	Stream_Out.data = buffer_Out;
	Stream_Out.pos = &pos;
	/*************************************************/

	error = V2gFac_encode_Message(&Stream_Out, &V2g_EVResMessage);
	if(error == 0){
		printf("3- Message is Encoded Successfully\n");
		writeBytesToFile(Stream_Out.data, *Stream_Out.pos, outputfile);
	}
	else{
		printf("Encoding Failed\n");
	}
}



void Testing_Init(){
	StateMachine_Init(&SM);
	V2gFac_init(&initConfig);
	StateMachine_Runnable(); /* To go From Unmated to IDLE State */
	Fac_RunTimeSelectedOptionsInit(&RunTimeVaribales);
	Fac_SuppliedParametersInit(&StubbedParameters);
}




int main_old(void) {


	Testing_Init();
	SessionSetup_Res_Hand(&V2g_EVReqMessage, &V2g_EVResMessage);
	V2g_EVReqMessage.iso2Doc->V2G_Message_isUsed=1;
	for(int i=0;i<8;i++)
		((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Header.SessionID.bytes[i]=i+i*2;

	((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Header.SessionID.bytesLen=8;
	ServiceDiscovery_Res_Hand(&V2g_EVReqMessage, &V2g_EVResMessage);
	PaymentDetails_Res_Hand(&V2g_EVReqMessage, &V2g_EVResMessage);

	printf("---------------Handshake Response Start ---------------\n");
	MessageTesting("EvAppHandshakeReqEXI","SEAppHandshakeResEXI");
	printf("---------------Handshake Response End ---------------\n\n\n");


	printf("---------------Session Setup Response Start ---------------\n");
	MessageTesting("EvSessionSetupReqEXI","SESessionSetupResEXI");
	printf("---------------Session Setup Response End---------------\n\n\n");

	printf("---------------Service Discovery Response Start ---------------\n");
	MessageTesting("EvServiceDiscoveryReqEXI","SEServiceDiscoveryResEXI");
	printf("---------------Service Discovery Response End ---------------\n\n\n");

	printf("---------------Payment Service Selection Response Start ---------------\n");
	MessageTesting("EvPaymentServiceSelectionReqEXI","SEPaymentServiceSelectionResEXI");
	printf("---------------Payment Service Selection Response End ---------------\n\n\n");

	printf("---------------Payment Details Response Start ---------------\n");
	MessageTesting("EvPaymentDetailsReqEXI","SEPaymentDetailsResEXI");
	printf("---------------Payment Details Response End ---------------\n\n\n");

	printf("---------------Authorization Response Start ---------------\n");
	MessageTesting("EvAuthorizationReqEXI","SEAuthorizationResEXI");
	printf("---------------Authorization Response End ---------------\n\n\n");

	printf("---------------Charging Parameter Discovery Response Start ---------------\n");
	MessageTesting("EvChargingParameterDiscoveryReqEXI","SEChargingParameterDiscoveryResEXI");
	printf("---------------Charging Parameter Discovery Response End ---------------\n\n\n");

	printf("---------------Cable Check Response Start ---------------\n");
	MessageTesting("EvCableCheckReqEXI","SECableCheckResEXI");
	printf("---------------Cable Check Response End ---------------\n\n\n");

	printf("---------------PreCharge Response Start ---------------\n");
	MessageTesting("EvPreChargeReqEXI","SEPreChargeResEXI");
	printf("---------------PreCharge Response End ---------------\n\n\n");

	printf("---------------Power Delivery Initial Response Start ---------------\n");
	MessageTesting("EvPowerDeliveryInitReqEXI","SEPowerDeliveryInitResEXI");
	printf("---------------Power Deliver Initial Response End ---------------\n\n\n");

	printf("---------------Current Demand Response Start ---------------\n");
	MessageTesting("EvCurrentDemandReqEXI","SECurrentDemandResEXI");
	printf("---------------Current Demand Response End ---------------\n\n\n");

	printf("---------------Power Delivery Termination Response Start ---------------\n");
	MessageTesting("EvPowerDeliveryTerminationReqEXI","SEPowerDeliveryTerminationResEXI");
	printf("---------------Power Delivery Termination Response End ---------------\n\n\n");


	printf("---------------Session Stop Response Start ---------------\n");
	MessageTesting("EvSessionStopReqEXI","SESessionStopResEXI");
	printf("---------------Session Stop Response Response End ---------------\n\n\n");





	return 0;
}

int main() {
	uint8_t buffer[1000]={
			0x80, 0x00, 0x75, 0xD5, 0xC9, 0xB8, 0xE9, 0xA5, 0xCD, 0xBC, 0xE8, 0xC4, 0xD4, 0xC4, 0xC4, 0xE0, 
		0xE8, 0xC8, 0xE8, 0xC8, 0xC0, 0xC4, 0xC0, 0xE9, 0x35, 0xCD, 0x9D, 0x11, 0x95, 0x98, 0x00, 0x80, 
		0x00, 0x02, 0x00, 0x00, 0xEB, 0xAB, 0x93, 0x71, 0xD3, 0x23, 0x4B, 0x71, 0xD1, 0xB9, 0x81, 0x89, 
		0x91, 0x89, 0xD1, 0x91, 0xD1, 0x91, 0x81, 0x89, 0x91, 0xD2, 0x6B, 0x9B, 0x3A, 0x23, 0x2B, 0x30, 
		0x01, 0x00, 0x00, 0x08, 0x04, 0x40
	};

	bitstream_t Stream_In;
	int posDecode = 0;
	Stream_In.size 		= BUFFER_SIZE;
	Stream_In.data 		= buffer;
	Stream_In.pos 		= &posDecode;  /* Check */
	Stream_In.buffer  	= 0;
	Stream_In.capacity	= 0;

	V2gFac_Message testingMsg;
	iso2EXIDocument testDoc;
	appHandEXIDocument testApp;
	testingMsg.HandshakeDoc = &testApp;
	testingMsg.iso2Doc = &testDoc;

	int error = V2gFac_decode_Message(&Stream_In, &testingMsg);
	printf("errn: %d", error);
	
}
