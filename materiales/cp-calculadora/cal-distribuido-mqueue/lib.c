
/*
 *  Copyright 2020-2026 Felix Garcia Carballeira, Alejandro Calderon Mateos,
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


#include "lib.h"


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

