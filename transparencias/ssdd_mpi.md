
# Comunicación con MPI
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ Licencia [GPLv3.0](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

 * Introducción a MPI
     * [Principales características](#introducción-a-mpi)
     * [Ejemplo en C: Hola mundo](#ejemplo-en-c-hola-mundo)
 * Comunicación punto a punto y comunicación colectiva:
    * [API de MPI](#comunicación-punto-a-punto-y-comunicación-colectiva)
    * [Ejemplo en C: send-receive](#ejemplo-en-c-send-receive)
    * [Ejemplo en C: broadcast y barrier](#ejemplo-en-c-broadcast-y-barrier)
  * Escalabilidad:
    * [Ejemplo en C: cálculo de π con MPI](#ejemplo-en-c-cálculo-de-π-con-mpi)
    * [Ejemplo en C: cálculo de π con OpenMP](#ejemplo-en-c-c%C3%A1lculo-de-%CF%80-con-openmp)
 

### Introducción a MPI

- MPI son las iniciales de *Message Passing Interface*
- Qué es:
  - Interfaz estándar de paso de mensajes para el desarrollo de aplicaciones paralelas que ejecutan en computadores que no comparten memoria
- Características principales:
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

    main(int argc, char **argv)
    {
       int node, size;
       int tam = 255;
       char name[255];
       
       MPI_Init(&argc, &argv);
       MPI_Comm_size(MPI_COMM_WORLD, &size);
       MPI_Comm_rank(MPI_COMM_WORLD, &node);
       MPI_Get_processor_name(name, &tam);
       printf("El proceso %d de %d procesos (%s)\n", node, size, name);
       MPI_Finalize();
    }
   ```

* Se puede compilar usando `mpicc` de la siguiente forma:
  ``` bash
  cd ~/lab_mpi
  mpicc -g -Wall -c hola.c -o hola.o
  mpicc -g -Wall -o hola hola.o
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
    mpirun -np 2 -machinefile machines ./hola
    ```


### Comunicación punto a punto y comunicación colectiva

El API de MPI incluye:
 - Estructuras de datos
    * Tipos de datos (básicos, vectores, compuestos, …)
    * Grupo de procesos (grupos, comunicadores, …)
 - Paso de mensajes
    * Llamadas punto a punto (bloqueantes, asíncronas)
    * Llamadas colectivas (bcast, scatter, gather, …)
 - Entrada y salida
    * Gestión de ficheros (apertura, cierre, …)
    * Gestión de contenidos (vistas, punteros, …)
 - Procesos
    * Gestión de procesos (creación, …)
    * *Profiling*


### Ejemplo en C: send-receive

**mpi_p2p.c**
```c
#include <stdio.h>
#include "mpi.h"

main(int argc, char **argv)
{
    int node, size;
    int tam = 255;
    char name[255];
    int num = 10;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);
    if (node == 0)
        MPI_Send(&num, 1 MPI_INT, 1, 0, MPI_COMM_WORLD);
    else
        MPI_Recv(&num, 1 MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Finalize();
}
```

* Se puede compilar usando `mpicc`:
   ``` bash
  mpicc -Wall -g mpi_p2p.c -o mpi_p2p
   ```


### Ejemplo en C: broadcast y barrier

**mpi_coll.c**
```c
#include <stdio.h>
#include "mpi.h"

main(int argc, char **argv)
{
    int node, size;
    int tam = 255;
    char name[255];
    int num;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &node);
    if (node == 0)
        num = 5;
    MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    printf("El proceso %d recibe %d\n", node, num);
    MPI_Finalize();
}
```

* Se puede compilar usando `mpicc`:
   ``` bash
  mpicc -Wall -g mpi_coll.c -o mpi_coll
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
    user$ mpirun -np 2 -machinefile machines ./pi_mpi
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


