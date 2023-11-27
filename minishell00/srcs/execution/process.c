/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:14:40 by yachen            #+#    #+#             */
/*   Updated: 2023/11/27 15:44:25 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	check_fdin_fdout(int *fdin, int *fdout, t_tokens *tokens)
{
	char	*here_doc;

	while (tokens)
	{
		if (tokens->type == REDIR_IN && tokens->next->type == INFILE)
			redirect_in(fdin, tokens->next->value);
		else if (tokens->type == REDIR_OUT && tokens->next->type == OUTFILE)
			redirect_out(fdout, tokens->next->value, 'T');
		else if (tokens->type == APPEN && tokens->next->type == OUTFILE)
			redirect_out(fdout, tokens->next->value, 'A');
		else if (tokens->type == HEREDOC)
		{
			here_doc = ft_here_doc(tokens->next->value);
			redirect_in(fdin, here_doc);
			free(here_doc);
		}
		if ((*fdin == -1) || (*fdout == -1))
			return (-1);
		tokens = tokens->next;
	}
	return (0);
}

void	exe_prcs(t_res *res, char **env, t_process *prcs, int i)
{
	int			fdin;
	int			fdout;

	fdin = 0;
	fdout = 1;
	prcs->pid = fork();
	if (prcs->pid == -1)
	{
		garbage_collector(res);
		perror("Error : fork");
		return ;
	}
	else if (prcs->pid == 0)
	{
		if (check_fdin_fdout(&fdin, &fdout, prcs->list_tokens) == -1)
		{
			clean_fds(fdin, fdout);
			garbage_collector(res);
			return ;
		}
		redirection_multi_prcs(fdin, fdout, res->tab, i);
		execute_cmd(res, env, prcs->list_tokens);
	}
	else
		close_pipeline_fds(res->tab, i);
}

void	close_pipeline_fds(t_tab *tab, int i)
{
	if (i == 0)
		close(tab->pipefd[i][1]);
	else if (i == tab->nb_pipe)
		close(tab->pipefd[i - 1][0]);
	else
	{
		close(tab->pipefd[i][1]);
		close(tab->pipefd[i - 1][0]);
	}
}

void	multi_prcs(t_res *res, char **env)
{
	int			i;
	t_process	*tmp;

	i = 0;
	tmp = res->prcs;
	res->tab = fill_tab(res->prcs);
	if (!res->tab)
	{
		garbage_collector(res);
		return ;
	}
	while (tmp)
	{
		pipe_pipefd(res->tab, i);
		exe_prcs(res, env, tmp, i);
		tmp = tmp->next;
		i++;
	}
	tmp = res->prcs;
	while (tmp)
	{
		if (tmp->pid != 0)
			waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
}

void	single_prcs(t_res *res, char **env)
{
	int			fdin;
	int			fdout;

	fdin = 0;
	fdout = 1;
	res->prcs->pid = fork();
	if (res->prcs->pid == -1)
	{
		clean_fds(fdin, fdout);
		garbage_collector(res);
		perror("Error : fork");
		return ;
	}
	else if (res->prcs->pid == 0)
	{
		if (check_fdin_fdout(&fdin, &fdout, res->prcs->list_tokens) == -1)
		{
			garbage_collector(res);
			return ;
		}
		redirection_single_prcs(fdin, fdout);
		execute_cmd(res, env, res->prcs->list_tokens);
	}
	waitpid(res->prcs->pid, NULL, 0);
}
