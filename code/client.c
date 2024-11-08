/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irolaizo <irolaizo@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:03:44 by irolaizo          #+#    #+#             */
/*   Updated: 2024/11/08 11:03:31 by irolaizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10;
		num = num + str[i] - '0';
		i++;
	}
	return (num * sign);
}



// Function to send each character bit by bit to the server
void send_character(pid_t server_pid, char character)
{
	int	i;

	i = 0;
	while (i < 8) {
		if ((character >> i) & 1)
			kill(server_pid, SIGUSR2); // Send SIGUSR2 for bit "1"
		else
			kill(server_pid, SIGUSR1); // Send SIGUSR1 for bit "0"
		usleep(150); // Small delay to ensure the server has time to process the signal
		usleep(150);
		i ++;
	}
}

int main(int argc, char **argv)
{
	int	i;
	i = 0;

	if (argc != 3) {
		write(2, "Usage: ./client [server_pid] [message]\n", 39);
		return 1;
	}

	pid_t server_pid = ft_atoi(argv[1]);
	char *message = argv[2];

	// Send each character of the message to the server
	i = 0;
	while (message[i])
		send_character(server_pid, message[i++]);
	// Optionally, send a null character to signal the end of the message
	send_character(server_pid, '\0');

	return (0);
}

