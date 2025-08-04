import socket
import sys

arguments = len(sys.argv)
if arguments < 3:
    print('Uso: client_base_tcp  <host> <port>')
    exit()

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = (sys.argv[1], int(sys.argv[2]))
print('conectando a {} y puerto {}'.format(*server_address))
sock.connect(server_address)

try:
    message = b'Esto es una cadena de prueba\0'
    sock.sendall(message)

    message = ''
    while True:
        msg = sock.recv(1)
        if (msg == b'\0'):
            break;
        message += msg.decode()
    message = message + "\0"

    print('mensaje: ' + message)
finally:
    sock.close()

