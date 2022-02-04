# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/04 10:12:36 by dthalman          #+#    #+#              #
#    Updated: 2022/02/04 10:12:36 by dthalman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILE ###
RM         = rm -rf
CC         = gcc
CDEBUG     = -g3 -fsanitize=address
CFLAGS     = -Werror -Wextra -Wall $(CDEBUG)
CLIBS      = 
NORM       = norminette
AR         = ar -rcs

### FILES ###
NAME       = libparser.a
INCS_DIR   = ./incs
SRCS_DIR   = ./srcs
SRCS_NAME  = ft_parser.c
SRCS       = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS       = $(SRCS:.c=.o)

### RULES ###
all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I $(INCS_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	$(NORM)
	
.PHONY: all clean fclean re
