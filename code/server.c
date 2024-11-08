/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irolaizo <irolaizo@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:03:36 by irolaizo          #+#    #+#             */
/*   Updated: 2024/11/07 11:12:48 by irolaizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>

// Variables to store incoming bits and build characters
volatile sig_atomic_t current_character = 0;
volatile sig_atomic_t current_bit_index = 0;

// Signal handler function
void handle_signal(int signal)
{
	char c;

	if (signal == SIGUSR2)
		current_character |= (1 << current_bit_index);

	current_bit_index++;

	if (current_bit_index == 8)
	{
		c = (char)current_character;
		write(1, &c, 1);
		current_character = 0;
		current_bit_index = 0;
	}
}

int main(void)
{
	struct sigaction sa;

	// Print server PID
	printf("Server PID: %d\n", getpid());

	// Set up signal handler
	sa.sa_handler = handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	// Wait for signals indefinitely
	while (1)
		pause();

	return 0;
}

