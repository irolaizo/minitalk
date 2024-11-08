/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irolaizo <irolaizo@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:03:36 by irolaizo          #+#    #+#             */
/*   Updated: 2024/11/08 10:41:35 by irolaizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int bit;

// Signal handler function
static void	get_signal(int signal)
{
	if (signal == SIGUSR1)
		bit = 0;
	else if (signal == SIGUSR2)
		bit = 1;
}

void handle_signal()
{
	static int				i = 0;
	static unsigned char	c = 0;

	pause();
	c |= (bit << i);
	i ++;
	if (i == 8)
	{
		write(1, &c, 1);
		c = 0;
		i = 0;
	}
}

int main(void)
{
	printf("Server PID: %d\n", getpid());

	signal(SIGUSR1, get_signal);
	signal(SIGUSR2, get_signal);

	while (1)
		handle_signal();
}

