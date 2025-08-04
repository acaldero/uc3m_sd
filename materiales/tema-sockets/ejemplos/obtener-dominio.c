
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, const char **argv)
{
   struct in_addr addr; struct hostent *hp;
   char **p; struct in_addr in;
   char **q; int err;

   if (argc != 2) {
       printf("USO: %s <Direccion-IP>\n", argv[0]);
       return (1);
   }

   err = inet_aton(argv[1], &addr);
   if (err == 0) {
       printf("por favor use direccion IP en formato a.b.c.d\n");
       return (2);
   }

   hp = gethostbyaddr((char *) &addr, sizeof(addr), AF_INET);
   if (hp == NULL) {
       printf("Error en gethostbyaddr\n");
       return (3);
   }

   for (p = hp->h_addr_list; *p != 0; p++)
   {
       memcpy(&(in.s_addr), *p, sizeof(in.s_addr));
       printf("%s es \t%s (%ld)\n", inet_ntoa(in), hp->h_name, in.s_addr) ;
       for (q=hp->h_aliases; *q != 0; q++) {
            printf("%s\n", *q);
       }
   }

   return(0);
}

