#include "config.h"
#include <epan/packet.h>
#include <epan/proto.h>
#include <epan/expert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <epan/prefs.h>
#include "packet-v2gexi.h"

#define V2G_PORT = 15118

/* Initialize the subtree pointers */
static gint ett_v2gexi = -1;
static gint ett_v2giso2 = -1;
static gint ett_v2giso2_header = -1;
static gint ett_v2giso2_body = -1;
static gint ett_v2giso2_array = -1;
static gint ett_v2giso2_array_i = -1;
static gint ett_v2giso2_iso2SignatureType = -1;
static gint ett_v2giso2_iso2SignedInfoType = -1;
static gint ett_v2giso2_iso2CanonicalizationMethodType = -1;
static gint ett_v2giso2_iso2SignatureMethodType = -1;
static gint ett_v2giso2_iso2ReferenceType = -1;
static gint ett_v2giso2_iso2TransformsType = -1;
static gint ett_v2giso2_iso2TransformType = -1;
static gint ett_v2giso2_iso2DigestMethodType = -1;
static gint ett_v2giso2_iso2SignatureValueType = -1;
static gint ett_v2giso2_iso2KeyInfoType = -1;
static gint ett_v2giso2_iso2PreChargeReqType = -1;
static gint ett_v2giso2_iso2DC_EVSEStatusType = -1;
static gint ett_v2giso2_iso2PhysicalValueType = -1;
static gint ett_v2giso2_iso2MeterInfoType = -1;
static gint ett_v2giso2_iso2EVSEStatusType = -1;
static gint ett_v2giso2_iso2PowerDeliveryReqType = -1;
static gint ett_v2giso2_iso2ChargingProfileType = -1;
static gint ett_v2giso2_iso2ProfileEntryType = -1;

// Variables for wrapping up the packet dissection fields.
static int hf_v2giso2_MessageHeaderType_SessionID = -1;

static int hf_v2giso2_SignatureType_Id = -1;
static int hf_v2giso2_SignedInfoType_Id = -1;

static int hf_v2giso2_CanonicalizationMethodType_Algorithm = -1;
static int hf_v2giso2_CanonicalizationMethodType_ANY = -1;

static int hf_v2giso2_SignatureMethodType_Algorithm = -1;
static int hf_v2giso2_SignatureMethodType_HMACOutputLength = -1;
static int hf_v2giso2_SignatureMethodType_ANY = -1;

static int hf_v2giso2_ReferenceType_Id = -1;
static int hf_v2giso2_ReferenceType_URI = -1;
static int hf_v2giso2_ReferenceType_Type = -1;

static int hf_v2giso2_TransformType_Algorithm = -1;
static int hf_v2giso2_TransformType_ANY = -1;
static int hf_v2giso2_ReferenceType_DigestValue = -1;
static int hf_v2giso2_TransformType_XPath = -1;
static int hf_v2giso2_DigestMethodType_Algorithm = -1;
static int hf_v2giso2_DigestMethodType_ANY = -1;

static int hf_v2giso2_iso2PreChargeResType_ResponseCode = -1;

static int hf_v2giso2_SignatureValueType_Id = -1;
static int hf_v2giso2_SignatureValueType_CONTENT = -1;

static int hf_v2giso2_iso2PaymentDetailsResType_ResponseCode = -1;
static int hf_v2giso2_iso2PaymentDetailsResType_GenChallenge = -1;
static int hf_v2giso2_iso2PaymentDetailsResType_EVSETimeStamp = -1;
static int hf_v2giso2_iso2PaymentDetailsResType_EVSEStatus_NotificationMaxDelay = -1;
static int hf_v2giso2_iso2PaymentDetailsResType_EVSEStatus_EVSENotification = -1;
static int hf_v2giso2_iso2ChargeParameterDiscoveryResType_EVSEStatus_NotificationMaxDelay = -1;
static int hf_v2giso2_iso2ChargeParameterDiscoveryResType_EVSEStatus_EVSENotification = -1;
/*----------------------------------------------------------------------------------*/
static int hf_v2g_iso2ChargeParameterDiscoveryReqType_MaxSupportingPoints = -1;
static int hf_v2g_iso2ChargeParameterDiscoveryReqType_EVEnergyTransferParameter = -1;
static int hf_v2g_iso2AC_EVChargeParameterType_DepartureTime = -1;
static int hf_v2g_iso2AC_EVBidirectionalParameterType_DepartureTime = -1;
static int hf_v2g_iso2WPT_EVChargeParameterType_DepartureTime = -1;
static int hf_v2g_iso2DC_EVChargeParameterType_DepartureTime = -1;
static int hf_v2g_iso2DC_EVChargeParameterType_CurrentSOC = -1;
static int hf_v2g_iso2DC_EVChargeParameterType_TargetSOC = -1;
static int hf_v2g_iso2DC_EVChargeParameterType_BulkSOC = -1;
static int hf_v2g_DC_EVBidirectionalParameterType_DepartureTime = -1;
static int hf_v2g_DC_EVBidirectionalParameterType_CurrentSOC = -1;
static int hf_v2g_DC_EVBidirectionalParameterType_TargetSOC = -1;
static int hf_v2g_DC_EVBidirectionalParameterType_BulkSOC = -1;
static int hf_v2g_DC_EVBidirectionalParameterType_MinimumSOC = -1;
static int hf_v2g_iso2MinimumPMaxRequest_arrayLen = -1;
static int hf_v2g_iso2PMaxScheduleEntryType_arrayLen = -1;
static int hf_v2g_iso2RelativeTimeInterval_start = -1;
static int hf_v2g_iso2RelativeTimeInterval_duration = -1;

/*----------------------------------------------------------------------------------*/
static int hf_v2giso2_iso2SessionSetupReqType_EVCCID = -1;
static int hf_v2giso2_iso2SessionSetupResType_ResponseCode = -1;
static int hf_v2giso2_iso2SessionSetupResType_EVSEID = -1;
static int hf_v2giso2_iso2SessionSetupResType_EVSETimeStamp = -1;
static int hf_v2giso2_iso2SessionSetupResType_EVSEStatus = -1;
static int hf_v2giso2_iso2SessionSetupResType_EVSEStatus_NotificationMaxDelay = -1;
static int hf_v2giso2_iso2SessionSetupResType_EVSEStatus_EVSENotification = -1;

static int hf_v2giso2_iso2AuthorizationReqType_Id = -1;
static int hf_v2giso2_iso2AuthorizationReqType_GenChallenge = -1;
static int hf_v2giso2_iso2AuthorizationResType_ResponseCode = -1;
static int hf_v2giso2_iso2AuthorizationResType_EVSEProcessing = -1;

static int hf_v2giso2_iso2PowerDeliveryReqType_ChargeProgress = -1;
static int hf_v2giso2_iso2PowerDeliveryReqType_SAScheduleTupleID = -1;
static int hf_v2giso2_iso2PowerDeliveryResType_ResponseCode = -1;
static int hf_v2giso2_iso2PowerDeliveryResType_EVSEProcessing = -1;
static int hf_v2giso2_iso2PowerDeliveryReqType_EVOperation = -1;
static int hf_v2giso2_iso2PhysicalValueType_exponent = -1;
static int hf_v2giso2_iso2PhysicalValueType_value = -1;

static int hf_v2gexi_handshake_request = -1;
static int hf_v2gexi_struct_appHandAppProtocolType_ProtocolNamespace = -1;
static int hf_v2gexi_struct_appHandAppProtocolType_VersionNumberMajor = -1;
static int hf_v2gexi_struct_appHandAppProtocolType_VersionNumberMinor = -1;
static int hf_v2gexi_struct_appHandAppProtocolType_SchemaID = -1;
static int hf_v2gexi_struct_appHandAppProtocolType_Priority = -1;

static int hf_v2gexi_handshake_response = -1;
static int hf_v2gexi_struct_supportedAppProtocolRes_ResponseCode = -1;
static int hf_v2gexi_struct_supportedAppProtocolRes_SchemaID = -1;

/* Specifically track voltage and current for graphing */
static int hf_v2giso2_target_voltage = -1;
static int hf_v2giso2_target_current = -1;
static int hf_v2giso2_present_voltage = -1;
static int hf_v2giso2_present_current = -1;

static int hf_v2giso2_iso2PaymentServiceSelectionReqType_SelectedPaymentOption = -1;
static int hf_v2giso2_iso2SelectedServiceType_ParameterSetID = -1;
static int hf_v2giso2_iso2SelectedServiceType_ServiceID = -1;
static int hf_v2giso2_iso2ServiceDiscoveryReqType_ServiceScope = -1;
static int hf_v2giso2_iso2ServiceDiscoveryReqType_ServiceCategory = -1;
static int hf_v2giso2_iso2CertificateChainType_Id = -1;
static int hf_v2giso2_iso2CertificateChainType_Certificate = -1;
static int hf_v2giso2_iso2SubCertificatesType_Certificate = -1;
static int hf_v2giso2_iso2PaymentDetailsReqType_eMAID = -1;

static int hf_v2giso2_iso2CurrentDemandResType_ResponseCode = -1;
static int hf_v2giso2_iso2CurrentDemandResType_EVSECurrentLimitAchieved = -1;
static int hf_v2giso2_iso2CurrentDemandResType_EVSEVoltageLimitAchieved = -1;
static int hf_v2giso2_iso2CurrentDemandResType_EVSEPowerLimitAchieved = -1;
static int hf_v2giso2_iso2CurrentDemandResType_EVSEID = -1;
static int hf_v2giso2_iso2CurrentDemandResType_SAScheduleTupleID = -1;
static int hf_v2giso2_iso2CurrentDemandResType_ReceiptRequired = -1;

static int hf_v2giso2_iso2CableCheckResType_ResponseCode = -1;
static int hf_v2giso2_iso2CableCheckResType_EVSEProcessing = -1;

static int hf_v2giso2_iso2DC_EVSEStatusType_NotificationMaxDelay = -1;
static int hf_v2giso2_iso2DC_EVSEStatusType_EVSENotification = -1;

static int hf_v2giso2_iso2SessionStopReqType_ChargingSession = -1;
static int hf_v2giso2_iso2SessionStopResType_ResponseCode = -1;

static int hf_v2giso2_iso2MeterInfoType_MeterID = -1;
static int hf_v2giso2_iso2MeterInfoType_MeterReadingCharged = -1;
static int hf_v2giso2_iso2MeterInfoType_MeterReadingDischarged = -1;
static int hf_v2giso2_iso2MeterInfoType_SigMeterReading = -1;
static int hf_v2giso2_iso2MeterInfoType_MeterStatus = -1;
static int hf_v2giso2_iso2MeterInfoType_TMeter = -1;

static int hf_v2giso2_ChargeParameterDiscoveryResType_EVSEProcessing = -1;
static int hf_v2giso2_ChargeParameterDiscoveryResType_ResponseCode = -1;
static int hf_v2giso2_SAScheduleTupleType_SAScheduleTupleID = -1;
static int hf_v2giso2_RelativeTimeIntervalType_duration = -1;
static int hf_v2giso2_RelativeTimeIntervalType_start = -1;

static int hf_v2giso2_iso2SalesTariffType_Id = -1;
static int hf_v2giso2_iso2SalesTariffType_SalesTariffDescription = -1;
static int hf_v2giso2_iso2SalesTariffType_NumEPriceLevels = -1;
static int hf_v2giso2_iso2SalesTariffEntryType_EPriceLevel = -1;

static int hf_v2giso2_iso1RelativeTimeIntervalType_start = -1;
static int hf_v2giso2_iso1RelativeTimeIntervalType_duration = -1;

static int hf_v2giso2_iso2CostType_costKind = -1;
static int hf_v2giso2_iso2CostType_amount = -1;
static int hf_v2giso2_iso2CostType_amountMultiplier = -1;
static int hf_v2giso2_iso2ChargeParameterDiscoveryResType_EVSEStatus_EnergyTransferParameter = -1;

static int hf_v2giso2_target_energy = -1;
static int hf_v2giso2_iso2CurrentRange = -1;
static int hf_v2giso2_iso2CurrentSOC = -1;
static int hf_v2giso2_iso2TargetSOC = -1;
static int hf_v2giso2_iso2BulkSOC = -1;
static int hf_v2giso2_iso2MinimumSOC = -1;
static int hf_v2giso2_iso2RemainingTimeToTargetSOC = -1;
static int hf_v2giso2_iso2RemainingTimeToBulkSOC_isUsed = -1;
static int hf_v2giso2_iso2RemainingTimeToMinimumSOC = -1;
static int hf_v2giso2_ChargingComplete = -1;
static int hf_v2giso2_BulkChargingComplete = -1;
static int hf_v2giso2_InletHot = -1;
static int hf_v2giso2_iso2PaymentServiceSelectionResType_ResponseCode = -1;
static int hf_v2giso2_iso2ServiceDiscoveryResType_ResponseCode = -1;
static int hf_v2giso2_iso2ServiceType_ServiceID = -1;
static int hf_v2giso2_iso2ServiceType_FreeService = -1;
static int hf_v2giso2_iso2PaymentOptionListType_PaymentOption = -1;

static int hf_v2giso2_iso2ProfileEntryType_ChargingProfileEntryStart = -1;
static int hf_v2giso2_iso2ProfileEntryType_ChargingProfileEntryMaxNumberOfPhasesInUse = -1;

static dissector_handle_t v2g_handle;

/* Dissector Handle */
static int proto_v2gexi = -1;

/* Helper Function */

/**
 * @brief raise the value to the power of the exponent given in the physicalvalue struct.
 *
 * @param physicalvalue struct containing the value `value field` and the exponent `exponent field`.
 * @return double - the calculated value.
 */
static inline double
v2giso2_physicalvalue_to_double(
    iso2PhysicalValueType *physicalvalue)
{
    double value;
    int32_t exponent;

    value = (double)physicalvalue->Value;
    exponent = physicalvalue->Exponent;
    if (exponent > 0)
    {
        for (; exponent != 0; exponent--)
        {
            value *= 10.0;
        }
    }
    if (exponent < 0)
    {
        for (; exponent != 0; exponent++)
        {
            value /= 10.0;
        }
    }

    return value;
}

/**
 * @brief A function to add a string to a proto_tree.
 *
 * @param tree  The proto_tree to add the string to.
 * @param hfindex   The header field index.
 * @param tvb   tvb pointer to the packet data.
 * @param characterstree   The tree containing the string.
 * @param characterslen   The length of the string.
 * @param charactersmaxsize  The maximum size of the string.
 */
static inline void
exi_add_characters(proto_tree *tree,
                   int hfindex,
                   tvbuff_t *tvb,
                   const exi_string_character_t *characters,
                   unsigned int characterslen,
                   size_t charactersmaxsize)
{
    unsigned int i;
    char *str;
    proto_item *it;

    if (characterslen > charactersmaxsize)
    {
        proto_tree_add_debug_text(tree,
                                  "characterslen %u > maxsize %zu",
                                  characterslen, charactersmaxsize);
        return;
    }

    str = alloca(characterslen + 1);
    if (str == NULL)
    {
        return;
    }

    for (i = 0; i < characterslen; i++)
    {
        str[i] = characters[i];
    }
    str[i] = '\0';

    /*
     * internally the proto string is a g_strdup - so, it's ok
     * to use the alloca stack reference from above
     */
    it = proto_tree_add_string(tree, hfindex, tvb, 0, 0, str);
    proto_item_set_generated(it);

    return;
}

/**
 * @brief A function to add a string bytes to a proto_tree.
 *
 * @param tree  The proto_tree to add the string to.
 * @param hfindex   The header field index.
 * @param tvb   tvb pointer to the packet data.
 * @param bytes     The bytes to add to the tree.
 * @param byteslen  The length of the bytes.
 * @param bytesmaxsize  The maximum size of the bytes.
 */
static inline void
exi_add_bytes(proto_tree *tree,
              int hfindex,
              tvbuff_t *tvb,
              const uint8_t *bytes,
              unsigned int byteslen,
              size_t bytesmaxsize)
{
    unsigned int i;
    char *str;
    proto_item *it;

    if (byteslen > bytesmaxsize)
    {
        // Check For Error
        /*Useful for quick debugging. Also sends string to STDOUT, so don't
        leave call to this function in production code.*/
        proto_tree_add_debug_text(tree, "byteslen %u > maxsize %zu",
                                  byteslen, bytesmaxsize);
        return;
    }

    str = alloca(2 * byteslen + 1);
    if (str == NULL)
    { // Memory not allocated
        return;
    }

    for (i = 0; i < byteslen; i++)
    { // Translates bytes of data into a string to be displayed
        snprintf(&str[2 * i], bytesmaxsize - 2 * i, "%02X" /*Takes to Hexdecimal digits to form a char*/, bytes[i]);
    }
    str[2 * i] = '\0';

    /*
     * internally the proto string is a g_strdup - so, it's ok
     * to use the alloca stack reference from above
     */
    it = proto_tree_add_string(tree, hfindex, tvb, 0, 0, str);
    proto_item_set_generated(it);

    return;
}
/**
 * @brief A function to add a string bytes to a proto_tree.
 *
 * @param chargingprofile   The chargingprofile struct to dissect.
 * @param tvb   tvb pointer to the packet data.
 * @param pinfo  packet info struct.
 * @param tree  The proto_tree to add the string to.
 * @param idx   The index of the chargingprofile.
 * @param subtree_name  The name of the subtree.
 */
