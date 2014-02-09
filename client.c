/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcim <jalcim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 20:33:04 by jalcim            #+#    #+#             */
/*   Updated: 2014/02/09 19:17:50 by jalcim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "client.h"

char	*g_arg[2];
void	ft_new_kill();
void	ft_first_kill();
void	ft_define_global(char *av, char *pid);



int main(int ac, char **av)
{
	int pid;

	//if (ac != 2)
	//	ft_error_ac(ac);

	pid = ft_atoi(av[1]);

	signal(SIGUSR1, ft_new_kill);
	//signal(SIGUSR2, brainfuck);

	sleep(1);
	ft_define_global(av[2], av[1]);
	ft_first_kill();

	return (0);
}

void	ft_first_kill()
{
	int		pid;
	unsigned int	mask;
	unsigned char	letter;

	pid = ft_atoi(g_arg[0]);
	mask = 1;
	letter = (unsigned char)g_arg[1][0];
	kill(pid, (mask & letter ? SIGUSR1 : SIGUSR2));
	sleep(10);
}

void	ft_new_kill()
{
	static int		i = 0;
	int		pid;
	static unsigned int	mask = 1;
	unsigned char	letter;
	static int		compt = 0;

	pid = ft_atoi(g_arg[0]);
	mask <<= 1;
	if (compt == sizeof(char) * 8)
	{
		compt = 0;
		if (g_arg[0][i] == '\0')
			exit(1);
		i = i + 1;
	}
	else
		compt = compt + 1;
	letter = (unsigned char)g_arg[1][i];
	kill(pid, (mask & letter ? SIGUSR1 : SIGUSR2));
	sleep(10);
}

void	ft_define_global(char *av, char *pid)
{
	g_arg[0] = (char *)malloc(sizeof(char) * (ft_strlen(pid) + 1));
	g_arg[0] = ft_strcpy(g_arg[0], pid);
	g_arg[1] = (char *)malloc(sizeof(char) * (ft_strlen(av) + 1));
	g_arg[1] = ft_strcpy(g_arg[1], av);
}
