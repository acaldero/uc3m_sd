
/*
 *  Copyright 2020-2021 Felix Garcia Carballeira, Alejandro Calderon Mateos,
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


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib.h"


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

