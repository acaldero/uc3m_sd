
# Comunicación con Colas de mensajes POSIX
+ **Felix García Carballeira y Alejandro Calderón Mateos** @ arcos.inf.uc3m.es
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

 * Introducción a colas de mensajes POSIX
    * [Principales características](#colas-de-mensajes-posix)
 * API para la gestión de colas de mensajes POSIX:
   * [Crear, abrir, cerrar y borrar](#llamadas-posix-para-gestión-de-colas-de-mensajes-13)
      * [Ejemplo en C: crear, cerrar y borrar](#ejemplo-en-c-crear-cerrar-y-borrar)
      * [Ejemplo en C: limpieza de colas NO borradas](#ejemplo-en-c-limpieza-de-colas-no-borradas)
   * [Enviar y recibir](#llamadas-posix-para-gestión-de-colas-de-mensajes-23)
      * [Ejemplo en C: productor-consumidor con colas de mensajes](#ejemplo-en-c-productor-consumidor-con-colas-de-mensajes)
   * [Consultar y cambiar atributos](#llamadas-posix-para-gestión-de-colas-de-mensajes-33)
      * [Ejemplo en C: imprimir los atributos de una cola POSIX](#ejemplo-en-c-imprimir-los-atributos-de-una-cola-posix)
 * [Cliente-servidor secuencial con colas POSIX](#cliente-servidor-secuencial-con-colas-posix)
 * Otros modelos
   * [Otros modelos de colas de mensajes](#otros-modelos-de-colas-de-mensajes)



### Colas de mensajes POSIX

- **Implementación** de paso de mensajes en POSIX
- Mecanismo de comunicación **y** sincronización
- API similar a la usada para ficheros:
  * `mqd = mq_open("/almacen.txt", O_CREAT | O_WRONLY, 0777, &atributos) ;`
  * `ret = mq_send    (mqd, (const char *)&dato, sizeof(int), 0) ;`
  * `ret = mq_receive (mqd, (      char *)&dato, sizeof(int), 0) ;`
  * `mq_close(mqd);`
  * `mq_unlink("/almacen.txt");`
- Nombrado:
  - **Se asigna nombres de ficheros a las colas** (`"/almacen.txt"` en los ejemplos anteriores de uso del API)
    - **Sólo procesos que comparten un mismo sistema de ficheros pueden utilizar colas de mensajes**
    -   El nombre de la cola permite compartir esta para que múltiples procesos puedan enviar y recibir datos
  - Nombrado indirecto
- Sincronización:
   - Envío asíncrono
   - Recepción síncrona o asíncrona
   -   Semántica bloqueante (por defecto) o no bloqueante (hay que usar `O_NONBLOCK`)
- Comunicación:
  - Flujo de datos **unidireccional** (se precisan dos colas de mensajes para bidireccional)
  - Los mensajes se pueden etiquetar con prioridades
  - Tamaño del mensaje *variable*


### Llamadas POSIX para gestión de colas de mensajes (1/3)

- **Crear** y **abrir** una cola de mensajes
   ```c
   mqd_t mq_open ( char *name, int flag, mode_t mode, struct mq_attr *attr ) ;
   ```
  - Argumentos de entrada:
    - Primer argumento: nombre de la cola
        - Sigue la convención de nombrado de archivos
        - ``man 7 mq_overview``
    - Segundo argumento: **flags** de la cola (fnctl.h)
        - `O_CREAT`: crea una cola si no existe
        - `O_RDONLY`: crea una cola para recibir
        - `O_WRONLY`: crea una cola para enviar
        - `O_RDWR`: crea una cola para recibir y enviar
        - `O_NONBLOCK`: envío y recepción no bloqueante
    - Tercer argumento: permisos de acceso a la cola (sys/stat.h)
        - `S_IRWXU`: lectura, escritura y ejecución para propietario/a
        - `S_IRWXU | S_IRWXG`: lectura, escritura y ejecución para propietario/a y grupo al que pertenece
        - `S_IRWXU | S_IRWXG | S_IRWXO`: lectura, escritura y ejecución para propietario/a, grupo al que pertenece y otras personas en la máquina
    - Cuarto argumento: atributos de la cola (```struct mq_attr attr```)
        -  `attr.mq_maxmsg`: número máximo de mensajes encolados
        - `attr.mq_msgsize`: tamaño máximo del mensaje en bytes que se puede enviar a la cola
  - Devuelve:
    - Un número entero que representa el descriptor de cola o ```(mqd_t) -1``` si hay error
- **Cerrar** una cola de mensajes
   ```c
   int mq_close ( mqd_t mqdes ) ;
   ```
- **Borrar** una cola de mensajes
   ```c
   int mq_unlink ( char *name ) ;
   ```
  * Recordar: **Borrar después de cerrar** la cola de mensajes


### Ejemplo en C: crear, cerrar y borrar

* Edición de ejemplo de crear una cola de mensajes
 
   **mq_crear.c**
   ```c
   #include <stdio.h>
   #include <mqueue.h>
   #include <stdlib.h>

   // Tip: el nombre es un path absoluto (empieza por '/')
   #define NOMBRE_COLA "/almacen.txt"

   int main ( int argc, char *argv[] )
   {
       mqd_t mqd;                  /* Descriptor de la cola */
       struct mq_attr atributos;   /* Atributos de la cola */
    
       atributos.mq_maxmsg = 10;           /* En Linux suele ser 10 para procesos sin privilegios */
       atributos.mq_msgsize = sizeof(int); /* Tamaño de cada mensaje en bytes */

       mqd = mq_open(NOMBRE_COLA, O_CREAT | O_WRONLY, 0777, &atributos) ;
       if (-1 == mqd) {
           perror("mq_open: ");
           exit(-1);
       }

       // ...Usar la cola de mensajes POSIX...

       mq_close(mqd);
       mq_unlink(NOMBRE_COLA);
   }
   ```

* Para compilar, se puede usar:
     ```bash
     gcc -Wall -g mq_crear.c -lrt -o mq_crear
     ```
   -   Es necesario enlazar con la biblioteca **`librt`**

* Para ejecutar, se puede usar:
     ```bash
     user$ ./mq_crear
     ```


### Ejemplo en C: limpieza de colas NO borradas

* Es posible que un programa que trabaja con colas POSIX falle y deje una cola sin borrar. 
   Esto puede suponer un problema, por lo que vamos a estudiar cómo solucionarlo con un ejemplo (`mq_nounlink.c`).
 
   **mq_nounlink.c**
   ```c
   #include <stdio.h>
   #include <mqueue.h>
   #include <stdlib.h>

   #define NOMBRE_COLA "/almacen.txt"

   int main ( int argc, char *argv[] )
   {
       mqd_t mqd;                  /* Descriptor de la cola */
       struct mq_attr atributos;   /* Atributos de la cola */
    
       atributos.mq_maxmsg = 10;           
       atributos.mq_msgsize = sizeof(int); 
       mqd = mq_open(NOMBRE_COLA, O_CREAT | O_WRONLY, 0777, &atributos) ;
       if (-1 == mqd) {
           perror("mq_open: ");
           exit(-1);
       }
       
       // <- ¡ no se borra con unlink(NOMBRE_COLA) !
   }
   ```

* Para compilar, se puede usar:
     ```bash
     gcc -Wall -g mq_nounlink.c -lrt -o mq_nounlink
     ```
   -   Es necesario enlazar con la biblioteca **`librt`**

* Para ejecutar, se puede usar:
     ```bash
     user$ ./mq_nounlink
     ```

 * **Importante**: Las colas POSIX pueden ser visibles desde la línea de mandatos:
   ``` bash
   user$ sudo mkdir /dev/mqueue
   user$ sudo mount -t mqueue none /dev/mqueue
   user$ ls -las /dev/mqueue

   total 0
   0 drwxrwxrwt  2 root   root     60 Jul  4 11:35 .
   0 drwxr-xr-x 12 root   root   3180 Jul  4 11:39 ..
   0 -rwx------  1 user   user     80 Jul  4 11:33 almacen.txt

   user$ cat /dev/mqueue/almacen.txt
   QSIZE:0          NOTIFY:0     SIGNO:0     NOTIFY_PID:0
   ```

  * **Importante**: Hay un máximo de colas POSIX que se pueden crear a la vez (256 en Linux/Ubuntu 24.04):
    ``` bash
    user$ cat /proc/sys/fs/mqueue/queues_max
    256
     ```

  * **Importante**: Si no se borran las colas POSIX que no se usan entonces puede llegar un momento que no se puedan crear más. Para evitar esto, es posible borrar las colas POSIX no usadas desde línea de mandatos:
    ``` bash
    user$ rm /dev/mqueue/*
    user$ ls -las /dev/mqueue/
    
    total 0
    0 drwxrwxrwt  2 root   root     60 Jul  4 11:35 .
    0 drwxr-xr-x 12 root   root   3180 Jul  4 11:39 ..
     ```


### Llamadas POSIX para gestión de colas de mensajes (2/3)

- **Enviar** un mensaje a una cola
   ```c
   int mq_send ( mqd_t mqdes, const char *msg, size_t len, unsigned int prio ) ;
   ```
  - El mensaje `msg` de longitud `len` bytes se envía por la cola de mensajes `mqdes` con prioridad `prio`
  - Argumentos de entrada:
    -   `mqdes`: Descriptor de la cola
    -   `msg`: Buffer que contiene el mensaje a enviar
    -   `len`: Longitud del mensaje a enviar
    -   `prio`: Prioridad del mensaje   Los mensajes se insertan según su prioridad (`0 ... MQ_PRIOMAX`)
   - Devuelve:
     - 0 en caso de éxito o -1 en caso de error
     - Si la cola está llena Y el envío no es bloqueante (O_NONBLOCK) entonces 
        el proceso no se bloquea pero devuelve -1 (EAGAIN)

- **Recibir** un mensaje desde una cola
   ```c
   int mq_receive ( mqd_t mqdes, char *msg, size_t len, unsigned int *prio ) ;
   ```
  - Recibe el mensaje `msg` con mayor prioridad en la cola (`prio`) de longitud `len` bytes de la cola `mqdes`
  - Argumentos de entrada:
    -   `mqdes`: Descriptor de la cola
    -   `msg`: Buffer que contiene el mensaje a recibir
    -   `len`: Longitud del mensaje a recibir
    -   `prio`: Prioridad del mensaje recibido
   - Devuelve:
   - El número de bytes del mensaje recibido o -1 en caso de error.
   - Si la cola está vacía Y la recepción es no bloqueante (O_NONBLOCK) entonces 
     el proceso no se bloquea pero devuelve -1 (EAGAIN) 


### Ejemplo en C: productor-consumidor con colas de mensajes

Idea general de diseño:
* A nivel de procesos
   ```mermaid
   flowchart LR
       Productor --> Consumidor
   ```
* A nivel de código dentro de cada proceso
   <html>
   <table border="1">
   <tr>
   <td>
   <pre>
   Productor() 
   {
       for(;;) {
            &lt;Producir dato&gt;
            <b>send</b>(Consumidor, dato);
        } /* end for */
   }
   </pre>
   </td>
   <td>
   <pre>
   Consumidor()
   {
       for(;;) {
            <b>receive</b>(Productor, dato);
            &lt;Consumir dato&gt;
        } /* end for */
   }
   </pre>
   </td>
   </tr>
   </table>
   </html>


**productor.c**
```c
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 10
#define DATOS_A_PRODUCIR 100000

void Productor ( mqd_t cola )
{
    int dato;
    int i, ret;
    
    for (i = 0; i < DATOS_A_PRODUCIR; i++)
    {
        dato = i; /* Producir dato */
        ret = mq_send(cola, (const char *)&dato, sizeof(int), 0) ;
        if (ret == -1) {
            perror("mq_send: ");
            mq_close(cola);
            exit(1);
        }
    }
}

int main ( int argc, char *argv[] )
{
    /* almacen: cola de mensajes donde dejar los datos producidos y extraer los datos a consumir */
    mqd_t almacen;
    struct mq_attr attr;
    attr.mq_maxmsg = MAX_BUFFER;
    attr.mq_msgsize = sizeof(int);

    almacen = mq_open("/ALMACEN", O_CREAT | O_WRONLY, 0700, &attr) ;
    if (almacen == -1) {
        perror("mq_open: ");
        exit(-1);
    }

    Productor(almacen);
    
    mq_close(almacen);
    return (0);
}
```

**consumidor.c**
```c
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 10
#define DATOS_A_PRODUCIR 100000

void Consumidor ( mqd_t cola )
{
    int dato;
    int i, ret;
    
    for (i = 0; i < DATOS_A_PRODUCIR; i++)
    {
        ret = mq_receive(cola, (char *)&dato, sizeof(int), 0) ;
        if (ret == -1) {
            perror("mq_receive: ");
            mq_close(cola);
            exit(1);
        }
        
        printf("El dato consumido es: %d\n", dato);
    }
}

int main ( int argc, char *argv[] )
{
    mqd_t almacen;

    if ((almacen = mq_open("/ALMACEN", O_RDONLY)) == -1) {
        perror("mq_open: ");
        exit(-1);
    }

    Consumidor(almacen);
    
    mq_close(almacen);
    return (0);
}
```

* Para compilar, se puede usar:
     ```bash
     gcc -Wall -g productor.c -lrt -o productor
     gcc -Wall -g consumidor.c -lrt -o consumidor
     ```

* Para ejecutar, se puede usar:
     ```bash
     user$ ./productor &
     user$ ./consumidor

     El dato consumido es: 0
     El dato consumido es: 1
     ...
     El dato consumido es: 99997
     El dato consumido es: 99998
     El dato consumido es: 99999
     [1]+  Done                    ./productor
     ```
   

### Llamadas POSIX para gestión de colas de mensajes (3/3)

- **Modificar** los atributos de una cola
   ```c
   int mq_setattr(mqd_t mqdes, struct mq_attr *qstat, struct mq_attr *oldmqstat) ;
   ```
  - Argumentos de entrada:
    -   `mqdes`: Descriptor de la cola
    -   `qstat`: Nuevos atributos de la cola
    -   `oldmqqstat`: Si oldmqstat es distinto de NULL entonces se almacenarán en él los antiguos atributos
  - Devuelve:
    - -1 si hay error
        
- **Obtener** los atributos de una cola
   ```c
   int mq_getattr(mqd_t mqdes, struct mq_attr *qstat) ;
   ```
  - Argumentos de entrada:
    -   `mqdes`: Descriptor de la cola
    -   `qstat`: Atributos de la cola
  - Devuelve:
    - -1 si hay error
    - `qstat` modificado con los atributos de la cola:
      - `mq_maxmsg`: Número máximo de mensajes
      - `mq_msgsize`: Tamaño máximo del mensaje
      - `mq_curmsgs`: Número actual de mensajes de la cola
      - `mq_flags`: Flags asociados a la cola


### Ejemplo en C: imprimir los atributos de una cola POSIX

**mq_attr.c**
```c
#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>

int main ( int argc, char *argv[] )
{
    mqd_t mqd;
    struct mq_attr atributos;

    mqd = mq_open("/almacen.txt", O_CREAT | O_WRONLY, 0777, &atributos) ;
    if (mqd == -1) {
        printf("Error mq_open\n");
        exit(-1);
    }

    if (mq_getattr(mqd, &atributos) == -1) {
        printf("Error mq_getattr\n");
        exit(-1);
    }

    printf("Número máximo de mensajes en la cola: %ld\n",      atributos.mq_maxmsg) ;
    printf("Longitud máxima del mensaje en la cola: %ld\n",    atributos.mq_msgsize) ;
    printf("Número de mensajes actualmente en la cola: %ld\n", atributos.mq_curmsgs) ;

    mq_close(mqd);
    exit(0);
}
```

* Para compilar, se puede usar:
     ```bash
     gcc -Wall -g mq_attr.c -lrt -o mq_attr
     ```

* Para ejecutar, se puede usar:
     ```bash
     user$ ./mq_attr

     Número máximo de mensajes en la cola: 10
     Longitud máxima del mensaje en la cola: 4
     Número de mensajes actualmente en la cola: 0
     ```


### Cliente-servidor secuencial con colas POSIX

Idea general del diseño:
* A nivel de procesos:
   ```mermaid
   flowchart LR
       Cliente <--struct peticion--> Servidor
   ```
* A nivel de código dentro de cada proceso:
   <html>
   <table border="1">
   <tr>
   <td>
   <pre>
  Cliente() 
  {
      peticion.cola_cliente <- nombre unívoco 
      peticion.operacion  <- valor
      peticion.argumentos <- valores 
      ...
      sq = mq_open(COLA_SERVIDOR, ...)
      cq = mq_open(peticion.cola_cliente, ...)
      <b>send</b>(sq, &peticion);
      <b>receive</b>(cq, &respuesta, ...)
      mq_close(sq)
      mq_close(cq)
      mq_unlink(peticion.cola_cliente)
      ...
      trabajar con respuesta...
  }
   </pre>
   </td>
   <td>
   <pre>
  Servidor()
  {
     sq = mq_open(COLA_SERVIDOR, ...)
     while(1) {
          <b>receive</b>(sq, &peticion, ...)
          ...
          respuesta <- procesar petición
          ...
          cq = mq_open(peticion.cola_cliente, ...)
          <b>send</b>(cq, &respuesta, ...)
          mq_close(cq)
      } /* end for */
  }
   </pre>
   </td>
   </tr>
   </table>
   </html>
   

**mensaje.h**
```c
#define MAXSIZE 256
#define SUMA   0
#define RESTAR 1
// . . .

struct peticion {
   int op; /* operación, 0 (+) 1 (-) */
   int  a; /* operando 1 */
   int  b; /* operando 2 */
   char q_name[MAXSIZE]; /* nombre de la cola cliente
                            donde debe enviar la respuesta el servidor */
};
```


**servidor.c**
```c
#include "mensaje.h"
#include <mqueue.h>

int main ( int argc, char *argv[] )
{
   mqd_t q_servidor; /* cola de mensajes del servidor */
   mqd_t q_cliente;  /* cola de mensajes del cliente */
   struct mq_attr attr;
   struct peticion pet;
   int res;

   attr.mq_maxmsg = 10;
   attr.mq_msgsize = sizeof(struct peticion);
   q_servidor = mq_open("/SERVIDOR_SUMA", O_CREAT|O_RDONLY, 0700, &attr);
   while(1)
   {
      mq_receive(q_servidor, (char *) &pet, sizeof(pet), 0);
      if (pet.op ==0) 
           res = pet.a + pet.b;
      else res = pet.a - pet.b;

      /* se responde al cliente abriendo previamente su cola */
      q_cliente = mq_open(pet.q_name, O_WRONLY);
      mq_send(q_cliente, (const char *)&res, sizeof(int), 0);
      mq_close(q_cliente);
   }
}
```


**cliente.c**
```c
#include <string.h>
#include <stdio.h>
#include <mqueue.h>
#include <unistd.h>
#include "mensaje.h"

int main ( int argc, char *argv[] )
{
   mqd_t q_servidor; /* cola de mensajes del proceso servidor */
   mqd_t q_cliente;  /* cola de mensajes para el proceso cliente */
   struct mq_attr attr;
   struct peticion pet;
   int res; 
   char queuename[MAXSIZE];

   attr.mq_maxmsg = 1;
   attr.mq_msgsize = sizeof(int);
   sprintf(queuename, "/CLIENTE-%d", getpid()) ; /* generar un nombre único por cliente */
   q_cliente  = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);
   q_servidor = mq_open("/SERVIDOR_SUMA", O_WRONLY);

   /* se rellena la petición y se envía */
   pet.op = 0;
   pet.a = 5;
   pet.b = 2;
   strcpy(pet.q_name, queuename);
   mq_send(q_servidor, (const char *)&pet, sizeof(pet), 0);

   /* se recepciona la respuesta y se imprime */
   mq_receive(q_cliente, (char *) &res, sizeof(int), 0);
   printf("Resultado = %d\n", res);

   /* se cierra y borra las colas POSIX */
   mq_close(q_servidor);
   mq_close(q_cliente);
   mq_unlink(queuename);

   return 0;
}
```


* Para compilar, se puede usar:
     ```bash
     gcc -Wall -g servidor.c -lrt -o servidor
     gcc -Wall -g cliente.c -lrt -o cliente
     ```

* Para ejecutar, se puede usar:
     ```bash
     user$ ./servidor &
     user$ ./cliente
     Resultado = 7
     
     user$  kill -9 %1
     ```



### Otros modelos de colas de mensajes

-   Advanced Message Queueing Protocol (AMQP)
-   Apache ActiveMQ
-   IBM MQ
-   Java Message Service
-   Microsoft Message Queuing


