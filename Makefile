#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalcim <jalcim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/09 07:40:23 by jalcim            #+#    #+#              #
#    Updated: 2014/02/09 08:43:48 by jalcim           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

all: save
	gcc -o client client.c
	gcc -o serveur serveur.c

re:	save fclean all

fclean: clean
	rm -r client
	rm -r serveur

clean:

save:
	cp client.c old/
	cp serveur.c old/
	cp Makefile old/

exec:
	./client
