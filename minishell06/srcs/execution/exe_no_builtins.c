/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_no_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:41:08 by yachen            #+#    #+#             */
/*   Updated: 2023/12/21 19:01:46 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static int	find_len(t_tokens *cmd)
{
	int			len;
	t_tokens	*tokens;

	len = 0;
	tokens = cmd;
	while (tokens && (tokens->type == CMD || tokens->type == WORD))
	{
		len++;
		tokens = tokens->next;
	}
	return (len);
}

static char	**make_cmdtk_to_arg(t_tokens *cmd)
{
	int			i;
	char		**arg;

	arg = (char **)malloc(sizeof(char *) * (find_len(cmd) + 1));
	if (!arg)
	{
		ft_putstr_fd("Error: make_cmtk_to_arg: malloc failed\n", 2);
		return (NULL);
	}
	i = 0;
	while (cmd && (cmd->type == CMD || cmd->type == WORD))
	{
		arg[i] = ft_strdup(cmd->value);
		if (!arg[i])
		{
			free_tab(arg);
			ft_putstr_fd("Error: make_cmtk_to_arg: malloc failed\n", 2);
			return (NULL);
		}
		i++;
		cmd = cmd->next;
	}
	arg[i] = NULL;
	return (arg);
}

// allocate memory for my char **env
static char	**allocate_a_tab(t_list *envlist)
{
	int		i;
	t_list	*tmp;
	char	**env;

	i = 0;
	tmp = envlist;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		ft_putstr_fd("Error: list_to_tab: malloc failed\n", 2);
	return (env);
}

// Make a char **env with actual envlist to give to parsing_cmd as parameter
static char	**list_to_tab(t_list *envlist)
{
	int		i;
	t_list	*tmp;
	char	**env;

	env = allocate_a_tab(envlist);
	if (!env)
		return (NULL);
	i = 0;
	tmp = envlist;
	while (tmp)
	{
		env[i] = ft_strdup(tmp->content);
		if (!env[i])
		{
			ft_putstr_fd("Error: list_to_tab: env[i]: malloc failed\n", 2);
			free_tab(env);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

// static void handler(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		return ;
// 	}
// }

int	exe_no_builtins(t_res *res, t_tokens *cmd)
{
	char	**arg;
	char	*path;
	char	**env;

	env = list_to_tab(res->blt->envlist);
	if (!env[0] && res->blt->envlist)
		return (-1);
	arg = make_cmdtk_to_arg(cmd);
	if (!arg)
	{
		free_tab(env);
		return (-1);
	}
	path = parsing_cmd(env, arg);
	if (!path)
	{
		free_tab(env);
		free_tab(arg);
		garbage_collector_child(res);
		exit(g_signal);
	}
	// if (res->prcs->pid == 0)
	// 	signal(SIGINT, handler);
	if (ft_execve(env, path, arg) == -1)
		return (-1);
	return (0);
}
