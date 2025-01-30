/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrinkine <mrinkine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:35:35 by mrinkine          #+#    #+#             */
/*   Updated: 2024/02/15 10:35:41 by mrinkine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../libft/libft.h"

int	mini_atoi(char c, int strlen)
{
	strlen = strlen * 10;
	strlen = strlen + (c - 48);
	return (strlen);
}

void	mini_printstring(char *str, int *index, int *strlen, int *havestrlen)
{
	if (*strlen != 0)
	{
		str[*index] = '\0';
		ft_putstr_fd(str, 1);
		free(str);
		str = NULL;
	}
	*havestrlen = 0;
	*strlen = 0;
	*index = 0;
}

static void	buildstring(char c)
{
	static int	havestringlen = 0;
	static int	strlen = 0;
	static int	index = 0;
	static char	*str = NULL;

	if (c == ' ' && havestringlen == 0)
		havestringlen = 1;
	else if (havestringlen == 0)
		strlen = mini_atoi(c, strlen);
	else if (havestringlen == 1 && index == 0 && strlen != 0)
	{
		str = NULL;
		str = malloc(strlen + 1);
		if (!str)
		{
			ft_putstr_fd("Malloc failure", 2);
			exit(EXIT_FAILURE);
		}
		str[index++] = c;
	}
	else if (havestringlen == 1 && index > 0 && c != 0 && strlen != 0)
		str[index++] = c;
	if (index == strlen)
		mini_printstring(str, &index, &strlen, &havestringlen);
}

static void	recivestring(int sig, siginfo_t *info, void *context)
{
	static int		i = 7;
	static char		c = 0;

	(void)context;
	(void)info;
	if (sig == SIGUSR2)
		c |= (1 << i);
	if (--i == -1)
	{
		buildstring(c);
		i = 7;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_printf("Server PID = %i\n", getpid());
	s_sigaction.sa_sigaction = recivestring;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
