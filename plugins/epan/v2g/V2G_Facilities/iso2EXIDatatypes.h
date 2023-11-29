/**********************************************************************************************
 *
 * Module: iso2EXIDatatypes
 *
 * File Name: iso2EXIDatatypes.h
 *
 * Description: Source file of iso2 EXI Datatypes module
 *
 * Author: Omar Reda - Aly Maamoun
 **********************************************************************************************/



#ifndef EXI_iso2_DATATYPES_H
#define EXI_iso2_DATATYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#define SUPPORT_YES 1
#define SUPPORT_NO 2
#define DEPLOY_ISO2_CODEC SUPPORT_YES
#define DEPLOY_ISO2_CODEC_FRAGMENT SUPPORT_NO

#if DEPLOY_ISO2_CODEC == SUPPORT_YES

/*******************************************************************************
 *                               Files includes                                *
 *******************************************************************************/
#include <stdint.h>

#include "EXITypes.h"

/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/
#define EXTRA_CHAR 0 /* Dummy */

#define UNION_YES 1
#define UNION_NO 2
#define SAVE_MEMORY_WITH_UNNAMED_UNION UNION_YES
#define SUPPORT_YES 1
#define SUPPORT_NO 2
#define DEPLOY_ISO2_CODEC SUPPORT_YES
#define DEPLOY_ISO2_CODEC_FRAGMENT SUPPORT_NO
/* Merge */
#define iso2AuthorizationReqType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2AuthorizationReqType_GenChallenge_BYTES_SIZE 16
#define iso2MeterInfoType_MeterID_CHARACTERS_SIZE 32 + EXTRA_CHAR
#define iso2MeterInfoType_SigMeterReading_BYTES_SIZE 64
#define iso2ServiceListType_Service_ARRAY_SIZE 8
#define iso2ParameterType_Name_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2ParameterType_stringValue_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2PaymentOptionListType_PaymentOption_ARRAY_SIZE 2
#define iso2ConsumptionCostType_Cost_ARRAY_SIZE 3
#define iso2PMaxScheduleEntryType_PMax_ARRAY_SIZE 3
#define iso2ChargingStatusResType_EVSEID_CHARACTERS_SIZE 37 + EXTRA_CHAR
#define iso2SubCertificatesType_Certificate_BYTES_SIZE 800
#define iso2SubCertificatesType_Certificate_ARRAY_SIZE 4
#define iso2CanonicalizationMethodType_Algorithm_CHARACTERS_SIZE 65 + EXTRA_CHAR
#define iso2CanonicalizationMethodType_ANY_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SignatureMethodType_Algorithm_CHARACTERS_SIZE 65 + EXTRA_CHAR
#define iso2SignatureMethodType_ANY_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SPKIDataType_SPKISexp_BYTES_SIZE 350
#define iso2SPKIDataType_SPKISexp_ARRAY_SIZE 1
#define iso2SPKIDataType_ANY_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2KeyValueType_ANY_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2MeteringReceiptReqType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2MeteringReceiptReqType_SessionID_BYTES_SIZE 8
#define iso2DSAKeyValueType_P_BYTES_SIZE 350
#define iso2DSAKeyValueType_Q_BYTES_SIZE 350
#define iso2DSAKeyValueType_G_BYTES_SIZE 350
#define iso2DSAKeyValueType_Y_BYTES_SIZE 350
#define iso2DSAKeyValueType_J_BYTES_SIZE 350
#define iso2DSAKeyValueType_Seed_BYTES_SIZE 350
#define iso2DSAKeyValueType_PgenCounter_BYTES_SIZE 350
#define iso2EMAIDType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2EMAIDType_CONTENT_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SignaturePropertyType_Target_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SignaturePropertyType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SignaturePropertyType_ANY_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2TransformType_Algorithm_CHARACTERS_SIZE 65 + EXTRA_CHAR
#define iso2TransformType_ANY_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2TransformType_XPath_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2TransformType_XPath_ARRAY_SIZE 1
#define iso2X509DataType_X509IssuerSerial_ARRAY_SIZE 1
#define iso2X509DataType_X509SKI_BYTES_SIZE 350
#define iso2X509DataType_X509SKI_ARRAY_SIZE 1
#define iso2X509DataType_X509SubjectName_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2X509DataType_X509SubjectName_ARRAY_SIZE 1
#define iso2X509DataType_X509Certificate_BYTES_SIZE 350
#define iso2X509DataType_X509Certificate_ARRAY_SIZE 1
#define iso2X509DataType_X509CRL_BYTES_SIZE 350
#define iso2X509DataType_X509CRL_ARRAY_SIZE 1
#define iso2X509DataType_ANY_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2X509IssuerSerialType_X509IssuerName_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2ContractSignatureEncryptedPrivateKeyType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2ContractSignatureEncryptedPrivateKeyType_CONTENT_BYTES_SIZE 350
#define iso2DigestMethodType_Algorithm_CHARACTERS_SIZE 65 + EXTRA_CHAR
#define iso2DigestMethodType_ANY_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2MagneticVectorSetupListType_MagneticVectorSetup_ARRAY_SIZE 5
#define iso2PGPDataType_PGPKeyID_BYTES_SIZE 350
#define iso2PGPDataType_PGPKeyPacket_BYTES_SIZE 350
#define iso2PGPDataType_ANY_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SignatureValueType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SignatureValueType_CONTENT_BYTES_SIZE 350
#define iso2DiffieHellmanPublickeyType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2DiffieHellmanPublickeyType_CONTENT_BYTES_SIZE 350
#define iso2SignaturePropertiesType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SignaturePropertiesType_SignatureProperty_ARRAY_SIZE 1
#define iso2RSAKeyValueType_Modulus_BYTES_SIZE 350
#define iso2RSAKeyValueType_Exponent_BYTES_SIZE 350
#define iso2MagneticVectorSetupType_GAID_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2ObjectType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2ObjectType_MimeType_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2ObjectType_Encoding_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2ObjectType_ANY_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SensorOrderListType_SensorPosition_ARRAY_SIZE 5
#define iso2MeasurementDataListType_MeasurementData_ARRAY_SIZE 5
#define iso2CertificateChainType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2CertificateChainType_Certificate_BYTES_SIZE 800
#define iso2TransformsType_Transform_ARRAY_SIZE 1
#define iso2DC_BidirectionalControlResType_EVSEID_CHARACTERS_SIZE 37 + EXTRA_CHAR
#define iso2SessionSetupReqType_EVCCID_BYTES_SIZE 6
#define iso2SessionSetupResType_EVSEID_CHARACTERS_SIZE 37 + EXTRA_CHAR
#define iso2SessionSetupResType_EVSEID_CHARACTERS_SIZE 37 + EXTRA_CHAR
#define iso2ReferenceType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2ReferenceType_URI_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2ReferenceType_Type_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2ReferenceType_DigestValue_BYTES_SIZE 350
#define iso2SensorListType_Sensor_ARRAY_SIZE 5
#define iso2ParameterSetType_Parameter_ARRAY_SIZE 16
#define iso2PaymentDetailsReqType_eMAID_CHARACTERS_SIZE 15 + EXTRA_CHAR
#define iso2SalesTariffEntryType_ConsumptionCost_ARRAY_SIZE 3
#define iso2ManifestType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2ManifestType_Reference_ARRAY_SIZE 1    //UNBOUNDED IN ISO
#define iso2SelectedServiceListType_SelectedService_ARRAY_SIZE 16
#define iso2ListOfRootCertificateIDsType_RootCertificateID_ARRAY_SIZE 20
#define iso2CurrentDemandResType_EVSEID_CHARACTERS_SIZE 37 + EXTRA_CHAR
#define iso2PowerDemandResType_EVSEID_CHARACTERS_SIZE 37 + EXTRA_CHAR
#define iso2ChargingProfileType_ProfileEntry_ARRAY_SIZE 24
#define iso2SalesTariffType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SalesTariffType_SalesTariffDescription_CHARACTERS_SIZE 32 + EXTRA_CHAR
#define iso2SalesTariffType_SalesTariffEntry_ARRAY_SIZE 5
#define iso2SignedInfoType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SignedInfoType_Reference_ARRAY_SIZE 1                           //UNBOUNDED IN ISO
#define iso2RetrievalMethodType_URI_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2RetrievalMethodType_Type_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2ServiceParameterListType_ParameterSet_ARRAY_SIZE 5
#define iso2PMaxScheduleType_PMaxScheduleEntry_ARRAY_SIZE 5
#define iso2CertificateUpdateReqType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2CertificateUpdateReqType_eMAID_CHARACTERS_SIZE 15 + EXTRA_CHAR
#define iso2CertificateInstallationReqType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2CertificateInstallationReqType_OEMProvisioningCert_BYTES_SIZE 800
#define iso2KeyInfoType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2KeyInfoType_KeyName_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2KeyInfoType_KeyName_ARRAY_SIZE 1
#define iso2KeyInfoType_KeyValue_ARRAY_SIZE 1
#define iso2KeyInfoType_RetrievalMethod_ARRAY_SIZE 1
#define iso2KeyInfoType_X509Data_ARRAY_SIZE 1
#define iso2KeyInfoType_PGPData_ARRAY_SIZE 1
#define iso2KeyInfoType_SPKIData_ARRAY_SIZE 1
#define iso2KeyInfoType_MgmtData_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2KeyInfoType_MgmtData_ARRAY_SIZE 1
#define iso2KeyInfoType_ANY_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SignatureType_Id_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2SignatureType_Object_ARRAY_SIZE 1
#define iso2SAScheduleListType_SAScheduleTuple_ARRAY_SIZE 3
#define iso2MessageHeaderType_SessionID_BYTES_SIZE 8
#define iso2EXIDocument_MgmtData_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2EXIDocument_KeyName_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2EXIDocument_DigestValue_BYTES_SIZE 350
#define iso2EXIFragment_stringValue_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2EXIFragment_PgenCounter_BYTES_SIZE 350
#define iso2EXIFragment_SalesTariffDescription_CHARACTERS_SIZE 32 + EXTRA_CHAR
#define iso2EXIFragment_SessionID_BYTES_SIZE 8
#define iso2EXIFragment_XPath_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2EXIFragment_MgmtData_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2EXIFragment_OEMProvisioningCert_BYTES_SIZE 800
#define iso2EXIFragment_P_BYTES_SIZE 350
#define iso2EXIFragment_Q_BYTES_SIZE 350
#define iso2EXIFragment_X509SubjectName_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2EXIFragment_G_BYTES_SIZE 350
#define iso2EXIFragment_J_BYTES_SIZE 350
#define iso2EXIFragment_Y_BYTES_SIZE 350
#define iso2EXIFragment_DigestValue_BYTES_SIZE 350
#define iso2EXIFragment_EVCCID_BYTES_SIZE 6
#define iso2EXIFragment_PGPKeyID_BYTES_SIZE 350
#define iso2EXIFragment_KeyName_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2EXIFragment_X509SKI_BYTES_SIZE 350
#define iso2EXIFragment_Certificate_BYTES_SIZE 800
#define iso2EXIFragment_Modulus_BYTES_SIZE 350
#define iso2EXIFragment_SigMeterReading_BYTES_SIZE 64
#define iso2EXIFragment_Exponent_BYTES_SIZE 350
#define iso2EXIFragment_PGPKeyPacket_BYTES_SIZE 350
#define iso2EXIFragment_Seed_BYTES_SIZE 350
#define iso2EXIFragment_MeterID_CHARACTERS_SIZE 32 + EXTRA_CHAR
#define iso2EXIFragment_X509CRL_BYTES_SIZE 350
#define iso2EXIFragment_SPKISexp_BYTES_SIZE 350
#define iso2EXIFragment_X509Certificate_BYTES_SIZE 350
#define iso2EXIFragment_EVSEID_CHARACTERS_SIZE 37 + EXTRA_CHAR /
#define iso2EXIFragment_GenChallenge_BYTES_SIZE 16
#define iso2EXIFragment_GAID_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2EXIFragment_X509IssuerName_CHARACTERS_SIZE 50 + EXTRA_CHAR
#define iso2PaymentDetailsResType_GenChallenge_BYTES_SIZE 16
#define iso2ServiceIDListType_ServiceID_ARRAY_SIZE 10


/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

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

typedef enum {
	iso2EVSENotificationType_StopCharging = 0,
	iso2EVSENotificationType_ReNegotiation = 1
} iso2EVSENotificationType;

typedef enum {
	iso2EVErrorCodeType_RESSTemperatureInhibit = 0,
	iso2EVErrorCodeType_EVShiftPosition = 1,
	iso2EVErrorCodeType_ChargerConnectorLockFault = 2,
	iso2EVErrorCodeType_EVRESSMalfunction = 3,
	iso2EVErrorCodeType_ChargingCurrentdifferential = 4,
	iso2EVErrorCodeType_ChargingVoltageOutOfRange = 5,
	iso2EVErrorCodeType_ChargingSystemIncompatibility = 6,
	iso2EVErrorCodeType_Reserved_A = 7,
	iso2EVErrorCodeType_Reserved_B = 8,
	iso2EVErrorCodeType_Reserved_C = 9
} iso2EVErrorCodeType;

typedef enum {
	iso2EVSEErrorCodeType_RESSTemperatureInhibit = 0,
	iso2EVSEErrorCodeType_ChargerConnectorLockFault = 1,
	iso2EVSEErrorCodeType_ChargingCurrentdifferential = 2,
	iso2EVSEErrorCodeType_ChargingVoltageOutOfRange = 3,
	iso2EVSEErrorCodeType_ChargingSystemIncompatibility = 4,
	iso2EVSEErrorCodeType_Reserved_A = 5,
	iso2EVSEErrorCodeType_Reserved_B = 6,
	iso2EVSEErrorCodeType_Reserved_C = 7
} iso2EVSEErrorCodeType;


typedef enum {
	iso2paymentOptionType_Contract = 0,
	iso2paymentOptionType_ExternalPayment = 1
} iso2paymentOptionType;

typedef enum {
	iso2chargingSessionType_Terminate = 0,
	iso2chargingSessionType_Pause = 1
} iso2chargingSessionType;
typedef enum {
	iso2EVSEProcessingType_Finished = 0,
	iso2EVSEProcessingType_Ongoing = 1,
	iso2EVSEProcessingType_Ongoing_WaitingForCustomerInteraction = 2
} iso2EVSEProcessingType;

typedef enum {
	iso2costKindType_relativePricePercentage = 0,
	iso2costKindType_RenewableGenerationPercentage = 1,
	iso2costKindType_CarbonDioxideEmission = 2
} iso2costKindType;

typedef enum {
	iso2chargeProgressType_Start = 0,
	iso2chargeProgressType_Stop = 1,
	iso2chargeProgressType_Renegotiate = 2
} iso2chargeProgressType;

typedef enum {
	iso2serviceCategoryType_EVCharging = 0,
	iso2serviceCategoryType_Internet = 1,
	iso2serviceCategoryType_ContractCertificate = 2,
	iso2serviceCategoryType_OtherCustom = 3
} iso2serviceCategoryType;

typedef enum {
	iso2valueType_bool = 0,
	iso2valueType_byte = 1,
	iso2valueType_short = 2,
	iso2valueType_int = 3,
	iso2valueType_physicalValue = 4,
	iso2valueType_string = 5
} iso2valueType;

typedef enum {
	iso2vehicleSpaceType_AutoParking = 0,
	iso2vehicleSpaceType_MVGuideManual = 1,
	iso2vehicleSpaceType_Manual = 2
} iso2vehicleSpaceType;


typedef enum {
	iso2operationModeType_Ready = 0,
	iso2operationModeType_NotReady = 1
} iso2operationModeType;

typedef struct  {
	int8_t Exponent ;
	int16_t Value ;
}iso2PhysicalValueType ;

typedef struct  {
	uint16_t NotificationMaxDelay ;
	iso2EVSENotificationType EVSENotification ;
}iso2EVSEStatusType;


/* Merge */
typedef struct  {
	 struct {
		uint8_t bytes[iso2SessionSetupReqType_EVCCID_BYTES_SIZE];
		uint16_t bytesLen;
	}  EVCCID ;
}iso2SessionSetupReqType;

typedef struct {
	struct {
		uint16_t array[iso2ServiceIDListType_ServiceID_ARRAY_SIZE];
		uint16_t arrayLen;
	} ServiceID;
}iso2ServiceIDListType;

typedef struct  {
	iso2ServiceIDListType SupportedServiceIDs ;
	unsigned int SupportedServiceIDs_isUsed:1;
}iso2ServiceDiscoveryReqType;

