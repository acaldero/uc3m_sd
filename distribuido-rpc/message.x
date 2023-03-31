
struct get_res 
{
  int value ;
  int status ;
} ;

program NANODT
{

	version NANODT_VERSION
        {
		int            d_init ( string name, int N )            = 1 ;
		int            d_set  ( string name, int i, int value ) = 2 ;
		struct get_res d_get  ( string name, int i )            = 3 ;
	}=1 ;

}=55555 ;
