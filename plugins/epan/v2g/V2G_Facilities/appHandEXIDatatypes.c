/**********************************************************************************************
 *
 * Module: V2xFac
 *
 * File Name: V2xFac.c
 *
 * Description: Source file of V2xFac module
 *
 * Author: Omar reda - Aly maamoun
 **********************************************************************************************/




/*******************************************************************************
 *                               Files includes                                *
 *******************************************************************************/
#include "appHandEXIDatatypes.h"
#include "EXITypes.h"



/*******************************************************************************
 *                      Function Definitons                                    *
 *******************************************************************************/
 
/************************************************************************************
 * Service Name: init_appHandEXIDocument
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): exiDoc - points to the  that holds the elements of the appHandShake .
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the appHandShake parameters by resetting the is used parameters.
 * Available via: appHandEXIDatatypes.h
 * Requirement: [

 ************************************************************************************/
 void V2gFac_init_appHandEXIDocument( appHandEXIDocument* exiDoc) {
	exiDoc->supportedAppProtocolReq_isUsed = 0u;
	exiDoc->supportedAppProtocolRes_isUsed = 0u;
}



/************************************************************************************
 * Service Name: init_appHandAppProtocolType
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): exiDoc - points to the  that holds the elements of the appHandShake .
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes The Apphandshake protocol.
 * Available via: appHandEXIDatatypes.h
 * Requirement: 

 ************************************************************************************/
void V2gFac_init_appHandAppProtocolType( appHandAppProtocolType* appHandAppProtocolType) {
}


/************************************************************************************
 * Service Name: init_appHandAnonType_supportedAppProtocolReq
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): appHandAnonType_supportedAppProtocolReq - Points to the  that carries the parameters of AppHandShake Request.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Reseting the parameter of the Request side .
 * Available via: appHandEXIDatatypes.h
 * Requirement: 

 ************************************************************************************/
void V2gFac_init_appHandAnonType_supportedAppProtocolReq( appHandAnonType_supportedAppProtocolReq* appHandAnonType_supportedAppProtocolReq) {
	appHandAnonType_supportedAppProtocolReq->AppProtocol.arrayLen = 0u;
}

/*---------------------------------- APIs Implementation -----------------------------------*/
/************************************************************************************
 * Service Name: init_appHandAnonType_supportedAppProtocolRes
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): appHandAnonType_supportedAppProtocolRes - Points to the  that carries the elements of Apphandshake protocol respond.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Reseting the parameter SchemaID_isUsed for the respond.
 * Available via: appHandEXIDatatypes.h
 * Requirement: 

 ************************************************************************************/
void V2gFac_init_appHandAnonType_supportedAppProtocolRes( appHandAnonType_supportedAppProtocolRes* appHandAnonType_supportedAppProtocolRes) {
	appHandAnonType_supportedAppProtocolRes->SchemaID_isUsed = 0u;
}

