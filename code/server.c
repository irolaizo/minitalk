/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irolaizo <irolaizo@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:03:36 by irolaizo          #+#    #+#             */
/*   Updated: 2024/08/11 17:03:36 by irolaizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>

// Global variables to accumulate incoming bits and build characters
volatile sig_atomic_t current_char = 0;  // Current character being constructed
volatile sig_atomic_t bit_position = 0;  // Current bit position (0-7)

// Function to handle incoming signals
void signal_handler(int signal)
{
	// Check which signal was received and set the corresponding bit in `current_char`
	if (signal == SIGUSR1)
	{
		// SIGUSR1 represents bit "0" (do nothing, default bit is 0)
	}
	else if (signal == SIGUSR2)
	{
		// SIGUSR2 represents bit "1", set the corresponding bit in `current_char`
		current_char |= (1 << bit_position);
	}

	// Move to the next bit position
	bit_position++;

	// If we have received all 8 bits, we have a complete character
	if (bit_position == 8)
	{
		// Print the received character
		write(1, &current_char, 1);  // Using write for simplicity and safety inside a signal handler

		// Reset for the next character
		current_char = 0;
		bit_position = 0;
	}
}
int main(void)
{
	struct sigaction signal_action;  // Struct to specify the action to be associated with a specific signal.
	sigset_t signal_set;             // Set of signals to be blocked during the execution of the signal handler.

	// Print the server PID so that the client knows where to send signals.
	printf("This is your server PID: %d\n", getpid());

	// Initialize the signal set to empty and check for errors.
	if (sigemptyset(&signal_set) == -1) {
		perror("Failed to initialize signal set");
		return 1;
	}

	// Add SIGUSR1 and SIGUSR2 to the signal set.
	if (sigaddset(&signal_set, SIGUSR1) == -1) {
		perror("Failed to add SIGUSR1 to signal set");
		return 1;
	}
	if (sigaddset(&signal_set, SIGUSR2) == -1) {
		perror("Failed to add SIGUSR2 to signal set");
		return 1;
	}

	// Set up the signal handler details.
	signal_action.sa_handler = signal_handler;  // Function to call when the signal is received.
	signal_action.sa_mask = signal_set;         // Signals to be blocked during the execution of the handler.
	signal_action.sa_flags = SA_RESTART;        // Automatically restart certain system calls if interrupted by a signal.

	// Register the signal handlers for SIGUSR1 and SIGUSR2.
	if (sigaction(SIGUSR1, &signal_action, NULL) == -1) {
		perror("Failed to register SIGUSR1 handler");
		return 1;
	}
	if (sigaction(SIGUSR2, &signal_action, NULL) == -1) {
		perror("Failed to register SIGUSR2 handler");
		return 1;
	}

	// Keep the server running indefinitely, waiting for signals.
	while (1) {
		sigsuspend(&signal_set);  // Suspend the process until a signal is received, with better control over signal reception.
	}

	return (0);
}