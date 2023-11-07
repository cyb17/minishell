# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachen <yachen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 14:39:57 by yachen            #+#    #+#              #
#    Updated: 2023/11/07 18:02:13 by yachen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS =  -Wall -Wextra -Werror -g

LIBFTDIR = ./srcs/libft

RM = rm -rf

SRC = srcs/builtins/export_part1.c srcs/builtins/export_part2.c srcs/builtins/echo.c \
	  srcs/builtins/env.c srcs/builtins/unset.c srcs/builtins/builtins_utils1.c \
	  srcs/builtins/pwd.c srcs/builtins/cd.c srcs/builtins/env.c \
	  srcs/execution/redirections.c srcs/execution/utils.c srcs/execution/garbage_collector.c \
	  #srcs/builtins/main.c \
	  
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@echo "\e[32m\n==================================="
		@make -C $(LIBFTDIR) bonus
		@echo "\e[32mCompiling minishell-----------------"
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFTDIR)/libft.a -o $(NAME) -lreadline
		@echo "\e[32m----created with success : minishell"
		@echo "\e[32m===================================\n\e[0m"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\e[32m\n====================="
	@echo "\e[32mCleaning minishell----"
	@$(RM) $(OBJ)
	@echo "\e[32m------minishell Cleaned"
	@make clean -C $(LIBFTDIR)
	@echo "\e[32m=====================\n\e[0m"

fclean:
	@echo "\e[32m\n====================="
	@echo "\e[32mCleaning minishell----"
	@$(RM) $(OBJ)
	@echo "\e[32m------minishell Cleaned"
	@$(RM) $(NAME)
	@make fclean -C $(LIBFTDIR)
	@echo "\e[32m=====================\n\e[0m"

re: fclean all

.PHONY: clean fclean all re bonus
