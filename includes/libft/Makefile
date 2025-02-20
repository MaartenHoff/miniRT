# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 12:44:41 by adiler            #+#    #+#              #
#    Updated: 2025/02/20 13:10:09 by maahoff          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = $(shell find -type f -name "*.c")

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
