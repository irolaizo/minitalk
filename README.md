Minitalk

Introducción

Ante todo, hay que entender que Minitalk es un programa que permite que dos programas diferentes se comuniquen entre sí mediante la terminal. Esto significa que se envían señales entre ellos.

Para comprender cómo realizar este programa, lo abordaremos paso a paso, comenzando por cómo nombraremos a los programas: server.c y client.c.

El subject indica que podemos hacer uso de las siguientes funciones: write, ft_printf y cualquier equivalente que tú hayas programado, signal, sigemptyset, sigaddset, sigaction, kill, getpid, malloc, free, pause, sleep, usleep, y exit.

Desarrollo del Server

Este es el programa que recibirá los mensajes y los imprimirá en la terminal. Empezaremos por crear un main y comprender la función pause. Esta función tiene como objetivo pausar el programa hasta recibir una señal. Tendremos que ponerla en un bucle infinito while (1) porque no queremos que nuestras terminales dejen de comunicarse entre sí.

Obtención del PID

El subject menciona que habrá que proporcionarle al cliente el número PID (Process Identity) para poder enviar mensajes de una terminal a otra. Por lo tanto, será necesario obtener el PID del servidor con la función getpid().

Uso de sigaction

Tras obtener el PID, que lo sacaremos con un printf, para poder enviar señales utilizaremos la estructura sigaction. En este caso, hemos denominado esta estructura signal_action. A continuación, hemos hecho lo siguiente:

Hemos vaciado el sigset_t con la función sigemptyset(&signal_set). Esta función recibe la dirección de memoria del sigset_t (&).

Luego, lo hemos rellenado añadiendo las señales mediante la función sigaddset(&signal_set, SIGUSR1), que recibe la dirección de memoria del sigset_t y la señal que queremos que reciba.

A continuación, hemos empezado a estructurar los datos:

signal_action.sa_handler = signal_handler; donde signal_handler será el nombre de una función que crearemos específicamente para manejar las señales.

signal_action.sa_mask = signal_set; le damos a sa_mask el valor de la variable signal_set que ya creamos.

signal_action.sa_flags = 0; asignamos 0 al campo sa_flags.

Función sigaction

Necesitamos entender la función sigaction, cuyo objetivo es gestionar las señales. Recibe tres parámetros: número de señal, la estructura sigaction, y un NULL.

sigaction(SIGUSR1, &signal_action, NULL);
sigaction(SIGUSR2, &signal_action, NULL);

Preparación para el Cliente

Al llegar a este punto, deberemos prestar atención al cliente. Este es el programa que enviará el mensaje para que el servidor lo reciba y lo imprima.

Este será el main del servidor:

int main(void)
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

Desarrollo del Cliente

El cliente es el programa que se encarga de enviar los mensajes al servidor. Para ello, tomará como argumentos el PID del servidor y el mensaje que debe enviarse. Cada bit del mensaje será enviado utilizando señales de UNIX (SIGUSR1 y SIGUSR2).

El cliente debe dividir cada carácter del mensaje en bits y enviarlos uno por uno al servidor, utilizando kill() para enviar señales. La señal SIGUSR1 representa un bit de valor 0, mientras que SIGUSR2 representa un bit de valor 1. Además, es importante añadir una pequeña pausa (usleep()) después de cada señal para garantizar que el servidor tenga tiempo suficiente para procesarlas.

Código del Cliente

int main(int argc, char **argv)
{
if (argc != 3) {
write(2, "Usage: ./client [server_pid] [message]\n", 39);
return 1;
}

    pid_t server_pid = atoi(argv[1]);
    char *message = argv[2];

    // Enviar cada carácter del mensaje al servidor
    for (size_t i = 0; i < strlen(message); i++) {
        send_character(server_pid, message[i]);
    }

    // Enviar un carácter nulo para indicar el final del mensaje
    send_character(server_pid, '\0');

    return 0;
}

Conclusión

Minitalk es un ejercicio interesante que nos permite comprender cómo funcionan las señales en UNIX y cómo se pueden usar para comunicar dos procesos diferentes. La implementación del servidor y el cliente nos ayuda a aprender cómo manejar señales, cómo trabajar con procesos en C y cómo implementar una comunicación básica entre programas.

Minitalk (English Version)

Introduction

First of all, it's important to understand that Minitalk is a program that allows two different programs to communicate with each other via the terminal. This means they send signals between them.

To understand how to create this program, we will approach it step by step, starting with how we will name the programs: server.c and client.c.

The subject indicates that we can use the following functions: write, ft_printf, and any equivalent that you have programmed, signal, sigemptyset, sigaddset, sigaction, kill, getpid, malloc, free, pause, sleep, usleep, and exit.

Server Development

This is the program that will receive messages and print them on the terminal. We will start by creating a main and understanding the pause function. The purpose of this function is to pause the program until a signal is received. We need to put it in an infinite while (1) loop because we do not want our terminals to stop communicating.

Getting the PID

The subject mentions that we need to provide the client with the PID (Process Identity) number to be able to send messages from one terminal to another. Therefore, it will be necessary to obtain the server's PID using the getpid() function.

Using sigaction

After obtaining the PID, which we will print with printf, we will use the sigaction structure to send signals. In this case, we named this structure signal_action. We then proceed as follows:

We cleared the sigset_t using the function sigemptyset(&signal_set). This function takes the memory address of sigset_t (&).

Then, we added signals using the function sigaddset(&signal_set, SIGUSR1), which takes the memory address of sigset_t and the signal we want to receive.

Next, we began structuring the data:

signal_action.sa_handler = signal_handler; where signal_handler will be the name of a function we create specifically to handle the signals.

signal_action.sa_mask = signal_set; we assign the value of signal_set to sa_mask.

signal_action.sa_flags = 0; we assign 0 to the sa_flags field.

sigaction Function

We need to understand the sigaction function, whose purpose is to manage signals. It takes three parameters: signal number, sigaction structure, and NULL.

sigaction(SIGUSR1, &signal_action, NULL);
sigaction(SIGUSR2, &signal_action, NULL);

Preparing for the Client

At this point, we need to focus on the client. This is the program that will send the message for the server to receive and print.

The Server main Function

int main(void)
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

Client Development

The client is the program responsible for sending messages to the server. It takes the server PID and the message to be sent as arguments. Each bit of the message is sent using UNIX signals (SIGUSR1 and SIGUSR2).

The client divides each character of the message into bits and sends them one by one to the server, using kill() to send signals. The signal SIGUSR1 represents a bit value of 0, while SIGUSR2 represents a bit value of 1. Additionally, it is important to add a small pause (usleep()) after each signal to ensure that the server has enough time to process them.

Client Code

int main(int argc, char **argv)
{
if (argc != 3) {
write(2, "Usage: ./client [server_pid] [message]\n", 39);
return 1;
}

    pid_t server_pid = atoi(argv[1]);
    char *message = argv[2];

    // Send each character of the message to the server
    for (size_t i = 0; i < strlen(message); i++) {
        send_character(server_pid, message[i]);
    }

    // Send a null character to signal the end of the message
    send_character(server_pid, '\0');

    return 0;
}

Conclusion
Minitalk is an interesting exercise that allows us to understand how UNIX signals work and how they can be used to communicate two different processes. Implementing the server and client helps us learn how to handle signals, work with processes in C, and implement basic communication between programs.
