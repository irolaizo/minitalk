# Minitalk

## Introducción

Ante todo, hay que entender que Minitalk es un programa que permite que dos programas diferentes se comuniquen entre sí mediante la terminal. Esto significa que se envían señales entre ellos.

Para comprender cómo realizar este programa, lo abordaremos paso a paso, comenzando por cómo nombraremos a los programas: `server.c` y `client.c`.

El subject indica que podemos hacer uso de las siguientes funciones: `write`, `ft_printf` y cualquier equivalente que **tú** hayas programado, `signal`, `sigemptyset`, `sigaddset`, `sigaction`, `kill`, `getpid`, `malloc`, `free`, `pause`, `sleep`, `usleep`, y `exit`.

## Desarrollo del Server

### Este será el `main` del servidor:

```c
int main (void)
{
    struct sigaction signal_action;
    sigset_t         signal_set;

    printf("This is your server PID: %d\n", getpid());
    sigemptyset(&signal_set);
    sigaddset(&signal_set, SIGUSR1);
    sigaddset(&signal_set, SIGUSR2);
    signal_action.sa_handler = signal_handler;
    signal_action.sa_mask = signal_set;
    signal_action.sa_flags = 0;
    sigaction(SIGUSR1, &signal_action, NULL);
    sigaction(SIGUSR2, &signal_action, NULL);
    while (1)
        pause();
    return (0);
}
Este es el programa que recibirá los mensajes y los imprimirá en la terminal. Empezaremos por crear un main y comprender la función pause. Esta función tiene como objetivo pausar el programa hasta recibir una señal. Tendremos que ponerla en un bucle infinito while (1) porque no queremos que nuestras terminales dejen de comunicarse entre sí.
Obtención del PID

El subject menciona que habrá que proporcionarle al client el número PID (Process Identity) para poder enviar mensajes de una terminal a otra. Por lo tanto, será necesario obtener el PID del servidor con la función getpid().
Uso de sigaction

Tras obtener el PID, que lo sacaremos con un printf, para poder enviar señales utilizaremos la estructura sigaction. En este caso, hemos denominado esta estructura signal_action. A continuación, hemos hecho lo siguiente:

    Hemos vaciado el sigset_t con la función sigemptyset(&signal_set). Esta función recibe la dirección de memoria del sigset_t (&).

    Luego, lo hemos rellenado añadiendo las señales mediante la función sigaddset(&signal_set, SIGUSR1), que recibe la dirección de memoria del sigset_t, y la señal que queremos que reciba.

    A continuación, hemos empezado a estructurar los datos:
        signal_action.sa_handler = signal_handler; donde signal_handler será el nombre de una función que crearemos específicamente para manejar las señales.
        signal_action.sa_mask = signal_set; le damos a sa_mask el valor de la variable signal_set que ya creamos.
        signal_action.sa_flags = 0; asignamos 0 al campo sa_flags.

Función sigaction

Necesitamos entender la función sigaction, cuyo objetivo es gestionar las señales. Recibe tres parámetros: número de señal, la estructura sigaction, y un NULL.
sigaction(SIGUSR1, &signal_action, NULL);
sigaction(SIGUSR2, &signal_action, NULL);
Preparación para el Cliente

Al llegar a este punto, deberemos prestar atención al client. Este es el programa que enviará el mensaje para que el server lo reciba y lo imprima.
