# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/25 12:53:25 by marvin            #+#    #+#              #
#    Updated: 2020/03/25 12:53:25 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

SRC_DIR = source/

LEM_IN = lem-in

SRC_LEM_IN = $(addprefix $(SRC_DIR), lemin.c)

OBJ_LEM_IN = $(SRC_LEM_IN:.c=.o)

LIB = libft/libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra  -g

HEADER = include/lemin.h

all: $(LIB) $(LEM_IN)

$(LIB):
	make -C libft/

$(LEM_IN): $(OBJ_LEM_IN) $(LIB)
	$(CC) $^ $(LIB) -o $@

$(OBJ_LEM_IN): $(HEADER)

clean:
	make clean -C libft
	rm -rf source/*.o

fclean: clean
	rm -rf $(LEM_IN) 
#$(LIB)

re: fclean all
