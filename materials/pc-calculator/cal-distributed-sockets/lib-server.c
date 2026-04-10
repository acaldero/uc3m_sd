
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
#include <stdarg.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "lib.h"
#include "lib-mesg.h"


void tratar_peticion ( int arg )
{
     int ret ;
     int sd_client ;
     struct message pr ;

     sd_client = (int) arg ;
     ret = read(sd_client , &pr, sizeof(struct message)) ; 

     switch (pr.op)
     {
         case 1: // ADD
                 pr.status = add(&(pr.value), pr.a, pr.b) ;
		 printf(" %d = add(%d, %d, %d);\n",    pr.status, pr.value, pr.a, pr.b) ;
                 break ;
         case 2: // DIV
                 pr.status = divide(&(pr.value), pr.a, pr.b) ;
		 printf(" %d = divide(%d, %d, %d);\n",    pr.status, pr.value, pr.a, pr.b) ;
                 break ;
         case 3: // NEG
                 pr.status = neg(&(pr.value), pr.a) ;
		 printf(" %d = neg(%d, %d);\n",    pr.status, pr.value, pr.a) ;
                 break ;
	 default:
		 printf(" unknown op:%d, a:%d, b:%d\n", pr.op, pr.a, pr.b) ;
                 break ;
     }

     ret = write(sd_client, (char *)&pr, sizeof(struct message)) ;
     if (ret < 0) {
	 perror("write: ") ;
     }

     ret = close(sd_client);
     if (ret < 0) {
	 perror("close: ") ;
     }
}


int   do_exit = 0 ;

void sigHandler ( int signo )
{
     do_exit = 1 ;
}

int main ( int argc, char *argv[] )
{
     int ret ;
     int sd_server, sd_client ;
     struct sigaction new_action, old_action;
     struct sockaddr_in address;
     int opt = 1;
     int addrlen = sizeof(address);

     // open server sockets
     if ((sd_server = socket(AF_INET, SOCK_STREAM, 0)) == 0)
     {
        perror("socket: ");
        exit(-1);
     }

     // socket options...
     if (setsockopt(sd_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
     {
         perror("setsockopt: ");
         exit(-1);
     }

     // bind + listen
     address.sin_family      = AF_INET ;
     address.sin_addr.s_addr = INADDR_ANY ;
     address.sin_port        = htons(4200) ;

     if (bind(sd_server, (struct sockaddr *)&address,  sizeof(address)) < 0)
     {
         perror("bind: ");
         exit(-1);
     }
     if (listen(sd_server, 3) < 0)
     {
         perror("listen: ") ;
         exit(-1);
     }

     // signal handler
     new_action.sa_handler = sigHandler ;
     sigemptyset (&new_action.sa_mask) ;
     new_action.sa_flags = 0 ;
     sigaction (SIGINT, NULL, &old_action) ;
     if (old_action.sa_handler != SIG_IGN) {
         sigaction (SIGINT, &new_action, NULL);
     }

     // receive and treat requests
     while (0 == do_exit)
     {
	  sd_client = accept(sd_server, (struct sockaddr *)&address,  (socklen_t*)&addrlen) ;
	  if (sd_client <= 0)
	  {
		perror("accept");
		exit(-1);
	  }

          tratar_peticion(sd_client) ;
     }

     // end
     ret = close(sd_server) ;
     if (ret < 0) {
	 perror("close: ") ;
     }

     printf("The End.\n") ;
     return 0 ;
}

