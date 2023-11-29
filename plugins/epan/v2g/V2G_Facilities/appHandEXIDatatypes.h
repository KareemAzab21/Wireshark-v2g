/**********************************************************************************************
 *
 * Module: AppHandEXIDatatypes
 *
 * File Name: appHandEXIDatatypes.h
 *
 * Description: Source file of AppHand EXI Datatypes module
 *
 * Author: Omar Reda - Aly Maamoun
 **********************************************************************************************/

#ifndef EXI_APPHAND_DATATYPES_H
#define EXI_APPHAND_DATATYPES_H



/*******************************************************************************
 *                               Files includes                                *
 *******************************************************************************/

#include <stdint.h>
#include "EXITypes.h"

/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/

#define UNION_YES 1
#define UNION_NO 2
#define SAVE_MEMORY_WITH_UNNAMED_UNION UNION_YES
#define appHandAppProtocolType_ProtocolNamespace_CHARACTERS_SIZE 100
#define appHandAnonType_supportedAppProtocolReq_AppProtocol_ARRAY_SIZE 20

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/


/* Description: Structure to configure each EVCC supported protocol type:
 *	    1. The ProtocolNamespace (Max 100 Characters)
 *	    2. The Protocol VersionNumberMajor (Major Version)
 *      3. The Protocol VersionNumberMinor (Minor Version)
 *      4. The SchemaID (ID)
 *      5. The Priority (1 "Highest" --> 20 "Lowest")
 */
typedef struct  {
	struct {
		exi_string_character_t characters[appHandAppProtocolType_ProtocolNamespace_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  ProtocolNamespace ;
	uint32_t VersionNumberMajor ;
	uint32_t VersionNumberMinor ;
	uint8_t SchemaID ;
	uint8_t Priority ;
}appHandAppProtocolType;

/*
 * Description: Enumeration for Application Handshake Response Codes
 */
typedef enum {
	appHandresponseCodeType_OK_SuccessfulNegotiation = 0,
	appHandresponseCodeType_OK_SuccessfulNegotiationWithMinorDeviation = 1,
	appHandresponseCodeType_Failed_NoNegotiation = 2
} appHandresponseCodeType;

/* Description: Structure to configure supported application protocol response message:
 *	    1. The ResponseCode
 *	    2. The SchemaID (Optional)
 */
typedef struct appHandAnonType_supportedAppProtocolRes {
	appHandresponseCodeType ResponseCode ;
	uint8_t SchemaID ;
	unsigned int SchemaID_isUsed:1;
}appHandAnonType_supportedAppProtocolRes;

/* Description: Array to configure supported application protocol request message:
 *	    1. The appHandAppProtocolType array (Max 20 Elements)
 */
typedef struct  {
	struct {
		appHandAppProtocolType array[appHandAnonType_supportedAppProtocolReq_AppProtocol_ARRAY_SIZE];
		uint16_t arrayLen;
	} AppProtocol;
}appHandAnonType_supportedAppProtocolReq;

/*
 * Description: Structure to configure appHandEXIDocument (Request OR Response Messages)
 */
typedef struct  {
#if SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES
	union {
#endif
	appHandAnonType_supportedAppProtocolReq supportedAppProtocolReq ;
	appHandAnonType_supportedAppProtocolRes supportedAppProtocolRes ;
#if SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES
	};
#endif
	unsigned int supportedAppProtocolReq_isUsed:1;
	unsigned int supportedAppProtocolRes_isUsed:1;
	int _warning_;
}appHandEXIDocument;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function that initializes the appHandEXIDocument Structure */
void V2gFac_init_appHandEXIDocument( appHandEXIDocument* exiDoc);
/* Function that initializes the appHandAppProtocolType Structure */
void V2gFac_init_appHandAppProtocolType( appHandAppProtocolType* appHandAppProtocolType);
/* Function that initializes the supportedAppProtocolReq Structure */
void V2gFac_init_appHandAnonType_supportedAppProtocolReq(appHandAnonType_supportedAppProtocolReq* appHandAnonType_supportedAppProtocolReq);
/* Function that initializes the supportedAppProtocolRes Structure */
void V2gFac_init_appHandAnonType_supportedAppProtocolRes( appHandAnonType_supportedAppProtocolRes* appHandAnonType_supportedAppProtocolRes);


#endif
