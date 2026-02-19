#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
   struct in_addr in;

   if (argc != 2) {
       printf("Uso: %s <decimal-punto>\n", argv[0]);
       exit(0);
   }

   if (inet_aton(argv[1], &in) == 0) {
       printf("Error en la dirección\n");
       exit(0);
   }

   printf("La dirección es %s\n", inet_ntoa(in));
   exit(0);
}

