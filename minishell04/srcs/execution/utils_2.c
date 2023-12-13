/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:57:26 by yachen            #+#    #+#             */
/*   Updated: 2023/12/08 17:05:49 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// If there is a infile or a outfile valid fd opened, close it.
void	clean_fds(int fdin, int fdout)
{
	if (fdin != STDIN_FILENO && fdin != -1)
		close(fdin);
	if (fdout != STDOUT_FILENO && fdout != -1)
		close(fdout);
}

int	isnot_builtins(char *str)
{
	if ((ft_strcmp("echo", str) == 1) || (ft_strcmp("cd", str) == 1)
		|| (ft_strcmp("env", str) == 1) || (ft_strcmp("exit", str) == 1)
		|| (ft_strcmp("export", str) == 1) || (ft_strcmp("unset", str) == 1)
		|| (ft_strcmp("pwd", str) == 1))
		return (0);
	return (1);
}

// If there is a cmd, return a pointer on cmd
t_tokens	*check_cmd_tk(t_tokens *list_tokens)
{
	t_tokens	*tmp;

	tmp = list_tokens;
	while (tmp)
	{
		if (tmp->type == CMD)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_execve(char **env, char *path, char *arg)
{
	char	**cmd;

	cmd = make_cmd(arg);
	if (execve(path, cmd, env) == -1)
	{
		perror("Error: execve");
		free_tab(cmd);
		free_tab(env);
		free(arg);
		free(path);
		return (-1);
	}
	return (0);
}

int	init_stdin_stdout(int stdin, int stdout)
{
	if (dup2(stdin, STDIN_FILENO) == -1)
	{
		perror("Error: init_stdin_stdout: dup2");
		close(stdin);
		close(stdout);
		return (-1);
	}
	close(stdin);
	if (dup2(stdout, STDOUT_FILENO) == -1)
	{
		perror("Error: init_stdin_stdout: dup2");
		close(stdin);
		close(stdout);
		return (-1);
	}
	close(stdout);
	return (0);
}
