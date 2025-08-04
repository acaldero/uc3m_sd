
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
#include <signal.h>
#include <unistd.h>

#include "lib-client.h"
#include "soapH.h"
#include "calc.nsmap"


char *get_server_address ( void )
{
     char *server ;

     server = getenv("SERVER_ADDR") ;
     if (NULL == server)
     {
         printf("ERROR: SERVER_ADDR is not defined.\n") ;
         printf("\n") ;
         printf("Example of SERVER_ADDR:\n") ;
         printf("export SERVER_ADDR=localhost:12345\n") ;
	 exit(-1) ;
     }

     return server ;
}

int d_add ( int *r, int a, int b )
{
     struct soap soap ;
     char *server ;

     server = get_server_address() ;
     soap_init(&soap) ;

     soap_call_ns__add(&soap, server, "", a, b, r) ;
     if (soap.error) {
         soap_print_fault(&soap, stderr) ;
	 exit(-1) ;
     }

     soap_done(&soap) ;

     return 0 ;
}

int d_divide ( int *r, int a, int b )
{
     struct soap soap ;
     char *server ;

     server = get_server_address() ;
     soap_init(&soap) ;

     soap_call_ns__divide(&soap, server, "", a, b, r) ;
     if (soap.error) {
         soap_print_fault(&soap, stderr) ;
	 exit(-1) ;
     }

     soap_done(&soap) ;

     return 0 ;
}

int d_neg ( int *r, int a )
{
     struct soap soap ;
     char *server ;

     server = get_server_address() ;
     soap_init(&soap) ;

     soap_call_ns__neg(&soap, server, "", a, r) ;
     if (soap.error) {
         soap_print_fault(&soap, stderr) ;
	 exit(-1) ;
     }

     soap_done(&soap) ;

     return 0 ;
}


