/**********************************************************************************************
 *
 * Module: AppHandEXIDatatypes
 *
 * File Name: appHandEXIDatatypes.h
 *
 * Description: Source file of AppHand EXI Datatypes module
 *
 * Author: Omar Reda - Aly Maamoun - Youssef Hussein - Tasneem Essmat
 **********************************************************************************************/

/*****************************
  _____ ______ 
 / ____|  ____|
| (___ | |__   
 \___ \|  __|  
 ____) | |____ 
|_____/|______|
 ******************************/
/*******************************************************************************
 *                               Files includes                                *
 *******************************************************************************/

#include "State_Machine_SWC.h"
 #include "Charging_Status_State_Machine_SWC.h"



/*******************************************************************************
 *                               Updates	                                   *
 *******************************************************************************/
/*
 * 1- In apphandshake , the protocol is selected depending on the lowest priority not the highest , since the lowest in number is the highest one
 * 2- Solved bugs in SessionSetup , some parameters were stored in currentdemand section in the message not in session setup
 * 3- Preparing for run time struct carring all selected parameters from the EV like protocol and payment option, also carring session ID (Fac_RunTimeSelectedOptions)
 * 4- Fac_RunTimeSelectedOptions has init function
 * 5- This init function is now defined in Fac.c
 * 6- new variable from Fac_RunTimeSelectedOptions is instantiated in fac.c and externed in fac.h
 * 7- this instance will replace all global variable in the code , like EV_PaymentServiceSelection_SelectedPaymentOption will no be longer exists
 * 8- SessionIDCheck function is called in every function now to check if the Session ID exists
 * 9- GenChallenge Generator function
 * 10-GenChallenge is implemented and tested , it generate random number depending on the SessionID
 * 11- Preparing for the Supplied parameters struct that carries the parameters that should be supplied from the outside like Electrical parameters and signatures and certificates
 * 12- Fac_SuppliedParameters struct will carry that supplied parameters
 * 13- init Function for that struct callecFac_SuppliedParametersInit will fill the struct with the stubbed values;
 * 14- StubbedParameters is instance of that struct and is externed
 * 15- This instance had replaced all stubbing values
 * 16- EVSE time stamp was removed due to unnecessary
 */


/*******************************************************************************
 *                               Global Variables                              *
 *******************************************************************************/







/*******************************************************************************
 *                             Selected options                                 *
 *******************************************************************************/
/*
 * 1- Protocol
 * 2- Payment option
 * 3- Service selection
 * 4- Session ID (not selected but unique for each session)
 */

/*******************************************************************************
 *                               Selected options                         		*
 *******************************************************************************/


/*******************************************************************************
 *                             Supplied parameters                              *
 *******************************************************************************/
/*
 * 1- Electrical parameters from the grid
 * 2- Signature and certificates from the Server
 * 3- TimeStamp from the Server
 */

/*******************************************************************************
 *                               Supplied parameters                     		*
 *******************************************************************************/



/*******************************************************************************
 *                               Variables Definitions                         *
 *******************************************************************************/

static V2g_stateFunctionRow stateFunc[] =
{
		/* NAME */               				/* FUNCITON */
		{ "UNMATED"								,&UNMATED_Hand							},
		{ "IDLE"								,&IDLE_Hand								},	     //Wait for apphandshakereq
		{ "Handshake_Res"    					,&Handshake_Res_Hand		 			},
		{ "SessionSetup_Res"      				,&SessionSetup_Res_Hand 				},
		{ "ServiceDiscovery_Res"      			,&ServiceDiscovery_Res_Hand 			},
		{ "PaymentServiceSelection_Res"     	,&PaymentServiceSelection_Res_Hand 		},
		{ "PaymentDetails_Res"     				,&PaymentDetails_Res_Hand 				},
		{ "Authorization_Res"      				,&Authorization_Res_Hand 				},
		{ "ChargingParameterDiscovery_Res"     	,&ChargingParameterDiscovery_Res_Hand 	},
		{ "CableCheck_Res"      				,&CableCheck_Res_Hand 					},
		{ "PreCharge_Res"      					,&PreCharge_Res_Hand 					},
		{ "PowerDeliveryInitial_Res"      		,&PowerDeliveryInitial_Res_Hand 		},
		{ "CurrentDemand_Res"      				,&CurrentDemand_Res_Hand 				},
		{ "PowerDeliveryTermination_Res"       	,&PowerDeliveryTermination_Res_Hand 	},
		{ "SessionStop_Res"      				,&SessionStop_Res_Hand 					}
};


static V2g_stateTransMatrixRow stateTransMatrix[] = {
		/* CURRENT STATE */ 					/* EVENT */              				/* NEXT STATE */
		{ UNMATED                           ,MATED                          ,IDLE  						   	},
		{ IDLE   					        ,Handshake_Req 					,Handshake_Res  				},
		{ Handshake_Res						,SessionSetup_Req				,SessionSetup_Res  			    },
		{ SessionSetup_Res					,ServiceDiscovery_Req			,ServiceDiscovery_Res 			},
		{ ServiceDiscovery_Res				,PaymentServiceSelection_Req	,PaymentServiceSelection_Res    },
		{ PaymentServiceSelection_Res		,PaymentDetails_Req				,PaymentDetails_Res  			},
		{ PaymentDetails_Res				,Authorization_Req				,Authorization_Res   			},
		{ Authorization_Res					,ChargingParameterDiscovery_Req	,ChargingParameterDiscovery_Res },
		{ ChargingParameterDiscovery_Res	,CableCheck_Req				    ,CableCheck_Res 				},
		{ CableCheck_Res					,CableCheck_Req			        ,CableCheck_Res  				},
		{ CableCheck_Res					,PreCharge_Req				    ,PreCharge_Res  				},
		{ PreCharge_Res						,PreCharge_Req   		        ,PreCharge_Res    				},
		{ PreCharge_Res						,PowerDeliveryInitial_Req		,PowerDeliveryInitial_Res    	},
		{ PowerDeliveryInitial_Res			,CurrentDemand_Req				,CurrentDemand_Res      		},
		{ CurrentDemand_Res					,CurrentDemand_Req				,CurrentDemand_Res				},
		{ CurrentDemand_Res					,PowerDeliveryTermination_Req	,PowerDeliveryTermination_Res   },
		{ PowerDeliveryTermination_Res		,SessionStop_Req				,SessionStop_Res 				},
		{ SessionStop_Res					,ANY_EVENT						,UNMATED							}
};



