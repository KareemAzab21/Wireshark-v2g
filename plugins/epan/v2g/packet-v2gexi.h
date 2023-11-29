/*
 * Copyright (c) 2022 ChargePoint, Inc.
 * All rights reserved.
 *
 * See LICENSE file
 */

#ifndef V2GEXI_H
#define V2GEXI_H

#include <string.h>
#include <ctype.h>
#include "config.h"
#include <epan/packet.h>
#include <epan/proto.h>
#include <epan/expert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <epan/prefs.h>
#include "V2G_Facilities/Fac.h"

void proto_register_v2gexi(void);

void proto_reg_handoff_v2gexi(void);

static int dissect_v2gexi(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data);

static void dissect_v2giso2_message_header(const iso2MessageHeaderType *header, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);

static void dissect_v2giso2_signature(const iso2SignatureType *signature, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_signedinfo(const iso2SignedInfoType *signedinfo, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_canonicalizationmethod(const iso2CanonicalizationMethodType *canonicalizationmethod, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_signaturemethod(const iso2SignatureMethodType *signaturemethod, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_reference(const iso2ReferenceType *reference, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_transforms(const iso2TransformsType *transforms, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_transform(const iso2TransformType *transform, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_digestmethod(const iso2DigestMethodType *digestmethod, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_signaturevalue(const iso2SignatureValueType *signaturevalue, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2gexi_apphandappprotocoltype(proto_tree *tree, tvbuff_t *tvb, appHandAppProtocolType *msg, const char *subtree_name);
static void dissect_v2gexi_supportedappprotocolreq(proto_tree *tree, tvbuff_t *tvb, appHandAnonType_supportedAppProtocolReq *msg);
static void dissect_v2gexi_supportedappprotocolres(proto_tree *tree, tvbuff_t *tvb, appHandAnonType_supportedAppProtocolRes *msg);
static void dissect_v2gexi_handshake(proto_tree *tree, tvbuff_t *tvb, appHandEXIDocument *msg);
static void dissect_v2giso2_Physicalvalue(proto_tree *tree, tvbuff_t *tvb, iso2PhysicalValueType *physicalValue, char *subtreeName);
static void dissect_v2giso2_Prechargereq(proto_tree *tree, tvbuff_t *tvb, iso2PreChargeReqType *msg);
static void dissect_v2giso2_cablecheckres(const iso2CableCheckResType *res, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_evsestatus(const iso2EVSEStatusType *evsestatus, tvbuff_t *tvb, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_authorizationres(const iso2AuthorizationResType *authorizationres, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_prechargeres(const iso2PreChargeResType *res, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_AC_EVChargeParameter(proto_tree *tree, tvbuff_t *tvb, iso2AC_EVChargeParameterType *msg);
static void dissect_v2giso2_AC_EVBidirectionalParameter(proto_tree *tree, tvbuff_t *tvb, iso2AC_EVBidirectionalParameterType *msg);
static void dissect_v2giso2_DC_EVChargeParameter(proto_tree *tree, tvbuff_t *tvb, iso2DC_EVChargeParameterType *msg);
static void dissect_v2giso2_DC_EVBidirectionalParameter(proto_tree *tree, tvbuff_t *tvb, iso2DC_EVBidirectionalParameterType *msg);
static void dissect_v2giso2_WPT_EVChargeParameter(proto_tree *tree, tvbuff_t *tvb, iso2WPT_EVChargeParameterType *msg);
static void dissect_v2giso2_RelativeTimeInterval(proto_tree *tree, tvbuff_t *tvb, iso2RelativeTimeIntervalType *msg);
static void dissect_v2giso2_PMaxScheduleEntry(proto_tree *tree, tvbuff_t *tvb, iso2PMaxScheduleEntryType *msg, int idx);
static void dissect_v2giso2_MinimumPMaxRequest(proto_tree *tree, tvbuff_t *tvb, iso2MinimumPMaxRequestType *msg);
static void dissect_v2giso2_ChargeParameterDiscoveryReq(proto_tree *tree, tvbuff_t *tvb, iso2ChargeParameterDiscoveryReqType *msg);
static void dissect_v2giso2_SessionStopRes(proto_tree *tree, tvbuff_t *tvb, iso2SessionStopResType *msg);
static void dissect_v2giso2_CurrentDemandResType(iso2CurrentDemandResType *res, tvbuff_t *tvb, proto_tree *tree, gint idx);
static void dissect_v2giso2_meterinfo(iso2MeterInfoType *meterinfo, tvbuff_t *tvb, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_PaymentServiceSelectionRes(proto_tree *tree, tvbuff_t *tvb, iso2PaymentServiceSelectionResType *PaymentServiceSelectionRes);
static void dissect_v2giso2_ServiceDiscoveryRes(proto_tree *tree, tvbuff_t *tvb, iso2ServiceDiscoveryResType *ServiceDiscoveryRes);
static void dissect_v2giso2_paymentoptionlist(proto_tree *tree, tvbuff_t *tvb, iso2PaymentOptionListType *PaymentOptionList);
static void dissect_v2giso2_service(proto_tree *tree, tvbuff_t *tvb, iso2ServiceType *Service, char *idx);
static void dissect_v2giso2_servicelist(proto_tree *tree, tvbuff_t *tvb, iso2ServiceListType *ServiceList);
static void dissect_v2g_certificatechain(iso2CertificateChainType *certificatechain, tvbuff_t *tvb, proto_tree *tree, int idx, const char *subtree_name);
static void dissect_v2giso2_subcertificates(iso2SubCertificatesType *subcertificates, tvbuff_t *tvb, proto_tree *tree, int idx, const char *subtree_name);
static void dissect_v2giso2_profileentry(struct iso2ProfileEntryType *profileentry, tvbuff_t *tvb, proto_tree *tree, gint idx, const char *subtree_name);
static void dissect_v2giso2_chargingprofile(iso2ChargingProfileType *chargingprofile, tvbuff_t *tvb, proto_tree *tree, gint idx, const char *subtree_name);
// Table of Response codes ( having values from 0 to 29 ) and the corresponding string which will be displayed for it in wireshark tree item

static const value_string v2giso2_response_code_names[] = {
	{iso2responseCodeType_OK, "OK"},
	{iso2responseCodeType_OK_NewSessionEstablished,
	 "OK (New Session Established)"},
	{iso2responseCodeType_OK_OldSessionJoined,
	 "OK (Old Session Joined)"},
	{iso2responseCodeType_OK_CertificateExpiresSoon,
	 "OK (Certificate Expires Soon)"},
	{iso2responseCodeType_OK_IsolationValid,
	 "OK (NewSession Established)"},
	{iso2responseCodeType_OK_IsolationWarning,
	 "OK (Isolation Valid)"},
	{iso2responseCodeType_WARNING_CertificateExpired,
	 "WARNING ! (Certificate Expired)"},
	{iso2responseCodeType_WARNING_NoCertificateAvailable,
	 "WARNING ! (No Certificate Available)"},
	{iso2responseCodeType_WARNING_CertValidationError,
	 "WARNING ! (Certificate Validation Error)"},
	{iso2responseCodeType_WARNING_CertVerificationError,
	 "WARNING ! (Certificate Verification Error)"},
	{iso2responseCodeType_WARNING_ContractCanceled,
	 "WARNING ! (Contract Canceled)"},
	{iso2responseCodeType_FAILED, "FAILED"},
	{iso2responseCodeType_FAILED_SequenceError,
	 "FAILED (SequenceError)"},
	{iso2responseCodeType_FAILED_ServiceIDInvalid,
	 "FAILED (Service ID Invalid)"},
	{iso2responseCodeType_FAILED_UnknownSession,
	 "FAILED (Unknown Session)"},
	{iso2responseCodeType_FAILED_ServiceSelectionInvalid,
	 "FAILED (ServiceSelectionInvalid)"},
	{iso2responseCodeType_FAILED_SignatureError,
	 "FAILED (Signature Error)"},
	{iso2responseCodeType_FAILED_PaymentSelectionInvalid,
	 "FAILED (PaymentSelectionInvalid)"},
	{iso2responseCodeType_FAILED_ChallengeInvalid,
	 "FAILED (Challenge Invalid)"},
	{iso2responseCodeType_FAILED_WrongChargeParameter,
	 "FAILED (Wrong Charge Parameter)"},
	{iso2responseCodeType_FAILED_IsolationFault,
	 "FAILED (Isolation Fault)"},
	{iso2responseCodeType_FAILED_PowerDeliveryNotApplied,
	 "FAILED (PowerDeliveryNotApplied)"},
	{iso2responseCodeType_FAILED_TariffSelectionInvalid,
	 "FAILED (TariffSelectionInvalid)"},
	{iso2responseCodeType_FAILED_ChargingProfileInvalid,
	 "FAILED (ChargingProfileInvalid)"},
	{iso2responseCodeType_FAILED_MeteringSignatureNotValid,
	 "FAILED (MeteringSignatureNotValid)"},
	{iso2responseCodeType_FAILED_NoChargeServiceSelected,
	 "FAILED (NoChargeServiceSelected)"},
	{iso2responseCodeType_FAILED_WrongEnergyTransferMode,
	 "FAILED (WrongEnergyTransferMode)"},
	{iso2responseCodeType_FAILED_ContactorError,
	 "FAILED (ContactorError)"},
	{iso2responseCodeType_FAILED_CertificateNotYetValid,
	 "FAILED (Certificate Not Yet Valid)"},
	{iso2responseCodeType_FAILED_CertificateRevoked,
	 "FAILED (CertificateRevoked)"}};

static const value_string v2giso2_enum_iso2paymentOptionType_names[] = {
	{iso2paymentOptionType_Contract, "Contract"},
	{iso2paymentOptionType_ExternalPayment, "ExternalPayment"}};

// Table of Current Running processes and the corresponding string which will be displayed for it in wireshark tree item
// These processes run at the SE during cable check

static const value_string v2giso2_evse_processing_names[] = {
	{iso2EVSEProcessingType_Finished, "Finished"},
	{iso2EVSEProcessingType_Ongoing, "Ongoing"},
	{iso2EVSEProcessingType_Ongoing_WaitingForCustomerInteraction,
	 "Ongoing (WaitingForCustomerInteraction)"}};

// Table of Notification Type codes which are sent by SE to EV during cable check process

static const value_string v2giso2_evsenotification_names[] = {
	{iso2EVSENotificationType_StopCharging, "StopCharging"},
	{iso2EVSENotificationType_ReNegotiation, "ReNegotiation"}};

static const value_string v2giso2_evoperation_names[] = {
	{iso2EVOperationType_Charge, "Charge"},
	{iso2EVOperationType_BPT, "BPT"}};

static const value_string v2gexi_response_code_names[] = {
	{appHandresponseCodeType_OK_SuccessfulNegotiation, "Success"},
	{appHandresponseCodeType_OK_SuccessfulNegotiationWithMinorDeviation,
	 "SuccessWithMinorDeviation"},
	{appHandresponseCodeType_Failed_NoNegotiation, "Failed"}};

/*
 * Decode the exi string character (int) into a c string
 */
static inline void
exi_add_characters(proto_tree *tree,
				   int hfindex,
				   tvbuff_t *tvb,
				   const exi_string_character_t *characters,
				   unsigned int characterslen,
				   size_t charactersmaxsize);

/*
 * Decode the exi bytes into a c string
 */
static inline void
exi_add_bytes(proto_tree *tree,
			  int hfindex,
			  tvbuff_t *tvb,
			  const uint8_t *bytes,
			  unsigned int byteslen,
			  size_t bytesmaxsize);

#endif
