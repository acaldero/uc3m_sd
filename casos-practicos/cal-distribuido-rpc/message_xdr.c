/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "message.h"

bool_t
xdr_result (XDR *xdrs, result *objp)
{
	 if (!xdr_int (xdrs, &objp->value))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->status))
		 return FALSE;

	return TRUE;
}

bool_t
xdr_d_add_1_argument (XDR *xdrs, d_add_1_argument *objp)
{
	 if (!xdr_int (xdrs, &objp->a))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->b))
		 return FALSE;

	return TRUE;
}

bool_t
xdr_d_divide_1_argument (XDR *xdrs, d_divide_1_argument *objp)
{
	 if (!xdr_int (xdrs, &objp->a))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->b))
		 return FALSE;

	return TRUE;
}

