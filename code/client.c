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
void send_message(pid_t server_pid, unsigned char *messege)
{
	int i;

	while (*messege)
	{
		i = -1;
		while (++i < 8)
		{
			if ((*messege >> i) & i)
				kill (server_pid,SIGUSR2);
			else
				kill (server_pid, SIGUSR1);
			usleep(50);
			usleep(50);
		}
		messege ++;
	}
	return (0);

int main(int argc, char **argv)
{
	int server_pid;
	char *message;

	if (argc != 3)
		return (write (2, "Usage: ./client [server_pid] [message]\n", 39), 1);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	return (send_message(server_pid, (unsigned char *)message));
}