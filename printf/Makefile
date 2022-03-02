# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/04 10:12:36 by dthalman          #+#    #+#              #
#    Updated: 2022/02/25 14:52:07 by dthalman         ###   ########.fr        #
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
NAME       = libprintf.a
INCS_DIR   = -I ../libft -I ./inc 
SRCS_DIR   = ./srcs
SRCS_NAME  = ft_print_hex_fd.c \
			 ft_print_pointer_fd.c \
			 ft_print_unsigned_dec_fd.c \
			 ft_print_utils_two.c \
			 ft_print_char_fd.c \
			 ft_print_integer_fd.c \
			 ft_print_string_fd.c \
			 ft_print_utils.c \
			 ft_ltox_fd.c \
			 ft_itoa_fd.c \
			 ft_fprintf.c \
			 ft_printf.c
SRCS       = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS       = $(SRCS:.c=.o)

### TESTS ###

ifeq ($(shell uname), Linux)
	LEAKS = 
else
#	LEAKS = leaks -atExit --
	LEAKS = 
endif

LIBFT_FLAG = -lft
LIBFT_DIR  = ./libft
LIBFT_INC  = ./libft
LIBFT_A    = ./libft/libft.a

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

.PHONY: all clean fclean re debug dev
