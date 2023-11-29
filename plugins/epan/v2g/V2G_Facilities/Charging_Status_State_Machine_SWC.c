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


/*------------------------------------- File Includes ------------------------------------- */
#include "Charging_Status_State_Machine_SWC.h"
#include <stdint.h>
#include <stdio.h>



void CS_UNMATED_Hand(){
	printf("ChargingStatus_SWC : UNMATED STATE\n");
}
void Mated_Hand(){
	printf("ChargingStatus_SWC : MATED STATE\n");
}
void Initialize_Hand(){
	printf("ChargingStatus_SWC : Initialize STATE\n");
}
void CableCheck_Hand(){
	printf("ChargingStatus_SWC : CableCheck STATE\n");
}
void Precharge_Hand(){
	printf("ChargingStatus_SWC : Precharge STATE\n");
}
void Charging_Hand(){
	printf("ChargingStatus_SWC : Charging STATE\n");
}
void PowerDown_Hand(){
	printf("ChargingStatus_SWC : PowerDown STATE\n");
}

static V2g_ChargingStatus_stateFunctionRow stateFunction[] = {
	      /* NAME */         						/* FUNCTION */
	{ "CS_UNMATED"							,  			 &CS_UNMATED_Hand			},
    { "Mated_State"						,  		 	 &Mated_Hand 			},      
    { "Initialize"						,   		 &Initialize_Hand	    },       
    { "CableCheck"						,   		 &CableCheck_Hand	    },       
	{ "Precharge"						,  		     &Precharge_Hand 		},      
    { "Charging"						,   		 &Charging_Hand 		},       
    { "PowerDown"						,  		     &PowerDown_Hand 		}

};


static V2g_ChargingStatus_stateTransMatrixRow stateTransMatrix[] = {
    /* CURRENT STATE */ 								/* EVENT */              		   /* NEXT STATE*/
	
    { CS_UNMATED						,  Mated_Event				,	  Mated_State     },
	{ Mated_State						,  started 					,    Initialize  	  },
	{ Initialize						,  Initialized 				,     CableCheck  	  },
    { CableCheck						,  CableChecked				,     Precharge 	  },
    { Precharge							,  Precharged				,     Charging   	  },
    { Charging							,  Charged					,     PowerDown  	  },
	{ PowerDown							,  PowerOFF					,     CS_UNMATED  	  	  }

};

void ChargingStatus_StateMachine_Init(V2g_ChargingStatus_stateMachine * stateMachine) {
    stateMachine->currState = CS_UNMATED;
}

void ChargingStatus_StateMachine_RunIteration(V2g_ChargingStatus_stateMachine *stateMachine,V2g_ChargingStatus_event event) {

    /* Iterate through the state transition matrix, checking if there is both a match with the current state and the event */
    for(int i = 0; i < sizeof(stateTransMatrix)/sizeof(stateTransMatrix[0]); i++) {
        if(stateTransMatrix[i].currState == stateMachine->currState) {
            if((stateTransMatrix[i].event == event)) {

                /* Transition to the next state */
                stateMachine->currState =  stateTransMatrix[i].nextState;

                /* Call the function associated with transition  */
                (stateFunction[stateMachine->currState].func)();
                break;
            }
        }
    }
}
V2g_ChargingStatus_stateMachine ChargingStatus_SM;
uint8_t Fac_StateMachine_State = 0 ;
void ChargingStatus_StateMachine_Runnable(){
	
	/* Fac_StateMachine_State = RTE_READ */
	V2g_ChargingStatus_event currEvent;

	if(Fac_StateMachine_State > 0 && Fac_StateMachine_State < 9){
		currEvent = started;
	}else if(Fac_StateMachine_State == 9){
		currEvent = Initialized;
	}else if(Fac_StateMachine_State == 10){
		currEvent = CableChecked;
	}else if(Fac_StateMachine_State == 11 || Fac_StateMachine_State == 12){
		currEvent = Precharged;
	}else if(Fac_StateMachine_State == 13){
		currEvent = Charged;
	}else if(Fac_StateMachine_State == 14 ){
		currEvent = PowerOFF;
	}else if(mated_init == 1){
		currEvent = Mated_Event;
	}

	
	ChargingStatus_StateMachine_RunIteration(&ChargingStatus_SM, currEvent);
	
}
