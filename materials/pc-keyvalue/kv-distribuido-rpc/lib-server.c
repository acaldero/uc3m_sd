
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

#include "lib.h"
#include "message.h"


bool_t d_init_1_svc ( char *name, int N, int *result, struct svc_req *rqstp )
{
	bool_t ret ;

	ret = TRUE ;
        *result = init(name, N) ;

	return ret ;
}

bool_t d_set_1_svc ( char *name, int i, int value, int *result, struct svc_req *rqstp)
{
	bool_t ret ;

	ret = TRUE ;
        *result = set(name, i, value) ;

	return ret ;
}

bool_t d_get_1_svc ( char *name, int i, struct get_res *result, struct svc_req *rqstp )
{
	bool_t ret ;

	ret = TRUE ;
        result->status = get(name, i, &(result->value)) ;

	return ret ;
}

int nanodt_1_freeresult ( SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result )
{
	bool_t ret ;

	ret = TRUE ;
        xdr_free(xdr_result, result) ;

	return ret ;
}

