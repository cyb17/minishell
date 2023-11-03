/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:06:32 by nap               #+#    #+#             */
/*   Updated: 2023/11/03 16:11:07 by achevala         ###   ########.fr       */
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

enum 	e_tokens_type
{
	CMD = 1,
	WORD = 2,
	INFILE = 3,
	OUTFILE = 4,
	REDIR_IN = 5,
	REDIR_OUT = 6,
	APPEN = 7,
	HEREDOC = 8
};

typedef struct s_tokens
{
	int				token_id;
	int				type;
	char 			*value;
	struct s_tokens	*next_tokens; 
}					t_tokens;

typedef struct s_process
{
    char				*section_cmd;
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
//int		main(int ac, char **av, char **env);

/* parsing.c */
int		ft_parse(char *line, t_process **process);
// bool	is_valid(char *l);
bool	first_readind(char *input);

/* utilis_parsing.c*/
int		check_quotes(char *input, char c, int i);
int		between_quotes(char *l, int i);
char	*ft_strdup_section(char *s, int start, int end);
void	ft_procsadd_back(t_process **lst, t_process *new);

/* init.c */
void	process_init(t_process *process);
void	*data_init(t_data *data, char *line);

/*split_input.c*/
t_process	**make_proces_list(char *line);
t_process	*create_process(char *start, int end, int id);

#endif
