/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:45:45 by yachen            #+#    #+#             */
/*   Updated: 2023/11/16 13:33:10 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	isnot_builtins(char *str)
{
	if ((strcmp("echo", str) == 1) || (strcmp("cd", str) == 1)
		|| (strcmp("env", str) == 1) || (strcmp("exit", str) == 1)
		|| (strcmp("export", str) == 1) || (strcmp("unset", str) == 1)
		|| (strcmp("pwd", str) == 1))
		return (0);
	return (1);
}

int	find_nb_process(t_process *process)
{
	int	nb_process;

	nb_process = 0;
	while (process)
	{
		nb_process++;
		process = process->next;
	}
	return (nb_process);
}

static char	*join_cmd_and_option(char *s1, char *s2)
{
	char	*tmp;
	char	*cmd;

	tmp = NULL;
	cmd = NULL;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	tmp = ft_strjoin(s1, " ");
	cmd = ft_strjoin(tmp, s2);
	if (tmp)
		free(tmp);
	return (cmd);
}

char	*make_cmdtk_to_arg(t_tokens *tokens)
{
	char		*tmp;
	char		*cmd;

	cmd = NULL;
	while (tokens && tokens->type != CMD)
		tokens = tokens->next;
	if (tokens == NULL)
		return (NULL);
	while (tokens && tokens != CMD && tokens != WORD)
	{
		tmp = cmd;
		cmd = join_cmd_and_option(cmd, tokens->value);
		if (tmp)
			free(tmp);
		if (!cmd)
			return (NULL);
		tokens = tokens->next;
	}
	return (cmd);
}

void	fixe_in_output(int *intput, int *output, t_tab *tab, int i)
{
	if (i == 0)
		*input = tab->fdin;
	else
		*input = tab->pipefd[i - 1][0];
	if (i == tab->nb_pipe)
		*output = tab->fdout;
	else
		*output = tab->pipefd[i][1];
}

static void	ft_close(int *input, int *output)
{
	close(*input);
	close(*output);
}

int	make_child_process(t_tokens *cmd_tk, t_tab *tab, int i, char **env)
{
	int	input;
	int	output;
	char	*arg;
	char	*path;

	input = 0;
	output = 0;
	fixe_in_output(&input, &output, tab, i);
	arg = NULL;
	tab->pid[i] = fork();
	if (tab->pid[i] == -1)
	{
		perror("Error : fork");
		return (-1);
	}
	else if (tab->pid[i] == 0)
	{
		arg = make_cmdtk_to_arg(cmd_tk);
		path = child_procs_part_1(tab, env, arg);
		child_procs_part_2(i, tab, input, output)
		child_procs_part_3(tab, path, arg);
	}
	else
		ft_close(&input, &output);
	return (0);
}

int	builtin_cmd_arg(t_tokens *cmd_tk, t_builtins *builtins)
{
	char		**arg;
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = cmd_tk;
	while (tmp && (tmp->type == CMD || tmp->type == WORD))
	{
		i++;
		tmp = tmp->next;
	}
	arg = (char **)malloc(sizeof(char *) * (i + 1));
	if (!arg)
		return (-1);
	i = 0;
	while (cmd_tk && (cmd_tk->type == CMD || cmd_tk->type == WORD))
	{
		arg[i++] = cmd_tk->value;
		cmd_tk = cmd_tk->next;
	}
	arg[i] = NULL;
	builtins->arg = arg;
	return (0);
}

void	which_cmd(t_builtins *builtins, t_tokens *cmd_tk, int *rlt)
{
	if (strcmp("echo", cmd_tk->value) == 1)
		*rlt = ft_echo(bultins->arg);
	else if (strcmp("cd", cmd_tk->value) == 1)
		*rlt = ft_cd(builtins->envlist, bultins->explist, builtins->arg);
	else if (strcmp("env", cmd_tk->value) == 1)
		*rlt = ft_env(builtins->envlist, builtins->arg);
	else if (strcmp("export", cmd_tk->value) == 1)
		*rlt = ft_export(builtins->envlist, builtins->explist, builtins->arg);
	else if (strcmp("unset", cmd_tk->value) == 1)
		*rlt = ft_unset(builtins->envlist, builtins->explist, builtins->arg[0]);
	else if (strcmp("pwd", cmd_tk->value) == 1)
		*rlt = ft_pwd();
	else if (strcmp("exit", cmd_tk->value) == 1)
		*rlt = ft_exit();
	free_tab(builtins->arg);
	builtins->arg = NULL;
}

int	execute_builtins(t_tokens *cmd_tk, t_tab *tab, int i, t_builtins *builtins)
{
	int	rlt;
	int	input;
	int	output;

	result = 0;
	input = 0;
	output = 0;
	fixe_in_output(&input, &output, tab, i);
	if (dup2(input, STDIN_FILENO) < 0 || dup2(output, STDOUT_FILENO) < 0)
	{
		close(input);
		close(output);
		perror("dup2");
		return (-1);
	}
	close(input);
	close(output);
	if (builtin_cmd_arg(cmd_tk, builtins) == -1)
		return (-1);
	which_cmd(buitins, cmd_tk, &rlt);
	return (rlt);
}

int	setup_in_out(t_tab *tab, t_tokens *tokens)
{
	char	*here_doc;

	while (tokens)
	{
		if (tokens->type == REDIR_IN && tokens->next->type == INFILE)
			redirect_in(&tab->fdin, tokens->next->value);
		else if (tokens->type = REDIR_OUT && tokens->next->type == OUTFILE)
			fredirect_out(&tab->fdout, tokens->next->value, 'T');
		else if (tokens->type = APPEN && tokens->next->type == OUTFILE)
			fredirect_out(&tab->fdout, tokens->next->value, 'A');
		else if (tokens->type = HEREDOC)
		{
			here_doc = ft_here_doc(tokens->next->value);
			redirect_in(&tab->fdin, here_doc);
			free(here_doc);
		}
		if ((tab->fdin == -1) || (tab->fdout == -1))
			return (-1);
		tokens = tokens->next;
	}
	return (0);
}

int	pipex(t_res *res, char **env)
{
	int		i;

	i = 0;
	rslt = 0;
	while (res->prcs)
	{
		if (setup_in_out(res->tab, res->prcs->list_tokens) == 0)
		{
			while (res->prcs->list_tokens)
			{
				if (res->prcs->list_tokens->type == CMD)
				{
					if (isnot_builtins(res->prcs->list->tokens->value) == 1)
					{
						make_child_process(res->prcs->list_tokens, res->tab, i, env);
						waitpid(res->tab->pid[i], &rlt, 0);
					}
					else
						rslt = execute_builtins(res->prcs->list_tokens, &tab, i, builtins);
					i++;
					break;
				}
				process->list_tokens = process->list_tokens->next;
			}
		}
		else
			res->prcs = res->prcs->next;
	}
//	wait_proces(tab->tab_pid, tab->nb_pipe);
	return (rsl);
}
////////////////////////////////////////////////////////////////////////////////
void	free_pipefd(int **pipefd, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
		free(pipefd[i++]);
	free(pipefd);
}

int	pipe_pipefd(int **pipefd, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		if ((pipe(pipefd[i])) < 0)
		{
			perror("fill_tab: creat_pipefd");
			while (--i >= 0)
			{
				close(pipefd[i][0]);
				close(pipefd[i][1]);
			}
			free_pipefd(pipefd);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	creat_pipefd(t_tab *tab)
{
	int	i;

	i = 0;
	tab->pipefd = (int **)malloc(sizeof(int *) * (tab->nb_pipe));
	if (!(tab->pipefd))
	{
		ft_putstr_fd("fill_tab: malloc_pipefd: pipefd: malloc failed\n", 2);
		return (-1);
	}
	i = 0;
	while (i < tab->nb_pipe)
	{
		tab->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!(tab->pipefd[i]))
		{
			ft_putstr_fd("fill_tab: malloc_pipefd: []: malloc failed\n", 2);
			free_pipefd(tab->pipefd, i);
			return (-1)
		}
		i++;
	}
	if (pipe_pipefd(tab->pipefd, tab->nb_pipe) == -1)
		return (-1);
	return (0);
}

t_tab	*fill_tab(t_process *process)
{
	t_tab	*tab

	tab = (t_tab *)malloc(sizeof(t_tab));
	if (!tab)
		return (NULL);
	tab->fdin = 0;
	tab->fdout = 0;
	tab->nb_pipe = find_nb_process(process) - 1;
	tab->tab_pid = (pit_t *)malloc(sizeof(pid_t) * (tab->nb_pipe + 1));
	if (!tab->tab_pid)
	{
		free(tab);
		ft_putstr_fd("fill_tab: tab_pid: malloc failed\n", 2);
		return (NULL);
	}
	ft_memset(tab->tab_pid, 0, tab->nb_pipe + 1);
	if (creat_pipefd(tab) == -1)
	{
		free(tab->tab_pid);
		free(tab);
		return (NULL);
	}
	return (tab);
}

t_builtins	*fill_builtins(char **env)
{
	t_builtins	*builtins;

	builtins = (t_builtins *)malloc(sizeof(t_builtins));
	if (!builtins)
		return (NULL);
	*builtins->envlist = env_to_envlist(env);
	if (*builtins->envlist == NULL)
	{
		free(builtins);
		return (NULL);
	}
	*builtins->explist = env_to_envlist(env);
	if (*builtins->explist == NULL)
	{
		clear_lst(builtins->envlist);
		free(builtins);
		return (NULL);
	}
	builtins->arg = NULL;
	return (builtins);
}// fonction teste, no pb
