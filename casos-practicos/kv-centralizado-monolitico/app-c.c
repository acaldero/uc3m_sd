
/*
 *  Copyright 2020-2024 Felix Garcia Carballeira, Alejandro Calderon Mateos,
 *
 *  This file is part of nanodt proyect.
 *
 *  nanodt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nanodt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with nanodt.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


   // Inicializar un array distribuido de N números enteros.
   int init ( char  *nombre,  int  N ) ;

   // Inserta el valor en la posición i del array nombre.
   int set ( char *nombre, int i, int valor ) ;

   // Recuperar el valor del elemento i del array nombre. 
   int get ( char *nombre, int i, int *valor ) ;



int   N = 10 ;
char *A = "nombre" ;


int main ( int argc, char *argv[] )
{
    int ret ;
    int val ;

    // init
    ret = init(A, N) ;
    if (ret < 0) {
        printf("init: error code %d\n", ret) ;
        exit(-1) ;
    }

    for (int i=0; i<N; i++)
    {
	    // set
	    ret = set (A, 100+i, i) ;
	    if (ret < 0) {
		printf("set: error code %d\n", ret) ;
		exit(-1) ;
	    }
	    printf("set(\"%s\", %d, 0x%x)\n", A, 100+i, i) ;
    }

    for (int i=0; i<N; i++)
    {
	    // get
	    ret = get (A, 100+i, &val) ;
	    if (ret < 0) {
		printf("get: error code %d\n", ret) ;
		exit(-1) ;
	    }
	    printf("get(\"%s\", %d) -> 0x%x\n", A, 100+i, val) ;
    }

    return 0 ;
}



/*
 * Internal data
 */

int    a_neltos = 0 ;
int  **a_values ; // = [ [0…N1], [0…N2], ... [0…NN] ] ;
char **a_keys   ; // = [ "key1", "key2", ... "keyN" ] ;


/*
 * Internal functions
 */

int buscar ( char *nombre )
{
     int index = -1 ;

     for (int i=0; i<a_neltos; i++) 
     {
            if (!strcmp(a_keys[i], nombre)) { 
                return i ;
            }
     }

     return index;
}

int insertar ( char *nombre, int N )
{
     void *ret ;

     // add new vector => [ [0…N1], [0…N2], ... [0…NN] ]
     ret = realloc(a_values, (a_neltos+1)*sizeof(int *)) ;
     if (NULL == ret) {
         perror("realloc: ") ;
         return -1 ; // en caso de error => -1
     }
     a_values = (int **)ret ;

     // new vector
     a_values[a_neltos] = malloc(N*sizeof(int)) ;
     if (a_values[a_neltos] == NULL) {
         perror("malloc: ") ;
         return -1 ; // en caso de error => -1
     }

     // add new key    => [ "key1", "key2", ... "keyN" ]
     ret = realloc(a_keys, (a_neltos+1)*sizeof(char *)) ;
     if (NULL == ret) {
         perror("realloc: ") ;
         return -1 ; // en caso de error => -1
     }
     a_keys = (char **)ret ;

     // new key
     a_keys[a_neltos] = strdup(nombre) ;
     if (a_keys[a_neltos] == NULL) {
         perror("malloc: ") ;
         return -1 ; // en caso de error => -1
     }

     a_neltos++ ;
     return 1 ; // todo bien => devolver 1
}


/*
 * API
 */

// Inicializar un array distribuido de N números enteros.
int init (char  *nombre,  int  N)
{
     int index = buscar(nombre) ;
     if (index != -1) return 0 ;   // Si array ya esté creado => devolver 0

     index = insertar(nombre, N) ;
     if (index == -1) return -1;  // en caso de error => -1

     return 1 ; // el array se ha creado por primera vez => devolver 1
}



// Inserta el valor en la posición i del array nombre.
int set (char *nombre, int i, int valor)
{
     int index = buscar(nombre) ;
     if (index == -1) {
	 return -1 ;   // Si error => devolver -1
     }

     a_values[index][i] = valor ;
     return 1;
}

// Recuperar el valor del elemento i del array nombre. 
int get (char*nombre, int i, int *valor)
{
     int index = buscar(nombre) ;
     if (index == -1) {
	 return -1 ;   // Si error => devolver -1
     }

     *valor = a_values[index][i] ;
     return 1;
}

