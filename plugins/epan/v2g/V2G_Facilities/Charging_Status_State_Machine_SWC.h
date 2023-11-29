/**********************************************************************************************
 *
 * Module: Charging Status State Machine SWC
 *
 * File Name: Charging_Status_State_Machine_SWC.h
 *
 * Description: SWC StateMachine
 *
 * Author: Youssef Hussien!!Totsino
 **********************************************************************************************/

#ifndef CHARGING_STATUS_SWC
#define CHARGING_STATUS_SWC



/*******************************************************************************
 *                               Files includes                                *
 *******************************************************************************/

#include <stdint.h>
#include "ErrorCodes.h"
#include "Fac.h"


extern uint8_t Fac_StateMachine_State;
typedef enum {
	CS_UNMATED,
	Mated_State,
	Initialize,
	CableCheck,
	Precharge,
	Charging,
	PowerDown
} V2g_ChargingStatus_state; /* V2g_state */
	
	
typedef enum {
	Mated_Event,
	started,
	Initialized,
	CableChecked,
	Precharged,
	Charged,
	PowerOFF
}V2g_ChargingStatus_event;

typedef struct {
    V2g_ChargingStatus_state currState;
} V2g_ChargingStatus_stateMachine;


typedef struct {
	/*a printable state name for debugging purposes*/
    const char * name;
	
	/*function pointer to the function which gets called for each state*/
    void (*func)(void);
} V2g_ChargingStatus_stateFunctionRow;


typedef struct {
    V2g_ChargingStatus_state currState;
   V2g_ChargingStatus_event event;
    V2g_ChargingStatus_state nextState;
} V2g_ChargingStatus_stateTransMatrixRow;

extern V2g_ChargingStatus_stateMachine ChargingStatus_SM;

void ChargingStatus_StateMachine_Init(V2g_ChargingStatus_stateMachine * stateMachine);
void ChargingStatus_StateMachine_RunIteration(V2g_ChargingStatus_stateMachine *stateMachine,V2g_ChargingStatus_event);
void ChargingStatus_StateMachine_Runnable();
void CS_UNMATED_Hand();
void Mated_Hand();
void Initialize_Hand();
void CableCheck_Hand();
void Precharge_Hand();
void Charging_Hand();
void PowerDown_Hand();

#endif
