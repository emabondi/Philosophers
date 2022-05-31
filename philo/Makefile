# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/25 11:11:59 by ebondi            #+#    #+#              #
#    Updated: 2022/04/25 11:11:59 by ebondi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main.c utility.c thread.c message.c
FLAG = -Wall -Werror -Wextra -pthread #-fsanitize=thread -g3

$(NAME):
		gcc $(FLAG) $(SRCS) -o $(NAME)

re: clean $(NAME)

all: $(NAME)
	
clean:
		rm -f $(NAME)

fclean: clean

