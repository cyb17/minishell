# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achevala <achevala@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 10:12:10 by yachen            #+#    #+#              #
#    Updated: 2023/12/09 12:59:29 by achevala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 

CFLAGS =  -Wall -Wextra -Werror -g3

READLINE = -lreadline

RM = rm -rf

SRC = ./srcs/main.c ./srcs/parsing.c ./srcs/init.c ./srcs/utils_parsing.c\
	./srcs/ft_split_minishell.c ./srcs/utils_cleaning.c\
	./srcs/split_input.c ./srcs/expand/expand.c ./srcs/clean_words.c\
	./srcs/utils_double.c ./srcs/utils_parsing2.c\
	./srcs/garbage_collector.c ./srcs/tokenization/token.c\
	./srcs/utils_parsing3.c ./srcs/utils_split_minishell.c\
	./srcs/utils_write_in.c ./srcs/redir.c\
	./srcs/utils_redir.c ./srcs/expand/expand_utils.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@echo "\033[32m\n==================================="
		@make -C ./libft
		@echo "\033[32mCompiling minishell-----------------"
		@$(CC) $(CFLAGS) $(OBJ) $(READLINE) ./libft/libft.a -o $(NAME)
		@echo "\033[32m----created with success : minishell"
		@echo "\033[32m===================================\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[32m\n====================="
	@echo "\033[32mCleaning minishell----"
	@$(RM) $(OBJ)
	@echo "\033[32m------minishell Cleaned"
	@make clean -C ./libft
	@echo "\033[32m=====================\n"

fclean:
	@echo "\033[32m\n====================="
	@echo "\033[32mCleaning minishell----"
	@$(RM) $(OBJ)
	@echo "\033[32m------minishell Cleaned"
	@$(RM) $(NAME)
	@make fclean -C ./libft
	@echo "\033[32m=====================\n"

re: fclean all

.PHONY: clean fclean all re bonus
