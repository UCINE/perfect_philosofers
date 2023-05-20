# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 04:14:24 by lahamoun          #+#    #+#              #
#    Updated: 2023/05/19 08:41:14 by lahamoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.c \
		utils.c \
		philos_routine.c \
		ft_atoi.c \
		ft_error.c \
	
OBJS	=$(SRC:.c=.o)

CC = cc 

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=thread -g

NAME	= philo

RM		= rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS) $(OBJS_B)

fclean : clean
	$(RM) $(NAME) $(NAME_B)

re : fclean all
