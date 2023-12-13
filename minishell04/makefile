# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachen <yachen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 14:39:57 by yachen            #+#    #+#              #
#    Updated: 2023/12/09 14:39:04 by yachen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS =  -Wall -Wextra -Werror -g3

LIBFTDIR = ./srcs/libft

PARSING = parsing init utils_parsing ft_split_minishell utils_cleaning \
		  split_input expand clean_words utils_parsing2 \
		  garbage_collector_parsing token utils_parsing3 utils_split_minishell \
		  utils_write_in redir utils_redir expand_utils \

BUILTINS = cd echo env export/export_part1 export/export_part2 export/export_part3 pwd unset utils exit \

EXECUTION = minishell single_prcs garbage_collector init_ressources \
			here_doc redirections_prcs pipex_parsing_cmd_1 pipex_parsing_cmd_2 \
			exe_no_builtins exe_builtins multi_process utils_1 utils_2 utils_3 \
			
RM = rm -rf

SRC = $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix srcs/execution/, $(EXECUTION))) \
	  $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS)))
	  
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
