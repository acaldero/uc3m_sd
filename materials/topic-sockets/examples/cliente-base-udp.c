
 #include <arpa/inet.h>
 #include <stdio.h>
 #include <string.h>
 #include <sys/socket.h>
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
     inet_pton(AF_INET, "localhost", &server_address.sin_addr);


     // Mensaje a ser enviado
     char buffer[1024];
     strcpy(buffer, "Hola mundo...") ;

     // (3) Transferencia de datos
     ret = sendto(sock,
                  buffer, 1024, 0,
                  (struct sockaddr*)&server_address,
                  sizeof(server_address));
     if (ret < 0) {
         printf("Error en sendto\n") ;
     }

     // Imprimir mensaje
     printf("mensaje: '%s'\n", buffer);

     // (4) Cerrar socket
     // * close(sock) equivale a shutdown(sock, SHUT_RDWR) ;
     // SHUT_RD: cierra canal de lectura
     // SHUT_WR: cierra el canal de escritura,
     //          al terminar los datos read devolverá 0
     // SHUT_RDWR: cierra ambos canales
     close(sock);

     return 0;
 }

