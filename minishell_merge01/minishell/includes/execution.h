/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:18:57 by yachen            #+#    #+#             */
/*   Updated: 2023/12/08 13:44:40 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "builtins.h"
# include "parsing.h"


/* EXECUTION */

// garbage_collector
void		garbage_collector_child(t_res *res);
void		garbage_collector_parent(t_res *res);

// init_ressources
int			find_nb_process(t_process *process);
t_tab		*fill_tab(t_process *process);
t_builtins	*fill_builtins(char **env);

// here_doc
char		*ft_here_doc(char *limiter);

// redirections_prcs
void		redirection_multi_prcs(int fdin, int fdout, t_tab *tab, int i);
int			redirection_single_prcs(int fdin, int fdout);

// pipex_parsing_cmd_1
char		*sub_parsing_cmd1(char **split_cmd);
char		*sub_parsing_cmd2(char **env_main, char *cmd);
char		*parsing_cmd(char **env_main, char *cmd);
char		**find_path(char **env, char *cmd);
// pipex_parsing_cmd_2
char		**find_path(char **env, char *cmd);
char		**make_cmd(char *str);
int			check_cmd(char *cmd);

// exe_no_builtins
int			exe_no_builtins(t_res *res, t_tokens *cmd);

// exe_builtins
int			exe_builtins(t_res *res, t_tokens *cmd);

// process
int			open_fdin_fdout(int *fdin, int *fdout, t_tokens *tokens);
void		exe_prcs(t_res *res, t_process *prcs, int i);
void		close_pipeline_fds(t_tab *tab, int i);
void		multi_prcs(t_res *res);
void		single_prcs(t_res *res);
int			init_stdin_stdout(int stdin, int stdout);

// process_utils_1
int			isnot_builtins(char *str);
t_tokens	*check_cmd_tk(t_tokens *list_tokens);
void		execute_cmd(t_res *res, t_tokens *list_tokens);
void		clean_fds(int fdin, int fdout);
int			ft_execve(char **env, char *path, char *arg);
void		ft_error(char *where, char *what);
int			init_stdin_stdout(int stdin, int stdout);
// process_utils_2
void		free_pipefd(int **pipefd, int nb_pipe);
int			pipe_pipefd(t_tab *tab, int i);
void		redirect_in(int *fdin, char *infile);
void		redirect_out(int *fdout, char *outfile, char mode);

// fonction for test
t_process	*create_list_process(void);

#endif