static void
dissect_v2giso2_chargingprofile(
    iso2ChargingProfileType *chargingprofile,
    tvbuff_t *tvb,
    proto_tree *tree,
    gint idx,
    const char *subtree_name)
{
    unsigned int i;
    proto_tree *subtree;
    proto_tree *profileentry_tree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0,
                                     idx, NULL, subtree_name);

    profileentry_tree = proto_tree_add_subtree(subtree,
                                               tvb, 0, 0, ett_v2giso2_array, NULL, "ProfileEntry");
    for (i = 0; i < chargingprofile->ProfileEntry.arrayLen; i++)
    {
        char index[sizeof("[65536]")];

        snprintf(index, sizeof(index), "[%u]", i);
        dissect_v2giso2_PMaxScheduleEntry(
            profileentry_tree, tvb,
            &chargingprofile->ProfileEntry.array[i],
            index);
    }

    return;
}

/*-----------------------------Dissecting Functions--------------------------------------*/
/**
 * @brief Dissect the iso2MessageHeaderType.
 *
 * @param header  The iso2MessageHeaderType struct to dissect.
 * @param tvb   tvb pointer to the packet data.
 * @param pinfo Pointer to the packet info.
 * @param tree  The proto_tree to add the dissected data to.
 * @param idx   The index of the subtree.
 * @param subtree_name  The name of the subtree created for this dissector.
 */
static void
dissect_v2giso2_message_header(const iso2MessageHeaderType *header,
                               tvbuff_t *tvb,
                               packet_info *pinfo,
                               proto_tree *tree,
                               gint idx,
                               const char *subtree_name)
{
    proto_tree *subtree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, idx, NULL, subtree_name);

    exi_add_bytes(subtree,
                  hf_v2giso2_MessageHeaderType_SessionID,
                  tvb,
                  header->SessionID.bytes,
                  header->SessionID.bytesLen,
                  sizeof(header->SessionID.bytes));

    if (header->Signature_isUsed)
    {
        dissect_v2giso2_signature(
            &header->Signature, tvb, pinfo, subtree,
            ett_v2giso2_iso2SignatureType,
            "Signature");
    }

    return;
}
/**
 * @brief Dissect the iso2SignatureType.
 *
 * @param signature  The iso2SignatureType struct to dissect.
 * @param tvb   tvb pointer to the packet data.
 * @param pinfo     Pointer to the packet info.
 * @param tree  The proto_tree to add the dissected data to.
 * @param idx       The index of the subtree.
 * @param subtree_name  The name of the subtree created for this dissector.
 */
static void
dissect_v2giso2_signature(const iso2SignatureType *signature,
                          tvbuff_t *tvb,
                          packet_info *pinfo,
                          proto_tree *tree,
                          gint idx,
                          const char *subtree_name)
{
    // unsigned int i;
    proto_tree *subtree;
    // proto_tree *object_tree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, idx, NULL, subtree_name);

    if (signature->Id_isUsed)
    {
        exi_add_characters(subtree,
                           hf_v2giso2_SignatureType_Id,
                           tvb,
                           signature->Id.characters,
                           signature->Id.charactersLen,
                           sizeof(signature->Id.characters));
    }

    dissect_v2giso2_signedinfo(&signature->SignedInfo,
                               tvb, pinfo, subtree,
                               ett_v2giso2_iso2SignedInfoType, "SignedInfo");

    dissect_v2giso2_signaturevalue(&signature->SignatureValue,
                                   tvb, pinfo, subtree,
                                   ett_v2giso2_iso2SignatureValueType, "SignatureValue");

    return;
}

/**
 * @brief Dissector for the iso2MeterInfoType struct.
 *
 * @param meterinfo struct to dissect
 * @param tvb pointer to the packet data
 * @param tree pointer to the tree to add the dissected data to.
 * @param idx  index of the subtree
 * @param subtree_name name of the subtree created for this dissector.
 */
static void
dissect_v2giso2_meterinfo(iso2MeterInfoType *meterinfo, tvbuff_t *tvb, proto_tree *tree, gint idx, const char *subtree_name)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0,
                                     idx, NULL, subtree_name);

    exi_add_characters(subtree,
                       hf_v2giso2_iso2MeterInfoType_MeterID,
                       tvb,
                       meterinfo->MeterID.characters,
                       meterinfo->MeterID.charactersLen,
                       sizeof(meterinfo->MeterID.characters));

    if (meterinfo->MeterReadingCharged_isUsed)
    {
        it = proto_tree_add_uint64(subtree,
                                   hf_v2giso2_iso2MeterInfoType_MeterReadingCharged,
                                   tvb, 0, 0, meterinfo->MeterReadingCharged);
        proto_item_set_generated(it);
    }

    if (meterinfo->MeterReadingDischarged_isUsed)
    {
        it = proto_tree_add_uint64(subtree,
                                   hf_v2giso2_iso2MeterInfoType_MeterReadingDischarged,
                                   tvb, 0, 0, meterinfo->MeterReadingDischarged);
        proto_item_set_generated(it);
    }

    if (meterinfo->SigMeterReading_isUsed)
    {
        exi_add_bytes(subtree,
                      hf_v2giso2_iso2MeterInfoType_SigMeterReading,
                      tvb,
                      meterinfo->SigMeterReading.bytes,
                      meterinfo->SigMeterReading.bytesLen,
                      sizeof(meterinfo->SigMeterReading.bytes));
    }

    if (meterinfo->MeterStatus_isUsed)
    {
        it = proto_tree_add_int(subtree,
                                hf_v2giso2_iso2MeterInfoType_MeterStatus,
                                tvb, 0, 0, meterinfo->MeterStatus);
        proto_item_set_generated(it);
    }

    if (meterinfo->TMeter_isUsed)
    {
        it = proto_tree_add_int64(subtree,
                                  hf_v2giso2_iso2MeterInfoType_TMeter,
                                  tvb, 0, 0, meterinfo->TMeter);
        proto_item_set_generated(it);
    }

    return;
}

/**
 * @brief Dissector for the iso2MeteringReceiptReqType struct.
 *
 * @param tree  pointer to the tree to add the dissected data to.
 * @param tvb   pointer to the packet data.
 * @param msg   the struct to dissect.
 */
static void
dissect_v2gexi_handshake(proto_tree *tree, tvbuff_t *tvb, appHandEXIDocument *msg)
{

    if (msg->supportedAppProtocolReq_isUsed)
    {
        dissect_v2gexi_supportedappprotocolreq(tree, tvb, &msg->supportedAppProtocolReq);
    }
    else if (msg->supportedAppProtocolRes_isUsed)
    {
        dissect_v2gexi_supportedappprotocolres(tree, tvb, &msg->supportedAppProtocolReq);
    }

    return;
}

/**
 * @brief Dissector for the iso2MeteringReceiptReqType struct.
 *
 * @param tree  pointer to the tree to add the dissected data to.
 * @param tvb   pointer to the packet data.
 * @param msg   the struct to dissect.
 */
static void
dissect_v2gexi_supportedappprotocolreq(proto_tree *tree, tvbuff_t *tvb, appHandAnonType_supportedAppProtocolReq *msg)
{
    proto_tree *supported_app_protocol_req_type_subtree = proto_tree_add_subtree(tree,
                                                                                 tvb, 0, 0, ett_v2gexi, NULL, "Supported App Protocol Request");
    for (int i = 0; i < msg->AppProtocol.arrayLen; i++)
    {
        char index[sizeof("[65536]")];
        snprintf(index, sizeof(index), "[%u]", i);
        dissect_v2gexi_apphandappprotocoltype(supported_app_protocol_req_type_subtree, tvb, &msg->AppProtocol.array[i], index);
    }
    return;
}

/**
 * @brief Dissector for the iso2MeteringReceiptReqType struct.
 *
 * @param tree   pointer to the tree to add the dissected data to.
 * @param tvb    pointer to the packet data.
 * @param msg   the struct to dissect.
 */
static void
dissect_v2gexi_supportedappprotocolres(proto_tree *tree, tvbuff_t *tvb, appHandAnonType_supportedAppProtocolRes *msg)
{
    proto_item *it;
    proto_tree *supported_app_protocol_res_type_subtree = proto_tree_add_subtree(tree,
                                                                                 tvb, 0, 0, ett_v2gexi, NULL, "Supported App Protocol Response");

    it = proto_tree_add_uint(supported_app_protocol_res_type_subtree,
                             hf_v2gexi_struct_supportedAppProtocolRes_ResponseCode,
                             tvb, 0, 0,
                             msg->ResponseCode);
    proto_item_set_generated(it);

    if (msg->SchemaID_isUsed)
    {
        guint schemaid;

        schemaid = msg->SchemaID;

        it = proto_tree_add_uint(supported_app_protocol_res_type_subtree,
                                 hf_v2gexi_struct_supportedAppProtocolRes_SchemaID,
                                 tvb, 0, 0,
                                 msg->SchemaID);
        proto_item_set_generated(it);
    }
    return;
}

/**
 * @brief Dissector for the iso2MeteringReceiptReqType struct.
 *
 * @param tree  pointer to the tree to add the dissected data to.
 * @param tvb   pointer to the packet data.
 * @param msg   the struct to dissect.
 * @param subtree_name  the name of the subtree to add the dissected data to.
 */
static void
dissect_v2gexi_apphandappprotocoltype(proto_tree *tree, tvbuff_t *tvb, appHandAppProtocolType *msg, const char *subtree_name)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL, subtree_name);

    exi_add_characters(subtree,
                       hf_v2gexi_struct_appHandAppProtocolType_ProtocolNamespace,
                       tvb, msg->ProtocolNamespace.characters, msg->ProtocolNamespace.charactersLen,
                       sizeof(msg->ProtocolNamespace.characters));

    it = proto_tree_add_uint(subtree,
                             hf_v2gexi_struct_appHandAppProtocolType_VersionNumberMajor,
                             tvb, 0, 0, msg->VersionNumberMajor);
    proto_item_set_generated(it);
    it = proto_tree_add_uint(subtree,
                             hf_v2gexi_struct_appHandAppProtocolType_VersionNumberMinor,
                             tvb, 0, 0, msg->VersionNumberMinor);
    proto_item_set_generated(it);

    it = proto_tree_add_uint(subtree,
                             hf_v2gexi_struct_appHandAppProtocolType_SchemaID,
                             tvb, 0, 0, msg->SchemaID);
    proto_item_set_generated(it);

    it = proto_tree_add_uint(subtree,
                             hf_v2gexi_struct_appHandAppProtocolType_Priority,
                             tvb, 0, 0, msg->Priority);
    proto_item_set_generated(it);
    return;
}

/**
 * @brief Dissector for the iso2MeteringReceiptReqType struct.
 *
 * @param signedinfo    the struct to dissect.
 * @param tvb        pointer to the packet data.
 * @param pinfo     pointer to the packet info.
 * @param tree    pointer to the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to add the dissected data to.
 */
static void
dissect_v2giso2_signedinfo(const iso2SignedInfoType *signedinfo,
                           tvbuff_t *tvb,
                           packet_info *pinfo,
                           proto_tree *tree,
                           gint idx,
                           const char *subtree_name)
{
    unsigned int i;
    proto_tree *subtree;
    proto_tree *reference_tree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, idx, NULL, subtree_name);

    if (signedinfo->Id_isUsed)
    {
        exi_add_characters(subtree,
                           hf_v2giso2_SignedInfoType_Id,
                           tvb,
                           signedinfo->Id.characters,
                           signedinfo->Id.charactersLen,
                           sizeof(signedinfo->Id.characters));
    }

    dissect_v2giso2_canonicalizationmethod(
        &signedinfo->CanonicalizationMethod,
        tvb, pinfo, subtree,
        ett_v2giso2_iso2CanonicalizationMethodType,
        "CanonicalizationMethod");

    dissect_v2giso2_signaturemethod(
        &signedinfo->SignatureMethod,
        tvb, pinfo, subtree,
        ett_v2giso2_iso2SignatureMethodType,
        "SignatureMethod");

    reference_tree = proto_tree_add_subtree(subtree, tvb, 0, 0, ett_v2giso2_array, NULL, "Reference");
    for (i = 0; i < signedinfo->Reference.arrayLen; i++)
    {
        char index[sizeof("[65536]")];

        snprintf(index, sizeof(index), "[%u]", i);
        dissect_v2giso2_reference(&signedinfo->Reference.array[i],
                                  tvb, pinfo, reference_tree,
                                  ett_v2giso2_iso2ReferenceType, index);
    }
    return;
}

/**
 * @brief   Dissector for the iso2SignatureValueType struct.
 *
 * @param signaturevalue    the struct to dissect.
 * @param tvb     pointer to the packet data.
 * @param _U_   pointer to the packet info.
 * @param tree   pointer to the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to add the dissected data to.
 */
static void
dissect_v2giso2_signaturevalue(
    const iso2SignatureValueType *signaturevalue,
    tvbuff_t *tvb,
    packet_info *pinfo _U_,
    proto_tree *tree,
    gint idx,
    const char *subtree_name)
{
    proto_tree *subtree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, idx, NULL, subtree_name);

    if (signaturevalue->Id_isUsed)
    {
        exi_add_characters(subtree,
                           hf_v2giso2_SignatureValueType_Id,
                           tvb,
                           signaturevalue->Id.characters,
                           signaturevalue->Id.charactersLen,
                           sizeof(signaturevalue->Id.characters));
    }

    exi_add_bytes(subtree,
                  hf_v2giso2_SignatureValueType_CONTENT,
                  tvb,
                  signaturevalue->CONTENT.bytes,
                  signaturevalue->CONTENT.bytesLen,
                  sizeof(signaturevalue->CONTENT.bytes));

    return;
}

/**
 * @brief  Dissector for the iso2SignatureType struct.
 *
 * @param reference     the struct to dissect.
 * @param tvb     pointer to the packet data.
 * @param pinfo     pointer to the packet info.
 * @param tree   pointer to the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to add the dissected data to.
 */
static void
dissect_v2giso2_reference(const iso2ReferenceType *reference,
                          tvbuff_t *tvb,
                          packet_info *pinfo,
                          proto_tree *tree,
                          gint idx,
                          const char *subtree_name)
{
    proto_tree *subtree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, idx, NULL, subtree_name);

    if (reference->Id_isUsed)
    {
        exi_add_characters(subtree,
                           hf_v2giso2_ReferenceType_Id,
                           tvb,
                           reference->Id.characters,
                           reference->Id.charactersLen,
                           sizeof(reference->Id.characters));
    }
    if (reference->URI_isUsed)
    {
        exi_add_characters(subtree,
                           hf_v2giso2_ReferenceType_URI,
                           tvb,
                           reference->URI.characters,
                           reference->URI.charactersLen,
                           sizeof(reference->URI.characters));
    }
    if (reference->Type_isUsed)
    {
        exi_add_characters(subtree,
                           hf_v2giso2_ReferenceType_Type,
                           tvb,
                           reference->Type.characters,
                           reference->Type.charactersLen,
                           sizeof(reference->Type.characters));
    }
    if (reference->Transforms_isUsed)
    {
        dissect_v2giso2_transforms(&reference->Transforms,
                                   tvb, pinfo, subtree,
                                   ett_v2giso2_iso2TransformsType,
                                   "Transforms");
    }

    dissect_v2giso2_digestmethod(&reference->DigestMethod,
                                 tvb, pinfo, subtree,
                                 ett_v2giso2_iso2DigestMethodType,
                                 "DigestMethod");

    exi_add_bytes(subtree,
                  hf_v2giso2_ReferenceType_DigestValue,
                  tvb,
                  reference->DigestValue.bytes,
                  reference->DigestValue.bytesLen,
                  sizeof(reference->DigestValue.bytes));

    return;
}

/**
 * @brief Dissector for the iso2TransformsType struct.
 *
 * @param transforms    the struct to dissect.
 * @param tvb   pointer to the packet data.
 * @param pinfo     pointer to the packet info.
 * @param tree  pointer to the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to add the dissected data to.
 */
static void
dissect_v2giso2_transforms(const iso2TransformsType *transforms,
                           tvbuff_t *tvb,
                           packet_info *pinfo,
                           proto_tree *tree,
                           gint idx,
                           const char *subtree_name)
{
    unsigned int i;
    proto_tree *subtree;
    proto_tree *transform_tree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, idx, NULL, subtree_name);

    transform_tree = proto_tree_add_subtree(subtree, tvb, 0, 0, ett_v2giso2_array, NULL, "Transform");
    for (i = 0; i < transforms->Transform.arrayLen; i++)
    {
        char index[sizeof("[65536]")];

        snprintf(index, sizeof(index), "[%u]", i);
        dissect_v2giso2_transform(&transforms->Transform.array[i],
                                  tvb, pinfo, transform_tree,
                                  ett_v2giso2_iso2TransformType, index);
    }

    return;
}

/**
 * @brief Dissector for the iso2TransformType struct.
 *
 * @param transform     the struct to dissect.
 * @param tvb   pointer to the packet data.
 * @param _U_   pointer to the packet info.
 * @param tree  pointer to the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to add the dissected data to.
 */
