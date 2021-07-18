# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 17:18:01 by nmisfit           #+#    #+#              #
#    Updated: 2021/07/18 16:43:21 by nmisfit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c\
	life_of_philo.c\
	lib_function.c\
	error_handle.c\

OBJ = $(SRC:.c=.o)

NAME = philo

CC = gcc

CFLAG = -Wall -Wextra -Werror -g

LIB = -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(LIB) $(OBJ) -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAG) -c $< -o $@ 

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re