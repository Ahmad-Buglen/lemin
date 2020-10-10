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

# .PHONY: all clean fclean re

# SRC_DIR = source/

# LEM_IN = lem-in

# SRC_LEM_IN = $(addprefix $(SRC_DIR), lemin.c)

# OBJ_LEM_IN = $(SRC_LEM_IN:.c=.o)

# LIB = libft/libft.a

# CC = gcc

# CFLAGS = -Wall -Werror -Wextra  -g

# HEADER = include/lemin.h

# all: $(LIB) $(LEM_IN)

# $(LIB):
# 	make -C libft/

# $(LEM_IN): $(OBJ_LEM_IN) $(LIB)
# 	$(CC) $^ $(LIB) -o $@

# $(OBJ_LEM_IN): $(HEADER)

# clean:
# 	make clean -C libft
# 	rm -rf source/*.o

# fclean: clean
# 	rm -rf $(LEM_IN) 
# #$(LIB)

# re: fclean all



NAME = lem-in

CC = gcc 
FLAGS = -g
#-Wextra -Wall -Werror -g
LIBRARIES = -lm -lft -L$(LIBFT_DIRECTORY)
#VIS_LIBRARIES = -lmlx -lm -L$(MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit

INCLUDES = -I $(LIBFT_HEADERS_DIRECTORY) -I $(HEADERS_DIRECTORY) 

# LIBFT
LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = libft/
LIBFT_HEADERS_DIRECTORY = $(LIBFT_DIRECTORY)/

# MINILIBX
#MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
#MINILIBX_DIRECTORY = ./minilibx_macos/
#MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

# LEM-IN

HEADERS_LIST = lemin.h get_next_line.h
HEADERS_DIRECTORY = include/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = source/
SOURCES_LIST = list.c main.c hash_map.c init_values.c print_functions.c \
free_functions.c rooms.c links.c other_parsing_funcs.c \
lemin.c get_next_line.c init_test.c print_ant_farm.c print_solution.c \
flow_distribution.c
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS) $(LIBFT)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) $(LIBRARIES) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

#$(MINILIBX):
#	@echo "MINILIBX: $(GREEN)Creating $(MINILIBX)$(RESET)"
#	@$(MAKE) -sC $(MINILIBX_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
#	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
#	@rm -f $(MINILIBX)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
