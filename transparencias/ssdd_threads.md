# Resumen de los principales aspectos del uso de hilos para Sistemas Distribuidos

### Materiales usados en ARCOS.INF.UC3M.ES con Licencia [CC BY-NC 4.0](http://creativecommons.org/licenses/by-nc/4.0/)


## Requisitos

Los principales requisitos son:
* Tener conexión a Internet para consultar documentación.
* Tener acceso a una máquina con Linux. 
  * -> se recuerda que el Laboratorio del Departamento de Informática ofrece unas Aulas Virtuales en: ["https://www.lab.inf.uc3m.es/servicios/aulas-virtuales-del-laboratorio/](https://www.lab.inf.uc3m.es/servicios/aulas-virtuales-del-laboratorio/)
* Tener instalado el software para desarrollo que sea preciso en la máquina con Linux:
  * sudo apt-get install build-essential gdb ddd


## 1.- <ins>Qué son y cómo se crean los hilos o threads</ins>

Como ejemplo, este programa tiene una función main que crea 5 hilos y espera a que todos los hilos terminen.

Cada hilo imprime "Hello world from thread &lt;id. del hilo&gt;!\n":
* ths_creatjoin.c
  ```c
  #include <stdlib.h>
  #include <stdio.h>
  #include <pthread.h>

  #define NUM_THREADS     5

  pthread_t threads[NUM_THREADS];

  void *th_function ( void *arg )
  {
      printf("Hello world from thread #%ld!\n", (long)arg) ;
      pthread_exit(NULL) ;
  }

  int main ( int argc, char *argv[] )
  {
    for (int t=0; t<NUM_THREADS; t++)
    {
           int rc = pthread_create(&(threads[t]), NULL, th_function, (void *)(long)t) ;
           if (rc)
           {
	       printf("ERROR from pthread_create(): %d\n", rc) ;
	       exit(-1) ;
	   }
    }

    for (int t=0; t<NUM_THREADS; t++)
    {
           int rc = pthread_join(threads[t], NULL) ;
           if (rc)
           {
	       printf("ERROR from pthread_join(): %d\n", rc) ;
	       exit(-1) ;
	   }
    }

    pthread_exit(NULL) ;
  }
  ```
  
Para compilar y ejecutar hay que usar:
```bash
gcc -Wall -g -o ths_creatjoin ths_creatjoin.c -lpthread
./ths_creatjoin
```

**Información recomendada**:
  * <a href="https://www.youtube.com/watch?v=n5qrEotEWfI">Repaso a los conceptos en hilos</a>
  * <a href="https://www.youtube.com/watch?v=akf9UG7Z5Go">Principales llamadas POSIX de hilos con ejemplos</a>



## 2.- <ins>Qué son y como se usan los **mutex**: para cuando (1) dos o más hilos (2) comparten una variable (3) al menos uno modifica la variable (4) y se hace de forma no atómica</ins>

Como ejemplo, este programa soluciona una condición de carrera entre dos hilos:
* race_sol.c
  ```c
  #include <stdlib.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <pthread.h>

  long acc ;
  pthread_mutex_t mutex_1; // MUTEX

  void *th_main_1 ( void *arg )
  {
    register int a1 ;

    pthread_mutex_lock(&mutex_1) ; // LOCK
    for (int j=0; j<2; j++)
    {
         a1  = acc ;
             printf("main_1 sees acc=%d...\n", a1) ;
         a1  = a1 + 1 ;
         acc = a1 ;
             printf("main_1 updates acc=%d...\n", a1) ;
	 sleep(1) ;
    }
    pthread_mutex_unlock(&mutex_1) ; // UNLOCK

    pthread_exit(NULL) ;
  }

  void *th_main_2 ( void *arg )
  {
    register int a2 ;

    pthread_mutex_lock(&mutex_1) ; // LOCK
    for (int j=0; j<2; j++)
    {
         a2  = acc ;
             printf("main_2 sees acc=%d...\n", a2) ;
         a2  = a2 - 1 ;
         acc = a2 ;
             printf("main_2 updates acc=%d...\n", a2) ;
	 sleep(1) ;
    }
    pthread_mutex_unlock(&mutex_1) ; // UNLOCK

    pthread_exit(NULL) ;
  }

  int main ( int argc, char *argv[] )
  {
    int rc ;
    pthread_t threads[2];

    // Initialize...
    acc = 0 ;
    pthread_mutex_init(&mutex_1, NULL) ; // INIT-MUTEX

    // Create threads...
    rc = pthread_create(&(threads[0]), NULL, th_main_1, NULL) ;
    if (rc) {
        printf("ERROR from pthread_create(): %d\n", rc) ;
        exit(-1) ;
    }
    rc = pthread_create(&(threads[1]), NULL, th_main_2, NULL) ;
    if (rc) {
        printf("ERROR from pthread_create(): %d\n", rc) ;
        exit(-1) ;
    }

    // Join threads...
    rc = pthread_join(threads[0], NULL) ;
    if (rc) {
        printf("ERROR from pthread_join(): %d\n", rc) ;
        exit(-1) ;
    }
    rc = pthread_join(threads[1], NULL) ;
    if (rc) {
        printf("ERROR from pthread_join(): %d\n", rc) ;
        exit(-1) ;
    }

    printf(" >>>>> acc = %ld\n", acc) ;

    // Destroy...
    pthread_mutex_destroy(&mutex_1) ; // DESTROY-MUTEX

    pthread_exit(NULL) ;
  }
  ```

Para compilar y ejecutar hay que usar:
```bash
: código con solución:
  gcc -Wall -g -o race_sol race_sol.c -lpthread
  ./race_sol
```

**Información recomendada**:
  * <a href="https://www.youtube.com/watch?v=PxjgVYgpGkk&t=471s">Condiciones de carrera</a>



## 3.- <ins>Qué son y cuando usar las **conditions**: hacer que la ejecución de un hilo se espere hasta que se ejecute un código de otro hilo</ins>

Como ejemplo, este programa sincroniza el hilo main y los hilos creados con pthread_create:
* sync_child_mnc_sol.c
  ```c
  #include <stdlib.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <pthread.h>

  long acc ;
  pthread_mutex_t mutex_1; // MUTEX

  void *th_main_1 ( void *arg )
  {
    register int a1 ;

    pthread_mutex_lock(&mutex_1) ; // LOCK
    for (int j=0; j<2; j++)
    {
         a1  = acc ;
             printf("main_1 sees acc=%d...\n", a1) ;
         a1  = a1 + 1 ;
         acc = a1 ;
             printf("main_1 updates acc=%d...\n", a1) ;
	 sleep(1) ;
    }
    pthread_mutex_unlock(&mutex_1) ; // UNLOCK

    pthread_exit(NULL) ;
  }

  void *th_main_2 ( void *arg )
  {
    register int a2 ;

    pthread_mutex_lock(&mutex_1) ; // LOCK
    for (int j=0; j<2; j++)
    {
         a2  = acc ;
             printf("main_2 sees acc=%d...\n", a2) ;
         a2  = a2 - 1 ;
         acc = a2 ;
             printf("main_2 updates acc=%d...\n", a2) ;
	 sleep(1) ;
    }
    pthread_mutex_unlock(&mutex_1) ; // UNLOCK

    pthread_exit(NULL) ;
  }

  int main ( int argc, char *argv[] )
  {
    int rc ;
    pthread_t threads[2];

    // Initialize...
    acc = 0 ;
    pthread_mutex_init(&mutex_1, NULL) ; // INIT-MUTEX

    // Create threads...
    rc = pthread_create(&(threads[0]), NULL, th_main_1, NULL) ;
    if (rc) {
        printf("ERROR from pthread_create(): %d\n", rc) ;
        exit(-1) ;
    }
    rc = pthread_create(&(threads[1]), NULL, th_main_2, NULL) ;
    if (rc) {
        printf("ERROR from pthread_create(): %d\n", rc) ;
        exit(-1) ;
    }

    // Join threads...
    rc = pthread_join(threads[0], NULL) ;
    if (rc) {
        printf("ERROR from pthread_join(): %d\n", rc) ;
        exit(-1) ;
    }
    rc = pthread_join(threads[1], NULL) ;
    if (rc) {
        printf("ERROR from pthread_join(): %d\n", rc) ;
        exit(-1) ;
    }

    printf(" >>>>> acc = %ld\n", acc) ;

    // Destroy...
    pthread_mutex_destroy(&mutex_1) ; // DESTROY-MUTEX

    pthread_exit(NULL) ;
  }
  ```

Para compilar y ejecutar hay que usar:
```bash
: código con solución:
  gcc -Wall -g -o sync_child_mnc_sol sync_child_mnc_sol.c -lpthread
  ./sync_child_mnc_sol
```

**Información recomendada**:
  * <a href="https://www.youtube.com/watch?v=EupaagvNpR0&t=807s">Funcionamiento de los mutex y conditions</a>

