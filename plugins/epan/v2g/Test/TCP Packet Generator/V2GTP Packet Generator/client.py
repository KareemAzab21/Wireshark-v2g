import socket


Protocol_version = b'\x01'
Protocol_version_inverse = b'\xfe'
Payload_type = b'\x80\x02'
Payload_length = b'\x12\43\56\77'
Payload1 = b'\x12\43\56\77'

Header = Protocol_version + Protocol_version_inverse + \
    Payload_type + Payload_length + Payload1

serverAddressPort = ('127.0.0.1', 15118)

bufferSize = 1024


# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


sock.connect((socket.gethostname(), 15118))

sock.sendto(Header, serverAddressPort)


msgFromServer = sock.recvfrom(bufferSize)


msg = "Message from Server {}".format(msgFromServer[0])

print(msg)
