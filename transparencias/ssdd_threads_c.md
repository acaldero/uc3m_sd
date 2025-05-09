
# Resumen de los principales aspectos del uso de hilos para Sistemas Distribuidos
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ Licencia [GPLv3.0](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Contenidos

  * Procesos ligeros (1) independientes, (2) que compiten y (3) que cooperan:
    * [1. Qué son y cómo se crean los hilos o threads](#1--qué-son-y-cómo-se-crean-los-hilos-o-threads)
    * [2. Qué son y cuándo se usan los **mutex**: dos o más hilos comparten una variable y al menos uno la modifica de forma no atómica](#2--qué-son-y-como-se-usan-los-mutex-para-cuando-1-dos-o-más-hilos-2-comparten-una-variable-3-al-menos-uno-modifica-la-variable-4-y-se-hace-de-forma-no-atómica)
    * [3. Qué son y cuándo usar las **conditions**: la ejecución de un hilo espera a la ejecución de código de otro](#3--qué-son-y-cuándo-usar-las-conditions-hacer-que-la-ejecución-de-un-hilo-se-espere-hasta-que-se-ejecute-un-código-de-otro-hilo)
  * Servidor de peticiones:
    * [4. Basado en hilos bajo demanda](#4--servidor-de-peticiones-basado-en-hilos-bajo-demanda)
    * [5. Basado en pool de hilos](#5--servidor-de-peticiones-basado-en-pool-de-hilos)
  * [Información adicional](#6--información-adicional)



## 1.- <ins>Qué son y cómo se crean los hilos o threads</ins>

Como ejemplo, este programa tiene:
* Una función main que crea 5 hilos y espera a que todos los hilos terminen.
* Cada hilo imprime "Hello world from thread &lt;id. del hilo&gt;!\n"

### ths_creatjoin.c
  ```c
  #include <stdlib.h>
  #include <stdio.h>
  #include <threads.h>

  #define NUM_THREADS     5

  thrd_t threads[NUM_THREADS];

  // La función th_function tiene el código que ejecutarán los hilos
  void *th_function ( void *arg )
  {
      printf("Hello world from thread #%ld!\n", (long)arg) ;
      thrd_exit(EXIT_SUCCESS) ;
  }

  int main ( int argc, char *argv[] )
  {
    // Crear NUM_THREADS hilos con función th_function y argumento el valor de t
    for (int t=0; t<NUM_THREADS; t++)
    {
           int rc = thrd_create(&(threads[t]), (thrd_start_t)th_function, (void *)(long)t) ;
           if (rc != thrd_success) {
              printf("ERROR from thrd_create(): %d\n", rc) ;
              exit(-1) ;
           }
    }

    // Esperar a que terminen los NUM_THREADS hilos
    for (int t=0; t<NUM_THREADS; t++)
    {
           int rc = thrd_join(threads[t], NULL) ;
           if (rc) {
              printf("ERROR from thrd_join(): %d\n", rc) ;
              exit(-1) ;
           }
    }

    // thrd_exit(EXIT_SUCCESS) ; // main es el hilo principal
    return 0 ;
  }
  ```

Para compilar y ejecutar hay que usar:
```bash
gcc -Wall -g -o ths_creatjoin ths_creatjoin.c
./ths_creatjoin
```

Recordatorios
* <details>
  <summary>No hacer asunciones en el orden de ejecución de código... (hacer click)</summary>

  * No depender una ejecución correcta de un orden particular sino de cualquier orden posible.
  </details>
* <details>
  <summary>Al hilo se pasa un único parámetro... (hacer click)</summary>

  * En el diseño de la API se pensó en pasar un único parámetro que fuera un puntero a la dirección de memoria de una estructura de C (struct) en la cuál se guarda todos los argumentos de trabajo del hilo.
  * (1/2) Antes de crear el hilo hay que reservar memoria y rellenar los valores de trabajo:
    ```
           th_args = (struct thread_arguments *)malloc(sizeof(struct thread_arguments)) ;
           if (NULL == th_args) {
              printf("ERROR from malloc\n") ;
              exit(-1) ;
           }

           th_args.arg1 = 'a' ;
           th_args.arg2 = 33  ;
           th_args.arg3 = j  ;
           ...

           int rc = thrd_create(&(threads[t]), (thrd_start_t)th_function, (void *)th_args) ;
           if (rc != thrd_success) {
              printf("ERROR from thrd_create(): %d\n", rc) ;
              exit(-1) ;
           }

           ...
  * (2/2) en el hilo se usa esta estructura y antes de terminar se libera la memoria asociada:
    ```
    void *th_function ( void *arg )
    {
        struct thread_arguments *th_args = (struct thread_arguments *) arg ;

        ...
        printf("Hello world from thread #%d!\n", th_args.arg3) ;
        ...

        free(th_args) ;
        th_args = NULL ;
        thrd_exit(EXIT_SUCCESS) ;
    }
    ```
  </details>

**Videos suplementarios**:
  * <a href="https://www.youtube.com/watch?v=n5qrEotEWfI">Repaso a los conceptos en hilos</a>
  * <a href="https://www.youtube.com/watch?v=akf9UG7Z5Go">Principales llamadas POSIX de hilos con ejemplos</a>



## 2.- <ins>Qué son y como se usan los **mutex**: para cuando (1) dos o más hilos (2) comparten una variable (3) al menos uno modifica la variable (4) y se hace de forma no atómica</ins>


Cuando (1) dos o más hilos (2) comparten una variable (3) al menos uno modifica la variable (4) y se hace de forma no atómica se presenta el problema llamado "condición de carrera".
La zona de código en la que cada hilo accede a la variable compartida (ya sea para consultar o para modificar) se llama "sección crítica".

Como ejemplo, este programa soluciona una condición de carrera entre dos hilos mediante el uso de un mutex "mutex_1".

### race_sol.c
  ```c
  #include <stdlib.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <threads.h>

  long acc ;
  mtx_t mutex_1; // MUTEX

  void *th_main_1 ( void *arg )
  {
    register int a1 ;

    mtx_lock(&mutex_1) ; // LOCK
    for (int j=0; j<2; j++)
    {
         a1  = acc ;
             printf("main_1 sees acc=%d...\n", a1) ;
         a1  = a1 + 1 ;
         acc = a1 ;
             printf("main_1 updates acc=%d...\n", a1) ;
	 sleep(1) ;
    }
    mtx_unlock(&mutex_1) ; // UNLOCK

    thrd_exit(EXIT_SUCCESS) ;
  }

  void *th_main_2 ( void *arg )
  {
    register int a2 ;

    mtx_lock(&mutex_1) ; // LOCK
    for (int j=0; j<2; j++)
    {
         a2  = acc ;
             printf("main_2 sees acc=%d...\n", a2) ;
         a2  = a2 - 1 ;
         acc = a2 ;
             printf("main_2 updates acc=%d...\n", a2) ;
	 sleep(1) ;
    }
    mtx_unlock(&mutex_1) ; // UNLOCK

    thrd_exit(EXIT_SUCCESS) ;
  }

  int main ( int argc, char *argv[] )
  {
    int rc ;
    thrd_t threads[2];

    // Initialize...
    acc = 0 ;
    mtx_init(&mutex_1, mtx_plain) ; // INIT-MUTEX

    // Create threads...
    rc = thrd_create(&(threads[0]), (thrd_start_t)th_main_1, NULL) ;
    if (rc != thrd_success) {
        printf("ERROR from thrd_create(): %d\n", rc) ;
        exit(-1) ;
    }
    rc = thrd_create(&(threads[1]), (thrd_start_t)th_main_2, NULL) ;
    if (rc != thrd_success) {
        printf("ERROR from thrd_create(): %d\n", rc) ;
        exit(-1) ;
    }

    // Join threads...
    rc = thrd_join(threads[0], NULL) ;
    if (rc != thrd_success) {
        printf("ERROR from thrd_join(): %d\n", rc) ;
        exit(-1) ;
    }
    rc = thrd_join(threads[1], NULL) ;
    if (rc != thrd_success) {
        printf("ERROR from thrd_join(): %d\n", rc) ;
        exit(-1) ;
    }

    printf(" >>>>> acc = %ld\n", acc) ;

    // Destroy...
    mtx_destroy(&mutex_1) ; // DESTROY-MUTEX

    thrd_exit(EXIT_SUCCESS) ;
  }
  ```

Para compilar y ejecutar hay que usar:
```bash
  gcc -Wall -g -o race_sol race_sol.c
  ./race_sol
```

Recordatorios
* <details>
  <summary>Cuidado con los interbloqueos con dos o más mutex... (hacer click)</summary>

  * Si se solapa el uso de dos o más mutex, hay que seguir el mismo orden de petición de bloqueo de los mutex usados para evitar interbloqueos (un hilo espere por un mutex que tiene otro y viceversa).
  ### interlock_sol.c
  ```c
  #include <stdlib.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <threads.h>

  mtx_t mutex_1;
  mtx_t mutex_2;

  void *th_main_1 ( void *arg )
  {
    mtx_lock(&mutex_1) ;
    sleep(1) ;
    mtx_lock(&mutex_2) ;

    printf("Hello from main_1...\n") ;

    mtx_unlock(&mutex_2) ;
    mtx_unlock(&mutex_1) ;

    thrd_exit(EXIT_SUCCESS) ;
  }

  void *th_main_2 ( void *arg )
  {
    mtx_lock(&mutex_1) ; // OK
    sleep(1) ;
    mtx_lock(&mutex_2) ; // OK

    printf("Hello from main_2...\n") ;
    sleep(1) ;

    mtx_unlock(&mutex_2) ;
    mtx_unlock(&mutex_1) ;

    thrd_exit(EXIT_SUCCESS) ;
  }

  int main ( int argc, char *argv[] )
  {
    int rc ;
    thrd_t threads[2];

    // Initialize mutexes...
    mtx_init(&mutex_1, mtx_plain) ;
    mtx_init(&mutex_2, mtx_plain) ;

    // Create threads...
    rc = thrd_create(&(threads[0]), (thrd_start_t)th_main_1, NULL) ;
    if (rc != thrd_success) {
        printf("ERROR from thrd_create(): %d\n", rc) ;
        exit(-1) ;
    }
    rc = thrd_create(&(threads[1]), (thrd_start_t)th_main_2, NULL) ;
    if (rc != thrd_success) {
        printf("ERROR from thrd_create(): %d\n", rc) ;
        exit(-1) ;
    }

    // Join threads...
    for (int t=0; t<2; t++)
    {
         rc = thrd_join(threads[t], NULL) ;
         if (rc != thrd_success) {
	     printf("ERROR from thrd_join(): %d\n", rc) ;
	     exit(-1) ;
	 }
    }

    // Destroy mutexes...
    mtx_destroy(&mutex_1) ;
    mtx_destroy(&mutex_2) ;

    thrd_exit(EXIT_SUCCESS) ;
  }
  ```

  Para compilar y ejecutar hay que usar:
  ```bash
  gcc -Wall -g -o interlock_sol interlock_sol.c
  ./interlock_sol
  ```
  </details>

**Videos suplementarios**:
  * <a href="https://www.youtube.com/watch?v=PxjgVYgpGkk&t=471s">Condiciones de carrera</a>
  * <a href="https://www.youtube.com/watch?v=PxjgVYgpGkk&t=924s">Condiciones de interbloqueo</a>



## 3.- <ins>Qué son y cuándo usar las **conditions**: hacer que la ejecución de un hilo se espere hasta que se ejecute un código de otro hilo</ins>

Como ejemplo, este programa sincroniza el hilo main y los hilos creados con thrd_create para que "main" espere hasta que se haya creado el hilo y también copiado los argumentos.

### sync_child_mnc_sol.c
  ```c
  #include <stdlib.h>
  #include <stdio.h>
  #include <threads.h>

  #define NUM_THREADS  5

    /// var + mutex + condition /////
    int             is_copied = 0; // boleano que indica "se ha copiado"
    mtx_t mutex_1;       // mutex que protege la variable global "is_copied":
                                   // compartida por 2 o más hilos, modificada por alguno y no de forma atómica.
    cnd_t  cond_cp;       // condition para esperar si el boleano dice que hay que esperar
    /////////////////////////////////

  void *th_function ( void *arg )
  {
    int *p_thid ;

    p_thid = (int *)arg ;

    /// Avisa que se ha copiado ///
    mtx_lock(&mutex_1) ;
    is_copied = 1 ;
    cnd_signal(&cond_cp) ;
    mtx_unlock(&mutex_1) ;
    ///////////////////////////////

    printf("Hello world from thread #%d!\n", *p_thid) ;

    thrd_exit(EXIT_SUCCESS) ;
  }

  int main ( int argc, char *argv[] )
  {
    int t, rc ;
    thrd_t threads[NUM_THREADS];

    // Initialize
    mtx_init(&mutex_1, mtx_plain) ;
    cnd_init(&cond_cp) ;

    // Crear hilos...
    for (t=0; t<NUM_THREADS; t++)
    {
           rc = thrd_create(&(threads[t]), (thrd_start_t)th_function, (void *)&t) ;
           if (rc) {
               printf("ERROR from thrd_create(): %d\n", rc) ;
               exit(-1) ;
           }

           /// Si no se ha copiado, espera al aviso de copiado ///
           mtx_lock(&mutex_1) ;
           while (0 == is_copied) {
                  cnd_wait(&cond_cp, &mutex_1) ;
           }
           is_copied = 0;
           mtx_unlock(&mutex_1) ;
           ////////////////////////////////////////////
    }

    // Esperar a los hilos...
    for (t=0; t<NUM_THREADS; t++)
    {
           rc = thrd_join(threads[t], NULL) ;
           if (rc) {
               printf("ERROR from thrd_join(): %d\n", rc) ;
               exit(-1) ;
           }
    }

    // Destroy...
    mtx_destroy(&mutex_1) ;
    cnd_destroy(&cond_cp) ;

    thrd_exit(EXIT_SUCCESS) ;
  }
  ```

Para compilar y ejecutar hay que usar:
```bash
  gcc -Wall -g -o sync_child_mnc_sol sync_child_mnc_sol.c
  ./sync_child_mnc_sol
```

Recordatorios
* <details>
  <summary>signal vs broadcast... (hacer click)</summary>

  * Para despertar a solo un hilo esperando en la condition usar <a href="https://en.cppreference.com/w/c/thread/cnd_signal">cnd_signal</a>:
    ```
    cnd_signal(&cond_cp) ;
    ```
  * Para despertar a todos los hilos esperando en la condition usar <a href="https://en.cppreference.com/w/c/thread/cnd_broadcast">cnd_broadcast</a>:
    ```
    cnd_broadcast(&cond_cp) ;
    ```
  </details>

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
  #include <threads.h>
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

     fprintf(stderr, "Petición %ld enviada después de %d segundos\n",  p->id, delay1 + delay2);
  }


  // Hilos bajo demanda //////////////////////

  mtx_t mutex;
  cnd_t  copied;
  int             is_copied;

  const int MAX_PETICIONES = 5;

  void * servicio ( void * p )
  {
        peticion_t  pet;

        // copy parameters...
        memmove(&pet,(peticion_t*)p, sizeof(peticion_t));

        // signal data is copied
        mtx_lock(&mutex) ;
        is_copied = 1 ;
        cnd_signal(&copied) ;
        mtx_unlock(&mutex) ;

        // process and response
        fprintf(stderr, "Iniciando servicio\n");
        responder_peticion(&pet);
        fprintf(stderr, "Terminando servicio\n");

        thrd_exit(0);
        return NULL;
  }

  void receptor ( void )
  {
       int i;
       peticion_t  p;
       thrd_t   th_hijo[MAX_PETICIONES];

       // for each request, a new thread...
       for (i=0; i<MAX_PETICIONES; i++)
       {
            // receive request and new thread treat it
            recibir_peticion(&p);
            thrd_create(&(th_hijo[i]), (thrd_start_t)servicio, &p);

            // wait data is copied
            mtx_lock(&mutex) ;
            while (!is_copied) {
                   cnd_wait(&copied, &mutex) ;
            }
            is_copied = 0 ;
            mtx_unlock(&mutex) ;
       }

       // wait for each thread ends
       for (i=0; i<MAX_PETICIONES; i++) {
            thrd_join(th_hijo[i], NULL) ;
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
gcc -Wall -g -o threads_ondemand  threads_ondemand.c
./threads_ondemand
```

**Video suplementario**:
  * <a href="https://www.youtube.com/watch?v=nDyYrpFYG-4&t=551s">Ejemplo de servidor de peticiones basado en hilos</a>



## 5.- <ins>Servidor de peticiones basado en pool de hilos</ins>

Como ejemplo, este programa simula un servidor de peticiones basado en pool de hilos.

### threads_pool.c
  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <sys/time.h>
  #include <time.h>
  #include <threads.h>
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

     fprintf(stderr, "Petición %ld enviada después de %d segundos\n",  p->id, delay1 + delay2);
  }


  // Pool de hilos ///////////////////////////

  #define MAX_BUFFER 128
  peticion_t  buffer[MAX_BUFFER];


  int  n_elementos  = 0;
  int  ha_arrancado = 0;
  int  fin = 0;

  mtx_t  mutex;
  cnd_t   no_lleno;
  cnd_t   no_vacio;
  cnd_t   arrancado;
  cnd_t   parado;

  const int MAX_PETICIONES = 5;
  const int MAX_SERVICIO   = 5;

  void * receptor ( void * param )
  {
         peticion_t p;
         int i, pos_receptor = 0;

         for (i=0; i<MAX_PETICIONES; i++)
         {
              recibir_peticion(&p);
              fprintf(stderr,"receptor: recepción de petición\n");

           // lock when not full...
              mtx_lock(&mutex);
              while (n_elementos == MAX_BUFFER) {
                     cnd_wait(&no_lleno, &mutex);
              }

           // inserting element into the buffer
              buffer[pos_receptor ] = p;
              pos_receptor = (pos_receptor +1) % MAX_BUFFER;
              n_elementos++;

           // signal not empty...
              cnd_signal(&no_vacio);
              mtx_unlock(&mutex);
         }

         fprintf(stderr,"receptor: finalizando\n");

         // signal end
         mtx_lock(&mutex);
         fin=1;
         cnd_broadcast(&no_vacio);
         mtx_unlock(&mutex);

         fprintf(stderr, "receptor: Finalizado\n");
         thrd_exit(0);
         return NULL;

  }

  void * servicio ( void * param )
  {
        peticion_t p;
        int pos_servicio = 0;

        // signal initializate...
        mtx_lock(&mutex);
        ha_arrancado = 1;
        cnd_signal(&arrancado);
        mtx_unlock(&mutex);

        for (;;)
        {
          // lock when not empty and not ended...
             mtx_lock(&mutex);
             while (n_elementos == 0)
             {
                  if (fin==1) {
                       fprintf(stderr,"servicio: finalizando\n");
                       cnd_signal(&parado);
                       mtx_unlock(&mutex);
                       thrd_exit(0);
                  }

                  cnd_wait(&no_vacio, &mutex);
             } // while

          // removing element from buffer...
             p = buffer[pos_servicio];
             pos_servicio = (pos_servicio + 1) % MAX_BUFFER;
             n_elementos--;

          // signal not full...
             cnd_signal(&no_lleno);
             mtx_unlock(&mutex);

          // process and response...
             fprintf(stderr, "servicio: sirviendo posicion %d\n", pos_servicio);
             responder_peticion(&p);
      }

      thrd_exit(0);
      return NULL;
  }

  int main ( int argc, char *argv[] )
  {
      struct timeval timenow;
      long t1, t2;
      thrd_t thr;
      thrd_t ths[MAX_SERVICIO];

      // initialize
      mtx_init(&mutex,     mtx_plain);
      cnd_init(&no_lleno);
      cnd_init(&no_vacio);
      cnd_init(&arrancado);
      cnd_init(&parado);

      // create threads
      for (int i=0;i<MAX_SERVICIO;i++)
      {
            thrd_create(&ths[i], (thrd_start_t)servicio, NULL);

            // wait thread is started
            mtx_lock(&mutex) ;
            while (!ha_arrancado) {
                   cnd_wait(&arrancado, &mutex) ;
            }
            ha_arrancado = 0 ;
            mtx_unlock(&mutex) ;
      }

      // t1
      gettimeofday(&timenow, NULL) ;
      t1 = (long)timenow.tv_sec * 1000 + (long)timenow.tv_usec / 1000 ;

            // receptor...
            thrd_create(&thr, (thrd_start_t)receptor, NULL);

            // wait thread is started
            mtx_lock(&mutex) ;
            while ( (!fin) || (n_elementos > 0) ) {
                   cnd_wait(&parado, &mutex) ;
            }
            mtx_unlock(&mutex) ;

            // finalizar
            thrd_join(thr, NULL);
            for (int i=0; i<MAX_SERVICIO; i++) {
                 thrd_join(ths[i], NULL);
            }

      // t2
      gettimeofday(&timenow, NULL) ;
      t2 = (long)timenow.tv_sec * 1000 + (long)timenow.tv_usec / 1000 ;

      mtx_destroy(&mutex);
      cnd_destroy(&no_lleno);
      cnd_destroy(&no_vacio);
      cnd_destroy(&arrancado);
      cnd_destroy(&parado);

      // imprimir t2-t1...
      printf("Tiempo total: %lf\n", (t2-t1)/1000.0);
      return 0;
  }
  ```

Para compilar y ejecutar hay que usar:
```bash
gcc -Wall -g -o threads_pool  threads_pool.c
./threads_pool
```

**Video suplementario**:
  * <a href="https://www.youtube.com/watch?v=nDyYrpFYG-4&t=940s">Ejemplo de servidor de peticiones basado en hilos pre-creados</a>



## 6.- Información adicional
  * [Ejemplos para Sistemas Operativos (github)](https://github.com/acaldero/uc3m_so/blob/main/ejemplos/README.md)

  <html>
  <small>
  <table>
  <tr><th>Sesión</th><th>Tema</th><th>:notebook: Transparencias</th><th>:clapper: Videos</th></tr>
  <tr><td rowspan="3">2</td>
      <td>Hilos</td>
      <td><ul>
        <li> <a href="https://acaldero.github.io/uc3m_so/transparencias/clase_w6-hilos.pdf">hilos.pdf</a></li>
      </ul></td>
      <td>
      <ul type="1">
        <li><a href="https://youtu.be/n5qrEotEWfI">Introducción a hilos</a></li>
        <li><a href="https://youtu.be/akf9UG7Z5Go">Principales servicios de hilos</a></li>
      </ul>
      </td>
  </tr>
  <tr><td>Repaso de concurrencia</td>
      <td><ul>
        <li> <a href="https://acaldero.github.io/uc3m_so/transparencias/clase_w9-concurrencia-introduccion.pdf">concurrencia-introduccion.pdf</a> </li>
        <li> <a href="https://acaldero.github.io/uc3m_so/transparencias/clase_w10-concurrencia-servicios.pdf">concurrencia-servicios.pdf</a> </li>
      </ul></td>
      <td>
      <ul type="1">
        <li><a href="https://youtu.be/PxjgVYgpGkk">Introducción</a></li>
        <li><a href="https://youtu.be/EupaagvNpR0">Mecanismos sincronización POSIX</a></li>
        <li><a href="https://youtu.be/8fdum4cvlvI">Ejemplo simple de productor-consumidor con mecanismos POSIX</a></li>
      </ul>
      </td>
  </tr>
  <tr><td>Servidores concurrentes</td>
      <td><ul>
        <li> <a href="https://acaldero.github.io/uc3m_so/transparencias/clase_w11-concurrencia-servidores.pdf">concurrencia-servidores.pdf</a> </li>
      </ul></td>
      <td>
      <ul type="1">
        <li><a href="https://youtu.be/nDyYrpFYG-4">Servidores concurrentes</a></li>
      </ul>
      </td>
  </tr>
  </table>
  </small>
  </html>

