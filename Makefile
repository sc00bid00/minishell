# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 10:41:06 by kczichow          #+#    #+#              #
#    Updated: 2023/02/27 16:55:34 by kczichow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL			=	/bin/bash
UNAME			=	$(shell uname)
#MAKEFLAGS		=	--no-print-directory
CFLAGS			= -g
# -Wall -Wextra -Werror
# CFLAGS			=	-g -fsanitize=address 
# CFLAGS			=	-Wall -Wextra -Werror #-g #-fsanitize=address 

NAME			=	minishell
NAME_TEST		=	test

# path to directories

SRC_DIR			=	src
OBJ_DIR			=	obj
LIB_DIR			=	lib
INC_DIR			=	inc
SRC_TEST_DIR	= 	src_test
OBJ_TEST_DIR	= 	obj_test

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

SRC				=	temp_kathrin/main	\
					prompt/prompt \
					signals/signals \
					env/env_build \
					env/env_update \
					env/env_transform \
					utils/utils_list \
					utils/utils_error \
					builtin/builtin_pwd \
					builtin/builtin_cd \
					builtin/builtin_env \
					builtin/builtin_echo

SRC_TEST		=	main \
					utils_lexer_mem \
					lexer

INC				=	${NAME}      \
					libft                               
LIB				=	libft
SRC_FILES		=	$(addsuffix .c, $(addprefix $(SRC_DIR)/, $(SRC)))
LIB_FILES		=	$(addsuffix .a, $(addprefix $(LIB_DIR)/$(LIB)/, $(LIB)))
OBJ_FILES		=	$(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(SRC)))
OBJ_TEST_FILES	=	$(addsuffix .o, $(addprefix $(OBJ_TEST_DIR)/, $(SRC_TEST)))
INC_FILES		=	$(addsuffix .h, $(addprefix $(INC_DIR)/, $(INC)))
READLINE		=	/usr/include/readline/readline.h
INCLUDES		=	-I ${INC_DIR}

# link libraries
LINKER			=	-L lib/libft -l ft -l readline

MAC_BREW		=	/Users/${USER}/.brewconfig.zsh
MAC_READLINE	=	~/.brew/opt/readline
MAC_INCLUDES	=	-I $(MAC_READLINE)/include
MAC_LINKER		=	-L $(MAC_READLINE)/lib

all: $(NAME)
$(LIB_FILES):
	# make -j8 -C $(LIB_FILES)
	@$(MAKE) MAKEFLAGS+=-j8 CFLAGS+="$(CFLAGS)" -C lib/libft
	@ar -rc $(LIB_FILES) $$(find ./lib/libft -type f -name '*.o') 
$(OBJ_DIR):
	@mkdir -p $(shell find src -type d | sed \s/src/obj/g)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) $(MAC_INCLUDES) -c $< -o $@

$(OBJ_TEST_DIR):
	@mkdir -p $(shell find src_test -type d | sed \s/src_test/obj_test/g)
$(OBJ_TEST_DIR)/%.o: $(SRC_TEST_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) $(MAC_INCLUDES) -c $< -o $@

# distinguish between Apple and Linux OS

test: $(NAME_TEST)

ifeq ($(UNAME), Darwin)
$(NAME): $(MAC_BREW) $(MAC_READLINE) $(LIB_FILES) $(OBJ_DIR) $(OBJ_FILES)
	@echo -en "\\r       ${BGREEN}$(NAME)${RESET}        ✔  ${BGREEN}./$(NAME)${RESET}${DEL_R}\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(INCLUDES) $(MAC_INCLUDES) $(LINKER) $(MAC_LINKER)
	@rm -f .tmp
$(NAME_TEST): $(MAC_BREW) $(MAC_READLINE) $(LIB_FILES) $(OBJ_TEST_DIR) $(OBJ_TEST_FILES)
	@echo -en "\\r       ${BGREEN}$(NAME_TEST)${RESET}        ✔  ${BGREEN}./$(NAME_TEST)${RESET}${DEL_R}\n"
	@$(CC) $(CFLAGS) -o $(NAME_TEST) $(OBJ_TEST_FILES) $(INCLUDES) $(MAC_INCLUDES) $(LINKER) $(MAC_LINKER)
	@rm -f .tmp	
else    
$(NAME): $(READLINE) $(LIB_FILES) $(OBJ_DIR) $(OBJ_FILES)
	@echo -en "\\r       ${BGREEN}$(NAME)${RESET}        ✔  ${BGREEN}./$(NAME)${RESET}${DEL_R}\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(INCLUDES) $(LINKER)
	@rm -f .tmp
endif

# installing readline

$(READLINE):
	@-if pacman -Sy --noconfirm readline &>/dev/null; then  \
		echo -e "\\rinstall...   readline     ✔  $(GREEN)apt install libreadline-dev$(RESET)\n"; \
	elif apt install -y libreadline-dev &>/dev/null; then \
		echo -e "\\rinstall...   readline     ✔  $(GREEN)pacman -Sy readline$(RESET)\n"; \
    fi
	@sleep 1
	
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

clean:
	@echo -en "cleaning objects...\n";
	@$(MAKE) fclean -C lib/libft
	@if find $(OBJ_DIR) -type f -name '*.o' -delete > /dev/null 2>&1; then        \
	echo -en "\\r$(GREEN)$(OBJ_DIR)/$(RESET)${DEL_R}";\
	fi
	@if find $(OBJ_DIR) -type d -empty -delete > /dev/null 2>&1; then         \
		:;                                                                      \
	fi
fclean: clean #header
	@echo -en "cleanig bins...\n"
	@if find $(LIB_DIR) -type d -empty -delete > /dev/null 2>&1; then         \
		:; \
	fi
	@if [ -f "${NAME}" ]; then                                                    \
		rm -f ${NAME};                                                          \
		echo -e "\\r $(NAME)         $(GREEN)$(NAME)$(RESET)${DEL_R}"; \
	fi

re: fclean all

.PHONY: all clean fclean re bonus