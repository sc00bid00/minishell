# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 05:06:00 by lsordo            #+#    #+#              #
#    Updated: 2023/04/08 08:14:53 by lsordo           ###   ########.fr        #
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
LSAN= ./lib/LeakSanitizer/liblsan.a
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

LS_LNK_MAC = -L ./lib/LeakSanitizer -llsan -lc++
LS_LNK_LNX = -rdynamic -L<path/to/library> -llsan -ldl -lstdc++
LS_INC = -Wno-gnu-include-next -I lib/LeakSanitizer/include

all: $(NAME)

ifeq ($(UNAME), Darwin)
$(NAME): $(MAC_BREW) $(MAC_READLINE) $(OBJ_DIR) $(LSAN) $(LIBFT) $(LIBGNL) $(OBJ)
	@echo "$(COLOR_MAKE)Make minishell for Darwin...$(DEFCL)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MAC_LINKER) $(LINKER) $(LS_LNK_MAC)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INC_DIR) $(MAC_INCLUDES) $(LS_INC) -c $^ -o $@
else
$(NAME): $(READLINE) $(LSAN) $(OBJ_DIR) $(LIBFT) $(LIBGNL) $(OBJ)
	@echo "$(COLOR_MAKE)Make minishell for Linux...$(DEFCL)"
	@$(CC) $(OBJ) $(LINKER) $(LS_LNK_LNX) -o $(NAME)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INC_DIR) $(LS_INC) $^ -o $@
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

$(LSAN):
	@echo "${COLOR_INSTALL}installing LeakSanitizer...${DEFCL}"
	@if [ ! -d "./lib/LeakSanitizer" ]; then \
		@git clone --recursive https://www.github.com/mhahnFr/LeakSanitizer.git ./lib/LeakSanitizer/; \
	fi;
	@echo "$(COLOR_MAKE)Make LeakSanitizer...$(DEFCL)"
	@$(MAKE) -C ./lib/LeakSanitizer

clean:
	@echo "$(BRED)Clean objects...$(DEFCL)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BRED)Clean libft...$(DEFCL)"
	@make clean -s -C ./lib/libft
	@echo "$(BRED)Clean libgnl...$(DEFCL)"
	@make clean -s -C ./lib/get_next_line
	@echo "$(BRED)Clean LeakSanitizer...$(DEFCL)"
	@make clean -s -C ./lib/LeakSanitizer

fclean: clean
	@echo "$(BRED)Clean exec...$(DEFCL)"
	@rm -f $(NAME)
	@make fclean -s -C ./lib/libft
	@make fclean -s -C ./lib/get_next_line
	@make fclean -s -C ./lib/LeakSanitizer

re: fclean all

.PHONY: all clean fclean re bonus
