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

# SRC = push_swap.c

OBJ = $(SRC:.c=.o)

# OBJ1 = main.o

CHECKER = checker

SORT = push_swap

#NAME = libftprintf.a

#MAIN = main

LIB = libft/libft.a

HEADER = include/push_swap.h

GENERATOR = generator

all: $(LIB) $(CHECKER) $(SORT) $(GENERATOR)

$(LIB):  libft/libft.h
	make -C libft

$(CHECKER): source/checker.c source/code_base.c $(HEADER) $(LIB)
	gcc source/checker.c source/code_base.c $(LIB) -o checker

$(SORT): source/push_swap.c source/code_base.c $(HEADER) $(LIB)
	gcc source/push_swap.c source/code_base.c $(LIB) -o push_swap
	gcc -g source/push_swap.c source/code_base.c $(LIB) -o ps

$(GENERATOR): source/generator.c $(HEADER) $(LIB)
	gcc ./source/generator.c $(LIB) -o generator

#$(NAME): $(OBJ) $(LIB)
#	ar rc $(NAME) $(OBJ) libft/*.o
#	make -C ./pft
#libft/*.o
#$(MAIN): $(NAME) $(OBJ1)
#	gcc -g sources/main.c sources/ft_printf.c -o ft_printf  libftprintf.a
#	gcc sources/main.c -o $(MAIN)  $(NAME)
#	./pft/test f
#-Wall -Wextra -Werror
%.o: source/%.c $(HEADER)
	gcc -c $<
clean:
	make clean -C libft
	rm -rf *.o
fclean: clean
	make fclean -C libft
	rm -rf $(CHECKER) $(SORT) ps
re: fclean all