/*******************************************************************************
 *                               Function Definitions                          *
 *******************************************************************************/

void StateMachine_Init(V2g_stateMachine * stateMachine) {
	stateMachine->currState = UNMATED;
}


void StateMachine_RunIteration(V2g_stateMachine *stateMachine, V2g_event event) {

	for(int i = 0; i < sizeof(stateTransMatrix)/sizeof(stateTransMatrix[0]); i++)
	{
		if(stateTransMatrix[i].currState == stateMachine->currState)
		{
			if(stateTransMatrix[i].event == event)
			{

				// Transition to the next state
				stateMachine->currState =  stateTransMatrix[i].nextState;

				// Call the function associated with transition
				Fac_StateMachine_State = stateMachine->currState; /* LINE FOR TESTING CHARGING STATUS STATE MACHINE */
				(stateFunc[stateMachine->currState].func)(&V2g_EVReqMessage,&V2g_EVResMessage);
				break;
			}
		}
	}
}


uint8_t powerDelivery_init =0;
V2g_stateMachine SM;

void StateMachine_Runnable(){

	V2g_event currEvent;

	if(mated_init == 0)
	{
		if (1/*call CS RTE Function to check Mating*/)
		{
			currEvent = MATED;
			mated_init = 1;
			ChargingStatus_StateMachine_Runnable();
		}

	}else{
		if ((V2g_EVReqMessage.HandshakeDoc) -> supportedAppProtocolReq_isUsed == 1u){

			currEvent = Handshake_Req;

		}else if(((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.SessionSetupReq_isUsed == 1u){

			currEvent =SessionSetup_Req;


		}else if(((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.ServiceDiscoveryReq_isUsed == 1u){

			currEvent =ServiceDiscovery_Req;


		}else if(((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.PaymentServiceSelectionReq_isUsed == 1u){

			currEvent= PaymentServiceSelection_Req;


		}else if(((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.PaymentDetailsReq_isUsed == 1u){

			currEvent = PaymentDetails_Req;


		}else if(((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.AuthorizationReq_isUsed == 1u){

			currEvent= Authorization_Req;

		}else if(((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq_isUsed == 1u){

			currEvent= ChargingParameterDiscovery_Req;

		}else if(((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.CableCheckReq_isUsed == 1u){

			/* LOOOOOOOOOOOOOOP */
			currEvent = CableCheck_Req;
			//((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.CableCheckReq_isUsed = 0u;

		}else if(((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.PreChargeReq_isUsed == 1u){

			/* LOOOOOOOOOOOOOOOOOP */
			currEvent = PreCharge_Req;
			//((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.PreChargeReq_isUsed = 0u;

		}else if(((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.PowerDeliveryReq_isUsed == 1u){
			//Checking function return termination or initial event
			// Handle cases of initial and termination inside handling functions  (Handling functions will call same function in SWC that fills the response )
			/* LOOOOOOOOOOOOOOOOP */
			if(powerDelivery_init == 0)
			{
				currEvent = PowerDeliveryInitial_Req;
				powerDelivery_init = 1;
			}
			else
			{
				currEvent = PowerDeliveryTermination_Req;
			}



			//((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.PowerDeliveryReq_isUsed = 0u;

		}else if(((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.CurrentDemandReq_isUsed == 1u){

			/* LOOOOOOOOOOOOOOP */
			currEvent = CurrentDemand_Req;
			//((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.CurrentDemandReq_isUsed = 0u;

		}else if (((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.SessionStopReq_isUsed == 1u){

			currEvent = SessionStop_Req;
			//((V2g_EVReqMessage.iso2Doc) -> V2G_Message).Body.SessionStopReq_isUsed = 0u;

		}
		else
		{
			currEvent = IDLE;
		}


	}

	StateMachine_RunIteration(&SM, currEvent);   // Fe init function hat5li el state be IDLE

}

static uint8_t SessionIdChecker (uint8_t *bytesReq,uint8_t bytelenReq ,uint8_t *bytesRes,uint8_t bytelenRes )
{
	if(bytelenReq!=bytelenRes)
	{
		return 0;
	}

	for(uint8_t i=0;i<bytelenReq;i++)
	{
		if(bytesReq[i]!=bytesRes[i])
		{
			return 0;
		}
	}
	return 1;
}


static void GenChallengeGenerator(uint8_t* Bytes,uint8_t BytesLen)
{
	for(uint8_t i=0;i<BytesLen;i++)
	{
		Bytes[i]=(i+1)*RunTimeVaribales.SessionIdArrayPtr[7-i];
		RunTimeVaribales.GenChallenge[i]= Bytes[i];
	}
}

//This function will recieve the AppHandshake request from the EVCC
//The EVCC will send array of supported app protocol
//Each array carries ProtocolNamespace , VersionNumberMajor,Minor , Schema ID, priority
//The EVSE have array of supported app protocols
//each array send from the EVCC must be compared with all supported protocols from the EVSE till matches one
//if one matched , add it's schema id to array of matched protocols
//the following step is sorted based on the priority
//after finishing return the arr[0] as schema ID, if the array is null , return nothing to indicate no matched schema
void Handshake_Res_Hand					(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{

	V2gFac_Message_Init(ResMsg);
	ResMsg->HandshakeDoc_isUsed=1u;

	uint8_t schemaidSupported[20]; //The array that will store the SchemaID of the matched Supported Procotols
	uint8_t schemaPriotrity[20];
	uint8_t SESupportedProtocolsMatched[20];
	/*arrays*/

	/*appHandAnonType_supportedAppProtocolReq Carriers*/
	appHandAnonType_supportedAppProtocolReq EVSE_SupportedProtocol=SE_Fac_Configuration.supportedAppProtocol;
	appHandAnonType_supportedAppProtocolReq EVCC_SupportedProtocol=((ReqMsg->HandshakeDoc)->supportedAppProtocolReq);
	/*appHandAnonType_supportedAppProtocolReq Carriers*/

	/*lengthes*/
	uint8_t EVSE_SupportedProcotolsNumber=SE_Fac_Configuration.supportedAppProtocol.AppProtocol.arrayLen;
	uint8_t EVCC_SupportedProcotolsNumber=((ReqMsg->HandshakeDoc)->supportedAppProtocolReq).AppProtocol.arrayLen;
	/*lengthes*/

	/*Loopers*/
	uint8_t EVCCProtocolLooper;
	uint8_t EVSEProtocolLooper;
	/*Loopers*/

	/*Misc*/
	uint8_t count=0;
	uint8_t SchemaChoosen;
	/*Misc*/

	/*Initializers*/
	schemaidSupported[0]=-1;
	SESupportedProtocolsMatched[0]=-1;
	schemaPriotrity[0]=-1;
	appHandresponseCodeType respStatus = appHandresponseCodeType_OK_SuccessfulNegotiation;
	/*Initializers*/

	if(EVCC_SupportedProcotolsNumber==0)
	{
		respStatus=appHandresponseCodeType_Failed_NoNegotiation;
	}
	for(EVCCProtocolLooper=0;EVCCProtocolLooper<EVCC_SupportedProcotolsNumber;EVCCProtocolLooper++)
	{
		for(EVSEProtocolLooper=0;EVSEProtocolLooper<EVSE_SupportedProcotolsNumber;EVSEProtocolLooper++)
		{
			uint8_t flag=1;
			if(EVSE_SupportedProtocol.AppProtocol.array[EVSEProtocolLooper].ProtocolNamespace.charactersLen==EVCC_SupportedProtocol.AppProtocol.array[EVCCProtocolLooper].ProtocolNamespace.charactersLen)
			{
				uint8_t charactersLen=EVSE_SupportedProtocol.AppProtocol.array[EVSEProtocolLooper].ProtocolNamespace.charactersLen;
				uint8_t characterloop;

				for(characterloop=0;characterloop<charactersLen;characterloop++)
				{
					if(EVSE_SupportedProtocol.AppProtocol.array[EVSEProtocolLooper].ProtocolNamespace.characters[characterloop]!=EVCC_SupportedProtocol.AppProtocol.array[EVCCProtocolLooper].ProtocolNamespace.characters[characterloop])
					{
						flag=0;
						break;
					}
				}
				if(flag)
				{
					if(EVSE_SupportedProtocol.AppProtocol.array[EVSEProtocolLooper].VersionNumberMajor!=EVCC_SupportedProtocol.AppProtocol.array[EVCCProtocolLooper].VersionNumberMajor)
					{
						flag=0;
					}
				}

				if(flag)
				{
					if(EVSE_SupportedProtocol.AppProtocol.array[EVSEProtocolLooper].VersionNumberMinor!=EVCC_SupportedProtocol.AppProtocol.array[EVCCProtocolLooper].VersionNumberMinor)
					{
						respStatus=appHandresponseCodeType_OK_SuccessfulNegotiationWithMinorDeviation;
					}

					schemaidSupported[count]=EVCC_SupportedProtocol.AppProtocol.array[EVCCProtocolLooper].SchemaID;
					schemaPriotrity[count]=EVCC_SupportedProtocol.AppProtocol.array[EVCCProtocolLooper].Priority;
					SESupportedProtocolsMatched[count]=EVSEProtocolLooper;
					count++;
				}

			}
		}
	}
	uint8_t MinimumPriority=20;
	uint8_t index=0;
	for(EVCCProtocolLooper=0;EVCCProtocolLooper<count;EVCCProtocolLooper++)
	{
		if(schemaPriotrity[EVCCProtocolLooper]<MinimumPriority)
		{
			MinimumPriority=schemaPriotrity[EVCCProtocolLooper];
			index=EVCCProtocolLooper;
		}
	}

	V2gFac_init_appHandAnonType_supportedAppProtocolRes(&(((ResMsg->HandshakeDoc)->supportedAppProtocolRes)));
	(ResMsg->HandshakeDoc)->supportedAppProtocolRes_isUsed=1u;
	if(schemaidSupported[0]==255)
	{
		((ResMsg->HandshakeDoc)->supportedAppProtocolRes).SchemaID_isUsed=0u;
		respStatus=appHandresponseCodeType_Failed_NoNegotiation;
	}
	else
	{
		SchemaChoosen=schemaidSupported[index];
		RunTimeVaribales.ProtocolIndex=SESupportedProtocolsMatched[index];
		((ResMsg->HandshakeDoc)->supportedAppProtocolRes).SchemaID=SchemaChoosen;
		((ResMsg->HandshakeDoc)->supportedAppProtocolRes).SchemaID_isUsed=1u;
	}
	((ResMsg->HandshakeDoc)->supportedAppProtocolRes_isUsed)=1u;
	((ResMsg->HandshakeDoc)->supportedAppProtocolRes).ResponseCode=respStatus;
	// V2g_FacSend()

}






void SessionSetup_Res_Hand				(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;
	iso2responseCodeType respStatus = iso2responseCodeType_OK_NewSessionEstablished;															//initially the response code is ok
	(ResMsg->iso2Doc) -> V2G_Message_isUsed = 1u;												//v2g message is used
	V2gFac_init_iso2BodyType(&(((ResMsg->iso2Doc) -> V2G_Message).Body));								//reseting all is used messages
	((ResMsg->iso2Doc) -> V2G_Message).Body.SessionSetupRes_isUsed = 1u;						//setting is used for session setup res
	V2gFac_init_iso2SessionSetupResType(&(((ResMsg->iso2Doc) -> V2G_Message).Body.SessionSetupRes));   //making timestamp and evse statues not used
	for(uint8_t i=0; i<8; i++) /* Fill Message Header SessionID with 01234567 {hard coded initially} */
	{
		((ResMsg->iso2Doc) -> V2G_Message).Header.SessionID.bytes[i] = i;
		RunTimeVaribales.SessionIdArrayPtr[i]=i;
	}
	((ResMsg->iso2Doc) -> V2G_Message).Header.SessionID.bytesLen = 8;
	RunTimeVaribales.SessionIdLen=(((ResMsg->iso2Doc) -> V2G_Message).Header.SessionID.bytesLen);
								//Session Id bytes length is 8
	((ResMsg->iso2Doc) -> V2G_Message).Header.Signature_isUsed = 0u;							//No signature
	((ResMsg->iso2Doc) -> V2G_Message).Body.SessionSetupRes.EVSEID.charactersLen=SE_Fac_Configuration.EVSEID.EVSEID.charactersLen;
	for(uint8_t i=0;i<SE_Fac_Configuration.EVSEID.EVSEID.charactersLen;i++)
	{
		((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes.EVSEID.characters[i]=SE_Fac_Configuration.EVSEID.EVSEID.characters[i];
	}
	((ResMsg->iso2Doc) -> V2G_Message).Body.SessionSetupRes.ResponseCode=respStatus;			//writing the response code

	// V2g_FacSend() 
}


/* ERRRRRROOOOOOOOOOOOOORRRRRRRR */
void ServiceDiscovery_Res_Hand			(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	//init for the v2g message

	V2gFac_Message_Init(ResMsg);
	//This message is iso2Doc
	ResMsg->iso2Doc_isUsed=1u;
	//Response Code initially is OK
	iso2responseCodeType respStatus = iso2responseCodeType_OK;
	//enable the message
	(ResMsg->iso2Doc) -> V2G_Message_isUsed = 1u;
	//resetting all is used fields
	V2gFac_init_iso2BodyType(&(((ResMsg->iso2Doc) -> V2G_Message).Body));
	//Resetting is used for the EVSE statues and VASLIST "will not be used"
	V2gFac_init_iso2ServiceDiscoveryResType(&(((ResMsg->iso2Doc) -> V2G_Message).Body.ServiceDiscoveryRes));
	//setting Service discovery is used field
	((ResMsg->iso2Doc) -> V2G_Message).Body.ServiceDiscoveryRes_isUsed = 1u;
	if(!SessionIdChecker(ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytes, ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytesLen, (RunTimeVaribales.SessionIdArrayPtr), RunTimeVaribales.SessionIdLen))
	{
		respStatus=iso2responseCodeType_FAILED_UnknownSession;
	}
	//loading the configuration parameters for the Service list
	//loading the number of services provided for the energy transfer
	((ResMsg->iso2Doc) -> V2G_Message).Body.ServiceDiscoveryRes.EnergyTransferServiceList.Service.arrayLen = SE_Fac_Configuration.ServiceIDList.Service.arrayLen;
	for(uint8_t i=0;i<SE_Fac_Configuration.ServiceIDList.Service.arrayLen;i++)
	{
		((ResMsg->iso2Doc) -> V2G_Message).Body.ServiceDiscoveryRes.EnergyTransferServiceList.Service.array[i].ServiceID = SE_Fac_Configuration.ServiceIDList.Service.array[i].ServiceID;
		((ResMsg->iso2Doc) -> V2G_Message).Body.ServiceDiscoveryRes.EnergyTransferServiceList.Service.array[i].FreeService=SE_Fac_Configuration.ServiceIDList.Service.array[i].FreeService;
	}
	((ResMsg->iso2Doc) -> V2G_Message).Body.ServiceDiscoveryRes.PaymentOptionList.PaymentOption.arrayLen=SE_Fac_Configuration.PaymentOptionList.PaymentOption.arrayLen;
	for(uint8_t i=0;i<SE_Fac_Configuration.PaymentOptionList.PaymentOption.arrayLen;i++)
	{
		((ResMsg->iso2Doc) -> V2G_Message).Body.ServiceDiscoveryRes.PaymentOptionList.PaymentOption.array[i]=SE_Fac_Configuration.PaymentOptionList.PaymentOption.array[i];
	}
	//Writing Response code on the message before sending
	((ResMsg->iso2Doc) -> V2G_Message).Body.ServiceDiscoveryRes.ResponseCode=respStatus;
	// V2g_FacSend() 
}


//Updates needed , check if the service and payment selected is provided by the SE
void PaymentServiceSelection_Res_Hand 		(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;
	//initial is ok
	iso2responseCodeType respStatus = iso2responseCodeType_OK;
	if(!SessionIdChecker(ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytes, ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytesLen, RunTimeVaribales.SessionIdArrayPtr, RunTimeVaribales.SessionIdLen))
	{
		respStatus=iso2responseCodeType_FAILED_UnknownSession;
	}
	else
	{
		//Check if the selected paymentServiceSelect is valid
		if(((ReqMsg->iso2Doc) -> V2G_Message).Body.PaymentServiceSelectionReq.SelectedPaymentOption!=1 &&((ReqMsg->iso2Doc) -> V2G_Message).Body.PaymentServiceSelectionReq.SelectedPaymentOption!=2)
		{
			//update the response code with non valid statues
			respStatus=iso2responseCodeType_FAILED_PaymentSelectionInvalid;
		}
		//if not valid skip this part to save time
		else
		{
			//Save it to the global variable to be used later
			RunTimeVaribales.PaymentOptionSelected=((ReqMsg->iso2Doc) -> V2G_Message).Body.PaymentServiceSelectionReq.SelectedPaymentOption;
			//Check if the selected Service id is valid
			if(((ReqMsg->iso2Doc) -> V2G_Message).Body.PaymentServiceSelectionReq.SelectedEnergyTransferService.ServiceID==0||((ReqMsg->iso2Doc) -> V2G_Message).Body.PaymentServiceSelectionReq.SelectedEnergyTransferService.ServiceID>4)
			{
				//update the response code with non valid statues
				respStatus= iso2responseCodeType_FAILED_ServiceSelectionInvalid;
			}
			//update the response code with non valid statues
			else
			{
				//Save it to the global variable to be used later
				RunTimeVaribales.ServiceSelected=((ReqMsg->iso2Doc) -> V2G_Message).Body.PaymentServiceSelectionReq.SelectedEnergyTransferService.ServiceID;
				//Save it to the global variable to be used later
				RunTimeVaribales.ParameterServiceSelected=((ReqMsg->iso2Doc) -> V2G_Message).Body.PaymentServiceSelectionReq.SelectedEnergyTransferService.ParameterSetID;
			}
		}
	}

	(ResMsg->iso2Doc) -> V2G_Message_isUsed = 1u;														//enable the message
	V2gFac_init_iso2BodyType(&(((ResMsg->iso2Doc) -> V2G_Message).Body));										//resetting all is used fields
	((ResMsg->iso2Doc) -> V2G_Message).Body.PaymentServiceSelectionRes_isUsed = 1u;						//set bit field is used of this message
	V2gFac_init_iso2PaymentServiceSelectionResType(&(((ResMsg->iso2Doc) -> V2G_Message).Body.PaymentServiceSelectionRes));//reset all is used inside the struct of the message
	((ResMsg->iso2Doc) -> V2G_Message).Body.PaymentServiceSelectionRes.ResponseCode=respStatus;			//Write the response code in the message to send
	// V2g_FacSend() 


}


//stubed
//Updates needed , create function to generate random GenChallenge
void PaymentDetails_Res_Hand			(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;
	//stubed response code due to certificates
	iso2responseCodeType respStatus = iso2responseCodeType_OK_CertificateExpiresSoon;
	//enable messages
	(ResMsg->iso2Doc) -> V2G_Message_isUsed = 1u;
	//disable all is used messages
	V2gFac_init_iso2BodyType(&(((ResMsg->iso2Doc) -> V2G_Message).Body));
	//enable is used field for this message type
	((ResMsg->iso2Doc) -> V2G_Message).Body.PaymentDetailsRes_isUsed = 1u;
	//resetting all is used fields inside the structure of this message
	V2gFac_init_iso2PaymentDetailsResType(&(((ResMsg->iso2Doc) -> V2G_Message).Body.PaymentDetailsRes));
	((ResMsg->iso2Doc) -> V2G_Message).Body.PaymentDetailsRes.GenChallenge.bytesLen = 8;
	GenChallengeGenerator((((ResMsg->iso2Doc) -> V2G_Message).Body.PaymentDetailsRes.GenChallenge.bytes), 8);
	//Writing responseCode to the message
	if(!SessionIdChecker(ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytes, ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytesLen, RunTimeVaribales.SessionIdArrayPtr, RunTimeVaribales.SessionIdLen))
	{
		respStatus=iso2responseCodeType_FAILED_UnknownSession;
	}
	((ResMsg->iso2Doc) -> V2G_Message).Body.PaymentDetailsRes.ResponseCode=respStatus;	
	// V2g_FacSend() 
}



void Authorization_Res_Hand				(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;
	//initially the response code is ok unless it met a condition that make it not ok
	iso2responseCodeType respStatus = iso2responseCodeType_OK;
	if(!SessionIdChecker(ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytes, ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytesLen, RunTimeVaribales.SessionIdArrayPtr, RunTimeVaribales.SessionIdLen))
	{
		respStatus=iso2responseCodeType_FAILED_UnknownSession;
	}
	else
	{
		//if the genChallenge recieved is not the same that was sent so there's an error
		if(((ReqMsg->iso2Doc) -> V2G_Message).Body.AuthorizationReq.GenChallenge.bytesLen!=RunTimeVaribales.GenChallengeLen)
		{
			respStatus = iso2responseCodeType_FAILED_ChallengeInvalid;
		}
		else
		{
			for(int i=0;i<RunTimeVaribales.GenChallengeLen;i++)
			{
				if(((ReqMsg->iso2Doc) -> V2G_Message).Body.AuthorizationReq.GenChallenge.bytes[i]!=RunTimeVaribales.GenChallenge[i])
				{
					respStatus = iso2responseCodeType_FAILED_ChallengeInvalid;
					break;
				}
			}

		}
	}
	//enable messages
	(ResMsg->iso2Doc) -> V2G_Message_isUsed = 1u;
	//reset all is used
	V2gFac_init_iso2BodyType(&(((ResMsg->iso2Doc) -> V2G_Message).Body));
	//enable this message in the is used
	((ResMsg->iso2Doc) -> V2G_Message).Body.AuthorizationRes_isUsed = 1u;
	//reset all is used fields inside the structure of this message
	V2gFac_init_iso2AuthorizationResType(&(((ResMsg->iso2Doc) -> V2G_Message).Body.AuthorizationRes));
	//Write the response code to the message
	((ResMsg->iso2Doc) -> V2G_Message).Body.AuthorizationRes.ResponseCode=respStatus;
	//Write the processing type of the SE to the message
	((ResMsg->iso2Doc) -> V2G_Message).Body.AuthorizationRes.EVSEProcessing=iso2EVSEProcessingType_Ongoing;
	// V2g_FacSend() 
}





void ChargingParameterDiscovery_Res_Hand(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;
	//initially the response code is ok unless it met a condition that make it not ok
	iso2responseCodeType respStatus = iso2responseCodeType_OK;
	//stubbet parameters , this parameters should be taken from the grid


	uint8_t EVCCMaxChargePowerValue =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMaximumChargePower.Value	;
	uint8_t EVCCMinChargePowerValue =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMinimumChargePower.Value	;
	uint8_t EVCCMaxChargeCurrValue  =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMaximumChargeCurrent.Value;
	uint8_t EVCCMinChargeCurrValue  =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMinimumChargeCurrent.Value;
	uint8_t EVCCMaxChargeVoltValue  =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMaximumVoltage.Value		;
	uint8_t EVCCTargetEnergyReqValue=((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVTargetEnergyRequest.Value	;
	uint8_t EVCCMaxEnergyReqValue   =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMaximumEnergyRequest.Value;
	uint8_t EVCCMinEnergyReqValue   =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMinimumEnergyRequest.Value;

	uint8_t EVCCMaxChargePowerExp   =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMaximumChargePower.Exponent	;
	uint8_t EVCCMinChargePowerExp   =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMinimumChargePower.Exponent	;
	uint8_t EVCCMaxChargeCurrExp    =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMaximumChargeCurrent.Exponent	;
	uint8_t EVCCMinChargeCurrExp    =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMinimumChargeCurrent.Exponent	;
	uint8_t EVCCMaxChargeVoltExp    =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMaximumVoltage.Exponent		;
	uint8_t EVCCTargetEnergyReqExp  =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVTargetEnergyRequest.Exponent	;
	uint8_t EVCCMaxEnergyReqExp     =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMaximumEnergyRequest.Exponent	;
	uint8_t EVCCMinEnergyReqExp     =((ReqMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter.EVMinimumEnergyRequest.Exponent	;

	// if max value in the SE is less than min value in the EV or min value in the SE is higher than max value in EV then stop the process and set the responseCode by failed
	if(EVCCMinChargePowerValue>StubbedParameters.GridParameters.EVSEMaximumChargePower.Value || EVCCMinChargeCurrValue>StubbedParameters.GridParameters.EVSEMaximumChargeCurrent.Value || EVCCMinEnergyReqValue>StubbedParameters.GridParameters.EVSEEnergyToBeDelivered.Value ||EVCCMaxChargeCurrValue <StubbedParameters.GridParameters.EVSEMinimumChargeCurrent.Value || EVCCMaxChargeVoltValue<StubbedParameters.GridParameters.EVSEMinimumVoltage.Value||EVCCTargetEnergyReqValue>StubbedParameters.GridParameters.EVSEEnergyToBeDelivered.Value)
	{
		respStatus=iso2responseCodeType_FAILED;
	}

	//enable messages
	(ResMsg->iso2Doc) -> V2G_Message_isUsed = 1u;
	//reset all is used
	V2gFac_init_iso2BodyType(&(((ResMsg->iso2Doc) -> V2G_Message).Body));
	//enable this message in the is used
	((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes_isUsed = 1u;
	//reset all is used fields inside the structure of this message
	V2gFac_init_iso2ChargeParameterDiscoveryResType(&(((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes));
	//Write the response code to the message
	((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.ResponseCode=respStatus;

	if(!SessionIdChecker(ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytes, ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytesLen, RunTimeVaribales.SessionIdArrayPtr, RunTimeVaribales.SessionIdLen))
	{
		respStatus=iso2responseCodeType_FAILED_UnknownSession;
	}
	else
	{
		if(respStatus==iso2responseCodeType_FAILED)
		{
			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.EVSEStatus.EVSENotification=iso2EVSENotificationType_StopCharging;
		}
		else
		{
			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.EVSEStatus.EVSENotification=iso2EVSENotificationType_ReNegotiation;
			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter_isUsed=1u;
			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.EVSEStatus.NotificationMaxDelay=5u;

			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter.EVSEMaximumChargePower.Value=StubbedParameters.GridParameters.EVSEMaximumChargePower.Value;
			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter.EVSEMaximumChargePower.Exponent=StubbedParameters.GridParameters.EVSEMaximumChargePower.Exponent;

			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter.EVSEMaximumChargeCurrent.Value=StubbedParameters.GridParameters.EVSEMaximumChargeCurrent.Value;
			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter.EVSEMaximumChargeCurrent.Exponent=StubbedParameters.GridParameters.EVSEMaximumChargeCurrent.Exponent;

			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter.EVSEMinimumChargeCurrent.Value=StubbedParameters.GridParameters.EVSEMinimumChargeCurrent.Value;
			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter.EVSEMinimumChargeCurrent.Exponent=StubbedParameters.GridParameters.EVSEMinimumChargeCurrent.Exponent;

			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter.EVSEMaximumVoltage.Value=StubbedParameters.GridParameters.EVSEMaximumVoltage.Value;
			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter.EVSEMaximumVoltage.Exponent=StubbedParameters.GridParameters.EVSEMaximumVoltage.Exponent;

			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter.EVSEMinimumVoltage.Value=StubbedParameters.GridParameters.EVSEMinimumVoltage.Value;
			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter.EVSEMinimumVoltage.Exponent=StubbedParameters.GridParameters.EVSEMinimumVoltage.Exponent;

			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter.EVSEPeakCurrentRipple.Value=StubbedParameters.GridParameters.EVSEPeakCurrentRipple.Value;
			((ResMsg->iso2Doc) -> V2G_Message).Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter.EVSEPeakCurrentRipple.Exponent=StubbedParameters.GridParameters.EVSEPeakCurrentRipple.Exponent;
		}

	}
	// V2g_FacSend() 

}




void CableCheck_Res_Hand				(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;
	//initially the response code is ok unless it met a condition that make it not ok
	iso2responseCodeType respStatus = iso2responseCodeType_OK;
	//enable messages
	((ResMsg->iso2Doc) -> V2G_Message_isUsed) = 1u;
	//reset all is used
	V2gFac_init_iso2BodyType(&(((ResMsg->iso2Doc) -> V2G_Message).Body));
	//enable this message in the is used
	((ResMsg->iso2Doc) -> V2G_Message).Body.CableCheckRes_isUsed = 1u;
	//reset all is used fields inside the structure of this message
	V2gFac_init_iso2CableCheckResType(&(((ResMsg->iso2Doc) -> V2G_Message).Body.CableCheckRes));
	//Write the response code to the message
	if(!SessionIdChecker(ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytes, ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytesLen, RunTimeVaribales.SessionIdArrayPtr, RunTimeVaribales.SessionIdLen))
	{
		respStatus=iso2responseCodeType_FAILED_UnknownSession;
	}
	((ResMsg->iso2Doc) -> V2G_Message).Body.CableCheckRes.ResponseCode=respStatus;
	((ResMsg->iso2Doc) -> V2G_Message).Body.CableCheckRes.EVSEProcessing=iso2EVSEProcessingType_Ongoing;
	// V2g_FacSend() 


}




void PreCharge_Res_Hand					(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;
	//initially the response code is ok unless it met a condition that make it not ok
	iso2responseCodeType respStatus = iso2responseCodeType_OK;
	uint8_t EVTargetVoltageValue=((ReqMsg->iso2Doc) -> V2G_Message).Body.PreChargeReq.EVTargetVoltage.Value;
	uint8_t EVTargetCurrentValue=((ReqMsg->iso2Doc) -> V2G_Message).Body.PreChargeReq.EVTargetCurrent.Value;
	uint8_t EVTargetVoltageExpo =((ReqMsg->iso2Doc) -> V2G_Message).Body.PreChargeReq.EVTargetVoltage.Exponent;
	uint8_t EVTargetCurrentExpo =((ReqMsg->iso2Doc) -> V2G_Message).Body.PreChargeReq.EVTargetCurrent.Exponent;

	if(EVTargetVoltageValue>StubbedParameters.GridParameters.EVSEMaximumVoltage.Value || EVTargetVoltageValue<StubbedParameters.GridParameters.EVSEMinimumVoltage.Value ||EVTargetCurrentValue>StubbedParameters.GridParameters.EVSEMaximumChargeCurrent.Value ||EVTargetCurrentValue<StubbedParameters.GridParameters.EVSEMinimumChargeCurrent.Value)
	{
		respStatus = iso2responseCodeType_FAILED;
	}
	//enable messages
	(ResMsg->iso2Doc) -> V2G_Message_isUsed = 1u;
	//reset all is used
	V2gFac_init_iso2BodyType(&(((ResMsg->iso2Doc) -> V2G_Message).Body));
	//enable this message in the is used
	((ResMsg->iso2Doc) -> V2G_Message).Body.PreChargeRes_isUsed = 1u;
	//reset all is used fields inside the structure of this message
	V2gFac_init_iso2PreChargeResType(&(((ResMsg->iso2Doc) -> V2G_Message).Body.PreChargeRes));
	//Write the response code to the message
	if(!SessionIdChecker(ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytes, ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytesLen, RunTimeVaribales.SessionIdArrayPtr, RunTimeVaribales.SessionIdLen))
	{
		respStatus=iso2responseCodeType_FAILED_UnknownSession;
	}
	((ResMsg->iso2Doc) -> V2G_Message).Body.PreChargeRes.ResponseCode=respStatus;
	if(respStatus==iso2responseCodeType_OK)
	{
		((ResMsg->iso2Doc) -> V2G_Message).Body.PreChargeRes.EVSEPresentVoltage.Value=EVTargetVoltageValue;
		((ResMsg->iso2Doc) -> V2G_Message).Body.PreChargeRes.EVSEPresentVoltage.Exponent=EVTargetVoltageExpo;
	}
	// V2g_FacSend() 


}



void PowerDeliveryInitial_Res_Hand			(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;
	//initially the response code is ok unless it met a condition that make it not ok
	iso2responseCodeType respStatus = iso2responseCodeType_OK;
	if(((ReqMsg->iso2Doc) -> V2G_Message).Body.PowerDeliveryReq.ChargeProgress==iso2chargeProgressType_Stop)
	{
		respStatus=iso2responseCodeType_FAILED_SequenceError;
	}

	//enable messages
	(ResMsg->iso2Doc) -> V2G_Message_isUsed = 1u;
	//reset all is used
	V2gFac_init_iso2BodyType(&(((ResMsg->iso2Doc) -> V2G_Message).Body));
	//enable this message in the is used
	((ResMsg->iso2Doc) -> V2G_Message).Body.PowerDeliveryRes_isUsed = 1u;
	//reset all is used fields inside the structure of this message
	V2gFac_init_iso2PowerDeliveryResType(&(((ResMsg->iso2Doc) -> V2G_Message).Body.PowerDeliveryRes));
	//Write the response code to the message
	if(!SessionIdChecker(ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytes, ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytesLen, RunTimeVaribales.SessionIdArrayPtr, RunTimeVaribales.SessionIdLen))
	{
		respStatus=iso2responseCodeType_FAILED_UnknownSession;
	}
	((ResMsg->iso2Doc) -> V2G_Message).Body.PowerDeliveryRes.ResponseCode=respStatus;
	((ResMsg->iso2Doc) -> V2G_Message).Body.PowerDeliveryRes.EVSEProcessing=iso2EVSEProcessingType_Ongoing;
	// V2g_FacSend() 
}



void PowerDeliveryTermination_Res_Hand		(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;
	//initially the response code is ok unless it met a condition that make it not ok
	iso2responseCodeType respStatus = iso2responseCodeType_OK;
	if(((ReqMsg->iso2Doc) -> V2G_Message).Body.PowerDeliveryReq.ChargeProgress!=iso2chargeProgressType_Stop)
	{
		respStatus=iso2responseCodeType_FAILED_SequenceError;
	}

	//enable messages
	(ResMsg->iso2Doc) -> V2G_Message_isUsed = 1u;
	//reset all is used
	V2gFac_init_iso2BodyType(&(((ResMsg->iso2Doc) -> V2G_Message).Body));
	//enable this message in the is used
	((ResMsg->iso2Doc) -> V2G_Message).Body.PowerDeliveryRes_isUsed = 1u;
	//reset all is used fields inside the structure of this message
	V2gFac_init_iso2PowerDeliveryResType(&(((ResMsg->iso2Doc) -> V2G_Message).Body.PowerDeliveryRes));
	//Write the response code to the message
	if(!SessionIdChecker(ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytes, ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytesLen, RunTimeVaribales.SessionIdArrayPtr, RunTimeVaribales.SessionIdLen))
	{
		respStatus=iso2responseCodeType_FAILED_UnknownSession;
	}
	((ResMsg->iso2Doc) -> V2G_Message).Body.PowerDeliveryRes.ResponseCode=respStatus;
	((ResMsg->iso2Doc) -> V2G_Message).Body.PowerDeliveryRes.EVSEProcessing=iso2EVSEProcessingType_Ongoing;
	// V2g_FacSend() 


}
//Check the DisplayParameters if the charging is complete or not
//Check if the the target current and voltage is in the acceptance range from the grid ( GridMinCurrent<TargetCurrent<GridMaxCurrent )
//if not in acceptance set the flag for example EVSECurrentLimitAchieved to let the EVCC know and take decision and Write warning in response code
//prepare the message by setting the v2g message and reset all is used and clear the content of the message
//Write the response code
//Write the present parameters (like EVSEPresentCurrent)
//Write the EVSE ID
//Write the EVSE statues
//Write the flags
//send the message
void CurrentDemand_Res_Hand				(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;
	//initially ok
	iso2responseCodeType respStatus = iso2responseCodeType_OK;
	uint8_t CurrentLimitFlag=0;
	uint8_t VoltagelimitFlag=0;
	uint8_t PowerLimirFlag=0;
	//Check the DisplayParameters if the charging is complete or not
	if(((ReqMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandReq.DisplayParameters.ChargingComplete==1u)
	{

	}
	//if not in acceptance set the flag for example EVSECurrentLimitAchieved to let the EVCC know and take decision and Write warning in response code
	if(((ReqMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandReq.EVTargetCurrent.Value>StubbedParameters.GridParameters.EVSEMaximumChargeCurrent.Value ||((ReqMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandReq.EVTargetCurrent.Value<StubbedParameters.GridParameters.EVSEMinimumChargeCurrent.Value)
	{
		CurrentLimitFlag=1;
		respStatus=iso2responseCodeType_FAILED;
	}
	if(((ReqMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandReq.EVTargetVoltage.Value>StubbedParameters.GridParameters.EVSEMaximumVoltage.Value||((ReqMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandReq.EVTargetVoltage.Value<StubbedParameters.GridParameters.EVSEMinimumVoltage.Value)
	{
		CurrentLimitFlag=1;
		respStatus=iso2responseCodeType_FAILED;
	}
	//enable messages
	(ResMsg->iso2Doc) -> V2G_Message_isUsed = 1u;
	//reset all is used
	V2gFac_init_iso2BodyType(&(((ResMsg->iso2Doc) -> V2G_Message).Body));
	//enable this message in the is used
	((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes_isUsed = 1u;
	V2gFac_init_iso2CurrentDemandResType(&(((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes));
	if(!SessionIdChecker(ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytes, ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytesLen, RunTimeVaribales.SessionIdArrayPtr, RunTimeVaribales.SessionIdLen))
	{
		respStatus=iso2responseCodeType_FAILED_UnknownSession;
	}
	((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes.ResponseCode=respStatus;
	((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes.EVSEVoltageLimitAchieved=VoltagelimitFlag;
	((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes.EVSECurrentLimitAchieved=CurrentLimitFlag;
	((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes.EVSEPowerLimitAchieved=PowerLimirFlag;
	((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes.EVSEID.charactersLen=SE_Fac_Configuration.EVSEID.EVSEID.charactersLen;
	for(uint8_t i=0;i<SE_Fac_Configuration.EVSEID.EVSEID.charactersLen;i++)
	{
		((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes.EVSEID.characters[i]=SE_Fac_Configuration.EVSEID.EVSEID.characters[i];
	}
	if(respStatus==iso2responseCodeType_OK)
	{
		((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes.EVSEPresentCurrent.Value=((ReqMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandReq.EVTargetCurrent.Value;
		((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes.EVSEPresentCurrent.Exponent=((ReqMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandReq.EVTargetCurrent.Exponent;
		((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes.EVSEPresentVoltage.Value=((ReqMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandReq.EVTargetVoltage.Value;
		((ResMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandRes.EVSEPresentVoltage.Exponent=((ReqMsg->iso2Doc) -> V2G_Message).Body.CurrentDemandReq.EVTargetVoltage.Exponent;		
	}


	// V2g_FacSend() 
}





void SessionStop_Res_Hand				(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;
	//initially the response code is ok unless it met a condition that make it not ok
	iso2responseCodeType respStatus = iso2responseCodeType_OK;
	//enable messages
	(ResMsg->iso2Doc) -> V2G_Message_isUsed = 1u;
	//reset all is used
	V2gFac_init_iso2BodyType(&(((ResMsg->iso2Doc) -> V2G_Message).Body));
	//enable this message in the is used
	((ResMsg->iso2Doc) -> V2G_Message).Body.SessionStopRes_isUsed = 1u;
	//reset all is used fields inside the structure of this message
	V2gFac_init_iso2SessionStopResType(&(((ResMsg->iso2Doc) -> V2G_Message).Body.SessionStopRes));
	//Write the response code to the message
	if(!SessionIdChecker(ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytes, ReqMsg->iso2Doc->V2G_Message.Header.SessionID.bytesLen, RunTimeVaribales.SessionIdArrayPtr, RunTimeVaribales.SessionIdLen))
	{
		respStatus=iso2responseCodeType_FAILED_UnknownSession;
	}
	((ResMsg->iso2Doc) -> V2G_Message).Body.SessionStopRes.ResponseCode=respStatus;
	// V2g_FacSend() 
}
void IDLE_Hand(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg )
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;

}
void UNMATED_Hand(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg)
{
	V2gFac_Message_Init(ResMsg);
	ResMsg->iso2Doc_isUsed=1u;

}


/*

typedef enum {
	iso2responseCodeType_OK = 0,
	iso2responseCodeType_OK_NewSessionEstablished = 1,
	iso2responseCodeType_OK_OldSessionJoined = 2,
	iso2responseCodeType_OK_CertificateExpiresSoon = 3,
	iso2responseCodeType_OK_IsolationValid = 4,
	iso2responseCodeType_OK_IsolationWarning = 5,
	iso2responseCodeType_WARNING_CertificateExpired = 6,
	iso2responseCodeType_WARNING_NoCertificateAvailable = 7,
	iso2responseCodeType_WARNING_CertValidationError = 8,
	iso2responseCodeType_WARNING_CertVerificationError = 9,
	iso2responseCodeType_WARNING_ContractCanceled = 10,
	iso2responseCodeType_FAILED = 11,
	iso2responseCodeType_FAILED_SequenceError = 12,
	iso2responseCodeType_FAILED_ServiceIDInvalid = 13,
	iso2responseCodeType_FAILED_UnknownSession = 14,
	iso2responseCodeType_FAILED_ServiceSelectionInvalid = 15,
	iso2responseCodeType_FAILED_SignatureError = 16,
	iso2responseCodeType_FAILED_PaymentSelectionInvalid = 17,
	iso2responseCodeType_FAILED_ChallengeInvalid = 18,
	iso2responseCodeType_FAILED_WrongChargeParameter = 19,
	iso2responseCodeType_FAILED_IsolationFault = 20,
	iso2responseCodeType_FAILED_PowerDeliveryNotApplied = 21,
	iso2responseCodeType_FAILED_TariffSelectionInvalid = 22,
	iso2responseCodeType_FAILED_ChargingProfileInvalid = 23,
	iso2responseCodeType_FAILED_MeteringSignatureNotValid = 24,
	iso2responseCodeType_FAILED_NoChargeServiceSelected = 25,
	iso2responseCodeType_FAILED_WrongEnergyTransferMode = 26,
	iso2responseCodeType_FAILED_ContactorError = 27,
	iso2responseCodeType_FAILED_CertificateRevoked = 28,
	iso2responseCodeType_FAILED_CertificateNotYetValid = 29
} iso2responseCodeType;

 */
//217//
