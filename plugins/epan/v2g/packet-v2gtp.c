#include "config.h"
#include <epan/packet.h>
#include <epan/expert.h>
#include <epan/capture_dissectors.h>

#include "packet-v2gtp.h"

/* Initialize the protocol */
static int proto_v2gtp = -1;                // init protocol handle
static int hf_v2gtp_version = -1;           // To control the formatting of the item. The pdu type is 1 byte of data, starting at 0 "Big indian"
static dissector_handle_t v2gtp_tcp_handle; // for TCP handle
static dissector_handle_t v2gtp_udp_handle; // for UDP handle
static dissector_handle_t v2gexi_handle;    // Handle of the called dissector v2gexi
static gboolean SDP = FALSE;                // Flag to indicate if we use UDP or TCP if it was SDP or not

/* Initialize the subtree pointers */
static gint ett_v2gtp = -1;

// Variables for wrapping up the packet dissection.
static int hf_v2gtp_version_inverse = -1;
static int hf_v2gtp_payload_type = -1;
static int hf_v2gtp_payload_length = -1;

// Expert Field Struct
static expert_field ei_v2gtp_version_check = EI_INIT;
static expert_field ei_v2gtp_inv_version_check = EI_INIT;
static expert_field ei_v2gtp_bad_payloadtype = EI_INIT;

/**
 * @brief   Function to test the packet if it should be passed and dissected by V2GTP or not
 *
 * @param pinfo     Packet info
 * @param tvb    The tvbuff_t structure for the packet being dissected.
 * @param offset   The offset into the tvbuff_t where the data to be dissected starts.
 * @param data    Data passed from the caller.
 */
void test_sdp(packet_info *pinfo, tvbuff_t *tvb, int offset, void *data)
{
    /* Third and forth byte only can contain the values 0x9000 , 0x9001 in case of wired SDP connection */
    if (tvb_get_guint16(tvb, 2, ENC_BIG_ENDIAN) == 0x9000 || tvb_get_guint16(tvb, 2, ENC_BIG_ENDIAN) == 0x9001)
    {
        SDP = TRUE;
        return;
    }
    /* Third and forth byte only can contain the values 0x9002 , 0x9003 in case of wireless SDP connection */
    if (tvb_get_guint16(tvb, 2, ENC_BIG_ENDIAN) == 0x9002 || tvb_get_guint16(tvb, 2, ENC_BIG_ENDIAN) == 0x9003)
    {
        SDP = TRUE;
        return;
    }
    /*FALSE means to direct the v2g packet normally to TCP*/
    SDP = FALSE;
    return;
}

/**
 * @brief  Function to test the packet if it should be passed and dissected by V2GTP or not
 *
 * @param pinfo     Packet info
 * @param tvb   The tvbuff_t structure for the packet being dissected.
 * @param offset    The offset into the tvbuff_t where the data to be dissected starts.
 * @param data   Data passed from the caller.
 * @return gboolean
 */
static gboolean test_v2gtp(packet_info *pinfo, tvbuff_t *tvb, int offset, void *data)
{
    /*Two variables to hold values of source and destination ports*/
    int source_port = (int)pinfo->srcport;
    int dest_port = (int)pinfo->destport;

    /* 0) Verify needed bytes available in tvb so tvb_get...() doesn't cause exception. */
    if (tvb_captured_length(tvb) < 8)
        return FALSE;

    /* 1) Verify that the source and destination ports are acceptable under iso 5118-20 */
    if (!(((source_port == 15118) && ((dest_port >= 49152) && (dest_port <= 65535))) || ((dest_port == 15118) && ((source_port >= 49152) && (source_port <= 65535)))))
        return FALSE;

    // if (!((dest_port == 15118) && (source_port >= 49152) && (source_port <= 65535)))
    // return FALSE;

    /* 2) first byte must be 0x01 and second byte must be 0xfe "Version and inverse version respectively*/
    if ((tvb_get_guint8(tvb, 0) != 0x01) && (tvb_get_guint8(tvb, 1) != 0xfe))
        return FALSE;

    /*TRUE means that the packet is v2gtp packet and is on the right dissector*/
    return TRUE;
}

