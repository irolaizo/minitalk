# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irolaizo <irolaizo@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/11 17:03:36 by irolaizo          #+#    #+#              #
#    Updated: 2024/08/11 17:03:36 by irolaizo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC_SERVER = code/server.c
SRC_CLIENT = code/client.c

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER):
	$(CC) $(CFLAGS) $(SRC_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT):
	$(CC) $(CFLAGS) $(SRC_CLIENT) -o $(NAME_CLIENT)

clean:

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re
