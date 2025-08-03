
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

#ifndef LIB_MSG_H
#define LIB_MSG_H

   #define MAX 256

   //  message = op + q_name + (a, b) + (a, b) + (a)
   struct message 
   {
      // peticion 
      int    op;
      char   q_name[MAX];
      int    a;
      int    b;
      // respuesta
      int    value;
      char   status;
   } ;

#endif


