/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:57:26 by yachen            #+#    #+#             */
/*   Updated: 2023/12/05 15:49:07 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

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

void	execute_cmd(t_res *res, t_tokens *list_tokens)
{
	t_tokens	*cmd;

	cmd = check_cmd_tk(list_tokens);
	if (!cmd)
		return ;
	if (isnot_builtins(cmd->value) == 1)
	{
		if (exe_no_builtins(res, cmd) == -1)
		{
			garbage_collector_parent(res);
			exit(1);
		}
	}
	else
		exe_builtins(res, cmd);
}

void	clean_fds(int fdin, int fdout)
{
	if (fdin != STDIN_FILENO && fdin != -1)
		close(fdin);
	if (fdout != STDOUT_FILENO && fdout != -1)
		close(fdout);
}

void	ft_error(char *where, char *what)
{
	char	*tmp;
	char	*err;

	tmp = ft_strjoin(where, what);
	if (!tmp)
	{
		ft_putstr_fd(where, 2);
		ft_putstr_fd(what, 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
	err = ft_strjoin(tmp, "\n");
	if (!err)
	{
		free(tmp);
		ft_putstr_fd(where, 2);
		ft_putstr_fd(what, 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
	free(tmp);
	ft_putstr_fd(err, 2);
	free(err);
}
