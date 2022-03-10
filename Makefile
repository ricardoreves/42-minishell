# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 01:47:02 by rpinto-r          #+#    #+#              #
#    Updated: 2022/03/10 02:10:43 by rpinto-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### VARIABLES ###
CC         = gcc
WARN_FLAG  = -Werror -Wextra -Wall
CFLAGS     = $(WARN_FLAG)
RM         = rm -rf
NORM       = norminette
NAME       = minishell
TEST_NAME  = tester
INC        = ./incs
TEST_DIR   = ./tests
SRC_DIR    = ./srcs
SRC_NAME   = main.c command.c error.c signal.c parsing.c parsing_wildcard.c parsing_utils.c redirect.c free.c pipe.c pids.c logfile_utils.c logfile.c command_utils.c prompt.c
SRC_NAME  += utils/array_utils.c utils/array_utils2.c utils/env_utils.c utils/env_utils2.c utils/utils.c utils/cmd_utils.c
SRC_NAME  += builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c builtins/pwd.c builtins/unset.c builtins/builtin.c
SRCS       = $(addprefix $(SRC_DIR)/, $(SRC_NAME))
OBJS       = $(SRCS:.c=.o)

LIBRL_FLAG = -lreadline
ifeq ($(shell uname), Linux)
    LIBRL_DIR  = /usr/lib
    LIBRL_INC  = /usr/include
	DEBUG_FLAG = -g3 -fsanitize=leak
else
	ifneq (,$(wildcard /usr/local/Cellar/readline/8.1.2/include/readline/readline.h))
		LIBRL_DIR  = /usr/local/Cellar/readline/8.1.2/lib
		LIBRL_INC  = /usr/local/Cellar/readline/8.1.2/include	
	else
		LIBRL_DIR  = $(HOME)/.brew/opt/readline/lib
		LIBRL_INC  = $(HOME)/.brew/opt/readline/include
	endif
	DEBUG_FLAG = -g3 -fsanitize=address
endif

LIBFT_FLAG = -lft
LIBFT_DIR  = ./libft
LIBFT_INC  = ./libft
LIBFT    = ./libft/libft.a

LIBPARSER_INC = ./parser/inc
LIBPARSER_FLAG = -lparser
LIBPARSER_DIR  = ./parser
LIBPARSER  = ./parser/libparser.a

LIBFTPRINTF_INC = ./printf/inc
LIBFTPRINTF_FLAG = -lprintf
LIBFTPRINTF_DIR  = ./printf
LIBFTPRINTF  = ./printf/libprintf.a


### RULES ###
all: $(NAME)

.c.o:
	$(CC) -I $(INC) -I $(LIBFT_INC) -I $(LIBRL_INC) -I $(LIBPARSER_INC) -I $(LIBFTPRINTF_INC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBPARSER_DIR)
	$(MAKE) -C $(LIBFTPRINTF_DIR)
	$(CC) $(OBJS) $(DEBUG_FLAG) $(LIBRL_FLAG) $(LIBPARSER_FLAG) $(LIBFT_FLAG) $(LIBFTPRINTF_FLAG) -L $(LIBPARSER_DIR) -L $(LIBFT_DIR) -L $(LIBRL_DIR) -L $(LIBFTPRINTF_DIR) -o $(NAME) 

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBPARSER_DIR) clean
	$(MAKE) -C $(LIBFTPRINTF_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(LIBPARSER_DIR) fclean
	$(MAKE) -C $(LIBFTPRINTF_DIR) fclean
	$(RM) $(NAME)

re: fclean all

run:
	./$(NAME)

norm:
	$(NORM) $(INC) $(SRC_DIR) $(LIBFT_DIR) $(LIBFTPRINTF_DIR) $(LIBPARSER_DIR)

#dev: re all run
dev: CFLAGS += $(DEBUG_FLAG)
dev: $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) dev
	$(MAKE) -C $(LIBPARSER_DIR) dev
	$(MAKE) -C $(LIBFTPRINTF_DIR) dev
	$(CC) $(OBJS) $(DEBUG_FLAG) $(LIBRL_FLAG) $(LIBPARSER_FLAG) $(LIBFT_FLAG) $(LIBFTPRINTF_FLAG) -L $(LIBPARSER_DIR) -L $(LIBFT_DIR) -L $(LIBRL_DIR) -L $(LIBFTPRINTF_DIR) -o $(NAME) 

sandbox:
	$(CC) sandbox/pipe_unlimited.c  -I $(INC) $(LIBFT) $(LIBPARSER) -o $(NAME) && ./$(NAME) hello world

dev2:
	$(CC) sandbox/save_error.c $(DEBUG_FLAG) -I $(INC) $(LIBFT) $(LIBPARSER) -o $(NAME) && ./$(NAME)

fd:
	ls -la /proc/$$$/fd

test: CFLAGS += $(DEBUG_FLAG)
test: $(subst $(SRC_DIR)/main.o, $(TEST_DIR)/minishell_tester.o, $(OBJS))
	$(MAKE) -C $(LIBFT_DIR) dev
	$(MAKE) -C $(LIBPARSER_DIR) dev
	$(MAKE) -C $(LIBFTPRINTF_DIR) dev
	$(CC) $(subst $(SRC_DIR)/main.o, $(TEST_DIR)/minishell_tester.o, $(OBJS)) $(DEBUG_FLAG) $(LIBRL_FLAG) $(LIBPARSER_FLAG) $(LIBFT_FLAG) $(LIBFTPRINTF_FLAG) -L $(LIBPARSER_DIR) -L $(LIBFT_DIR) -L $(LIBRL_DIR) -L $(LIBFTPRINTF_DIR) -o $(TEST_NAME)

valgrind:
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re sandbox
