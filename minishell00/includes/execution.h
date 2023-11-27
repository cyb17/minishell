/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:18:57 by yachen            #+#    #+#             */
/*   Updated: 2023/11/27 15:51:11 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "builtins.h"

/* EXECUTION */

// garbage_collector
void		garbage_collector(t_res *res);
int			ft_compare(char *limiter, char *str);

// init_ressources
void		free_pipefd(int **pipefd, int nb_pipe);
int			pipe_pipefd(t_tab *tab, int i);
int			find_nb_process(t_process *process);
t_tab		*fill_tab(t_process *process);
t_builtins	*fill_builtins(char **env);

// redirections_1
void		redirect_in(int *fdin, char *infile);
void		redirect_out(int *fdout, char *outfile, char mode);
char		*ft_here_doc(char *limiter);
// redirections_2
void		redirection_multi_prcs(int fdin, int fdout, t_tab *tab, int i);
void		redirection_single_prcs(int fdin, int fdout);

// pipex_parsing_cmd_1
char		*sub_parsing_cmd1(char **split_cmd);
char		*sub_parsing_cmd2(char **env_main, char **env_exev, char *cmd);
char		*parsing_cmd(char **env_main, char *cmd, char **env_exev);
char		**find_path(char **env, char *cmd);
// pipex_parsing_cmd_2
char		**find_path(char **env, char *cmd);
char		**make_cmd(char *str);
int			check_cmd(char *cmd);

// exe_no_builtins
char		*find_execve_path(t_res *res, char **env, char *argv_value);
void		ft_execve(t_res *res, char *path, char *argv_value);
char		*make_cmdtk_to_arg(t_tokens *tokens);
void		exe_no_builtins(t_res *res, char **env, t_tokens *cmd);

// exe_builtins
void		exe_builtins(t_res *res, t_tokens *cmd);

// process
int			check_fdin_fdout(int *fdin, int *fdout, t_tokens *tokens);
void		exe_prcs(t_res *res, char **env, t_process *prcs, int i);
void		close_pipeline_fds(t_tab *tab, int i);
void		multi_prcs(t_res *res, char **env);
void		single_prcs(t_res *res, char **env);

// process_utils
int			isnot_builtins(char *str);
t_tokens	*check_cmd_tk(t_tokens *list_tokens);
void		execute_cmd(t_res *res, char **env, t_tokens *list_tokens);
void		clean_fds(int fdin, int fdout);
void		ft_error(char *where, char *what);

// fonction for test
t_process	*create_list_process(void);

#endif
