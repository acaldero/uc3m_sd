
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
   struct hostent *hp;
   struct in_addr in;

   hp = gethostbyname("www.uc3m.es");
   if (hp == NULL) {
       printf("Error en gethostbyname\n"); exit(0);
   }

   memcpy(&(in.s_addr), *(hp->h_addr_list), sizeof(in.s_addr));
   printf("%s es %s (%ld)\n", hp->h_name, inet_ntoa(in), in.s_addr);

   return 0;
}

