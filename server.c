
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signal_handler(int signal)
{
    printf("We get you %d\n", signal);
    int    be_error;
    be_error = 1;
    if (be_error)
        printf("You are wrong\n")
}

int main (void)
{
    signal(SIGINT, (signal_handler)
    while(1)
    {
    }
    return (0);
    pid_t pid = getpid();
    printf("El PID del proceso actual es: %d\n", pid);
    return 0;
    sigset_t signalSet;
    sigemptyset
}
