import socket

 


Protocol_version = b'\x01'
Protocol_version_inverse = b'\xfe'
Payload_type = b'\x90\x00'
Payload_length = b'\x12\43\56\77'
Payload0 = b'\x80'
Payload1 = b'\x01\xef\xbf\xbd'
Payload2 = b'\xef\xbf\xbd\01' 
Payload3 = b'\x00\x00\x00\44'
Payload4 = b'\xef\xbf\xbd\00'
Payload5 = b'\x75\xef\xbf\xbd'
Payload6 = b'\xc9\xb8\xef\xbf'
Payload7 = b'\xbd\xcd\xbc\xef'
Payload8 = b'\xbf\xbd\xef\xbf'
Payload9 = b'\xbd\xef\xbf\xbd'
Payload10 = b'\xef\xbf\xbd\xef'
Payload11 = b'\xbf\xbd\xef\xbf'
Payload12 = b'\xbd\xef\xbf\xbd'
Payload13 = b'\xef\xbf\xbd\xef'
Payload14 = b'\xbf\xbd\xef\xbf'
Payload15 = b'\xbd\xef\xbf\xbd'
Payload16 = b'\xef\xbf\xbd\xef'
Payload17 = b'\xbf\xbd\xef\xbf'
Payload18 = b'\xbd\x35\xcd\x9d'
Payload19 = b'\x11\xef\xbf\xbd'
Payload20 = b'\xef\xbf\xbd\x00'
Payload21 = b'\xef\xbf\xbd\x00'
Payload22 = b'\x02\x00\x00\xdb'
Payload23 = b'\xab\xef\xbf\xbd'
Payload24 = b'\x71\xef\xbf\xbd'
Payload25 = b'\x23\x4b\x71\xd1'
Payload26 = b'\xb9\xef\xbf\xbd'
Payload27 = b'\xef\xbf\xbd\xef'
Payload28 = b'\xbf\xbd\xef\xbf'
Payload29 = b'\xbd\xd1\x91\xef'
Payload30 = b'\xbf\xbd\xef\xbf'
Payload31 = b'\xbd\xef\xbf\xbd'
Payload32 = b'\xef\xbf\xbd\x6b'
Payload33 = b'\xef\xbf\xbd\x3a'
Payload34 = b'\x23\x2b\x30\x01'
Payload35 = b'\x00\x00\x08\x04'
Payload36 = b'\x40\x00\x00\x00'

Header = Protocol_version + Protocol_version_inverse + Payload_type + Payload_length + Payload0 + Payload1 + Payload2+Payload3+Payload4+Payload5+Payload6+Payload7+Payload8+Payload9+Payload10+Payload11+Payload12+Payload13+Payload14+Payload15+Payload16+Payload17+Payload18+Payload19+Payload20+Payload21+Payload22+Payload23+Payload24+Payload25+Payload26+Payload27+Payload28+Payload29+Payload30+Payload31+Payload32+Payload33+Payload34+Payload35+Payload36

serverAddressPort   = ("127.0.0.1", 15118)

bufferSize          = 1024


# Create a UDP socket at client side

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

 

# Send to server using created UDP socket

UDPClientSocket.sendto(Header, serverAddressPort)

 

msgFromServer = UDPClientSocket.recvfrom(bufferSize)

 

msg = "Message from Server {}".format(msgFromServer[0])

print(msg)
