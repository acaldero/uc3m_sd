# Resumen de los principales aspectos del uso de hilos para Sistemas Distribuidos

### Materiales usados en ARCOS.INF.UC3M.ES con Licencia [CC BY-NC 4.0](http://creativecommons.org/licenses/by-nc/4.0/)


## Requisitos

Los principales requisitos son:
* Tener conexión a Internet para consultar documentación.
* Tener acceso a una máquina con Linux con software de desarrollo instalado:
  * Puede usar las Aulas Virtuales del Laboratorio del Departamento de Informática:
    * ["https://www.lab.inf.uc3m.es/servicios/aulas-virtuales-del-laboratorio/](https://www.lab.inf.uc3m.es/servicios/aulas-virtuales-del-laboratorio/)
  * Puede usar su Debian/Ubuntu con: sudo apt-get install build-essential gdb ddd

## Contenidos

  1. [Qué son y cómo se crean los hilos o threads](#1--qué-son-y-cómo-se-crean-los-hilos-o-threads)
  2. [Qué son y como se usan los **mutex**: dos o más hilos comparten una variable y al menos uno la modifica de forma no atómica](#2--qué-son-y-como-se-usan-los-mutex-para-cuando-1-dos-o-más-hilos-2-comparten-una-variable-3-al-menos-uno-modifica-la-variable-4-y-se-hace-de-forma-no-atómica)
  3. [Qué son y cuando usar las **conditions**: la ejecución de un hilo espera a la ejecución de código de otro](#3--qué-son-y-cuando-usar-las-conditions-hacer-que-la-ejecución-de-un-hilo-se-espere-hasta-que-se-ejecute-un-código-de-otro-hilo)
  4. [Servidor de peticiones basado en hilos bajo demanda](#4--servidor-de-peticiones-basado-en-hilos-bajo-demanda)
  5. [Información adicional](#5--información-adicional)
    


## 1.- <ins>Qué son y cómo se crean los hilos o threads</ins>

Como ejemplo, este programa tiene:
* Una función main que crea 5 hilos y espera a que todos los hilos terminen.
* Cada hilo imprime "Hello world from thread &lt;id. del hilo&gt;!\n"
  
### ths_creatjoin.c
  ```c
  #include <stdlib.h>
  #include <stdio.h>
  #include <pthread.h>

  #define NUM_THREADS     5

  pthread_t threads[NUM_THREADS];

  // La función th_function tiene el código que ejecutarán los hilos
  void *th_function ( void *arg )
  {
      printf("Hello world from thread #%ld!\n", (long)arg) ;
      pthread_exit(NULL) ;
  }

  int main ( int argc, char *argv[] )
  {
    // Crear NUM_THREADS hilos con función th_function y argumento el valor de t
    for (int t=0; t<NUM_THREADS; t++)
    {
           int rc = pthread_create(&(threads[t]), NULL, th_function, (void *)(long)t) ;
           if (rc) {
              printf("ERROR from pthread_create(): %d\n", rc) ;
              exit(-1) ;
           }
    }

    // Esperar a que terminen los NUM_THREADS hilos
    for (int t=0; t<NUM_THREADS; t++)
    {
           int rc = pthread_join(threads[t], NULL) ;
           if (rc) {
              printf("ERROR from pthread_join(): %d\n", rc) ;
              exit(-1) ;
           }
    }

    // pthread_exit(NULL) ; // main es el hilo principal
    return 0 ;
  }
  ```
  
Para compilar y ejecutar hay que usar:
```bash
gcc -Wall -g -o ths_creatjoin ths_creatjoin.c -lpthread
./ths_creatjoin
```

Recordatorios
* <details>
  <summary>No hacer asunciones en el orden de ejecución de código... (hacer click)</summary>

  * No depender una ejecución correcta de un orden particular sino de cualquier orden posible.
  </details>

**Videos suplementarios**:
  * <a href="https://www.youtube.com/watch?v=n5qrEotEWfI">Repaso a los conceptos en hilos</a>
  * <a href="https://www.youtube.com/watch?v=akf9UG7Z5Go">Principales llamadas POSIX de hilos con ejemplos</a>



## 2.- <ins>Qué son y como se usan los **mutex**: para cuando (1) dos o más hilos (2) comparten una variable (3) al menos uno modifica la variable (4) y se hace de forma no atómica</ins>

Como ejemplo, este programa soluciona una condición de carrera entre dos hilos.

### race_sol.c
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
  gcc -Wall -g -o race_sol race_sol.c -lpthread
  ./race_sol
```

Recordatorios
* <details>
  <summary>Cuidado con los interbloqueos con dos o más mutex... (hacer click)</summary>

  * Si se solapa el uso de dos o más mutex, hay que seguir el mismo orden de petición de bloqueo de los mutex usados para evitar interbloqueos (un hilo espere por un mutex que tiene otro y viceversa).
  ```c
  #include <stdlib.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <pthread.h>

  pthread_mutex_t mutex_1;
  pthread_mutex_t mutex_2;

  void *th_main_1 ( void *arg )
  {
    pthread_mutex_lock(&mutex_1) ;
    sleep(1) ;
    pthread_mutex_lock(&mutex_2) ;

    printf("Hello from main_1...\n") ;

    pthread_mutex_unlock(&mutex_2) ;
    pthread_mutex_unlock(&mutex_1) ;

    pthread_exit(NULL) ;
  }

  void *th_main_2 ( void *arg )
  {
    pthread_mutex_lock(&mutex_1) ; // OK
    sleep(1) ;
    pthread_mutex_lock(&mutex_2) ; // OK

    printf("Hello from main_2...\n") ;
    sleep(1) ;

    pthread_mutex_unlock(&mutex_2) ;
    pthread_mutex_unlock(&mutex_1) ;

    pthread_exit(NULL) ;
  }

  int main ( int argc, char *argv[] )
  {
    int rc ;
    pthread_t threads[2];

    // Initialize mutexes...
    pthread_mutex_init(&mutex_1, NULL) ;
    pthread_mutex_init(&mutex_2, NULL) ;

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
    for (int t=0; t<2; t++)
    {
         rc = pthread_join(threads[t], NULL) ;
         if (rc) {
	     printf("ERROR from pthread_join(): %d\n", rc) ;
	     exit(-1) ;
	 }
    }

    // Destroy mutexes...
    pthread_mutex_destroy(&mutex_1) ;
    pthread_mutex_destroy(&mutex_2) ;

    pthread_exit(NULL) ;
  }
  ```
  
  Para compilar y ejecutar hay que usar:
  ```bash
  gcc -Wall -g -o interlock_sol interlock_sol.c -lpthread
  ./interlock_sol
  ```
  </details>

**Videos suplementarios**:
  * <a href="https://www.youtube.com/watch?v=PxjgVYgpGkk&t=471s">Condiciones de carrera</a>
  * <a href="https://www.youtube.com/watch?v=PxjgVYgpGkk&t=924s">Condiciones de interbloqueo</a>   



## 3.- <ins>Qué son y cuando usar las **conditions**: hacer que la ejecución de un hilo se espere hasta que se ejecute un código de otro hilo</ins>

Como ejemplo, este programa sincroniza el hilo main y los hilos creados con pthread_create.

### sync_child_mnc_sol.c
  ```c
  #include <stdlib.h>
  #include <stdio.h>
  #include <pthread.h>

  #define NUM_THREADS  5

  int             is_copied; // boolean to say "is copied"
  pthread_mutex_t mutex_1;   // protect the is_copied global variable:
                             // it is shared by thread, modified, but might be not atomically modified
  pthread_cond_t  cond_cp;   // condition to wait if boolean said we need to wait

  void *th_function ( void *arg )
  {
    int *p_thid ;

    p_thid = (int *)arg ;

    /// Avisa que se ha copiado ///
    pthread_mutex_lock(&mutex_1) ;
    is_copied = 1 ;
    pthread_cond_signal(&cond_cp) ;
    pthread_mutex_unlock(&mutex_1) ;
    ///////////////////////////////

    printf("Hello world from thread #%d!\n", *p_thid) ;
    pthread_exit(NULL) ;
  }

  int main ( int argc, char *argv[] )
  {
    int t, rc ;
    pthread_t threads[NUM_THREADS];

    // Initialize
    pthread_mutex_init(&mutex_1, NULL) ;
    pthread_cond_init(&cond_cp, NULL) ;

    // Crear hilos...
    is_copied = 0;
    for (t=0; t<NUM_THREADS; t++)
    {
           rc = pthread_create(&(threads[t]), NULL, th_function, (void *)&t) ;
           if (rc) {
               printf("ERROR from pthread_create(): %d\n", rc) ;
               exit(-1) ;
           }

           /// Espera al aviso de que se ha copiado ///
           pthread_mutex_lock(&mutex_1) ;
           while (0 == is_copied) {
                  pthread_cond_wait(&cond_cp, &mutex_1) ;
           }
           is_copied = 0;
           pthread_mutex_unlock(&mutex_1) ;
           ////////////////////////////////////////////
    }

    // Esperar a los hilos...
    for (t=0; t<NUM_THREADS; t++)
    {
           rc = pthread_join(threads[t], NULL) ;
           if (rc) {
               printf("ERROR from pthread_join(): %d\n", rc) ;
               exit(-1) ;
           }
    }

    // Destroy...
    pthread_mutex_destroy(&mutex_1) ;
    pthread_cond_destroy(&cond_cp) ;

    pthread_exit(NULL) ;
  }
  ```

Para compilar y ejecutar hay que usar:
```bash
  gcc -Wall -g -o sync_child_mnc_sol sync_child_mnc_sol.c -lpthread
  ./sync_child_mnc_sol
```

**Video suplementario**:
  * <a href="https://www.youtube.com/watch?v=EupaagvNpR0&t=807s">Funcionamiento de los mutex y conditions</a>



## 4.- <ins>Servidor de peticiones basado en hilos bajo demanda</ins>

Como ejemplo, este programa simula un servidor de peticiones basado en hilos bajo demanda.
De cara a que el hilo en el servidor que atiende la petición del cliente se crea lo antes posible, la función de servicio espera hasta que se haya creado el hilo hijo y dicho hilo haya copiado los parámetros.

### threads_ondemand.c
  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <sys/time.h>
  #include <pthread.h>
  #include <unistd.h>

  // Peticiones //////////////////////////////

   struct peticion {
      long id;
      int tipo;
      /* ... */
   };
   typedef struct peticion peticion_t;

  static long petid = 0;

  void recibir_peticion (peticion_t * p)
  {
     fprintf(stderr, "Recibiendo petición\n");

     /* Simulación de tiempo de E/S */
     int delay = rand() % 10;
     sleep(delay);

     p->id = petid++;

     fprintf(stderr,"Petición %ld recibida después de %d segundos\n", p->id, delay);
  }

  void responder_peticion (peticion_t * p)
  {
    fprintf(stderr, "Enviando petición %ld\n", p->id);

    /* Simulación de tiempo de procesamiento */
    int delay1 = rand() % 5;
    sleep(delay1);

    /* Simulación de tiempo de E/S */
    int delay2 = rand() % 10;
    sleep(delay2);

    fprintf(stderr, "Petición %ld enviada después de %d segundos\n",  p->id, delay);
  }


  // Hilos bajo demanda //////////////////////

  pthread_mutex_t mutex;
  pthread_cond_t  copied;
  int             is_copied;

  const int MAX_PETICIONES = 5;

  void * servicio ( void * p )
  {
        peticion_t  pet;

        // copy parameters...
        memmove(&pet,(peticion_t*)p, sizeof(peticion_t));

        // signal data is copied
        pthread_mutex_lock(&mutex) ;
        is_copied = 1 ;
        pthread_cond_signal(&copied) ;
        pthread_mutex_unlock(&mutex) ;

        // process and response
        fprintf(stderr, "Iniciando servicio\n");
        responder_peticion(&pet);
        fprintf(stderr, "Terminando servicio\n");

        pthread_exit(0);
        return NULL;
  }

  void receptor ( void )
  {
       int i;
       peticion_t  p;
       pthread_t   th_hijo[MAX_PETICIONES];

       // for each request, a new thread...
       for (i=0; i<MAX_PETICIONES; i++)
       {
            // receive request and new thread treat it
            recibir_peticion(&p);
            pthread_create(&(th_hijo[i]), NULL, servicio, &p);

            // wait data is copied
            pthread_mutex_lock(&mutex) ;
            while (!is_copied) {
                   pthread_cond_wait(&copied, &mutex) ;
            }
            is_copied = 0 ;
            pthread_mutex_unlock(&mutex) ;
       }

       // wait for each thread ends
       for (i=0; i<MAX_PETICIONES; i++) {
            pthread_join(th_hijo[i], NULL) ;
       }
  }

  int main ( int argc, char *argv[] )
  {
      struct timeval timenow;

      // t1
      gettimeofday(&timenow, NULL) ;
      long t1 = (long)timenow.tv_sec * 1000 + (long)timenow.tv_usec / 1000 ;

      // Dispacher de peticiones...
      receptor() ;

      // t2
      gettimeofday(&timenow, NULL) ;
      long t2 = (long)timenow.tv_sec * 1000 + (long)timenow.tv_usec / 1000 ;

      // imprimir t2-t1...
      printf("Tiempo total: %lf\n", (t2-t1)/1000.0);
      return 0;
  }
  ```

Para compilar y ejecutar hay que usar:
```bash
gcc -Wall -g -o threads_ondemand  threads_ondemand.c -lpthread
./threads_ondemand
```

**Video suplementario**:
  * <a href="https://www.youtube.com/watch?v=nDyYrpFYG-4&t=551s">Ejemplo de servidor de peticiones basado en hilos</a>



## 5.- Información adicional
  * [Ejemplos para Sistemas Operativos (github)](https://github.com/acaldero/uc3m_so/blob/main/ejemplos/README.md)

