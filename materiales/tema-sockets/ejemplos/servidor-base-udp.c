#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

 int main ( int argc, char *argv[] )
 {
     int sock, ret;

     // (1) Creación del socket
     sock = socket(PF_INET, SOCK_DGRAM, 0) ;
     if (sock < 0) {
         perror("Error al crear el socket: ") ;
         return -1;
     }

     // (2) Obtener la dirección del socket
     struct sockaddr_in server_address;
     memset(&server_address, 0, sizeof(server_address));
     server_address.sin_family      = AF_INET;
     server_address.sin_port        = htons(4200);
     server_address.sin_addr.s_addr = htonl(INADDR_ANY);

     // (3) Asignación de dirección
     ret = bind(sock, (struct sockaddr *)&server_address, sizeof(server_address)) ;
     if (ret < 0) {
         perror("Error en bind: ");
         return -1;
     }

     // Buffer de recepción de mensajes y
     // estructura donde guardar la dirección del cliente
     struct sockaddr_in client_address;
     unsigned int client_address_len = 0;
     char buffer[1024];

     // Bucle
     while (true)
     {
             // borrar memoria del mensaje anterior
             memset(buffer, 0, 1024) ;

             // (4) Transferencia de datos
             ret = recvfrom(sock,
                            buffer, 1024, 0,
                            (struct sockaddr *)&client_address,
                            &client_address_len);
             if (ret < 0) {
                 printf("ERROR en recvfrom :-(\n") ;
             }

             // Imprimir mensaje
             printf("mensaje: '%s' desde: %s\n",
                    buffer,
                    inet_ntoa(client_address.sin_addr));
     }

     // (5) Cerrar socket
     close(sock) ;

     return 0;
}