static void
dissect_v2giso2_transform(const iso2TransformType *transform,
                          tvbuff_t *tvb,
                          packet_info *pinfo _U_,
                          proto_tree *tree,
                          gint idx,
                          const char *subtree_name)
{
    unsigned int i;
    proto_tree *subtree;
    proto_tree *xpath_tree;
    proto_tree *xpath_i_tree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, idx, NULL, subtree_name);

    exi_add_characters(subtree,
                       hf_v2giso2_TransformType_Algorithm,
                       tvb,
                       transform->Algorithm.characters,
                       transform->Algorithm.charactersLen,
                       sizeof(transform->Algorithm.characters));

    if (transform->ANY_isUsed)
    {
        exi_add_characters(subtree,
                           hf_v2giso2_TransformType_ANY,
                           tvb,
                           transform->ANY.characters,
                           transform->ANY.charactersLen,
                           sizeof(transform->ANY.characters));
    }

    xpath_tree = proto_tree_add_subtree(subtree, tvb, 0, 0, ett_v2giso2_array, NULL, "XPath");
    for (i = 0; i < transform->XPath.arrayLen; i++)
    {
        xpath_i_tree = proto_tree_add_subtree_format(xpath_tree, tvb, 0, 0, ett_v2giso2_array_i, NULL, "[%u]", i);
        exi_add_characters(xpath_i_tree,
                           hf_v2giso2_TransformType_XPath,
                           tvb,
                           transform->XPath.array[i].characters,
                           transform->XPath.array[i].charactersLen,
                           sizeof(transform->XPath.array[i].characters));
    }

    return;
}

/**
 * @brief Dissector for the iso2DigestMethodType struct.
 *
 * @param digestmethod  the struct to dissect.
 * @param tvb   pointer to the packet data.
 * @param _U_   pointer to the packet info.
 * @param tree  pointer to the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to add the dissected data to.
 */
static void
dissect_v2giso2_digestmethod(const iso2DigestMethodType *digestmethod,
                             tvbuff_t *tvb,
                             packet_info *pinfo _U_,
                             proto_tree *tree,
                             gint idx,
                             const char *subtree_name)
{
    proto_tree *subtree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, idx, NULL, subtree_name);

    exi_add_characters(subtree,
                       hf_v2giso2_DigestMethodType_Algorithm,
                       tvb,
                       digestmethod->Algorithm.characters,
                       digestmethod->Algorithm.charactersLen,
                       sizeof(digestmethod->Algorithm.characters));

    if (digestmethod->ANY_isUsed)
    {
        exi_add_characters(subtree,
                           hf_v2giso2_DigestMethodType_ANY,
                           tvb,
                           digestmethod->ANY.characters,
                           digestmethod->ANY.charactersLen,
                           sizeof(digestmethod->ANY.characters));
    }

    return;
}

/**
 * @brief Dissector for the iso2SignatureValueType struct.
 *
 * @param canonicalizationmethod    the struct to dissect.
 * @param tvb   pointer to the packet data.
 * @param _U_   pointer to the packet info.
 * @param tree  pointer to the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to add the dissected data to.
 */
static void
dissect_v2giso2_canonicalizationmethod(
    const iso2CanonicalizationMethodType *canonicalizationmethod,
    tvbuff_t *tvb,
    packet_info *pinfo _U_,
    proto_tree *tree,
    gint idx,
    const char *subtree_name)
{
    proto_tree *subtree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, idx, NULL, subtree_name);

    exi_add_characters(subtree,
                       hf_v2giso2_CanonicalizationMethodType_Algorithm,
                       tvb,
                       canonicalizationmethod->Algorithm.characters,
                       canonicalizationmethod->Algorithm.charactersLen,
                       sizeof(canonicalizationmethod->Algorithm.characters));

    if (canonicalizationmethod->ANY_isUsed)
    {
        exi_add_characters(subtree,
                           hf_v2giso2_CanonicalizationMethodType_ANY,
                           tvb,
                           canonicalizationmethod->ANY.characters,
                           canonicalizationmethod->ANY.charactersLen,
                           sizeof(canonicalizationmethod->ANY.characters));
    }

    return;
}
/**
 * @brief Dissector for the iso2SignatureValueType struct.
 *
 * @param signaturemethod  the struct to dissect.
 * @param tvb   pointer to the packet data.
 * @param _U_   pointer to the packet info.
 * @param tree  pointer to the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to add the dissected data to.
 */
static void
dissect_v2giso2_signaturemethod(
    const iso2SignatureMethodType *signaturemethod,
    tvbuff_t *tvb,
    packet_info *pinfo _U_,
    proto_tree *tree,
    gint idx,
    const char *subtree_name)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, idx, NULL, subtree_name);

    exi_add_characters(subtree,
                       hf_v2giso2_SignatureMethodType_Algorithm,
                       tvb,
                       signaturemethod->Algorithm.characters,
                       signaturemethod->Algorithm.charactersLen,
                       sizeof(signaturemethod->Algorithm.characters));

    if (signaturemethod->HMACOutputLength_isUsed)
    {
        it = proto_tree_add_int64(subtree,
                                  hf_v2giso2_SignatureMethodType_HMACOutputLength,
                                  tvb, 0, 0, signaturemethod->HMACOutputLength);
        proto_item_set_generated(it);
    }

    if (signaturemethod->ANY_isUsed)
    {
        exi_add_characters(subtree,
                           hf_v2giso2_SignatureMethodType_ANY,
                           tvb,
                           signaturemethod->ANY.characters,
                           signaturemethod->ANY.charactersLen,
                           sizeof(signaturemethod->ANY.characters));
    }

    return;
}
/**
 * @brief   Dissector for the iso2SignatureValueType struct.
 *
 * @param tree  pointer to the tree to add the dissected data to.
 * @param tvb   pointer to the packet data.
 * @param msg   the struct to dissect.
 */
static void
dissect_iso2PaymentDetailsResType(proto_tree *tree, tvbuff_t *tvb,
                                  iso2PaymentDetailsResType *msg)
{
    proto_tree *payment_details_res_type_subtree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL, "Payment Details Response");
    proto_item *it;
    it = proto_tree_add_uint(payment_details_res_type_subtree, hf_v2giso2_iso2PaymentDetailsResType_ResponseCode,
                             tvb, 0, 0, msg->ResponseCode);
    proto_item_set_generated(it);
    /*Checks For errors and puts the string produced from packet in the tree*/
    exi_add_bytes(payment_details_res_type_subtree,
                  hf_v2giso2_iso2PaymentDetailsResType_GenChallenge,
                  tvb,
                  msg->GenChallenge.bytes,
                  msg->GenChallenge.bytesLen,
                  sizeof(msg->GenChallenge.bytes));
    it = proto_tree_add_int64(payment_details_res_type_subtree,
                              hf_v2giso2_iso2PaymentDetailsResType_EVSETimeStamp, tvb, 0, 0, msg->EVSETimeStamp);
    proto_item_set_generated(it);
    if (msg->EVSEStatus_isUsed)
    {
        it = proto_tree_add_int(payment_details_res_type_subtree,
                                hf_v2giso2_iso2PaymentDetailsResType_EVSEStatus_NotificationMaxDelay, tvb, 0, 0, msg->EVSEStatus.NotificationMaxDelay);
        proto_item_set_generated(it);
        it = proto_tree_add_int(payment_details_res_type_subtree,
                                hf_v2giso2_iso2PaymentDetailsResType_EVSEStatus_EVSENotification, tvb, 0, 0, msg->EVSEStatus.EVSENotification);
        proto_item_set_generated(it);
    }

    return;
}

/**
 * @brief Dissector for the iso2SessionSetupReqType struct.
 *
 * @param tree  pointer to the tree to add the dissected data to.
 * @param tvb   pointer to the packet data.
 * @param msg   the struct to dissect.
 */
static void
dissect_iso2SessionSetupReqType(proto_tree *tree, tvbuff_t *tvb,
                                iso2SessionSetupReqType *msg)
{
    proto_tree *session_setup_req_type_subtree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL, "Session Setup Request");

    exi_add_bytes(session_setup_req_type_subtree,
                  hf_v2giso2_iso2SessionSetupReqType_EVCCID, tvb, msg->EVCCID.bytes, msg->EVCCID.bytesLen, sizeof(msg->EVCCID.bytes));

    return;
}

/**
 * @brief Dissector for the iso2SessionSetupResType struct.
 *
 * @param res   pointer to the struct to dissect
 * @param tvb   pointer to the packet data.
 * @param tree  pointer to the tree to add the dissected data to.
 * @param idx   index of the subtree to add the dissected data to.
 */
static void
dissect_v2giso2_CurrentDemandResType(iso2CurrentDemandResType *res, tvbuff_t *tvb,
                                     proto_tree *tree, gint idx)
{
    proto_tree *subtree;
    proto_item *it;
    double value;
    subtree = proto_tree_add_subtree(tree,
                                     tvb, 0, -1, idx, NULL, "Current Demand Response");
    it = proto_tree_add_uint(subtree,
                             hf_v2giso2_iso2CurrentDemandResType_ResponseCode,
                             tvb, 0, 0, res->ResponseCode);
    proto_item_set_generated(it);
    if (res->EVSEStatus_isUsed)
    {
        dissect_v2giso2_evsestatus(&res->EVSEStatus, tvb, subtree, ett_v2giso2_iso2DC_EVSEStatusType, "EVSEStatus");
    }

    dissect_v2giso2_Physicalvalue(
        subtree, tvb,
        &res->EVSEPresentVoltage,
        "EVSEPresentVoltage");
    value = v2giso2_physicalvalue_to_double(&res->EVSEPresentVoltage);
    it = proto_tree_add_double(subtree,
                               hf_v2giso2_present_voltage,
                               tvb, 0, 0, value);
    proto_item_set_generated(it);

    dissect_v2giso2_Physicalvalue(
        subtree, tvb,
        &res->EVSEPresentCurrent,
        "EVSEPresentCurrent");
    value = v2giso2_physicalvalue_to_double(&res->EVSEPresentCurrent);
    it = proto_tree_add_double(subtree,
                               hf_v2giso2_present_current,
                               tvb, 0, 0, value);
    proto_item_set_generated(it);

    it = proto_tree_add_int(subtree,
                            hf_v2giso2_iso2CurrentDemandResType_EVSECurrentLimitAchieved,
                            tvb, 0, 0, res->EVSECurrentLimitAchieved);
    proto_item_set_generated(it);

    it = proto_tree_add_int(subtree,
                            hf_v2giso2_iso2CurrentDemandResType_EVSEVoltageLimitAchieved,
                            tvb, 0, 0, res->EVSEVoltageLimitAchieved);
    proto_item_set_generated(it);

    it = proto_tree_add_int(subtree,
                            hf_v2giso2_iso2CurrentDemandResType_EVSEPowerLimitAchieved,
                            tvb, 0, 0, res->EVSEPowerLimitAchieved);
    proto_item_set_generated(it);

    if (res->EVSEMaximumVoltage_isUsed)
    {
        dissect_v2giso2_Physicalvalue(
            subtree, tvb,
            &res->EVSEMaximumVoltage,
            "EVSEMaximumVoltageLimit");
    }
    if (res->EVSEMaximumCurrent_isUsed)
    {
        dissect_v2giso2_Physicalvalue(
            subtree, tvb,
            &res->EVSEMaximumCurrent,
            "EVSEMaximumCurrentLimit");
    }
    if (res->EVSEMaximumPower_isUsed)
    {
        dissect_v2giso2_Physicalvalue(
            subtree, tvb,
            &res->EVSEMaximumPower,
            "EVSEMaximumPowerLimit");
    }

    exi_add_characters(subtree,
                       hf_v2giso2_iso2CurrentDemandResType_EVSEID,
                       tvb,
                       res->EVSEID.characters,
                       res->EVSEID.charactersLen,
                       sizeof(res->EVSEID.characters));
    if (res->SAScheduleTupleID_isUsed)
    {
        it = proto_tree_add_uint(subtree,
                                 hf_v2giso2_iso2CurrentDemandResType_SAScheduleTupleID,
                                 tvb, 0, 0, res->SAScheduleTupleID);
        proto_item_set_generated(it);
    }
    if (res->MeterInfo_isUsed)
    {
        dissect_v2giso2_meterinfo(
            &res->MeterInfo,
            tvb, subtree,
            ett_v2giso2_iso2MeterInfoType,
            "MeterInfo");
    }

    if (res->ReceiptRequired_isUsed)
    {
        it = proto_tree_add_int(subtree,
                                hf_v2giso2_iso2CurrentDemandResType_ReceiptRequired,
                                tvb, 0, 0, res->ReceiptRequired);
        proto_item_set_generated(it);
    }

    return;
}

/**
 * @brief  Dissector for the iso2SessionSetupResType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2SessionSetupResType struct to dissect.
 */
static void
dissect_iso2SessionSetupResType(proto_tree *tree, tvbuff_t *tvb,
                                iso2SessionSetupResType *msg)
{
    proto_tree *session_setup_res_type_subtree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL, "Session Setup Response");

    proto_item *it;

    it = proto_tree_add_uint(session_setup_res_type_subtree,
                             hf_v2giso2_iso2SessionSetupResType_ResponseCode, tvb, 0, 0, msg->ResponseCode);
    proto_item_set_generated(it);

    exi_add_characters(session_setup_res_type_subtree, hf_v2giso2_iso2SessionSetupResType_EVSEID,
                       tvb, msg->EVSEID.characters, msg->EVSEID.charactersLen, sizeof(msg->EVSEID.characters));

    if (msg->EVSETimeStamp_isUsed)
    {
        it = proto_tree_add_int64(session_setup_res_type_subtree,
                                  hf_v2giso2_iso2SessionSetupResType_EVSETimeStamp, tvb, 0, 0, msg->EVSETimeStamp);
        proto_item_set_generated(it);
    }
    if (msg->EVSEStatus_isUsed)
    {
        dissect_v2giso2_evsestatus(&msg->EVSEStatus, tvb, session_setup_res_type_subtree, ett_v2gexi, "EVSEStatus");
    }

    return;
}

/**
 * @brief Dissector for the iso2SessionSetupReqType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2SessionSetupReqType struct to dissect.
 */
static void
dissect_v2giso2_PowerDeliveryReqType(proto_tree *tree, tvbuff_t *tvb,
                                     iso2PowerDeliveryReqType *msg)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree,
                                     tvb, 0, 0, ett_v2giso2_iso2PowerDeliveryReqType, NULL, "Power Delivery Request");

    it = proto_tree_add_uint(subtree,
                             hf_v2giso2_iso2PowerDeliveryReqType_ChargeProgress,
                             tvb, 0, 0, msg->ChargeProgress);
    proto_item_set_generated(it);

    if (msg->EVOperation_isUsed)
    {
        it = proto_tree_add_uint(subtree,
                                 hf_v2giso2_iso2PowerDeliveryReqType_EVOperation,
                                 tvb, 0, 0, msg->EVOperation);
        proto_item_set_generated(it);
    }
    if (msg->SAScheduleTupleID_isUsed)
    {
        it = proto_tree_add_uint(subtree,
                                 hf_v2giso2_iso2PowerDeliveryReqType_SAScheduleTupleID,
                                 tvb, 0, 0, msg->SAScheduleTupleID);
        proto_item_set_generated(it);
    }
    if (msg->ChargingProfile_isUsed)
    {
        dissect_v2giso2_chargingprofile(
            &msg->ChargingProfile,
            tvb, subtree,
            ett_v2giso2_iso2ChargingProfileType,
            "ChargingProfile");
    }

    return;
}

/**
 * @brief Dissector for the iso2PowerDeliveryResType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2PowerDeliveryResType struct to dissect.
 */
static void
dissect_v2giso2_PowerDeliveryRes(proto_tree *tree, tvbuff_t *tvb,
                                 iso2PowerDeliveryResType *msg)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL, "Power Delivery Response");

    it = proto_tree_add_uint(subtree, hf_v2giso2_iso2PowerDeliveryResType_ResponseCode,
                             tvb, 0, 0, msg->ResponseCode);
    proto_item_set_generated(it);

    if (msg->EVSEStatus_isUsed)
    {
        dissect_v2giso2_evsestatus(&msg->EVSEStatus, tvb, subtree, ett_v2gexi, "EVSEStatus");
    }
    it = proto_tree_add_uint(subtree, hf_v2giso2_iso2PowerDeliveryResType_EVSEProcessing,
                             tvb, 0, 0, msg->EVSEProcessing);
    proto_item_set_generated(it);
    return;
}

/**
 * @brief Dissector for the iso2AuthorizationReqType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2AuthorizationReqType struct to dissect.
 */
static void
dissect_v2giso2_AuthorizationReq(proto_tree *tree, tvbuff_t *tvb,
                                 iso2AuthorizationReqType *msg)
{
    proto_tree *authorization_req_type;

    authorization_req_type = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL, "Authorization Request");

    if (msg->Id_isUsed)
    {
        exi_add_characters(authorization_req_type, hf_v2giso2_iso2AuthorizationReqType_Id, tvb, msg->Id.characters, msg->Id.charactersLen, sizeof(msg->Id.characters));
    }

    if (msg->GenChallenge_isUsed)
    {
        exi_add_bytes(authorization_req_type, hf_v2giso2_iso2AuthorizationReqType_GenChallenge, tvb, msg->GenChallenge.bytes, msg->GenChallenge.bytesLen, sizeof(msg->GenChallenge.bytes));
    }

    return;
}

/**
 * @brief Dissector for the iso2AuthorizationResType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2AuthorizationResType struct to dissect.
 */
static void
dissect_v2giso2_SessionStopReq(proto_tree *tree, tvbuff_t *tvb,
                               iso2SessionStopReqType *msg)
{

    proto_tree *session_stop_req_type_subtree;
    proto_item *it;

    session_stop_req_type_subtree = proto_tree_add_subtree(tree,
                                                           tvb, 0, 0, ett_v2gexi, NULL, "Session Stop Request");

    it = proto_tree_add_uint(session_stop_req_type_subtree,
                             hf_v2giso2_iso2SessionStopReqType_ChargingSession,
                             tvb, 0, 0, msg->ChargingSession);
    proto_item_set_generated(it);

    return;
}

/**
 * @brief Dissector for the iso2SessionStopResType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2SessionStopResType struct to dissect.
 */
