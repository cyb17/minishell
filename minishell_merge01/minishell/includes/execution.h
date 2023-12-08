/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:18:57 by yachen            #+#    #+#             */
/*   Updated: 2023/12/08 16:19:37 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "builtins.h"
# include "parsing.h"


/* EXECUTION */

// exe_builtins
int			exe_builtins(t_res *res, t_tokens *cmd);

// exe_no_builtins
int			exe_no_builtins(t_res *res, t_tokens *cmd);

// garbage_collector
void		garbage_collector_child(t_res *res);
void		garbage_collector_parent(t_res *res);

// here_doc
char		*ft_here_doc(char *limiter);

// init_ressources
int			find_nb_process(t_process *process);
t_tab		*fill_tab(t_process *process);
t_builtins	*fill_builtins(char **env);

// multi_prcs
void		multi_prcs(t_res *res);

// pipex_parsing_cmd_1
char		*sub_parsing_cmd1(char **split_cmd);
char		*sub_parsing_cmd2(char **env_main, char *cmd);
char		*parsing_cmd(char **env_main, char *cmd);
char		**find_path(char **env, char *cmd);
// pipex_parsing_cmd_2
char		**find_path(char **env, char *cmd);
char		**make_cmd(char *str);
int			check_cmd(char *cmd);

// redirections_prcs
void		redirection_multi_prcs(int fdin, int fdout, t_tab *tab, int i);
int			redirection_single_prcs(int fdin, int fdout);

// single_prcs
void		single_prcs(t_res *res);

// utils_1
void		free_pipefd(int **pipefd, int nb_pipe);
int			pipe_pipefd(t_tab *tab, int i);
void		redirect_in(int *fdin, char *infile);
void		redirect_out(int *fdout, char *outfile, char mode);
int			open_fdin_fdout(int *fdin, int *fdout, t_tokens *tokens);
// utils_2
void		clean_fds(int fdin, int fdout);
int			isnot_builtins(char *str);
t_tokens	*check_cmd_tk(t_tokens *list_tokens);
int			ft_execve(char **env, char *path, char *arg);
int			init_stdin_stdout(int stdin, int stdout);

// utils_3
void		ft_error(char *where, char *what);











#endif
