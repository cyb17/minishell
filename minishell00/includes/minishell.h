/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:18:57 by yachen            #+#    #+#             */
/*   Updated: 2023/11/17 17:02:51 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "../srcs/builtins/builtins.h"

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
	int				token_id;
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

typedef struct s_builtins
{
	t_list	*envlist;
	t_list	*explist;
	char	**arg;
}				t_builtins;

typedef struct s_tab
{
	int			fdin;
	int			fdout;
	int			nb_pipe;
	int			**pipefd;
	pid_t		*tab_pid;
}			t_tab;

typedef struct s_res
{
	t_process	*prcs;
	t_builtins	*blt;
	t_tab		*tab;
	char		*input;
}				t_res;
/*
EXECUTION

//utils
int		ft_compare(char *limiter, char *str);
void	close_allfd(t_tab *tab);
void	wait_proces(int *pid, int nb_proces);
*/
//garbage_collector
void	garbage_collector(t_res *res);
/*
// redirections
void	redirect_in(int *fdin, char *infile);
void	redirect_out(int *fdout, char *outfile, char mode);
char	*ft_here_doc(char *limiter);

// pipex_parsing_cmd
char	**make_cmd(char *str);
int		check_cmd(char *cmd);
char	*sub_parsing_cmd1(char **split_cmd);
char	*sub_parsing_cmd2(char **env_main, char **env_exev, char *cmd);
char	*parsing_cmd(char **env_main, char *cmd, char **env_exev);

// pipex_find_path
char	**find_path(char **env, char *cmd);

// pipex_child_proces_step
char	*child_procs_part_1(t_tab *tab, char **env, char *argv_value);
void	child_procs_part_2(t_tab *tab, int input, int output, char *arg);
void	child_procs_part_3(t_tab *tab, char *path, char *argv_value);
*/

// test
t_process	*create_list_process(char **arg);
void		clear_lst(t_list **list);
t_list		*env_to_envlist(char **env);
int			find_nb_process(t_process *process);
void		free_pipefd(int **pipefd, int nb_pipe);
int			pipe_pipefd(int **pipefd, int nb_pipe);
int			creat_pipefd(t_tab *tab);
t_tab		*fill_tab(t_process *process);
t_builtins	*fill_builtins(char **env);

#endif
