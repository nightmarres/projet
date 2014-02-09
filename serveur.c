/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveurv2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcim <jalcim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 15:27:36 by jalcim            #+#    #+#             */
/*   Updated: 2014/02/09 19:51:53 by jalcim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

typedef struct sigaction t_sig;
//typedef struct siginfo_t t_info;
typedef struct s_data t_data;

struct s_data
{
	char *str;//a malloc et realloc
	int index;
	int compt;
	unsigned char letter;
	unsigned char mask;

	siginfo_t *info;
};

void error(char *error);
void two(t_data *data);
void one(t_data *data);
t_data *recup(t_data *data);
void fct(int value, siginfo_t *info, void *i_dont_understand);
int init(t_sig *rcv_sig1, t_sig *rcv_sig2);
int alloc(t_data **data, t_sig **rcv_sig1, t_sig **rcv_sig2);
void standby(t_data *data);

int main()
{
	static t_data *data;
	t_sig *rcv_sig1;
	t_sig *rcv_sig2;
	int compt;

	printf("%d\n", getpid());
	compt = 0;
	while (alloc(&data, &rcv_sig1, &rcv_sig2))
	{
		printf("error at malloc wait pliz\n");
		if (!(compt < 3))
			main();
		compt++;
	}
	compt = 0;
	while (init(rcv_sig1, rcv_sig2))
	{
		printf("error ar init wait pliz\n");
		if (!(compt < 3))
			main();
		compt++;
	}
	printf("connect");
	standby(data);

	return (0);
}

void standby(t_data *data)
{
	printf("%s\n", data->str);
	sleep(5);
	if (data->info)
	{
		printf("error aucun signal detecter\n");
//		kill(data->info->si_pid, SIGUSR2);
	}
	while (42);
}

int alloc(t_data **data, t_sig **rcv_sig1, t_sig **rcv_sig2)
{
	if (!((*data) = (t_data *)malloc(sizeof(t_data))))
		return (1);
	bzero((*data), sizeof(t_data));
	recup((*data));
	if (!((*data)->str = (char *)malloc(100)))
		return (1);
	if (0 > ((*rcv_sig1) = (t_sig *)malloc(sizeof(t_sig))))
		return (1);
	bzero((*rcv_sig1), sizeof(t_sig));
	if (0 > ((*rcv_sig2) = (t_sig *)malloc(sizeof(t_sig))))
		return (1);
	bzero((*rcv_sig2), sizeof(t_sig));
	(*data)->index = 0;
	return (0);
}

int init(t_sig *rcv_sig1, t_sig *rcv_sig2)
{
	rcv_sig1->sa_sigaction = fct;
	rcv_sig1->sa_flags = SA_SIGINFO;
	rcv_sig1->sa_mask = SA_NODEFER;
	if (sigaction(SIGUSR1, rcv_sig1, NULL))
	{
		printf("error sigaction\n");
		return (1);
	}
	rcv_sig2->sa_sigaction = fct;
	rcv_sig2->sa_flags = SA_SIGINFO;
	rcv_sig2->sa_mask = SA_NODEFER;
	if (sigaction(SIGUSR2, rcv_sig2, NULL))
	{
		printf("error sigaction\n");
		return (1);
	}
	return (0);
}

void fct(int value, siginfo_t *info, __attribute__ ((unused)) void *i_dont_understand)
{
	static t_data *data = NULL;

	if (!data)
		data = recup(NULL);
	data->info = info;
	if (value == SIGUSR1)
		one(data);
	if (value == SIGUSR2)
		two(data);
}

t_data *recup(t_data *data)
{
	static t_data *rdata;
	if (!data)
		return (rdata);
	else
		rdata = data;
	return (NULL);
}

void one(t_data *data)
{
	unsigned char mask;

	if (data->compt >= (int)(sizeof(char) * 8))
	{
		data->compt = 0;
		if (!(data->index < (int)sizeof(*data->str)))
			if (!(realloc(data->str, (sizeof(*data->str) * 2))))
				error("error at realloc");
		data->str[data->index] = data->letter;//malloc et realloc str
		printf("%c\n", data->letter);//tmp
		data->letter = 0;
	}
	mask = 1;
	mask <<= data->compt;
	data->letter |= mask;
	data->compt++;
	kill(data->info->si_pid, SIGUSR1);
	standby(data);
}

void two(t_data *data)
{
	data->compt++;
	kill(data->info->si_pid, SIGUSR1);
	standby(data);
}

void error(char *error)
{
	printf("%s\n", error);
	exit (0);
}
