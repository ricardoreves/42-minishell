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
CFLAGS     = -Werror -Wextra -Wall
LDFLAGS    = 
CLIBS      = 
NORM       = norminette
AR         = ar -rcs

### FILES ###
NAME       = libparser.a
INCS_DIR   = -I ../libft
SRCS_DIR   = ./srcs
SRCS_NAME  = ft_parser.c \
			 ft_ascii.c
SRCS       = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS       = $(SRCS:.c=.o)
LIBFT_DIR  = ../libft
LIBFT_A    = $(LIBFT_DIR)/libft.a

### TESTS ###
TEST       = tester
TESTS_DIR  = ./tests
TESTS_NAME = libparser_tester.c 
TESTS_INCS = -I./srcs
TESTS_LNK  = -L. -lparser -L$(LIBFT_DIR) -lft 
TESTS_SRCS = $(addprefix $(TESTS_DIR)/, $(TESTS_NAME))
TESTS_OBJS = $(TESTS_SRCS:.c=.o)

### RULES ###
all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCS_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

debug: CFLAGS += $(CDEBUG)
debug: $(NAME)

dev: debug

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	$(NORM)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)
	
test: CFLAGS += $(CDEBUG)
test: LDFLAGS += $(TESTS_LNK)
test: INCS_DIR += $(TESTS_INCS)
test: $(NAME) $(LIBFT_A) $(TESTS_OBJS)
	$(CC) $(CFLAGS) $(TESTS_INCS) $(TESTS_OBJS) $(LDFLAGS) -o $(TEST)

.PHONY: all clean fclean re debug dev