typedef struct  {
	 struct {
		exi_string_character_t characters[iso2AuthorizationReqType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	unsigned int Id_isUsed:1;
	 struct {
		uint8_t bytes[iso2AuthorizationReqType_GenChallenge_BYTES_SIZE];
		uint16_t bytesLen;
	}  GenChallenge ;
	unsigned int GenChallenge_isUsed:1;
}iso2AuthorizationReqType;

typedef struct{
	iso2responseCodeType ResponseCode ;
    iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	iso2EVSEProcessingType EVSEProcessing ;
}iso2AuthorizationResType;

typedef struct  {
	iso2chargingSessionType ChargingSession ;
}iso2SessionStopReqType;
typedef struct  {
	iso2responseCodeType ResponseCode ;
	iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
}iso2SessionStopResType;

typedef struct  {
	int noContent;
}iso2CableCheckReqType;



typedef struct  {
	iso2responseCodeType ResponseCode ;
	iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	iso2EVSEProcessingType EVSEProcessing ;
}iso2CableCheckResType;


typedef struct  {
	iso2PhysicalValueType EVTargetVoltage ;
	iso2PhysicalValueType EVTargetCurrent ;
}iso2PreChargeReqType;


typedef struct  {
	int noContent;
}iso2WeldingDetectionReqType;



typedef struct  {
	iso2responseCodeType ResponseCode ;
	iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	iso2PhysicalValueType EVSEPresentVoltage ;
}iso2WeldingDetectionResType;




typedef struct  {
	 struct { //
		exi_string_character_t characters[iso2MeterInfoType_MeterID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  MeterID ;
	uint64_t MeterReadingCharged ;  //
	unsigned int MeterReadingCharged_isUsed:1; //
	uint64_t MeterReadingDischarged ;   //
	unsigned int MeterReadingDischarged_isUsed:1;  //
	 struct {
		uint8_t bytes[iso2MeterInfoType_SigMeterReading_BYTES_SIZE];
		uint16_t bytesLen;
	}  SigMeterReading ;
	unsigned int SigMeterReading_isUsed:1;
	int16_t MeterStatus ;
	unsigned int MeterStatus_isUsed:1;
	int64_t TMeter ;
	unsigned int TMeter_isUsed:1;
}iso2MeterInfoType;

typedef struct  {
	uint16_t ServiceID ;
	int FreeService ;
}iso2ServiceType;

typedef struct  {
	 struct {
		iso2ServiceType array[iso2ServiceListType_Service_ARRAY_SIZE];
		uint16_t arrayLen;
	} Service;
}iso2ServiceListType;


typedef struct  {
	uint32_t start ;
	uint32_t duration ;
	unsigned int duration_isUsed:1;
}iso2RelativeTimeIntervalType;

typedef struct  {
	iso2responseCodeType ResponseCode ;
	iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
}iso2MeteringReceiptResType;


typedef struct  {
	 iso2PhysicalValueType EVSEMaximumChargePower ;
	 iso2PhysicalValueType EVSEMaximumChargeCurrent ;
	 iso2PhysicalValueType EVSEMinimumChargeCurrent ;
	 iso2PhysicalValueType EVSEMaximumVoltage ;
	 iso2PhysicalValueType EVSEMinimumVoltage ;
	 iso2PhysicalValueType EVSECurrentRegulationTolerance ;
	unsigned int EVSECurrentRegulationTolerance_isUsed:1;
	 iso2PhysicalValueType EVSEPeakCurrentRipple ;
	 iso2PhysicalValueType EVSEEnergyToBeDelivered ;
	unsigned int EVSEEnergyToBeDelivered_isUsed:1;
}iso2DC_EVSEChargeParameterType;




typedef struct  {
	 struct {
		exi_string_character_t characters[iso2ParameterType_Name_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Name ;
	int boolValue ;
	unsigned int boolValue_isUsed:1;
	int8_t byteValue ;
	unsigned int byteValue_isUsed:1;
	int16_t shortValue ;
	unsigned int shortValue_isUsed:1;
	int32_t intValue ;
	unsigned int intValue_isUsed:1;
	iso2PhysicalValueType physicalValue ;
	unsigned int physicalValue_isUsed:1;
	 struct {
		exi_string_character_t characters[iso2ParameterType_stringValue_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  stringValue ;
	unsigned int stringValue_isUsed:1;
}iso2ParameterType;


typedef struct  {
	 struct {
		iso2paymentOptionType array[iso2PaymentOptionListType_PaymentOption_ARRAY_SIZE];
		uint16_t arrayLen;
	} PaymentOption;
}iso2PaymentOptionListType;

typedef struct  {
	iso2costKindType costKind ;
	 iso2PhysicalValueType amount ;
}iso2CostType;

typedef struct  {
	 iso2PhysicalValueType startValue ;
	 struct {
		 iso2CostType array[iso2ConsumptionCostType_Cost_ARRAY_SIZE];
		uint16_t arrayLen;
	} Cost;
}iso2ConsumptionCostType;


typedef struct  {
	uint32_t DepartureTime ;
	 iso2PhysicalValueType EVMaximumChargePower ;
	 iso2PhysicalValueType EVMaximumChargeCurrent ;
	 iso2PhysicalValueType EVMinimumChargeCurrent ;
	 iso2PhysicalValueType EVTargetEnergyRequest ;
	unsigned int EVTargetEnergyRequest_isUsed:1;
	 iso2PhysicalValueType EVMaximumEnergyRequest ;
	unsigned int EVMaximumEnergyRequest_isUsed:1;
	 iso2PhysicalValueType EVMinimumEnergyRequest ;
	unsigned int EVMinimumEnergyRequest_isUsed:1;
	 iso2PhysicalValueType EVMaximumVoltage ;
	 iso2PhysicalValueType EVMaximumDischargePower ;
	 iso2PhysicalValueType EVMaximumDischargeCurrent ;
	 iso2PhysicalValueType EVMinimumDischargeCurrent ;
}iso2AC_EVBidirectionalParameterType;


typedef struct  {
	 iso2RelativeTimeIntervalType RelativeTimeInterval ;
	 struct {
		iso2PhysicalValueType array[iso2PMaxScheduleEntryType_PMax_ARRAY_SIZE];
		uint16_t arrayLen;
	} PMax;
}iso2PMaxScheduleEntryType;



typedef struct  {
	iso2responseCodeType ResponseCode ;
	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	 struct {
		exi_string_character_t characters[iso2ChargingStatusResType_EVSEID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  EVSEID ;
	uint8_t SAScheduleTupleID ;
	unsigned int SAScheduleTupleID_isUsed:1;
	 iso2MeterInfoType MeterInfo ;
	unsigned int MeterInfo_isUsed:1;
	int ReceiptRequired ;
	unsigned int ReceiptRequired_isUsed:1;
	 iso2PhysicalValueType EVSETargetPower ;
	unsigned int EVSETargetPower_isUsed:1;
}iso2ChargingStatusResType;


typedef struct  {
	uint32_t DepartureTime ;
	 iso2PhysicalValueType EVMaximumChargePower ;
	 iso2PhysicalValueType EVMaximumChargeCurrent ;
	 iso2PhysicalValueType EVMinimumChargeCurrent ;
	 iso2PhysicalValueType EVTargetEnergyRequest ;
	unsigned int EVTargetEnergyRequest_isUsed:1;
	 iso2PhysicalValueType EVMaximumEnergyRequest ;
	unsigned int EVMaximumEnergyRequest_isUsed:1;
	 iso2PhysicalValueType EVMinimumEnergyRequest ;
	unsigned int EVMinimumEnergyRequest_isUsed:1;
	 iso2PhysicalValueType EVMaximumVoltage ;
}iso2AC_EVChargeParameterType;

typedef struct  {
	uint16_t ServiceID ;
	uint16_t ParameterSetID ;
}iso2SelectedServiceType;


typedef struct  {
	 struct {
		struct {
		uint8_t bytes[iso2SubCertificatesType_Certificate_BYTES_SIZE];
		uint16_t bytesLen;
	}  array[iso2SubCertificatesType_Certificate_ARRAY_SIZE];
		uint16_t arrayLen;
	} Certificate;
}iso2SubCertificatesType;


typedef struct  {
	uint16_t ServiceID ;
}iso2ServiceDetailReqType;


typedef struct  {
	uint32_t DepartureTime ;
	 iso2PhysicalValueType EVMaximumChargePower ;
	unsigned int EVMaximumChargePower_isUsed:1;
	 iso2PhysicalValueType EVMinimumChargePower ;
	unsigned int EVMinimumChargePower_isUsed:1;
	 iso2PhysicalValueType EVMaximumChargeCurrent ;
	 iso2PhysicalValueType EVMinimumChargeCurrent ;
	 iso2PhysicalValueType EVMaximumVoltage ;
	 iso2PhysicalValueType EVTargetEnergyRequest ;
	unsigned int EVTargetEnergyRequest_isUsed:1;
	 iso2PhysicalValueType EVMaximumEnergyRequest ;
	unsigned int EVMaximumEnergyRequest_isUsed:1;
	 iso2PhysicalValueType EVMinimumEnergyRequest ;
	unsigned int EVMinimumEnergyRequest_isUsed:1;
	int8_t CurrentSOC ;
	unsigned int CurrentSOC_isUsed:1;
	int8_t TargetSOC ;
	unsigned int TargetSOC_isUsed:1;
	int8_t BulkSOC ;
	unsigned int BulkSOC_isUsed:1;
}iso2DC_EVChargeParameterType;

typedef struct {

	 struct {
		exi_string_character_t characters[iso2CanonicalizationMethodType_Algorithm_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Algorithm ;

	 struct {
		exi_string_character_t characters[iso2CanonicalizationMethodType_ANY_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  ANY ;
	unsigned int ANY_isUsed:1;
}iso2CanonicalizationMethodType;


typedef struct  {
	 struct {
		exi_string_character_t characters[iso2SignatureMethodType_Algorithm_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Algorithm ;
	int64_t HMACOutputLength ;
	unsigned int HMACOutputLength_isUsed:1;

	 struct {
		exi_string_character_t characters[iso2SignatureMethodType_ANY_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  ANY ;
	unsigned int ANY_isUsed:1;
}iso2SignatureMethodType;


typedef struct  {
	 struct {
		 struct {
			uint8_t bytes[iso2SPKIDataType_SPKISexp_BYTES_SIZE];
			uint16_t bytesLen;
		}  array[iso2SPKIDataType_SPKISexp_ARRAY_SIZE];
		uint16_t arrayLen;
	} SPKISexp;
	 struct {
		exi_string_character_t characters[iso2SPKIDataType_ANY_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  ANY ;
	unsigned int ANY_isUsed:1;
}iso2SPKIDataType;

typedef struct  {
	int noContent;
}iso2BodyBaseType;
typedef struct  {
	 struct {
		uint8_t bytes[iso2DSAKeyValueType_P_BYTES_SIZE];
		uint16_t bytesLen;
	}  P ;
	unsigned int P_isUsed:1;
	 struct {
		uint8_t bytes[iso2DSAKeyValueType_Q_BYTES_SIZE];
		uint16_t bytesLen;
	}  Q ;
	unsigned int Q_isUsed:1;
	 struct {
		uint8_t bytes[iso2DSAKeyValueType_G_BYTES_SIZE];
		uint16_t bytesLen;
	}  G ;
	unsigned int G_isUsed:1;
	 struct {
		uint8_t bytes[iso2DSAKeyValueType_Y_BYTES_SIZE];
		uint16_t bytesLen;
	}  Y ;
	 struct {
		uint8_t bytes[iso2DSAKeyValueType_J_BYTES_SIZE];
		uint16_t bytesLen;
	}  J ;
	unsigned int J_isUsed:1;
	 struct {
		uint8_t bytes[iso2DSAKeyValueType_Seed_BYTES_SIZE];
		uint16_t bytesLen;
	}  Seed ;
	unsigned int Seed_isUsed:1;
	 struct {
		uint8_t bytes[iso2DSAKeyValueType_PgenCounter_BYTES_SIZE];
		uint16_t bytesLen;
	}  PgenCounter ;
	unsigned int PgenCounter_isUsed:1;
}iso2DSAKeyValueType;

typedef struct  {
	 struct {
		uint8_t bytes[iso2RSAKeyValueType_Modulus_BYTES_SIZE];
		uint16_t bytesLen;
	}  Modulus ;
	 struct {
		uint8_t bytes[iso2RSAKeyValueType_Exponent_BYTES_SIZE];
		uint16_t bytesLen;
	}  Exponent ;
}iso2RSAKeyValueType;

typedef struct  {
	 iso2DSAKeyValueType DSAKeyValue ;
	unsigned int DSAKeyValue_isUsed:1;
	 iso2RSAKeyValueType RSAKeyValue ;
	unsigned int RSAKeyValue_isUsed:1;
	 struct {
		exi_string_character_t characters[iso2KeyValueType_ANY_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  ANY ;
	unsigned int ANY_isUsed:1;
}iso2KeyValueType;



typedef struct  {
	 struct {
		exi_string_character_t characters[iso2MeteringReceiptReqType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	 struct {
		uint8_t bytes[iso2MeteringReceiptReqType_SessionID_BYTES_SIZE];
		uint16_t bytesLen;
	}  SessionID ;
	uint8_t SAScheduleTupleID ;
	unsigned int SAScheduleTupleID_isUsed:1;
	iso2MeterInfoType MeterInfo ;
}iso2MeteringReceiptReqType;

typedef struct  {
	 iso2RelativeTimeIntervalType RelativeTimeInterval ;
}iso2EntryType;

typedef struct  {
	 struct {
		exi_string_character_t characters[iso2EMAIDType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	 struct {
		exi_string_character_t characters[iso2EMAIDType_CONTENT_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  CONTENT ;
}iso2EMAIDType;


typedef struct  {
	 struct {
		exi_string_character_t characters[iso2SignaturePropertyType_Target_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Target ;
	 struct {
		exi_string_character_t characters[iso2SignaturePropertyType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	unsigned int Id_isUsed:1;
	 struct {
		exi_string_character_t characters[iso2SignaturePropertyType_ANY_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  ANY ;
	unsigned int ANY_isUsed:1;
}iso2SignaturePropertyType;


typedef struct  {
	 struct {
		exi_string_character_t characters[iso2TransformType_Algorithm_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Algorithm ;
	 struct {
		exi_string_character_t characters[iso2TransformType_ANY_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  ANY ;
	unsigned int ANY_isUsed:1;
	 struct {
		 struct {
			exi_string_character_t characters[iso2TransformType_XPath_CHARACTERS_SIZE];
			uint16_t charactersLen;
		}  array[iso2TransformType_XPath_ARRAY_SIZE];
		uint16_t arrayLen;
	} XPath;
}iso2TransformType;


typedef struct  {
	 struct {
		exi_string_character_t characters[iso2X509IssuerSerialType_X509IssuerName_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  X509IssuerName ;

	int64_t X509SerialNumber ;
}iso2X509IssuerSerialType;

typedef struct  {
	 struct {
		 iso2X509IssuerSerialType array[iso2X509DataType_X509IssuerSerial_ARRAY_SIZE];
		uint16_t arrayLen;
	} X509IssuerSerial;
	struct {
		struct {
			uint8_t bytes[iso2X509DataType_X509SKI_BYTES_SIZE];
			uint16_t bytesLen;
		}  array[iso2X509DataType_X509SKI_ARRAY_SIZE];
		uint16_t arrayLen;
	} X509SKI;
	 struct {
		 struct {
			exi_string_character_t characters[iso2X509DataType_X509SubjectName_CHARACTERS_SIZE];
			uint16_t charactersLen;
		}  array[iso2X509DataType_X509SubjectName_ARRAY_SIZE];
		uint16_t arrayLen;
	} X509SubjectName;
	 struct {
		 struct {
			uint8_t bytes[iso2X509DataType_X509Certificate_BYTES_SIZE];
			uint16_t bytesLen;
		}  array[iso2X509DataType_X509Certificate_ARRAY_SIZE];
		uint16_t arrayLen;
	} X509Certificate;
	 struct {
		 struct {
			uint8_t bytes[iso2X509DataType_X509CRL_BYTES_SIZE];
			uint16_t bytesLen;
		}  array[iso2X509DataType_X509CRL_ARRAY_SIZE];
		uint16_t arrayLen;
	} X509CRL;
	 struct {
		exi_string_character_t characters[iso2X509DataType_ANY_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  ANY ;
	unsigned int ANY_isUsed:1;
}iso2X509DataType;


typedef struct  {
	 struct {
		exi_string_character_t characters[iso2ContractSignatureEncryptedPrivateKeyType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	 struct {
		uint8_t bytes[iso2ContractSignatureEncryptedPrivateKeyType_CONTENT_BYTES_SIZE];
		uint16_t bytesLen;
	}  CONTENT ;
}iso2ContractSignatureEncryptedPrivateKeyType;

typedef struct  {
	 struct {
		exi_string_character_t characters[iso2DigestMethodType_Algorithm_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Algorithm ;
	 struct {
		exi_string_character_t characters[iso2DigestMethodType_ANY_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  ANY ;
	unsigned int ANY_isUsed:1;
}iso2DigestMethodType;


//NOT INSCOPE OR NOT ISO

typedef struct  {
	int noContent;
}iso2V2GRequestType;

typedef struct  {
	int noContent;
}iso2EVSEEnergyTransferParameterType;
typedef enum {
	iso2EVCheckInStatusType_CheckIn = 0,
	iso2EVCheckInStatusType_Processing = 1,
	iso2EVCheckInStatusType_Completed = 2
} iso2EVCheckInStatusType;

typedef enum {
	iso2mechanicalChargingDeviceStatusType_Home = 0,
	iso2mechanicalChargingDeviceStatusType_Moving = 1,
	iso2mechanicalChargingDeviceStatusType_EndPosition = 2
} iso2mechanicalChargingDeviceStatusType;

typedef struct  {
	iso2operationModeType OperationMode ;
	iso2mechanicalChargingDeviceStatusType EVMechanicalChargingDeviceStatus ;
}iso2SystemStatusReqType ;

typedef struct {
	int noContent;
}iso2EVSEFinePositioningSetupParametersType ;

typedef struct  {
	int noContent;
}iso2EVSEFinePositioningParametersType;

typedef enum {
	iso2FODStatusType_ObjectOnPad = 0,
	iso2FODStatusType_PadClear = 1,
	iso2FODStatusType_UnknownError = 2
} iso2FODStatusType;


typedef struct  {
	uint16_t TargetOffsetX ;
	uint16_t TargetOffsetY ;
}iso2TargetPositionType;

typedef enum {
	iso2EVOperationType_Charge = 0,
	iso2EVOperationType_BPT = 1
} iso2EVOperationType;



typedef struct  {
	int16_t XCoordinate ;
	int16_t YCoordinate ;
	int16_t ZCoordinate ;
}iso2CartesianCoordinatesType;

typedef enum {
	iso2parkingMethodType_AutoParking = 0,
	iso2parkingMethodType_MVGuideManual = 1,
	iso2parkingMethodType_Manual = 2
} iso2parkingMethodType;

typedef struct  {
	uint32_t DepartureTime ;
}iso2EVEnergyTransferParameterType;

typedef struct  {
	 struct {
		exi_string_character_t characters[iso2MagneticVectorSetupType_GAID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  GAID ;
	uint32_t FrequencyChannel ;
}iso2MagneticVectorSetupType;

typedef struct  {
	 struct {
		iso2MagneticVectorSetupType array[iso2MagneticVectorSetupListType_MagneticVectorSetup_ARRAY_SIZE];
		uint16_t arrayLen;
	} MagneticVectorSetup;
}iso2MagneticVectorSetupListType;


typedef enum {
	iso2EVSECheckOutStatusType_Scheduled = 0,
	iso2EVSECheckOutStatusType_Completed = 1
} iso2EVSECheckOutStatusType;


typedef struct  {
	 struct {
		uint8_t bytes[iso2PGPDataType_PGPKeyID_BYTES_SIZE];
		uint16_t bytesLen;
	}  PGPKeyID ;
	unsigned int PGPKeyID_isUsed:1;
	 struct {
		uint8_t bytes[iso2PGPDataType_PGPKeyPacket_BYTES_SIZE];
		uint16_t bytesLen;
	}  PGPKeyPacket ;
	unsigned int PGPKeyPacket_isUsed:1;

	 struct {
		exi_string_character_t characters[iso2PGPDataType_ANY_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  ANY ;
	unsigned int ANY_isUsed:1;
}iso2PGPDataType ;

typedef struct  {
	int noContent;
}iso2EVFinePositioningSetupParametersType;


typedef enum {
	iso2EVCheckOutStatusType_CheckOut = 0,
	iso2EVCheckOutStatusType_Processing = 1,
	iso2EVCheckOutStatusType_Completed = 2
} iso2EVCheckOutStatusType;


typedef struct  {
	uint8_t SensorID ;
	 iso2CartesianCoordinatesType SensorPosition ;
	 iso2CartesianCoordinatesType SensorOrientation ;
}iso2SensorType;


typedef struct  {

	 struct {
		exi_string_character_t characters[iso2SignatureValueType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	unsigned int Id_isUsed:1;

	 struct {
		uint8_t bytes[iso2SignatureValueType_CONTENT_BYTES_SIZE];
		uint16_t bytesLen;
	}  CONTENT ;
}iso2SignatureValueType;


typedef enum {
	iso2electricalChargingDeviceStatusType_Connected = 0,
	iso2electricalChargingDeviceStatusType_Disconnected = 1
} iso2electricalChargingDeviceStatusType;


typedef struct  {
	 struct {
		exi_string_character_t characters[iso2DiffieHellmanPublickeyType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	 struct {
		uint8_t bytes[iso2DiffieHellmanPublickeyType_CONTENT_BYTES_SIZE];
		uint16_t bytesLen;
	}  CONTENT ;
}iso2DiffieHellmanPublickeyType;

typedef struct  {
	uint32_t FrequencyChannel ;
	unsigned int FrequencyChannel_isUsed:1;
	 iso2MagneticVectorSetupListType MagneticVectorSetupList ;
	unsigned int MagneticVectorSetupList_isUsed:1;
}iso2MV_EVSEFinePositioningSetupParametersType;



typedef struct  {
	 iso2PhysicalValueType EVSEMaximumChargeCurrent ;
	 iso2PhysicalValueType EVSENominalVoltage ;
	 iso2PhysicalValueType EVSENominalFrequency ;
	 iso2PhysicalValueType EVSEMaximumDischargeCurrent ;
}iso2AC_EVSEBidirectionalParameterType;


typedef struct  {
	iso2responseCodeType ResponseCode ;
	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	iso2EVCheckOutStatusType EVSECheckOutStatus ;
}iso2VehicleCheckOutResType;


typedef struct  {
	 struct {
		exi_string_character_t characters[iso2SignaturePropertiesType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	unsigned int Id_isUsed:1;
	 struct {
		 iso2SignaturePropertyType array[iso2SignaturePropertiesType_SignatureProperty_ARRAY_SIZE];
		uint16_t arrayLen;
	} SignatureProperty;
}iso2SignaturePropertiesType;


typedef struct  {
	iso2responseCodeType ResponseCode ;
	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	iso2EVSEProcessingType EVSEProcessing ;
	iso2electricalChargingDeviceStatusType EVSEElectricalChargingDeviceStatus ;
	iso2mechanicalChargingDeviceStatusType EVSEMechanicalChargingDeviceStatus ;
}iso2ConnectChargingDeviceResType;

typedef struct  {
	iso2responseCodeType ResponseCode ;
	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	uint16_t VehicleSpace ;
	 iso2TargetPositionType TargetOffset ;
	unsigned int TargetOffset_isUsed:1;
}iso2VehicleCheckInResType;


typedef struct  {
	 struct {
		exi_string_character_t characters[iso2ObjectType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	unsigned int Id_isUsed:1;
	 struct {
		exi_string_character_t characters[iso2ObjectType_MimeType_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  MimeType ;
	unsigned int MimeType_isUsed:1;
	 struct {
		exi_string_character_t characters[iso2ObjectType_Encoding_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Encoding ;
	unsigned int Encoding_isUsed:1;

	 struct {
		exi_string_character_t characters[iso2ObjectType_ANY_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  ANY ;
	unsigned int ANY_isUsed:1;
}iso2ObjectType;

typedef struct  {
	int noContent;
}iso2EVFinePositioningParametersType;



typedef struct  {
	 struct {
		uint8_t array[iso2SensorOrderListType_SensorPosition_ARRAY_SIZE];
		uint16_t arrayLen;
	} SensorPosition;
}iso2SensorOrderListType;


typedef struct  {
	 struct {
		uint16_t array[iso2MeasurementDataListType_MeasurementData_ARRAY_SIZE];
		uint16_t arrayLen;
	} MeasurementData;
}iso2MeasurementDataListType;

typedef struct  {
	iso2electricalChargingDeviceStatusType EVElectricalChargingDeviceStatus ;
	iso2mechanicalChargingDeviceStatusType EVMechanicalChargingDeviceStatus ;
}iso2DisconnectChargingDeviceReqType;



typedef struct  {
	uint32_t DepartureTime ;
	 iso2PhysicalValueType EVMaximumPower ;
	 iso2PhysicalValueType EVMinimumPower ;
	 iso2PhysicalValueType EVTargetEnergyRequest ;
	unsigned int EVTargetEnergyRequest_isUsed:1;
	 iso2PhysicalValueType EVMaximumEnergyRequest ;
	unsigned int EVMaximumEnergyRequest_isUsed:1;
	 iso2PhysicalValueType EVMinimumEnergyRequest ;
	unsigned int EVMinimumEnergyRequest_isUsed:1;
}iso2WPT_EVChargeParameterType;


typedef struct  {

	 struct {
		exi_string_character_t characters[iso2CertificateChainType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	unsigned int Id_isUsed:1;
	 struct {
		uint8_t bytes[iso2CertificateChainType_Certificate_BYTES_SIZE];
		uint16_t bytesLen;
	}  Certificate ;
	iso2SubCertificatesType SubCertificates ;
	unsigned int SubCertificates_isUsed:1;
}iso2CertificateChainType;

typedef struct  {
	uint8_t SensorID ;
	int8_t EffectiveRadiatedPower ;
	 iso2MeasurementDataListType MeasurementDataList ;
}iso2SensorMeasurementsType;

typedef struct  {
	 struct {
		 iso2TransformType array[iso2TransformsType_Transform_ARRAY_SIZE];
		uint16_t arrayLen;
	} Transform;
}iso2TransformsType;

typedef struct  {
	iso2EVCheckInStatusType EVCheckInStatus ;
	iso2parkingMethodType ParkingMethod ;
	unsigned int ParkingMethod_isUsed:1;
}iso2VehicleCheckInReqType;


typedef struct  {
	iso2responseCodeType ResponseCode ;
	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	 iso2PhysicalValueType EVSEPresentCurrent ;
	 iso2PhysicalValueType EVSEPresentVoltage ;
	int EVSEPowerLimitAchieved ;
	int EVSECurrentLimitAchieved ;
	int EVSEVoltageLimitAchieved ;
	 iso2PhysicalValueType EVSEMaximumChargePower ;
	unsigned int EVSEMaximumChargePower_isUsed:1;
	 iso2PhysicalValueType EVSEMaximumDischargePower ;
	unsigned int EVSEMaximumDischargePower_isUsed:1;
	 iso2PhysicalValueType EVSEMaximumChargeCurrent ;
	unsigned int EVSEMaximumChargeCurrent_isUsed:1;
	 iso2PhysicalValueType EVSEMaximumDischargeCurrent ;
	unsigned int EVSEMaximumDischargeCurrent_isUsed:1;
	 iso2PhysicalValueType EVSEMaximumVoltage ;
	unsigned int EVSEMaximumVoltage_isUsed:1;
	 iso2PhysicalValueType EVSEMinimumVoltage ;
	unsigned int EVSEMinimumVoltage_isUsed:1;
	 struct {
		exi_string_character_t characters[iso2DC_BidirectionalControlResType_EVSEID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  EVSEID ;
	uint8_t SAScheduleTupleID ;
	unsigned int SAScheduleTupleID_isUsed:1;
	 iso2MeterInfoType MeterInfo ;
	unsigned int MeterInfo_isUsed:1;
	int ReceiptRequired ;
	unsigned int ReceiptRequired_isUsed:1;
}iso2DC_BidirectionalControlResType;







/* Description: Structure to configure Session Setup Response Message:
 *	    1. The Response Code (Enumeration)
 *	    2. The EVSEID (Length: 7 - 37 )
 *      3. The EVSE Status (Minor Version)    //NOT ISO
 *      4. The EVSETimeStamp (Optional)
 */
typedef struct{

	iso2responseCodeType ResponseCode ;
	iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	 struct {
		exi_string_character_t characters[iso2SessionSetupResType_EVSEID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  EVSEID ;
	int64_t EVSETimeStamp ;
	unsigned int EVSETimeStamp_isUsed:1;
}iso2SessionSetupResType;

/* Description: Structure to configure Reference Type:
 *	    1. The ID (Optional)
 *	    2. The URI (Optional)
 *      3. The Type (Optional)
 *      4. The Transforms (Optional)
 *      5. The DigestMethod
 *      6. The DigestValue
 */
typedef struct {

	 struct {
		exi_string_character_t characters[iso2ReferenceType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	unsigned int Id_isUsed:1;

	 struct {
		exi_string_character_t characters[iso2ReferenceType_URI_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  URI ;
	unsigned int URI_isUsed:1;

	 struct {
		exi_string_character_t characters[iso2ReferenceType_Type_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Type ;
	unsigned int Type_isUsed:1;

	iso2TransformsType Transforms ;
	unsigned int Transforms_isUsed:1;


	iso2DigestMethodType DigestMethod ;

	 struct {
		uint8_t bytes[iso2ReferenceType_DigestValue_BYTES_SIZE];
		uint16_t bytesLen;
	}  DigestValue ;
}iso2ReferenceType;

//NOT ISO
typedef struct {

	 struct {
		iso2SensorType array[iso2SensorListType_Sensor_ARRAY_SIZE];
		uint16_t arrayLen;
	} Sensor;
}iso2SensorListType;

//NOT ISO
typedef struct {

	uint8_t NumberOfSensors ;

	iso2SensorListType SensorList ;

	iso2SensorOrderListType SensorOrder ;

	uint8_t SignalPulseDuration ;

	uint8_t SignalSeparationTime ;

	uint8_t PackageSeparationTime ;

	uint16_t AlignmentOffset ;
}iso2LFA_EVFinePositioningSetupParametersType;

//NOT ISO
typedef struct{

	iso2PhysicalValueType EVSEMaximumPower ;

	iso2PhysicalValueType EVSEMinimumPower ;
}iso2WPT_EVSEChargeParameterType;

/* Description: Structure to configure ParameterSet:
 *	    1. ParameterSetID
 *	    2. Parameter
 */
typedef struct {

	uint16_t ParameterSetID ;
	struct {
		 iso2ParameterType array[iso2ParameterSetType_Parameter_ARRAY_SIZE];
		uint16_t arrayLen;
	} Parameter;
}iso2ParameterSetType;

/* Description: Structure to configure Payment Details Response Message:
 *	    1. Response Code (Enumeration)
 *	    2. EVSEStatus               //NOT ISO
 *	    3. GenChallenge
 *	    4. EVSETimeStamp
 */
typedef struct {

	iso2responseCodeType ResponseCode ;

	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;

	struct {
		uint8_t bytes[iso2PaymentDetailsResType_GenChallenge_BYTES_SIZE];
		uint16_t bytesLen;
	}  GenChallenge ;

	int64_t EVSETimeStamp ;
}iso2PaymentDetailsResType;

//NOT ISO
#define iso2AC_BidirectionalControlResType_EVSEID_CHARACTERS_SIZE 37 + EXTRA_CHAR
typedef struct {
	iso2responseCodeType ResponseCode ;
	iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	iso2EVSEProcessingType EVSEProcessing ;
	iso2PhysicalValueType EVSETargetPower ;
	iso2PhysicalValueType EVSETargetReactivePower ;
	 struct {
		exi_string_character_t characters[iso2AC_BidirectionalControlResType_EVSEID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  EVSEID ;
	uint8_t SAScheduleTupleID ;
	unsigned int SAScheduleTupleID_isUsed:1;
	 iso2MeterInfoType MeterInfo ;
	unsigned int MeterInfo_isUsed:1;
	int ReceiptRequired ;
	unsigned int ReceiptRequired_isUsed:1;
}iso2AC_BidirectionalControlResType;

//NOT ISO
typedef struct {
	iso2EVCheckOutStatusType EVCheckOutStatus ;
	uint64_t CheckOutTime ;
} iso2VehicleCheckOutReqType;

//NOT ISO
typedef struct {
	iso2responseCodeType ResponseCode ;
	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	iso2EVSEProcessingType EVSEProcessing ;
	 iso2ParameterSetType AlignmentCheckParameters ;
	unsigned int AlignmentCheckParameters_isUsed:1;
}iso2AlignmentCheckResType;

//RESEARCH    iSO2 P.129 , P.91
#define iso2MinimumPMaxRequestType_MinimumPMaxScheduleEntry_ARRAY_SIZE 3
typedef struct {
	 struct {
		 iso2PMaxScheduleEntryType array[iso2MinimumPMaxRequestType_MinimumPMaxScheduleEntry_ARRAY_SIZE];
		uint16_t arrayLen;
	} MinimumPMaxScheduleEntry;
}iso2MinimumPMaxRequestType;

//NOT ISO
typedef struct {
	iso2responseCodeType ResponseCode ;
    iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	iso2EVSEProcessingType EVSEProcessing ;
	iso2electricalChargingDeviceStatusType EVSEElectricalChargingDeviceStatus ;
	iso2mechanicalChargingDeviceStatusType EVSEMechanicalChargingDeviceStatus ;
}iso2DisconnectChargingDeviceResType;


/* Description: Structure to configure Payment Details Request Message:
 *	    1. eMAID (Identification of Contract)
 *	    2. ContractSignatureCertChain
 */
typedef struct {

	 struct {
		exi_string_character_t characters[iso2PaymentDetailsReqType_eMAID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  eMAID ;

	 iso2CertificateChainType ContractSignatureCertChain ;
}iso2PaymentDetailsReqType;

//NOT ISO
typedef struct {
	iso2ParameterSetType GenericParameters ;
}iso2Generic_EVFinePositioningParametersType;

//NOT ISO
typedef struct {
	iso2electricalChargingDeviceStatusType EVElectricalChargingDeviceStatus ;
	iso2mechanicalChargingDeviceStatusType EVMechanicalChargingDeviceStatus ;
}iso2ConnectChargingDeviceReqType;

/* Description: Structure to configure AC EVSE Charging Parameter:
 *	    1. EVSEMaximumChargeCurrent
 *	    2. EVSENominalVoltage
 *	    3. EVSENominalFrequency
 */
                 //RESEARCH P.143 (Parameters)
typedef struct {
	 iso2PhysicalValueType EVSEMaximumChargeCurrent ;
	 iso2PhysicalValueType EVSENominalVoltage ;
	 iso2PhysicalValueType EVSENominalFrequency ;
}iso2AC_EVSEChargeParameterType;

/* Description: Structure to configure Sales Tariff Entry:
 *	    1. EPriceLevel (Optional)
 *	    2. RelativeTimeInterval
 *	    3. ConsumptionCost
 */
typedef struct {
	 iso2RelativeTimeIntervalType RelativeTimeInterval ;

	uint8_t EPriceLevel ;
	unsigned int EPriceLevel_isUsed:1;

	 struct {
		 iso2ConsumptionCostType array[iso2SalesTariffEntryType_ConsumptionCost_ARRAY_SIZE];
		uint16_t arrayLen;
	} ConsumptionCost;
}iso2SalesTariffEntryType;


//NOT ISO
//RESEARCH P.282
typedef struct {
	iso2PhysicalValueType EVSEMaximumChargePower ;
	iso2PhysicalValueType EVSEMaximumChargeCurrent ;
	 iso2PhysicalValueType EVSEMinimumChargeCurrent ;
     iso2PhysicalValueType EVSEMaximumVoltage ;
	iso2PhysicalValueType EVSEMinimumVoltage ;
	iso2PhysicalValueType EVSECurrentRegulationTolerance ;
	unsigned int EVSECurrentRegulationTolerance_isUsed:1;
	 iso2PhysicalValueType EVSEPeakCurrentRipple ;
	iso2PhysicalValueType EVSEEnergyToBeDelivered ;
	unsigned int EVSEEnergyToBeDelivered_isUsed:1;
	iso2PhysicalValueType EVSEMaximumDischargePower ;
	iso2PhysicalValueType EVSEMaximumDischargeCurrent ;
	 iso2PhysicalValueType EVSEMinimumDischargeCurrent ;
}iso2DC_EVSEBidirectionalParameterType;


//NOT ISO
//RESEARCH
typedef struct {
	uint16_t CurrentRange ;
	unsigned int CurrentRange_isUsed:1;
	int8_t CurrentSOC ;
	unsigned int CurrentSOC_isUsed:1;
	int8_t TargetSOC ;
	unsigned int TargetSOC_isUsed:1;
	int8_t BulkSOC ;
	unsigned int BulkSOC_isUsed:1;
	int8_t MinimumSOC ;
	unsigned int MinimumSOC_isUsed:1;
	 iso2PhysicalValueType ChargingPerformance ;
	unsigned int ChargingPerformance_isUsed:1;
	int8_t RemainingTimeToTargetSOC ;
	unsigned int RemainingTimeToTargetSOC_isUsed:1;
	int8_t RemainingTimeToBulkSOC ;
	unsigned int RemainingTimeToBulkSOC_isUsed:1;
	int8_t RemainingTimeToMinimumSOC ;
	unsigned int RemainingTimeToMinimumSOC_isUsed:1;
	int ChargingComplete ;
	unsigned int ChargingComplete_isUsed:1;
	int BulkChargingComplete ;
	unsigned int BulkChargingComplete_isUsed:1;
	int InletHot ;
	unsigned int InletHot_isUsed:1;
}iso2DisplayParametersType ;

/* Description: Structure to configure DC EV Parameter Type:
 *	    1. DepartureTime
 *	    2. EVMaximumChargePower (Optional)
 *	    3. EVMinimumChargePower (Optional)
 *	    4. EVMaximumChargeCurrent
 *	    5. EVMinimumChargeCurrent
 *	    6. EVMaximumVoltage
 *	    7. EVTargetEnergyRequest  (Optional)
 *	    8. EVMaximumEnergyRequest (Optional)
 *	    9. EVMinimumEnergyRequest (Optional)
 *	    10. CurrentSOC
 *	    11. TargetSOC
 *	    12. BulkSOC
 *	    13. EVMaximumDischargePower (Optional)
 *	    14. EVMinimumDischargePower (Optional)
 *	    15. EVMaximumDischargeCurrent
 *	    16. EVMinimumDischargeCurrent
 *	    17. EVMinimumVoltage
 *	    18. MinimumSOC             (Optional)
 */
//RESEARCH P.281
typedef struct {
	uint32_t DepartureTime ;

	 iso2PhysicalValueType EVMaximumChargePower ;
	unsigned int EVMaximumChargePower_isUsed:1;

	 iso2PhysicalValueType EVMinimumChargePower ;
	unsigned int EVMinimumChargePower_isUsed:1;

	 iso2PhysicalValueType EVMaximumChargeCurrent ;
	 iso2PhysicalValueType EVMinimumChargeCurrent ;
	 iso2PhysicalValueType EVMaximumVoltage ;

	 iso2PhysicalValueType EVTargetEnergyRequest ;
	unsigned int EVTargetEnergyRequest_isUsed:1;

	 iso2PhysicalValueType EVMaximumEnergyRequest ;
	unsigned int EVMaximumEnergyRequest_isUsed:1;

	 iso2PhysicalValueType EVMinimumEnergyRequest ;
	unsigned int EVMinimumEnergyRequest_isUsed:1;

	int8_t CurrentSOC ;
	unsigned int CurrentSOC_isUsed:1;

	int8_t TargetSOC ;
	unsigned int TargetSOC_isUsed:1;

	int8_t BulkSOC ;
	unsigned int BulkSOC_isUsed:1;

	 iso2PhysicalValueType EVMaximumDischargePower ;
	unsigned int EVMaximumDischargePower_isUsed:1;

	 iso2PhysicalValueType EVMinimumDischargePower ;
	unsigned int EVMinimumDischargePower_isUsed:1;

	 iso2PhysicalValueType EVMaximumDischargeCurrent ;
	 iso2PhysicalValueType EVMinimumDischargeCurrent ;
	 iso2PhysicalValueType EVMinimumVoltage ;

	int8_t MinimumSOC ;
	unsigned int MinimumSOC_isUsed:1;
}iso2DC_EVBidirectionalParameterType;

//NOT ISO
#define iso2MagneticVectorType_GAID_CHARACTERS_SIZE 50 + EXTRA_CHAR 
typedef struct {
	 struct {
		exi_string_character_t characters[iso2MagneticVectorType_GAID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  GAID ;
	uint16_t Distance ;
	 iso2PhysicalValueType AngleGAtoVA ;
	 iso2PhysicalValueType RotationVAtoGA ;
	iso2FODStatusType FODStatus ;
}iso2MagneticVectorType;

//NOT ISO
typedef struct {
	iso2responseCodeType ResponseCode ;
	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	iso2operationModeType OperationMode ;
	iso2mechanicalChargingDeviceStatusType EVSEMechanicalChargingDeviceStatus ;
}iso2SystemStatusResType;

//NOT ISO
typedef struct {
	iso2responseCodeType ResponseCode ;
	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
}iso2V2GResponseType;

/* Description: Structure to configure Pre Charge Response:
 *	    1. ResponseCode
 *	    2. EVSEStatus  (Optional)
 *	    3. EVSEPresentVoltage
 */
typedef struct {
	iso2responseCodeType ResponseCode ;
	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	 iso2PhysicalValueType EVSEPresentVoltage ;
}iso2PreChargeResType;

/* Description: Structure to configure Payment Service Selection Response:
 *	    1. ResponseCode
 *	    2. EVSEStatus (Optional)
 */
typedef struct {
	iso2responseCodeType ResponseCode ;

	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
}iso2PaymentServiceSelectionResType;

/* Description: Structure to configure Manifest Type:
 *	    1. ID (Optional)
 *	    2. Reference
 */
typedef struct {
	 struct {
		exi_string_character_t characters[iso2ManifestType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	unsigned int Id_isUsed:1;

	struct {
		 iso2ReferenceType array[iso2ManifestType_Reference_ARRAY_SIZE];
		uint16_t arrayLen;
	} Reference;
}iso2ManifestType;

/* Description: Structure to configure Selected Service List:
 *	    1. SelectedService (MAX: 16)
 */
typedef struct {
	 struct {
		 iso2SelectedServiceType array[iso2SelectedServiceListType_SelectedService_ARRAY_SIZE];
		uint16_t arrayLen;
	} SelectedService;
}iso2SelectedServiceListType;

//NOT ISO
typedef struct {
	 iso2ParameterSetType GenericParameters ;
}iso2Generic_EVSEFinePositioningParametersType;

/* Description: Structure to configure List Of Root Certificate IDs:
 *	    1. RootCertificateID (MAX: 20)
 */
typedef struct {
	 struct {
		 iso2X509IssuerSerialType array[iso2ListOfRootCertificateIDsType_RootCertificateID_ARRAY_SIZE];
		uint16_t arrayLen;
	} RootCertificateID;
}iso2ListOfRootCertificateIDsType;

//NOT ISO
typedef struct {
	iso2EVSEProcessingType EVProcessing ;
	 iso2ParameterSetType PairingParameters ;
	unsigned int PairingParameters_isUsed:1;
}iso2PairingReqType;

/* Description: Structure to configure Current Demand Response Type:
 *	    1. Response Code
 *	    2. EVSEStatus (Optional)
 *	    3. EVSEPresentCurrent
 *	    4. EVSEPresentVoltage
 *	    5. EVSEPowerLimitAchieved
 *	    6. EVSECurrentLimitAchieved
 *	    7. EVSEVoltageLimitAchieved
 *	    8. EVSEMaximumPower (Optional)
 *	    9. EVSEMaximumCurrent (Optional)
 *	    10. EVSEMaximumVoltage (Optional)
 *	    11. EVSEID
 *	    12. SAScheduleTupleID (Optional)
 *	    13. MeterInfo (Optional)
 *	    14. ReceiptRequired (Optional)
 */
typedef struct {
	iso2responseCodeType ResponseCode ;        //

	 iso2EVSEStatusType EVSEStatus ;   //
	unsigned int EVSEStatus_isUsed:1; //

	 iso2PhysicalValueType EVSEPresentCurrent ;  // 
	 iso2PhysicalValueType EVSEPresentVoltage ;  // 
	int EVSEPowerLimitAchieved ;   //
	int EVSECurrentLimitAchieved ;  //
	int EVSEVoltageLimitAchieved ;  //

	 iso2PhysicalValueType EVSEMaximumPower ; //
	unsigned int EVSEMaximumPower_isUsed:1; //
 
	 iso2PhysicalValueType EVSEMaximumCurrent ;  //
	unsigned int EVSEMaximumCurrent_isUsed:1;  //

	 iso2PhysicalValueType EVSEMaximumVoltage ;  //
	unsigned int EVSEMaximumVoltage_isUsed:1;  //

	 struct { //
		exi_string_character_t characters[iso2CurrentDemandResType_EVSEID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  EVSEID ;

	uint8_t SAScheduleTupleID ; //
	unsigned int SAScheduleTupleID_isUsed:1; //

	 iso2MeterInfoType MeterInfo ;
	unsigned int MeterInfo_isUsed:1;

	int ReceiptRequired ;
	unsigned int ReceiptRequired_isUsed:1;
}iso2CurrentDemandResType;

//RESEARCH P.275
typedef struct {
	 iso2PhysicalValueType EVTargetEnergyRequest ;

	 iso2PhysicalValueType EVMaximumEnergyRequest ;
	unsigned int EVMaximumEnergyRequest_isUsed:1;

	 iso2PhysicalValueType EVMinimumEnergyRequest ;
	unsigned int EVMinimumEnergyRequest_isUsed:1;

	 iso2DisplayParametersType DisplayParameters ;
	unsigned int DisplayParameters_isUsed:1;

	 iso2PhysicalValueType EVMaximumChargePower ;
	unsigned int EVMaximumChargePower_isUsed:1;

	 iso2PhysicalValueType EVMaximumChargeCurrent ;
	unsigned int EVMaximumChargeCurrent_isUsed:1;

	 iso2PhysicalValueType EVMinimumChargeCurrent ;
	unsigned int EVMinimumChargeCurrent_isUsed:1;
}iso2ChargingStatusReqType;

/* Description: Structure to configure Certificate Installation Response Type:
 *	    1. ResponseCode
 *	    2. EVSEStatus (Optional) //NOT ISO
 *	    3. SAProvisioningCertificateChain
 *	    4. ContractSignatureCertChain
 *	    5. ContractSignatureEncryptedPrivateKey
 *	    6. DHpublickey
 *	    7. eMAID
 */
typedef struct {
	iso2responseCodeType ResponseCode ;

	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;

	 iso2CertificateChainType SAProvisioningCertificateChain ;
	 iso2CertificateChainType ContractSignatureCertChain ;
	 iso2ContractSignatureEncryptedPrivateKeyType ContractSignatureEncryptedPrivateKey ;
	 iso2DiffieHellmanPublickeyType DHpublickey ;
	 iso2EMAIDType eMAID ;
}iso2CertificateInstallationResType;

//NOT ISO
#define iso2SensorPackageType_SensorMeasurements_ARRAY_SIZE 5
typedef struct {
	uint32_t PackageIndex ;
	 struct {
		 iso2SensorMeasurementsType array[iso2SensorPackageType_SensorMeasurements_ARRAY_SIZE];
		uint16_t arrayLen;
	} SensorMeasurements;
}iso2SensorPackageType;

/* Description: Structure to configure Service Discovery Response Type:
 *	    1. ResponseCode
 *	    2. EVSEStatus (Optional) //NOT ISO
 *	    3. PaymentOptionList
 *	    4. EnergyTransferServiceList
 *	    5. VASList (Optional)
 */
typedef struct {
	iso2responseCodeType ResponseCode ;

	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;

	 iso2PaymentOptionListType PaymentOptionList ;
	 iso2ServiceListType EnergyTransferServiceList ;  //ChargeService

	 iso2ServiceListType VASList ;
	unsigned int VASList_isUsed:1;
}iso2ServiceDiscoveryResType;

/* Description: Structure to configure Power Demand Response Type:
 *	    1. ResponseCode
 *	    2. EVSEStatus (Optional) //NOT ISO
 *	    3. EVSEOutputPower
 *	    4. SAScheduleTupleID (Optional)
 *	    5. MeterInfo (Optional)
 *	    6. ReceiptRequired (Optional)
 *	    7. PowerDemandParameters (Optional)
 */
//RESEARCH P.93
typedef struct {
	iso2responseCodeType ResponseCode;

	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;

	 iso2PhysicalValueType EVSEOutputPower ;
	 struct {
		exi_string_character_t characters[iso2PowerDemandResType_EVSEID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  EVSEID ;

	uint8_t SAScheduleTupleID ;
	unsigned int SAScheduleTupleID_isUsed:1;

	 iso2MeterInfoType MeterInfo ;
	unsigned int MeterInfo_isUsed:1;

	int ReceiptRequired ;
	unsigned int ReceiptRequired_isUsed:1;

	 iso2ParameterSetType PowerDemandParameters ;
	unsigned int PowerDemandParameters_isUsed:1;
}iso2PowerDemandResType;

/* Description: Structure to configure Charging Profile Type:
 *	    1. ProfileEntry (MAX: 24)
 */
typedef struct {
	 struct {
		 iso2PMaxScheduleEntryType array[iso2ChargingProfileType_ProfileEntry_ARRAY_SIZE];
		uint16_t arrayLen;
	} ProfileEntry;
}iso2ChargingProfileType;

/* Description: Structure to configure Sales Tariff Type:
 *	    1. ID
 *	    2. SalesTariffID
 *	    3. EVSEOutputPower
 *	    4. SalesTariffDescription
 *	    5. NumEPriceLevels (Optional)
 *	    6. SalesTariffEntry
 */
typedef struct {
	struct {
		exi_string_character_t characters[iso2SalesTariffType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	uint8_t SalesTariffID ;

	struct {
		exi_string_character_t characters[iso2SalesTariffType_SalesTariffDescription_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  SalesTariffDescription ;
	unsigned int SalesTariffDescription_isUsed:1;

	uint8_t NumEPriceLevels ;
	unsigned int NumEPriceLevels_isUsed:1;

	struct {
		 iso2SalesTariffEntryType array[iso2SalesTariffType_SalesTariffEntry_ARRAY_SIZE];
		uint16_t arrayLen;
	} SalesTariffEntry;
}iso2SalesTariffType;

/* Description: Structure to configure Signed Info Type:
 *	    1. ID (Optional)
 *	    2. CanonicalizationMethod
 *	    3. SignatureMethod
 *	    4. SalesTariffDescription
 *	    5. Reference
 */
typedef struct {
	struct {
		exi_string_character_t characters[iso2SignedInfoType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	unsigned int Id_isUsed:1;

	 iso2CanonicalizationMethodType CanonicalizationMethod ;
	 iso2SignatureMethodType SignatureMethod ;
	 struct {
		 iso2ReferenceType array[iso2SignedInfoType_Reference_ARRAY_SIZE];
		uint16_t arrayLen;
	} Reference;
}iso2SignedInfoType;

//NOT ISO   (PowerDeliveryRes implemented.....?)
typedef struct {
	iso2responseCodeType ResponseCode ; //

	 iso2EVSEStatusType EVSEStatus ; // 
	unsigned int EVSEStatus_isUsed:1;

	iso2EVSEProcessingType EVSEProcessing ;
}iso2PowerDeliveryResType;

/* Description: Structure to configure Retrieval Method Type:
 *	    1. URI (Optional)
 *	    2. Type (Optional)
 *	    3. Transforms  (Optional)
 */
typedef struct {
	struct {
		exi_string_character_t characters[iso2RetrievalMethodType_URI_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  URI ;
	unsigned int URI_isUsed:1;

	struct {
		exi_string_character_t characters[iso2RetrievalMethodType_Type_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Type ;
	unsigned int Type_isUsed:1;

	iso2TransformsType Transforms ;
	unsigned int Transforms_isUsed:1;
}iso2RetrievalMethodType;

//NOT ISO
#define iso2MagneticVectorListType_MagneticVector_ARRAY_SIZE 5
typedef struct {
	struct {
		 iso2MagneticVectorType array[iso2MagneticVectorListType_MagneticVector_ARRAY_SIZE];
		uint16_t arrayLen;
	} MagneticVector;
}iso2MagneticVectorListType;

/* Description: Structure to configure Service Parameter List Type:
 *	    1. ParameterSet
 */
typedef struct {
	 struct {
		 iso2ParameterSetType array[iso2ServiceParameterListType_ParameterSet_ARRAY_SIZE];
		uint16_t arrayLen;
	} ParameterSet;
}iso2ServiceParameterListType;

/* Description: Structure to configure Service Parameter List Type:
 *	    1. PMaxScheduleEntry
 */
typedef struct {
	 struct {
		 iso2PMaxScheduleEntryType array[iso2PMaxScheduleType_PMaxScheduleEntry_ARRAY_SIZE];
		uint16_t arrayLen;
	} PMaxScheduleEntry;
}iso2PMaxScheduleType;

/* Description: Structure to configure Certificate Update Response:
 *	    1. ResponseCode
 *	    2. EVSEStatus (Optional)
 *	    3. SAProvisioningCertificateChain
 *	    4. ContractSignatureCertChain
 *	    5. ContractSignatureEncryptedPrivateKey
 *	    6. DHpublickey
 *	    7. eMAID
 *	    8. RetryCounter (Optional)
 */
typedef struct {
	iso2responseCodeType ResponseCode ;

	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;

	 iso2CertificateChainType SAProvisioningCertificateChain ;
	 iso2CertificateChainType ContractSignatureCertChain ;
	 iso2ContractSignatureEncryptedPrivateKeyType ContractSignatureEncryptedPrivateKey ;
	 iso2DiffieHellmanPublickeyType DHpublickey ;
	 iso2EMAIDType eMAID ;

	int16_t RetryCounter ;
	unsigned int RetryCounter_isUsed:1;
}iso2CertificateUpdateResType;

//NOT ISO
typedef struct {
	 iso2PhysicalValueType EVTargetEnergyRequest ;
	 iso2PhysicalValueType EVMaximumEnergyRequest ;
	unsigned int EVMaximumEnergyRequest_isUsed:1;
	 iso2PhysicalValueType EVMinimumEnergyRequest ;
	unsigned int EVMinimumEnergyRequest_isUsed:1;
	 iso2DisplayParametersType DisplayParameters ;
	unsigned int DisplayParameters_isUsed:1;
	 iso2PhysicalValueType EVTargetCurrent ;
	 iso2PhysicalValueType EVTargetVoltage ;
	 iso2PhysicalValueType EVMaximumVoltage ;
	 iso2PhysicalValueType EVMinimumVoltage ;
	 iso2PhysicalValueType EVMaximumChargeCurrent ;
	 iso2PhysicalValueType EVMaximumDischargeCurrent ;
	unsigned int EVMaximumDischargeCurrent_isUsed:1;
	 iso2PhysicalValueType EVMaximumChargePower ;
	unsigned int EVMaximumChargePower_isUsed:1;
	 iso2PhysicalValueType EVMaximumDischargePower ;
	unsigned int EVMaximumDischargePower_isUsed:1;
}iso2DC_BidirectionalControlReqType;

/* Description: Structure to configure Certificate Update Request:
 *	    1. ID
 *	    2. ContractSignatureCertChain
 *	    3. eMAID
 *	    4. ContractSignatureCertChain
 *	    5. ListOfRootCertificateIDs
 */
typedef struct {
	 struct {
		exi_string_character_t characters[iso2CertificateUpdateReqType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	 iso2CertificateChainType ContractSignatureCertChain ;
	 struct {
		exi_string_character_t characters[iso2CertificateUpdateReqType_eMAID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  eMAID ;
	 iso2ListOfRootCertificateIDsType ListOfRootCertificateIDs ;
}iso2CertificateUpdateReqType;

//NOT ISO
typedef struct {
	uint8_t NumberOfSensors ;
	 iso2SensorListType SensorList ;
	 iso2SensorOrderListType SensorOrder ;
	uint8_t SignalPulseDuration ;
	uint8_t SignalSeparationTime ;
	uint8_t PackageSeparationTime ;
	uint16_t AlignmentOffset ;
	uint16_t SignalFrequency ;
}iso2LFA_EVSEFinePositioningSetupParametersType;
//NOT ISO
typedef struct {
	iso2EVSEProcessingType EVProcessing ;
	 iso2ParameterSetType AlignmentCheckParameters ;
	unsigned int AlignmentCheckParameters_isUsed:1;
}iso2AlignmentCheckReqType;

/* Description: Structure to configure Certificate Installation Request:
 *	    1. ID
 *	    2. OEMProvisioningCert
 *	    3. ListOfRootCertificateIDs
 */
typedef struct {
	 struct {
		exi_string_character_t characters[iso2CertificateInstallationReqType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	 struct {
		uint8_t bytes[iso2CertificateInstallationReqType_OEMProvisioningCert_BYTES_SIZE];
		uint16_t bytesLen;
	}  OEMProvisioningCert ;
	iso2ListOfRootCertificateIDsType ListOfRootCertificateIDs ;
}iso2CertificateInstallationReqType;

/* Description: Structure to configure Charge Parameter Discovery Request:
 *	    1. MaxSupportingPoints (Optional)
 *	    2. EVEnergyTransferParameter (Optional)
 *	    3. AC_EVChargeParameter (Optional)
 *	    4. AC_EVBidirectionalParameter (Optional)  //NOT ISO
 *	    5. DC_EVChargeParameter (Optional)
 *	    6. DC_EVBidirectionalParameter (Optional)  //NOT ISO
 *	    7. WPT_EVChargeParameter (Optional) //NOT ISO
 *	    8. MinimumPMaxRequest (Optional)
 */
typedef struct {

	uint16_t MaxSupportingPoints ;
	unsigned int MaxSupportingPoints_isUsed:1;

	 iso2EVEnergyTransferParameterType EVEnergyTransferParameter ;
	unsigned int EVEnergyTransferParameter_isUsed:1;

	 iso2AC_EVChargeParameterType AC_EVChargeParameter ;
	unsigned int AC_EVChargeParameter_isUsed:1;

	 iso2AC_EVBidirectionalParameterType AC_EVBidirectionalParameter ;
	unsigned int AC_EVBidirectionalParameter_isUsed:1;

	 iso2DC_EVChargeParameterType DC_EVChargeParameter ;
	unsigned int DC_EVChargeParameter_isUsed:1;

	 iso2DC_EVBidirectionalParameterType DC_EVBidirectionalParameter ;
	unsigned int DC_EVBidirectionalParameter_isUsed:1;

	 iso2WPT_EVChargeParameterType WPT_EVChargeParameter ;
	unsigned int WPT_EVChargeParameter_isUsed:1;

	 iso2MinimumPMaxRequestType MinimumPMaxRequest ;
	unsigned int MinimumPMaxRequest_isUsed:1;
}iso2ChargeParameterDiscoveryReqType;

//NOT ISO
#define iso2SensorPackageListType_SensorPackage_ARRAY_SIZE 5
typedef struct {
	 struct {
		 iso2SensorPackageType array[iso2SensorPackageListType_SensorPackage_ARRAY_SIZE];
		uint16_t arrayLen;
	} SensorPackage;
}iso2SensorPackageListType;

//NOT ISO
typedef struct {
	 iso2PhysicalValueType EVTargetEnergyRequest ;

	 iso2PhysicalValueType EVMaximumEnergyRequest ;
	unsigned int EVMaximumEnergyRequest_isUsed:1;

	 iso2PhysicalValueType EVMinimumEnergyRequest ;
	unsigned int EVMinimumEnergyRequest_isUsed:1;

	 iso2DisplayParametersType DisplayParameters ;
	unsigned int DisplayParameters_isUsed:1;
}iso2ChargeLoopReqType;

//NOT ISO
typedef struct {
	 iso2PhysicalValueType EVTargetEnergyRequest ;

	 iso2PhysicalValueType EVMaximumEnergyRequest ;
	unsigned int EVMaximumEnergyRequest_isUsed:1;

	 iso2PhysicalValueType EVMinimumEnergyRequest ;
	unsigned int EVMinimumEnergyRequest_isUsed:1;

	 iso2DisplayParametersType DisplayParameters ;
	unsigned int DisplayParameters_isUsed:1;

	iso2EVOperationType EVOperation ;
	unsigned int EVOperation_isUsed:1;

	 iso2PhysicalValueType EVMaximumChargePower ;

	 iso2PhysicalValueType EVMaximumDischargePower ;
	unsigned int EVMaximumDischargePower_isUsed:1;

	 iso2PhysicalValueType EVMaximumChargeCurrent ;

	 iso2PhysicalValueType EVMaximumDischargeCurrent ;
	unsigned int EVMaximumDischargeCurrent_isUsed:1;

	 iso2PhysicalValueType EVMinimumChargeCurrent ;

	 iso2PhysicalValueType EVMinimumDischargeCurrent ;
	unsigned int EVMinimumDischargeCurrent_isUsed:1;

	 iso2PhysicalValueType EVPresentActivePower ;
	 iso2PhysicalValueType EVPresentReactivePower ;
}iso2AC_BidirectionalControlReqType;

//NOT ISO
typedef struct {
	 iso2MagneticVectorListType MagneticVectorList ;
}iso2MV_EVSEFinePositioningParametersType;

/* Description: Structure to configure Current Demand Request:
 *	    1. EVTargetEnergyRequest
 *	    2. EVMaximumEnergyRequest (Optional)
 *	    3. EVMinimumEnergyRequest (Optional)
 *	    4. DisplayParameters (Optional)
 *	    5. EVTargetCurrent
 *	    6. EVTargetVoltage
 *	    7. EVMaximumCurrent (Optional)
 *	    8. EVMaximumPower (Optional)
 *	    9. EVMaximumVoltage (Optional)
 */
//RESEARCH P.113
typedef struct {
	 iso2PhysicalValueType EVTargetEnergyRequest ;

	 iso2PhysicalValueType EVMaximumEnergyRequest ;
	unsigned int EVMaximumEnergyRequest_isUsed:1;

	 iso2PhysicalValueType EVMinimumEnergyRequest ;
	unsigned int EVMinimumEnergyRequest_isUsed:1;

	 iso2DisplayParametersType DisplayParameters ;
	unsigned int DisplayParameters_isUsed:1;

	 iso2PhysicalValueType EVTargetCurrent ;
	 iso2PhysicalValueType EVTargetVoltage ;

	 iso2PhysicalValueType EVMaximumCurrent ;
	unsigned int EVMaximumCurrent_isUsed:1;

	 iso2PhysicalValueType EVMaximumPower ;
	unsigned int EVMaximumPower_isUsed:1;

	 iso2PhysicalValueType EVMaximumVoltage ;
	unsigned int EVMaximumVoltage_isUsed:1;
}iso2CurrentDemandReqType;

//ISO 2
typedef struct {
#if SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES
	union {
#endif
		 iso2EVFinePositioningSetupParametersType EVFinePositioningSetupParameters ;
		 iso2LFA_EVFinePositioningSetupParametersType LFA_EVFinePositioningSetupParameters ;
#if SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES
	};
#endif
		unsigned int EVFinePositioningSetupParameters_isUsed:1;
		unsigned int LFA_EVFinePositioningSetupParameters_isUsed:1;
}iso2FinePositioningSetupReqType;

/* Description: Structure to configure Schedule Tuple:
 *	    1. SAScheduleTupleID
 *	    2. PMaxSchedule
 *	    3. PMaxDischargeSchedule (Optional) //NOT ISO
 *	    4. SalesTariff (Optional)
 *	    5. BuyBackTariff (Optional) //NOT ISO
 */
typedef struct {
	uint8_t SAScheduleTupleID ;
	 iso2PMaxScheduleType PMaxSchedule ;

	 iso2PMaxScheduleType PMaxDischargeSchedule ;
	unsigned int PMaxDischargeSchedule_isUsed:1;

	 iso2SalesTariffType SalesTariff ;
	unsigned int SalesTariff_isUsed:1;

	 iso2SalesTariffType BuyBackTariff ;
	unsigned int BuyBackTariff_isUsed:1;
}iso2SAScheduleTupleType;

/* Description: Structure to configure Service Detail Response:
 *	    1. ResponseCode
 *	    2. EVSEStatus  (Optional)    //NOT ISO
 *	    3. ServiceID
 *	    4. ServiceParameterList (Optional)
 */
typedef struct {
	iso2responseCodeType ResponseCode ;

	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;

	uint16_t ServiceID ;

	 iso2ServiceParameterListType ServiceParameterList ;
	unsigned int ServiceParameterList_isUsed:1;
}iso2ServiceDetailResType;

/* Description: Structure to configure Power Delivery Request:
 *	    1. ChargeProgress
 *	    2. EVOperation  (Optional)
 *	    3. SAScheduleTupleID
 *	    4. ChargingProfile (Optional)
 */
typedef struct {
	iso2chargeProgressType ChargeProgress ;

	iso2EVOperationType EVOperation ;
	unsigned int EVOperation_isUsed:1;

	uint8_t SAScheduleTupleID ;
	unsigned int SAScheduleTupleID_isUsed:1;

	 iso2ChargingProfileType ChargingProfile ;
	unsigned int ChargingProfile_isUsed:1;
}iso2PowerDeliveryReqType;

//NOT ISO
typedef struct {
	iso2responseCodeType ResponseCode ;
	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	iso2EVSEProcessingType EVSEProcessing ;
	 iso2ParameterSetType PairingParameters ;
	unsigned int PairingParameters_isUsed:1;
}iso2PairingResType;

//NOT ISO   (PowerDeliveryReq implemented.....?)
typedef struct {
	 iso2PhysicalValueType EVTargetEnergyRequest ;

	 iso2PhysicalValueType EVMaximumEnergyRequest ;
	unsigned int EVMaximumEnergyRequest_isUsed:1;

	 iso2PhysicalValueType EVMinimumEnergyRequest ;
	unsigned int EVMinimumEnergyRequest_isUsed:1;

	 iso2DisplayParametersType DisplayParameters ;
	unsigned int DisplayParameters_isUsed:1;

	 iso2PhysicalValueType EVTargetPower ;
	 iso2PhysicalValueType EVInputPower ;

	 iso2ParameterSetType PowerDemandParameters ;
	unsigned int PowerDemandParameters_isUsed:1;
}iso2PowerDemandReqType;

/* Description: Structure to configure Payment Service Selection Request:
 *	    1. SelectedPaymentOption
 *	    2. SelectedEnergyTransferService
 *	    3. SelectedVASList (Optional) //NOT ISO
 */
typedef struct {
	iso2paymentOptionType SelectedPaymentOption ;
	 iso2SelectedServiceType SelectedEnergyTransferService ;

	 iso2SelectedServiceListType SelectedVASList ;
	unsigned int SelectedVASList_isUsed:1;
}iso2PaymentServiceSelectionReqType;

//NOT ISO
typedef struct {
	uint8_t NumberOfSignalPackages ;
	 iso2SensorPackageListType SensorPackageList ;
}iso2LFA_EVFinePositioningParametersType;


/* Description: Structure to configure Key Info:
 *	    1. Id (Optional)
 *	    2. KeyName
 *	    3. KeyValue
 *	    4. RetrievalMethod
 *	    5. X509Data
 *	    6. PGPData
 *	    7. SPKIData
 *	    8. MgmtData
 *	    9. ANY (Optional) //NOT ISO
 */
typedef struct {

	 struct {
		exi_string_character_t characters[iso2KeyInfoType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	unsigned int Id_isUsed:1;

	 struct {
		struct {
			exi_string_character_t characters[iso2KeyInfoType_KeyName_CHARACTERS_SIZE];
			uint16_t charactersLen;
		}  array[iso2KeyInfoType_KeyName_ARRAY_SIZE];
		uint16_t arrayLen;
	} KeyName;
	 struct {
		 iso2KeyValueType array[iso2KeyInfoType_KeyValue_ARRAY_SIZE];
		uint16_t arrayLen;
	} KeyValue;
	 struct {
		 iso2RetrievalMethodType array[iso2KeyInfoType_RetrievalMethod_ARRAY_SIZE];
		uint16_t arrayLen;
	} RetrievalMethod;
	 struct {
		 iso2X509DataType array[iso2KeyInfoType_X509Data_ARRAY_SIZE];
		uint16_t arrayLen;
	} X509Data;
	 struct {
		 iso2PGPDataType array[iso2KeyInfoType_PGPData_ARRAY_SIZE];
		uint16_t arrayLen;
	} PGPData;
	 struct {
		 iso2SPKIDataType array[iso2KeyInfoType_SPKIData_ARRAY_SIZE];
		uint16_t arrayLen;
	} SPKIData;
	 struct {
		struct {
			exi_string_character_t characters[iso2KeyInfoType_MgmtData_CHARACTERS_SIZE];
			uint16_t charactersLen;
		}  array[iso2KeyInfoType_MgmtData_ARRAY_SIZE];
		uint16_t arrayLen;
	} MgmtData;
	 struct {
		exi_string_character_t characters[iso2KeyInfoType_ANY_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  ANY ;
	unsigned int ANY_isUsed:1;
}iso2KeyInfoType;

//NOT ISO
typedef struct {
	iso2EVSEProcessingType EVProcessing ;

	 iso2EVFinePositioningParametersType EVFinePositioningParameters ;
	unsigned int EVFinePositioningParameters_isUsed:1;

	 iso2Generic_EVFinePositioningParametersType Generic_EVFinePositioningParameters ;
	unsigned int Generic_EVFinePositioningParameters_isUsed:1;

	 iso2LFA_EVFinePositioningParametersType LFA_EVFinePositioningParameters ;
	unsigned int LFA_EVFinePositioningParameters_isUsed:1;
}iso2FinePositioningReqType;

/* Description: Structure to configure Signature Type:
 *	    1. Id (Optional)
 *	    2. SignedInfo
 *	    3. SignatureValue
 *	    4. KeyInfo (Optional)
 *	    5. Object
 */
typedef struct {
	 struct {
		exi_string_character_t characters[iso2SignatureType_Id_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  Id ;
	unsigned int Id_isUsed:1;

	 iso2SignedInfoType SignedInfo ;
	 iso2SignatureValueType SignatureValue ;

	 iso2KeyInfoType KeyInfo ;
	unsigned int KeyInfo_isUsed:1;

	 struct {
		 iso2ObjectType array[iso2SignatureType_Object_ARRAY_SIZE];
		uint16_t arrayLen;
	} Object;
}iso2SignatureType;

//NOT ISO
typedef struct {
	iso2responseCodeType ResponseCode ;
	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	 iso2EVSEFinePositioningSetupParametersType EVSEFinePositioningSetupParameters ;
	unsigned int EVSEFinePositioningSetupParameters_isUsed:1;
	 iso2LFA_EVSEFinePositioningSetupParametersType LFA_EVSEFinePositioningSetupParameters ;
	unsigned int LFA_EVSEFinePositioningSetupParameters_isUsed:1;
	 iso2MV_EVSEFinePositioningSetupParametersType MV_EVSEFinePositioningSetupParameters ;
	unsigned int MV_EVSEFinePositioningSetupParameters_isUsed:1;
}iso2FinePositioningSetupResType;

/* Description: Structure to configure SASchedule List:
 *	    1. SAScheduleTuple (MAX: 3)
 */
typedef struct {
	 struct {
		 iso2SAScheduleTupleType array[iso2SAScheduleListType_SAScheduleTuple_ARRAY_SIZE];
		uint16_t arrayLen;
	} SAScheduleTuple;
}iso2SAScheduleListType;

//NOT ISO
typedef struct {
	uint8_t NumberOfSignalPackages ;
	 iso2SensorPackageListType SensorPackageList ;
}iso2LFA_EVSEFinePositioningParametersType;

/* Description: Structure to configure Message Header:
 *	    1. Session ID
 *	    2. Signature (Optional)
 */
//RESEARCH P.270
typedef struct {
	 struct {
		uint8_t bytes[iso2MessageHeaderType_SessionID_BYTES_SIZE];
		uint16_t bytesLen;
	}  SessionID ;
	 iso2SignatureType Signature ;
	unsigned int Signature_isUsed:1;
}iso2MessageHeaderType;

//NOT ISO
typedef struct {
	iso2responseCodeType ResponseCode ;
	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;
	iso2EVSEProcessingType EVSEProcessing ;
	 iso2EVSEFinePositioningParametersType EVSEFinePositioningParameters ;
	unsigned int EVSEFinePositioningParameters_isUsed:1;
	 iso2Generic_EVSEFinePositioningParametersType Generic_EVSEFinePositioningParameters ;
	unsigned int Generic_EVSEFinePositioningParameters_isUsed:1;
	 iso2LFA_EVSEFinePositioningParametersType LFA_EVSEFinePositioningParameters ;
	unsigned int LFA_EVSEFinePositioningParameters_isUsed:1;
	 iso2MV_EVSEFinePositioningParametersType MV_EVSEFinePositioningParameters ;
	unsigned int MV_EVSEFinePositioningParameters_isUsed:1;
}iso2FinePositioningResType;

/* Description: Structure to configure Charge Parameter Discovery Response:
 *	    1. Response Code
 *	    2. EVSEStatus (Optional) //NOT ISO
 *	    3. EVSEProcessing
 *	    4. SAScheduleList (Optional)
 *	    5. EVSEEnergyTransferParameter (Optional) //RESEARCH P.92
 *	    6. AC_EVSEChargeParameter (Optional)
 *	    7. AC_EVSEBidirectionalParameter (Optional)  //NOT ISO
 *	    8. DC_EVSEChargeParameter (Optional)
 *	    9. DC_EVSEBidirectionalParameter (Optional) //NOT ISO
 *	    10. WPT_EVSEChargeParameter (Optional) //NOT ISO
 */
typedef struct {
	iso2responseCodeType ResponseCode ;

	 iso2EVSEStatusType EVSEStatus ;
	unsigned int EVSEStatus_isUsed:1;

	iso2EVSEProcessingType EVSEProcessing ;

	 iso2SAScheduleListType SAScheduleList ;
	unsigned int SAScheduleList_isUsed:1;

	 iso2EVSEEnergyTransferParameterType EVSEEnergyTransferParameter ;
	unsigned int EVSEEnergyTransferParameter_isUsed:1;

	 iso2AC_EVSEChargeParameterType AC_EVSEChargeParameter ;
	unsigned int AC_EVSEChargeParameter_isUsed:1;

	 iso2AC_EVSEBidirectionalParameterType AC_EVSEBidirectionalParameter ;
	unsigned int AC_EVSEBidirectionalParameter_isUsed:1;

	 iso2DC_EVSEChargeParameterType DC_EVSEChargeParameter ;
	unsigned int DC_EVSEChargeParameter_isUsed:1;

	 iso2DC_EVSEBidirectionalParameterType DC_EVSEBidirectionalParameter ;
	unsigned int DC_EVSEBidirectionalParameter_isUsed:1;

	 iso2WPT_EVSEChargeParameterType WPT_EVSEChargeParameter ;
	unsigned int WPT_EVSEChargeParameter_isUsed:1;
}iso2ChargeParameterDiscoveryResType;









/*------------------------------------------------------------------------------------------------------------------------------------------*/

/* Description: Structure to configure Message Body Type */
typedef struct {
#if SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES
	union {
#endif /* SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES */
		 iso2BodyBaseType BodyElement ;
		 iso2BodyBaseType V2GRequest ;
		 iso2DisconnectChargingDeviceReqType DisconnectChargingDeviceReq ;
		 iso2ConnectChargingDeviceReqType ConnectChargingDeviceReq ;
		 iso2SystemStatusReqType SystemStatusReq ;
		 iso2DC_BidirectionalControlReqType DC_BidirectionalControlReq ;
		 iso2AC_BidirectionalControlReqType AC_BidirectionalControlReq ;
		 iso2VehicleCheckOutReqType VehicleCheckOutReq ;
		 iso2VehicleCheckInReqType VehicleCheckInReq ;
		 iso2PowerDemandReqType PowerDemandReq ;
		 iso2PairingReqType PairingReq ;
		 iso2AlignmentCheckReqType AlignmentCheckReq ;
		 iso2FinePositioningReqType FinePositioningReq ;
		 iso2FinePositioningSetupReqType FinePositioningSetupReq ;
		 iso2WeldingDetectionReqType WeldingDetectionReq ;
		 iso2CurrentDemandReqType CurrentDemandReq ;
		 iso2PreChargeReqType PreChargeReq ;
		 iso2CableCheckReqType CableCheckReq ;
		 iso2ChargingStatusReqType ChargingStatusReq ;
		 iso2CertificateInstallationReqType CertificateInstallationReq ;
		 iso2CertificateUpdateReqType CertificateUpdateReq ;
		 iso2SessionStopReqType SessionStopReq ;
		 iso2MeteringReceiptReqType MeteringReceiptReq ;
		 iso2PowerDeliveryReqType PowerDeliveryReq ;
		 iso2ChargeParameterDiscoveryReqType ChargeParameterDiscoveryReq ;
		 iso2AuthorizationReqType AuthorizationReq ;
		 iso2PaymentDetailsReqType PaymentDetailsReq ;
		 iso2PaymentServiceSelectionReqType PaymentServiceSelectionReq ;
		 iso2ServiceDetailReqType ServiceDetailReq ;
		 iso2ServiceDiscoveryReqType ServiceDiscoveryReq ;
		 iso2SessionSetupReqType SessionSetupReq ;
		 iso2V2GResponseType V2GResponse ;
		 iso2DisconnectChargingDeviceResType DisconnectChargingDeviceRes ;
		 iso2ConnectChargingDeviceResType ConnectChargingDeviceRes ;
		 iso2SystemStatusResType SystemStatusRes ;
		 iso2DC_BidirectionalControlResType DC_BidirectionalControlRes ;
		 iso2AC_BidirectionalControlResType AC_BidirectionalControlRes ;
		 iso2VehicleCheckOutResType VehicleCheckOutRes ;
		 iso2VehicleCheckInResType VehicleCheckInRes ;
		 iso2PowerDemandResType PowerDemandRes ;
		 iso2PairingResType PairingRes ;
		 iso2AlignmentCheckResType AlignmentCheckRes ;
		 iso2FinePositioningResType FinePositioningRes ;
		 iso2FinePositioningSetupResType FinePositioningSetupRes ;
		 iso2WeldingDetectionResType WeldingDetectionRes ;
		 iso2CurrentDemandResType CurrentDemandRes ;
		 iso2PreChargeResType PreChargeRes ;
		 iso2CableCheckResType CableCheckRes ;
		 iso2ChargingStatusResType ChargingStatusRes ;
		 iso2CertificateInstallationResType CertificateInstallationRes ;
		 iso2CertificateUpdateResType CertificateUpdateRes ;
		 iso2SessionStopResType SessionStopRes ;
		 iso2MeteringReceiptResType MeteringReceiptRes ;
		 iso2PowerDeliveryResType PowerDeliveryRes ;
		 iso2ChargeParameterDiscoveryResType ChargeParameterDiscoveryRes ;
		 iso2AuthorizationResType AuthorizationRes ;
		 iso2PaymentDetailsResType PaymentDetailsRes ;
		 iso2PaymentServiceSelectionResType PaymentServiceSelectionRes ;
		 iso2ServiceDetailResType ServiceDetailRes ;
		 iso2ServiceDiscoveryResType ServiceDiscoveryRes ;
		 iso2SessionSetupResType SessionSetupRes ;
#if SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES
	};
#endif /* SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES */
		unsigned int BodyElement_isUsed:1;
		unsigned int V2GRequest_isUsed:1;
		unsigned int DisconnectChargingDeviceReq_isUsed:1;
		unsigned int ConnectChargingDeviceReq_isUsed:1;
		unsigned int SystemStatusReq_isUsed:1;
		unsigned int DC_BidirectionalControlReq_isUsed:1;
		unsigned int AC_BidirectionalControlReq_isUsed:1;
		unsigned int VehicleCheckOutReq_isUsed:1;
		unsigned int VehicleCheckInReq_isUsed:1;
		unsigned int PowerDemandReq_isUsed:1;
		unsigned int PairingReq_isUsed:1;
		unsigned int AlignmentCheckReq_isUsed:1;
		unsigned int FinePositioningReq_isUsed:1;
		unsigned int FinePositioningSetupReq_isUsed:1;
		unsigned int WeldingDetectionReq_isUsed:1;
		unsigned int CurrentDemandReq_isUsed:1;
		unsigned int PreChargeReq_isUsed:1;
		unsigned int CableCheckReq_isUsed:1;
		unsigned int ChargingStatusReq_isUsed:1;
		unsigned int CertificateInstallationReq_isUsed:1;
		unsigned int CertificateUpdateReq_isUsed:1;
		unsigned int SessionStopReq_isUsed:1;
		unsigned int MeteringReceiptReq_isUsed:1;
		unsigned int PowerDeliveryReq_isUsed:1;
		unsigned int ChargeParameterDiscoveryReq_isUsed:1;
		unsigned int AuthorizationReq_isUsed:1;
		unsigned int PaymentDetailsReq_isUsed:1;
		unsigned int PaymentServiceSelectionReq_isUsed:1;
		unsigned int ServiceDetailReq_isUsed:1;
		unsigned int ServiceDiscoveryReq_isUsed:1;
		unsigned int SessionSetupReq_isUsed:1;
		unsigned int V2GResponse_isUsed:1;
		unsigned int DisconnectChargingDeviceRes_isUsed:1;
		unsigned int ConnectChargingDeviceRes_isUsed:1;
		unsigned int SystemStatusRes_isUsed:1;
		unsigned int DC_BidirectionalControlRes_isUsed:1;
		unsigned int AC_BidirectionalControlRes_isUsed:1;
		unsigned int VehicleCheckOutRes_isUsed:1;
		unsigned int VehicleCheckInRes_isUsed:1;
		unsigned int PowerDemandRes_isUsed:1;
		unsigned int PairingRes_isUsed:1;
		unsigned int AlignmentCheckRes_isUsed:1;
		unsigned int FinePositioningRes_isUsed:1;
		unsigned int FinePositioningSetupRes_isUsed:1;
		unsigned int WeldingDetectionRes_isUsed:1;
		unsigned int CurrentDemandRes_isUsed:1;
		unsigned int PreChargeRes_isUsed:1;
		unsigned int CableCheckRes_isUsed:1;
		unsigned int ChargingStatusRes_isUsed:1;
		unsigned int CertificateInstallationRes_isUsed:1;
		unsigned int CertificateUpdateRes_isUsed:1;
		unsigned int SessionStopRes_isUsed:1;
		unsigned int MeteringReceiptRes_isUsed:1;
		unsigned int PowerDeliveryRes_isUsed:1;
		unsigned int ChargeParameterDiscoveryRes_isUsed:1;
		unsigned int AuthorizationRes_isUsed:1;
		unsigned int PaymentDetailsRes_isUsed:1;
		unsigned int PaymentServiceSelectionRes_isUsed:1;
		unsigned int ServiceDetailRes_isUsed:1;
		unsigned int ServiceDiscoveryRes_isUsed:1;
		unsigned int SessionSetupRes_isUsed:1;
}iso2BodyType;

/* Description: Structure to configure V2G Message */
typedef struct {
	 iso2MessageHeaderType Header ;
	 iso2BodyType Body ;
}iso2AnonType_V2G_Message;


/* Description: Structure to configure all messages */
typedef struct {
#if SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES
	union {
#endif /* SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES */
	  iso2AnonType_V2G_Message V2G_Message ;
	  iso2ServiceDiscoveryReqType ServiceDiscoveryReq ;
	  iso2ServiceDiscoveryResType ServiceDiscoveryRes ;
	  iso2FinePositioningReqType FinePositioningReq ;
	  iso2FinePositioningResType FinePositioningRes ;
	  iso2DisconnectChargingDeviceReqType DisconnectChargingDeviceReq ;
	  iso2DisconnectChargingDeviceResType DisconnectChargingDeviceRes ;
	  iso2PowerDemandReqType PowerDemandReq ;
	  iso2MeteringReceiptReqType MeteringReceiptReq ;
	  iso2PaymentDetailsReqType PaymentDetailsReq ;
	  iso2PowerDemandResType PowerDemandRes ;
	  iso2MeteringReceiptResType MeteringReceiptRes ;
	  iso2PaymentDetailsResType PaymentDetailsRes ;
	  iso2SessionSetupReqType SessionSetupReq ;
	  iso2SessionSetupResType SessionSetupRes ;
	  iso2CableCheckReqType CableCheckReq ;
	  iso2CableCheckResType CableCheckRes ;
	  iso2CertificateInstallationReqType CertificateInstallationReq ;
	  iso2CertificateInstallationResType CertificateInstallationRes ;
	  iso2SystemStatusReqType SystemStatusReq ;
	  iso2SystemStatusResType SystemStatusRes ;
	  iso2PairingReqType PairingReq ;
	  iso2WeldingDetectionReqType WeldingDetectionReq ;
	  iso2ConnectChargingDeviceReqType ConnectChargingDeviceReq ;
	  iso2PairingResType PairingRes ;
	  iso2WeldingDetectionResType WeldingDetectionRes ;
	  iso2ConnectChargingDeviceResType ConnectChargingDeviceRes ;
	  iso2CertificateUpdateReqType CertificateUpdateReq ;
	  iso2CertificateUpdateResType CertificateUpdateRes ;
	  iso2PaymentServiceSelectionReqType PaymentServiceSelectionReq ;
	  iso2PowerDeliveryReqType PowerDeliveryReq ;
	  iso2PaymentServiceSelectionResType PaymentServiceSelectionRes ;
	  iso2PowerDeliveryResType PowerDeliveryRes ;
	  iso2ChargingStatusReqType ChargingStatusReq ;
	  iso2ChargingStatusResType ChargingStatusRes ;
	  iso2BodyBaseType BodyElement ;
	  iso2AC_BidirectionalControlReqType AC_BidirectionalControlReq ;
	  iso2AC_BidirectionalControlResType AC_BidirectionalControlRes ;
	  iso2VehicleCheckInReqType VehicleCheckInReq ;
	  iso2CurrentDemandReqType CurrentDemandReq ;
	  iso2VehicleCheckInResType VehicleCheckInRes ;
	  iso2PreChargeReqType PreChargeReq ;
	  iso2CurrentDemandResType CurrentDemandRes ;
	  iso2PreChargeResType PreChargeRes ;
	  iso2AlignmentCheckReqType AlignmentCheckReq ;
	  iso2BodyBaseType V2GRequest ;
	  iso2SessionStopReqType SessionStopReq ;
	  iso2AuthorizationReqType AuthorizationReq ;
	  iso2AlignmentCheckResType AlignmentCheckRes ;
	  iso2SessionStopResType SessionStopRes ;
	  iso2AuthorizationResType AuthorizationRes ;
	  iso2VehicleCheckOutReqType VehicleCheckOutReq ;
	  iso2ChargeParameterDiscoveryReqType ChargeParameterDiscoveryReq ;
	  iso2VehicleCheckOutResType VehicleCheckOutRes ;
	  iso2ChargeParameterDiscoveryResType ChargeParameterDiscoveryRes ;
	  iso2V2GResponseType V2GResponse ;
	iso2FinePositioningSetupReqType FinePositioningSetupReq ;
	  iso2FinePositioningSetupResType FinePositioningSetupRes ;
	  iso2ServiceDetailReqType ServiceDetailReq ;
	  iso2DC_BidirectionalControlReqType DC_BidirectionalControlReq ;
	  iso2ServiceDetailResType ServiceDetailRes ;
	  iso2DC_BidirectionalControlResType DC_BidirectionalControlRes ;
	  iso2LFA_EVFinePositioningSetupParametersType LFA_EVFinePositioningSetupParameters ;
	  iso2MV_EVSEFinePositioningParametersType MV_EVSEFinePositioningParameters ;
	  iso2RelativeTimeIntervalType RelativeTimeInterval ;
	  iso2SalesTariffEntryType SalesTariffEntry ;
	  iso2LFA_EVSEFinePositioningSetupParametersType LFA_EVSEFinePositioningSetupParameters ;
	  iso2AC_EVChargeParameterType AC_EVChargeParameter ;
	  iso2MV_EVSEFinePositioningSetupParametersType MV_EVSEFinePositioningSetupParameters ;
	  iso2EVEnergyTransferParameterType EVEnergyTransferParameter ;
	  iso2DC_EVSEBidirectionalParameterType DC_EVSEBidirectionalParameter ;
	  iso2SAScheduleListType SAScheduleList ;
	  iso2EVSEFinePositioningSetupParametersType EVSEFinePositioningSetupParameters ;
	  iso2Generic_EVSEFinePositioningParametersType Generic_EVSEFinePositioningParameters ;
	  iso2DC_EVChargeParameterType DC_EVChargeParameter ;
	  iso2DC_EVSEChargeParameterType DC_EVSEChargeParameter ;
	  iso2LFA_EVFinePositioningParametersType LFA_EVFinePositioningParameters ;
	  iso2EVFinePositioningSetupParametersType EVFinePositioningSetupParameters ;
	  iso2AC_EVSEBidirectionalParameterType AC_EVSEBidirectionalParameter ;
	  iso2EVFinePositioningParametersType EVFinePositioningParameters ;
	  iso2WPT_EVChargeParameterType WPT_EVChargeParameter ;
	  iso2LFA_EVSEFinePositioningParametersType LFA_EVSEFinePositioningParameters ;
	  iso2EVSEEnergyTransferParameterType EVSEEnergyTransferParameter ;
	  iso2AC_EVBidirectionalParameterType AC_EVBidirectionalParameter ;
	  iso2EVSEFinePositioningParametersType EVSEFinePositioningParameters ;
	  iso2WPT_EVSEChargeParameterType WPT_EVSEChargeParameter ;
	  iso2AC_EVSEChargeParameterType AC_EVSEChargeParameter ;
	  iso2PMaxScheduleEntryType PMaxScheduleEntry ;
	  iso2Generic_EVFinePositioningParametersType Generic_EVFinePositioningParameters ;
	  iso2DC_EVBidirectionalParameterType DC_EVBidirectionalParameter ;
	  iso2SignaturePropertyType SignatureProperty ;
	  iso2DSAKeyValueType DSAKeyValue ;
	  iso2SignaturePropertiesType SignatureProperties ;
	  iso2KeyValueType KeyValue ;
	  iso2TransformsType Transforms ;
	  iso2DigestMethodType DigestMethod ;
	  iso2SignatureType Signature ;
	  iso2RetrievalMethodType RetrievalMethod ;
	  iso2ManifestType Manifest ;
	  iso2ReferenceType Reference ;
	  iso2CanonicalizationMethodType CanonicalizationMethod ;
	  iso2RSAKeyValueType RSAKeyValue ;
	  iso2TransformType Transform ;
	  iso2PGPDataType PGPData ;
	   struct {
		exi_string_character_t characters[iso2EXIDocument_MgmtData_CHARACTERS_SIZE];
		uint16_t charactersLen;
	  }  MgmtData ;
	 iso2SignatureMethodType SignatureMethod ;
	 iso2KeyInfoType KeyInfo ;
	 iso2SPKIDataType SPKIData ;
	 iso2X509DataType X509Data ;
	 iso2SignatureValueType SignatureValue ;
	 struct {
		exi_string_character_t characters[iso2EXIDocument_KeyName_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  KeyName ;
	 struct {
		uint8_t bytes[iso2EXIDocument_DigestValue_BYTES_SIZE];
		uint16_t bytesLen;
	}  DigestValue ;
	 iso2SignedInfoType SignedInfo ;
	 iso2ObjectType Object ;
#if SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES
	};
#endif /* SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES */
	unsigned int V2G_Message_isUsed:1;
	unsigned int ServiceDiscoveryReq_isUsed:1;
	unsigned int ServiceDiscoveryRes_isUsed:1;
	unsigned int FinePositioningReq_isUsed:1;
	unsigned int FinePositioningRes_isUsed:1;
	unsigned int DisconnectChargingDeviceReq_isUsed:1;
	unsigned int DisconnectChargingDeviceRes_isUsed:1;
	unsigned int PowerDemandReq_isUsed:1;
	unsigned int MeteringReceiptReq_isUsed:1;
	unsigned int PaymentDetailsReq_isUsed:1;
	unsigned int PowerDemandRes_isUsed:1;
	unsigned int MeteringReceiptRes_isUsed:1;
	unsigned int PaymentDetailsRes_isUsed:1;
	unsigned int SessionSetupReq_isUsed:1;
	unsigned int SessionSetupRes_isUsed:1;
	unsigned int CableCheckReq_isUsed:1;
	unsigned int CableCheckRes_isUsed:1;
	unsigned int CertificateInstallationReq_isUsed:1;
	unsigned int CertificateInstallationRes_isUsed:1;
	unsigned int SystemStatusReq_isUsed:1;
	unsigned int SystemStatusRes_isUsed:1;
	unsigned int PairingReq_isUsed:1;
	unsigned int WeldingDetectionReq_isUsed:1;
	unsigned int ConnectChargingDeviceReq_isUsed:1;
	unsigned int PairingRes_isUsed:1;
	unsigned int WeldingDetectionRes_isUsed:1;
	unsigned int ConnectChargingDeviceRes_isUsed:1;
	unsigned int CertificateUpdateReq_isUsed:1;
	unsigned int CertificateUpdateRes_isUsed:1;
	unsigned int PaymentServiceSelectionReq_isUsed:1;
	unsigned int PowerDeliveryReq_isUsed:1;
	unsigned int PaymentServiceSelectionRes_isUsed:1;
	unsigned int PowerDeliveryRes_isUsed:1;
	unsigned int ChargingStatusReq_isUsed:1;
	unsigned int ChargingStatusRes_isUsed:1;
	unsigned int BodyElement_isUsed:1;
	unsigned int AC_BidirectionalControlReq_isUsed:1;
	unsigned int AC_BidirectionalControlRes_isUsed:1;
	unsigned int VehicleCheckInReq_isUsed:1;
	unsigned int CurrentDemandReq_isUsed:1;
	unsigned int VehicleCheckInRes_isUsed:1;
	unsigned int PreChargeReq_isUsed:1;
	unsigned int CurrentDemandRes_isUsed:1;
	unsigned int PreChargeRes_isUsed:1;
	unsigned int AlignmentCheckReq_isUsed:1;
	unsigned int V2GRequest_isUsed:1;
	unsigned int SessionStopReq_isUsed:1;
	unsigned int AuthorizationReq_isUsed:1;
	unsigned int AlignmentCheckRes_isUsed:1;
	unsigned int SessionStopRes_isUsed:1;
	unsigned int AuthorizationRes_isUsed:1;
	unsigned int VehicleCheckOutReq_isUsed:1;
	unsigned int ChargeParameterDiscoveryReq_isUsed:1;
	unsigned int VehicleCheckOutRes_isUsed:1;
	unsigned int ChargeParameterDiscoveryRes_isUsed:1;
	unsigned int V2GResponse_isUsed:1;
	unsigned int FinePositioningSetupReq_isUsed:1;
	unsigned int FinePositioningSetupRes_isUsed:1;
	unsigned int ServiceDetailReq_isUsed:1;
	unsigned int DC_BidirectionalControlReq_isUsed:1;
	unsigned int ServiceDetailRes_isUsed:1;
	unsigned int DC_BidirectionalControlRes_isUsed:1;
	unsigned int LFA_EVFinePositioningSetupParameters_isUsed:1;
	unsigned int MV_EVSEFinePositioningParameters_isUsed:1;
	unsigned int RelativeTimeInterval_isUsed:1;
	unsigned int SalesTariffEntry_isUsed:1;
	unsigned int LFA_EVSEFinePositioningSetupParameters_isUsed:1;
	unsigned int AC_EVChargeParameter_isUsed:1;
	unsigned int MV_EVSEFinePositioningSetupParameters_isUsed:1;
	unsigned int EVEnergyTransferParameter_isUsed:1;
	unsigned int DC_EVSEBidirectionalParameter_isUsed:1;
	unsigned int SAScheduleList_isUsed:1;
	unsigned int EVSEFinePositioningSetupParameters_isUsed:1;
	unsigned int Generic_EVSEFinePositioningParameters_isUsed:1;
	unsigned int DC_EVChargeParameter_isUsed:1;
	unsigned int DC_EVSEChargeParameter_isUsed:1;
	unsigned int LFA_EVFinePositioningParameters_isUsed:1;
	unsigned int EVFinePositioningSetupParameters_isUsed:1;
	unsigned int AC_EVSEBidirectionalParameter_isUsed:1;
	unsigned int EVFinePositioningParameters_isUsed:1;
	unsigned int WPT_EVChargeParameter_isUsed:1;
	unsigned int LFA_EVSEFinePositioningParameters_isUsed:1;
	unsigned int EVSEEnergyTransferParameter_isUsed:1;
	unsigned int AC_EVBidirectionalParameter_isUsed:1;
	unsigned int EVSEFinePositioningParameters_isUsed:1;
	unsigned int WPT_EVSEChargeParameter_isUsed:1;
	unsigned int AC_EVSEChargeParameter_isUsed:1;
	unsigned int PMaxScheduleEntry_isUsed:1;
	unsigned int Generic_EVFinePositioningParameters_isUsed:1;
	unsigned int DC_EVBidirectionalParameter_isUsed:1;
	unsigned int SignatureProperty_isUsed:1;
	unsigned int DSAKeyValue_isUsed:1;
	unsigned int SignatureProperties_isUsed:1;
	unsigned int KeyValue_isUsed:1;
	unsigned int Transforms_isUsed:1;
	unsigned int DigestMethod_isUsed:1;
	unsigned int Signature_isUsed:1;
	unsigned int RetrievalMethod_isUsed:1;
	unsigned int Manifest_isUsed:1;
	unsigned int Reference_isUsed:1;
	unsigned int CanonicalizationMethod_isUsed:1;
	unsigned int RSAKeyValue_isUsed:1;
	unsigned int Transform_isUsed:1;
	unsigned int PGPData_isUsed:1;
	unsigned int MgmtData_isUsed:1;
	unsigned int SignatureMethod_isUsed:1;
	unsigned int KeyInfo_isUsed:1;
	unsigned int SPKIData_isUsed:1;
	unsigned int X509Data_isUsed:1;
	unsigned int SignatureValue_isUsed:1;
	unsigned int KeyName_isUsed:1;
	unsigned int DigestValue_isUsed:1;
	unsigned int SignedInfo_isUsed:1;
	unsigned int Object_isUsed:1;


	int _warning_;
}iso2EXIDocument;


#if DEPLOY_ISO2_CODEC_FRAGMENT == SUPPORT_YES
typedef struct {
#if SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES
	union {
#endif /* SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES */
	 iso2PhysicalValueType EVMaximumVoltage ;
	uint32_t FrequencyChannel ;
	iso2EVSEProcessingType EVProcessing ;
	int BulkChargingComplete ;
	iso2parkingMethodType ParkingMethod ;
	uint8_t SAScheduleTupleID ;
	uint16_t Distance ;
	 iso2ParameterSetType ParameterSet ;
	 iso2PhysicalValueType EVMinimumDischargeCurrent ;
	uint8_t SignalSeparationTime ;
	 iso2EVSEEnergyTransferParameterType EVSEEnergyTransferParameter ;
	 iso2PhysicalValueType EVSEMaximumVoltage ;
	 iso2DC_EVSEBidirectionalParameterType DC_EVSEBidirectionalParameter ;
	iso2chargingSessionType ChargingSession ;
	 iso2SubCertificatesType SubCertificates ;
	 iso2RetrievalMethodType RetrievalMethod ;
	 iso2MagneticVectorSetupListType MagneticVectorSetupList ;
	 iso2ParameterSetType PairingParameters ;
	 iso2PhysicalValueType EVSEMinimumPower ;
	 iso2AC_BidirectionalControlReqType AC_BidirectionalControlReq ;
	 iso2CostType Cost ;
	 iso2AC_BidirectionalControlResType AC_BidirectionalControlRes ;
	 iso2SalesTariffType BuyBackTariff ;
	int16_t XCoordinate ;
	iso2EVCheckOutStatusType EVSECheckOutStatus ;
	 struct {
		exi_string_character_t characters[iso2EXIFragment_stringValue_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  stringValue ;
	int16_t RetryCounter ;
	 iso2PhysicalValueType EVSEMaximumDischargeCurrent ;
	 iso2SensorType Sensor ;
	uint64_t MeterReadingCharged ;
	int64_t HMACOutputLength ;
	 iso2V2GResponseType V2GResponse ;
	 iso2PhysicalValueType EVMinimumVoltage ;
	 iso2PhysicalValueType EVMinimumEnergyRequest ;
	 iso2RelativeTimeIntervalType RelativeTimeInterval ;
	 iso2WPT_EVChargeParameterType WPT_EVChargeParameter ;
	 iso2SAScheduleTupleType SAScheduleTuple ;
	uint16_t ServiceID ;
	 struct {
		uint8_t bytes[iso2EXIFragment_PgenCounter_BYTES_SIZE];
		uint16_t bytesLen;
	}  PgenCounter ;
	 struct {
		exi_string_character_t characters[iso2EXIFragment_SalesTariffDescription_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  SalesTariffDescription ;
	 iso2PhysicalValueType AngleGAtoVA ;
	int boolValue ;
	 iso2PhysicalValueType EVMaximumDischargeCurrent ;
	uint16_t NotificationMaxDelay ;
	 iso2PhysicalValueType EVSEMaximumDischargePower ;
	 iso2PGPDataType PGPData ;
	 iso2PhysicalValueType EVSEMaximumChargePower ;
	 struct {
		uint8_t bytes[iso2EXIFragment_SessionID_BYTES_SIZE];
		uint16_t bytesLen;
	}  SessionID ;
	 iso2PhysicalValueType EVSEEnergyToBeDelivered ;
	 iso2PhysicalValueType EVMaximumPower ;
	 iso2PhysicalValueType EVMaximumCurrent ;
	 iso2RSAKeyValueType RSAKeyValue ;
	 iso2PhysicalValueType EVSENominalVoltage ;
	 iso2MagneticVectorType MagneticVector ;
	 struct {
		exi_string_character_t characters[iso2EXIFragment_XPath_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  XPath ;
	 iso2SignatureType Signature ;
	iso2electricalChargingDeviceStatusType EVElectricalChargingDeviceStatus ;
	iso2EVSEProcessingType EVSEProcessing ;
	iso2FODStatusType FODStatus ;
	 iso2PowerDeliveryResType PowerDeliveryRes ;
	 iso2SessionStopResType SessionStopRes ;
	 iso2WPT_EVSEChargeParameterType WPT_EVSEChargeParameter ;
	iso2responseCodeType ResponseCode ;
	 iso2PhysicalValueType EVTargetEnergyRequest ;
	 iso2FinePositioningSetupReqType FinePositioningSetupReq ;
	 iso2PhysicalValueType EVSEPresentCurrent ;
	 iso2FinePositioningSetupResType FinePositioningSetupRes ;
	 iso2PMaxScheduleEntryType ProfileEntry ;
	 struct {
		exi_string_character_t characters[iso2EXIFragment_MgmtData_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  MgmtData ;
	 iso2CertificateChainType SAProvisioningCertificateChain ;
	 iso2PowerDeliveryReqType PowerDeliveryReq ;
	 iso2SessionStopReqType SessionStopReq ;
	int ReceiptRequired ;
	 iso2ChargingProfileType ChargingProfile ;
	uint16_t MaxSupportingPoints ;
	uint32_t start ;
	 iso2PhysicalValueType EVMinimumChargePower ;
	 iso2PhysicalValueType amount ;
	 iso2PreChargeReqType PreChargeReq ;
	 struct {
		uint8_t bytes[iso2EXIFragment_OEMProvisioningCert_BYTES_SIZE];
		uint16_t bytesLen;
	}  OEMProvisioningCert ;
	uint32_t PackageIndex ;
	 iso2PreChargeResType PreChargeRes ;
	 struct {
		uint8_t bytes[iso2EXIFragment_P_BYTES_SIZE];
		uint16_t bytesLen;
	}  P ;
	 struct {
		uint8_t bytes[iso2EXIFragment_Q_BYTES_SIZE];
		uint16_t bytesLen;
	}  Q ;
	 struct {
		exi_string_character_t characters[iso2EXIFragment_X509SubjectName_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  X509SubjectName ;
	 struct {
		uint8_t bytes[iso2EXIFragment_G_BYTES_SIZE];
		uint16_t bytesLen;
	}  G ;
	 struct {
		uint8_t bytes[iso2EXIFragment_J_BYTES_SIZE];
		uint16_t bytesLen;
	}  J ;
	 iso2CertificateChainType ContractSignatureCertChain ;
	 iso2MV_EVSEFinePositioningSetupParametersType MV_EVSEFinePositioningSetupParameters ;
	 iso2PhysicalValueType EVSEMinimumDischargeCurrent ;
	 iso2PhysicalValueType EVMaximumChargeCurrent ;
	uint16_t AlignmentOffset ;
	 struct {
		uint8_t bytes[iso2EXIFragment_Y_BYTES_SIZE];
		uint16_t bytesLen;
	}  Y ;
	int8_t RemainingTimeToTargetSOC ;
	 struct {
		uint8_t bytes[iso2EXIFragment_DigestValue_BYTES_SIZE];
		uint16_t bytesLen;
	}  DigestValue ;
	 iso2SensorMeasurementsType SensorMeasurements ;
	 iso2SalesTariffType SalesTariff ;
	 struct {
		uint8_t bytes[iso2EXIFragment_EVCCID_BYTES_SIZE];
		uint16_t bytesLen;
	}  EVCCID ;
	 iso2PhysicalValueType EVSEMaximumPower ;
	 iso2TargetPositionType TargetOffset ;
	 iso2ParameterSetType PowerDemandParameters ;
	 struct {
		uint8_t bytes[iso2EXIFragment_PGPKeyID_BYTES_SIZE];
		uint16_t bytesLen;
	}  PGPKeyID ;
	 iso2DisconnectChargingDeviceReqType DisconnectChargingDeviceReq ;
	 iso2DisconnectChargingDeviceResType DisconnectChargingDeviceRes ;
	 iso2DSAKeyValueType DSAKeyValue ;
	 iso2SalesTariffEntryType SalesTariffEntry ;
	 iso2CertificateInstallationResType CertificateInstallationRes ;
	 iso2CanonicalizationMethodType CanonicalizationMethod ;
	 iso2Generic_EVFinePositioningParametersType Generic_EVFinePositioningParameters ;
	 iso2PhysicalValueType EVSEMinimumVoltage ;
	 iso2SystemStatusResType SystemStatusRes ;
	 iso2PhysicalValueType EVSEOutputPower ;
	 iso2SignedInfoType SignedInfo ;
	 iso2PhysicalValueType EVMinimumChargeCurrent ;
	iso2costKindType costKind ;
	 iso2SystemStatusReqType SystemStatusReq ;
	 iso2CableCheckReqType CableCheckReq ;
	uint8_t NumEPriceLevels ;
	int EVSEVoltageLimitAchieved ;
	uint8_t PackageSeparationTime ;
	 iso2CableCheckResType CableCheckRes ;
	iso2EVCheckInStatusType EVCheckInStatus ;
	 iso2PMaxScheduleType PMaxDischargeSchedule ;
	 iso2PhysicalValueType EVMinimumPower ;
	 iso2PhysicalValueType ChargingPerformance ;
	 iso2AlignmentCheckReqType AlignmentCheckReq ;
	iso2mechanicalChargingDeviceStatusType EVMechanicalChargingDeviceStatus ;
	uint16_t VehicleSpace ;
	 iso2AlignmentCheckResType AlignmentCheckRes ;
	 iso2PhysicalValueType EVMinimumDischargePower ;
	int8_t RemainingTimeToMinimumSOC ;
	 iso2AuthorizationResType AuthorizationRes ;
	 iso2CertificateInstallationReqType CertificateInstallationReq ;
	 iso2PaymentDetailsReqType PaymentDetailsReq ;
	 iso2PaymentDetailsResType PaymentDetailsRes ;
	 iso2AuthorizationReqType AuthorizationReq ;
	 iso2PhysicalValueType EVTargetCurrent ;
	 iso2SessionSetupReqType SessionSetupReq ;
	 iso2SessionSetupResType SessionSetupRes ;
	 iso2PhysicalValueType EVSENominalFrequency ;
	 iso2MessageHeaderType Header ;
	uint8_t NumberOfSensors ;
	int64_t EVSETimeStamp ;
	int16_t MeterStatus ;
	 iso2MV_EVSEFinePositioningParametersType MV_EVSEFinePositioningParameters ;
	iso2chargeProgressType ChargeProgress ;
	 struct {
		exi_string_character_t characters[iso2EXIFragment_KeyName_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  KeyName ;
	 iso2PMaxScheduleType PMaxSchedule ;
	uint32_t duration ;
	int8_t RemainingTimeToBulkSOC ;
	 iso2CartesianCoordinatesType SensorOrientation ;
	 iso2PhysicalValueType EVSEMaximumChargeCurrent ;
	 iso2LFA_EVSEFinePositioningParametersType LFA_EVSEFinePositioningParameters ;
	 iso2VehicleCheckInResType VehicleCheckInRes ;
	 iso2PMaxScheduleEntryType PMaxScheduleEntry ;
	 iso2SAScheduleListType SAScheduleList ;
	 struct {
		uint8_t bytes[iso2EXIFragment_X509SKI_BYTES_SIZE];
		uint16_t bytesLen;
	}  X509SKI ;
	 iso2PaymentOptionListType PaymentOptionList ;
	 iso2ContractSignatureEncryptedPrivateKeyType ContractSignatureEncryptedPrivateKey ;
	 iso2VehicleCheckInReqType VehicleCheckInReq ;
	 struct {
		uint8_t bytes[iso2EXIFragment_Certificate_BYTES_SIZE];
		uint16_t bytesLen;
	}  Certificate ;
	uint64_t CheckOutTime ;
	int8_t CurrentSOC ;
	int16_t ZCoordinate ;
	uint16_t MeasurementData ;
	 iso2PairingResType PairingRes ;
	 iso2PhysicalValueType EVSEMaximumCurrent ;
	 iso2LFA_EVFinePositioningParametersType LFA_EVFinePositioningParameters ;
	 iso2ParameterSetType AlignmentCheckParameters ;
	int8_t EffectiveRadiatedPower ;
	 iso2PairingReqType PairingReq ;
	int16_t Value ;
	int8_t byteValue ;
	 iso2CurrentDemandReqType CurrentDemandReq ;
	 iso2Generic_EVSEFinePositioningParametersType Generic_EVSEFinePositioningParameters ;
	 iso2CurrentDemandResType CurrentDemandRes ;
	 iso2AC_EVBidirectionalParameterType AC_EVBidirectionalParameter ;
	 struct {
		uint8_t bytes[iso2EXIFragment_Modulus_BYTES_SIZE];
		uint16_t bytesLen;
	}  Modulus ;
	 iso2SelectedServiceType SelectedEnergyTransferService ;
	 iso2PhysicalValueType startValue ;
	 iso2SelectedServiceListType SelectedVASList ;
	 iso2ChargeParameterDiscoveryReqType ChargeParameterDiscoveryReq ;
	 iso2ChargeParameterDiscoveryResType ChargeParameterDiscoveryRes ;
	 struct {
		uint8_t bytes[iso2EXIFragment_SigMeterReading_BYTES_SIZE];
		uint16_t bytesLen;
	}  SigMeterReading ;
	int8_t TargetSOC ;
	 iso2EVSEStatusType EVSEStatus ;
	 iso2PhysicalValueType EVSEMinimumChargeCurrent ;
	iso2electricalChargingDeviceStatusType EVSEElectricalChargingDeviceStatus ;
	int64_t X509SerialNumber ;
	iso2paymentOptionType PaymentOption ;
	 iso2TransformsType Transforms ;
	 iso2PhysicalValueType EVSEPeakCurrentRipple ;
	 iso2ConsumptionCostType ConsumptionCost ;
	 iso2EVSEFinePositioningSetupParametersType EVSEFinePositioningSetupParameters ;
	uint8_t EPriceLevel ;
	 struct {
		uint8_t bytes[iso2EXIFragment_Exponent_BYTES_SIZE];
		uint16_t bytesLen;
	}  Exponent ;
	 iso2X509IssuerSerialType X509IssuerSerial ;
	 iso2SPKIDataType SPKIData ;
	 iso2MagneticVectorListType MagneticVectorList ;
	 iso2EVSEFinePositioningParametersType EVSEFinePositioningParameters ;
	 iso2PhysicalValueType EVTargetPower ;
	 iso2SensorPackageListType SensorPackageList ;
	uint32_t DepartureTime ;
	int InletHot ;
	 iso2PhysicalValueType EVPresentActivePower ;
	 iso2X509DataType X509Data ;
	int16_t YCoordinate ;
	 iso2KeyValueType KeyValue ;
	 iso2DisplayParametersType DisplayParameters ;
	int EVSEPowerLimitAchieved ;
	 iso2BodyType Body ;
	 iso2DC_EVChargeParameterType DC_EVChargeParameter ;
	 iso2ServiceType Service ;
	 iso2SignaturePropertyType SignatureProperty ;
	 struct {
		uint8_t bytes[iso2EXIFragment_PGPKeyPacket_BYTES_SIZE];
		uint16_t bytesLen;
	}  PGPKeyPacket ;
	 struct {
		uint8_t bytes[iso2EXIFragment_Seed_BYTES_SIZE];
		uint16_t bytesLen;
	}  Seed ;
	 iso2LFA_EVFinePositioningSetupParametersType LFA_EVFinePositioningSetupParameters ;
	 iso2MinimumPMaxRequestType MinimumPMaxRequest ;
	 iso2FinePositioningReqType FinePositioningReq ;
	 iso2ServiceListType EnergyTransferServiceList ;
	 iso2FinePositioningResType FinePositioningRes ;
	 iso2AC_EVSEBidirectionalParameterType AC_EVSEBidirectionalParameter ;
	int FreeService ;
	 iso2AC_EVSEChargeParameterType AC_EVSEChargeParameter ;
	uint8_t SensorID ;
	 iso2PhysicalValueType EVSECurrentRegulationTolerance ;
	iso2mechanicalChargingDeviceStatusType EVSEMechanicalChargingDeviceStatus ;
	 iso2EVEnergyTransferParameterType EVEnergyTransferParameter ;
	uint8_t SignalPulseDuration ;
	int16_t shortValue ;
	 iso2ManifestType Manifest ;
	 iso2DC_EVSEChargeParameterType DC_EVSEChargeParameter ;
	 iso2MeteringReceiptReqType MeteringReceiptReq ;
	 struct {
		exi_string_character_t characters[iso2EXIFragment_MeterID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  MeterID ;
	 iso2MeteringReceiptResType MeteringReceiptRes ;
	 iso2ServiceDiscoveryReqType ServiceDiscoveryReq ;
	uint8_t SalesTariffID ;
	 iso2ServiceDiscoveryResType ServiceDiscoveryRes ;
	 struct {
		uint8_t bytes[iso2EXIFragment_X509CRL_BYTES_SIZE];
		uint16_t bytesLen;
	}  X509CRL ;
	 iso2MagneticVectorSetupType MagneticVectorSetup ;
	 iso2DigestMethodType DigestMethod ;
	 struct {
		uint8_t bytes[iso2EXIFragment_SPKISexp_BYTES_SIZE];
		uint16_t bytesLen;
	}  SPKISexp ;
	uint64_t MeterReadingDischarged ;
	 iso2MeasurementDataListType MeasurementDataList ;
	 iso2SignaturePropertiesType SignatureProperties ;
	 iso2CartesianCoordinatesType SensorPosition ;
	 iso2LFA_EVSEFinePositioningSetupParametersType LFA_EVSEFinePositioningSetupParameters ;
	 iso2EMAIDType eMAID ;
	 iso2SensorPackageType SensorPackage ;
	iso2EVCheckOutStatusType EVCheckOutStatus ;
	 struct {
		uint8_t bytes[iso2EXIFragment_X509Certificate_BYTES_SIZE];
		uint16_t bytesLen;
	}  X509Certificate ;
	 iso2X509IssuerSerialType RootCertificateID ;
	 iso2DC_BidirectionalControlReqType DC_BidirectionalControlReq ;
	 iso2PhysicalValueType EVSEPresentVoltage ;
	 iso2DC_BidirectionalControlResType DC_BidirectionalControlRes ;
	 iso2ServiceListType VASList ;
	 iso2MeterInfoType MeterInfo ;
	 iso2PhysicalValueType EVSETargetReactivePower ;
	 iso2ChargingStatusReqType ChargingStatusReq ;
	 iso2ParameterSetType GenericParameters ;
	 iso2ChargingStatusResType ChargingStatusRes ;
	 iso2PhysicalValueType EVMaximumChargePower ;
	int8_t BulkSOC ;
	uint8_t NumberOfSignalPackages ;
	uint16_t ParameterSetID ;
	 iso2PhysicalValueType PMax ;
	 iso2PhysicalValueType EVMaximumEnergyRequest ;
	iso2EVOperationType EVOperation ;
	 iso2CertificateUpdateResType CertificateUpdateRes ;
	int ChargingComplete ;
	 iso2ListOfRootCertificateIDsType ListOfRootCertificateIDs ;
	 iso2PhysicalValueType RotationVAtoGA ;
	 iso2PhysicalValueType EVTargetVoltage ;
	 iso2CertificateUpdateReqType CertificateUpdateReq ;
	 iso2ConnectChargingDeviceResType ConnectChargingDeviceRes ;
	 iso2DiffieHellmanPublickeyType DHpublickey ;
	 iso2ServiceParameterListType ServiceParameterList ;
	 iso2SignatureValueType SignatureValue ;
	 iso2PhysicalValueType physicalValue ;
	iso2operationModeType OperationMode ;
	int EVSECurrentLimitAchieved ;
	 iso2ServiceDetailReqType ServiceDetailReq ;
	 iso2ServiceDetailResType ServiceDetailRes ;
	int32_t intValue ;
	 iso2PhysicalValueType EVMaximumDischargePower ;
	int8_t MinimumSOC ;
	iso2paymentOptionType SelectedPaymentOption ;
	 iso2AnonType_V2G_Message V2G_Message ;
	 struct {
		exi_string_character_t characters[iso2EXIFragment_EVSEID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  EVSEID ;
	int64_t TMeter ;
	 iso2SensorOrderListType SensorOrder ;
	 iso2ServiceIDListType SupportedServiceIDs ;
	 struct {
		uint8_t bytes[iso2EXIFragment_GenChallenge_BYTES_SIZE];
		uint16_t bytesLen;
	}  GenChallenge ;
	 iso2EVFinePositioningParametersType EVFinePositioningParameters ;
	 iso2SensorListType SensorList ;
	 iso2KeyInfoType KeyInfo ;
	 iso2ConnectChargingDeviceReqType ConnectChargingDeviceReq ;
	 iso2AC_EVChargeParameterType AC_EVChargeParameter ;
	 iso2ParameterType Parameter ;
	 iso2WeldingDetectionResType WeldingDetectionRes ;
	 struct {
		exi_string_character_t characters[iso2EXIFragment_GAID_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  GAID ;
	uint16_t SignalFrequency ;
	 iso2PhysicalValueType EVSETargetPower ;
	 iso2DC_EVBidirectionalParameterType DC_EVBidirectionalParameter ;
	 iso2SignatureMethodType SignatureMethod ;
	 iso2WeldingDetectionReqType WeldingDetectionReq ;
	 iso2SelectedServiceType SelectedService ;
	 iso2PhysicalValueType EVInputPower ;
	 iso2VehicleCheckOutReqType VehicleCheckOutReq ;
	 iso2PowerDemandReqType PowerDemandReq ;
	 iso2VehicleCheckOutResType VehicleCheckOutRes ;
	uint16_t CurrentRange ;
	 iso2PhysicalValueType EVPresentReactivePower ;
	 struct {
		exi_string_character_t characters[iso2EXIFragment_X509IssuerName_CHARACTERS_SIZE];
		uint16_t charactersLen;
	}  X509IssuerName ;
	 iso2BodyBaseType V2GRequest ;
	 iso2ReferenceType Reference ;
	 iso2BodyBaseType BodyElement ;
	 iso2PMaxScheduleEntryType MinimumPMaxScheduleEntry ;
	 iso2EVFinePositioningSetupParametersType EVFinePositioningSetupParameters ;
	iso2EVSENotificationType EVSENotification ;
	 iso2PaymentServiceSelectionReqType PaymentServiceSelectionReq ;
	 iso2PaymentServiceSelectionResType PaymentServiceSelectionRes ;
	 iso2TransformType Transform ;
	 iso2ObjectType Object ;
	uint16_t TargetOffsetY ;
	 iso2PowerDemandResType PowerDemandRes ;
	uint16_t TargetOffsetX ;
#if SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES
	};
#endif /* SAVE_MEMORY_WITH_UNNAMED_UNION == UNION_YES */
	unsigned int EVMaximumVoltage_isUsed:1;
	unsigned int FrequencyChannel_isUsed:1;
	unsigned int EVProcessing_isUsed:1;
	unsigned int BulkChargingComplete_isUsed:1;
	unsigned int ParkingMethod_isUsed:1;
	unsigned int SAScheduleTupleID_isUsed:1;
	unsigned int Distance_isUsed:1;
	unsigned int ParameterSet_isUsed:1;
	unsigned int EVMinimumDischargeCurrent_isUsed:1;
	unsigned int SignalSeparationTime_isUsed:1;
	unsigned int EVSEEnergyTransferParameter_isUsed:1;
	unsigned int EVSEMaximumVoltage_isUsed:1;
	unsigned int DC_EVSEBidirectionalParameter_isUsed:1;
	unsigned int ChargingSession_isUsed:1;
	unsigned int SubCertificates_isUsed:1;
	unsigned int RetrievalMethod_isUsed:1;
	unsigned int MagneticVectorSetupList_isUsed:1;
	unsigned int PairingParameters_isUsed:1;
	unsigned int EVSEMinimumPower_isUsed:1;
	unsigned int AC_BidirectionalControlReq_isUsed:1;
	unsigned int Cost_isUsed:1;
	unsigned int AC_BidirectionalControlRes_isUsed:1;
	unsigned int BuyBackTariff_isUsed:1;
	unsigned int XCoordinate_isUsed:1;
	unsigned int EVSECheckOutStatus_isUsed:1;
	unsigned int stringValue_isUsed:1;
	unsigned int RetryCounter_isUsed:1;
	unsigned int EVSEMaximumDischargeCurrent_isUsed:1;
	unsigned int Sensor_isUsed:1;
	unsigned int MeterReadingCharged_isUsed:1;
	unsigned int HMACOutputLength_isUsed:1;
	unsigned int V2GResponse_isUsed:1;
	unsigned int EVMinimumVoltage_isUsed:1;
	unsigned int EVMinimumEnergyRequest_isUsed:1;
	unsigned int RelativeTimeInterval_isUsed:1;
	unsigned int WPT_EVChargeParameter_isUsed:1;
	unsigned int SAScheduleTuple_isUsed:1;
	unsigned int ServiceID_isUsed:1;
	unsigned int PgenCounter_isUsed:1;
	unsigned int SalesTariffDescription_isUsed:1;
	unsigned int AngleGAtoVA_isUsed:1;
	unsigned int boolValue_isUsed:1;
	unsigned int EVMaximumDischargeCurrent_isUsed:1;
	unsigned int NotificationMaxDelay_isUsed:1;
	unsigned int EVSEMaximumDischargePower_isUsed:1;
	unsigned int PGPData_isUsed:1;
	unsigned int EVSEMaximumChargePower_isUsed:1;
	unsigned int SessionID_isUsed:1;
	unsigned int EVSEEnergyToBeDelivered_isUsed:1;
	unsigned int EVMaximumPower_isUsed:1;
	unsigned int EVMaximumCurrent_isUsed:1;
	unsigned int RSAKeyValue_isUsed:1;
	unsigned int EVSENominalVoltage_isUsed:1;
	unsigned int MagneticVector_isUsed:1;
	unsigned int XPath_isUsed:1;
	unsigned int Signature_isUsed:1;
	unsigned int EVElectricalChargingDeviceStatus_isUsed:1;
	unsigned int EVSEProcessing_isUsed:1;
	unsigned int FODStatus_isUsed:1;
	unsigned int PowerDeliveryRes_isUsed:1;
	unsigned int SessionStopRes_isUsed:1;
	unsigned int WPT_EVSEChargeParameter_isUsed:1;
	unsigned int ResponseCode_isUsed:1;
	unsigned int EVTargetEnergyRequest_isUsed:1;
	unsigned int FinePositioningSetupReq_isUsed:1;
	unsigned int EVSEPresentCurrent_isUsed:1;
	unsigned int FinePositioningSetupRes_isUsed:1;
	unsigned int ProfileEntry_isUsed:1;
	unsigned int MgmtData_isUsed:1;
	unsigned int SAProvisioningCertificateChain_isUsed:1;
	unsigned int PowerDeliveryReq_isUsed:1;
	unsigned int SessionStopReq_isUsed:1;
	unsigned int ReceiptRequired_isUsed:1;
	unsigned int ChargingProfile_isUsed:1;
	unsigned int MaxSupportingPoints_isUsed:1;
	unsigned int start_isUsed:1;
	unsigned int EVMinimumChargePower_isUsed:1;
	unsigned int amount_isUsed:1;
	unsigned int PreChargeReq_isUsed:1;
	unsigned int OEMProvisioningCert_isUsed:1;
	unsigned int PackageIndex_isUsed:1;
	unsigned int PreChargeRes_isUsed:1;
	unsigned int P_isUsed:1;
	unsigned int Q_isUsed:1;
	unsigned int X509SubjectName_isUsed:1;
	unsigned int G_isUsed:1;
	unsigned int J_isUsed:1;
	unsigned int ContractSignatureCertChain_isUsed:1;
	unsigned int MV_EVSEFinePositioningSetupParameters_isUsed:1;
	unsigned int EVSEMinimumDischargeCurrent_isUsed:1;
	unsigned int EVMaximumChargeCurrent_isUsed:1;
	unsigned int AlignmentOffset_isUsed:1;
	unsigned int Y_isUsed:1;
	unsigned int RemainingTimeToTargetSOC_isUsed:1;
	unsigned int DigestValue_isUsed:1;
	unsigned int SensorMeasurements_isUsed:1;
	unsigned int SalesTariff_isUsed:1;
	unsigned int EVCCID_isUsed:1;
	unsigned int EVSEMaximumPower_isUsed:1;
	unsigned int TargetOffset_isUsed:1;
	unsigned int PowerDemandParameters_isUsed:1;
	unsigned int PGPKeyID_isUsed:1;
	unsigned int DisconnectChargingDeviceReq_isUsed:1;
	unsigned int DisconnectChargingDeviceRes_isUsed:1;
	unsigned int DSAKeyValue_isUsed:1;
	unsigned int SalesTariffEntry_isUsed:1;
	unsigned int CertificateInstallationRes_isUsed:1;
	unsigned int CanonicalizationMethod_isUsed:1;
	unsigned int Generic_EVFinePositioningParameters_isUsed:1;
	unsigned int EVSEMinimumVoltage_isUsed:1;
	unsigned int SystemStatusRes_isUsed:1;
	unsigned int EVSEOutputPower_isUsed:1;
	unsigned int SignedInfo_isUsed:1;
	unsigned int EVMinimumChargeCurrent_isUsed:1;
	unsigned int costKind_isUsed:1;
	unsigned int SystemStatusReq_isUsed:1;
	unsigned int CableCheckReq_isUsed:1;
	unsigned int NumEPriceLevels_isUsed:1;
	unsigned int EVSEVoltageLimitAchieved_isUsed:1;
	unsigned int PackageSeparationTime_isUsed:1;
	unsigned int CableCheckRes_isUsed:1;
	unsigned int EVCheckInStatus_isUsed:1;
	unsigned int PMaxDischargeSchedule_isUsed:1;
	unsigned int EVMinimumPower_isUsed:1;
	unsigned int ChargingPerformance_isUsed:1;
	unsigned int AlignmentCheckReq_isUsed:1;
	unsigned int EVMechanicalChargingDeviceStatus_isUsed:1;
	unsigned int VehicleSpace_isUsed:1;
	unsigned int AlignmentCheckRes_isUsed:1;
	unsigned int EVMinimumDischargePower_isUsed:1;
	unsigned int RemainingTimeToMinimumSOC_isUsed:1;
	unsigned int AuthorizationRes_isUsed:1;
	unsigned int CertificateInstallationReq_isUsed:1;
	unsigned int PaymentDetailsReq_isUsed:1;
	unsigned int PaymentDetailsRes_isUsed:1;
	unsigned int AuthorizationReq_isUsed:1;
	unsigned int EVTargetCurrent_isUsed:1;
	unsigned int SessionSetupReq_isUsed:1;
	unsigned int SessionSetupRes_isUsed:1;
	unsigned int EVSENominalFrequency_isUsed:1;
	unsigned int Header_isUsed:1;
	unsigned int NumberOfSensors_isUsed:1;
	unsigned int EVSETimeStamp_isUsed:1;
	unsigned int MeterStatus_isUsed:1;
	unsigned int MV_EVSEFinePositioningParameters_isUsed:1;
	unsigned int ChargeProgress_isUsed:1;
	unsigned int KeyName_isUsed:1;
	unsigned int PMaxSchedule_isUsed:1;
	unsigned int duration_isUsed:1;
	unsigned int RemainingTimeToBulkSOC_isUsed:1;
	unsigned int SensorOrientation_isUsed:1;
	unsigned int EVSEMaximumChargeCurrent_isUsed:1;
	unsigned int LFA_EVSEFinePositioningParameters_isUsed:1;
	unsigned int VehicleCheckInRes_isUsed:1;
	unsigned int PMaxScheduleEntry_isUsed:1;
	unsigned int SAScheduleList_isUsed:1;
	unsigned int X509SKI_isUsed:1;
	unsigned int PaymentOptionList_isUsed:1;
	unsigned int ContractSignatureEncryptedPrivateKey_isUsed:1;
	unsigned int VehicleCheckInReq_isUsed:1;
	unsigned int Certificate_isUsed:1;
	unsigned int CheckOutTime_isUsed:1;
	unsigned int CurrentSOC_isUsed:1;
	unsigned int ZCoordinate_isUsed:1;
	unsigned int MeasurementData_isUsed:1;
	unsigned int PairingRes_isUsed:1;
	unsigned int EVSEMaximumCurrent_isUsed:1;
	unsigned int LFA_EVFinePositioningParameters_isUsed:1;
	unsigned int AlignmentCheckParameters_isUsed:1;
	unsigned int EffectiveRadiatedPower_isUsed:1;
	unsigned int PairingReq_isUsed:1;
	unsigned int Value_isUsed:1;
	unsigned int byteValue_isUsed:1;
	unsigned int CurrentDemandReq_isUsed:1;
	unsigned int Generic_EVSEFinePositioningParameters_isUsed:1;
	unsigned int CurrentDemandRes_isUsed:1;
	unsigned int AC_EVBidirectionalParameter_isUsed:1;
	unsigned int Modulus_isUsed:1;
	unsigned int SelectedEnergyTransferService_isUsed:1;
	unsigned int startValue_isUsed:1;
	unsigned int SelectedVASList_isUsed:1;
	unsigned int ChargeParameterDiscoveryReq_isUsed:1;
	unsigned int ChargeParameterDiscoveryRes_isUsed:1;
	unsigned int SigMeterReading_isUsed:1;
	unsigned int TargetSOC_isUsed:1;
	unsigned int EVSEStatus_isUsed:1;
	unsigned int EVSEMinimumChargeCurrent_isUsed:1;
	unsigned int EVSEElectricalChargingDeviceStatus_isUsed:1;
	unsigned int X509SerialNumber_isUsed:1;
	unsigned int PaymentOption_isUsed:1;
	unsigned int Transforms_isUsed:1;
	unsigned int EVSEPeakCurrentRipple_isUsed:1;
	unsigned int ConsumptionCost_isUsed:1;
	unsigned int EVSEFinePositioningSetupParameters_isUsed:1;
	unsigned int EPriceLevel_isUsed:1;
	unsigned int Exponent_isUsed:1;
	unsigned int X509IssuerSerial_isUsed:1;
	unsigned int SPKIData_isUsed:1;
	unsigned int MagneticVectorList_isUsed:1;
	unsigned int EVSEFinePositioningParameters_isUsed:1;
	unsigned int EVTargetPower_isUsed:1;
	unsigned int SensorPackageList_isUsed:1;
	unsigned int DepartureTime_isUsed:1;
	unsigned int InletHot_isUsed:1;
	unsigned int EVPresentActivePower_isUsed:1;
	unsigned int X509Data_isUsed:1;
	unsigned int YCoordinate_isUsed:1;
	unsigned int KeyValue_isUsed:1;
	unsigned int DisplayParameters_isUsed:1;
	unsigned int EVSEPowerLimitAchieved_isUsed:1;
	unsigned int Body_isUsed:1;
	unsigned int DC_EVChargeParameter_isUsed:1;
	unsigned int Service_isUsed:1;
	unsigned int SignatureProperty_isUsed:1;
	unsigned int PGPKeyPacket_isUsed:1;
	unsigned int Seed_isUsed:1;
	unsigned int LFA_EVFinePositioningSetupParameters_isUsed:1;
	unsigned int MinimumPMaxRequest_isUsed:1;
	unsigned int FinePositioningReq_isUsed:1;
	unsigned int EnergyTransferServiceList_isUsed:1;
	unsigned int FinePositioningRes_isUsed:1;
	unsigned int AC_EVSEBidirectionalParameter_isUsed:1;
	unsigned int FreeService_isUsed:1;
	unsigned int AC_EVSEChargeParameter_isUsed:1;
	unsigned int SensorID_isUsed:1;
	unsigned int EVSECurrentRegulationTolerance_isUsed:1;
	unsigned int EVSEMechanicalChargingDeviceStatus_isUsed:1;
	unsigned int EVEnergyTransferParameter_isUsed:1;
	unsigned int SignalPulseDuration_isUsed:1;
	unsigned int shortValue_isUsed:1;
	unsigned int Manifest_isUsed:1;
	unsigned int DC_EVSEChargeParameter_isUsed:1;
	unsigned int MeteringReceiptReq_isUsed:1;
	unsigned int MeterID_isUsed:1;
	unsigned int MeteringReceiptRes_isUsed:1;
	unsigned int ServiceDiscoveryReq_isUsed:1;
	unsigned int SalesTariffID_isUsed:1;
	unsigned int ServiceDiscoveryRes_isUsed:1;
	unsigned int X509CRL_isUsed:1;
	unsigned int MagneticVectorSetup_isUsed:1;
	unsigned int DigestMethod_isUsed:1;
	unsigned int SPKISexp_isUsed:1;
	unsigned int MeterReadingDischarged_isUsed:1;
	unsigned int MeasurementDataList_isUsed:1;
	unsigned int SignatureProperties_isUsed:1;
	unsigned int SensorPosition_isUsed:1;
	unsigned int LFA_EVSEFinePositioningSetupParameters_isUsed:1;
	unsigned int eMAID_isUsed:1;
	unsigned int SensorPackage_isUsed:1;
	unsigned int EVCheckOutStatus_isUsed:1;
	unsigned int X509Certificate_isUsed:1;
	unsigned int RootCertificateID_isUsed:1;
	unsigned int DC_BidirectionalControlReq_isUsed:1;
	unsigned int EVSEPresentVoltage_isUsed:1;
	unsigned int DC_BidirectionalControlRes_isUsed:1;
	unsigned int VASList_isUsed:1;
	unsigned int MeterInfo_isUsed:1;
	unsigned int EVSETargetReactivePower_isUsed:1;
	unsigned int ChargingStatusReq_isUsed:1;
	unsigned int GenericParameters_isUsed:1;
	unsigned int ChargingStatusRes_isUsed:1;
	unsigned int EVMaximumChargePower_isUsed:1;
	unsigned int BulkSOC_isUsed:1;
	unsigned int NumberOfSignalPackages_isUsed:1;
	unsigned int ParameterSetID_isUsed:1;
	unsigned int PMax_isUsed:1;
	unsigned int EVMaximumEnergyRequest_isUsed:1;
	unsigned int EVOperation_isUsed:1;
	unsigned int CertificateUpdateRes_isUsed:1;
	unsigned int ChargingComplete_isUsed:1;
	unsigned int ListOfRootCertificateIDs_isUsed:1;
	unsigned int RotationVAtoGA_isUsed:1;
	unsigned int EVTargetVoltage_isUsed:1;
	unsigned int CertificateUpdateReq_isUsed:1;
	unsigned int ConnectChargingDeviceRes_isUsed:1;
	unsigned int DHpublickey_isUsed:1;
	unsigned int ServiceParameterList_isUsed:1;
	unsigned int SignatureValue_isUsed:1;
	unsigned int physicalValue_isUsed:1;
	unsigned int OperationMode_isUsed:1;
	unsigned int EVSECurrentLimitAchieved_isUsed:1;
	unsigned int ServiceDetailReq_isUsed:1;
	unsigned int ServiceDetailRes_isUsed:1;
	unsigned int intValue_isUsed:1;
	unsigned int EVMaximumDischargePower_isUsed:1;
	unsigned int MinimumSOC_isUsed:1;
	unsigned int SelectedPaymentOption_isUsed:1;
	unsigned int V2G_Message_isUsed:1;
	unsigned int EVSEID_isUsed:1;
	unsigned int TMeter_isUsed:1;
	unsigned int SensorOrder_isUsed:1;
	unsigned int SupportedServiceIDs_isUsed:1;
	unsigned int GenChallenge_isUsed:1;
	unsigned int EVFinePositioningParameters_isUsed:1;
	unsigned int SensorList_isUsed:1;
	unsigned int KeyInfo_isUsed:1;
	unsigned int ConnectChargingDeviceReq_isUsed:1;
	unsigned int AC_EVChargeParameter_isUsed:1;
	unsigned int Parameter_isUsed:1;
	unsigned int WeldingDetectionRes_isUsed:1;
	unsigned int GAID_isUsed:1;
	unsigned int SignalFrequency_isUsed:1;
	unsigned int EVSETargetPower_isUsed:1;
	unsigned int DC_EVBidirectionalParameter_isUsed:1;
	unsigned int SignatureMethod_isUsed:1;
	unsigned int WeldingDetectionReq_isUsed:1;
	unsigned int SelectedService_isUsed:1;
	unsigned int EVInputPower_isUsed:1;
	unsigned int VehicleCheckOutReq_isUsed:1;
	unsigned int PowerDemandReq_isUsed:1;
	unsigned int VehicleCheckOutRes_isUsed:1;
	unsigned int CurrentRange_isUsed:1;
	unsigned int EVPresentReactivePower_isUsed:1;
	unsigned int X509IssuerName_isUsed:1;
	unsigned int V2GRequest_isUsed:1;
	unsigned int Reference_isUsed:1;
	unsigned int BodyElement_isUsed:1;
	unsigned int MinimumPMaxScheduleEntry_isUsed:1;
	unsigned int EVFinePositioningSetupParameters_isUsed:1;
	unsigned int EVSENotification_isUsed:1;
	unsigned int PaymentServiceSelectionReq_isUsed:1;
	unsigned int PaymentServiceSelectionRes_isUsed:1;
	unsigned int Transform_isUsed:1;
	unsigned int Object_isUsed:1;
	unsigned int TargetOffsetY_isUsed:1;
	unsigned int PowerDemandRes_isUsed:1;
	unsigned int TargetOffsetX_isUsed:1;


	int _warning_;
}iso2EXIFragment;



#endif /* DEPLOY_ISO2_CODEC_FRAGMENT */



/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/



/******************************************* Functions that initializes each structure ****************************************/

void V2gFac_init_iso2EXIDocument( iso2EXIDocument* exiDoc);
#if DEPLOY_ISO2_CODEC_FRAGMENT == SUPPORT_YES
void V2gFac_init_iso2EXIFragment( iso2EXIFragment* exiFrag);
#endif /* DEPLOY_ISO2_CODEC_FRAGMENT */
void V2gFac_init_iso2RetrievalMethodType( iso2RetrievalMethodType* iso2RetrievalMethodType);
void V2gFac_init_iso2AuthorizationResType( iso2AuthorizationResType* iso2AuthorizationResType);
void V2gFac_init_iso2MV_EVSEFinePositioningSetupParametersType( iso2MV_EVSEFinePositioningSetupParametersType* iso2MV_EVSEFinePositioningSetupParametersType);
void V2gFac_init_iso2X509DataType( iso2X509DataType* iso2X509DataType);
void V2gFac_init_iso2RSAKeyValueType( iso2RSAKeyValueType* iso2RSAKeyValueType);
void V2gFac_init_iso2DC_BidirectionalControlResType( iso2DC_BidirectionalControlResType* iso2DC_BidirectionalControlResType);
void V2gFac_init_iso2CostType( iso2CostType* iso2CostType);
void V2gFac_init_iso2ChargingStatusResType( iso2ChargingStatusResType* iso2ChargingStatusResType);
void V2gFac_init_iso2MeterInfoType( iso2MeterInfoType* iso2MeterInfoType);
void V2gFac_init_iso2AC_EVChargeParameterType( iso2AC_EVChargeParameterType* iso2AC_EVChargeParameterType);
void V2gFac_init_iso2AC_EVSEBidirectionalParameterType( iso2AC_EVSEBidirectionalParameterType* iso2AC_EVSEBidirectionalParameterType);
void V2gFac_init_iso2VehicleCheckOutResType( iso2VehicleCheckOutResType* iso2VehicleCheckOutResType);
void V2gFac_init_iso2MagneticVectorListType( iso2MagneticVectorListType* iso2MagneticVectorListType);
void V2gFac_init_iso2CableCheckResType( iso2CableCheckResType* iso2CableCheckResType);
void V2gFac_init_iso2ServiceDiscoveryReqType( iso2ServiceDiscoveryReqType* iso2ServiceDiscoveryReqType);
void V2gFac_init_iso2ServiceType( iso2ServiceType* iso2ServiceType);
void V2gFac_init_iso2ServiceParameterListType( iso2ServiceParameterListType* iso2ServiceParameterListType);
void V2gFac_init_iso2PMaxScheduleType( iso2PMaxScheduleType* iso2PMaxScheduleType);
void V2gFac_init_iso2SignaturePropertiesType( iso2SignaturePropertiesType* iso2SignaturePropertiesType);
void V2gFac_init_iso2PMaxScheduleEntryType( iso2PMaxScheduleEntryType* iso2PMaxScheduleEntryType);
void V2gFac_init_iso2SignatureType( iso2SignatureType* iso2SignatureType);
void V2gFac_init_iso2VehicleCheckInReqType( iso2VehicleCheckInReqType* iso2VehicleCheckInReqType);
void V2gFac_init_iso2ConnectChargingDeviceResType( iso2ConnectChargingDeviceResType* iso2ConnectChargingDeviceResType);
void V2gFac_init_iso2WeldingDetectionResType( iso2WeldingDetectionResType* iso2WeldingDetectionResType);
void V2gFac_init_iso2SessionStopResType( iso2SessionStopResType* iso2SessionStopResType);
void V2gFac_init_iso2VehicleCheckInResType( iso2VehicleCheckInResType* iso2VehicleCheckInResType);
void V2gFac_init_iso2ServiceListType( iso2ServiceListType* iso2ServiceListType);
void V2gFac_init_iso2CertificateUpdateResType( iso2CertificateUpdateResType* iso2CertificateUpdateResType);
void V2gFac_init_iso2FinePositioningSetupResType( iso2FinePositioningSetupResType* iso2FinePositioningSetupResType);
void V2gFac_init_iso2AC_EVBidirectionalParameterType( iso2AC_EVBidirectionalParameterType* iso2AC_EVBidirectionalParameterType);
void V2gFac_init_iso2DC_BidirectionalControlReqType( iso2DC_BidirectionalControlReqType* iso2DC_BidirectionalControlReqType);
void V2gFac_init_iso2CertificateUpdateReqType( iso2CertificateUpdateReqType* iso2CertificateUpdateReqType);
void V2gFac_init_iso2ConsumptionCostType( iso2ConsumptionCostType* iso2ConsumptionCostType);
void V2gFac_init_iso2SAScheduleListType( iso2SAScheduleListType* iso2SAScheduleListType);
void V2gFac_init_iso2MagneticVectorSetupType( iso2MagneticVectorSetupType* iso2MagneticVectorSetupType);
void V2gFac_init_iso2LFA_EVSEFinePositioningSetupParametersType( iso2LFA_EVSEFinePositioningSetupParametersType* iso2LFA_EVSEFinePositioningSetupParametersType);
void V2gFac_init_iso2PaymentOptionListType( iso2PaymentOptionListType* iso2PaymentOptionListType);
void V2gFac_init_iso2LFA_EVSEFinePositioningParametersType( iso2LFA_EVSEFinePositioningParametersType* iso2LFA_EVSEFinePositioningParametersType);
void V2gFac_init_iso2RelativeTimeIntervalType( iso2RelativeTimeIntervalType* iso2RelativeTimeIntervalType);
void V2gFac_init_iso2EVFinePositioningParametersType( iso2EVFinePositioningParametersType* iso2EVFinePositioningParametersType);
void V2gFac_init_iso2AlignmentCheckReqType( iso2AlignmentCheckReqType* iso2AlignmentCheckReqType);
void V2gFac_init_iso2CertificateInstallationReqType( iso2CertificateInstallationReqType* iso2CertificateInstallationReqType);
void V2gFac_init_iso2TransformsType( iso2TransformsType* iso2TransformsType);
void V2gFac_init_iso2ObjectType( iso2ObjectType* iso2ObjectType);
void V2gFac_init_iso2SensorOrderListType( iso2SensorOrderListType* iso2SensorOrderListType);
void V2gFac_init_iso2ChargeParameterDiscoveryReqType( iso2ChargeParameterDiscoveryReqType* iso2ChargeParameterDiscoveryReqType);
void V2gFac_init_iso2ParameterType( iso2ParameterType* iso2ParameterType);
void V2gFac_init_iso2SessionStopReqType( iso2SessionStopReqType* iso2SessionStopReqType);
void V2gFac_init_iso2SensorMeasurementsType( iso2SensorMeasurementsType* iso2SensorMeasurementsType);
void V2gFac_init_iso2DC_EVSEChargeParameterType( iso2DC_EVSEChargeParameterType* iso2DC_EVSEChargeParameterType);
void V2gFac_init_iso2SensorPackageListType( iso2SensorPackageListType* iso2SensorPackageListType);
void V2gFac_init_iso2MeasurementDataListType( iso2MeasurementDataListType* iso2MeasurementDataListType);
void V2gFac_init_iso2CertificateChainType( iso2CertificateChainType* iso2CertificateChainType);
void V2gFac_init_iso2SignaturePropertyType( iso2SignaturePropertyType* iso2SignaturePropertyType);
void V2gFac_init_iso2TransformType( iso2TransformType* iso2TransformType);
void V2gFac_init_iso2EMAIDType( iso2EMAIDType* iso2EMAIDType);
void V2gFac_init_iso2DSAKeyValueType( iso2DSAKeyValueType* iso2DSAKeyValueType);
void V2gFac_init_iso2EntryType( iso2EntryType* iso2EntryType);
void V2gFac_init_iso2MessageHeaderType( iso2MessageHeaderType* iso2MessageHeaderType);
void V2gFac_init_iso2WPT_EVChargeParameterType( iso2WPT_EVChargeParameterType* iso2WPT_EVChargeParameterType);
void V2gFac_init_iso2DisconnectChargingDeviceReqType( iso2DisconnectChargingDeviceReqType* iso2DisconnectChargingDeviceReqType);
void V2gFac_init_iso2ChargeLoopReqType( iso2ChargeLoopReqType* iso2ChargeLoopReqType);
void V2gFac_init_iso2V2GRequestType( iso2V2GRequestType* iso2V2GRequestType);
void V2gFac_init_iso2MeteringReceiptResType( iso2MeteringReceiptResType* iso2MeteringReceiptResType);
void V2gFac_init_iso2SessionSetupResType( iso2SessionSetupResType* iso2SessionSetupResType);
void V2gFac_init_iso2AC_BidirectionalControlReqType( iso2AC_BidirectionalControlReqType* iso2AC_BidirectionalControlReqType);
void V2gFac_init_iso2MV_EVSEFinePositioningParametersType( iso2MV_EVSEFinePositioningParametersType* iso2MV_EVSEFinePositioningParametersType);
void V2gFac_init_iso2ReferenceType( iso2ReferenceType* iso2ReferenceType);
void V2gFac_init_iso2EVSEEnergyTransferParameterType( iso2EVSEEnergyTransferParameterType* iso2EVSEEnergyTransferParameterType);
void V2gFac_init_iso2MeteringReceiptReqType( iso2MeteringReceiptReqType* iso2MeteringReceiptReqType);
void V2gFac_init_iso2KeyValueType( iso2KeyValueType* iso2KeyValueType);
void V2gFac_init_iso2SensorListType( iso2SensorListType* iso2SensorListType);
void V2gFac_init_iso2CurrentDemandReqType( iso2CurrentDemandReqType* iso2CurrentDemandReqType);
void V2gFac_init_iso2FinePositioningSetupReqType( iso2FinePositioningSetupReqType* iso2FinePositioningSetupReqType);
void V2gFac_init_iso2LFA_EVFinePositioningSetupParametersType( iso2LFA_EVFinePositioningSetupParametersType* iso2LFA_EVFinePositioningSetupParametersType);
void V2gFac_init_iso2SAScheduleTupleType( iso2SAScheduleTupleType* iso2SAScheduleTupleType);
void V2gFac_init_iso2WPT_EVSEChargeParameterType( iso2WPT_EVSEChargeParameterType* iso2WPT_EVSEChargeParameterType);
void V2gFac_init_iso2FinePositioningResType( iso2FinePositioningResType* iso2FinePositioningResType);
void V2gFac_init_iso2BodyBaseType( iso2BodyBaseType* iso2BodyBaseType);
void V2gFac_init_iso2ServiceDetailResType( iso2ServiceDetailResType* iso2ServiceDetailResType);
void V2gFac_init_iso2PowerDeliveryReqType( iso2PowerDeliveryReqType* iso2PowerDeliveryReqType);
void V2gFac_init_iso2PairingResType( iso2PairingResType* iso2PairingResType);
void V2gFac_init_iso2AuthorizationReqType( iso2AuthorizationReqType* iso2AuthorizationReqType);
void V2gFac_init_iso2ParameterSetType( iso2ParameterSetType* iso2ParameterSetType);
void V2gFac_init_iso2SPKIDataType( iso2SPKIDataType* iso2SPKIDataType);
void V2gFac_init_iso2PaymentDetailsResType( iso2PaymentDetailsResType* iso2PaymentDetailsResType);
void V2gFac_init_iso2SignatureMethodType( iso2SignatureMethodType* iso2SignatureMethodType);
void V2gFac_init_iso2AC_BidirectionalControlResType( iso2AC_BidirectionalControlResType* iso2AC_BidirectionalControlResType);
void V2gFac_init_iso2VehicleCheckOutReqType( iso2VehicleCheckOutReqType* iso2VehicleCheckOutReqType);
void V2gFac_init_iso2WeldingDetectionReqType( iso2WeldingDetectionReqType* iso2WeldingDetectionReqType);
void V2gFac_init_iso2AlignmentCheckResType( iso2AlignmentCheckResType* iso2AlignmentCheckResType);
void V2gFac_init_iso2PowerDemandReqType( iso2PowerDemandReqType* iso2PowerDemandReqType);
void V2gFac_init_iso2MinimumPMaxRequestType( iso2MinimumPMaxRequestType* iso2MinimumPMaxRequestType);
void V2gFac_init_iso2DisconnectChargingDeviceResType( iso2DisconnectChargingDeviceResType* iso2DisconnectChargingDeviceResType);
void V2gFac_init_iso2SessionSetupReqType( iso2SessionSetupReqType* iso2SessionSetupReqType);
void V2gFac_init_iso2PaymentDetailsReqType( iso2PaymentDetailsReqType* iso2PaymentDetailsReqType);
void V2gFac_init_iso2Generic_EVFinePositioningParametersType( iso2Generic_EVFinePositioningParametersType* iso2Generic_EVFinePositioningParametersType);
void V2gFac_init_iso2ConnectChargingDeviceReqType( iso2ConnectChargingDeviceReqType* iso2ConnectChargingDeviceReqType);
void V2gFac_init_iso2AC_EVSEChargeParameterType( iso2AC_EVSEChargeParameterType* iso2AC_EVSEChargeParameterType);
void V2gFac_init_iso2SalesTariffEntryType( iso2SalesTariffEntryType* iso2SalesTariffEntryType);
void V2gFac_init_iso2DC_EVSEBidirectionalParameterType( iso2DC_EVSEBidirectionalParameterType* iso2DC_EVSEBidirectionalParameterType);
void V2gFac_init_iso2CanonicalizationMethodType( iso2CanonicalizationMethodType* iso2CanonicalizationMethodType);
void V2gFac_init_iso2DisplayParametersType( iso2DisplayParametersType* iso2DisplayParametersType);
void V2gFac_init_iso2DC_EVBidirectionalParameterType( iso2DC_EVBidirectionalParameterType* iso2DC_EVBidirectionalParameterType);
void V2gFac_init_iso2PaymentServiceSelectionReqType( iso2PaymentServiceSelectionReqType* iso2PaymentServiceSelectionReqType);
void V2gFac_init_iso2MagneticVectorType( iso2MagneticVectorType* iso2MagneticVectorType);
void V2gFac_init_iso2PhysicalValueType( iso2PhysicalValueType* iso2PhysicalValueType);
void V2gFac_init_iso2SystemStatusReqType( iso2SystemStatusReqType* iso2SystemStatusReqType);
void V2gFac_init_iso2SystemStatusResType( iso2SystemStatusResType* iso2SystemStatusResType);
void V2gFac_init_iso2EVSEFinePositioningSetupParametersType( iso2EVSEFinePositioningSetupParametersType* iso2EVSEFinePositioningSetupParametersType);
void V2gFac_init_iso2V2GResponseType( iso2V2GResponseType* iso2V2GResponseType);
void V2gFac_init_iso2BodyType( iso2BodyType* iso2BodyType);
void V2gFac_init_iso2PreChargeResType( iso2PreChargeResType* iso2PreChargeResType);
void V2gFac_init_iso2EVSEFinePositioningParametersType( iso2EVSEFinePositioningParametersType* iso2EVSEFinePositioningParametersType);
void V2gFac_init_iso2PaymentServiceSelectionResType( iso2PaymentServiceSelectionResType* iso2PaymentServiceSelectionResType);
void V2gFac_init_iso2DigestMethodType( iso2DigestMethodType* iso2DigestMethodType);
void V2gFac_init_iso2TargetPositionType( iso2TargetPositionType* iso2TargetPositionType);
void V2gFac_init_iso2LFA_EVFinePositioningParametersType( iso2LFA_EVFinePositioningParametersType* iso2LFA_EVFinePositioningParametersType);
void V2gFac_init_iso2DC_EVChargeParameterType( iso2DC_EVChargeParameterType* iso2DC_EVChargeParameterType);
void V2gFac_init_iso2ServiceDetailReqType( iso2ServiceDetailReqType* iso2ServiceDetailReqType);
void V2gFac_init_iso2PreChargeReqType( iso2PreChargeReqType* iso2PreChargeReqType);
void V2gFac_init_iso2ManifestType( iso2ManifestType* iso2ManifestType);
void V2gFac_init_iso2AnonType_V2G_Message( iso2AnonType_V2G_Message* iso2AnonType_V2G_Message);
void V2gFac_init_iso2SelectedServiceListType( iso2SelectedServiceListType* iso2SelectedServiceListType);
void V2gFac_init_iso2Generic_EVSEFinePositioningParametersType( iso2Generic_EVSEFinePositioningParametersType* iso2Generic_EVSEFinePositioningParametersType);
void V2gFac_init_iso2CartesianCoordinatesType( iso2CartesianCoordinatesType* iso2CartesianCoordinatesType);
void V2gFac_init_iso2KeyInfoType( iso2KeyInfoType* iso2KeyInfoType);
void V2gFac_init_iso2SubCertificatesType( iso2SubCertificatesType* iso2SubCertificatesType);
void V2gFac_init_iso2ListOfRootCertificateIDsType( iso2ListOfRootCertificateIDsType* iso2ListOfRootCertificateIDsType);
void V2gFac_init_iso2EVEnergyTransferParameterType( iso2EVEnergyTransferParameterType* iso2EVEnergyTransferParameterType);
void V2gFac_init_iso2ContractSignatureEncryptedPrivateKeyType( iso2ContractSignatureEncryptedPrivateKeyType* iso2ContractSignatureEncryptedPrivateKeyType);
void V2gFac_init_iso2MagneticVectorSetupListType( iso2MagneticVectorSetupListType* iso2MagneticVectorSetupListType);
void V2gFac_init_iso2PairingReqType( iso2PairingReqType* iso2PairingReqType);
void V2gFac_init_iso2CurrentDemandResType( iso2CurrentDemandResType* iso2CurrentDemandResType);
void V2gFac_init_iso2X509IssuerSerialType( iso2X509IssuerSerialType* iso2X509IssuerSerialType);
void V2gFac_init_iso2ChargingStatusReqType( iso2ChargingStatusReqType* iso2ChargingStatusReqType);
void V2gFac_init_iso2CertificateInstallationResType( iso2CertificateInstallationResType* iso2CertificateInstallationResType);
void V2gFac_init_iso2SensorPackageType( iso2SensorPackageType* iso2SensorPackageType);
void V2gFac_init_iso2PGPDataType( iso2PGPDataType* iso2PGPDataType);
void V2gFac_init_iso2ServiceDiscoveryResType( iso2ServiceDiscoveryResType* iso2ServiceDiscoveryResType);
void V2gFac_init_iso2ServiceIDListType( iso2ServiceIDListType* iso2ServiceIDListType);
void V2gFac_init_iso2EVFinePositioningSetupParametersType( iso2EVFinePositioningSetupParametersType* iso2EVFinePositioningSetupParametersType);
void V2gFac_init_iso2ChargeParameterDiscoveryResType( iso2ChargeParameterDiscoveryResType* iso2ChargeParameterDiscoveryResType);
void V2gFac_init_iso2PowerDemandResType( iso2PowerDemandResType* iso2PowerDemandResType);
void V2gFac_init_iso2ChargingProfileType( iso2ChargingProfileType* iso2ChargingProfileType);
void V2gFac_init_iso2FinePositioningReqType( iso2FinePositioningReqType* iso2FinePositioningReqType);
void V2gFac_init_iso2SalesTariffType( iso2SalesTariffType* iso2SalesTariffType);
void V2gFac_init_iso2SensorType( iso2SensorType* iso2SensorType);
void V2gFac_init_iso2SignatureValueType( iso2SignatureValueType* iso2SignatureValueType);
void V2gFac_init_iso2SignedInfoType( iso2SignedInfoType* iso2SignedInfoType);
void V2gFac_init_iso2PowerDeliveryResType( iso2PowerDeliveryResType* iso2PowerDeliveryResType);
void V2gFac_init_iso2CableCheckReqType( iso2CableCheckReqType* iso2CableCheckReqType);
void V2gFac_init_iso2SelectedServiceType( iso2SelectedServiceType* iso2SelectedServiceType);
void V2gFac_init_iso2DiffieHellmanPublickeyType( iso2DiffieHellmanPublickeyType* iso2DiffieHellmanPublickeyType);
void V2gFac_init_iso2EVSEStatusType( iso2EVSEStatusType* iso2EVSEStatusType);


#endif /* DEPLOY_ISO2_CODEC */

#ifdef __cplusplus
}
#endif

#endif
