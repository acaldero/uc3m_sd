
import socket
import struct

// Example from: https://pythontic.com/modules/socket/inet_aton
IPQuad  = "192.168.0.0"
IP32Bit = socket.inet_aton(IPQuad)
print(IP32Bit)

