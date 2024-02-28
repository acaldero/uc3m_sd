# Comunicación con RPC
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ Licencia [GPLv3.0](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

 * Introducción a RPC
   * [Motivación](#llamadas-a-procedimientos-remotos--objetivo)
   * [(1/2) Transparencia de invocación remota](#-1-2--transparencia-de-invocación-remota)
   * [(2/2) Generación automática](#-2-2--generación-automática)
 * Ejemplos de uso de RPC
   * [(1/2) Suma remota](#suma-remota)
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
       ![Alt text](./ssdd_rpc_drawio_10.svg)<img src="./transparencias/ssdd_rpc_drawio_10.svg">

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

   ```mermaid
   flowchart TD
      A["Aplicaciones/Servicios"]
      B["RMI y **RPC**"]
      C["Aplanamiento (marshalling), representación externa de datos"]
      D["Sockets"]
      E["Protocolo de transporte<br>UDP y TCP"]
      subgraph  
      A --- B
      B --- C
      C --- D
      D --- E
      end
   ```

  * De forma general, los elementos que participan son:
       ![Alt text](./ssdd_rpc_drawio_16.svg)<img src="./transparencias/ssdd_rpc_drawio_16.svg">

    * Entre el stub_cliente y stub_servidor se utiliza una comunicación cliente/servidor, donde el cliente hace una petición y el servidor responde a dicha petición.
    * En la petición del cliente se envía un mensaje que contiene, al menos, el código de operación y los argumentos.
    * En la respuesta al cliente se envía un mensaje que contine, al menos, el resultado de la función invocada.



## Suma remota

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


