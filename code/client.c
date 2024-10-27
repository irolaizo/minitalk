/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irolaizo <irolaizo@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:03:44 by irolaizo          #+#    #+#             */
/*   Updated: 2024/08/11 17:03:44 by irolaizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

// Function to send each character bit by bit to the server
void send_character(pid_t server_pid, char character)
{
	for (int i = 0; i < 8; i++) {
		if ((character >> i) & 1)
			kill(server_pid, SIGUSR2); // Send SIGUSR2 for bit "1"
		else
			kill(server_pid, SIGUSR1); // Send SIGUSR1 for bit "0"
		usleep(100); // Small delay to ensure the server has time to process the signal
	}
}

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

	// Optionally, send a null character to signal the end of the message
	send_character(server_pid, '\0');

	return 0;
}

