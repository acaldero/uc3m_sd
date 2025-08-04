
import socket
import sys

arguments = len(sys.argv)
if arguments < 2:
   print('Uso: dns <host>')
   exit()
try:
   hostname, aliases, addresses = socket.gethostbyaddr(sys.argv[1])
   print(sys.argv[1] + ': ', hostname)
   print(sys.argv[1] + ': ', aliases)
   print(sys.argv[1] + ': ', addresses)
except socket.error as msg:
   print('ERROR: ', msg)

