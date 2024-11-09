/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irolaizo <irolaizo@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:03:36 by irolaizo          #+#    #+#             */
/*   Updated: 2024/11/09 16:48:49 by irolaizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"

void	signal_received(int signal)
{
	static	size_t	i = 0;
	static	size_t byte = 0;

	if (signal == SIGUSR1)
		byte = byte << 1;
	else if (signal == SIGUSR2)
		byte = (byte << 1) | 1;
	i++;
	if (i == 8)
	{
		ft_printf("%c", (char)byte);
		i = 0;
		byte = 0;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 1 || av[1])
	{
		ft_printf("Please dont put any argument\n");
		return (1);
	}
	pid = getpid();
	if (pid == -1)
	{
		ft_printf("Error getting pid\n");
		return (1);
	}
	ft_printf("pid: %d\n", pid);
	signal(SIGUSR1, signal_received);
	signal(SIGUSR2, signal_received);
	while (1)
	{
		pause();
	}
	return (0);
}