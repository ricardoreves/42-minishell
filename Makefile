# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 01:47:02 by rpinto-r          #+#    #+#              #
#    Updated: 2022/03/01 22:47:15 by rpinto-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### VARIABLES ###
CC         = gcc
WARN_FLAG  = -Werror -Wextra -Wall
RM         = rm -rf
NORM       = norminette
NAME       = minishell
INC        = ./incs
SRC_DIR    = ./srcs
SRC_NAME   = main.c builtin.c command.c error.c signal.c parsing.c parsing_sanitize.c parsing_utils.c redirect.c free.c pipe.c pids.c
SRC_NAME  += utils/array_utils.c utils/env_utils.c utils/env_utils2.c utils/utils.c utils/cmd_utils.c
SRC_NAME  += builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c builtins/pwd.c builtins/unset.c
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
LIBFT_A    = ./libft/libft.a

LIBPARSER_INC = ./parser/inc
LIBPARSER_FLAG = -lparser
LIBPARSER_DIR  = ./parser
LIBPARSER  = ./parser/libparser.a

### RULES ###
all: $(NAME)

.c.o:
	$(CC) -I $(INC) -I $(LIBRL_INC) -I $(LIBFT_INC) -I $(LIBPARSER_INC) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBPARSER_DIR)
	$(CC) $(OBJS) $(DEBUG_FLAG) $(LIBRL_FLAG) $(LIBPARSER_FLAG) $(LIBFT_FLAG) -L $(LIBPARSER_DIR) -L $(LIBFT_DIR) -L $(LIBRL_DIR) -o $(NAME) 

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBPARSER_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(LIBPARSER_DIR) fclean
	$(RM) $(NAME)

re: fclean all

run:
	./$(NAME)

norm:
	$(NORM)

dev: re all run

sandbox:
	$(CC) sandbox/pipe_unlimited.c  -I $(INC) $(LIBFT_A) $(LIBPARSER) -o $(NAME) && ./$(NAME) hello world

fd:
	ls -la /proc/$$$/fd

.PHONY: all clean fclean re sandbox
