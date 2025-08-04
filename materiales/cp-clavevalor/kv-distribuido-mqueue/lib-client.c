
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
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

#include "lib-client.h"
#include "lib-mesg.h"


int d_send_receive ( struct message *pr )
{
     int  ret ;
     char qr_name[1024] ;
     struct mq_attr attr;
     int qs, qr ;
     unsigned prio ;

     /* Initialize the queue attributes (attr) */
     bzero(&attr, sizeof(struct mq_attr)) ;
     attr.mq_flags   = 0 ;
     attr.mq_maxmsg  = 10 ;
     attr.mq_msgsize = sizeof(struct message) ;
     attr.mq_curmsgs = 0 ;

  // qs = mq_open("/SERVIDOR", O_WRONLY, 0700, &attr) ;
     qs = mq_open("/SERVIDOR", O_WRONLY) ;
     if (qs == -1) {
	 perror("mq_open: ") ;
	 return -1 ;
     }

     sprintf(qr_name, "%s%d", "/CLIENTE_", getpid()) ;
     qr = mq_open(qr_name, O_CREAT|O_RDONLY, 0664, &attr) ;
     if (qr == -1) {
	 perror("mq_open: ") ;
	 mq_close(qs) ;
	 return -1;
     }
     strcpy(pr->q_name, qr_name) ;

     // send request
     ret = mq_send(qs,    (char *)pr, sizeof(struct message), 0) ;
     if (ret < 0) {
	 perror("mq_send: ") ;
	 mq_close(qs) ;
	 mq_close(qr) ;
         mq_unlink(qr_name) ;
	 return -1;
     }

     // receive response
     ret = mq_receive(qr, (char *)pr, sizeof(struct message), &prio) ;
     if (ret < 0) {
	 perror("mq_receive: ") ;
	 mq_close(qs) ;
	 mq_close(qr) ;
         mq_unlink(qr_name) ;
	 return -1;
     }

     // close queues
     ret = mq_close(qs);
     if (ret < 0) {
	 perror("mq_close: ") ;
     }
     ret = mq_close(qr);
     if (ret < 0) {
	 perror("mq_close: ") ;
     }
     ret = mq_unlink(qr_name);
     if (ret < 0) {
	 perror("mq_unlink: ") ;
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

