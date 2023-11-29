from core.Config import *
from core.Logs import log_hpgp
from layerscapy.HomePlugGP import *
from core.layers.SECC import *
from core.layers.V2G import *
from core.BasicWrapper import *
from core.PInterceptor import *
import binascii

# method to generate a V2G message from an XML string (EXI encoded) on TCP
def gen_v2g_msg(encoded_xml):
    ether = Ether()
    ip = IP(dst="127.0.0.1")
    trans = TCP(sport=15118, dport=54054, flags=24)
    v2g=V2GTP()
    packet = ether/ip/trans/v2g
    # encoded_xml=encodeEXI(xml)
    packet.Payload = encoded_xml
    packet.PayloadLen = len(encoded_xml)
    return packet

# TODO: look at the remaining SECC msg fields
def gen_sdp_msg(dir):
    ether = Ether()
    ip = IP(dst="127.0.0.1")
    trans = UDP(sport=15118, dport=54054)
    sdp=SECC()
    packet = ether/ip/trans/sdp
    if dir == 'request':
        packet.SECCType = 0x9000
        r = SECC_RequestMessage()
        r.SecurityProtocol = 0x10
    elif dir == 'response':
        packet.SECCType = 0x9001
        r = SECC_ResponseMessage()
        r.TargetAddress = '127.0.0.1'
        r.TargetPort = 15118
        r.SecurityProtocol = 0x10

    packet = packet/r
    packet.PayloadLen = len(r)
    return packet

def gen_Ev_msg(msg_name, trans):
    with open("EVEXI_Msgs/" + msg_name, "rb") as f:
        data = f.read()

        ether = Ether()
        ip = IP(dst="127.0.0.1")
        if(trans == 'tcp'):
            trans = TCP(sport=54054, dport=15118, flags=24)
        else:
            trans = UDP(sport=54054, dport=15118)
        v2g=V2GTP()
        packet = ether/ip/trans/v2g
        packet.Payload = data
        packet.PayloadLen = len(data)
        sendp(packet)
        
def gen_SE_msg(msg_name, trans):
   with open("SEEXI_Msgs/" + msg_name, "rb") as f:
       data = f.read()

       ether = Ether()
       ip = IP(dst="127.0.0.1")
       if(trans == 'tcp'):
           trans = TCP(sport=15118, dport=54054, flags=24)
       else:
           trans = UDP(sport=15118, dport=54054)
       v2g=V2GTP()
       packet = ether/ip/trans/v2g
       packet.Payload = data
       packet.PayloadLen = len(data)
       sendp(packet)
       packet.Payload = data
       packet.PayloadLen = len(data)
       sendp(packet)
