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

NAME = philo_bonus
SRCS = main.c utility.c thread.c message.c
FLAG = -Wall -Werror -Wextra -pthread

$(NAME):
		gcc $(FLAG) $(SRCS) -o $(NAME)

re: clean $(NAME)

all: $(NAME)
	
clean:
		rm -f $(NAME)

fclean: clean

