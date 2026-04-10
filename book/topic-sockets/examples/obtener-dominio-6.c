#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main ( int argc, char*argv[] )
{
    int ret;
    struct addrinfo *results;
    struct addrinfo *res;
    char hostname[1025] ;

    // domain name -> lista de direcciones
    ret = getaddrinfo("www.uc3m.es", NULL, NULL, &results);
    if (ret < 0) {
        printf("ERROR en getaddrinfo: %s\n", gai_strerror(ret));
        return -1;
    }

    // recorrer todos los resultados y hacer búsqueda inversa
    for (res = results; res != NULL; res = res->ai_next)
    {
        strcpy(hostname, "") ;
        ret = getnameinfo(res->ai_addr, res->ai_addrlen,
                      hostname, 1025,
                      NULL, 0, 0);
        if (ret < 0) {
            printf("ERROR en getnameinfo: %s\n", gai_strerror(ret));
            continue;
        }

        if (*hostname != '\0')
             printf("hostname: %s\n", hostname);
        else printf("hostname: <empty>\n");
    }

    // liberar memoria de los resultados
    freeaddrinfo(results);

    return 0;
}

