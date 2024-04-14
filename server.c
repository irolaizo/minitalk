
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <signal.h>

/*1. Definir una función de manejo de señales:
Primero, necesitas definir una función que actuará como el manejador de la señal.
Esta función será llamada cada vez que se reciba la señal específica*/

void signal_handler(int signum)
{
    printf("Se recibió la señal %d\n", signum);
}

/*2. Registrar el manejador de señales:
Luego, debes registrar esta función de manejo de señales utilizando la función signal().
La sintaxis de signal() es la siguiente:*/

void (*signal(int signum, void (*handler)(int)))(int);
{

}

/*Donde:
signum es el número de la señal que se desea manejar.
handler es un puntero a la función que actuará como el manejador de la señal.

Por ejemplo, para registrar signal_handler como el manejador de la señal SIGINT
(la señal enviada cuando se presiona Ctrl+C), puedes hacer lo siguiente:*/

signal(SIGINT, signal_handler);

/*3. Mantener el programa en ejecución:
Finalmente, para mantener el programa en ejecución después de registrar el manejador
de señales, puedes agregar alguna forma de espera, como un bucle infinito o una pausa.
Por ejemplo:*/

while (1)
{

}


/*sigaction es una función en C que se utiliza para establecer el comportamiento de
manejo de señales en un programa. Permite al programa especificar cómo debe manejar
una señal específica cuando ésta es recibida.*/

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
{

}

//signum: Es el número de la señal que se desea manejar.
/*act: Es un puntero a una estructura struct sigaction que especifica
el nuevo comportamiento para la señal signum.*/
/*oldact: Es un puntero a una estructura struct sigaction donde se almacenará
el comportamiento anterior de la señal (opcional).*/
/*sigaction: puedes especificar una función que se llamará cuando se reciba esa
señal particular. Esto es útil para manejar eventos como interrupciones de usuario,
errores de segmentación, y otros eventos importantes que pueden ocurrir durante la
ejecución de un programa.*/

int main()
{
    // Obtenemos el PID del proceso actual
    pid_t pid = getpid();

    // Mostramos el PID en la salida estándar
    printf("El PID del proceso actual es: %d\n", pid);

    return 0;
}