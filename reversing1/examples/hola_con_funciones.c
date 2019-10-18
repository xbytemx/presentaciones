#include <stdio.h>

void imprimir(char *mensaje)
{
    printf(mensaje);
}

int main()
{
    char msg[] ="hola mundo\n";
    imprimir(msg);
}
