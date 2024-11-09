/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irolaizo <irolaizo@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:03:44 by irolaizo          #+#    #+#             */
/*   Updated: 2024/11/09 18:00:20 by irolaizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"

void	sendsignal(int pid, char *string)
{
	int	i;
	int	bit;

	i = 0;
	bit = 8;
	while (string[i] != '\0')
	{
		bit = 8;
		while (--bit >= 0)
		{
			if (((string[i] >> bit) & 1))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(1000);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3)
	{
		ft_printf("Please put the server pid and the sending String\n");
		return (1);
	}
	else
		pid = ft_atoi(av[1]);
	if (pid == 0)
		return (1);
	if (pid )
		sendsignal(pid, av[2]);
	return (0);
}