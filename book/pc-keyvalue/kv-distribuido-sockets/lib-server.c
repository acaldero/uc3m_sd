
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

int d_printf ( const char *format, ... )
{
     int n = 0 ;
     va_list ap ;

     va_start(ap, format) ;
     n = vprintf(format, ap) ;
     va_end(ap) ;
     return n ;
}

void tratar_peticion ( int arg )
{
     int ret ;
     int sd_client ;
     struct message pr ;

     sd_client = (int) arg ;
     ret = read(sd_client , &pr, sizeof(struct message)) ; 

     switch (pr.op)
     {
         case 1: // INIT
                 pr.status = init(pr.name, pr.value) ;
                 d_printf(" %d = init(%s, %d);\n",    pr.status, pr.name, pr.value) ;
                 break ;
         case 2: // SET
                 pr.status = set(pr.name, pr.i, pr.value) ;
                 d_printf(" %d = set(%s, %d, 0x%x);\n", pr.status, pr.name, pr.i, pr.value) ;
                 break ;
         case 3: // GET
                 pr.status = get(pr.name, pr.i, &(pr.value)) ;
                 d_printf(" %d = get(%s, %d, 0x%x);\n", pr.status, pr.name, pr.i, pr.value) ;
                 break ;
	 default:
                 d_printf(" unknown(%s, %d, %d);\n", pr.name, pr.i, pr.value) ;
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
     int opt ;
     int addrlen = sizeof(address);

     // open server sockets
     sd_server = socket(AF_INET, SOCK_STREAM, 0) ;
     if (sd_server < 0)
     {
        perror("socket: ");
        exit(-1);
     }

     // socket options...
     opt = 1;
     ret = setsockopt(sd_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) ;
     if (ret < 0)
     {
         perror("setsockopt: ");
         exit(-1);
     }

     // bind + listen
     address.sin_family      = AF_INET ;
     address.sin_addr.s_addr = INADDR_ANY ;
     address.sin_port        = htons(4200) ;

     ret = bind(sd_server, (struct sockaddr *)&address,  sizeof(address)) ;
     if (ret < 0)
     {
         perror("bind: ");
         exit(-1);
     }
     ret = listen(sd_server, 3) ;
     if (ret < 0)
     {
         perror("listen: ") ;
         exit(-1);
     }

     // signal handler
     sigemptyset (&new_action.sa_mask) ;
     new_action.sa_flags = 0 ;
     new_action.sa_handler = sigHandler ;
	
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
