
# Sistemas de ficheros distribuidos  
+ **Felix García Carballeira y Alejandro Calderón Mateos**  
+ Licencia [GPLv3.0]([https://github.com/acaldero/uc3m_sd/blob/main/LICENSE](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE))  
  
  
## Contenidos  
  
* Introducción a sistemas de ficheros  
  * [Sistema de ficheros](#sistema-de-ficheros)  
  * [Arquitectura básica de un sistema de ficheros](#arquitectura-basica-de-un-sistema-de-ficheros)
* Sistemas de almacenamiento remotos  
  * [Sistema de ficheros remoto](#sistema-de-ficheros-remoto)  
  * [Sistema de ficheros distribuido](#sistema-de-ficheros-distribuido)  
  * [Sistema de ficheros paralelo](#sistema-de-ficheros-paralelo)  
  
  
  
## Sistema de ficheros  
  
* En una máquina Von Neumann, tanto los datos como el código de un programa ha de estar cargado en memoria principal para ejecutar:  
  ```mermaid  
  flowchart LR  
  A[CPU] <--> B(Memoria principal)  
  ```  
  
* A día de hoy hay dos tecnologías principales para el almacenamiento:  
  ```mermaid  
  flowchart LR  
  A[CPU] <--> B(Memoria)  
  B[Memoria] <--> C(Disco)  
  ```  
  * Memoria RAM  
    * **Volátil** (se pierde contenido si falta electricidad)  
    * **Menor** capacidad (orden de Gigabyte)  
    * Direccionamiento a nivel de **byte**  
  * Disco  
    * **NO Volátil** (permanente)  
    * **Mayor** capacidad (orden de Terabytes)  
    * Direccionamiento a nivel de **bloque**  
  
* **Problema**: que los/as programadoras/es tengan que ocuparse de tratar con los bloques de disco para buscar en qué bloque están los datos, recuperar o guardar datos de un bloque, etc.  
* **Objetivo**: Ofrecer una abstracción de datos intermedia que se traduzca a bloques de manera que:  
  * Sea independiente del dispositivo físico.  
  * Ofrezca una visión lógica unificada.  
  * Sea lo suficientemente simple pero completa.  
  ```mermaid  
  flowchart LR  
  A(Proceso)---|"(1) Abstracción de datos"|B("(2) Gestor de abstracción")  
  B --- C(Disco)  
  C -.- D("b1, b2, ...")  
  ```  
  
* El sistema operativo integra una <u>abstracción básica y genérica</u> (**ficheros y directorios**) y hay un componente en el sistema operativo que es el <u>gestor de dicha abstracción</u> (**sistema de ficheros**).  
  ```mermaid  
  flowchart LR  
  A(Proceso)---|"ficheros y directorios"|B("sistema de ficheros")  
  B --- C(Disco)  
  C -.- D("b1, b2, ...")  
  ```  
* Aunque hay más soluciones alternativas como una base de datos donde <u>la abstracción</u> **se basa en el uso de tablas** y hay un componente que es el <u>gestor de dicha abstracción</u> **que es el gestor de base de datos**.  
  ```mermaid  
  flowchart LR  
  A(Proceso)---|"base de datos"|B("gestor BBDD")  
  B --- C(Disco)  
  C -.- D("b1, b2, ...")  
  ```  
 
 
#### Para más información:
  * Puede repasar de sistemas operativos el tema [sistema de ficheros (1/3)]([https://acaldero.github.io/uc3m_so/transparencias/clase_w12-sf-ficheros.pdf#page9](https://acaldero.github.io/uc3m_so/transparencias/clase_w12-sf-ficheros.pdf#page9))  
 
 
## Arquitectura básica de un sistema de ficheros  

* La arquitectura general de un sistema de ficheros es:          
![Arquitectura básica general de un sistema de ficheros en Unix](./ssdd_sfd/ssdd_sfd_intro_2.svg)<img src="./transparencias/ssdd_sfd/ssdd_sfd_intro_2.svg">
* En dicha arquitectura se tiene los siguientes componentes:
  * **Manejador de dispositivo**:
    * Transforma peticiones de bloques en peticiones de dispositivo.
  * **Servidor de bloques**:
    * Gestiona las peticiones de operaciones de bloques sobre dispositivos.
    * Mantiene una caché de bloques o páginas.
  * **Módulo de organización de archivos**:
    * Transforma peticiones lógicas en físicas.
    * Distinto para cada sistema de ficheros particular.
  * **Servidor de ficheros/archivos virtual**:
    * Proporciona interfaz de llamadas de E/S.
    * Independiente de sistema de ficheros particular.

* La caché de bloques tiene las siguientes operaciones:
  * **getblk**: busca/reserva en caché un bloque (a partir de un v nodo, desplazamiento y tamaño dado).
  * **brelse**: libera un bloque y lo pasa a la lista de libres.
  * **bwrite**: escribe un bloque de la caché a disco.
  * **bread**: lee un bloque de disco a caché.
  * **breada**: lee un bloque (y el siguiente) de disco a caché.

* Los algoritmos de bajo nivel son:
  * **namei**: convierte una ruta al i-nodo asociado.
  * **iget**: devuelve un i-nodo de la tabla de i-nodos y si no está lo lee de memoria secundaria, lo añade a la tabla de i-nodos y lo devuelve.
  * **iput**: libera un i-nodo de la tabla de i-nodos, y si es necesario lo actualiza en
memoria secundaria.
  * **ialloc**: asignar un i-nodo a un fichero.
  * **ifree**: libera un i-nodo previamente asignado a un fichero.
  * **bmap**: calcula el bloque de disco asociado a un desplazamiento del fichero. Traduce direcciones lógicas (*offset* de fichero) a físicas (bloque de disco).
  * **alloc**: asigna un bloque a un fichero.
  * **free**: libera un bloque previamente asignado a un fichero.


#### Para más información:
  * Puede repasar de sistemas operativos el tema [sistema de ficheros (3/3)]([https://acaldero.github.io/uc3m_so/transparencias/clase_w12-sf-ficheros.pdf#page18](https://acaldero.github.io/uc3m_so/transparencias/clase_w14-sf-sistfich#page18))  
  * Dispone de un ejemplo de un mínimo sistema de ficheros de ejemplo en [nanofs]([https://github.com/acaldero/nanofs])
  
## Sistema de ficheros remoto  
  
  
## Sistema de ficheros distribuido  
  
  
## Sistema de ficheros paralelo


