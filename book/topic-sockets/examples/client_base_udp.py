import socket
import sys

arguments = len(sys.argv)
if arguments < 3:
    print('Uso: client_base_tcp  <host> <port>')
    exit()

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = (sys.argv[1], int(sys.argv[2]))
print('destino con dirección {} y puerto {}'.format(*server_address))

try:
    message = 'Esto es una cadena de prueba\0'
    sock.sendto(bytes(message, "utf-8"), server_address)
finally:
    sock.close()