static void
dissect_v2giso2_SessionStopRes(proto_tree *tree, tvbuff_t *tvb, iso2SessionStopResType *msg)
{
    proto_tree *session_stopRes_type_subtree;
    proto_item *it;
    session_stopRes_type_subtree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL, "Session Stop Resuest");
    it = proto_tree_add_uint(session_stopRes_type_subtree, hf_v2giso2_iso2SessionStopResType_ResponseCode, tvb, 0, 0, msg->ResponseCode);
    proto_item_set_generated(it);

    if (msg->EVSEStatus_isUsed)
    {
        dissect_v2giso2_evsestatus(&msg->EVSEStatus, tvb, session_stopRes_type_subtree, ett_v2gexi, "EVSEStatus");
    }

    return;
}

/**
 * @brief   Dissector for the iso2CableCheckReqType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2CableCheckReqType struct to dissect.
 */
static void
dissect_iso2CableCheckReqType(proto_tree *tree, tvbuff_t *tvb,
                              iso2CableCheckReqType *msg)
{
    proto_tree *subtree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL,
                                                 "Cable Check Request");
    return;
}

/**
 * @brief  Dissector for the iso2CableCheckResType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2CableCheckResType struct to dissect.
 */
static void
dissect_v2giso2_PaymentServiceSelectionReq(proto_tree *tree, tvbuff_t *tvb,
                                           iso2PaymentServiceSelectionReqType *msg)
{
    proto_tree *subtree;
    proto_tree *selectedservice_tree;
    proto_tree *payment_service_selection_req_subtree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL, "Payment Service Selection Request");
    proto_item *it;
    it = proto_tree_add_uint(payment_service_selection_req_subtree,
                             hf_v2giso2_iso2PaymentServiceSelectionReqType_SelectedPaymentOption,
                             tvb, 0, 0, msg->SelectedPaymentOption);
    proto_item_set_generated(it);

    unsigned int i;
    if (msg->SelectedVASList_isUsed)
    {
        subtree = proto_tree_add_subtree(payment_service_selection_req_subtree, tvb, 0, 0, ett_v2gexi, NULL, "SelectedServiceList");
        selectedservice_tree = proto_tree_add_subtree(subtree,
                                                      tvb, 0, 0, ett_v2gexi, NULL, "SelectedService");
        for (i = 0; i < msg->SelectedVASList.SelectedService.arrayLen; i++)
        {
            char index[sizeof("[65536]")];
            subtree = proto_tree_add_subtree(selectedservice_tree, tvb, 0, 0, ett_v2gexi, NULL, index);
            it = proto_tree_add_uint(subtree, hf_v2giso2_iso2SelectedServiceType_ServiceID, tvb, 0, 0, msg->SelectedVASList.SelectedService.array[i].ServiceID);
            proto_item_set_generated(it);
            it = proto_tree_add_uint(subtree, hf_v2giso2_iso2SelectedServiceType_ParameterSetID, tvb, 0, 0, msg->SelectedVASList.SelectedService.array[i].ParameterSetID);
            proto_item_set_generated(it);
        }
    }
    return;
}

/**
 * @brief   Dissector for the iso2PaymentServiceSelectionResType struct;
 *
 * @param tree the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2PaymentServiceSelectionResType struct to dissect.
 */

static void
dissect_v2giso2_ServiceDiscoveryReq(proto_tree *tree, tvbuff_t *tvb,
                                    iso2ServiceDiscoveryReqType *msg)
{
    proto_tree *service_discovery_req_subtree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL, "Service Discovery Request");
    proto_item *it;
    if (msg->SupportedServiceIDs_isUsed)
    {
        exi_add_characters(service_discovery_req_subtree,
                           hf_v2giso2_iso2ServiceDiscoveryReqType_ServiceScope,
                           tvb,
                           msg->SupportedServiceIDs.ServiceID.array,
                           msg->SupportedServiceIDs.ServiceID.arrayLen,
                           sizeof(msg->SupportedServiceIDs.ServiceID.array));
    }
    return;
}

/**
 * @brief   Dissector for the iso2ServiceDiscoveryResType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param paymentdetailsreq     the iso2ServiceDiscoveryResType struct to dissect.
 */
static void
dissect_v2giso2_PaymentDetailsReq(proto_tree *tree, tvbuff_t *tvb,
                                  iso2PaymentDetailsReqType *paymentdetailsreq)
{
    proto_tree *payment_details_req_subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL, "Payment Details Req");
    exi_add_characters(payment_details_req_subtree,
                       hf_v2giso2_iso2PaymentDetailsReqType_eMAID,
                       tvb,
                       paymentdetailsreq->eMAID.characters,
                       paymentdetailsreq->eMAID.charactersLen,
                       sizeof(paymentdetailsreq->eMAID.characters));

    dissect_v2g_certificatechain(
        &paymentdetailsreq->ContractSignatureCertChain,
        tvb, payment_details_req_subtree,
        ett_v2gexi,
        "ContractSignatureCertChain");

    return;
}
/**
 * @brief  Dissector for the iso2PaymentDetailsResType struct;
 *
 * @param certificatechain  the iso2CertificateChainType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to which we add the data.
 */
static void
dissect_v2g_certificatechain(iso2CertificateChainType *certificatechain, tvbuff_t *tvb,
                             proto_tree *tree, int idx, const char *subtree_name)
{
    proto_tree *subtree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0,
                                     idx, NULL, subtree_name);

    if (certificatechain->Id_isUsed)
    {
        exi_add_characters(subtree,
                           hf_v2giso2_iso2CertificateChainType_Id,
                           tvb,
                           certificatechain->Id.characters,
                           certificatechain->Id.charactersLen,
                           sizeof(certificatechain->Id.characters));
    }

    exi_add_bytes(subtree,
                  hf_v2giso2_iso2CertificateChainType_Certificate,
                  tvb,
                  certificatechain->Certificate.bytes,
                  certificatechain->Certificate.bytesLen,
                  sizeof(certificatechain->Certificate.bytes));

    /*-------------------------------------*/

    if (certificatechain->SubCertificates_isUsed)
    {
        dissect_v2giso2_subcertificates(
            &certificatechain->SubCertificates,
            tvb, subtree,
            ett_v2gexi,
            "SubCertificates");
    }
    return;
}

/**
 * @brief  Dissector for the iso2SubCertificatesType struct;
 *
 * @param subcertificates   the iso2SubCertificatesType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to which we add the data.
 */
static void
dissect_v2giso2_subcertificates(iso2SubCertificatesType *subcertificates, tvbuff_t *tvb,
                                proto_tree *tree, int idx, const char *subtree_name)
{
    unsigned int i;
    proto_tree *subtree;
    proto_tree *certificate_tree;
    proto_tree *certificate_i_tree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0,
                                     idx, NULL, subtree_name);

    certificate_tree = proto_tree_add_subtree(subtree,
                                              tvb, 0, 0, ett_v2gexi, NULL, "Certificate");
    for (i = 0; i < subcertificates->Certificate.arrayLen; i++)
    {
        certificate_i_tree = proto_tree_add_subtree_format(
            certificate_tree,
            tvb, 0, 0, ett_v2gexi, NULL, "[%u]", i);
        exi_add_bytes(certificate_i_tree,
                      hf_v2giso2_iso2SubCertificatesType_Certificate,
                      tvb,
                      subcertificates->Certificate.array[i].bytes,
                      subcertificates->Certificate.array[i].bytesLen,
                      sizeof(subcertificates->Certificate.array[i].bytes));
    }
    return;
}

/**
 * @brief  Dissector for the iso2PhysicalValueType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param physicalValue    the iso2PhysicalValueType struct to dissect.
 * @param subtreeName   the name of the subtree to which we add the data.
 */
static void
dissect_v2giso2_Physicalvalue(proto_tree *tree, tvbuff_t *tvb,
                              iso2PhysicalValueType *physicalValue, char *subtreeName)
{
    proto_tree *subtree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL,
                                     subtreeName);
    proto_item *it;

    it = proto_tree_add_int(subtree,
                            hf_v2giso2_iso2PhysicalValueType_exponent,
                            tvb, 0, 0, physicalValue->Exponent);
    proto_item_set_generated(it);

    it = proto_tree_add_int(subtree,
                            hf_v2giso2_iso2PhysicalValueType_value,
                            tvb, 0, 0, physicalValue->Value);
    proto_item_set_generated(it);
    return;
}

/**
 * @brief   Dissector for the iso2PreChargeReqType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2PreChargeReqType struct to dissect.
 */
static void
dissect_v2giso2_Prechargereq(proto_tree *tree, tvbuff_t *tvb,
                             iso2PreChargeReqType *msg)
{
    proto_tree *subtree;
    subtree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL, "PreCharge Request");
    proto_item *it;
    double value;

    dissect_v2giso2_Physicalvalue(subtree, tvb, &msg->EVTargetVoltage, "EV Target Voltage");
    value = v2giso2_physicalvalue_to_double(&msg->EVTargetVoltage);
    it = proto_tree_add_double(subtree, hf_v2giso2_target_voltage, tvb, 0, 0, value);
    proto_item_set_generated(it);

    dissect_v2giso2_Physicalvalue(subtree, tvb, &msg->EVTargetCurrent, "EV Target Current");
    value = v2giso2_physicalvalue_to_double(&msg->EVTargetCurrent);
    it = proto_tree_add_double(subtree, hf_v2giso2_target_current, tvb, 0, 0, value);
    proto_item_set_generated(it);

    return;
}

/**
 * @brief   Dissector for the iso2PreChargeResType struct;
 *
 * @param res   the iso2PreChargeResType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param pinfo     the packet_info struct containing the packet information.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to which we add the data.
 */
static void
dissect_v2giso2_prechargeres(const iso2PreChargeResType *res, tvbuff_t *tvb,
                             packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, -1, idx, NULL, subtree_name);

    it = proto_tree_add_uint(subtree, hf_v2giso2_iso2PreChargeResType_ResponseCode, tvb, 0, 4, res->ResponseCode);
    proto_item_set_generated(it);

    dissect_v2giso2_evsestatus(
        &res->EVSEStatus,
        tvb, subtree,
        ett_v2giso2_iso2DC_EVSEStatusType,
        "EVSEStatus");

    dissect_v2giso2_Physicalvalue(subtree, tvb, &res->EVSEPresentVoltage, "EV Present Voltage");

    return;
}

/**
 * @brief  Dissector for the iso2AC_EVChargeParameterType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2AC_EVChargeParameterType struct to dissect.
 */
static void
dissect_v2giso2_AC_EVChargeParameter(proto_tree *tree, tvbuff_t *tvb,
                                     iso2AC_EVChargeParameterType *msg)
{
    proto_tree *subtree;
    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL,
                                     "AC: EV Charge Parameter");
    proto_item *it;

    it = proto_tree_add_uint(subtree,
                             hf_v2g_iso2AC_EVChargeParameterType_DepartureTime,
                             tvb, 0, 0, msg->DepartureTime);
    proto_item_set_generated(it);

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumChargePower, "EV Maximum Charge Power");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumChargeCurrent, "EV Maximum Charge Current");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMinimumChargeCurrent, "EV Minimum Charge Current");

    if (msg->EVTargetEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVTargetEnergyRequest, "EV Target Energy Request");
    }

    if (msg->EVMaximumEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMaximumEnergyRequest, "EV Maximum Energy Request");
    }

    if (msg->EVMinimumEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMinimumEnergyRequest, "EV Minimum Energy Request");
    }

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumVoltage, "EV Maximum Voltage");

    return;
}

/**
 * @brief Dissector for the iso2AC_EVBidirectionalParameterType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2AC_EVBidirectionalParameterType struct to dissect.
 */
static void
dissect_v2giso2_AC_EVBidirectionalParameter(proto_tree *tree, tvbuff_t *tvb,
                                            iso2AC_EVBidirectionalParameterType *msg)
{
    proto_tree *subtree;
    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL,
                                     "AC: EV Bidirectional Parameter");
    proto_item *it;

    it = proto_tree_add_uint(subtree,
                             hf_v2g_iso2AC_EVBidirectionalParameterType_DepartureTime,
                             tvb, 0, 0, msg->DepartureTime);
    proto_item_set_generated(it);

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumChargePower, "EV Maximum Charge Power");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumChargeCurrent, "EV Maximum Charge Current");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMinimumChargeCurrent, "EV Minimum Charge Current");

    if (msg->EVTargetEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVTargetEnergyRequest, "EV Target Energy Request");
    }

    if (msg->EVMaximumEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMaximumEnergyRequest, "EV Maximum Energy Request");
    }

    if (msg->EVMinimumEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMinimumEnergyRequest, "EV Minimum Energy Request");
    }

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumVoltage, "EV Maximum Voltage");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumDischargePower, "EV Maximum Discharge Power");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumDischargeCurrent, "EV Maximum Discharge Current");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMinimumDischargeCurrent, "EV Minimum Discharge Current");

    return;
}

/**
 * @brief Dissector for the iso2DC_EVChargeParameterType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2DC_EVChargeParameterType struct to dissect.
 */
static void
dissect_v2giso2_DC_EVChargeParameter(proto_tree *tree, tvbuff_t *tvb,
                                     iso2DC_EVChargeParameterType *msg)
{
    proto_tree *subtree;
    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL,
                                     "DC: EV Charge Parameter");
    proto_item *it;

    it = proto_tree_add_uint(subtree,
                             hf_v2g_iso2DC_EVChargeParameterType_DepartureTime,
                             tvb, 0, 0, msg->DepartureTime);
    proto_item_set_generated(it);

    if (msg->EVMaximumChargePower_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMaximumChargePower, "EV Maximum Charge Power");
    }

    if (msg->EVMinimumChargePower_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMinimumChargePower, "EV Minimum Charge Power");
    }

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumChargeCurrent, "EV Maximum Charge Current");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMinimumChargeCurrent, "EV Minimum Charge Current");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumVoltage, "EV Maximum Voltage");

    if (msg->EVTargetEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVTargetEnergyRequest, "EV Target Energy Request");
    }

    if (msg->EVMaximumEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMaximumEnergyRequest, "EV Maximum Energy Request");
    }

    if (msg->EVMinimumEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMinimumEnergyRequest, "EV Minimum Energy Request");
    }

    if (msg->CurrentSOC_isUsed)
    {
        it = proto_tree_add_int(subtree,
                                hf_v2g_iso2DC_EVChargeParameterType_CurrentSOC,
                                tvb, 0, 0, msg->CurrentSOC);
        proto_item_set_generated(it);
    }

    if (msg->TargetSOC_isUsed)
    {
        it = proto_tree_add_int(subtree,
                                hf_v2g_iso2DC_EVChargeParameterType_TargetSOC,
                                tvb, 0, 0, msg->TargetSOC);
        proto_item_set_generated(it);
    }

    if (msg->BulkSOC_isUsed)
    {
        it = proto_tree_add_int(subtree,
                                hf_v2g_iso2DC_EVChargeParameterType_BulkSOC,
                                tvb, 0, 0, msg->BulkSOC);
        proto_item_set_generated(it);
    }
    return;
}

/**
 * @brief Dissector for the iso2DC_EVStatusType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2DC_EVStatusType struct to dissect.
 */
static void
dissect_v2giso2_DC_EVBidirectionalParameter(proto_tree *tree, tvbuff_t *tvb,
                                            iso2DC_EVBidirectionalParameterType *msg)
{
    proto_tree *subtree;
    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL,
                                     "DC: EV Bidirectional Parameter");
    proto_item *it;

    it = proto_tree_add_uint(subtree,
                             hf_v2g_DC_EVBidirectionalParameterType_DepartureTime,
                             tvb, 0, 0, msg->DepartureTime);
    proto_item_set_generated(it);

    if (msg->EVMaximumChargePower_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMaximumChargePower, "EV Maximum Charge Power");
    }

    if (msg->EVMinimumChargePower_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMinimumChargePower, "EV Minimum Charge Power");
    }

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumChargeCurrent, "EV Maximum Charge Current");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMinimumChargeCurrent, "EV Minimum Charge Current");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumVoltage, "EV Maximum Voltage");

    if (msg->EVTargetEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVTargetEnergyRequest, "EV Target Energy Request");
    }

    if (msg->EVMaximumEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMaximumEnergyRequest, "EV Maximum Energy Request");
    }

    if (msg->EVMinimumEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMinimumEnergyRequest, "EV Minimum Energy Request");
    }

    if (msg->CurrentSOC_isUsed)
    {
        it = proto_tree_add_int(subtree,
                                hf_v2g_DC_EVBidirectionalParameterType_CurrentSOC,
                                tvb, 0, 0, msg->CurrentSOC);
        proto_item_set_generated(it);
    }

    if (msg->TargetSOC_isUsed)
    {
        it = proto_tree_add_int(subtree,
                                hf_v2g_DC_EVBidirectionalParameterType_TargetSOC,
                                tvb, 0, 0, msg->TargetSOC);
        proto_item_set_generated(it);
    }

    if (msg->BulkSOC_isUsed)
    {
        it = proto_tree_add_int(subtree,
                                hf_v2g_DC_EVBidirectionalParameterType_BulkSOC,
                                tvb, 0, 0, msg->BulkSOC);
        proto_item_set_generated(it);
    }

    if (msg->EVMaximumDischargePower_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMaximumDischargePower, "EV Maximum Discharge Power");
    }

    if (msg->EVMinimumDischargePower_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMinimumDischargePower, "EV Minimum Discharge Power");
    }

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumDischargeCurrent, "EV Maximum Discharge Current");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMinimumDischargeCurrent, "EV Minimum Discharge Current");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMinimumVoltage, "EV Minimum Voltage");

    if (msg->MinimumSOC_isUsed)
    {
        it = proto_tree_add_int(subtree,
                                hf_v2g_DC_EVBidirectionalParameterType_MinimumSOC,
                                tvb, 0, 0, msg->MinimumSOC);
        proto_item_set_generated(it);
    }
    return;
}

