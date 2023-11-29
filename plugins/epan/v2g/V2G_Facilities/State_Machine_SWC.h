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

#ifndef STATE_MACHINE_SWC_H
#define STATE_MACHINE_SWC_H

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

#include <stdint.h>
#include "EXITypes.h"
#include "iso2EXIDatatypes.h"
#include "appHandEXIDatatypes.h"
#include "ErrorCodes.h"
#include "Fac.h"


/*******************************************************************************
 *                               Type Definitons                               *
 *******************************************************************************/
typedef enum {
	UNMATED,
	IDLE,
	Handshake_Res,
	SessionSetup_Res,
	ServiceDiscovery_Res,
	PaymentServiceSelection_Res,
	PaymentDetails_Res,
	Authorization_Res,
	ChargingParameterDiscovery_Res,
	CableCheck_Res,
	PreCharge_Res,
	PowerDeliveryInitial_Res,
	CurrentDemand_Res,
	PowerDeliveryTermination_Res,
	SessionStop_Res
	}V2g_state;

typedef enum {
	MATED,
   	Handshake_Req,
	SessionSetup_Req,
	ServiceDiscovery_Req,
	PaymentServiceSelection_Req,
	PaymentDetails_Req,
	Authorization_Req,
	ChargingParameterDiscovery_Req,
	CableCheck_Req,
	PreCharge_Req,
	PowerDeliveryInitial_Req,
	CurrentDemand_Req,
	PowerDeliveryTermination_Req,
	SessionStop_Req,
	ANY_EVENT
} V2g_event;

typedef struct {
	V2g_state currState;
}V2g_stateMachine;

typedef struct {
    const char * name;
    void (*func)(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg);
} V2g_stateFunctionRow;

typedef struct {
	V2g_state currState;
	V2g_event event;
    V2g_state nextState;
} V2g_stateTransMatrixRow;




/*******************************************************************************
 *                               Function Prototypes                           *
 *******************************************************************************/
void StateMachine_Init(V2g_stateMachine * stateMachine);
void StateMachine_RunIteration(V2g_stateMachine *stateMachine, V2g_event event);


/************* Handling Functions *************/

/* ReqMsg For SE, Is the Filled Msg from EV / ResMsg for SE , is the Msg will be formed */
void StateMachine_Runnable();
void Handshake_Res_Hand					(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void SessionSetup_Res_Hand				(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void ServiceDiscovery_Res_Hand			(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void PaymentServiceSelection_Res_Hand	(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void PaymentDetails_Res_Hand			(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void Authorization_Res_Hand				(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void ChargingParameterDiscovery_Res_Hand(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void CableCheck_Res_Hand				(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void PreCharge_Res_Hand					(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void PowerDeliveryInitial_Res_Hand		(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void PowerDeliveryTermination_Res_Hand	(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void CurrentDemand_Res_Hand				(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void SessionStop_Res_Hand				(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void IDLE_Hand							(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
void UNMATED_Hand						(V2gFac_Message * ReqMsg 	,		V2gFac_Message * ResMsg );
extern V2g_stateMachine SM;


#endif
