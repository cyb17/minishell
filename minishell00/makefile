# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachen <yachen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 14:39:57 by yachen            #+#    #+#              #
#    Updated: 2023/11/18 14:47:07 by yachen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS =  -Wall -Wextra -Werror -g

LIBFTDIR = ./srcs/libft

BUILTINS =

EXECUTION = minishell list_process fonctions_for_test garbage_collector init_ressources \
			redirections pipex pipex_child_procs_step pipex_find_path pipex_parsing_cmd \
			#utils \
			
RM = rm -rf

SRC = $(addsuffix .c, $(addprefix srcs/execution/, $(EXECUTION)))
	  
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