/**
 * @brief  Dissecror for V2GTP header coming on TCP
 *
 * @param tvb   The tvbuff_t structure for the packet being dissected.
 * @param pinfo     Packet info
 * @param tree     Tree to add the protocol subtree to.
 * @param data   Data passed from the caller.
 * @return int  The length of the V2GTP header
 */
static int dissect_v2gtp_tcp(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data)
{
    test_sdp(pinfo, tvb, 0, data); // To check if the payload type is SDP or not

    gint offset = 0; // Help to keep track of where we are in the packet dissection.
    guint16 payload_type = tvb_get_guint16(tvb, 2, ENC_BIG_ENDIAN);
    guint32 version_checker = 0xFFFF;     // Variable for V2GTP Version checking by XORing with the packet fields
    guint32 inv_version_checker = 0xFFFF; // Variable for Inverse of V2GTP Version checking
    guint32 payload_checker = 0xFFFF;     // Variable for payload type checking

    // remove packet from wireshark if it is not v2gtp packet
    // if (!(test_v2gtp(pinfo, tvb, 0, data)))
    //     return 0;

    const char *err = val_to_str(payload_type, payload_types_table, "Unknown (0x%02x)");
    col_set_str(pinfo->cinfo, COL_PROTOCOL, "V2GTP");
    /* Clear the info column */
    col_clear(pinfo->cinfo, COL_INFO);

    col_add_fstr(pinfo->cinfo, COL_INFO, "Payload Type %s", val_to_str(payload_type, payload_types_table, "Unknown (0x%02x)"));

    // Building a subtree to decode our packet into , used to label our payload to be human readable
    proto_item *ti = proto_tree_add_item(tree, proto_v2gtp, tvb, 0, 8, ENC_NA /*encoding not applicable*/); // Add a child node to the protocol tree

    proto_tree *v2gtp_tree = proto_item_add_subtree(ti, ett_v2gtp);
    // Create a subtree under v2gtp tree
    /* proto_tree *v2gtp_subtree = proto_tree_add_subtree(v2gtp_tree, tvb, offset, 8, ett_v2gtp, NULL, "V2GTP Header Info"); */
    proto_tree *v2gtp_subtree = v2gtp_tree;

    ti = proto_tree_add_item_ret_uint(v2gtp_subtree, hf_v2gtp_version, tvb, offset, 1, ENC_BIG_ENDIAN, &version_checker);
    /*Checking version*/
    if (version_checker != 0x01)
    {
        expert_add_info(pinfo, ti, &ei_v2gtp_version_check);
        col_append_fstr(pinfo->cinfo, COL_INFO, " [Illegal protocol version ]");
    }
    offset += 1;
    ti = proto_tree_add_item_ret_uint(v2gtp_subtree, hf_v2gtp_version_inverse, tvb, offset, 1, ENC_BIG_ENDIAN, &inv_version_checker);
    /*Checking version inverse*/
    if (inv_version_checker != 0xfe)
    {
        expert_add_info(pinfo, ti, &ei_v2gtp_inv_version_check);
        col_append_fstr(pinfo->cinfo, COL_INFO, " [Illegal inverse protocol version ]");
    }
    offset += 1;
    ti = proto_tree_add_item_ret_uint(v2gtp_subtree, hf_v2gtp_payload_type, tvb, offset, 2, ENC_BIG_ENDIAN, &payload_checker);
    proto_item_append_text(ti, ", Payload Type : %s", val_to_str(payload_type, payload_types_table, "Unknown (0x%02x)"));
    /*Checking payload type*/
    err = val_to_str(payload_type, payload_types_table, "Unknown (0x%02x)");
    if (SDP == TRUE)
    {
        expert_add_info_format(pinfo, ti, &ei_v2gtp_bad_payloadtype, "SDP should be sent only over UDP not TCP");
        col_append_fstr(pinfo->cinfo, COL_INFO, " [SDP should be sent only over UDP not TCP ]");
    }
    if (err[0] == 'U')
    {
        expert_add_info_format(pinfo, ti, &ei_v2gtp_bad_payloadtype, "Not applicable payload type");
        col_append_fstr(pinfo->cinfo, COL_INFO, " [Not applicable payload type ]");
    }
    offset += 2;
    proto_tree_add_item(v2gtp_subtree, hf_v2gtp_payload_length, tvb, offset, 4, ENC_BIG_ENDIAN);
    offset += 4;
    // Adding new subtree of Application Message
    // proto_tree *app_msg = proto_tree_add_subtree(v2gtp_tree, tvb, offset, tvb_reported_length_remaining(tvb, offset), ett_app, NULL, "Application Message");
    tvbuff_t *metadata_tvb = tvb_new_subset_remaining(tvb, offset);
    call_dissector(v2gexi_handle, metadata_tvb, pinfo, tree);
    return tvb_captured_length(tvb);
}
/**
 * @brief   Dissecror for V2GTP header coming on TCP
 *
 * @param tvb   structure that contains the data of the packet.
 * @param pinfo     structure that contains info about the packet.
 * @param tree      structure that contains the tree of the packet.
 * @param data      structure that contains the data of the packet.
 * @return int    The length of the V2GTP header.
 */
