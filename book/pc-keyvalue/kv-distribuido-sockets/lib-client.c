
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "lib-client.h"
#include "lib-mesg.h"


int d_send_receive ( struct message *pr )
{
     int ret ;
     int sd_server ;
     struct sockaddr_in address;

     // open server sockets
     sd_server = socket(AF_INET, SOCK_STREAM, 0) ;
     if (sd_server <= 0) {
        perror("socket: ") ;
        exit(-1) ;
     }

     // connect
     address.sin_family = AF_INET ;
     address.sin_port   = htons(4200) ;

     ret = inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) ;
     if (ret <= 0) { 
         printf("\nInvalid address or address not supported\n") ;
	 close(sd_server) ;
         exit(-1);
     } 

     ret = connect(sd_server, (struct sockaddr *)&address, sizeof(address)) ;
     if (ret < 0) { 
         perror("connect: ");
	 close(sd_server) ;
         exit(-1);
     } 

     // send request
     ret = write(sd_server, (char *)pr, sizeof(struct message)) ;
     if (ret < 0) {
	 perror("write: ") ;
	 close(sd_server) ;
         exit(-1);
     }

     // receive response
     ret = read(sd_server, (char *)pr, sizeof(struct message)) ;
     if (ret < 0) {
	 perror("read: ") ;
	 close(sd_server) ;
         exit(-1);
     }

     // close socket
     ret = close(sd_server) ;
     if (ret < 0) {
	 perror("close: ") ;
         exit(-1);
     }

     // return status
     return pr->status ;
}

int d_init ( char  *nombre,  int  N )
{
     struct message pr;

     // init message
     bzero(&pr, sizeof(struct message)) ;
     pr.op    = 1 ;
     pr.value = N ;
     strcpy(pr.name,   nombre) ;

     // send request and receive response
     d_send_receive(&pr) ;

     // return status
     return pr.status ;
}

int d_set ( char *nombre, int i, int valor )
{
     struct message pr;

     // set message
     bzero(&pr, sizeof(struct message)) ;
     pr.op    = 2 ;
     pr.i     = i ;
     pr.value = valor ;
     strcpy(pr.name,   nombre) ;

     // send request and receive response
     d_send_receive(&pr) ;

     // return status
     return pr.status ;
}

int d_get ( char *nombre, int i, int *valor )
{
     struct message pr;

     // get message
     bzero(&pr, sizeof(struct message)) ;
     pr.op    = 3 ;
     pr.i     = i ;
     strcpy(pr.name, nombre) ;

     // send request and receive response
     d_send_receive(&pr) ;

     // return value + status
     *valor = pr.value ;
     return pr.status ;
}

