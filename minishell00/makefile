# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachen <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 14:39:57 by yachen            #+#    #+#              #
#    Updated: 2023/10/24 14:54:02 by yachen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS =  -Wall -Wextra -Werror -g

LIBFTDIR = ./libft

RM = rm -rf

SRC = srcs/builtins.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@echo "\033[32m\n==================================="
		@make -C $(LIBFTDIR) bonus
		@echo "\033[32mCompiling minishell-----------------"
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFTDIR)/libft.a -o $(NAME)
		@echo "\033[32m----created with success : minishell"
		@echo "\033[32m===================================\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[32m\n====================="
	@echo "\033[32mCleaning minishell----"
	@$(RM) $(OBJ)
	@echo "\033[32m------minishell Cleaned"
	@make clean -C $(LIBFTDIR)
	@echo "\033[32m=====================\n"

fclean:
	@echo "\033[32m\n====================="
	@echo "\033[32mCleaning minishell----"
	@$(RM) $(OBJ)
	@echo "\033[32m------minishell Cleaned"
	@$(RM) $(NAME)
	@make fclean -C $(LIBFTDIR)
	@echo "\033[32m=====================\n"

re: fclean all

.PHONY: clean fclean all re bonus
