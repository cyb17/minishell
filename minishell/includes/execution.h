/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:18:57 by yachen            #+#    #+#             */
/*   Updated: 2023/12/21 15:08:58 by yachen           ###   ########.fr       */
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

// ft_here_doc
char		*ft_here_doc(char *limiter);

// init_ressources
int			find_nb_process(t_process *process);
t_tab		*fill_tab(t_process *process);
t_builtins	*fill_builtins(char **env);
void		start_data_init(t_res *res, t_all *all, char **env, char **argv);

// multi_prcs
void		multi_prcs(t_res *res);

// cmd_parsing
char		*parsing_cmd(char **env_main, char **cmd);

// redir_multi_prcs
int			redirection_multi_prcs(int fdin, int fdout, t_tab *tab, int i);

// single_prcs
void		single_prcs(t_res *res);

// utils_1
void		free_pipefd(int **pipefd, int nb_pipe);
int			pipe_pipefd(t_tab *tab, int i);
void		redirect_in(int *fdin, char *infile);
void		redirect_out(int *fdout, char *outfile, char mode);
int			open_fdin_fdout(int *fdin, int *fdout, t_process *prcs);
// utils_2
void		clean_fdin_fdout(int fdin, int fdout);
t_tokens	*check_cmd_tk(t_tokens *list_tokens);
int			ft_execve(char **env, char *path, char **arg);
int			init_io(t_redir *io);
int			init_stdin_stdout(int stdin, int stdout);
// utils_3
int			isnot_builtins(char *str);
void		signal_handler_main(int signum);
void		signal_handler_hd(int signum);
void		ft_ctrl_d(void);
void		waitpid_and_fixe_exit_code(t_res *res);

#endif