static int dissect_v2gtp_udp(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data)
{
    test_sdp(pinfo, tvb, 0, data); // To check if the payload type is SDP or not

    gint offset = 0; // Help to keep track of where we are in the packet dissection.
    guint16 payload_type = tvb_get_guint16(tvb, 2, ENC_BIG_ENDIAN);
    guint32 version_checker = 0xFFFF;     // Variable for V2GTP Version checking
    guint32 inv_version_checker = 0xFFFF; // Variable for Inverse of V2GTP Version checking
    guint32 payload_checker = 0xFFFF;     // Variable for payload type checking

    // remove packet from wireshark if it is not v2gtp packet
    if (!(test_v2gtp(pinfo, tvb, 0, data)))
        return 0;

    const char *err = val_to_str(payload_type, payload_types_table, "Unknown (0x%02x)");

    col_set_str(pinfo->cinfo, COL_PROTOCOL, "V2GTP");
    /* Clear the info column */
    col_clear(pinfo->cinfo, COL_INFO);

    col_add_fstr(pinfo->cinfo, COL_INFO, "Payload Type %s", val_to_str(payload_type, payload_types_table, "Unknown (0x%02x)"));

    // Building a subtree to decode our packet into , used to label our payload to be human readable
    proto_item *ti = proto_tree_add_item(tree, proto_v2gtp, tvb, 0, 8, ENC_NA /*encoding not applicable*/); // Add a child node to the protocol tree

    proto_tree *v2gtp_tree = proto_item_add_subtree(ti, ett_v2gtp);
    // Create a subtree under v2gtp tree
    proto_tree *v2gtp_subtree = proto_tree_add_subtree(v2gtp_tree, tvb, offset, 8, ett_v2gtp, NULL, "V2GTP Header Info");

    ti = proto_tree_add_item_ret_uint(v2gtp_subtree, hf_v2gtp_version, tvb, offset, 1, ENC_BIG_ENDIAN, &version_checker);
    /*Checking version*/
    if (version_checker != 0x01)
    {
        expert_add_info(pinfo, ti, &ei_v2gtp_version_check);
        col_append_fstr(pinfo->cinfo, COL_INFO, " [Illegal protocol version ]");
    }
    offset += 1;
    ti = proto_tree_add_item_ret_uint(v2gtp_subtree, hf_v2gtp_version_inverse, tvb, offset, 1, ENC_BIG_ENDIAN, &inv_version_checker);
    /*Checking version inverse*/
    if (inv_version_checker != 0xfe)
    {
        expert_add_info(pinfo, ti, &ei_v2gtp_inv_version_check);
        col_append_fstr(pinfo->cinfo, COL_INFO, " [Illegal inverse protocol version ]");
    }
    offset += 1;
    ti = proto_tree_add_item_ret_uint(v2gtp_subtree, hf_v2gtp_payload_type, tvb, offset, 2, ENC_BIG_ENDIAN, &payload_checker);
    proto_item_append_text(ti, ", Payload Type : %s", val_to_str(payload_type, payload_types_table, "Unknown (0x%02x)"));
    /*Checking payload type*/
    err = val_to_str(payload_type, payload_types_table, "Unknown (0x%02x)");
    if (SDP == FALSE)
    {
        expert_add_info_format(pinfo, ti, &ei_v2gtp_bad_payloadtype, "SDP Payload type is the only accepted type to be sent over UDP");
        col_append_fstr(pinfo->cinfo, COL_INFO, " [SDP Payload type is the only accepted type to be sent over UDP]");
    }
    if (err[0] == 'U')
    {
        expert_add_info_format(pinfo, ti, &ei_v2gtp_bad_payloadtype, "Not applicable payload type");
        col_append_fstr(pinfo->cinfo, COL_INFO, " [Not applicable payload type ]");
    }
    offset += 2;
    proto_tree_add_item(v2gtp_subtree, hf_v2gtp_payload_length, tvb, offset, 4, ENC_BIG_ENDIAN);
    offset += 4;

    tvbuff_t *metadata_tvb = tvb_new_subset_remaining(tvb, offset);
    call_dissector(v2gexi_handle, metadata_tvb, pinfo, tree);

    return tvb_captured_length(tvb);
}
/**
 * @brief Register the protocol with Wireshark
 *
 */
