# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 05:06:00 by lsordo            #+#    #+#              #
#    Updated: 2023/04/04 14:13:39 by lsordo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME = $(shell uname)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

#COLORS-----------------------------------------------------------------------#
BRED	=	\033[1;31m
BGREEN	=	\033[1;32m
BYELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
WHITE	=	\033[0m
#-----------------------------------------------------------------------------#

COLOR_MAKE = $(BGREEN)
COLOR_INSTALL = $(BYELLOW)
COLOR_CLEAN = $(BRED)

NAME = minishell

SRC_DIR =	./src/
OBJ_DIR =	./obj/
INC_DIR =	-I ./inc \
			-I ./lib/libft \
			-I ./lib/get_next_line/include

LIBFT= ./lib/libft/libft.a
LIBGNL= ./lib/get_next_line/libgnl.a

SRC =		builtin.c \
			builtin_cd.c \
			builtin_echo.c \
			builtin_echo_2.c \
			builtin_echo_3.c \
			builtin_echo_4.c \
			builtin_echo_5.c \
			builtin_env.c \
			builtin_exit.c \
			builtin_export.c \
			builtin_pwd.c \
			builtin_unset.c \
			env_build.c \
			env_update.c \
			executor.c\
			executor_2.c \
			lexer.c \
			lexer_2.c \
			minishell.c \
			parser.c \
			prexec_2.c \
			prexec.c \
			prompt.c \
			signals.c \
			utils_cleanup.c \
			utils_error.c \
			utils_executor_2.c \
			utils_executor.c \
			utils_expand.c \
			utils_init.c \
			utils_lexer.c \
			utils_lexer_2.c \
			utils_libhelper.c \
			utils_list.c \
			utils_parser.c \
			utils_prexec.c \
			utils_prexechelp.c \
			utils_redsyntax.c \
			utils_tmp_2.c \
			utils_tmp.c

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

# link libraries
LINKER			=	-l readline -L lib/libft -l ft -L lib/get_next_line -l gnl

MAC_BREW		=	/Users/${USER}/.brewconfig.zsh
MAC_READLINE	=	~/.brew/opt/readline
MAC_INCLUDES	=	-I $(MAC_READLINE)/include
MAC_LINKER		=	-L $(MAC_READLINE)/lib

all: $(NAME)

ifeq ($(UNAME), Darwin)
$(NAME): $(MAC_BREW) $(MAC_READLINE) $(OBJ_DIR) $(LIBFT) $(LIBGNL) $(OBJ)
	@echo "$(COLOR_MAKE)Make minishell for Darwin...$(DEFCL)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MAC_LINKER) $(LINKER)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INC_DIR) $(MAC_INCLUDES) -c $^ -o $@
else
$(NAME): $(READLINE) $(OBJ_DIR) $(LIBFT) $(LIBGNL) $(OBJ)
	@echo "$(COLOR_MAKE)Make minishell for Linux...$(DEFCL)"
	@$(CC) $(OBJ) $(LINKER) -o $(NAME)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INC_DIR) $^ -o $@
endif

$(OBJ_DIR):
	@mkdir -p ./obj

$(LIBFT):
	@echo "$(COLOR_MAKE)Make libft...$(DEFCL)"
	@$(MAKE) -s -C ./lib/libft
$(LIBGNL):
	@echo "$(COLOR_MAKE)Make libgnl...$(DEFCL)"
	@$(MAKE) -s -C ./lib/get_next_line

$(READLINE):
	@echo -n "install...	  readline	   "
	@-if pacman -Sy --noconfirm readline &>/dev/null; then  \
		echo -e "\\rinstall...	  readline	   ✔  $(COLOR_INSTALL)apt install libreadline-dev$(DEFCL)\n"; \
	elif apt install -y libreadline-dev &>/dev/null; then \
		echo -e "\\rinstall...	  readline	   ✔  $(COLOR_INSTALL)pacman -Sy readline$(DEFCL)\n"; \
	fi
	@sleep 1

$(MAC_BREW):
	@echo "${COLOR_INSTALL}installing brew...${DEFCL}"
	@curl -fsL https://rawgit.com/kube/42homebrew/master/install.sh | zsh;
	@source ~/.zshrc
	@brew install readline
	@echo ""

$(MAC_READLINE):
	@echo "${COLOR_INSTALL}installing readline...${DEFCL}"
	@brew install readline
	@echo ""

clean:
	@echo "$(BRED)Clean objects...$(DEFCL)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BRED)Clean libft...$(DEFCL)"
	@make clean -s -C ./lib/libft
	@echo "$(BRED)Clean libgnl...$(DEFCL)"
	@make clean -s -C ./lib/get_next_line

fclean: clean
	@echo "$(BRED)Clean exec...$(DEFCL)"
	@rm -f $(NAME)
	@make fclean -s -C ./lib/libft
	@make fclean -s -C ./lib/get_next_line

re: fclean all

.PHONY: all clean fclean re bonus
