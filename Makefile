# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 05:06:00 by lsordo            #+#    #+#              #
#    Updated: 2023/02/15 17:26:18 by lsordo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lexer
NAME_TEST = test
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC_DIR = ./src/
OBJ_DIR = ./obj/
SRC_TEST_DIR = ./src_test/
OBJ_TEST_DIR = ./obj_test/

INC_DIR = -I ./inc -I ./lib/libft
LIBFT= ./lib/libft/libft.a

SRC =	lexer.c \
		main.c \
		utils_lexer_mem.c \
		utils_lexer_tmp.c

SRC_TEST =

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

OBJ_TEST = $(SRC_TEST:%.c=$(OBJ_TEST_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INC_DIR) $^ -o $@

$(OBJ_DIR):
	@mkdir -p ./obj

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_DIR_BONUS) $(LIBFT) $(LIBGNL) $(OBJ_BONUS)
	@$(CC) $(OBJ_BONUS) $(LIBFT) $(LIBGNL) -o $(NAME)

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c
	@$(CC) -c $(CFLAGS) $(INC_DIR) $^ -o $@

$(OBJ_DIR_BONUS):
	@mkdir -p ./obj_bonus

test:

$(NAME_TEST): $(OBJ_TEST_DIR) $(LIBFT) $(OBJ_TEST)
	@$(CC) $(OBJ_TEST) $(LIBFT) $(LIBGNL) -o $(NAME_TEST)

$(OBJ_TEST_DIR)%.o: $(SRC_TEST_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INC_DIR) $^ -o $@

$(OBJ_TEST_DIR):
	@mkdir -p ./obj_test

$(LIBFT):
	@$(MAKE) -C ./lib/libft

clean:
	@rm -rf $(OBJ_TEST_DIR)
	@rm -rf $(OBJ_DIR)
	@make clean -C ./lib/libft

fclean: clean
	@rm -f $(NAME_TEST)
	@rm -f $(NAME)
	@make fclean -C ./lib/libft


re: fclean all

.PHONY: all clean fclean re bonus
