# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/13 17:18:01 by nmisfit           #+#    #+#              #
#    Updated: 2021/07/16 16:04:04 by nmisfit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = *.c
	

OBJ = $(SRC:.c=.o)

NAME = philo

CC = gcc

CFLAG = -g

LIB = -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(LIB) $(OBJ) -o $(NAME)

%.o: %.c 
	$(CC) -c $(CFLAG) -o $@ $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re