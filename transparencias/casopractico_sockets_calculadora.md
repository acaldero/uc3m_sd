# Ejemplo de calculadora distribuida basada en sockets TCP
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ Licencia [GPLv3.0](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

 * [Enunciado](#enunciado)
 * [Guía para ayudar a la resolución de ejercicios de diseño de aplicaciones distribuidas](#guía-para-ayudar-a-la-resolución-de-ejercicios-de-diseño-de-aplicaciones-distribuidas)
 * [Ejemplo de diseño de calculadora distribuida basada en sockets](#ejemplo-de-diseño-de-calculadora-distribuida-basada-en-sockets)
 * [Ejemplo de implementación de servicio distribuido de calculadora con TCP](#ejemplo-de-implementación-de-servicio-distribuido-de-calculadora-con-tcp)


## Enunciado

Se pide diseñar e implementar un servicio de calculadora distribuida fiable que permita sumar y restar en C11 usando sockets.


## Guía para ayudar a la resolución de ejercicios de diseño de aplicaciones distribuidas

<html>
<table>
<tr>
<td>
<ol type="1" start="1">
<li>Identificar las partes cliente y servidor
<ul>
<li> Cliente: elemento activo, puede haber varios
<li> Servidor: elemento pasivo
</ul>
<li>Indentificar el protocolo de servicio
<ul>
<li>Identificar peticiones/respuestas
<li>Identificar los tipos mensajes
<li>Identificar la secuencia de intercambio de mensajes
</ul>
</ol>
</td>
<td>
Qué
</td>
</tr>

<tr>
<td>
<ol type="1" start="3">
<li>Elegir el tipo de servidor:
<ul>
    <li> No orientado a conexión (UDP)
    <li> Orientado a conexión (TCP)
    <ul>
      <li> Conexión por petición
      <li> Conexión por sesión
    </ul>
</ul>
</ol>
</td>
<td>
Cómo (1/2)
</td>
</tr>

<tr>
<td>
<ol type="1" start="4">
<li>Definir el formato de los mensajes (representación de los datos) <br>
y la secuencia detallada de paso de mensajes
<ul>
<li>Buscar en lo posible independencia (lenguaje, arquitectura, implementación, ...)
</ul>
</ol>
</td>
<td>
Diseño inicial
</td>
</tr>

<tr>
<td>
<ol type="1" start="5">
 <li>Diseñar aspectos de concurrencia (secuencial, proceso pesado, proceso ligero bajo demanda o proceso ligero con pool)
 <li>Nombrado (direccionamiento estático o dinámico)
</ol>
</td>
<td>
Cómo (2/2)
</td>
</tr>

<tr>
<td>
<ol type="1" start="7">
<li> Modificar el formato de los mensajes y modificar la secuencia detallada de paso de mensajes si fuera necesario
</ol>
</td>
<td>
Diseño final
</td>
</tr>
</table>
</html>



##  Ejemplo de diseño de calculadora distribuida basada en sockets

1. Identificar las partes cliente y servidor:
   * **Cliente: elemento activo que al ejecutar en la máquina A envía petición por la red.**
   * **Servidor: elemento pasivo que al ejecutar en la máquina B que está en un bucle en el que (1) recibe la petición por la red de un cliente, (2) la procesa y (3) responde con el resultado.**

2. Indentificar el protocolo de servicio (peticiones/respuesta, tipos y secuencia de intercambio):
   ```mermaid
    sequenceDiagram
      Cliente1  ->>+  Servidor: petición de suma/resta
      Note right of Servidor: procesa petición
      Servidor ->>-   Cliente1: resultado suma/resta

      Cliente2  ->>+  Servidor: petición suma/resta
      Note left of Servidor: procesa petición
      Servidor ->>-   Cliente2: resultado suma/resta
   ```

3. Tipo de servidor: se utiliza orientado a conexión con conexión por petición:
   * **TCP: No se quiere que se pierda los mensajes intercambiados**
   * **Por petición: No se precisa una sesión con varias peticiones en dicha petición**

4. Definición del formato de los mensajes (representación de datos) y la secuencia detallada de paso de mensajes:
   ```mermaid
    sequenceDiagram
      Cliente1  ->>+  Servidor: Código de operación (1 byte)
      Cliente1  ->>   Servidor: Primer  operando (4 bytes, formato de red)
      Cliente1  ->>   Servidor: Segundo operando (4 bytes, formato de red)
      Note right of Servidor: Procesa petición
      Servidor ->>-   Cliente1: Resultado (4 bytes, formato de red)

      Cliente2  ->>+  Servidor: Código de operación (1 byte)
      Cliente2  ->>   Servidor: Primer  operando (4 bytes, formato de red)
      Cliente2  ->>   Servidor: Segundo operando (4 bytes, formato de red)
      Note left of Servidor: Procesa petición
      Servidor ->>-   Cliente2: Resultado (4 bytes, formato de red)
   ```

5. Diseñar aspectos de concurrencia (secuencial, proceso pesado, proceso ligero bajo demanda, proceso ligero con pool)
   * **Servidor secuencial.**

6. Nombrado (direccionamiento estático o dinámico) 
   * **Direccionamiento "estático": el servidor atiende en el puerto 4200 y al cliente se ha de indicarle la dirección IP de la máquina.**

8. Modificar el formato de los mensajes y modificar la secuencia detallada de paso de mensajes si fuera necesario 
   * **Para el servidor secuencial y direccionamiento estático no se precisa modificar el diagrama del paso 4.**



## Ejemplo de implementación de servicio distribuido de calculadora con TCP

* Una posible implementación sería la basada en la siguiente estructura:

    ![Estructura de la implementación de la calculadora](/transparencias/casopractico_sockets_calculadora/calc-arq.svg)

  * calc-servidor-tcp.c -> implementación de un servicio de calculadora con sockets TCP.
  * calc-cliente-tcp.c  -> implementación de un cliente  de calculadora con sockets TCP.
  * comm.h -> interfaz de la librería de comunicaciones.
  * comm.c -> implementación de la librería de comunicaciones.


* Para compilar, se puede usar:
  ```bash
  gcc -I./ -Wall -g -c comm.c
  gcc -I./ -Wall -g -c calc-servidor-tcp.c
  gcc -I./ -Wall -g -c calc-cliente-tcp.c
  gcc  -o calc-cliente-tcp  calc-cliente-tcp.o  comm.o
  gcc  -o calc-servidor-tcp calc-servidor-tcp.o comm.o
  ```

* Los archivos serían:

<details open>
<summary><b>comm.h</b></summary>

  ```c
  #ifndef _COMM_H_
  #define _COMM_H_

       #include <sys/types.h>
       #include <sys/socket.h>
       #include <arpa/inet.h>
       #include <netdb.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <string.h>
       #include <errno.h>

       int     serverSocket ( unsigned int addr, int port, int type ) ;
       int     serverAccept ( int sd ) ;
       int     clientSocket ( char *remote, int port ) ;
       int     closeSocket  ( int sd ) ;

       int     sendMessage  ( int socket, char *buffer, int len );
       int     recvMessage  ( int socket, char *buffer, int len );

       ssize_t writeLine    ( int fd, char *buffer ) ;
       ssize_t readLine     ( int fd, char *buffer, size_t n );

  #endif
  ```
</details>


<details open>
<summary><b>calc-servidor-tcp.c</b></summary>
        
   ```c
    #include <unistd.h>
    #include <stdio.h>
    #include <strings.h>
    #include <signal.h>
    #include "comm.h"

    int servicio ( int sc )
    {
        int ret ;
        char op;
        int32_t a, b, res;

        ret = recvMessage(sc, (char *) &op, sizeof(char)); // operación
        if (ret < 0) {
            printf("Error en recepción op\n");
            return -1 ;
        }

        ret = recvMessage(sc, (char *) &a, sizeof(int32_t)); // recibe a
        if (ret == -1) {
            printf("Error en recepción a\n");
            return -1 ;
        }
        a = ntohl(a); // unmarshalling

        ret = recvMessage(sc, (char *) &b, sizeof(int32_t)); // recibe b
        if (ret == -1) {
            printf("Error en recepción b\n");
            return -1 ;
        }
        b = ntohl(b); // unmarshalling

        res = 0;
        if (0 == op) res = a + b;
        if (1 == op) res = a - b;
        if (2 == op) res = a * b;
        if (3 == op) res = a / b;

        res = htonl(res); // marshalling
        ret = sendMessage(sc, (char *)&res, sizeof(int32_t));
        if (ret == -1) {
            printf("Error en envío\n");
            return -1 ;
        }

        return 0 ;
    }

    int the_end = 0;

    void sigHandler ( int signo )
    {
         the_end = 1 ;
    }

    int main ( int argc, char *argv[] )
    {
        int sd, sc;

        // crear socket
        sd = serverSocket(INADDR_ANY, 4200, SOCK_STREAM) ;
        if (sd < 0) {
            printf("SERVER: Error en serverSocket\n");
            return 0;
        }

        // si se presiona Ctrl-C el bucle termina
        signal(SIGINT, sigHandler);

        while (0 == the_end)
        {
                // aceptar conexión con cliente
                sc = serverAccept(sd) ;
                if (sc < 0) {
                    printf("Error en serverAccept\n");
                    continue ;
                }

                // procesar petición
                servicio(sc) ;

                // cerrar conexión con cliente
                closeSocket(sc);
        }

        closeSocket(sd);
        return 0;
    }
   ```

</details>


<details open>
<summary><b>calc-cliente-tcp.c</b></summary>
        
  ```c
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "comm.h"

    int suma_remota ( int sd, int *r, int x, int y )
    {
        int ret;
        char    op;
        int32_t a, b, res ;

        op = 0; // operación sumar
        ret = sendMessage(sd, (char *) &op, sizeof(char));  // envía operación
        if (ret == -1) {
            printf("Error envío op\n");
            return -1;
        }

        a = htonl(x); // marshalling: a <- host to network long(x)
        ret = sendMessage(sd, (char *) &a, sizeof(int32_t)); // envía a
        if (ret == -1) {
            printf("Error envío a\n");
            return -1;
        }

        b = htonl(y); // marshalling: b <- host to network long(y)
        ret = sendMessage(sd, (char *) &b, sizeof(int32_t)); // envía b
        if (ret == -1) {
            printf("Error envío b\n");
            return -1;
        }

        ret = recvMessage(sd, (char *) &res, sizeof(int32_t)); // recibe respuesta
        if (ret == -1) {
            printf("Error en recepción\n");
            return -1;
        }
        *r = ntohl(res); // unmarshalling: *r <- network to host long(res)

        return 0 ;
    }

    int main ( int argc, char **argv )
    {
        int sd, ret, res;

        if (argc != 3) {
            printf("Uso: %s <dirección servidor> <puerto servidor>\n", argv[0]);
            printf("Ejemplo -> %s localhost 4200\n\n", argv[0]);
            return(0);
        }

        char *host = argv[1] ;
        int   port = atoi(argv[2]) ;

        sd = clientSocket(host, port) ;
        if (sd < 0) {
            printf("Error en clientSocket with %s:%d\n", host, port);
            return -1;
        }

        ret = suma_remota(sd, &res, 5, 2) ;
        if (ret < 0) {
            closeSocket(sd);
            return -1;
        }

        printf("Resultado de a+b es: %d\n", res);

        closeSocket(sd);
        return 0;
    }
  ```

</details>


<details open>
<summary><b>comm.c</b></summary>
    
  ```c
    #include "comm.h"

    int serverSocket ( unsigned int addr, int port, int type )
    {
        struct sockaddr_in server_addr ;
        int sd, ret;

        // Crear socket
        sd = socket(AF_INET, type, 0) ;
        if (sd < 0) {
            perror("socket: ");
            return (0);
        }

        // Opción de reusar dirección
        int val = 1;
        setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &val, sizeof(int));

        // Dirección
        bzero((char *)&server_addr, sizeof(server_addr));
        server_addr.sin_family      = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port        = htons(port);

        // Bind
        ret = bind(sd, (const struct sockaddr *)&server_addr, sizeof(server_addr));
        if (ret == -1) {
            perror("bind: ");
            return -1;
        }

        // Listen
        ret = listen(sd, SOMAXCONN);
        if (ret == -1) {
            perror("listen: ");
            return -1;
        }

        return sd ;
    }

    int serverAccept ( int sd )
    {
        int sc ;
        struct sockaddr_in client_addr ;
        socklen_t size ;

        printf("esperando conexión...\n");

        size = sizeof(client_addr) ;
        sc = accept(sd, (struct sockaddr *)&client_addr, (socklen_t *)&size);
        if (sc < 0) {
            perror("accept: ");
            return -1;
        }

        printf("conexión aceptada de IP: %s y puerto: %d\n",
                inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        return sc ;
    }

    int clientSocket ( char *remote, int port )
    {
        struct sockaddr_in server_addr ;
        struct hostent *hp;
        int sd, ret;

        sd = socket(AF_INET, SOCK_STREAM, 0);
        if (sd < 0) {
            perror("socket: ");
            return -1;
        }

        hp = gethostbyname(remote) ;
        if (hp == NULL) {
            printf("Error en gethostbyname\n");
            return -1;
        }

        bzero((char *)&server_addr, sizeof(server_addr));
        memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length);
        server_addr.sin_family  = AF_INET;
        server_addr.sin_port    = htons(port);

        ret = connect(sd, (struct sockaddr *) &server_addr,  sizeof(server_addr));
        if (ret < 0) {
            perror("connect: ");
            return -1;
        }

        return sd ;
    }

    int  closeSocket ( int sd )
    {
        int ret ;

        ret = close(sd) ;
        if (ret < 0) {
            perror("close: ");
            return -1;
        }

        return ret ;
    }

    int sendMessage ( int socket, char * buffer, int len )
    {
        int r;
        int l = len;

        do
        {
                r = write(socket, buffer, l);
                if (r < 0) {
                    return (-1); /* error */
                }
                l = l -r;
                buffer = buffer + r;

        } while ((l>0) && (r>=0));

        return 0;
    }

    int recvMessage ( int socket, char *buffer, int len )
    {
        int r;
        int l = len;

        do {
                r = read(socket, buffer, l);
                if (r < 0) {
                    return (-1); /* error */
                }
                l = l -r ;
                buffer = buffer + r;

        } while ((l>0) && (r>=0));

        return 0;
    }

    ssize_t writeLine ( int fd, char *buffer )
    {
        return sendMessage(fd, buffer, strlen(buffer)+1) ;
    }

    ssize_t readLine ( int fd, char *buffer, size_t n )
    {
        ssize_t numRead;  /* bytes leídos en último read() */
        size_t totRead;   /* bytes leídos hasta ahora */
        char *buf;
        char ch;

        if (n <= 0 || buffer == NULL) {
            errno = EINVAL;
            return -1;
        }

        buf = buffer;
        totRead = 0;

        while (1)
        {
                numRead = read(fd, &ch, 1);  /* leer un byte */

                if (numRead == -1) {
                    if (errno == EINTR)      /* interrupción -> reiniciar read() */
                         continue;
                    else return -1;          /* otro tipo de error */
                } else if (numRead == 0) {   /* EOF */
                    if (totRead == 0)        /* no bytes leídos -> return 0 */
                         return 0;
                    else break;
                } else {                     /* numRead debe ser 1 aquí */
                    if (ch == '\n') break;
                    if (ch == '\0') break;
                    if (totRead < n - 1) {   /* descartar > (n-1) bytes */
                        totRead++;
                        *buf++ = ch;
                    }
                }
        }

        *buf = '\0';
        return totRead;
    }
  ```

</details>



* Para ejecutar en una máquina, se puede usar:
  ```bash
  $ ./calc-servidor-tcp &
  esperando conexión...

  $ ./calc-cliente-tcp
  Uso: ./calc-cliente-tcp <dirección servidor> <puerto servidor>
  Ejemplo -> ./calc-cliente-tcp localhost 4200

  $ ./calc-cliente-tcp localhost 4200
  conexión aceptada de IP: 127.0.0.1 y puerto: 41356
  esperando conexión...
  Resultado de a+b es: 7

  $ ./calc-cliente-tcp localhost 4200
  conexión aceptada de IP: 127.0.0.1 y puerto: 41368
  esperando conexión...
  Resultado de a+b es: 7

  $ pkill -n -f calc-servidor-tcp
  ```

* Para ejecutar en dos máquinas, se puede usar:
  <table>
  <tr><td></td><td> host-a </td> <td> host-b </td></tr>
  <tr>
  <td>1. Arrancar servidor</td>
  <td width=50%></td>
  <td width=50%>

  ```bash
  $ ./calc-servidor-tcp &
  esperando conexión...
  ```

  </td>
  </tr>
  <tr>
  <td>2.- Ejecutar cliente</td>
  <td><small>

  ```bash
  $ ./calc-cliente-tcp
  Uso: ./calc-cliente-tcp <dirección> <puerto>
  Ejemplo -> ./calc-cliente-tcp localhost 4200

  $ ./calc-cliente-tcp host-b 4200
  conexión aceptada de IP: 127.0.0.1 y puerto: 41356
  esperando conexion...
  Resultado de a+b es: 7

  $ ./calc-cliente-tcp localhost 4200
  conexión aceptada de IP: 127.0.0.1 y puerto: 41368
  esperando conexión...
  Resultado de a+b es: 7
  ```

  </small></td>
  <td> 
  </td>
  </tr>
  <tr>
  <td>3.- Finalizar servidor</td>
  <td></td>
  <td>

  ```bash
  $ pkill -n -f calc-servidor-tcp
  ```

  </td>
  </tr>
  </table>


