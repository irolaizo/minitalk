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
	int				i;
	unsigned char	c;

	i = 0;
	while(i < 8)
	{
		pause();
		c |= (bit << i);
		i ++;
	}
	write(1, &c, 1);

int main(void)
{
	printf("Server PID: %d\n", getpid());

	signal(SIGUSR1, get_signal);
	signal(SIGUSR2, get_signal);

	while (1)
		handle_signal();
}