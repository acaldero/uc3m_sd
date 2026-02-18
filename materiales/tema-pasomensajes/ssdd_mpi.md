
# Comunicación con MPI
+ **Felix García Carballeira y Alejandro Calderón Mateos** @ arcos.inf.uc3m.es
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

 * Introducción a MPI:
     * [Definir MPI](#introducción-a-mpi)
     * [Características principales](#características-principales)
     * [Ejemplo en C: Hola mundo](#ejemplo-en-c-hola-mundo)
 * Comunicación punto a punto y comunicación colectiva:
    * [API de MPI](#comunicación-punto-a-punto)
    * [Ejemplo en C: send y receive](#ejemplo-en-c-send-y-receive)
    * [Comunicación colectiva](#comunicación-colectiva)
    * [Ejemplo en C: broadcast y barrier](#ejemplo-en-c-broadcast-y-barrier)
  * Escalabilidad:
    * [Ejemplo en C: cálculo de π con MPI](#ejemplo-en-c-cálculo-de-π-con-mpi)
    * [Ejemplo en C: cálculo de π con OpenMP](#ejemplo-en-c-c%C3%A1lculo-de-%CF%80-con-openmp)
 

### Introducción a MPI

- "MPI es una **interfaz**  de paso de mensaje que representa un esfuerzo prometedor de mejorar la disponibilidad de un software **altamente  eficiente** y **portable** para satisfacer las necesidades actuales en la **computación de alto rendimiento** a través de la definición de un estándar de paso de mensajes universal."
   * William D. Gropp et al.

- MPI son las iniciales de *Message Passing Interface*:
  - Es una interfaz estándar de paso de mensajes para el desarrollo de aplicaciones paralelas <br> que ejecutan en computadores que no comparten memoria (memoria distribuida).

- No es una implementación sino la especificación que tiene que cumplir las implementaciones de MPI. <br>
  Las más conocidas son:
  - OpenMPI 4.1.6 (30/9/2023) –[http://www.open-mpi.org/](http://www.open-mpi.org/)
  - MPICH 4.1.2 (8/6/2023)       –[http://www.mpich.org/](http://www.mpich.org/)

 
 
### Características principales

  - **Portabilidad**: 
     - Definido independiente de plataforma paralela
     - Útil en arquitecturas paralelas heterogéneas
  - **Eficiencia**: 
    - Definido para aplicaciones multihilo
    - Sobre una comunicación fiable y eficiente
    - Busca el máximo de cada plataforma
  - **Funcionalidad**:
    - Fácil de usar por cualquier programador que ya haya usado cualquier biblioteca de paso de mensajes


### Modelo de MPI

-   Los procesos ejecutan el mismo programa
-   Todas las estructuras de datos y variables son locales a cada proceso
    -   Los procesos ejecutan en espacios de direcciones distintos (máquinas distintas)
    -   Los procesos no comparten memoria
    -   Los procesos intercambian datos mediante paso de mensajes


### Ejemplo en C: Hola mundo

* **mpi_hola.c**
   ```c
    #include <stdio.h>
    #include "mpi.h"

    int main ( int argc, char **argv )
    {
       int comm_size, my_rank;
       int  tam = 255;
       char name[255];
       
       /* Inicializar MPI, lo primero en el programa (puede modificar argc y argv) */
       MPI_Init(&argc, &argv);
       
       MPI_Comm_size(MPI_COMM_WORLD, &comm_size); /* size <- cuántos procesos somos */
       MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);   /* node <- mi identificador, de 0 a (size-1) */
       
       MPI_Get_processor_name(name, &tam);
       printf("El proceso %d de %d procesos (%s)\n", my_rank, comm_size, name);
       
       /* Finalizar MPI, no se puede inicializar de nuevo luego */
       MPI_Finalize();
       return 0;
    }
   ```

* Se puede compilar usando `mpicc` de la siguiente forma:
  ``` bash
  mpicc -g -Wall -c mpi_hola.c -o mpi_hola.o
  mpicc -g -Wall -o mpi_hola mpi_hola.o
  ```

* Se puede ejecutar en la máquina local usando `mpirun`:
  1. Primero hay que crear un archivo `machines` con la lista de máquinas (una por línea) que van a ser usadas para ejecutar:
    ``` bash
    cat <<EOF > machines
    localhost
    localhost
    EOF
    ```
  2. Luego se ha de usar `mpirun`:
    ``` bash
    mpirun -np 2 -machinefile machines ./mpi_hola
    ```

* La salida sería similar a:
  ``` bash
  El proceso 0 de 2 procesos (kiwi)
  El proceso 1 de 2 procesos (kiwi)
  ```


### Comunicación punto a punto

El API de MPI incluye:
 - Estructuras de datos:
    * Tipos de datos (básicos, vectores, compuestos, …)
    * Grupo de procesos (grupos, comunicadores, …)
 - Paso de mensajes:
    * Llamadas punto a punto (bloqueantes, asíncronas)
    * Llamadas colectivas (bcast, scatter, gather, …)
 - Entrada y salida:
    * Gestión de ficheros (apertura, cierre, …)
    * Gestión de contenidos (vistas, punteros, …)
 - Procesos:
    * Gestión de procesos (creación, …)
    * *Profiling*


### Ejemplo en C: send y receive

**mpi_p2p.c**
```c
#include <stdio.h>
#include "mpi.h"

int main ( int argc, char **argv )
{
    int comm_size, my_rank;
    int num = 0;
    
    /* Inicializar MPI, lo primero en el programa (puede modificar argc y argv) */
    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size); /* size <- cuántos procesos somos */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);   /* node <- mi identificador, de 0 a (size-1) */

    if (my_rank == 0) {
        /* Envía (MPI_Send) desde una dirección de memoria (&num)
           un (1) entero (MPI_INT) al proceso con rank 1 (1)
           en mensaje con etiqueta 0 por el comunicador MPI_COMM_WORD */
        num = 10 ;
        MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else {
        /* Recibe (MPI_Recv) en una dirección de memoria (&num)
           un (1) entero (MPI_INT) desde el proceso con rank 0 (0)
           en mensaje con etiqueta 0 por el comunicador MPI_COMM_WORD */
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("[0 -> %d] num: %d\n", my_rank, num) ;
    }
    
    /* Finalizar MPI, no se puede inicializar de nuevo luego */
    MPI_Finalize();
    return 0;
}
```

* Se puede compilar usando `mpicc`:
   ``` bash
  mpicc -Wall -g mpi_p2p.c -o mpi_p2p
   ```

* Se puede ejecutar en la máquina local usando `mpirun`:
  1. Primero hay que crear un archivo `machines` con la lista de máquinas (una por línea) que van a ser usadas para ejecutar:
    ``` bash
    cat <<EOF > machines
    localhost
    localhost
    EOF
    ```
  2. Luego se ha de usar `mpirun`:
    ``` bash
    mpirun -np 2 ./mpi_p2p
    ```

* La salida sería similar a:
  ``` bash
  [0 -> 1] num: 10
  ```


### Comunicación colectiva

Principales primitivas de comunicación colectiva:
* MPI_Barrier y MPI_Bcast:
  <html>
    <table border="0">
        <tr>
            <td><img alt="MPI_Barrier"   src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/tema-pasomensajes/ssdd_mpi/mpi_barrier.svg" height="125"></td>
            <td><img width="25" height="1"></td>
            <td><img alt="MPI_Bcast"     src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/tema-pasomensajes/ssdd_mpi/mpi_bcast.svg" height="150"></td>
        </tr>
    </table>
  </html>
* MPI_Scatter vs MPI_Gather:
  <html>
    <table border="0">
        <tr>
            <td><img alt="MPI_Scatter"   src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/tema-pasomensajes/ssdd_mpi/mpi_scatter.svg" height="150"></td>
            <td><img width="25" height="1"></td>
            <td><img alt="MPI_Gather"    src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/tema-pasomensajes/ssdd_mpi/mpi_gather.svg" height="150"></td>
        </tr>
    </table>
  </html>
* MPI_Gather vs MPI_Allgather:
  <html>
    <table border="0">
        <tr>
            <td><img alt="MPI_Gather"    src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/tema-pasomensajes/ssdd_mpi/mpi_gather.svg" height="175"></td>
            <td><img width="25" height="1"></td>
            <td><img alt="MPI_Allgather" src="https://raw.githubusercontent.com/acaldero/uc3m_sd/main/materiales/tema-pasomensajes/ssdd_mpi/mpi_allgather.svg" height="175"></td>
        <tr>
    </table>
  </html>
* MPI_Reduce vs MPI_Allreduce:
  <html>
    <table border="0">
        </tr>
            <td><img alt="MPI_Reduce"    src="http://hustcat.github.io/assets/mpi/mpi_reduce_00.png" height="150"></td>
            <td><img width="25" height="1"></td>
            <td><img alt="MPI_Allreduce" src="http://hustcat.github.io/assets/mpi/mpi_allreduce_00.png" height="150"></td>
        </tr>
    </table>
  </html>


### Ejemplo en C: broadcast y barrier

**mpi_coll.c**
```c
#include <stdio.h>
#include "mpi.h"

int main ( int argc, char **argv )
{
    int comm_size, my_rank;
    int num = 0;
    
    /* Inicializar MPI, lo primero en el programa (puede modificar argc y argv) */
    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size); /* size <- cuántos procesos somos */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);   /* node <- mi identificador, de 0 a (size-1) */
    
    if (0 == my_rank)
         num = 5;  /* solo el proceso 0 tiene num el valor 5 */
    else num = 0 ; /* el resto de procesos tiene num el valor 0 */
    
    MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    printf("El proceso %d tiene num: %d\n", my_rank, num);
    
    /* Finalizar MPI, no se puede inicializar de nuevo luego */
    MPI_Finalize();
    return 0;
}
```

* Se puede compilar usando `mpicc`:
   ``` bash
  mpicc -Wall -g mpi_coll.c -o mpi_coll
   ```

* Se puede ejecutar en la máquina local usando `mpirun`:
  1. Primero hay que crear un archivo `machines` con la lista de máquinas (una por línea) que van a ser usadas para ejecutar:
    ``` bash
    cat <<EOF > machines
    localhost
    localhost
    EOF
    ```
  2. Luego se ha de usar `mpirun`:
    ``` bash
    mpirun -np 2 ./mpi_coll
    ```

* La salida sería similar a:
  ``` bash
  El proceso 0 tiene num: 5
  El proceso 1 tiene num: 5
  ```


### Ejemplo en C: cálculo de π con MPI

**pi_mpi.c**
```c
#include <math.h>
#include <stdio.h>
#include <mpi.h>

#define N 1E9
#define d 1E-9

int main(int argc, char* argv[])
{
    int rank, size;
    double pi = 0.0, result = 0.0, sum = 0.0, s = 0, x = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = rank; i < N; i += size) {
        x = d * i;
        s = sqrt(4 * (1 - x * x)) * d;
        result = result + s;
    }

    MPI_Reduce(&result, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi = 2 * sum;
        printf("np = %2d; PI = %lf\n", size, pi);
    }

    MPI_Finalize();
    return 0;
}
```

* Se puede compilar usando `mpicc`:
  ``` bash
  mpicc -Wall -g pi_mpi.c -lm -o pi_mpi
  ```

* Se puede ejecutar en la máquina local usando `mpirun`:
  * Primero hay que crear un archivo `machines` con la lista de máquinas (una por línea) que van a ser usadas para ejecutar:
    ``` bash
    cat <<EOF > machines
    localhost
    localhost
    EOF
    ```
  * Luego se ha de usar `mpirun`:
    ``` bash
    mpirun -np 2 -machinefile machines ./pi_mpi
    ```

* La salida sería similar a:
  ``` bash
  np =  2; PI = 3.141593
  ```


### Ejemplo en C: cálculo de π con OpenMP

**pi_omp.c**
```c
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define N 1000000000
#define d 1E-9

int main ( int argc, char* argv[] )
{
    long long i;
    double PI = 0.0, result = 0.0;

    #pragma omp parallel for reduction(+:result)
    for (i = 0; i < N; i++) {
        double x = d * i;
        result += sqrt(4 * (1 - x * x)) * d;
    }

    PI = 2 * result;
    printf("PI = %f\n", PI);

    return 0;
}
```

* Se puede compilar usando:
  ``` bash
  gcc -o pi_omp -fopenmp pi_omp.c -lm
  ```
  * Se precisa la librería de OpenMP `libopenmp.a` y la librería matemática `libm.a`

* Se puede ejecutar mediante:
   ``` bash
  user$ ./pi_omp
   ```

* La salida sería similar a:
  ``` bash
  PI = 3.141593
  ```


### Lecturas adicionales

* https://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/
* http://hustcat.github.io/collective-communication-in-mpi/
* https://nyu-cds.github.io/python-mpi/05-collectives/

