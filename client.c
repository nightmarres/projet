/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcim <jalcim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 20:33:04 by jalcim            #+#    #+#             */
/*   Updated: 2014/02/09 08:16:48 by jalcim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void fct1();
void check(int bit);
void ok(int bit);
void error();
void send_pid(unsigned int pid);
void send_addr(int pid);

int main()
{
	int pid;

	pid = fork();
	if (!pid)
		execve("./serveur", NULL, NULL);

	signal(SIGUSR1, fct1);
	signal(SIGUSR2, error);

	sleep(1);
	send_pid((unsigned int)pid);
	send_addr(pid);
	kill(pid, SIGINT);

	return (0);
}

void send_pid(unsigned int pid)
{
	unsigned int mask;
	int compt;

	pid = getpid();
	mask = 1;
	compt = -1;
	while (compt < (sizeof(unsigned int) * 8))
	{
		kill(pid, (mask & pid ? SIGUSR1 : SIGUSR2));
		check(mask & pid ? SIGUSR1 : SIGUSR2);
	}
}

void send_addr(int pid)
{
	static int flag;
	char *string;
	long unsigned int send;
	long unsigned int mask;
	int compt = 0;

	printf("moi j'y vais\n");
	string = (char *)malloc(20);
	bzero(string, 20);
	strncpy(string, "coucou\0", 7);
	send = (long unsigned int)string;
	printf("%lu\n", (long unsigned int)string);
	printf("%lu\n", send);
	mask = 1;
	while (compt < (sizeof(char *) * 8))
	{
		kill(pid, (mask & send ? SIGUSR1 : SIGUSR2));
		flag = (mask & send ? SIGUSR1 : SIGUSR2);
		check((mask & send ? 1 : 0));
	}
	sleep(5);
}

void check(int bit)
{
	sleep(10);
	error();
}

void ok(int bit)
{
	long unsigned int ptr;
	long unsigned int *mask;
	int *compt;
	int *pid;

/*!*/ptr = (((long unsigned int)send_addr) - 1520);
	mask = (long unsigned int *)ptr;
	*mask <<= 1;
/*!*/ptr = (((long unsigned int)send_pid) - 762);
	compt = (int *)ptr;
	*compt++;
/*!*/ptr = (((long unsigned int)main) - 762);
	pid = (int *)ptr;
	kill(*pid, (bit ? SIGUSR1 : SIGUSR2));
}

void fct1()
{
	long unsigned int ptr;
	int *flag;

/*!*/ptr = (((long unsigned int)send_addr) - 762);
	flag = (int *)ptr;
	if (flag)
		ok(1);
}

void fct2()
{
	long unsigned int ptr;
	int *flag;

/*!*/ptr = (((long unsigned int)send_addr) - 762);
	flag = (int *)ptr;
	if (!flag)
		ok(0);
}

void error()
{

}
