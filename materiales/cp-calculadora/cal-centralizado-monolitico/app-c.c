
/*
 *  Copyright 2020-2025 Felix Garcia Carballeira, Alejandro Calderon Mateos,
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


  // Sumar: *r = a + b Y devuelve 0
  int add ( int *r, int a, int b ) ;

  // Divide dos números enteros: *r = a + b Y devuele (-1 si b==0 / 0 si b!=0)
  int divide ( int *r, int a, int b ) ;

  // Cambio de signo: *r = -a Y devuelve 0
  int neg ( int *r, int a ) ;




int main ( int argc, char *argv[] )
{
    int   N1 = 20 ;
    int   N2 = 10 ;
    int   val, ret ;

    // add
    ret = add(&val, N1, N2) ;
    printf("%d = add(%d, %d, %d)\n", ret, val, N1, N2) ;

    // sub
    ret = divide(&val, N1, N2) ;
    printf("%d = divide(%d, %d, %d)\n", ret, val, N1, N2) ;

    // neg
    ret = neg(&val, N2) ;
    printf("%d = neg(%d, %d)\n", ret, val, N2) ;

    return 0 ;
}



/*
 * Internal functions
 */


// Sumar dos números enteros.
int add ( int *r, int a, int b )
{
    *r = a + b ;
    return 0 ;
}

// Divide dos números enteros.
int divide ( int *r, int a, int b )
{
    if (0 == b) {
        *r = 0 ;
	return -1 ;
    }

    *r = a / b ;
    return 0 ;
}

// Cambio de signo de un número entero.
int neg ( int *r, int a )
{
    *r = -a ;
    return 0 ;
}

