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

NAME = lem-in

CC = gcc 
FLAGS = -Wextra -Wall -Werror -g
LIBRARIES = -lm -lft -L$(LIBFT_DIRECTORY)

INCLUDES = -I $(LIBFT_HEADERS_DIRECTORY) -I $(HEADERS_DIRECTORY) 

# LIBFT
LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = libft/
LIBFT_HEADERS_DIRECTORY = $(LIBFT_DIRECTORY)/

# LEM-IN
HEADERS_LIST = lemin.h get_next_line.h
HEADERS_DIRECTORY = include/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = source/
SOURCES_LIST = list.c hash_map.c init_values.c \
free_functions.c rooms.c links.c other_parsing_funcs.c \
get_next_line.c print_ant_farm.c print_solution.c \
flow_distribution.c ft_strtol.c close_program.c\
route_map.c connect_room.c recursive_search.c bhandari_search.c \
dijkstra_search.c routes_sift.c route_flow.c \
main.c

SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS) $(LIBFT)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) $(LIBRARIES) -o $(NAME)
	echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	echo "$(NAME): $(NAME) was created"

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)
	echo "$(NAME): $(OBJECTS_DIRECTORY) was created"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	echo "$(NAME): $(GREEN)Creating $(LIBFT)"
	$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	rm -rf $(OBJECTS_DIRECTORY)
	echo "$(NAME): $(OBJECTS_DIRECTORY) was deleted"
	@echo "$(NAME): object files were deleted"

fclean: clean
	rm -f $(LIBFT)
	echo "$(NAME): $(LIBFT) was deleted"
	rm -f $(NAME)
	echo "$(NAME): $(NAME) was deleted"

re:
	$(MAKE) fclean
	$(MAKE) all
