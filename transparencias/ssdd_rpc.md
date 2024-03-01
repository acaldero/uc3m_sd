# Comunicación con RPC
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ Licencia [GPLv3.0](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

 * Introducción a RPC
   * [Motivación: transparencia de invocación y generación automática](#llamadas-a-procedimientos-remotos--objetivo)
   * [Breve historia](#breve-historia-de-las-rpc)
   * [Estructura de las RPC](#estructura-de-las-rpc)
 * Ejemplos de uso de RPC
   * [Desarrollando con las RPC: suma remota](#desarrollando-con-las-rpc)
   * [Calculadora remota](#calculadora-remota)
 * Aspectos adicionales
   * [RPC en Ubuntu](#rpc-en-ubuntu)
   

## Llamadas a procedimientos remotos: objetivo

 * **Objetivo**: hacer que una aplicación distribuida se programe lo más igual posible que una aplicación no distribuida
   * Mediante el modelo RPC la comunicación se realiza conceptualmente igual que una invocación de un procedimiento local.
    ```mermaid
    sequenceDiagram
      ProcesoA  ->>+  ProcesoB: proc1(arg1, arg2)
      ProcesoB  ->>+  ProcesoA: proc2(arg1)
      ProcesoA  ->>+  ProcesoB: proc3(arg1, arg2, arg3)
    ```
 * Hay **dos ingredientes principales**:
    * Código de invocación remota lo más transparente posible.
    * Generación lo más automatizada posible del código de invocación remota.
    

## (1/2) Transparencia de invocación remota

 * Uno de los ingredientes es la transparencia de la invocación remota: se busca que código de invocación remota lo más transparente posible, de manera que se parezca a una invocación a una función local.
 
 * En el siguiente ejemplo a la izquierda se muestra los elementos de una aplicación no distribuida con llamada local a la función de sumar. A la izquierda se muestra la misma aplicación con una llamada remota a la función de sumar:
       ![Organización del código para invocación remota mediante colas POSIX](./ssdd_rpc_drawio_10.svg)<img src="./transparencias/ssdd_rpc_drawio_10.svg">

    * El código del stub_servidor y del stub_cliente oculta a la función "main(...)" los detalles de que la ejecución es remota.
    * El componente biblioteca de la aplicación pasa a estar en otro proceso, y se comunican en este ejemplo usando colas POSIX.


## (2/2) Generación automática

 * El otro ingrediente es la generación lo más automatizada posible del código de invocación remota, es decir, que el stub_servidor y stub_cliente se pueda obtener de forma automática a partir de la definición de la interfaz de las funciones remotas (sumar, etc. para el ejemplo anterior)
 
 * De esta forma:
    * Se facilita la generación de nuevas aplicaciones distribuidas así como transformar aplicaciones existentes a distribuidas
    * Se garantiza que el código generado se base en una gramática que puede validarse (el código funcione).


## Breve historia de las RPC

 * RPC (Remote Procedure Call): llamadas a procedimientos remotos
   * Por Birrel y Nelson (1985) en “Implementing Procedure Calls”
 * Híbrido:
    * Llamadas a procedimientos
    * Paso de mensajes
 * Las RPC constituyen el núcleo de muchos sistemas distribuidos
   * Llegaron a su culminación con DCE (Distributed Computing Environment)
   * Han evolucionado a invocación de métodos remotos (CORBA, RMI) e invocación de servicios (Web Services)


## Estructura de las RPC

 * Las RPC ofrecen una interfaz sencilla para construir aplicaciones distribuidas sobre TCP/IP

   ![Pila software con RPC y marshalling](./ssdd_rpc_drawio_10.svg)<img src="./transparencias/ssdd_rpc_drawio_13.svg">

  * De forma general, los elementos que participan son:
     * Un cliente **activo**, que realiza una RPC al servidor
          * El stub_cliente realiza una comunicación cliente/servidor, enviando una petición al stub_servidor
          * En la petición del cliente se envía un mensaje que contiene, al menos, el código de operación y los argumentos.
     * Un servidor **pasivo**, que realiza el servicio y devuelve el resultado de la RPC al cliente
          * El stub_servidor responde a la petición del cliente
          * En la respuesta al cliente se envía un mensaje que contine, al menos, el resultado de la función invocada. 

      ![Cliente, stub_cliente, stub_servidor y servidor](./ssdd_rpc_drawio_16.svg)<img src="./transparencias/ssdd_rpc_drawio_16.svg">

  * Conceptos básicos:
     * Un **servicio de red** es una colección de uno o más programas remotos
     * Un **programa remoto** implementa uno o más procedimientos remotos 
     * Un **procedimiento remoto**, sus parámetros y sus resultados se especifican en un fichero de especificación del protocolo escrito en un lenguaje de especificación de interfaces (IDL)
     * Un servidor puede soportar más de una **versión de un programa remoto**
        * Permite al servidor ser compatible con las actualizaciones del servicio
     * Un **suplente** (stub o proxy) es responsable de convertir los parámetros y resultados durante el procedimiento remoto, además de enviar y recibir dichos valores mediante mensajes.
        * Los suplentes (stub_cliente y stub_servidor) son independientes de la implementación que se haga del servidor.
        * Son dependientes de la interfaz del servicio
        * Se generan **automáticamente** por el software de RPC


## Desarrollando con las RPC

 1. Definir la interfaz de servicio un lenguaje de definición de interfaces (IDL):
	 * Hay que definir cada operación, sus argumentos de entrada y salida, así como sus resultados

      ### Ejemplo: suma.x
     ```c
     program SUMAR {  
        version SUMAVER {  
           int SUMA(int a, int b) = 1;  
        } = 1;  
     } = 99;
    ```

 2. Compilación de la interfaz:
	 * Se utiliza un compilador que a partir de la interfaz IDL genera los archivos que se encargan de las comunicaciones del lado del cliente y del servidor.

      ### Ejemplo: rpcgen
     ```bash 
     rpcgen -N -M -a suma.x  
     ```

 3. Se implementa el servicio en el lado del servidor.

    ### Ejemplo: suma_server.c
    ```c
    #include "suma.h"

    bool_t suma_1_svc ( int a, int b, int *result,  
                        struct svc_req *rqstp )
    {
        *result = a + b;
      	return TRUE;
    }

    int sumar_1_freeresult ( SVCXPRT *transp, 
                             xdrproc_t xdr_result, caddr_t result )
    {
    	xdr_free (xdr_result, result);
    	return 1;
    }
    ```

 4. Se implementación el cliente que hace uso de la interfaz en el lado del cliente.

    ### Ejemplo: suma_client.c
    ```c
    #include "suma.h"

    void sumar_1 ( char *host, int a, int b )
    {
        CLIENT *clnt ;
        enum clnt_stat retval ;
        int result ;

        clnt = clnt_create (host, SUMAR, SUMAVER, "udp");
        if (clnt == NULL) {
            clnt_pcreateerror (host);
            exit (-1);
        }
        retval = suma_1(a, b, &result, clnt);
        if (retval != RPC_SUCCESS) {
            clnt_perror (clnt, "call failed");
        }
        clnt_destroy (clnt);
        return result ;
    }
    
    int main ( int argc, char *argv[] )
    {
      if (argc < 2) {
          printf ("Uso: %s <host>\n", argv[0]);
          exit (-1);
      }
      sumar_1 (argv[1]);
      return 0 ;
    }
    ```

 5. Se compila y genera los ejecutables en el lado del cliente y del servidor.

      ### Ejemplo: compilación individual
    ```bash
    gcc –c suma_xdr.c
    gcc –c suma_svc.c
    gcc –c suma_clnt.c
    gcc –c suma_client.c
    gcc –c suma_server.c
    gcc suma_xdr.o suma_clnt.o suma_client.o –o cliente
    gcc suma_xdr.o suma_svc.o suma_server.c –o servidor
    ```

## Lenguaje IDL

 * Un Lenguaje de Definición de Interfaz (IDL) permite especificar una **interfaz**:
    * **Nombre de servicio** que utilizan los clientes y servidores
    * **Nombres de procedimientos**
    * **Parámetros de los procedimientos**
       * Entrada
       * Salida
    * **Tipos de datos** de los argumentos.
    * Puede incluir opciones de comunicación.

 * La interfaz es compartida por cliente y servidor.
   * Los compiladores pueden diseñarse para que los clientes y servidores se escriban en lenguajes diferentes

      ![IDL, stubs y cliente/servidor](./ssdd_rpc_drawio_36.svg)<img src="./transparencias/ssdd_rpc_drawio_36.svg">

 * Programación con un paquete de RPC:
   * El programador debe proporcionar:
      * La **definición de la interfaz** (IDL)
         * Nombres de los procedimientos
         * Parámetros que el cliente pasa al servidor
         * Resultados que devuelve el servidor al cliente
      * El **código del cliente**
      * El **código del servidor**
   * El compilador de IDL genera :
      * El **suplente** (stub) **del cliente**
      * El **suplente** (stub) **del servidor**


## Aplanamiento (marshalling)

 * Los parámetros son **aplanados** (*marshalling*) para resolver los **problemas** en la representación de los datos:
   * Servidor y cliente pueden ejecutar en máquinas con arquitecturas distintas (número bits, ordenamiento de bytes, etc.)
   * No es posible enviar un puntero dado que cliente y servidor tienen un espacio de direcciones distinto.

 * Posibles esquemas de representación de datos:
   * **XDR** (e**X**ternal **D**ata **R**epresentation) es un estándar que define la representación de tipos de datos (**RFC 1832**)
   * **CDR** es la representación común de datos de CORBA.
   * **XML** (e**X**tensible **M**arkup **L**anguage) es un metalenguaje basado en etiquetas definida por W3C
   * **JSON** (**J**ava**S**cript **O**bject **N**otation) formato de texto ligero para el intercambio de datos.

 * Ejemplo:  'Smith', 'Paris', 1934
        ![Comparación entre XDR, CDR, XML y JSON](./ssdd_rpc_drawio_40.svg)<img src="./transparencias/ssdd_rpc_drawio_40.svg">


## Localización y enlazado (*binding*)

 * **Servicio de enlace**: servicio que permite establecer la asociación entre el cliente y el servidor:
    * Implica **localizar al servidor** que ofrece un determinado servicio
    * El servidor debe **registrar su dirección** en un servicio de nombres gestionado por un servidor de enlazado dinámico (*binder*)

 * El **enlazador dinámico (*binder*)** es el **servicio** que mantiene una **tabla de traducciones** entre **nombres de servicio** y **direcciones**.  Incluye funciones para:
    * Registrar un nombre de servicio
    * Eliminar un nombre de servicio
    * Buscar la dirección correspondiente a un nombre de servicio
 * Cómo **localizar** al enlazador dinámico:
   1. Ejecuta en una dirección fija de un computador fijo
   2. El sistema operativo se encarga de indicar su dirección
   3. Difundiendo un mensaje (*broadcast*) cuando los procesos comienzan su ejecución.

* Los pasos para el registro y enlace son:
   1. Servidor obtiene dirección
   2. Registra dirección
   3. Busca servidor
   4. Devuelve dirección
   5. Petición
   6. Respuesta
   7. Borra dirección (fin del servicio)

     ```mermaid
   flowchart TD
       subgraph id1 [ ]
       A["Cliente"]
       B["Servidor"]
       C["Binder"]
       end
       B -.->|"(1)"| B
       B -->|"(2)"| C
       B -->|"(7)"| C
       A -->|"(3)"| C
       C -->|"(4)"| A
       A -->|"(5)"| B
       B -->|"(6)"| A
     ```

## Tipos de fallos que pueden aparecer con las RPC

   * El cliente no es capaz de localizar al servidor
      * Posibles soluciones:  
        * Revisar si servidor caído
        * Revisar que no se use una versión antigua del servidor
   * Pérdidas de mensajes
      *  Se pierde el mensaje de petición del cliente al servidor
          * Posible solución:
            * Se activa un temporizador después de enviar el mensaje y **si no hay respuesta se retransmite el mensaje**.
      *  Se pierde el mensaje de respuesta del servidor al cliente
         * Posibles soluciones: 
           * Si es una operación **idempotente** (se pueden repetir y devuelven el mismo resultado) no hay problema. 
           * Con operación **no idempotente** hay que descartar las peticiones ya ejecutadadas: hay que añadir **un número de secuencia y un campo para indicar si es original o retransmisión** en el cliente y guardar un histórico de las peticiones anteriores y su respuesta para no ejecutar de nuevo en el servidor.
   * El servidor falla después de recibir una petición
     * Posibles soluciones:
        * **No garantizar nada**
        * Semántica **al menos una vez**: reintentar y garantizar que la RPC se realiza al menos una vez (cuidado con operaciones no idempotentes)
        * Semántica **a lo más una vez**: no reintentar, puede que no se realice ni usa sola vez
        * Semántica de **exactamente una**
   * El cliente falla después de enviar una petición
     * Posible solución: 
       * Disponer de la posibilidad de cancelar una operación en curso.


## Características que definen una RPC

* Tipos de IDL:
     *  Integrado con un lenguaje de programación (Cedar, Argus, RMI de Java)
     *  Lenguaje de definición de interfaces específico para describir las interfaces entre los clientes y los servidores (RPC de Sun/ONC, RPC de DCE, CORBA, Google RPC)

* Tipos de parámetros:
  * Parámetro de entrada (in)
     * El parámetro se envía del cliente al servidor
  *  Parámetro de salida (out)
     * El parámetro se envía del servidor al cliente
  *  Parámetro de entrada/salida (inout)

 * Modelos de RPC
    * RPC síncronas: petición y respuesta
    * RPC asíncronas: solo petición
       * El cliente no espera la respuesta
       * No admite parámetros de salida
       * Ejemplo en CORBA: métodos *oneway*

 * Posibles esquemas de representación de datos:
   * **XDR** (e**X**ternal **D**ata **R**epresentation) 
   * **CDR** es la representación común de datos de CORBA.
   * **XML** (e**X**tensible **M**arkup **L**anguage) es un metalenguaje basado en etiquetas definida por W3C
   * **JSON** (**J**ava**S**cript **O**bject **N**otation) formato de texto ligero para el intercambio de datos.

 * Tipos de **conversión de datos**:
    * Conversión de datos **asimétrica**:
       * El cliente convierte a la representación de datos del servidor
    * Conversión de datos **simétrica**:
       * El cliente y el servidor convierten a una representación de
datos estándar
       * ONC-RPC utiliza representación de datos simétrica

 * Tipos de **tipados**:
    * Tipado **explícito**:
       * Cada dato enviado incluye el valor y su tipo
    * Tipado **implícito**:
       * Cada dato enviado solo incluye el valor, no se incluye el tipo
      * ONC-RPC utiliza tipado implícito

* Tipos de **enlace**:
   * Enlace **no persistente**: el enlace entre cliente y servidor **se estable en cada RPC**
      * Más tolerante a fallos
      * Permite migración de servicios
   * Enlace **persistente**: el enlace **se mantiene después de la primera RPC**
     *  Mejor rendimiento en aplicaciones con muchas RPC repetidas
     * Problemas si los servidores cambian de lugar
    * Modelos **híbridos**

 * Tipos de indicaciones de error:
   * Devolver un **código de error** (-1 / NULL)
      * A evitar: que el código de error está dentro del rango de posibles valores, como por ejemplo -1 para sumar(a,b)
   * **Elevar una excepción**
      * Precisa un lenguaje que tenga excepciones

 * Estrategias ante fallos:
    * Cliente RPC
      * Reenviar petición tras temporizador
      * Incluir identificador de petición (número de secuencia)
    * Servidor RPC
      * Analizar número de secuencia para filtrar peticiones duplicadas (guardar histórico y no ejecutar de nuevo peticiones repetidas)
      * Ofrecer semántica:
        * **No garantizar nada**
        * **Al menos una vez**: reintentar y garantizar que la RPC se realiza al menos una vez (cuidado con operaciones no idempotentes)
        * **A lo más una vez**: no reintentar, puede que no se realice ni usa sola vez
        * **Exactamente una**

 * Tipos de protocolos usado:
   * ¿El protocolo es orientado a conexión?
      * Orientado a conexión
      * No orientado a conexión
   * ¿El protocolo está estandarizado?
      * Estándar (por ejemplo TCP o UDP)
      * Específico (no estándard)


## RPC de Sun/ONC

(58-59)

 * Breve historia:
   * Diseñado inicialmente para el sistema de ficheros NFS
   * Descrito en RFC 1831
   * También se denomina ONC-RPC (*Open network computing*)

 * Características:
    * Se puede usar tanto UDP como TCP
       * Cliente y servidor deben estar de acuerdo en el protocolo de transporte a utilizar
    * **Semántica al menos una vez**
    * Lenguaje de definición de interfaces **XDR**
    * **Tipado implícito**
    * **Representación de datos simétrica**
    * Incluye:
       * Un generador de suplentes (stubs) llamado rpcgen 
       * Bibliotecas de funciones de soporte de las RPC (<rpc/rpc.h>)
       * Servicio de registro de procedimientos (*portmapper* o *rpcbind*)

 * Soporte:
   * Para C en UNIX/Linux, Windows, etc.
   * Para Java
      * http://sourceforge.net/projects/remotetea/


## XDR 

 * Principales características:
   * Utiliza representación big-endian
   * No utiliza protocolo de negociación
   * Todos los elementos en XDR son múltiplos de 4 bytes
   * La transmisión de mensajes utiliza tipado implícito (el tipo de datos no viaje con el valor)
   * Utiliza conversión de datos simétrica
   * Los datos se codifican en un flujo de bytes
   * Gestión de memoria: las RPC no reservan memoria dinámica. 
      * El servidor tiene que reservar memoria e implementarse xxx_freeresult(...) correspondiente.
      * El cliente tiene que reservar memoria antes de invocar a la RPC y liberar luego con xdr_free(...)

### Constantes

 * Definición de **constantes**:
    * En XDR:
      ```c
      const MAX_SIZE = 8192;
      ```
    * Traducción a C:
       ```c
      #define MAX_SIZE 8192
      ```

### Tipos básicos

 * Definición de **entero con signo**:
    * En XDR:
      ```c
      int a;
      ```
    * Traducción a C:
       ```c
      int a;
      ```

 * Definición de **entero sin signo**:
    * En XDR:
      ```c
      unsigned a;
      ```
    * Traducción a C:
       ```c
      unsigned int a;
      ```

 * Definición de **coma flotante**:
    * En XDR:
      ```c
      float a; double c;
      ```
    * Traducción a C:
       ```c
      float a; double c;
      ```

 * Definición de **cadena de longitud fija**:
    * En XDR:
      ```c
      string a<37>;
      ```
    * Traducción a C:
       ```c
      char *a;
      ```
     * Al transmitir por red, se envía primero la longitud (37) y luego la secuencia de caracteres ASCII.

 * Definición de **cadena de longitud variable**:
    * En XDR:
      ```c
      string b<>;
      ```
    * Traducción a C:
       ```c
      struct {
          u_int  b_len;
          char  *b_val;
      } b ;
      ```

 * Definición de **vectores de tamaño fijo**:
    * En XDR:
      ```c
      int a[12];
      ```
    * Traducción a C:
       ```c
      int a[12];
      ```

 * Definición de **vectores de tamaño variable**:
    * En XDR:
      ```c
      int d<>; int d<MAX>;
      ```
    * Traducción a C:
       ```c
      struct {
          u_int  d_len;
          char  *d_val;
      } d ;
      ```

 * Definición de **cadena de bytes de tamaño fijo**:
    * En XDR:
      ```c
      opaque a[20];
      ```
    * Traducción a C:
       ```c
      char a[20];
      ```

 * Definición de **cadena de bytes de tamaño variable**:
    * En XDR:
      ```c
      opaque b<>;
      ```
    * Traducción a C:
       ```c
      struct {
          u_int  a_len;
          char  *a_val;
      } a ;
      ```

### Tipos nuevos

 * Definición de **tipos enumerados**:
    * En XDR:
      ```c
      enum color {
        ROJO = 0,
        VERDE = 1,
        AZUL = 2
      };
      ```
    * Traducción a C:
       ```c
      enum color {
        ROJO = 0,
        VERDE = 1,
        AZUL = 2
      };
      typedef enum color color;
      bool_t xdr_color (XDR *, colortype*);
      ```

 * Definición de **estructuras**:
    * En XDR:
      ```c
      struct punto {
        int x;
        int y;
      };
      ```
    * Traducción a C:
       ```c
      struct punto {
        int x;
        int y;
      };
      typedef struct punto punto;
      bool_t xdr_punto (XDR *, punto*);
      ```

 * Definición de **uniones**:
    * En XDR:
      ```c
      union resultado switch (int error) {
        case 0:
           int n;
        default:
           void;
      } ;
      ```
    * Traducción a C:
       ```c
      struct resultado {
        int error;
        union { 
           int n;
        } resultado_u ;
      } ;
      typedef struct resultado resultado;
      bool_t xdr_resultado (XDR *, resultado*);
      ```

 * **Definición de tipos nuevos**:
    * En XDR:
      ```c
      typedef punto puntos[2];
      ```
    * Traducción a C:
       ```c
      typedef punto puntos[2];
      ```

 * Definición de **lista enlazada**:
    * En XDR:
      ```c
      struct lista {
         int x;
         lista *next;
      }
      ```


## Calculadora remota

1. Crear el archivo de interfaz suma.x
    ### suma.x
   ```c
   program SUMAR {  
      version SUMAVER {  
         int SUMA(int a, int b) = 1;  
         int RESTA(int a, int b) = 2;  
      } = 1;  
   } = 99;
   ```

2. Hay que usar prcgen con suma.x:
   ```bash 
   rpcgen -NMa suma.x  
   ```

3. Hay que editar suma_server.c y añadir el código de los servicios a ser invocados de forma remota:
   ### suma_server.c
   ```c
   #include "suma.h"

   bool_t suma_1_svc(int a, int b, int *result,  struct svc_req *rqstp)
   {
     	bool_t retval;

     	/*  insert server code here */
   	   *result = a + b;
     	retval = TRUE;

     	return retval;
   }

   bool_t resta_1_svc(int a, int b, int *result,  struct svc_req *rqstp)
   {
     	bool_t retval;

     	/*  insert server code here */
   	   *result = a - b;
     	retval = TRUE;

    	return retval;
   }

   int sumar_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
   {
   	xdr_free (xdr_result, result);

	   /*
   	 * Insert additional freeing code here, **if needed**
   	 */

   	return 1;
   }
   ```

4. Hay que editar suma_cliente.c y cambiar el código inicial de ejemplo que usa los servicios remotos con el deseado.
 
5. Compilar el ejemplo con:
   ```bash
   make -f Makefile.suma  
    ```
   Dicho proceso de compilación suele suponer los siguientes pasos:

   ```bash
    gcc –c suma_xdr.c
    gcc –c suma_svc.c
    gcc –c suma_clnt.c
    gcc –c suma_client.c
    gcc –c suma_server.c
    gcc suma_xdr.o suma_clnt.o suma_client.o –o cliente
    gcc suma_xdr.o suma_svc.o suma_server.c –o servidor
    ```


## RPC en Ubuntu

Hay 3 detalles a comprobar en su instalación de Ubuntu:

1) Hay que tener instalado los siguientes paquetes:
    libtirpc-common
    libtirpc-dev
    libtirpc3
    rpcsvc-proto
    rpcbind  

3) Hay que editar el Makefile.suma y comprobar que está lo indicado destacado entre '**':
    ```make
    ...  
    CFLAGS += -g **-I/usr/include/tirpc**
    LDLIBS += -lnsl -lpthread -ldl **-ltirpc**  
    ...
    ```
5) Se ha de arrancar rpcbind. Si hay un error al arrancar por favor pruebe lo siguiente:
   ```bash
   sudo mkdir -p /run/sendsigs.omit.d/  
   sudo /etc/init.d/rpcbind restart   
   ```


