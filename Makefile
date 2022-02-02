# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 01:47:02 by rpinto-r          #+#    #+#              #
#    Updated: 2022/02/02 17:32:10 by rpinto-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILE ###
RM         = rm -rf
CC         = gcc
CFLAGS     = -Werror -Wextra -Wall
CDEBUG     = -g3 -fsanitize=address
CLIBS      = -lreadline
NORM       = norminette

### FILES ###
NAME       = minishell
INCS_DIR   = ./incs
SRCS_DIR   = ./srcs
SRCS_NAME  = main.c utils.c
SRCS       = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS       = $(SRCS:.c=.o)
LIBFT_DIR  = ./libft
LIBFT_A    = $(LIBFT_DIR)/libft.a

### RULES ###
all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I $(INCS_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(CLIBS) -L $(LIBFT_DIR) -lft -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	$(NORM)
	
dev:
	$(CC) $(CDEBUG) $(CLIBS) -I $(INCS_DIR) srcs/main.c $(LIBFT_A) -o $(NAME) && ./$(NAME)

pipe:
	$(CC) $(CDEBUG) $(CLIBS) -I $(INCS_DIR) srcs/sample_pipe_and_redirect.c  -o $(NAME) && ./$(NAME)
	
.PHONY: all clean fclean re