/**
 * @brief Dissector for the iso2DC_EVStatusType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2DC_EVStatusType struct to dissect.
 */
static void
dissect_v2giso2_WPT_EVChargeParameter(proto_tree *tree, tvbuff_t *tvb,
                                      iso2WPT_EVChargeParameterType *msg)
{
    proto_tree *subtree;
    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL,
                                     "WPT: EV Charge Parameter");
    proto_item *it;

    it = proto_tree_add_uint(subtree,
                             hf_v2g_iso2WPT_EVChargeParameterType_DepartureTime,
                             tvb, 0, 0, msg->DepartureTime);
    proto_item_set_generated(it);

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMaximumPower, "EV Maximum Power");

    dissect_v2giso2_Physicalvalue(subtree,
                                  tvb, &msg->EVMinimumPower, "EV Minimum Power");

    if (msg->EVTargetEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVTargetEnergyRequest, "EV Target Energy Request");
    }

    if (msg->EVMaximumEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMaximumEnergyRequest, "EV Maximum Energy Request");
    }

    if (msg->EVMinimumEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->EVMinimumEnergyRequest, "EV Minimum Energy Request");
    }
    return;
}

/**
 * @brief   Dissector for the iso2RelativeTimeIntervalType struct;
 *
 * @param tree   the tree to add the dissected data to.
 * @param tvb    the tvbuff_t containing the data to dissect.
 * @param msg    the iso2RelativeTimeIntervalType struct to dissect.
 */
static void
dissect_v2giso2_RelativeTimeInterval(proto_tree *tree, tvbuff_t *tvb,
                                     iso2RelativeTimeIntervalType *msg)
{
    proto_tree *subtree;
    subtree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL,
                                     "Relative Time Interval");
    proto_item *it;

    it = proto_tree_add_uint(subtree,
                             hf_v2g_iso2RelativeTimeInterval_start,
                             tvb, 0, 0, msg->start);
    proto_item_set_generated(it);

    if (msg->duration_isUsed)
    {
        it = proto_tree_add_uint(subtree,
                                 hf_v2g_iso2RelativeTimeInterval_duration,
                                 tvb, 0, 0, msg->duration);
        proto_item_set_generated(it);
    }
    return;
}

/**
 * @brief  Dissector for the iso2PMaxScheduleEntryType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2PMaxScheduleEntryType struct to dissect.
 * @param idx   the index of the entry in the array.
 */
static void
dissect_v2giso2_PMaxScheduleEntry(proto_tree *tree, tvbuff_t *tvb,
                                  iso2PMaxScheduleEntryType *msg, int idx)
{
    proto_tree *root_tree;
    char *intStr;
    sprintf(intStr, "%d", idx);
    char *str = "PMaxScheduleEntry[";
    strcat(str, intStr);
    strcat(str, "]");

    root_tree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL,
                                       str);

    dissect_v2giso2_RelativeTimeInterval(root_tree,
                                         tvb, &msg->RelativeTimeInterval);

    proto_tree *subtree;
    subtree = proto_tree_add_subtree(root_tree, tvb, 0, 0, ett_v2gexi, NULL,
                                     "PMax");
    proto_item *it;

    for (int i = 0; i < msg->PMax.arrayLen; i++)
    {
        str = "PMax[";
        intStr = "";
        sprintf(intStr, "%d", i);
        strcat(str, intStr);
        strcat(str, "]");
        dissect_v2giso2_Physicalvalue(subtree,
                                      tvb, &msg->PMax.array[i], str);
    }

    it = proto_tree_add_uint(subtree,
                             hf_v2g_iso2PMaxScheduleEntryType_arrayLen,
                             tvb, 0, 0, msg->PMax.arrayLen);
    proto_item_set_generated(it);

    return;
}

/**
 * @brief Dissector for the iso2MinimumPMaxRequestType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param msg   the iso2MinimumPMaxRequestType struct to dissect.
 */
static void
dissect_v2giso2_MinimumPMaxRequest(proto_tree *tree, tvbuff_t *tvb,
                                   iso2MinimumPMaxRequestType *msg)
{
    proto_tree *rootTree;
    rootTree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL,
                                      "Minimum PMax Request");
    proto_tree *subtree;
    subtree = proto_tree_add_subtree(rootTree, tvb, 0, 0, ett_v2gexi, NULL,
                                     "Minimum PMax Schedule Entry");
    proto_item *it;

    for (int i = 0; i < msg->MinimumPMaxScheduleEntry.arrayLen; i++)
    {
        dissect_v2giso2_PMaxScheduleEntry(subtree,
                                          tvb, &msg->MinimumPMaxScheduleEntry.array[i], i);
    }

    it = proto_tree_add_uint(subtree,
                             hf_v2g_iso2MinimumPMaxRequest_arrayLen,
                             tvb, 0, 0, &msg->MinimumPMaxScheduleEntry.arrayLen);
    proto_item_set_generated(it);

    return;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief Dissector for the iso2ChargeParameterDiscoveryReqType struct;
 *
 * @param tree   the tree to add the dissected data to.
 * @param tvb    the tvbuff_t containing the data to dissect.
 * @param msg   the iso2ChargeParameterDiscoveryReqType struct to dissect.
 */
static void
dissect_v2giso2_ChargeParameterDiscoveryReq(proto_tree *tree, tvbuff_t *tvb,
                                            iso2ChargeParameterDiscoveryReqType *msg)
{
    proto_tree *subtree;
    subtree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL,
                                     "Charge Parameter Discovery Request");
    proto_item *it;

    if (msg->MaxSupportingPoints_isUsed)
    {
        it = proto_tree_add_uint(subtree,
                                 hf_v2g_iso2ChargeParameterDiscoveryReqType_MaxSupportingPoints,
                                 tvb, 0, 0, msg->MaxSupportingPoints);
        proto_item_set_generated(it);
    }

    if (msg->EVEnergyTransferParameter_isUsed)
    {
        proto_tree *tmp = proto_tree_add_subtree(subtree, tvb, 0, 0, ett_v2gexi, NULL,
                                                 "EV Enenrgy Transfer Parameter");

        it = proto_tree_add_uint(tmp,
                                 hf_v2g_iso2ChargeParameterDiscoveryReqType_EVEnergyTransferParameter,
                                 tvb, 0, 0, msg->EVEnergyTransferParameter.DepartureTime);
        proto_item_set_generated(it);
    }

    if (msg->AC_EVChargeParameter_isUsed)
    {
        dissect_v2giso2_AC_EVChargeParameter(subtree, tvb,
                                             &msg->AC_EVChargeParameter);
    }

    if (msg->AC_EVBidirectionalParameter_isUsed)
    {
        dissect_v2giso2_AC_EVBidirectionalParameter(subtree, tvb,
                                                    &msg->AC_EVBidirectionalParameter);
    }

    if (msg->DC_EVChargeParameter_isUsed)
    {
        dissect_v2giso2_DC_EVChargeParameter(subtree, tvb,
                                             &msg->DC_EVChargeParameter);
    }

    if (msg->DC_EVBidirectionalParameter_isUsed)
    {
        dissect_v2giso2_DC_EVBidirectionalParameter(subtree, tvb,
                                                    &msg->DC_EVBidirectionalParameter);
    }

    if (msg->WPT_EVChargeParameter_isUsed)
    {
        dissect_v2giso2_WPT_EVChargeParameter(subtree, tvb,
                                              &msg->WPT_EVChargeParameter);
    }

    if (msg->MinimumPMaxRequest_isUsed)
    {
        dissect_v2giso2_MinimumPMaxRequest(subtree, tvb,
                                           &msg->MinimumPMaxRequest);
    }
    return;
}

/**
 * @brief Dissector for the iso2ChargeParameterDiscoveryResType struct;
 *
 * @param pmaxschedule   the iso2PMaxScheduleType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree.
 */
static void
dissect_v2giso2_pmaxschedule(
    iso2PMaxScheduleType *pmaxschedule,
    tvbuff_t *tvb,
    proto_tree *tree,
    int idx,
    char *subtree_name)
{
    unsigned int i;
    proto_tree *subtree;
    proto_tree *pmaxscheduleentry_tree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0,
                                     idx, NULL, subtree_name);

    pmaxscheduleentry_tree = proto_tree_add_subtree(subtree,
                                                    tvb, 0, 0, idx, NULL, "PMaxScheduleEntry");
    for (i = 0; i < pmaxschedule->PMaxScheduleEntry.arrayLen; i++)
    {
        char index[sizeof("[65536]")];
        dissect_v2giso2_PMaxScheduleEntry(pmaxscheduleentry_tree, tvb,
                                          &pmaxschedule->PMaxScheduleEntry.array[i], index);
    }

    return;
}

/**
 * @brief Dissector for the iso2ChargeParameterDiscoveryResType struct;
 *
 * @param cost  the iso2CostType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree.
 */
static void
dissect_v2giso2_cost(
    iso2CostType *cost,
    tvbuff_t *tvb,
    proto_tree *tree,
    int idx,
    char *subtree_name)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0,
                                     idx, NULL, subtree_name);

    it = proto_tree_add_uint(subtree,
                             hf_v2giso2_iso2CostType_costKind,
                             tvb, 0, 0, cost->costKind);
    proto_item_set_generated(it);

    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &cost->amount, "Cost amount");

    return;
}

/**
 * @brief Dissector for the iso2ChargeParameterDiscoveryResType struct;
 *
 * @param consumptioncost   the iso2ConsumptionCostType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree.
 */
static void
dissect_v2giso2_consumptioncost(iso2ConsumptionCostType *consumptioncost, tvbuff_t *tvb,
                                proto_tree *tree, int idx, char *subtree_name)
{
    unsigned int i;
    proto_tree *subtree;
    proto_tree *cost_tree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0,
                                     idx, NULL, subtree_name);

    dissect_v2giso2_Physicalvalue(
        subtree, tvb, &consumptioncost->startValue, "startValue");
    cost_tree = proto_tree_add_subtree(subtree,
                                       tvb, 0, 0, idx, NULL, "Cost");
    for (i = 0; i < consumptioncost->Cost.arrayLen; i++)
    {
        char index[sizeof("[65536]")];
        dissect_v2giso2_cost(
            &consumptioncost->Cost.array[i],
            tvb, cost_tree,
            idx, index);
    }

    return;
}

/**
 * @brief   Dissector for the iso2ChargeParameterDiscoveryResType struct;
 *
 * @param salestariffentry  the iso2SalesTariffEntryType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree.
 */
static void
dissect_v2giso2_salestariffentry(iso2SalesTariffEntryType *salestariffentry, tvbuff_t *tvb,
                                 proto_tree *tree, int idx, char *subtree_name)
{
    unsigned int i;
    proto_tree *subtree;
    proto_tree *consumptioncost_tree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0,
                                     idx, NULL, subtree_name);
    dissect_v2giso2_RelativeTimeInterval(subtree, tvb,
                                         &salestariffentry->RelativeTimeInterval);
    if (salestariffentry->EPriceLevel_isUsed)
    {
        it = proto_tree_add_uint(subtree,
                                 hf_v2giso2_iso2SalesTariffEntryType_EPriceLevel,
                                 tvb, 0, 0, salestariffentry->EPriceLevel);
        proto_item_set_generated(it);
    }
    consumptioncost_tree = proto_tree_add_subtree(subtree,
                                                  tvb, 0, 0, idx, NULL, "ConsumptionCost");
    for (i = 0; i < salestariffentry->ConsumptionCost.arrayLen; i++)
    {
        char index[sizeof("[65536]")];
        dissect_v2giso2_consumptioncost(
            &salestariffentry->ConsumptionCost.array[i],
            tvb, consumptioncost_tree,
            idx, index);
    }

    return;
}

/**
 * @brief   Dissector for the iso2ChargeParameterDiscoveryResType struct;
 *
 * @param salestariff   the iso2SalesTariffType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to which we add data.
 */
static void
dissect_v2giso2_salestariff(iso2SalesTariffType *salestariff, tvbuff_t *tvb,
                            proto_tree *tree, int idx, char *subtree_name)
{
    unsigned int i;
    proto_tree *subtree;
    proto_tree *salestariffentry_tree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0,
                                     idx, NULL, subtree_name);

    exi_add_characters(subtree,
                       hf_v2giso2_iso2SalesTariffType_Id,
                       tvb,
                       salestariff->Id.characters,
                       salestariff->Id.charactersLen,
                       sizeof(salestariff->Id.characters));

    if (salestariff->SalesTariffDescription_isUsed)
    {
        exi_add_characters(subtree,
                           hf_v2giso2_iso2SalesTariffType_SalesTariffDescription,
                           tvb,
                           salestariff->SalesTariffDescription.characters,
                           salestariff->SalesTariffDescription.charactersLen,
                           sizeof(salestariff->SalesTariffDescription.characters));
    }

    it = proto_tree_add_uint(subtree,
                             hf_v2giso2_iso2SalesTariffType_NumEPriceLevels,
                             tvb, 0, 0, salestariff->NumEPriceLevels);
    proto_item_set_generated(it);

    salestariffentry_tree = proto_tree_add_subtree(subtree,
                                                   tvb, 0, 0, idx, NULL, "SalesTariffEntry");
    for (i = 0; i < salestariff->SalesTariffEntry.arrayLen; i++)
    {
        char index[sizeof("[65536]")];
        dissect_v2giso2_salestariffentry(
            &salestariff->SalesTariffEntry.array[i],
            tvb, salestariffentry_tree,
            idx, index);
    }

    return;
}

/**
 * @brief  Dissector for the iso2ChargeParameterDiscoveryResType struct;
 *
 * @param sascheduletuple   the iso2SAScheduleTupleType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to which we add data.
 */
static void
dissect_v2giso2_sascheduletuple(
    iso2SAScheduleTupleType *sascheduletuple,
    tvbuff_t *tvb,
    proto_tree *tree,
    int idx,
    char *subtree_name)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, idx, NULL, subtree_name);

    it = proto_tree_add_uint(subtree, hf_v2giso2_SAScheduleTupleType_SAScheduleTupleID, tvb, 0, 0, sascheduletuple->SAScheduleTupleID);
    proto_item_set_generated(it);

    dissect_v2giso2_pmaxschedule(&sascheduletuple->PMaxSchedule,
                                 tvb, subtree,
                                 idx,
                                 "PMaxSchedule");

    if (sascheduletuple->SalesTariff_isUsed)
    {
        dissect_v2giso2_salestariff(&sascheduletuple->SalesTariff,
                                    tvb, subtree,
                                    idx,
                                    "SalesTariff");
    }

    return;
}

/**
 * @brief Dissector for the iso2SAScheduleListType struct;
 *
 * @param saschedulelist    the iso2SAScheduleListType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param subtree_name  the name of the subtree to which we add data.
 */
static void
dissect_v2giso2_saschedulelist(
    iso2SAScheduleListType *saschedulelist,
    tvbuff_t *tvb,
    proto_tree *tree,
    char *subtree_name)
{
    unsigned int i;
    proto_tree *subtree;
    proto_tree *sascheduletuple_tree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0,
                                     ett_v2gexi, NULL, subtree_name);

    sascheduletuple_tree = proto_tree_add_subtree(subtree,
                                                  tvb, 0, 0, ett_v2gexi, NULL, "SAScheduleTuple");
    for (i = 0; i < saschedulelist->SAScheduleTuple.arrayLen; i++)
    {
        char index[sizeof("[65536]")];

        snprintf(index, sizeof(index), "[%u]", i);
        dissect_v2giso2_sascheduletuple(
            &saschedulelist->SAScheduleTuple.array[i],
            tvb, sascheduletuple_tree,
            ett_v2gexi, index);
    }

    return;
}

/**
 * @brief   Dissector for the iso2ChargeParameterDiscoveryResType struct;
 *
 * @param evsechargeparameter   the iso2EVSEChargeParameterType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to which we add data.
 */
static void
dissect_v2giso2_evsechargeparameter(
    iso2AC_EVSEChargeParameterType *evsechargeparameter,
    tvbuff_t *tvb,
    proto_tree *tree,
    int idx,
    char *subtree_name)
{
    proto_tree *subtree;
    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL, subtree_name);
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMaximumChargeCurrent, "EVSE Maximum Charge Current");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSENominalVoltage, "EVSE Nominal Voltage");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSENominalFrequency, "EVSE Nominal Frequency");

    return;
}

/**
 * @brief   Dissector for the iso2EVSEBidirectionalParameterType struct;
 *
 * @param evsechargeparameter   the iso2EVSEBidirectionalParameterType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to which we add data.
 */
static void
dissect_v2giso2_EVSEBidirectionalParameter(iso2AC_EVSEBidirectionalParameterType *evsechargeparameter, tvbuff_t *tvb,
                                           proto_tree *tree,
                                           int idx,
                                           char *subtree_name)
{
    proto_tree *subtree;
    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL, subtree_name);
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMaximumChargeCurrent, "EVSE Maximum Charge Current");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSENominalVoltage, "EVSE Nominal Voltage");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSENominalFrequency, "EVSE Nominal Frequency");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMaximumDischargeCurrent, "EVSE Maximum Discharge Current");

    return;
}

