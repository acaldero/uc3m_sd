
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
#include <fcntl.h>
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <signal.h>

#include "lib.h"
#include "lib-mesg.h"


void tratar_peticion ( struct message * pr )
{
     int ret ;
     int qr ;

     switch (pr->op)
     {
         case 1: // INIT
                 pr->status = init(pr->name, pr->value) ;
		 printf(" %d = init(%s, %d);\n",    pr->status, pr->name, pr->value) ;
                 break ;
         case 2: // SET
                 pr->status = set(pr->name, pr->i, pr->value) ;
		 printf(" %d = set(%s, %d, 0x%x);\n", pr->status, pr->name, pr->i, pr->value) ;
                 break ;
         case 3: // GET
                 pr->status = get(pr->name, pr->i, &(pr->value)) ;
		 printf(" %d = get(%s, %d, 0x%x);\n", pr->status, pr->name, pr->i, pr->value) ;
                 break ;
	 default:
		 printf(" unknown(%s, %d, %d);\n", pr->name, pr->i, pr->value) ;
                 break ;
     }

     qr = mq_open(pr->q_name, O_WRONLY) ;
     if (qr < 0) {
	 perror("mq_open: ") ;
         mq_close(qr);
	 return ;
     }

     ret = mq_send(qr, (char *)pr, sizeof(struct message), 0) ;
     if (ret < 0) {
	 perror("mq_send: ") ;
     }

     ret = mq_close(qr);
     if (ret < 0) {
	 perror("mq_close: ") ;
     }
}


char *q_name  = "/SERVIDOR" ;
int   do_exit = 0 ;

void sigHandler ( int signo )
{
     do_exit = 1 ;
}

int main ( int argc, char *argv[] )
{
     int ret ;
     struct message pr ;
     int qs ;
     struct mq_attr attr ;
     unsigned int prio ;
     struct sigaction new_action, old_action;

     // Initialize the queue attributes (attr)
     attr.mq_flags   = 0 ;
     attr.mq_maxmsg  = 10 ;
     attr.mq_msgsize = sizeof(struct message) ;
     attr.mq_curmsgs = 0 ;

     // open server queue
     qs = mq_open(q_name, O_CREAT|O_RDONLY, 0664, &attr) ;
     if (qs < 0) {
	 perror("mq_open: ") ;
	 return -1 ;
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
          ret = mq_receive(qs, (char *)&pr, sizeof(struct message), &prio) ;
          if (ret < 0) {
	      perror("mq_receive: ") ;
	      continue;
          }

          tratar_peticion(&pr) ;
     }

     // end
     ret = mq_close(qs) ;
     if (ret < 0) {
	 perror("mq_close: ") ;
     }

     ret = mq_unlink(q_name);
     if (ret < 0) {
	 perror("mq_unlink: ") ;
     }

     printf("The End.\n") ;
     return 0 ;
}

