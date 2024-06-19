
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void signalHandler(int signal)
{
    printf("Se recibe señal %d\n", signal)
}
int main (void)
{
    signal(SIGINT, signalHandler);
    //manejo la señal SIGNIT (Ctrl+C)
    while(1)
    {
        //Something
    }
    return(0);
}
//'signalHandler' imprime el número de señal
// Funcion: signal(SIGINT, signalHandler) configura el manejo de la señal SIGNIT para que llame a la función 'signalHandler'.
// El programa ejecuta un bucle hasta que se reciba la señal SIGINT

int main (void)
{
    sigset_t signalSet;
    sigemptyset(&signalSet);
    return(0);
}
// 'sigemptyset' se usa para inicializar un conjunto de señales
// 'sigemptyset(&signalSet);' inicializa el conjunto de señales vacio
// 