/**
 * @brief  Dissector for the iso2DC_EVSEChargeParameterType struct;
 *
 * @param evsechargeparameter   the iso2DC_EVSEChargeParameterType struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree to which we add data.
 */
static void
dissect_v2giso2_DC_EVSEBidirectionalParameter_isUsed(iso2DC_EVSEBidirectionalParameterType *evsechargeparameter, tvbuff_t *tvb,
                                                     proto_tree *tree,
                                                     int idx,
                                                     char *subtree_name)
{
    proto_tree *subtree;
    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL, subtree_name);

    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMaximumDischargePower, "EVSE Maximum Discharge Power");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMaximumDischargeCurrent, "EVSE Maximum Discharge Current");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMinimumDischargeCurrent, "EVSE Minimum Discharge Current");

    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMaximumChargeCurrent, "EVSE Maximum Charge Current");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMaximumChargePower, "EVSE Maximum Charge Power");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMinimumChargeCurrent, "EVSE Minimum Charge Current");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMaximumVoltage, "EVSE Maximum Voltage");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMinimumVoltage, "EVSE Minimum Voltage");
    if (evsechargeparameter->EVSECurrentRegulationTolerance_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree, tvb,
                                      &evsechargeparameter->EVSEPeakCurrentRipple, "EVSE Peak Current Ripple");
    }
    if (evsechargeparameter->EVSEEnergyToBeDelivered_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree, tvb,
                                      &evsechargeparameter->EVSEEnergyToBeDelivered, "EVSE Energy ToBe Delivered");
    }
    return;
}

dissect_v2giso2_DC_EVSEChargeParameter_isUsed(iso2DC_EVSEChargeParameterType *evsechargeparameter, tvbuff_t *tvb,
                                              proto_tree *tree,
                                              int idx,
                                              char *subtree_name)
{

    proto_tree *subtree;
    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL, subtree_name);
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMaximumChargeCurrent, "EVSE Maximum Charge Current");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMaximumChargePower, "EVSE Maximum Charge Power");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMinimumChargeCurrent, "EVSE Minimum Charge Current");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMaximumVoltage, "EVSE Maximum Voltage");
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEMinimumVoltage, "EVSE Minimum Voltage");
    if (evsechargeparameter->EVSECurrentRegulationTolerance_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree, tvb,
                                      &evsechargeparameter->EVSECurrentRegulationTolerance, "EVSE Current Regulation Tolerance");
    }
    dissect_v2giso2_Physicalvalue(subtree, tvb,
                                  &evsechargeparameter->EVSEPeakCurrentRipple, "EVSE Peak Current Ripple");
    if (evsechargeparameter->EVSEEnergyToBeDelivered_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree, tvb,
                                      &evsechargeparameter->EVSEEnergyToBeDelivered, "EVSE Energy ToBe Delivered");
    }

    return;
}

/**
 * @brief Dissector for the iso2DC_EVSEChargeParameterType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param chargeparameterdiscoveryres   the struct to dissect.
 */
static void
dissect_v2giso2_ChargeParameterDiscoveryRes(proto_tree *tree, tvbuff_t *tvb,
                                            iso2ChargeParameterDiscoveryResType *chargeparameterdiscoveryres)

{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL, "Charge Parameter Discovery Response");

    it = proto_tree_add_uint(subtree, hf_v2giso2_ChargeParameterDiscoveryResType_ResponseCode, tvb, 0, 0,
                             chargeparameterdiscoveryres->ResponseCode);
    proto_item_set_generated(it);

    it = proto_tree_add_uint(subtree, hf_v2giso2_ChargeParameterDiscoveryResType_EVSEProcessing, tvb, 0, 0,
                             chargeparameterdiscoveryres->EVSEProcessing);
    proto_item_set_generated(it);

    if (chargeparameterdiscoveryres->EVSEStatus_isUsed)
    {
        it = proto_tree_add_int(subtree,
                                hf_v2giso2_iso2ChargeParameterDiscoveryResType_EVSEStatus_NotificationMaxDelay, tvb, 0, 0, chargeparameterdiscoveryres->EVSEStatus.NotificationMaxDelay);
        proto_item_set_generated(it);
        it = proto_tree_add_int(subtree,
                                hf_v2giso2_iso2ChargeParameterDiscoveryResType_EVSEStatus_EVSENotification, tvb, 0, 0, chargeparameterdiscoveryres->EVSEStatus.EVSENotification);
        proto_item_set_generated(it);
    }

    if (chargeparameterdiscoveryres->SAScheduleList_isUsed)
    {
        dissect_v2giso2_saschedulelist(
            &chargeparameterdiscoveryres->SAScheduleList, tvb, subtree, "SAScheduleList");
    }
    if (chargeparameterdiscoveryres->EVSEEnergyTransferParameter_isUsed)
    {
        it = proto_tree_add_int(subtree,
                                hf_v2giso2_iso2ChargeParameterDiscoveryResType_EVSEStatus_EnergyTransferParameter, tvb,
                                0, 0, chargeparameterdiscoveryres->EVSEEnergyTransferParameter.noContent);
        proto_item_set_generated(it);
    }
    if (chargeparameterdiscoveryres->AC_EVSEChargeParameter_isUsed)
    {
        dissect_v2giso2_evsechargeparameter(&chargeparameterdiscoveryres->AC_EVSEChargeParameter,
                                            tvb, subtree,
                                            ett_v2gexi,
                                            "EVSEChargeParameter");
    }
    if (chargeparameterdiscoveryres->AC_EVSEBidirectionalParameter_isUsed)
    {
        dissect_v2giso2_EVSEBidirectionalParameter(&chargeparameterdiscoveryres->AC_EVSEBidirectionalParameter,
                                                   tvb, subtree,
                                                   ett_v2gexi,
                                                   "EVSEBidirectionalParameter");
    }
    if (chargeparameterdiscoveryres->DC_EVSEChargeParameter_isUsed)
    {
        dissect_v2giso2_DC_EVSEChargeParameter_isUsed(
            &chargeparameterdiscoveryres->DC_EVSEChargeParameter,
            tvb, subtree,
            ett_v2gexi,
            "DC_EVSEChargeParameter");
    }
    if (chargeparameterdiscoveryres->DC_EVSEBidirectionalParameter_isUsed)
    {
        dissect_v2giso2_DC_EVSEBidirectionalParameter_isUsed(
            &chargeparameterdiscoveryres->DC_EVSEBidirectionalParameter,
            tvb, subtree,
            ett_v2gexi,
            "DC_EVSEBidirectionalParameter");
    }
    /**/
    if (chargeparameterdiscoveryres->WPT_EVSEChargeParameter_isUsed)
    {
        proto_tree *subtree2;
        subtree2 = proto_tree_add_subtree(subtree, tvb, 0, 0, ett_v2gexi, NULL, "WPT EVSECharge Parameter");
        dissect_v2giso2_Physicalvalue(subtree, tvb,
                                      &chargeparameterdiscoveryres->WPT_EVSEChargeParameter.EVSEMaximumPower, "EVSE Maximum Power");
        dissect_v2giso2_Physicalvalue(subtree, tvb,
                                      &chargeparameterdiscoveryres->WPT_EVSEChargeParameter.EVSEMinimumPower, "EVSE Minimum Power");
    }

    return;
}

/**
 * @brief   Dissector for the iso2DisplayParametersType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param displayparameter  the struct to dissect.
 */
static void
dissect_v2giso2_DisplayParametersType(proto_tree *tree, tvbuff_t *tvb, iso2DisplayParametersType *displayparameter)
{
    proto_tree *subtree;
    proto_item *it;
    double value;

    subtree = proto_tree_add_subtree(tree, tvb, 0, -1, ett_v2gexi, NULL, "Display Parameter");
    if (displayparameter->CurrentRange_isUsed)
    {
        it = proto_tree_add_uint(subtree, hf_v2giso2_iso2CurrentRange, tvb, 0, 2, displayparameter->CurrentRange);
        proto_item_set_generated(it);
    }

    if (displayparameter->CurrentSOC_isUsed)
    {
        it = proto_tree_add_uint(subtree, hf_v2giso2_iso2CurrentSOC, tvb, 0, 1, displayparameter->CurrentSOC);
        proto_item_set_generated(it);
    }

    if (displayparameter->TargetSOC_isUsed)
    {
        it = proto_tree_add_uint(subtree, hf_v2giso2_iso2TargetSOC, tvb, 0, 1, displayparameter->TargetSOC);
        proto_item_set_generated(it);
    }
    /*    */
    if (displayparameter->BulkSOC_isUsed)
    {
        it = proto_tree_add_uint(subtree, hf_v2giso2_iso2BulkSOC, tvb, 0, 1, displayparameter->BulkSOC);
        proto_item_set_generated(it);
    }

    if (displayparameter->MinimumSOC_isUsed)
    {
        it = proto_tree_add_uint(subtree, hf_v2giso2_iso2MinimumSOC, tvb, 0, 1, displayparameter->MinimumSOC);
        proto_item_set_generated(it);
    }

    if (displayparameter->ChargingPerformance_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree, tvb, &displayparameter->ChargingPerformance, "Charging Performance");
    }

    if (displayparameter->RemainingTimeToTargetSOC_isUsed)
    {
        it = proto_tree_add_uint(subtree, hf_v2giso2_iso2RemainingTimeToTargetSOC, tvb, 0, 1, displayparameter->RemainingTimeToTargetSOC);
        proto_item_set_generated(it);
    }

    if (displayparameter->RemainingTimeToMinimumSOC_isUsed)
    {
        it = proto_tree_add_uint(subtree, hf_v2giso2_iso2RemainingTimeToMinimumSOC, tvb, 0, 1, displayparameter->RemainingTimeToMinimumSOC);
        proto_item_set_generated(it);
    }

    if (displayparameter->ChargingComplete_isUsed)
    {
        it = proto_tree_add_uint(subtree, hf_v2giso2_ChargingComplete, tvb, 0, 1, displayparameter->ChargingComplete);
        proto_item_set_generated(it);
    }

    if (displayparameter->BulkChargingComplete_isUsed)
    {
        it = proto_tree_add_uint(subtree, hf_v2giso2_BulkChargingComplete, tvb, 0, 1, displayparameter->BulkChargingComplete);
        proto_item_set_generated(it);
    }

    if (displayparameter->InletHot_isUsed)
    {
        it = proto_tree_add_uint(subtree, hf_v2giso2_InletHot, tvb, 0, 1, displayparameter->InletHot);
        proto_item_set_generated(it);
    }
}

/**
 * @brief   Dissector for the iso2CurrentDemandReqType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param req   the struct to dissect.
 */
static void
dissect_v2giso2_CurrentDemandReq(proto_tree *tree, tvbuff_t *tvb, iso2CurrentDemandReqType *req)
{
    proto_tree *subtree;
    proto_item *it;
    double value;

    subtree = proto_tree_add_subtree(tree,
                                     tvb, 0, 0, ett_v2gexi, NULL, "Current Demand Request");

    dissect_v2giso2_Physicalvalue(subtree, tvb, &req->EVTargetVoltage, "EV Target Voltage");
    value = v2giso2_physicalvalue_to_double(&req->EVTargetVoltage);
    it = proto_tree_add_double(subtree, hf_v2giso2_target_voltage, tvb, 0, 0, value);
    proto_item_set_generated(it);

    dissect_v2giso2_Physicalvalue(subtree, tvb, &req->EVTargetEnergyRequest, "EV Target Energy Request");
    value = v2giso2_physicalvalue_to_double(&req->EVTargetEnergyRequest);
    it = proto_tree_add_double(subtree, hf_v2giso2_target_energy, tvb, 0, 0, value);
    proto_item_set_generated(it);

    dissect_v2giso2_Physicalvalue(subtree, tvb, &req->EVTargetCurrent, "EV Target Current");
    value = v2giso2_physicalvalue_to_double(&req->EVTargetCurrent);
    it = proto_tree_add_double(subtree, hf_v2giso2_target_current, tvb, 0, 0, value);
    proto_item_set_generated(it);

    if (req->EVMaximumVoltage_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree, tvb, &req->EVMaximumVoltage, "EV Maximum Voltage");
    }

    if (req->EVMaximumCurrent_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree, tvb, &req->EVMaximumCurrent, "EV Maximum Current");
    }

    if (req->EVMaximumPower_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree, tvb, &req->EVMaximumPower, "EV Maximum Power");
    }

    if (req->EVMinimumEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree, tvb, &req->EVMinimumEnergyRequest, "EV Minimum Energy ");
    }

    if (req->EVMaximumEnergyRequest_isUsed)
    {
        dissect_v2giso2_Physicalvalue(subtree, tvb, &req->EVMaximumEnergyRequest, "EV Maximum Energy ");
    }

    if (req->DisplayParameters_isUsed)
    {
        dissect_v2giso2_DisplayParametersType(subtree, tvb, &req->DisplayParameters);
    }

    return;
}

/*============================= Dissecting functions for Cable Check Response =============================*/
/**
 * @brief  Dissector for the iso2CableCheckResType struct;
 *
 * @param res   the struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param pinfo     the packet_info struct.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree.
 */
static void dissect_v2giso2_cablecheckres(const iso2CableCheckResType *res, tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, gint idx, const char *subtree_name)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, -1, idx, NULL, subtree_name);

    it = proto_tree_add_uint(subtree, hf_v2giso2_iso2CableCheckResType_ResponseCode, tvb, 0, 4, res->ResponseCode);
    proto_item_set_generated(it);

    dissect_v2giso2_evsestatus(
        &res->EVSEStatus,
        tvb, subtree,
        ett_v2giso2_iso2DC_EVSEStatusType,
        "DC_EVSEStatus");

    it = proto_tree_add_uint(subtree, hf_v2giso2_iso2CableCheckResType_EVSEProcessing, tvb, 0, 4, res->EVSEProcessing);
    proto_item_set_generated(it);

    return;
}

/**
 * @brief   Dissector for the iso2EVSEStatusType struct;
 *
 * @param dc_evsestatus     the struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree.
 */
static void
dissect_v2giso2_evsestatus(const iso2EVSEStatusType *dc_evsestatus, tvbuff_t *tvb, proto_tree *tree, gint idx, const char *subtree_name)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, -1, idx, NULL, subtree_name);

    it = proto_tree_add_uint(subtree, hf_v2giso2_iso2DC_EVSEStatusType_NotificationMaxDelay, tvb, 0, 2, dc_evsestatus->NotificationMaxDelay);
    proto_item_set_generated(it);

    it = proto_tree_add_uint(subtree, hf_v2giso2_iso2DC_EVSEStatusType_EVSENotification, tvb, 0, 4, dc_evsestatus->EVSENotification);
    proto_item_set_generated(it);

    return;
};

/*============================= Dissecting functions for Authorization Response =============================*/
/**
 * @brief   Dissector for the iso2AuthorizationResType struct;
 *
 * @param authorizationres  the struct to dissect.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param _U_   the packet_info struct.
 * @param tree  the tree to add the dissected data to.
 * @param idx   the index of the subtree.
 * @param subtree_name  the name of the subtree.
 */
static void dissect_v2giso2_authorizationres(const iso2AuthorizationResType *authorizationres, tvbuff_t *tvb, packet_info *pinfo _U_, proto_tree *tree, gint idx, const char *subtree_name)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, -1, idx, NULL, subtree_name);

    it = proto_tree_add_uint(subtree, hf_v2giso2_iso2AuthorizationResType_ResponseCode, tvb, 0, 4, authorizationres->ResponseCode);
    proto_item_set_generated(it);

    it = proto_tree_add_uint(subtree, hf_v2giso2_iso2AuthorizationResType_EVSEProcessing, tvb, 0, 4, authorizationres->EVSEProcessing);
    proto_item_set_generated(it);

    return;
}

/**
 * @brief  Dissector for the iso2EVSEProcessingType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param PaymentServiceSelectionRes    the struct to dissect.
 */
static void
dissect_v2giso2_PaymentServiceSelectionRes(proto_tree *tree, tvbuff_t *tvb,
                                           iso2PaymentServiceSelectionResType *PaymentServiceSelectionRes)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL,
                                     "Payment Service Selection Response");

    it = proto_tree_add_uint(subtree,
                             hf_v2giso2_iso2PaymentServiceSelectionResType_ResponseCode,
                             tvb, 0, 0, PaymentServiceSelectionRes->ResponseCode);
    proto_item_set_generated(it);

    if (PaymentServiceSelectionRes->EVSEStatus_isUsed)
    {
        dissect_v2giso2_evsestatus(
            &PaymentServiceSelectionRes->EVSEStatus,
            tvb, subtree,
            ett_v2giso2_iso2EVSEStatusType,
            "EVSEStatus");
    }

    return;
}

/**
 * @brief   Dissector for the iso2PaymentOptionListType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param PaymentOptionList     the struct to dissect.
 */
static void
dissect_v2giso2_paymentoptionlist(proto_tree *tree, tvbuff_t *tvb,
                                  iso2PaymentOptionListType *PaymentOptionList)
{
    proto_tree *subtree;
    proto_tree *paymentoption_tree;
    proto_tree *paymentoption_i_tree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL,
                                     "Payment Option List");

    paymentoption_tree = proto_tree_add_subtree(subtree,
                                                tvb, 0, 0, ett_v2giso2_array, NULL, "Payment Option");

    int arrayLen = PaymentOptionList->PaymentOption.arrayLen;
    for (int i = 0; i < arrayLen; i++)
    {
        char index[sizeof("[65536]")];

        snprintf(index, sizeof(index), "[%u]", i);
        paymentoption_i_tree = proto_tree_add_subtree(
            paymentoption_tree, tvb, 0, 0,
            ett_v2giso2_array_i, NULL, index);

        it = proto_tree_add_uint(paymentoption_i_tree,
                                 hf_v2giso2_iso2PaymentOptionListType_PaymentOption,
                                 tvb, 0, 0,
                                 PaymentOptionList->PaymentOption.array[i]);
        proto_item_set_generated(it);
    }

    return;
}

