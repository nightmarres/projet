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

NAME1  = client
NAME2  = serveur

SRC1    = client.c \
		  ft_atoi.c \
		  ft_strcpy.c \
		  ft_strlen.c

SRC2    = serveur.c \

OBJ1		= $(SRC1:.c=.o)
OBJ2		= $(SRC2:.c=.o)
INCL	= .
CMP		= cc
FLAGS	= -Wall -Werror -Wextra

.PHONY: re all clean fclean 

all: $(NAME) $(NAME2)

$(NAME1): $(OBJ1)
	@$(CMP) -o $(NAME) $(FLAGS) $(OBJ1)

$(NAME2): $(OBJ)
	@$(CMP) -o $(NAME) $(FLAGS) $(OBJ)

%.o: %.c
	@$(CMP) -I $(INCL) -o $@ -c $? $(FLAGS)

.PHONY: clean fclean re

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME1)
	@rm -f $(NAME2)

re: fclean all
