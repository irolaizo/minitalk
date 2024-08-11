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
#include <bits/types/sigset_t.h>
#include <signal.h>
#include <bits/stdint-uintn.h>

void	signal_handler(int signal)
{

}

int	main(void)
{
	struct sigaction	signal_action;
	sigset_t			signal_set;

	printf("This is your server PID: %d\n", getpid());
	sigemptyset (&signal_action);
	sigaddset (&signal_action, SIGUSR1);
	sigaddset (&signal_action, SIGUSR2);
	signal_action.sa_handler = signal_handler;
	signal_action.sa_mask = signal_set;
	signal_action.sa_flags = 0;
	sigaction (SIGUSR1, &signal_action, NULL);
	sigaction (SIGUSR2, &signal_action, NULL);
	while (1)
		pause ();
	return (0);
}

