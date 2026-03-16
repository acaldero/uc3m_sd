

  
# Introducción a los Sistemas Distribuidos
+ **Felix García Carballeira y Alejandro Calderón Mateos** @ arcos.inf.uc3m.es
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

 1. Introducción
     * 1.2. [Conceptos base](#11-conceptos-base)
     * 1.2. [Sistema distribuido](#12-sistema-distribuido)
     * 1.3. [Aplicación distribuida](#13-aplicaci%C3%B3n-distribuida)
     * 1.4. [Evolución hacia los sistemas distribuidos](#14-evoluci%C3%B3n-hacia-los-sistemas-distribuidos)
     <br>
 2. Elementos en las aplicaciones distribuidas
     * 2.1  [Características principales](#21-caracter%C3%ADsticas-principales)
     * 2.2 [Objetivos de un sistema distribuido](#22-objetivos-de-un-sistema-distribuido)
       * 2.2.1. [Transparencia](#221-transparencia)
       * 2.2.2. [Escalabilidad](#222-escalabilidad)
       * 2.2.3. [Consistencia](#223-consistencia)
       * 2.2.4. [Tolerancia a fallos](#224-tolerancia-a-fallos)
       * 2.2.5. [Seguridad](#223-seguridad)
     * 2.3  [Elementos típicos](#23-elementos-t%C3%ADpicos)
       * 2.3.1. [Mecanismo de comunicación](#231-mecanismo-de-comunicaci%C3%B3n)
       * 2.3.2. [Mecanismo de sincronización](#232-mecanismo-de-sincronizaci%C3%B3n)
       * 2.3.3. [Soporte de concurrencia](#233-soporte-de-concurrencia)
       * 2.3.4. [Modelos comunes de arquitectura de comunicación](#234-arquitecturas-de-comunicaci%C3%B3n)


## 1. Introducción

### 1.1 Conceptos base

* ***Host* conectado**: procesador + memoria + subsistema de comunicación
     * **Subsistema de comunicación**: conjunto de componentes hardware y software que proporcionan servicios de comunicación en un sistema distribuido 

* **Red de computadores**: conjunto de *hosts* conectados por medio de una red 
   * ***Host***: es un computador u otros dispositivo que usan la red para propósitos de comunicación. 

* **Protocolo**: conjunto de reglas e instrucciones que gobiernan la comunicación en un sistema distribuido, es decir, el intercambio de paquetes y mensajes.
  * **Mensaje**: objeto lógico que se intercambian entre dos o más procesos 
     * Su tamaño puede ser bastante grande 
     * Un mensaje se descompone en paquetes 
  * **Paquete**: tipo de mensaje que se intercambia entre dos dispositivos de comunicación 
     * Tamaño limitado por el hardware


### 1.2 Sistema distribuido

* **Red de computadores**: 
   * Una red de computadores es un conjunto de computadores conectados por una red de interconexión.
   * Objetivo habitual: compartir impresora o disco remoto.
* **Sistema distribuido**:
   * **Sistema** formado por **recursos de computación** (hardware y software) **físicamente distribuidos** e **interconectados** a través de una **red**, que comunican mediante paso de mensajes y **cooperan** para realizar una determinada **tarea**.
     * Objetivo habitual: compartir recursos y colaborar.
   * Un conjunto de computadores independientes que aparecen ante los usuarios como un único sistema coherente.
* **Sistema paralelo**:
   * **Sistema distribuido** para realizar una determinada **tarea** lo más rápidamente posible.
   * Objetivo habitual:
     * Alto rendimiento (*High Performance Computing*)
     * Alta productividad (*High Throughput Computing*)


### 1.3 Aplicación distribuida

 * **Aplicaciones monolítica (no distribuida)**:
    * Conjunto de procesos que ejecutan en solo un computador, que pueden colaborar y comunicar por memoria compartida.
 * **Aplicaciones distribuidas**:
     * Conjunto de procesos que ejecutan en uno o más computadores que colaboran y comunican intercambiando mensajes.
     * Algunos ejemplos:
       * WorldWide Web (WWW)
       * Correo electrónico (IMAP, POP) 
       * Transferencia de ficheros (FTP)


### 1.4 Evolución hacia los sistemas distribuidos

<html>
<table border="1"><tr valign="top"><td>
</html>

 **~1950: <br>Computación centralizada**
   * Características principales:
     -   **Mainframes centrales**
     -   **Sistemas de tiempo compartido**
     -   **Recursos completamente centralizados**
     -   **Terminales simples** conectados al mainframe
     -   **Interfaces poco amigables**
  * Contexto tecnológico:
     -   Primeras **redes de computadores**
     -   Usuarios dependían completamente del sistema central

<html></td><td></html>

 **~1960/70: <br>Aparición de TCP/IP**
  -   **1969:** creación de **ARPANET**
  -   **1974:** diseño del protocolo **TCP/IP**
* Autores principales:
  -   Vinton G. Cerf
  -   Robert E. Kahn
* Impacto:
  -   Base de Internet
  -   Permite comunicación entre redes heterogéneas

<html></td><td></html>

**~1980: <br>Computación distribuida inicial**

 * Cambios importantes:
   - Aparición de **PCs y estaciones de trabajo**
   - **Estandarización del hardware**
   - Crecimiento del número de computadores
 * Características:
   - Aplicaciones ejecutadas **localmente**
   - Interfaces de usuario más amigables
   - Aparición de **redes de área local (LAN)**
  * Uso de las redes:
    - Compartición de recursos
       - impresoras
       - sistemas de archivos
  * Primeros **sistemas operativos distribuidos**:
    - Mach
    - Sprite
    - Chorus

<html></td><td></html>

 **~1990: <br>Internet y modelo cliente-servidor**

* Características:
  - Crecimiento de **arquitecturas cliente-servidor**
  - Mayor **descentralización**
  - Aplicaciones distribuidas entre cliente y servidor
 * Evento clave:
   - **1991: aparición de la Web**
   - Creada por **Tim Berners-Lee en el CERN**
 * Consecuencias:
   - Explosión del uso de Internet
   - Nuevas aplicaciones:
 * Ejemplos:
   - Comercio electrónico
   - Aplicaciones multimedia
   - Sistemas de control
   - Aplicaciones médicas
   - Supercomputación distribuida

<html></td><td></html>

 **~now: <br>Tendencias modernas**
  - Computación distribuida masiva
  - Sistemas en red global
  - Cloud computing
  - Sistemas móviles
  - Internet de las cosas (IoT)

<html>
</td></tr></table>
</html>


### 1.5 Repaso redes computadores

* Una red de computadores permite:
   - Comunicación entre sistemas
   - Compartición de recursos
   - Transferencia de datos
 <br>
* **Tipos** principales de redes:
   * **LAN (Local Area Network)**
      * Características:
         - Área geográfica pequeña
         - Alta velocidad
         - Baja latencia
      * Ejemplos:
         - Redes de oficina
         - Redes universitarias
   * **WAN (Wide Area Network)**
      * Características:
         - Gran área geográfica
         - Mayor latencia
         - Interconexión de múltiples redes
      * Ejemplo:
         - Internet
 <br>
* **Protocolos de comunicación** más importantes:
   * **TCP**
      - Comunicación fiable
      - Control de errores
      - Orientado a conexión
   * **UDP**
      - No orientado a conexión
      - Menor sobrecarga
      - Mayor velocidad


### 1.6 Repaso memoria compartida versus memoria distribuida

* **Sistemas de memoria compartida**
  * Características:
     - Todos los procesadores acceden a **una memoria común**
     - Comunicación mediante **lectura/escritura en memoria**
  * Ventajas:
     - Programación más sencilla
     - Comunicación rápida
  * Problemas:
     - Escalabilidad limitada
     - Contención de memoria
     - Coste elevado
  * Ejemplos:
     - Multiprocesadores
     - Sistemas SMP
<br>
* **Sistemas de memoria distribuida**
  * Características:
     -   Cada nodo tiene **su propia memoria local**
     -   Comunicación mediante **intercambio de mensajes**
  * Ventajas:
     -   Mayor escalabilidad
     -   Mejor tolerancia a fallos
     -   Coste menor
  * Problemas:
     -   Programación más compleja
     -   Coste de comunicación
  * Ejemplos:
     -   Clusters
     -   Sistemas distribuidos


## 2. Elementos en las aplicaciones distribuidas

### 2.1 Características principales

* **Múltiples componentes autónomos**
  * Única forma de comunicación y sincronización: basado en paso de mensajes.
* **Concurrencia**
   - Múltiples procesos ejecutándose simultáneamente.
* **Ausencia de reloj global**
   - No existe un reloj único que permita coordinar las acciones de los programas que ejecutan en el sistema.
* **Fallos independientes**
   - Cada nodo puede fallar de forma independiente.
* Software más complejo


### 2.2 Objetivos de un sistema distribuido

Objetivos y aspectos de diseño de un sistema distribuido:
* <ins>Compartición de recursos</ins>
* <ins>Mejor rendimiento</ins>
* <ins>Transparencia</ins>: parecer un sistema único en todo lo posible
* <ins>Escalabilidad</ins>: capacidad de crecimiento
* <ins>Tolerancia a fallos</ins>: seguir funcionando en presencia de fallos
* <ins>Seguridad</ins>: acceso seguro a los recursos
* <ins>Calidad de servicio (QoS)</ins>


#### 2.2.1 Transparencia

* La transparencia intenta que el sistema distribuido **parezca un sistema único**.
* Tipos principales:
   * **Transparencia de acceso**
     * Acceso uniforme a recursos locales o remotos.
   * **Transparencia de localización**
     * El usuario no necesita conocer dónde está el recurso.
   * **Transparencia de migración**
     * Los recursos pueden cambiar de ubicación sin afectar al usuario.
   * **Transparencia de replicación**
     * Múltiples copias de recursos sin que el usuario lo perciba.
   * **Transparencia de concurrencia**
     * Varios usuarios acceden simultáneamente a los recursos.
   * **Transparencia frente a fallos**
     * El sistema oculta fallos de componentes.


#### 2.2.2	 Escalabilidad

* Capacidad del sistema para crecer en:
   - Número de usuarios
   - Recursos
   - Nodos
* Para que un sistema con ``n`` usuarios sea escalable,
   la cantidad de recursos necesarios para soportarlo debería ser proporcional a ``n`` ó ``O(n)``.
* Tipos:
   - Escalabilidad de tamaño
   - Escalabilidad geográfica
   - Escalabilidad administrativa
* Técnicas de escalabilidad:
   * **Replicación**
      * Datos: múltiples copias del mismo dato
      * Procesos: múltiples ejecuciones de la misma computación
   * **Caching**
      * Copias locales de datos recientemente o más utilizados
   * **Distribución**
      * Distribución de carga en múltiples nodos
         * DNS, DHT
* La replicación y las técnicas de caching pueden introducir problemas de consistencia y coherencia


#### 2.2.3	 Consistencia

El problema de la consistencia (coherencia) surge cuando varios procesos acceden y actualizan datos de forma concurrente
* Coherencia de las actualizaciones
* Coherencia de la replicación
* Coherencia de caches
* Coherencia ante fallos
* Relojes consistentes


#### 2.2.4	 Tolerancia a fallos

* El sistema debe seguir funcionando cuando:
   - Falla un nodo
   - Falla una red
   - Falla un componente
*  Técnicas:
   - Replicación
   - Recuperación
   - Redundancia


#### 2.2.5  Seguridad

 - **Autenticación**:  verifica la identidad del usuario/a.
 - **Confidencialidad**: asegura que solo los autorizados accedan a los datos.
 - **Integridad**: garantiza que los datos no sean modificados indebidamente.
 - **Control de acceso**: define y limita qué puede hacer cada usuario/a autenticado/a. 


### 2.3 Elementos típicos

* <ins>Comunicación y sincronización</ins> 
   * Mecanismo de **comunicación**: intercambio de información entre procesos
   * Mecanismo de **sincronización**: eventos que controlan la ejecución en un proceso dependiente de un evento
* <ins>Soporte de **concurrencia**</ins>:
     * **Secuencial**: se ejecuta las peticiones de una en una
     * **Concurrente**: se ejecutan peticiones a la vez.
          * **Modelo de concurrencia**: maestro/trabajadores, lectores/escritores, productor/consumidor, etc.
* Estructura de software: <ins>modelo de arquitectura distribuida</ins>:
 	 * Cliente/servidor entorno al 80% de las veces.
  	 * Publish/subscribe, Peer-to-peer,  etc.
* <ins>Heterogeneidad</ins> de los componentes
   * Es la variedad y diferencia de los siguientes componentes: redes, lenguajes de programación, etc.
   * Ayuda: empleo de sistemas abiertos y estándares
* <ins>Nombrado</ins> 
    * Notación humana -> notación máquina
      * Los/as usuarios/as designan a los objetos mediante un nombre (ej.: www.uc3m.es)
      * Los programas designan a los objetos mediante un identificador (ej.: 163.117.100.10)
      * Resolver un nombre implica obtener el identificador a partir del nombre.
    * Objetivo importante: los nombres deben ser independientes de su localización.


#### 2.3.1 Mecanismo de comunicación

* **Tipos** de mecanismos:
    * <ins>Básicos</ins>:
       * **Memoria compartida**
       * **Paso de mensajes**
    * <ins>Colaterales</ins>:
      * Ficheros
      * Correos
      * Etc.
<br>
* **Paradigmas** (moldes/patrones): usando los mecanismos de comunicación básicos se han construido otros mecanismos de comunicación que se pueden clasificar atendiendo al paradigma de comunicación usado:
  * **Paso de mensajes**
     * Modelo típico en sistemas distribuidos.
     * Características:
        - Comunicación explícita
        - Envío y recepción de mensajes
     * Ejemplo:
        - Sockets
  * **Invocación remota (RPC)**
     * Permite llamar a funciones en otro computador como si fueran locales.
     * Ventajas:
       - Simplifica la programación
     * Problemas:
        - Latencia
        - Manejo de fallos
  * **Comunicación orientada a mensajes**
     * Se usan sistemas intermedios:
        - Colas de mensajes
        - Middleware
     * Ejemplo:
        - Sistemas de mensajería


#### 2.3.2. Mecanismo de sincronización

* Mecanismos **en memoria compartida**:
   * Semáforos 
   * Mutex y variables condicionales 
* Mecanismos de comunicación **en memoria distribuida** usados también para sincronizar (mecanismos **colaterales**):
  * Tuberías (pipes, FIFOs)
  * Paso de mensajes
* **Otros**:
   * Señales (asincronismo)
   * Etc.


#### 2.3.3. Soporte de concurrencia

* Servidores **secuenciales**:
  ```mermaid
  graph LR
  A{Recurso}
  B((Servidor))
  C[Cliente_1]
  D[Cliente_2]
  E[...]
  
  C <-- petición/respuesta --> B
  D <-- petición/respuesta --> B
  E <-- petición/respuesta --> B
  B --- A
  ```

* Servidores **concurrentes**:
  ```mermaid
  graph TD
  A@{ shape: cyl, label: "Recurso" }
  B((Servidor))
  C@{ shape: procs, label: "Hilo de servicio"}
  D[Cliente_1]
  
  D <-- petición --> B
  C <-- respuesta --> D
  B --- A
  B <-- crear hilo de servicio --> C
  ```

     * **Modelos de concurrencia** más frecuentes:
       * Productor/Consumidor
       * Lectores/Escritores     
       * Etc.


#### 2.3.4. Arquitecturas de comunicación

* Modelos más conocidos de arquitectura en aplicaciones distribuidas:
   * **Cliente-Servidor**
     * Modelo más común.
     * Componentes:
        - **Cliente**: solicita servicios
        - **Servidor**: proporciona servicios
     * Ventajas:
        - Organización clara
        - Fácil mantenimiento
     * Problemas:
        - Posible cuello de botella
        - Dependencia del servidor
   * **Peer-to-Peer (P2P)**
     * Todos los nodos pueden actuar como:
        - Clientes
        - Servidores
     * Características:
        - Descentralización
        - Mayor escalabilidad
     * Ejemplos:
        - Redes de intercambio de archivos
* Otros modelos:
  * Publish/subscribe (Pub/Sub)
  * Etc.
* Es posible usar modelos conocidos o distintas mezclas de estos modelos.


