/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_no_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:41:08 by yachen            #+#    #+#             */
/*   Updated: 2023/12/13 12:37:09 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// Join 2 tokens with a space between them
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

// Make cmd_tk to a char * to give to parsing_cmd as parameter
static char	*make_cmdtk_to_arg(t_tokens *tokens)
{
	char		*tmp;
	char		*cmd;

	cmd = NULL;
	while (tokens && (tokens->type == CMD || tokens->type == WORD))
	{
		tmp = cmd;
		cmd = join_cmd_and_option(cmd, tokens->value);
		if (tmp)
			free(tmp);
		if (!cmd)
		{
			ft_putstr_fd("Error: make_cmtk_to_arg: malloc failed\n", 2);
			return (NULL);
		}
		tokens = tokens->next;
	}
	return (cmd);
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

int	exe_no_builtins(t_res *res, t_tokens *cmd)
{
	char	*arg;
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
		free(arg);
		garbage_collector_child(res);
		exit(g_signal);
	}
	if (ft_execve(env, path, arg) == -1)
		return (-1);
	return (0);
}
