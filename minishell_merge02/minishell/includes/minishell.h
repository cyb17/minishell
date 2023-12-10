/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:29:40 by yachen            #+#    #+#             */
/*   Updated: 2023/12/09 14:25:26 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../srcs/libft/libft.h"

extern int	g_signal[2];

enum tokens_type
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
	int				id;
	int				type;
	char 			*value;
	struct s_tokens	*next;
}					t_tokens;

typedef struct s_process
{
    char				*section_cmd;
	int					section_cmd_id;
	t_tokens			*list_tokens;
	pid_t				pid;
	struct s_process	*next;
}						t_process;

typedef struct s_all	t_all;

typedef struct s_p
{
	char				*s;
	char				*s0;
	char				*s1;
	char				*cpy2;
	char				*s3;
	int					len;
	int					len1;
	int					start;
	int					id;
	int					i;
	int					z;
	int					j;
	int					k;
	int					l;
	int					max;
	char				**words;
	char				**tkn;
	t_all				*all;
}						t_p;

typedef struct s_all
{
	t_process	*process;
	t_p			*p;
	t_list		*envlist;
}				t_all;

typedef struct s_builtins
{
	t_list	*envlist;
	t_list	*explist;
	char	**arg;
}				t_builtins;

typedef struct s_tab
{
	int			nb_pipe;
	int			**pipefd;
}			t_tab;

typedef struct s_var
{
	t_list	**list;
	t_list	*oldvar;
	t_list	*newvar;
	int		oldvar_i;
	int		equal_i;
	int		plus_i;
}			t_var;

typedef struct s_redir
{
	int			fdin;
	int			fdout;
	int			stdin;
	int			stdout;
}				t_redir;

typedef struct s_res
{
	t_process	*prcs;
	t_builtins	*blt;
	t_tab		*tab;
	char		*input;
	t_redir		*io;
}				t_res;

#endif