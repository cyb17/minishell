/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:06:32 by nap               #+#    #+#             */
/*   Updated: 2023/11/01 16:31:28 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include <curses.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef enum 	e_tokens_type
{
	T_CMD = 1,
	T_WORD = 2,
	T_INFILE = 3,
	T_OUTFILE = 4,
	T_REDIR_IN = 5,
	T_REDIR_OUT = 6,
	T_APPEN = 7,
	T_HEREDOC = 8,
	T_SPACE = 9,
}				t_tokens_type;

typedef struct s_tokens
{
	int				token_id;
	int				type;
	char 			*value;
	struct s_tokens	*next_tokens; 
}					t_tokens;

typedef struct s_process
{
    char				**section_cmd;
	int					section_cmd_id;
	t_tokens			*list_tokens;
	pid_t				pid;
	struct s_process	*next_process;
}						t_process;

typedef struct s_data
{
	char				*s;
	int					len;
	struct s_process	*process;
}						t_data;

/* main.c */
int		main(int ac, char **av, char **env);

/* parsing.c */
int		ft_parse(char *line);
int		check_quotes(char *input, char c, int i);
bool	is_valid(char *l);
bool	first_readind(char *input);

/* utilis_parsing.c*/
bool	valid_char(char c);
int		between_quotes(char *l, int i);

/* init.c */
void	process_init(t_process *process);
void	*data_init(t_data *data, char *line);

#endif
