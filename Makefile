# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 17:29:28 by ael-rhai          #+#    #+#              #
#    Updated: 2024/12/22 20:53:55 by ael-rhai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
SYMLINK = libft_malloc.so
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC
SRC = src/area.c src/block.c src/free_helpers.c src/free.c src/global.c\
	src/helpers.c src/malloc.c src/realloc.c src/show_memory.c main.c
OBJ = $(SRC:.c=.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


all: $(NAME) $(SYMLINK)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -shared -o $@ $^

$(SYMLINK): $(NAME)
	ln -sf $< $(SYMLINK)

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(SYMLINK)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
