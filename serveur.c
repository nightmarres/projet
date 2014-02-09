/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcim <jalcim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 20:33:52 by jalcim            #+#    #+#             */
/*   Updated: 2014/02/09 08:43:22 by jalcim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//unsigned long int ptr = 0;//unsigned int ptr = 0;

void recev_pid1();
void recev_pid2();
void recev_adr1();
void recev_adr2();
void error();
void standby();
void trace(int *flag, int bit);
void reponse(int bit);
//void term();

int main()
{
	int compt;

 	compt = 0;
 	printf("connect\n");


 	signal(SIGUSR1, recev_adr1);
 	signal(SIGUSR2, recev_adr2);
//	signal(SIGINT, term);
//	printf("%lu\n", (sizeof(unsigned long int *) * 8));

	standby();
}

void standby()
{
	sleep(10);
	error();
}

void trace(int *flag, int bit)
{
	if (*flag == 2)
	{
		*flag = 1;
		standby();
	}
	if (*flag == 1)
	{
		*flag = 0;
		reponse(bit);
	}
	if (!(*flag))
		*flag = 2;
	else
		error();
}

void reponse(int bit)
{
	unsigned long int ptr;
	int *pid;

	ptr = (unsigned long int)recev_adr1;
	pid = (int *)ptr; 
	kill(*pid, (bit ? SIGUSR1 : SIGUSR2));
	sleep(1);
	error();
}

void error()
{
	long unsigned int ptr;
	long unsigned int *mask;
	int pid;//a implenter

	kill(pid, SIGUSR2);

/*!*/ptr = (((long unsigned int)recev_adr1) - 762);
	ptr -= 1;//(sizeof(long unsigned int) / 8);
	mask = (long unsigned int *)ptr;
}

void recev_pid1()
{
	static int flag = 1;
	static unsigned int pid;
	static unsigned int mask;
	long unsigned int *ptr;
	int *compt;

	trace(&flag, 1);
/*!*/ptr = (((long unsigned int *)main) - 762);
	compt = (int*)ptr;
	if (!(*compt < (sizeof(unsigned int) * 8)))
		*compt = 0;
	compt++;
}

void recev_pid2()
{
	static int flag = 1;
	long unsigned int *ptr;
	int *compt;

	trace(&flag, 0);
/*!*/ptr = (((long unsigned int *)main) - 762);
	compt = (int*)ptr;
	if (!(*compt < (sizeof(unsigned int) * 8)))
		*compt = 0;
	compt++;	
}

void recev_adr1()
{
	static long unsigned int addr = 0;
	static long unsigned int mask;
	static int flag = 1;
	long unsigned int *ptr;
	int *compt;

//	printf("%lu\n%lu\n", (long unsigned int)fct1, (long unsigned int)&ptr);
	trace(&flag, 1);
/*!*/ptr = (((long unsigned int *)main) - 762);
	compt = (int*)ptr;
	if (!(*compt < (sizeof(unsigned int) * 8)))
		*compt = 0;
	mask = 1;
	mask <<= *compt;
	addr = mask | addr;
	printf("%lu\n", addr);
	*compt++;
	flag = 1;
}

void recev_adr2()
{
	static int flag = 1; // 1 = pas encore passer; 2 = derniere instruction; 0 = en cour de check
	long unsigned int *ptr;
	int *compt;

	trace(&flag, 0);
/*!*/ptr = (((long unsigned int *)main) - 762);
	compt = (int*)ptr;
	if (!(*compt < (sizeof(unsigned int) * 8)))
		*compt = 0;
	*compt++;
}

/*
void term()
{
	long unsigned int *ptr;
	long unsigned int aff;

	ptr = NULL;
	ptr = (long unsigned int *)fct1;
	ptr -= 672;

//	aff = (long unsigned int)(*ptr);
	printf("au final %lu\n", (long unsigned int)*ptr);
	exit(1);
}
*/
