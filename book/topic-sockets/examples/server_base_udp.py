import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = ('localhost', 10009)
sock.bind(server_address)

while True:
     message, addr = sock.recvfrom(1024)  
     print("mensaje: ", message) 

