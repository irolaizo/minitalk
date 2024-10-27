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

#include <unistd.h>
#include <stdio.h>
#include <bits/types/sigset_t.h>
#include <signal.h>
#include <bits/stdint-uintn.h>
#include "server.h"

void send_char(pid_t server_pid, char c)
{
	for (int i = 0; i < 8; i++) {
		if ((c >> i) & 1) {
			kill(server_pid, SIGUSR2); // Send SIGUSR2 for bit "1"
		} else {
			kill(server_pid, SIGUSR1); // Send SIGUSR1 for bit "0"
		}
		usleep(100); // Small delay to ensure signal is received
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

	for (size_t i = 0; i < strlen(message); i++) {
		send_char(server_pid, message[i]);
	}

	return 0;
}

