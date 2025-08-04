#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
    char maquina[256];
    int err;

    err = gethostname(maquina, 256);
    if (err < 0) {
        perror("gethostname: ") ;
        return -1;
    }

    printf("Ejecuto en la maquina %s\n", maquina) ;
    return 0 ;
}

