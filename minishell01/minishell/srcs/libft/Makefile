# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachen <yachen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 17:32:38 by yachen            #+#    #+#              #
#    Updated: 2023/08/31 14:59:19 by yachen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a 

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRC = ft_atoi.c ft_isalpha.c ft_memchr.c ft_memset.c ft_putstr_fd.c ft_strjoin.c ft_strnstr.c ft_tolower.c \
	ft_bzero.c ft_isascii.c ft_memcmp.c ft_putchar_fd.c ft_split.c ft_strlcat.c ft_strrchr.c ft_toupper.c \
	ft_calloc.c ft_isdigit.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcpy.c ft_strtrim.c \
	ft_isalnum.c ft_isprint.c ft_memmove.c ft_putnbr_fd.c ft_strdup.c ft_strncmp.c ft_substr.c \
	ft_strlen.c ft_itoa.c ft_strmapi.c ft_striteri.c get_next_line.c get_next_line_utils.c\
	ft_printf.c ft_printf_str.c ft_printf_nbr.c ft_printf_hexa.c ft_printf_char.c ft_printf_unsi.c ft_printf_ptr.c \
	str_len.c free_tab.c ft_strcmp.c \

BONUS_SRC = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
			ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_lstmap.c \

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(BONUS_SRC:.c=.o)

all: $(NAME)

bonus: $(OBJ) $(OBJ_BONUS)
	@ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)

$(NAME): $(OBJ)
	@echo "\033[33mCompiling Libft---------------"
	@ar rcs $(NAME) $(OBJ)
	@echo "\033[33m----Libft created with success"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[33mCleaning Libft----"
	@$(RM) $(OBJ) $(OBJ_BONUS)
	@echo "\033[33m-----Libft Cleaned"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all bonus re
