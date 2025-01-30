/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrinkine <mrinkine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:33:39 by mrinkine          #+#    #+#             */
/*   Updated: 2024/02/15 10:34:24 by mrinkine         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	int			len;
	int			pid;
	char		*stringlen;

	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);
	stringlen = ft_itoa(len);
	if (!stringlen)
		return (EXIT_FAILURE);
	ft_printf("Sending to PID: %i\n", pid);
	sendstring(pid, stringlen, 1);
	sendstring(pid, " ", 0);
	sendstring(pid, argv[2], 0);
	return (0);
}