/**
 * @brief   Dissector for the iso2PaymentDetailsReqType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param Service   the struct to dissect.
 * @param idx   the index of the subtree.
 */
static void
dissect_v2giso2_service(proto_tree *tree, tvbuff_t *tvb,
                        iso2ServiceType *Service, char *idx)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL,
                                     idx);

    it = proto_tree_add_uint(subtree,
                             hf_v2giso2_iso2ServiceType_ServiceID,
                             tvb, 0, 0, Service->ServiceID);
    proto_item_set_generated(it);

    it = proto_tree_add_int(subtree,
                            hf_v2giso2_iso2ServiceType_FreeService,
                            tvb, 0, 0, Service->FreeService);
    proto_item_set_generated(it);

    return;
}

/**
 * @brief   Dissector for the iso2ServiceListType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param ServiceList  the struct to dissect.
 */
static void
dissect_v2giso2_servicelist(proto_tree *tree, tvbuff_t *tvb,
                            iso2ServiceListType *ServiceList)
{
    proto_tree *subtree;
    proto_tree *service_tree;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL,
                                     "Service List");

    service_tree = proto_tree_add_subtree(subtree,
                                          tvb, 0, 0, ett_v2giso2_array, NULL, "Service");

    int arrayLen = ServiceList->Service.arrayLen;

    for (int i = 0; i < arrayLen; i++)
    {
        char index[sizeof("[65536]")];

        snprintf(index, sizeof(index), "[%u]", i);
        dissect_v2giso2_service(subtree, tvb,
                                &ServiceList->Service.array[i], index);
    }

    return;
}

/**
 * @brief   Dissector for the iso2ServiceDiscoveryResType struct;
 *
 * @param tree  the tree to add the dissected data to.
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param ServiceDiscoveryRes   the struct to dissect.
 */
static void
dissect_v2giso2_ServiceDiscoveryRes(proto_tree *tree, tvbuff_t *tvb,
                                    iso2ServiceDiscoveryResType *ServiceDiscoveryRes)
{
    proto_tree *subtree;
    proto_item *it;

    subtree = proto_tree_add_subtree(tree, tvb, 0, 0, ett_v2gexi, NULL,
                                     "Service Discovery Response");

    it = proto_tree_add_uint(subtree,
                             hf_v2giso2_iso2ServiceDiscoveryResType_ResponseCode,
                             tvb, 0, 0, ServiceDiscoveryRes->ResponseCode);
    proto_item_set_generated(it);

    if (ServiceDiscoveryRes->EVSEStatus_isUsed)
    {
        dissect_v2giso2_evsestatus(
            &ServiceDiscoveryRes->EVSEStatus,
            tvb, subtree,
            ett_v2giso2_iso2EVSEStatusType,
            "EVSEStatus");
    }

    dissect_v2giso2_paymentoptionlist(subtree, tvb,
                                      &ServiceDiscoveryRes->PaymentOptionList);

    dissect_v2giso2_servicelist(subtree, tvb,
                                &ServiceDiscoveryRes->EnergyTransferServiceList);

    if (ServiceDiscoveryRes->VASList_isUsed)
    {
        dissect_v2giso2_servicelist(subtree, tvb,
                                    &ServiceDiscoveryRes->VASList);
    }

    return;
}

/*------------------------------------------------------------------------------------*/
/**
 * @brief  The driver dissctor for all V2GEXI messages.;
 *
 * @param tvb   the tvbuff_t containing the data to dissect.
 * @param pinfo     the packet_info struct of the current packet.
 * @param _U_   the tree to add the dissected data to.
 * @param _U_   the data to dissect.
 * @return int  the length of the dissected data.
 */
static int dissect_v2gexi(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree _U_, void *data _U_)
{
    bitstream_t stream;
    int err = 0;

    /* Initializing Stream Container */

    stream.size = tvb_captured_length(tvb);
    stream.data = tvb_memdup(wmem_packet_scope(), tvb, 0, stream.size);
    size_t pos = 0;
    stream.pos = &pos;
    stream.buffer = 0;
    stream.capacity = 0;

    V2gFac_Message message;
    iso2EXIDocument isoDoc;
    appHandEXIDocument appDoc;
    message.iso2Doc = &isoDoc;
    message.HandshakeDoc = &appDoc;

    // Function to allocate memory of the given size in the pool which is pointed to by pinfo->pool
    message.iso2Doc = wmem_alloc(pinfo->pool, sizeof(*(message.iso2Doc)));

    // err = V2gFac_decode_Message(&stream, &message);
    // proto_tree_add_debug_text(tree, "error: %d", err);

    col_set_str(pinfo->cinfo, COL_PROTOCOL, "V2GEXI");
    proto_item *ti = proto_tree_add_item(tree, proto_v2gexi, tvb, 0, -1, ENC_NA /*encoding not applicable*/); // Add a child node to the protocol tree

    proto_tree *v2gexi_tree = proto_item_add_subtree(ti, ett_v2gexi);

    // Directing packet to suitable dissecting function
    if (err)
    {
        wmem_free(pinfo->pool, message.iso2Doc);
        return 0;
    }
    else
    {
        proto_tree *v2giso2_tree;

        if (message.HandshakeDoc_isUsed)
        {
            v2giso2_tree = proto_tree_add_subtree(v2gexi_tree, tvb, 0, -1, ett_v2giso2, NULL, "App Handshake Message");
            dissect_v2gexi_handshake(v2giso2_tree, tvb, message.HandshakeDoc);
        }
        else if (message.iso2Doc_isUsed)
        {
            v2giso2_tree = proto_tree_add_subtree(v2gexi_tree, tvb, 0, -1, ett_v2giso2, NULL, "V2G Message");
            // Every v2g message consist of Header and Body
            dissect_v2giso2_message_header(&message.iso2Doc->V2G_Message.Header, tvb, pinfo, v2giso2_tree, ett_v2giso2_header, "Header");
            // dissect_v2g_body(&message.iso2Doc->V2G_Message.Body, tvb, pinfo, v2giso2_tree, ett_v2giso2_body, "Body");

            // Tree to include v2g message body content
            proto_tree *body_tree;
            body_tree = proto_tree_add_subtree(v2giso2_tree, tvb, 0, 0, ett_v2giso2_body, NULL, "Body");
            if (message.iso2Doc->V2G_Message.Body.CableCheckReq_isUsed)
            {
                dissect_iso2CableCheckReqType(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.CableCheckReq);
            }
            else if (message.iso2Doc->V2G_Message.Body.PaymentDetailsRes_isUsed)
            {
                dissect_iso2PaymentDetailsResType(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.PaymentDetailsRes);
            }
            else if (message.iso2Doc->V2G_Message.Body.SessionSetupReq_isUsed)
            {
                dissect_iso2SessionSetupReqType(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.SessionSetupReq);
            }
            else if (message.iso2Doc->V2G_Message.Body.SessionSetupRes_isUsed)
            {
                dissect_iso2SessionSetupResType(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.SessionSetupRes);
            }
            else if (message.iso2Doc->V2G_Message.Body.SessionStopReq_isUsed)
            {
                dissect_v2giso2_SessionStopReq(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.SessionStopReq);
            }
            else if (message.iso2Doc->V2G_Message.Body.SessionStopRes_isUsed)
            {
                dissect_v2giso2_SessionStopRes(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.SessionStopRes);
            }
            else if (message.iso2Doc->V2G_Message.Body.PowerDeliveryReq_isUsed)
            {
                dissect_v2giso2_PowerDeliveryReqType(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.PowerDeliveryReq);
            }
            else if (message.iso2Doc->V2G_Message.Body.PowerDeliveryRes_isUsed)
            {
                dissect_v2giso2_PowerDeliveryRes(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.PowerDeliveryRes);
            }
            else if (message.iso2Doc->V2G_Message.Body.AuthorizationReq_isUsed)
            {
                dissect_v2giso2_AuthorizationReq(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.AuthorizationReq);
            }
            else if (message.iso2Doc->V2G_Message.Body.PaymentDetailsReq_isUsed)
            {
                dissect_v2giso2_PaymentDetailsReq(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.PaymentDetailsReq);
            }
            else if (message.iso2Doc->V2G_Message.Body.PaymentServiceSelectionReq_isUsed)
            {
                dissect_v2giso2_PaymentServiceSelectionReq(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.PaymentServiceSelectionReq);
            }
            else if (message.iso2Doc->V2G_Message.Body.ServiceDiscoveryReq_isUsed)
            {
                dissect_v2giso2_ServiceDiscoveryReq(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.ServiceDiscoveryReq);
            }
            else if (message.iso2Doc->V2G_Message.Body.PreChargeReq_isUsed)
            {
                dissect_v2giso2_Prechargereq(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.PreChargeReq);
            }
            else if (message.iso2Doc->V2G_Message.Body.ChargeParameterDiscoveryReq_isUsed)
            {
                dissect_v2giso2_ChargeParameterDiscoveryReq(body_tree, tvb,
                                                            &message.iso2Doc->V2G_Message.Body.ChargeParameterDiscoveryReq);
            }
            else if (message.iso2Doc->V2G_Message.Body.CableCheckRes_isUsed)
            {
                dissect_v2giso2_cablecheckres(&message.iso2Doc->V2G_Message.Body.CableCheckRes, tvb, pinfo, body_tree, ett_v2giso2_body, "Cable Check Response");
            }
            else if (message.iso2Doc->V2G_Message.Body.AuthorizationRes_isUsed)
            {
                dissect_v2giso2_authorizationres(&message.iso2Doc->V2G_Message.Body.AuthorizationRes, tvb, pinfo, body_tree, ett_v2giso2_body, "Authorization Response");
            }
            else if (message.iso2Doc->V2G_Message.Body.PreChargeRes_isUsed)
            {
                dissect_v2giso2_prechargeres(&message.iso2Doc->V2G_Message.Body.PreChargeRes, tvb, pinfo, body_tree, ett_v2giso2_body, "Pre-Charge Response");
            }
            else if (message.iso2Doc->V2G_Message.Body.CurrentDemandRes_isUsed)
            {
                dissect_v2giso2_CurrentDemandResType(&message.iso2Doc->V2G_Message.Body.CurrentDemandRes, tvb, body_tree, ett_v2giso2_body);
            }
            else if (message.iso2Doc->V2G_Message.Body.ChargeParameterDiscoveryRes_isUsed)
            {
                dissect_v2giso2_ChargeParameterDiscoveryRes(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.ChargeParameterDiscoveryRes);
            }
            else if (message.iso2Doc->V2G_Message.Body.CurrentDemandReq_isUsed)
            {

                dissect_v2giso2_CurrentDemandReq(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.CurrentDemandReq);
            }
            else if (message.iso2Doc->V2G_Message.Body.PaymentServiceSelectionRes_isUsed)
            {
                dissect_v2giso2_PaymentServiceSelectionRes(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.PaymentServiceSelectionRes);
            }
            else if (message.iso2Doc->V2G_Message.Body.ServiceDiscoveryRes_isUsed)
            {
                dissect_v2giso2_ServiceDiscoveryRes(body_tree, tvb, &message.iso2Doc->V2G_Message.Body.ServiceDiscoveryRes);
            }
        }
    }
    return tvb_captured_length(tvb);
}
/**
 * @brief Register the protocol with Wireshark
 *
 */
