import socket

 


Protocol_version = b'\x01'
Protocol_version_inverse = b'\xfe'
Payload_type = b'\x90\x00'
Payload_length = b'\x12\43\56\77'
authorization_request = b'\x80\xE8\x01\x00\x00\x20\x40\x60\x80\xA0\xC0\xE4\x20\x12\xAC\x64\x8E\x8A\xAC\x92\x88\x00\x40\x40'
paymentresponse = b'\x80\xE8\x01\x00\x00\x20\x40\x60\x80\xA0\xC0\xE5\x10\x32\x08\x07\x0C\x0F\x10\x0C\x0F\x70\x00\x08\x18\x08\x08\x20\x00'
sessionsetuprequest = b'\x80\xE8\x01\x00\x00\x00\x00\x00\x00\x00\x00\x05\x78\x02\x14\x00'
cablecheckres = b'\x80\xE8\x01\x00\x00\x20\x40\x60\x80\xA0\xC0\xE4\x40\x02\x40'
AuthorizationResponse = b'\x80\xE8\x01\x00\x00\x20\x40\x60\x80\xA0\xC0\xE4\x29\x22\x40'
PreChargeRes = b'\x80\xE8\x01\x00\x00\x20\x40\x60\x80\xA0\xC0\xE5\x50\x02\x40\xEA\x01\x00'

Header = Protocol_version + Protocol_version_inverse + Payload_type + Payload_length + PreChargeRes
serverAddressPort   = ("127.0.0.1", 15118)

bufferSize          = 1024


# Create a UDP socket at client side

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

 

# Send to server using created UDP socket

UDPClientSocket.sendto(Header, serverAddressPort)

 

msgFromServer = UDPClientSocket.recvfrom(bufferSize)

 

msg = "Message from Server {}".format(msgFromServer[0])

print(msg)
