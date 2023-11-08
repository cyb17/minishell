/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:45:45 by yachen            #+#    #+#             */
/*   Updated: 2023/11/08 17:22:30 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_inoutfile(int *fdin, int *fdout, t_tokens *tokens)
{
	char	*here_doc;

	while (tokens)
	{
		if (tokens->type == REDIR_IN && tokens->next->type == INFILE)
			redirect_in(fdin, tokens->next->value);
		else if (tokens->type = REDIR_OUT && tokens->next->type == OUTFILE)
			fredirect_out(fdout, tokens->next->value, 'T');
		else if (tokens->type = APPEN && tokens->next->type == OUTFILE)
			fredirect_out(fdout, tokens->next->value, 'A');
		else if (tokens->type = HEREDOC)
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

int	make_inoutfile(int *fdin, int *fdout, t_process *process)
{
	while (process)
	{
		if (find_inoutfile(fdin, fdout, process->list_tokens) == -1)
		{
			if (*fdin > 0)
				close(*fdin);
			if (*fdout > 0)
				close(*fdout);
			return (-1);
		}
		process = process->next;
	}
	return(0);
}

char	*join_cmd_and_option(char *s1, char *s2)
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

int	isnot_builtins(char *str)
{
	if ((strcmp("echo", str) == 1) || (strcmp("cd", str) == 1)
		|| (strcmp("env", str) == 1) || (strcmp("exit", str) == 1)
		|| (strcmp("export", str) == 1) || (strcmp("unset", str) == 1)
		|| (strcmp("pwd", str) == 1))
		return (0);
	return (1);
}

int	find_nb_cmd(t_process *process)
{
	int	nb_cmd;

	nb_cmd = 0;
	while (process)
	{
		while (process->list_tokens)
		{
			if (process->list_tokens->type == CMD
				&& isnot_builtins(process->list_tokens->value) == 1)
			{
				nb_cmd++;
				break;
			}
			process->list_tokens = process->list_tokens->next;
		}
		process = process->next;
	}
	return (nb_cmd);
}

char	*find_cmd(t_tokens *tokens)
{
	char		*tmp;
	char		*cmd;

	cmd = NULL;
	while (tokens && tokens->type != CMD)
		tokens = tokens->next;
	if (tokens == NULL || isnot_builtins(tokens->value) == 0)
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

char	**make_tab_cmd(t_process *process, int nb_cmd)
{
	char	**tab_cmd;
	int		i;

	tab_cmd = (char **)malloc(sizeof(char *) * (nb_cmd + 1));
	if (!tab_cmd)
		return (NULL);
	i = 0;
	while (process)
	{
		tab_cmd[i] = find_cmd(process->list_tokens);
		if (tab_cmd[i] != NULL)
			i++;
		process = process->next;
	}
	tab_cmd[i] = NULL;
	return (tab_cmd);
}

int	init_tab(t_tab *tab, t_process *process)
{
	int	i;

	tab->fdin = 0;
	tab->fdout = 0;
	tab->nb_pipe = find_nb_cmd(process) - 1;
	tab->pipefd = (int **)malloc(sizeof(int *) * (tab->nb_pipe));
	if (!(tab->pipefd))
		return (-1);
	i = 0;
	while (i < tab->nb_pipe)
	{
		tab->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!(tab->pipefd[i]))
		{
			while (--i >= 0)
			{
				if (tab->pipefd[i])
					free(tab->pipefd[i]);
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

int	pipex(t_process *process, char **env)
{
	t_tab	tab;
	char	**tab_cmd;
	int		i;

	init_tab(&tab, process);
	tab_cmd = make_tab_cmd(process, tab.nb_pipe + 1);
	if (!tab_cmd)
	{
		ft_putstr_fd("minishell: pipex failed\n", 2);
		return (1);
	}
	i = 0;

}