void proto_register_v2gexi(void)
{

    proto_v2gexi = proto_register_protocol("V2G Extensible XML Interchange", /* name */ "V2GEXI", /* short_name */ "v2gexi" /* filter_name */);
    register_dissector("v2gexi" /*filter name*/, dissect_v2gexi, proto_v2gexi);

    static hf_register_info hf[] = {
        /* struct MessageHeaderType */
        {&hf_v2giso2_MessageHeaderType_SessionID,
         {"SessionID", "v2g.struct.messageheader.sessionid",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_SignatureType_Id,
         {"Id", "v2g.struct.signature.id",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_SignedInfoType_Id,
         {"Id", "v2g.struct.signedinfo.id",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_CanonicalizationMethodType_Algorithm,
         {"Algorithm",
          "v2g.struct.canonicalizationmethod.algorithm",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_CanonicalizationMethodType_ANY,
         {"ANY",
          "v2g.struct.canonicalizationmethod.any",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        /* struct iso2SignatureMethodType */
        {&hf_v2giso2_SignatureMethodType_Algorithm,
         {"Algorithm", "v2g.struct.signaturemethod.algorithm",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_SignatureMethodType_HMACOutputLength,
         {"HMACOutputLength",
          "v2g.struct.signaturemethod.hmacoutputlength",
          FT_INT64, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_SignatureMethodType_ANY,
         {"ANY", "v2g.struct.signaturemethod.any",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        /* struct iso2ReferenceType */
        {&hf_v2giso2_ReferenceType_Id,
         {"Id", "v2g.struct.reference.id",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_ReferenceType_URI,
         {"URI", "v2g.struct.reference.uri",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_ReferenceType_Type,
         {"Type", "v2g.struct.reference.type",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_target_voltage,
         {"Voltage", "v2giso2.target.voltage",
          FT_DOUBLE, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PhysicalValueType_exponent,
         {"Exponent", "v2giso2.v2giso2.physicalValue.exponent",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PhysicalValueType_value,
         {"Value", "v2giso2.physicalValue.value",
          FT_INT16, BASE_DEC, NULL, 0x0, NULL, HFILL}},

        /* struct iso2TransformType */
        {&hf_v2giso2_TransformType_Algorithm,
         {"Algorithm", "v2g.struct.transform.algorithm",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_TransformType_ANY,
         {"ANY", "v2g.struct.transform.any",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_ReferenceType_DigestValue,
         {"DigestValue", "v2g.struct.reference.digestvalue",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_TransformType_XPath,
         {"XPath", "v2g.struct.transform.xpath",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_DigestMethodType_Algorithm,
         {"Algorithm", "v2giso2.struct.digestmethod.algorithm",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_DigestMethodType_ANY,
         {"ANY", "v2giso2.struct.digestmethod.any",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_SignatureValueType_Id,
         {"Id", "v2giso2.struct.signavturevalue.id",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_SignatureValueType_CONTENT,
         {"CONTENT", "v2giso2.struct.signaturevalue.content",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PaymentDetailsResType_ResponseCode,
         {"ResponseCode", "v2giso2.struct.paymentdetailsres.responsecode", FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PaymentDetailsResType_GenChallenge,
         {"GenChallenge", "v2giso2.struct.paymentdetailsres.genchallenge", FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PaymentDetailsResType_EVSETimeStamp,
         {"EVSETimeStamp", "v2giso2.struct.paymentdetailsres.evsetimestamp", FT_INT64, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PaymentDetailsResType_EVSEStatus_NotificationMaxDelay,
         {"Notification Max Delay", "v2giso2.struct.paymentdetailsres.evsestatus.notificationmaxdelay", FT_INT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PaymentDetailsResType_EVSEStatus_EVSENotification,
         {"EVSE Notification", "v2giso2.struct.paymentdetailsres.evsestatus.evsenotification", FT_INT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2ChargeParameterDiscoveryReqType_MaxSupportingPoints,
         {"MaxSupportingPoints", "v2g.chargeparameterdiscoveryreq.maxsupportingpoints",
          FT_INT16, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2ChargeParameterDiscoveryReqType_EVEnergyTransferParameter,
         {"EVEnergyTransferParameter", "v2g.chargeparameterdiscoveryreq.evenergytransferparameter",
          FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2AC_EVChargeParameterType_DepartureTime,
         {"DepartureTime", "v2g.ac_evchargeparameter.departuretime",
          FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2AC_EVBidirectionalParameterType_DepartureTime,
         {"DepartureTime", "v2g.ac_evbidirectionalparameter.departuretime",
          FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2WPT_EVChargeParameterType_DepartureTime,
         {"DepartureTime", "v2g.wpt_evchargeparameter.departuretime",
          FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2DC_EVChargeParameterType_DepartureTime,
         {"DepartureTime", "v2g.dc_evchargeparameter.departuretime",
          FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2DC_EVChargeParameterType_CurrentSOC,
         {"CurrentSOC", "v2g.dc_evchargeparameter.currentsoc",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2DC_EVChargeParameterType_TargetSOC,
         {"TargetSOC", "v2g.dc_evchargeparameter.targetsoc",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2DC_EVChargeParameterType_BulkSOC,
         {"BulkSOC", "v2g.dc_evchargeparameter.bulksoc",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_DC_EVBidirectionalParameterType_DepartureTime,
         {"DepartureTime", "v2g.dc_evbidirectionalparameter.departuretime",
          FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_DC_EVBidirectionalParameterType_CurrentSOC,
         {"CurrentSOC", "v2g.dc_evbidirectionalparameter.currentsoc",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_DC_EVBidirectionalParameterType_TargetSOC,
         {"TargetSOC", "v2g.dc_evbidirectionalparameter.targetsoc",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_DC_EVBidirectionalParameterType_BulkSOC,
         {"BulkSOC", "v2g.dc_evbidirectionalparameter.bulksoc",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_DC_EVBidirectionalParameterType_MinimumSOC,
         {"MinimumSOC", "v2g.dc_evbidirectionalparameter.minimumsoc",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2MinimumPMaxRequest_arrayLen,
         {"arrayLen", "v2g.minimumpmaxrequest.arraylen",
          FT_INT16, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2PMaxScheduleEntryType_arrayLen,
         {"arrayLen", "v2g.pmaxscheduleentry.arraylen",
          FT_INT16, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2RelativeTimeInterval_start,
         {"start", "v2g.relativetimeinterval.start",
          FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2g_iso2RelativeTimeInterval_duration,
         {"duration", "v2g.relativetimeinterval.duration",
          FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SessionSetupReqType_EVCCID,
         {"EVCCID", "v2giso2.struct.sessionsetupreq.evccid",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SessionSetupResType_EVSEStatus,
         {"EVSEStatus", "v2giso2.struct.paymentdetailsres.evsestatus",
          FT_INT64, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SessionSetupResType_EVSEStatus_NotificationMaxDelay,
         {"Notification Max Delay", "v2giso2.struct.sessionsetupres.evsestatus.notificationmaxdelay", FT_INT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SessionSetupResType_EVSEStatus_EVSENotification,
         {"EVSE Notification", "v2giso2.struct.sessionsetupres.evsestatus.evsenotification", FT_INT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        /* struct iso2PowerDeliveryReqType */
        {&hf_v2giso2_iso2PowerDeliveryReqType_ChargeProgress,
         {"ChargeProgress", "v2g.struct.powerdeliveryreq.chargeprogress", FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PowerDeliveryReqType_SAScheduleTupleID,
         {"SAScheduleTupleID", "v2giso2.struct.powerdeliveryreq.sascheduletupleid", FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        /* struct iso2PowerDeliveryResType */
        {&hf_v2giso2_iso2PowerDeliveryResType_ResponseCode,
         {"ResponseCode", "v2giso2.struct.powerdeliveryres.responsecode", FT_UINT32, BASE_DEC, VALS(v2giso2_response_code_names), 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SessionStopReqType_ChargingSession,
         {"ChargingSession",
          "v2giso2.struct.sessionstopreq.chargingsession",
          FT_UINT32, BASE_DEC, NULL,
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SessionStopResType_ResponseCode,
         {"ResponseCode",
          "v2giso2.struct.sessionstopres.responsecode",
          FT_UINT32, BASE_DEC, NULL,
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2AuthorizationReqType_Id,
         {"Id", "v2giso2.struct.authorizationreq.id",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2AuthorizationReqType_GenChallenge,
         {"GenChallenge",
          "v2giso2.struct.authorizationreq.genchallenge",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2gexi_struct_appHandAppProtocolType_ProtocolNamespace,
         {"ProtocolNamespace", "v2gexi.struct.apphandappprotocoltype.protocolnamespace", FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2gexi_struct_appHandAppProtocolType_VersionNumberMajor,
         {"VersionNumberMajor", "v2gexi.struct.apphandappprotocoltype.versionnumbermajor", FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2gexi_struct_appHandAppProtocolType_VersionNumberMinor,
         {"VersionNumberMinor", "v2gexi.struct.apphandappprotocoltype.versionnumberminor", FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2gexi_struct_appHandAppProtocolType_SchemaID,
         {"SchemaID", "v2gexi.struct.apphandappprotocoltype.schemaid", FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2gexi_struct_appHandAppProtocolType_Priority,
         {"Priority", "v2gexi.struct.apphandappprotocoltype.priority", FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PaymentServiceSelectionReqType_SelectedPaymentOption,
         {"SelectedPaymentOption", "v2giso2.struct.paymentserviceslectionreq.selectpaymentoption", FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SelectedServiceType_ParameterSetID,
         {"ParameterSetID", "v2giso2.struct.selectedservice.parametersetid", FT_INT16, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SelectedServiceType_ServiceID,
         {"ServiceID", "v2giso2.struct.selectedservice.serviceid",
          FT_UINT16, BASE_HEX, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2ServiceDiscoveryReqType_ServiceScope,
         {"ServiceScope",
          "v2giso2.struct.servicediscoveryreq.servicescope",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2ServiceDiscoveryReqType_ServiceCategory,
         {"ServiceCategory",
          "v2giso2.struct.servicediscoveryreq.servicecategory",
          FT_UINT32, BASE_DEC, NULL,
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CertificateChainType_Id,
         {"Id", "v2giso2.struct.certificatechain.id",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CertificateChainType_Certificate,
         {"Certificate",
          "v2giso2.struct.certificatechain.certificate",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SubCertificatesType_Certificate,
         {"Certificate",
          "v2giso2.struct.subcertificates.certificate",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PaymentDetailsReqType_eMAID,
         {"eMAID", "v2giso2.struct.paymentdetailsreq.emaid",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        /* struct iso2CableCheckResType */
        {&hf_v2giso2_iso2CableCheckResType_ResponseCode,
         {"ResponseCode", "v2giso2.struct.cablecheckres.responsecode",
          FT_UINT32, BASE_DEC, VALS(v2giso2_response_code_names),
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CableCheckResType_EVSEProcessing,
         {"EVSEProcessing",
          "v2giso2.struct.cablecheckres.evseprocessing",
          FT_UINT32, BASE_DEC, VALS(v2giso2_evse_processing_names),
          0x0, NULL, HFILL}},
        /* struct iso2EVSEStatusType */
        {&hf_v2giso2_iso2DC_EVSEStatusType_NotificationMaxDelay,
         {"NotificationMaxDelay",
          "v2giso2.struct.dc_evsestatus.notificationmaxdelay",
          FT_UINT16, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2DC_EVSEStatusType_EVSENotification,
         {"EVSENotification",
          "v2giso2.struct.dc_evsestatus.evsenotification",
          FT_UINT32, BASE_DEC, VALS(v2giso2_evsenotification_names),
          0x0, NULL, HFILL}},
        /* struct iso1AuthorizationResType */
        {&hf_v2giso2_iso2AuthorizationResType_ResponseCode,
         {"ResponseCode",
          "v2giso2.struct.authorizationres.responsecode",
          FT_UINT32, BASE_DEC, VALS(v2giso2_response_code_names),
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2AuthorizationResType_EVSEProcessing,
         {"EVSEProcessing",
          "v2giso2.struct.authorizationres.evseprocessing",
          FT_UINT32, BASE_DEC, VALS(v2giso2_evse_processing_names),
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PowerDeliveryResType_EVSEProcessing,
         {"EVSEProcessing",
          "v2giso2.struct.powerdeliveryres.evseprocessing",
          FT_UINT32, BASE_DEC, VALS(v2giso2_evse_processing_names),
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PreChargeResType_ResponseCode,
         {"ResponseCode", "v2giso2.struct.prechargeres.responsecode",
          FT_UINT32, BASE_DEC, VALS(v2giso2_response_code_names),
          0x0, NULL, HFILL}},
        {&hf_v2giso2_present_voltage,
         {"Voltage", "v2giso2.present.voltage",
          FT_DOUBLE, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_present_current,
         {"Current", "v2giso2.present.current",
          FT_DOUBLE, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        /* struct appHandAnonType_supportedAppProtocolRes */
        {&hf_v2gexi_struct_supportedAppProtocolRes_ResponseCode,
         {"ResponseCode",
          "v2gexi.struct.supportedappprotocolres.responsecode",
          FT_UINT16, BASE_DEC, VALS(v2gexi_response_code_names),
          0x0, NULL, HFILL}},
        {&hf_v2gexi_struct_supportedAppProtocolRes_SchemaID,
         {"SchemaID",
          "v2gexi.struct.supportedappprotocolres.schemaid",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},

        {&hf_v2giso2_iso2SessionSetupResType_ResponseCode,
         {"ResponseCode",
          "v2giso2.struct.sessionsetupres.responsecode",
          FT_UINT32, BASE_DEC, VALS(v2giso2_response_code_names),
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SessionSetupResType_EVSEID,
         {"EVSEID", "v2giso2.struct.sessionsetupres.evseid",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SessionSetupResType_EVSETimeStamp,
         {"EVSETimeStamp",
          "v2giso2.struct.sessionsetupres.evsetimestamp",
          FT_INT64, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CurrentDemandResType_ResponseCode,
         {"ResponseCode",
          "v2giso2.struct.currentdemandres.responsecode",
          FT_UINT32, BASE_DEC, VALS(v2giso2_response_code_names),
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CurrentDemandResType_EVSECurrentLimitAchieved,
         {"EVSECurrentLimitAchieved",
          "v2giso2.struct.currentdemandres.evsecurrentlimitachieved",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CurrentDemandResType_EVSEVoltageLimitAchieved,
         {"EVSEVoltageLimitAchieved",
          "v2giso2.struct.currentdemandres.evsevoltagelimitachieved",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CurrentDemandResType_EVSEPowerLimitAchieved,
         {"EVSEPowerLimitAchieved",
          "v2giso2.struct.currentdemandres.evsepowerlimitachieved",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CurrentDemandResType_EVSEID,
         {"EVSEID", "v2giso2.struct.currentdemandres.evseid",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CurrentDemandResType_SAScheduleTupleID,
         {"SAScheduleTupleID",
          "v2giso2.struct.currentdemandres.sascheduletupleid",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CurrentDemandResType_ReceiptRequired,
         {"ReceiptRequired",
          "v2giso2.struct.currentdemandres.receiptrequired",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2MeterInfoType_MeterID,
         {"MeterID", "v2giso2.struct.meterinfo.meterid",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2MeterInfoType_MeterReadingCharged,
         {"MeterReadingCharged", "v2giso2.struct.meterinfo.meterreadingcharged",
          FT_UINT64, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2MeterInfoType_MeterReadingDischarged,
         {"MeterReadingDischarged", "v2giso2.struct.meterinfo.meterreadingdischarged",
          FT_UINT64, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2MeterInfoType_SigMeterReading,
         {"SigMeterReading",
          "v2giso2.struct.meterinfo.sigmeterreading",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2MeterInfoType_MeterStatus,
         {"MeterStatus", "v2giso2.struct.meterinfo.meterstatus",
          FT_INT16, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2MeterInfoType_TMeter,
         {"TMeter", "v2giso2.struct.meterinfo.tmeter",
          FT_INT64, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        /* struct iso1ChargeParameterDiscoveryResType */
        {&hf_v2giso2_ChargeParameterDiscoveryResType_ResponseCode,
         {"ResponseCode",
          "v2giso2.struct.chargeparameterdiscoveryres.responsecode",
          FT_UINT32, BASE_DEC, NULL,
          0x0, NULL, HFILL}},
        {&hf_v2giso2_ChargeParameterDiscoveryResType_EVSEProcessing,
         {"EVSEProcessing",
          "v2giso2.struct.chargeparameterdiscoveryres.evseprocessing",
          FT_UINT32, BASE_DEC, NULL,
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2ChargeParameterDiscoveryResType_EVSEStatus_NotificationMaxDelay,
         {"Notification Max Delay", "v2giso2.struct.chargeparameterdiscoveryres.evsestatus.notificationmaxdelay",
          FT_INT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2ChargeParameterDiscoveryResType_EVSEStatus_EnergyTransferParameter,
         {"Energy Transfer Parameter", "v2giso2.struct.chargeparameterdiscoveryres.evsestatus.energytransferparameter",
          FT_INT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2ChargeParameterDiscoveryResType_EVSEStatus_EVSENotification,
         {"EVSE Notification", "v2giso2.struct.chargeparameterdiscoveryres.evsestatus.evsenotification",
          FT_INT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_SAScheduleTupleType_SAScheduleTupleID,
         {"SAScheduleTupleID",
          "v2giso2.struct.sascheduletuple.sascheduletupleid",
          FT_UINT8, BASE_HEX, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_RelativeTimeIntervalType_start,
         {"start", "v2giso2.struct.relativetimeinterval.start",
          FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_RelativeTimeIntervalType_duration,
         {"duration", "v2giso2.struct.relativetimeinterval.duration",
          FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        /* struct iso1SalesTariffType */
        {&hf_v2giso2_iso2SalesTariffType_Id,
         {"Id", "v2giso2.struct.salestariff.id",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SalesTariffType_SalesTariffDescription,
         {"SalesTariffDescription",
          "v2giso2.struct.salestariff.salestariffdescription",
          FT_STRING, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2SalesTariffType_NumEPriceLevels,
         {"NumEPriceLevels",
          "v2giso2.struct.salestariff.numepricelevels",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},

        /* struct iso1SalesTariffEntryType */
        {&hf_v2giso2_iso2SalesTariffEntryType_EPriceLevel,
         {"EPriceLevel",
          "v2giso2.struct.salestariffentry.epricelevel",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        /* struct iso1CostType */
        {&hf_v2giso2_iso2CostType_costKind,
         {"costKind", "v2giso2.struct.cost.costkind",
          FT_UINT32, BASE_DEC, NULL,
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CostType_amount,
         {"amount", "v2giso2.struct.cost.amount",
          FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CostType_amountMultiplier,
         {"amountMultiplier", "v2giso2.struct.cost.amountmultiplier",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_target_current,
         {"Current", "v2giso2.target.current",
          FT_DOUBLE, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_target_energy,
         {"Energy", "v2giso2.target.energy",
          FT_DOUBLE, BASE_NONE, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CurrentRange,
         {"CurrentRange",
          "v2giso2.struct.currentrange",
          FT_UINT16, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2CurrentSOC,
         {"CurrentSOC", "v2giso2.struct.CurrentSOC",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2TargetSOC,
         {"CurrentSOC", "v2giso2.struct.CurrentSOC",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2BulkSOC,
         {"BulkSOC", "v2giso2.struct.BulkSOC",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2MinimumSOC,
         {"BulkSOC", "v2giso2.struct.MinimumSOC",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2RemainingTimeToTargetSOC,
         {"BulkSOC", "v2giso2.struct.RemainingTimeToTargetSOC",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2RemainingTimeToBulkSOC_isUsed,
         {"BulkSOC", "v2giso2.struct.RemainingTimeToBulkSOC_isUsed",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2RemainingTimeToMinimumSOC,
         {"BulkSOC", "v2giso2.struct.RemainingTimeToMinimumSOC",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_ChargingComplete,
         {"ChargingComplete", "v2giso2.struct.ChargingComplete",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_BulkChargingComplete,
         {"BulkChargingComplete", "v2giso2.struct.BulkChargingComplete",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_InletHot,
         {"InletHot", "v2giso2.struct.InletHot",
          FT_UINT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PaymentServiceSelectionResType_ResponseCode,
         {"ResponseCode", "v2g.paymentselectionres.responsecode",
          FT_UINT32, BASE_DEC, VALS(v2giso2_response_code_names),
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2ServiceDiscoveryResType_ResponseCode,
         {"ResponseCode", "v2g.servicediscoveryres.responsecode",
          FT_UINT32, BASE_DEC, VALS(v2giso2_response_code_names),
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2ServiceType_ServiceID,
         {"ServiceID", "vgiso2.struct.serviceidlist.serviceid",
          FT_UINT16, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2ServiceType_FreeService,
         {"FreeService", "vgiso2.struct.service.freeservice",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PaymentOptionListType_PaymentOption,
         {"PaymentOption",
          "vgiso2.struct.paymentoptionlist.paymentoption",
          FT_UINT16, BASE_DEC,
          VALS(v2giso2_enum_iso2paymentOptionType_names),
          0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2ProfileEntryType_ChargingProfileEntryStart,
         {"ChargingProfileEntryStart",
          "v2giso2.struct.profilentry.chargingprofileentrystart",
          FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2ProfileEntryType_ChargingProfileEntryMaxNumberOfPhasesInUse,
         {"ChargingProfileEntryMaxNumberOfPhasesInUse",
          "v2giso2.struct.profilentry.chargingprofileentrymaxnumberofphasesinuses",
          FT_INT8, BASE_DEC, NULL, 0x0, NULL, HFILL}},
        {&hf_v2giso2_iso2PowerDeliveryReqType_EVOperation,
         {"EVOperation",
          "vgiso2.struct.powerdeliveryreq.evoperation",
          FT_UINT16, BASE_DEC,
          VALS(v2giso2_evoperation_names),
          0x0, NULL, HFILL}}};
    /* Setup protocol subtree array */
    static gint *ett[] = {
        &ett_v2gexi,
        &ett_v2giso2,
        &ett_v2giso2_header,
        &ett_v2giso2_body,
        &ett_v2giso2_array,
        &ett_v2giso2_array_i,

        &ett_v2giso2_iso2SignatureType,
        &ett_v2giso2_iso2SignedInfoType,
        &ett_v2giso2_iso2CanonicalizationMethodType,
        &ett_v2giso2_iso2SignatureMethodType,
        &ett_v2giso2_iso2ReferenceType,
        &ett_v2giso2_iso2TransformsType,
        &ett_v2giso2_iso2TransformType,
        &ett_v2giso2_iso2DigestMethodType,
        &ett_v2giso2_iso2SignatureValueType,
        &ett_v2giso2_iso2KeyInfoType,
        &ett_v2giso2_iso2PreChargeReqType,
        &ett_v2giso2_iso2DC_EVSEStatusType,
        &ett_v2giso2_iso2PhysicalValueType,
        &ett_v2giso2_iso2MeterInfoType,
        &ett_v2giso2_iso2EVSEStatusType,
        &ett_v2giso2_iso2PowerDeliveryReqType,
        &ett_v2giso2_iso2ChargingProfileType,
        &ett_v2giso2_iso2ProfileEntryType};

    proto_register_field_array(proto_v2gexi, hf, array_length(hf));
    proto_register_subtree_array(ett, array_length(ett));
}

void proto_reg_handoff_v2gexi(void)
{
    create_dissector_handle(dissect_v2gexi, proto_v2gexi);
}
