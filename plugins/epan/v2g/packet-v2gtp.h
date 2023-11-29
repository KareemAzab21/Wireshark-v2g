#ifndef __V2GTP__
#define __V2GTP__
#include "config.h"
#include <epan/packet.h>
#include <epan/expert.h>
#include <epan/capture_dissectors.h>

#define V2GTP_PORT 15118
#define V2GTP_PORT_RANGE "49152-65535"

static int dissect_v2gtp_tcp(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data);
void proto_register_v2gtp(void);
void proto_reg_handoff_v2gtp(void);
void test_sdp(packet_info *pinfo, tvbuff_t *tvb, int offset, void *data);
static gboolean test_v2gtp(packet_info *pinfo, tvbuff_t *tvb, int offset, void *data);

static const value_string payload_types_table[] = {
    {0x8001, "( SAP Payload ID )"},
    {0x8002, "( Part20 Mainstream Payload ID )"},
    {0x8003, "( Part20 AC Mainstream Payload ID )"},
    {0x8004, "( Part20 DC Mainstream Payload ID )"},
    {0x8005, "( Part20 ACDP Mainstream Payload ID )"},
    {0x8006, "( Part20 WPT Mainstream Payload ID )"},
    {0x8101, "( Schedule Renegotiation Payload ID )"},
    {0x8102, "( Metering Confirmation Payload ID )"},
    {0x8103, "( ACDP System Status Payload ID )"},
    {0x8104, "( Parking Status Payload ID )"},
    {0x9000, "( SDP Request Payload ID )"},
    {0x9001, "( SDP Response Payload ID )"},
    {0x9002, "( SDP Request Wireless Payload ID )"},
    {0x9003, "( SDP Response Wireless Payload ID )"},
    {0, NULL}};

#endif
