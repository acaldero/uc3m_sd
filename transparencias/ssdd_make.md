
# Resumen de los principales aspectos del uso de Make para Sistemas Distribuidos
+ **Felix García Carballeira y Alejandro Calderón Mateos**
+ [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-blue.svg)](https://github.com/acaldero/uc3m_sd/blob/main/LICENSE)


## Requisitos

Los principales requisitos son:
* Tener conexión a Internet para consultar documentación.
* Tener acceso a una máquina con Linux con software de desarrollo instalado:
  * Puede usar las Aulas Virtuales del Laboratorio del Departamento de Informática:
    * ["https://www.lab.inf.uc3m.es/servicios/aulas-virtuales-del-laboratorio/](https://www.lab.inf.uc3m.es/servicios/aulas-virtuales-del-laboratorio/)
  * Puede usar su Debian/Ubuntu con: sudo apt-get install build-essential gdb ddd


## Ejemplo de código para compilar con Makefile

Usaremos tres archivos:

* lib_hola.h
  ```c
  void di_hola ( void ) ;
  ```

* lib_hola.c
  ```c
  void di_hola ( void )
  {
     printf("Hola Mundo...") ;
  }
  ```

* main.c
  ```c
  #include <lib_hola.h>

  int main ( int argc, char *argv[] )
  {
     di_hola() ;
     return 0 ;
  }
  ```

## Compilación SIN Makefile (compilación manual)

Para compilar los anteriores archivos hay que ejecutar los siguientes mandatos:

```bash
gcc -g -Wall -c lib_hola.c -o lib_hola.o
gcc -g -Wall -c main.c     -o main.o
gcc -g -Wall -o main main.o lib_hola.o
```

## Compilación con Makefile (primera versión)

* Archivo Makefile inicial:
  ```bash
  all:
  	gcc -g -Wall -c lib_hola.c -o lib_hola.o
  	gcc -g -Wall -c main.c     -o main.o
  	gcc -g -Wall -o main main.o lib_hola.o
  ```

Para usar el archivo Makefile hay que ejecutar:
```bash
make
```

El esqueleto del Makefile anterior es:
```bash
targets: prerequisites
	command 1
	command 2
	command 3
```
Donde para obtener un objetivo (targets) se indica 2 elementos:
  * Prerequisitos (prerequisites): que son objetivos que hay que cumplir primero
  * Mandatos (command 1/2/3): una vez se tengan los prerequisitos la forma de tener el objetivo es ejecutar los mandatos uno detrás de otro
  * Importante: no vale usar espacios en blanco antes de cada "gcc -g ...", solo vale tabuladores.


## Compilación con Makefile (segunda versión con variables)

* Archivo Makefile:
  ```bash
  CC=gcc
  CFLAGS=-g -Wall

  all:
  	$(CC) $(CFLAGS) -c lib_hola.c -o lib_hola.o
  	$(CC) $(CFLAGS) -c main.c     -o main.o
  	$(CC) $(CFLAGS) -o main main.o lib_hola.o
  ```

Para usar el archivo Makefile hay que ejecutar:
```bash
make
```

## Compilación con Makefile (tercera versión con reglas)

* Archivo Makefile:
  ```bash
  CC=gcc
  CFLAGS=-g -Wall
  OBJS=main.o lib_hola.o

  all: $(OBJS)
  	$(CC) $(CFLAGS) -o main $(OBJS)

  lib_hola.o: lib_hola.c
  	$(CC) $(CFLAGS) -c lib_hola.c -o lib_hola.o

  main.o: main.c
  	$(CC) $(CFLAGS) -c main.c     -o main.o
	
  clean: $(OBJS)
  	rm -fr $(OBJS)
  ```

Para usar el archivo Makefile se recomienda ejecutar:
```bash
make clean; make
```


## Compilación con Makefile (cuarta versión con reglas especiales)

* Archivo Makefile:
  ```bash
  CC=gcc
  CFLAGS=-g -Wall
  OBJS=main.o lib_hola.o

  .PHONY: all clean

  all: $(OBJS)
  	$(CC) $(CFLAGS) -o main $(OBJS)

  %.o: %.c
  	@echo "Compiling... $<"
  	$(CC) $(CFLAGS) -c $< -o $@

  clean: $(OBJS)
  	@echo "Removing $(OBJS)..."
  	rm -fr $(OBJS)
  ```

Para usar el archivo Makefile se recomienda ejecutar:
```bash
make clean; make
```

Hay dos reglas especiales:
* La regla de ignorar ficheros que se llamen all y clean (de otra forma hacer un make all si hay un archivo all supone que se cumple la regla y no se ejecuta):
  ```bash
    .PHONY: all clean
  ```
* Usar una única regla para indicar que cada archivo .o (%.o) precisa un archivo .c asociado (%.c) y se compila con ```-c $< -o $@``` donde ```$<``` es el nombre del archivo .c y ```$@``` es el nombre del archivo .o:
  ```bash
    %.o: %.c
    	@echo "Compiling... $<"
  	$(CC) $(CFLAGS) -c $< -o $@
  ```



## Material recomendado
  * https://makefiletutorial.com/
  * https://www3.nd.edu/~zxu2/acms60212-40212/Makefile.pdf


