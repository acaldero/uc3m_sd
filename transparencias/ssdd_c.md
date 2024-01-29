# Resumen de los principales aspectos del lenguaje C para Sistemas Distribuidos

### Materiales usados en ARCOS.INF.UC3M.ES con Licencia [CC BY-NC 4.0](http://creativecommons.org/licenses/by-nc/4.0/)


## Requisitos

Los principales requisitos son:
* Tener conexión a Internet para consultar documentación.
* Tener acceso a una máquina con Linux. 
  * -> se recuerda que el Laboratorio del Departamento de Informática ofrece unas Aulas Virtuales en: ["https://www.lab.inf.uc3m.es/servicios/aulas-virtuales-del-laboratorio/](https://www.lab.inf.uc3m.es/servicios/aulas-virtuales-del-laboratorio/)
* Tener instalado el software para desarrollo que sea preciso en la máquina con Linux:
  * sudo apt-get install build-essential gdb ddd


## 1.- Proceso de compilación

El lenguaje C estándar es compilado (y no interpretado como Python) por lo que a partir del código fuente hay que primero compilar para generar un código ejecutable que es el que se ejecuta.

**Si todo va bien**, el proceso de trabajo en general es:
  ```mermaid
    stateDiagram-v2
    direction LR
    state "Editor"                  as s_edit
    state "Compilador"              as s_cc
    state "Ejecutar"                as s_exe

    [*]       --> s_edit:   editar   ->\n  gedit main.c
    s_edit    --> s_cc:     compilar ->\n  gcc -o main ...
    s_cc      --> s_exe:    ejecutar ->\n  ./main
    s_exe     --> [*]:      ejecución\n correcta
  ```

Como ejemplo usaremos el siguiente archivo:
* main.c
  ```c
  #include <stdio.h>

  int main ( int argc, char *argv[] )
  {
     printf("Hola mundo... %d\n",
     /*                     ^           */
     /*                     |           */
                           argc) ;

     return 0 ;
  }
  ```

Para compilar usaremos:

```bash
gcc -g -Wall -c main.c -o main.o
gcc -g -Wall -o main      main.o
```

* <details>
    <summary>Sobre -g, -Wall, ... (hacer click)</summary>

   * A la hora de compilar se utiliza los siguientes modificadores (flags):
     * "-g" para añadir información de depuración que es útil si se usa un depurador
     * "-Wall" para que muestre todas las advertencias (Warnings) de posibles problemas que detecte el compilador
   * Se podría usar también:
     * "-Werror" para indicar que trate todas las advertencias (warnings) como errores.
     * "-std=c90 -pedantic" para indicar que use el estándar de C versión 90 de forma extricta sin extensiones de GNU adicionales.

  </details>

Para ejecutar usaremos:

```bash
./main
```


### 1.1 Y si hay problemas... depuramos

La premisa es que todo vaya bien y no haya problemas.
Pero nuestro trabajo incluye tratar con problemas para resolverlos de la mejor forma posible.
Los problemas habituales aparecen:
* A la hora de compilar: errores de compilación por sintáxis incorrecta del archivo fuente .c
  * <details>
      <summary>Recomendaciones para depurar problemas de compilación... (hacer click)</summary>

    * Tratar de solucionar primero el primer error que aparece y luego volver a compilar (hay errores dependientes de otros)
    * Leer bien los mensajes de error del compilador, buscando entender qué problema indica el compilador:
      * Buscar primero en la línea indicada en el compilador...
      * ...es posible que haya un error en el código en la línea X que se manifieste para el compilador como otro error y en líneas posteriores
    </details>
* A la hora de ejecutar: errores de ejecución porque el comportamiento esperado no es igual al comportamiento real.
  * <details>
      <summary>Recomendaciones para depurar problemas de ejecución... (hacer click)</summary>

      * El uso de "fuerza bruta" con mensajes de impresión (programas pequeños y/o uso de hilos):
        * Mensaje de los puntos por dónde pasa la ejecución: ```printf("Aquí 1\n"); ... printf("Aquí 2\n"); ...```
        * Mensaje de qué estado tienen las variables entre dos puntos anteriores: ```printf("variable: %d\n", valor_int); ....```
      * El uso de algún depurador (kdbg, ddd, gdb, ...)
      * Realizar programación "defensiva": desde el principio añadir todas las comprobaciones y mensajes de impresión posibles 
    </details>

El proceso de trabajo en general incluyendo el tratamiento de problemas sería en general:
  ```mermaid
    stateDiagram-v2
    direction TB
    state "Editor"       as s_edit
    state "Compilador"   as s_cc
    state "Ejecutar"     as s_exe
    state "Depurador"    as s_dbg

    [*]       --> s_edit
    s_edit    --> s_cc:     compilar
    s_cc      --> s_edit:   problema al compilar
    s_cc      --> s_exe:    ejecutar
    s_exe     --> s_edit:   problema detectado al ejecutar
    s_exe     --> s_dbg:    problema al ejecutar
    s_dbg     --> s_edit:   problema detectado al depurar
    s_exe     --> [*]:      ejecución correcta
  ```

<details>
  <summary>Depurar con ddd... (hacer click)</summary>
<br>

 * Para depurar con ddd ha de ejecutar:
   ```bash
   ddd ./main &
   ```

 * La aplicación ddd es una interfaz gráfica sobre el depurador gdb de línea de mandatos, facilitando su uso:
  ![DDD | main](./images/ddd-1.jpg)

 * Se puede instalar en Debian/Ubuntu mediante:
   ```bash
   sudo apt-get install ddd
   ```
 
</details>


<details>
  <summary>Depurar con seer... (hacer click)</summary>
<br>
 
 * NOTA: aprovecho para agradecer a Adolfo la información de seer así como recomendar su uso
 
 * Seer está disponible en:
   https://github.com/epasveer/seer 

 * Seer es una interfaz gráfica para gdb en Linux:
   ![seer | main](https://raw.githubusercontent.com/epasveer/seer/main/images/mainview.png)

</details>


## 2.- Sentencias de control de flujo en C

Como ejemplo de uso de sentencias de control de flujo en C, usaremos el siguiente archivo:
* main.c
  ```c
  #include <stdio.h>

  int main ( int argc, char *argv[] )
  {
     int i ;

     if (NULL == argv)  {
         printf("argv is NULL 🦖\n") ;
     }

     for (i=0; i<argc; i++)
     {
        printf(" argv[%d] -> %s\n", i, argv[i]) ;
     }

     return 0 ;
  }
  ```
  
Este ejemplo permite imprimir los argumentos con los que se invoca un programa.

```bash
gcc -g -Wall -c main.c -o main.o
gcc -g -Wall -o main      main.o

./main uno dos tres
```

Recordatorios:
* <details>
  <summary>De "alternar" entre opciones en C... (hacer click)</summary>

  * if-then-else:
    ```c
    if ("condición cierta o falsa")  // 0 es falso y resto es verdadero
    {
      "si es cierta..."
    }
    else
    {
      "si es falsa..."
    }
    ```
  </details>
* <details>
  <summary>Para "iterar" en C... (hacer click)</summary>

  * for (de 0 a n veces):
    ```c
    for ("valores iniciales de contadores"; "condición de mantenimiento en el bucle"; "actualización de contadores")
    {
      ...
    }
    ```
  * while (de 0 a n veces):
    ```c
    "valores iniciales de contadores";
    while ("condición de mantenimiento en el bucle")
    {
      ...
      "actualización de contadores";
    }
    ```
  * do-while (de 1 a n veces):
    ```c
    "valores iniciales de contadores";
    do
    {
      ...
      "actualización de contadores";
    }
    while ("condición de mantenimiento en el bucle")
    ```
</details>


NOTA: gracias a José Antonio por el siguiente ejercicio:
* Iterar de 1 a 100 y si el número es múltiplo de 3, escribir "Fizz"; si es múltiplo de 5, "Buzz"; y si es múltiplo de 3 y 5, "FizzBuzz".

* <details>
  <summary>Posible implementación... (hacer click)</summary>

  ```c
  #include <stdio.h>

  int main ( int argc, char *argv[] )
  {
     int i ;

     for (i=0; i<100; i++)
     {
        printf("%d -> ", i) ;

        if ((i % 3) == 0)
        {
            printf("Fizz") ;
        }
        if ((i % 5) == 0)
        {
            printf("Buzz") ;
        }

        printf("\n") ;
     }

     return 0 ;
  }
  ```

  </details>


**Información recomendada**:
  * [Sentencias de control (youtube)](http://www.youtube.com/watch?embed=no&v=ux_J98WmjPA&feature=related)



## 3.- Uso de estructuras (struct) en C

Como ejemplo de (array de) structs, usaremos el siguiente archivo:
* main.c
  ```c
  #include <stdio.h>
  #include <stdlib.h>

  #define N_PERSONAS 10

  struct dni {
     int  id ;
     char letra ;
     char nombre[128] ;
  } ;

  struct dni personas[N_PERSONAS] ;

  int main ( int argc, char *argv[] )
  {
     int i ;

     /* Rellenar personas con valores por defecto (persona 0,1...) */
     for (i=0; i<N_PERSONAS; i++)
     {
        personas[i].id    = i ;
        personas[i].letra = 'A' ; 
        sprintf(personas[i].nombre,  /* cadena destino */
               "persona %d",         /* formato */
               personas[i].id) ;     /* %d */
     }

     /* Imprimir personas */
     for (i=0; i<N_PERSONAS; i++)
     {
        printf(" * Persona '%s' que tiene un id '%d' y letra '%c'.\n",
               personas[i].nombre,
               personas[i].id,
               personas[i].letra) ;
     }

     /* El tamaño de un struct puede no ser la suma del tamaño de los campos que la componen: puede haber rellenos */
     printf(" * Tamaño en bytes del tipo DNI: %ld\n", sizeof(struct dni)) ;
     printf(" * Tamaño en bytes de los campos del tipo DNI: %ld, %ld, %ld\n",
                sizeof(personas[0].nombre), sizeof(personas[0].letra), sizeof(personas[0].id)) ;

     return 0 ;
  }
  ```

Aclaraciones:
* Sobre arrays:
  * Al usar un array con solo su nombre (sin corchetes []) tendremos la dirección de memoria del primer elemento
    * array == &(array[0])
    * Es una dirección de memoria constante (determinada en tiempo de compilación) que apunta a un elemento variable (en tiempo de ejecución puede cambiar).
  * No hay un tipo string ya incluido en C pero podemos usar un array de caracteres para representar un string de una longitud máxima prefijada en compilación:
    ```c
    char string1[128]; // string de hasta 127 caracteres más caracter fin de cadena ('\0') para indicar el último

    strcpy(string1, "Hola mundo") ;
    ```
* Sobre structs:
  * Al definir un tipo estructura con ```struct nombre-de-tipo-estructura``` "siempre" tenemos que usar la palabra struct en el nombre del tipo para definir variables: ```struct nombre-de-tipo-estructura variable```
  * Es posible crear un tipo nuevo de datos a partir de otros con typedef:
    ```c
    typedef   struct dni     cien_personas[100] ;
    cien_personas  personal ;
    ```
  * Es posible no tener que usar "struct" siempre al crear un tipo nuevo de datos con typedef:
    ```c
    typedef   struct dni     dni_t ;
    dni_t personas[N_PERSONAS] ;
    ```

**Información recomendada**:
* [Array y Struct en C (youtube)](http://www.youtube.com/watch?embed=no&v=o5Jl_Dzga88&feature=related)



## 4.- Uso de punteros I (qué es un puntero)

Como ejemplo inicial de qué representa un puntero en C, usaremos el siguiente archivo:
* main.c
  ```c
  #include <stdio.h>
  #include <stdlib.h>

  int main ( int argc, char *argv[] )
  {
      /* Definir variables */
      int   i ;
      int *pi ;     /* (1) */
  //  int &ri = i ; /* (2) <- solo en C++ */


      /* Modificar valor de variables */
       i  = 5 ;
       pi = &i ;     /* (4) */
      *pi = 5 ;      /* (3) */
  //   ri = 5 ;      /* <- solo en C++ */


      /* Consultar valor de variables */
      printf("  i = %d\n",   i) ;
      printf(" pi = %x\n",  pi) ;
      printf("*pi = %d\n", *pi) ; /* (3) */
  //  printf(" ri = %d\n",  ri) ; /* <- solo en C++ */

      // Una variable puntero es un variable que guarda la dirección de una posición de memoria,
      // se parece mucho a una variable del tipo "unsigned long int"
      printf(" pi = %x\n",  pi) ;
      printf(" &i = %x\n",  &i) ; /* (4) */
      // Una variable puntero a su vez se guarda en una posición de memoria
      // (se puede aplicar el operador & para conocer dicha dirección)
      printf("&pi = %x\n", &pi) ; /* (4) */

      return 0 ;
  }
  ```

A recordar:
* El uso de los operadores "&" y "*" depende del contexto:

  | contexto/operador    |   *                |   &                  |
  |:--------------------:|:------------------:|:--------------------:|
  | definición variable  | (1) puntero a...   | (2) referencia a...  |
  | uso de variable      | (3) acceder a...   | (4) dirección de...  |

**Información recomendada**:
* [Introducción a punteros  I (youtube)](http://www.youtube.com/watch?embed=no&v=iQF-2vUNEJk&feature=related)
* [Introducción a punteros II (youtube)](http://www.youtube.com/watch?embed=no&v=m6sdKI3zhKg&feature=related)



## 4.- Uso de punteros II (memoria dinámica)

Como ejemplo de uso de punteros para memoria dinámica, usaremos el siguiente archivo:
* main.c
  ```c
  #include <stdio.h>
  #include <stdlib.h>


  void imprimir ( int *vector, int n_eltos )
  {
      int i ;

      for (i=0; i<n_eltos; i++)
      {
           printf(" >> vector[%d] = %d\n", i, vector[i]) ;
      }
  }

  int main ( int argc, char *argv[] )
  {
      /*
       * Array estático
       */

      /* Definir array estático (de tamaño fijo, en tiempo de compilación) */
      int  earray[5]  = { 1, 2, 3, 4, 5 } ;

      /* Modificar valor de variables */
        earray[0] = 1 ;   earray[1] = 2 ;   earray[2] = 3 ;   earray[3] = 4 ;   earray[4] = 5 ;
      *(earray+0) = 1 ; *(earray+1) = 2 ; *(earray+2) = 3 ; *(earray+3) = 4 ; *(earray+4) = 5 ;

  /* CUIDADO:
      earray[5] = 5 ;  !!  fuera de rango
  */

      /* Consultar valor de variables */
      printf("Estático:\n") ;
      imprimir(earray, 5) ;


      /*
       * Array dinámico
       */

      /* Definir array dinámico (tamaño variable fijado en ejecución) */
      int *darray  = NULL ;
      int  n_eltos = 0 ;

            /* a) vamos a pedir memoria para 2 enteros... */
            n_eltos = 2 ;
            darray  = malloc(n_eltos * sizeof(int)) ;
            if (NULL == darray) {
                perror("malloc ha fallado: ") ;
                exit(-1) ;
            }

      /* Modificar valor de variables */
        darray[0] = 1 ;   darray[1] = 2 ;
      *(darray+0) = 1 ; *(darray+1) = 2 ;

  /* CUIDADO:
      darray    = 1 ;  !!  darray almacena la dirección 0x1 de memoria pero no se guarda 1 en el primer elemento
      darray[2] = 3 ;  !!  fuera de rango
  */

      /* Consultar valor de variables */
      printf("Dinámico:\n") ;
      imprimir(darray,  n_eltos) ;

  /* CUIDADO:
      imprimir(&darray, n_eltos) ;  !! dirección de la variable que guarda la dirección del primer elemento...
  */

            /* b) se libera la memoria cuando ya NO sea necesario volver a usarse */
            free(darray) ;
            darray  = NULL ;
            n_eltos = 0 ;

      return 0 ;
  }
  ```

En este ejemplo:
* Hay un array estático (earray) de enteros:
  * Un array estático es de tamaño fijo determinado en tiempo de compilación.
  * En tiempo de ejecución no se puede cambiar su tamaño por lo que normalmente se indica en tiempo de compilación un tamaño máximo que el/la programador/a no se ha de sobrepasar.
* Hay un array dinámico (darray) de enteros:
  * El array dinámico se implementa con dos elementos: un entero con el tamaño del array (en elementos o bytes) y un puntero al primer elemento (el resto están a continuación).
  * En tiempo de ejecución se reserva espacio (malloc) y luego se puede usar como un array estático (usando los corchetes y el índice del elemento a acceder).

A recordar en C:
* **Hay que llevar la contabilidad de los punteros al usarlos**:
  * **Dirección**: ¿es válida?
  * **Espacio apuntado**: ¿se ha reservado previamente (en compilación o ejecución)?
* Estados en el uso recomendado de un puntero:
  ```mermaid
    stateDiagram-v2
    direction TB
    state "px==¿?"             as px_xx
    state "px==NULL"           as px_null
    state "px==&x"             as px_atx
    state "px -> alloc(size)"  as px_alloc

    px_xx     --> px_null:  px = NULL
    px_null   --> px_atx:   px = &x
    px_atx    --> px_null:  px = NULL
    px_null   --> px_alloc: px = malloc(size_en_bytes)
    px_alloc  --> px_null:  free(px) + px = NULL
    px_alloc  --> px_alloc: px_aux = realloc(px, nuevo_size_en_bytes) +\n if (px_aux != NULL) px = px_aux
    px_atx    --> px_alloc: px = malloc(size_en_bytes)
  ```

**Información recomendada**:
* [Introducción a punteros  I (youtube)](http://www.youtube.com/watch?embed=no&v=iQF-2vUNEJk&feature=related)
* [Introducción a punteros II (youtube)](http://www.youtube.com/watch?embed=no&v=m6sdKI3zhKg&feature=related)



## 5.- Paso de parámetros a funciones

Es importante tener presente que en lenguaje C:
* Los valores con los que se llama a una función se llaman **argumentos reales**:
  ```c
  int ret = f(1, 'a', 3.14) ;
  ```
* Los valores dentro de una función se llaman **argumentos formales**:
  ```c
  int f(int a1, char a2, float a3) { ... }
  ```
* **En el momento de la llamada a una función se hace una asignación (copia) de los argumentos reales a los formales**.
  * Por tanto, **TODO argumento se pasa por valor**.
* El nombre de un array de tipo X equivale a la dirección de memoria donde se guarda el primer elemento de tipo X
  * Por tanto, el argumento formal para un array de tipo X puede ser un puntero a X.
  ```c
        int f(char *a4, char a5[]) ;
       //           ^        ^
       //           |        |
  int ret = f(array_char, "Hola") ;
  ```


Como ejemplo de paso por parámetros, usaremos el siguiente archivo:
* main.c
  ```c
  #include <stdio.h>
  #include <stdlib.h>

  int imprimir_char ( char valor )
  {
      printf("valor: '%c'\n", valor) ;

      return 1 ; // convenio aquí: 1 OK y 0 KO
  }

  int imprimir_string ( char *valor )
  {
      // comprobar argumentos: programación "defensiva"...
      if (NULL == valor)
          return 0 ;

      // si todo bien, acción y devolver OK
      printf("valor: '%s'\n", valor) ;

      return 1 ; // convenio aquí: 1 OK y 0 KO
  }

  int main ( int argc, char *argv[] )
  {
      int ret ;
      char  c  = 'x' ;
      char *s1 = "Hola" ;
      char  s2[120] ;

      /* Caracter (char) */

         ret = imprimir_char(c) ;
         if (ret != 1) return -1 ;

         ret = imprimir_char('x') ;
         if (ret != 1) return -1 ;


      /* Cadena de caracteres (string) */

         ret = imprimir_string(s1) ; // a recordar: s1 es la dirección del primer caracter en la cadena guardada en s1
         if (ret != 1) return -1 ;

         ret = imprimir_char(s1[3]) ;
         if (ret != 1) return -1 ;

         ret = imprimir_char(*(s1+3)) ;
         if (ret != 1) return -1 ;

         strcpy(s2, "Adios") ;
         ret = imprimir_string(s2) ; // a recordar: s2 es la dirección del primer caracter en la cadena guardada en s2
         if (ret != 1) return -1 ;

         ret = imprimir_char(s2[3]) ;
         if (ret != 1) return -1 ;

         ret = imprimir_char(*(s2+3)) ;
         if (ret != 1) return -1 ;

      return 0 ; // convenio aquí: 0 OK, negativos KO
  }
  ```

**Información recomendada**:
* [Paso de parámetros a funciones (youtube)](https://youtu.be/mS0gnJ-su_Y&t=7m33s)


Como ejemplo de paso por parámetros de punteros, usaremos el siguiente archivo:
* main.c
  ```c
  #include <stdio.h>
  #include <stdlib.h>

  void * mi_malloc ( long size )
  {
      // comprobar argumentos...
      if (0 == size) return NULL ;

      return (void *)malloc(size) ;
  }

  int mi_free ( void **ptr )
  {
      // comprobar argumentos...
      if (NULL == ptr) return -1 ;

      // si ya es NULL, ignorar
      if (NULL == *ptr) return 0 ;

      // liberar y poner a NULL
      free(*ptr) ;
      *ptr = NULL ;

      return 1 ;
  }

  int main ( int argc, char *argv[] )
  {
      int ret ;
      char *s1 ;

      s1 = mi_malloc(128) ;

   // ...

      mi_free(&s1) ;

      return 0 ;
  }
  ```

**Información recomendada**:
* [Paso de parámetros a funciones (youtube)](https://youtu.be/mS0gnJ-su_Y&t=7m33s)



## 6.- Archivos de cabecera y proyectos de varios archivos

Como ejemplo usaremos estos tres archivos:

* lib_hola.h
  ```c
  // NOTA: "guarda" para evitar incluir más de una vez la misma librería por importaciones "transitivas"
  #ifndef LIB_HOLA
  #define LIB_HOLA

      // NOTA: solo "declaraciones" (e.g.: external int err_code;) y no "definiciones" (e.g.: int err_code = 0;)
      void di_hola ( void ) ;

  #endif
  ```

* lib_hola.c
  ```c
  // NOTA: el preprocesador remplaza "#include" por el contenido del archivo de cabecera
  #include "lib_hola.h"

  void di_hola ( void )
  {
     printf("Hola Mundo...\n") ;
  }
  ```

* main.c
  ```c
  // NOTA: el preprocesador remplaza "#include" por el contenido del archivo de cabecera
  #include "lib_hola.h"
  // NOTA: usar #include <fichero> solo busca en las cabeceras del sistema,
  //       #include "fichero" busca además en directorios definidos por programador(a)
  //       con el argumento -Idirectorio al compilar
  #include <stdio.h>

  int main ( int argc, char *argv[] )
  {
     di_hola() ;

     return 0 ;
  }
  ```


Para compilar los anteriores archivos hay que ejecutar:

```bash
gcc -g -Wall -c lib_hola.c -o lib_hola.o
gcc -g -Wall -c main.c     -o main.o      -I./
gcc -g -Wall -o main main.o lib_hola.o
```

Donde:
* "-c ... -o ..." genera el archivo binario asociado a un fichero fuente:
  ```bash
  gcc -g -Wall -c fichero.c -o fichero.o
  ```
* "-o ... libs..." genera el archivo ejecutable combinando todos los binarios (incluidas bibliotecas como libc.a con -lc):
  ```bash
  gcc -g -Wall -o fichero fichero.o lib_hola.o -lc
  ```


**Información recomendada**:
  * [Ejemplo de biblioteca (youtube)](https://youtu.be/B_7jBxe_VOQ&t=2m34s)
  * [Solucionar las multiples inclusiones (youtube)](https://youtu.be/B_7jBxe_VOQ&t=5m04s)
  * [Ejemplo de bibliotecas estática (youtube)](https://youtu.be/B_7jBxe_VOQ&t=7m42s)
  * [Ejemplo de bibliotecas dinámica (youtube)](https://youtu.be/B_7jBxe_VOQ&t=10m05s)

