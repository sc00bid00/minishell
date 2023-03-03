# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 05:06:00 by lsordo            #+#    #+#              #
#    Updated: 2023/03/03 08:17:31 by lsordo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME = $(shell uname)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g


#FORMAT----------------------------------#
DEFCL			=	$(shell echo -e "\033[0m")
RED				=	$(shell echo -e "\033[0;31m")
GREEN			=	$(shell echo -e "\033[0;32m")
BGREEN			=	$(shell echo -e "\033[1;32m")
YELLOW			=	$(shell echo -e "\033[0;33m")
BLUE			=	$(shell echo -e "\033[0;34m")
BBLUE			=	$(shell echo -e "\033[1;34m")
PURPLE			=	$(shell echo -e "\033[0;35m")
CYAN			=	$(shell echo -e "\033[0;36m")
BCYAN			=	$(shell echo -e "\033[1;36m")
GRAY			=	$(shell echo -e "\033[0m\033[38;5;239m")
DEL_R			=	\033[K
# ---------------------------------------#

NAME = minishell

SRC_DIR =	./src/
OBJ_DIR =	./obj/
INC_DIR =	-I ./inc \
			-I ./lib/libft \
			-I ./lib/get_next_line/include \
			-I /usr/include/readline

LIBFT= ./lib/libft/libft.a
LIBGNL= ./lib/get_next_line/libgnl.a

SRC =		main.c \
			lexer.c \
			utils_lexer.c \
			parser.c \
			utils_parser.c \
			prexec.c \
			utils_prexec.c \
			executor.c\
			utils_executor.c \
			utils_init.c \
			utils_cleanup.c \
			utils_tmp.c

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(LIBGNL) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT) $(LIBGNL) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INC_DIR) $^ -o $@

$(OBJ_DIR):
	@mkdir -p ./obj

$(LIBFT):
	@$(MAKE) -C ./lib/libft
$(LIBGNL):
	@$(MAKE) -C ./lib/get_next_line

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C ./lib/libft
	@make clean -C ./lib/get_next_line

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./lib/libft
	@make fclean -C ./lib/get_next_line

re: fclean all

.PHONY: all clean fclean re bonus
