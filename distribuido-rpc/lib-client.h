
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

#ifndef LIB_CLIENT_H
#define LIB_CLIENT_H

   // Inicializar un array distribuido de N números enteros.
   int init ( char  *nombre,  int  N ) ;

   // Inserta el valor en la posición i del array nombre.
   int set ( char *nombre, int i, int valor ) ;

   // Recuperar el valor del elemento i del array nombre. 
   int get ( char *nombre, int i, int *valor ) ;

   // Finalizar un array distribuido
   int finalize ( char  *nombre,  int  N ) ;

#endif

