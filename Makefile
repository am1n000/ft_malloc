# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-rhai <ael-rhai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 17:29:28 by ael-rhai          #+#    #+#              #
#    Updated: 2024/12/19 13:07:13 by ael-rhai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


CC=gcc
FLAGS= -Wall -Wextra -Werror
NAME=malloc
SRC=main.c src/malloc.c src/global.c

all: $(NAME)


$(NAME): $(SRC)
	@$(CC) $^ -o $@
	@echo "\033[32m Compilation success\033[0m"

clean:
	@rm -rf src/*.o
	@echo "\033[31m object files deleted\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[31m program terminated\033[0m"

re: fclean all
