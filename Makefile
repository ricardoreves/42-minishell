# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 01:47:02 by rpinto-r          #+#    #+#              #
#    Updated: 2022/02/06 18:28:30 by rpinto-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILE ###
RM         = rm -rf
CC         = gcc
CFLAGS     = -Werror -Wextra -Wall
CDEBUG     = -g3 -fsanitize=address
READLINE   = -lreadline
LIBFT      = -lft
LIBFT_DIR  = ./libft
LIBFT_NAME = ./libft/libft.a
NORM       = norminette

### FILES ###
NAME       = minishell
INCS_DIR   = ./incs
SRCS_DIR   = ./srcs
SRCS_NAME  = main.c array.c env_utils.c utils.c signal.c
SRCS_NAME  += builtins/echo.c builtins/env.c builtins/export.c builtins/pwd.c builtins/unset.c builtins/cd.c builtins/exit.c
SRCS       = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS       = $(SRCS:.c=.o)

### RULES ###
all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(READLINE) -I $(INCS_DIR) -I /usr/include -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(READLINE) -L $(LIBFT_DIR) $(LIBFT) -o $(NAME) 

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

norm:
	$(NORM)

run:
	./$(NAME)
	
dev:
	$(CC) $(CDEBUG) $(READLINE) -I $(INCS_DIR) $(SRCS) -L $(LIBFT_DIR) $(LIBFT) -o $(NAME) && ./$(NAME)

pipe:
	$(CC) $(CDEBUG) $(READLINE) -I $(INCS_DIR) srcs/sample_pipe_and_redirect.c -L $(LIBFT_DIR) $(LIBFT) -o $(NAME) && ./$(NAME)
	
.PHONY: all clean fclean re
