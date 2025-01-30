/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrinkine <mrinkine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:43:08 by mrinkine          #+#    #+#             */
/*   Updated: 2024/02/15 10:43:11 by mrinkine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../libft/libft.h"

void	sendstring(int pid, char *str, int free_itoa)
{
	int	i;
	int	x;

	i = 0;
	while (str[i] != '\0')
	{
		x = 7;
		while (x >= 0)
		{
			if (str[i] >> x & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(200);
			x--;
		}
		i++;
	}
	if (free_itoa)
		free(str);
}

static void	getmessage(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR1)
	{
		ft_printf("Message sent successfully\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	s_sigaction;
	int					len;
	int					pid;
	char				*stringlen;

	if (argc != 3)
		return (1);
	s_sigaction.sa_sigaction = getmessage;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	pid = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);
	stringlen = ft_itoa(len);
	if (!stringlen)
		return (EXIT_FAILURE);
	ft_printf("Sending bonus message to PID: %i\n", pid);
	sendstring(pid, stringlen, 1);
	sendstring(pid, " ", 0);
	sendstring(pid, argv[2], 0);
	sleep(5);
	ft_printf("PID not found\n");
	return (0);
}
