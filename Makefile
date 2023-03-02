# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 05:06:00 by lsordo            #+#    #+#              #
#    Updated: 2023/03/02 18:20:11 by lsordo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = executor
NAME_TEST = test
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC_DIR = ./srcs/
OBJ_DIR = ./obj/
SRC_TEST_DIR = ./src_test/
OBJ_TEST_DIR = ./obj_test/

INC_DIR = -I ./includes -I ./lib/libft -I ./lib/get_next_line/include
LIBFT= ./lib/libft/libft.a
LIBGNL= ./lib/get_next_line/libgnl.a

SRC =		executor.c\
			lexer.c \
			main.c \
			parser.c \
			prexec.c \
			utils_cleanup.c \
			utils_executor.c \
			utils_init.c \
			utils_lexer.c \
			utils_parser_get.c \
			utils_prexec.c \
			utils_tmp.c

SRC_TEST =	main.c

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

OBJ_TEST = $(SRC_TEST:%.c=$(OBJ_TEST_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(LIBGNL) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT) $(LIBGNL) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INC_DIR) $^ -o $@

$(OBJ_DIR):
	@mkdir -p ./obj

test:

$(NAME_TEST): $(OBJ_TEST_DIR) $(LIBFT) $(LIBGNL) $(OBJ_TEST)
	@$(CC) $(OBJ_TEST) $(LIBFT) $(LIBGNL) -o $(NAME_TEST)

$(OBJ_TEST_DIR)%.o: $(SRC_TEST_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INC_DIR) $^ -o $@

$(OBJ_TEST_DIR):
	@mkdir -p ./obj_test

$(LIBFT):
	@$(MAKE) -C ./lib/libft
$(LIBGNL):
	@$(MAKE) -C ./lib/get_next_line

clean:
	@rm -rf $(OBJ_TEST_DIR)
	@rm -rf $(OBJ_DIR)
	@make clean -C ./lib/libft
	@make clean -C ./lib/get_next_line

fclean: clean
	@rm -f $(NAME_TEST)
	@rm -f $(NAME)
	@make fclean -C ./lib/libft
	@make fclean -C ./lib/get_next_line


re: fclean all

.PHONY: all clean fclean re bonus
