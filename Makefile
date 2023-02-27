# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 10:41:06 by kczichow          #+#    #+#              #
#    Updated: 2023/02/27 17:51:49 by lsordo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL			=	/bin/bash
UNAME			=	$(shell uname)
#MAKEFLAGS		=	--no-print-directory
#CFLAGS			=	-Wall -Wextra -Werror #-g #-fsanitize=address

NAME			=	minishell

# path to directories

SRC_DIR			=	src
OBJ_DIR			=	obj
LIB_DIR			=	lib
INC_DIR			=	inc

# color codes for command line messages

BOLD	= \033[1m
BLACK	= \033[30;1m
RED		= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

# souce and objects files

SRC				=	lexer/lexer \
					prompt/prompt \

INC				=	${NAME}      \
					libft
LIB				=	libft
SRC_FILES		=	$(addsuffix .c, $(addprefix $(SRC_DIR)/, $(SRC)))
LIB_FILES		=	$(addsuffix .a, $(addprefix $(LIB_DIR)/, $(LIB)))
OBJ_FILES		=	$(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(SRC)))
INC_FILES		=	$(addsuffix .h, $(addprefix $(INC_DIR)/, $(INC)))
READLINE		=	/usr/include/readline/readline.h
INCLUDES		=	-I ${INC_DIR}

# link libraries
LINKER			=	-L lib -l ft -l readline

MAC_BREW		=	/Users/${USER}/.brewconfig.zsh
MAC_READLINE	=	~/.brew/opt/readline
MAC_INCLUDES	=	-I $(MAC_READLINE)/include
MAC_LINKER		=	-L $(MAC_READLINE)/lib

all: $(NAME)
$(LIB_FILES): #header
   # @echo -n "compile..."
   # @touch .tmp
	@$(MAKE) MAKEFLAGS+=-j8 CFLAGS+="$(CFLAGS)" -C lib/libft
	@ar -rc $(LIB_FILES) $$(find ./lib/libft -type f -name '*.o')
$(OBJ_DIR):
	@mkdir -p $(shell find src -type d | sed \s/src/obj/g)
#	mkdir $@
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c #header_c
#	@if [ ! -f .tmp ]; then
#		echo -n "compile...";
#		touch .tmp;
#	fi
#	@echo -en "\\r     ➜  ${BCYAN}$(NAME)${RESET}...    »  $@${DEL_R}"
	@$(CC) $(CFLAGS) $(INCLUDES) $(MAC_INCLUDES) -c $< -o $@

# distinguish between Apple and Linux OS

# ifeq ($(UNAME), Darwin)
$(NAME): $(MAC_BREW) $(MAC_READLINE) $(LIB_FILES) $(OBJ_DIR) $(OBJ_FILES)
#	@echo -en "\\r       ${BGREEN}$(NAME)${RESET}        ✔  ${BGREEN}./$(NAME)${RESET}${DEL_R}\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(INCLUDES) $(MAC_INCLUDES) $(LINKER) $(MAC_LINKER)
#	@rm -f .tmp
#else
#$(NAME): $(READLINE) $(LIB_FILES) $(OBJ_DIR) $(OBJ_FILES)
#    @echo -en "\\r       ${BGREEN}$(NAME)${DEFCL}        ✔  ${BGREEN}./$(NAME)${DEFCL}${DEL_R}\n"
#    @$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(INCLUDES) $(LINKER)
#    @rm -f .tmp
# endif
# $(READLINE):
#     @echo -n "install...     readline     "
#     @-if pacman -Sy --noconfirm readline &>/dev/null; then  \
#         echo -e "\\rinstall...   readline     ✔  $(GREEN)apt install libreadline-dev$(DEFCL)\n"; \
#     elif apt install -y libreadline-dev &>/dev/null; then \
#         echo -e "\\rinstall...   readline     ✔  $(GREEN)pacman -Sy readline$(DEFCL)\n"; \
#     fi
#     @sleep 1

# installing brew

$(MAC_BREW):
	@echo "$(MAGENTA) INSTALLING BREW ... $(RESET)"
	@curl -fsL https://rawgit.com/kube/42homebrew/master/install.sh | zsh;
	@source ~/.zshrc
	@brew install readline
	@echo ""

# installing readline

$(MAC_READLINE):
	@echo "$(MAGENTA) INSTALLING READLINE ...$(RESET)"
	@brew install readline
	@echo ""

# header:
#     @if [ ! -f ".header" ]; then                       \
#         echo    "$(BLUE) MINISHELL ${RESET}";          \
#         echo    "$(BCYAN) by Luca & Kathrin $(RESET)"; \
#         echo    "";                                    \
#         touch .header;                                 \
#     fi
clean: #header
#	@rm -f .header
	@echo -en "cleaning objects...\n";
	@$(MAKE) clean -C lib/libft
	@if find $(OBJ_DIR) -type f -name '*.o' -delete > /dev/null 2>&1; then        \
	echo -en "\\r$(GREEN)$(OBJ_DIR)/$(RESET)${DEL_R}";\
	fi
#	@echo -e "\n";
	@if find $(OBJ_DIR) -type d -empty -delete > /dev/null 2>&1; then         \
		:;                                                                      \
	fi
fclean: clean #header
	@echo -en "cleanig bins...\n"
	@$(MAKE) fclean -C lib/libft
	@if find $(LIB_DIR) -type d -empty -delete > /dev/null 2>&1; then         \
		:; \
	fi
	@if [ -f "${NAME}" ]; then                                                    \
		rm -f ${NAME};                                                          \
		echo -e "\\r $(NAME)         $(GREEN)$(NAME)$(RESET)${DEL_R}"; \
	fi

# header_c:
#     @rm -f .header
re: fclean all
# .INTERMEDIATE: header header_c
.PHONY: all clean fclean re bonus
