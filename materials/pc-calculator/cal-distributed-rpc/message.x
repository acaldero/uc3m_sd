
struct result 
{
  int value ;
  int status ;
} ;

program CALC
{

	version CALC_VERSION
        {
                struct result  d_add    ( int a, int b ) = 1 ;
                struct result  d_divide ( int a, int b ) = 2 ;
                struct result  d_neg    ( int a )        = 3 ;
	} = 1 ;

} = 55555 ;