void proto_register_v2gtp(void)
{
    // An array "table" to define which fields will be present in the packet
    static hf_register_info hf[] = {
        {&hf_v2gtp_version, {"V2GTP Version", "v2gtp.version", FT_UINT8, BASE_HEX, NULL, 0x0, NULL, HFILL}},
        /*      hf_v2gtp_version - The node’s index.
                v2gtp Version" - The item’s label.
                v2gtp.version - The item’s abbreviated name, for use in the display filter.
                FT_UINT8 - The item’s type: An 8bit unsigned integer.
                BASE_DEC - For an integer type, this tells it to be printed as a decimal number. It could be hex (BASE_HEX) or oct (BASE_OCT). */

        {&hf_v2gtp_version_inverse, {"V2GTP Version Inverse", "v2gtp.version_inverse", FT_UINT8, BASE_HEX, NULL, 0x0, NULL, HFILL}},
        {&hf_v2gtp_payload_type, {"V2GTP Payload Type", "v2gtp.payload_type", FT_UINT16, BASE_HEX, NULL, 0x0, NULL, HFILL}},
        {&hf_v2gtp_payload_length, {"V2GTP Paylaod Length", "v2gtp.payload_length", FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL}}};

    /* Setup protocol subtree array */
    static gint *ett[] = {
        &ett_v2gtp};

    proto_v2gtp = proto_register_protocol("V2G Transport Protocol", /* name */ "V2GTP", /* short_name */ "v2gtp" /* filter_name */);

    proto_register_field_array(proto_v2gtp, hf, array_length(hf));
    proto_register_subtree_array(ett, array_length(ett));

    static ei_register_info ei[] = {
        {&ei_v2gtp_version_check,
         {"v2gtp.version.bad", PI_MALFORMED, PI_ERROR,
          "V2GTP Version is invalid", EXPFILL}},
        {&ei_v2gtp_inv_version_check,
         {"v2gtp.inverse.version.bad", PI_MALFORMED, PI_ERROR,
          "V2GTP Inverse Version is invalid", EXPFILL}},
        {&ei_v2gtp_bad_payloadtype,
         {"v2gtp.payloadtype.bad", PI_MALFORMED, PI_ERROR,
          "Invalid Payload Type", EXPFILL}}

    };

    expert_module_t *expert_v2gtp_check;
    expert_v2gtp_check = expert_register_protocol(proto_v2gtp);
    expert_register_field_array(expert_v2gtp_check, ei, array_length(ei));
}
void proto_reg_handoff_v2gtp(void)
{

    // create dissector to do dissecting (UDP)
    v2gtp_tcp_handle = create_dissector_handle(dissect_v2gtp_tcp, proto_v2gtp);
    // dissector for TCP connection
    v2gtp_udp_handle = create_dissector_handle(dissect_v2gtp_udp, proto_v2gtp); //////////////////

    /* Adding port number and port range which are referenced by the 2 handles
     *v2gtp_udp_handle* and *v2gtp_tcp_handle* to UDP and TCP dissector tables */
    dissector_add_uint_range_with_preference("udp.port", V2GTP_PORT_RANGE, v2gtp_udp_handle);
    dissector_add_uint("udp.port", V2GTP_PORT, v2gtp_udp_handle);

    dissector_add_uint_range_with_preference("tcp.port", V2GTP_PORT_RANGE, v2gtp_tcp_handle);
    dissector_add_uint("tcp.port", V2GTP_PORT, v2gtp_tcp_handle);

    // Searching for v2gtp dissector handle whose filter name is v2gexi
    v2gexi_handle = find_dissector("v2gexi");
}
