/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_no_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:41:08 by yachen            #+#    #+#             */
/*   Updated: 2023/12/02 15:34:52 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// Parse cmd and find path for execution
char	*find_execve_path(t_res *res, char **env, char *argv_value)
{
	char	*path;

	path = parsing_cmd(env, argv_value);
	if (!path)
	{
		garbage_collector(res);
		free(argv_value);
		exit (1);
	}
	return (path);
}

// Execute the command
void	ft_execve(t_res *res, char **env, char *path, char *argv_value)
{
	char	**cmd;

	cmd = make_cmd(argv_value);
	if (execve(path, cmd, env) == -1)
	{
		perror("Error: execve");
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		garbage_collector(res);
		free(path);
		free(argv_value);
		exit (1);
	}
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

static char	**list_to_tab(t_list *envlist)
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
	if(!env)
	{
		ft_putstr_fd("Error: list_to_tab: malloc failed\n", 2);
		return (NULL);
	}
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
		return (1);
	arg = make_cmdtk_to_arg(cmd);
	if (!arg)
		return (1);
	path = find_execve_path(res, env, arg);
	ft_execve(res, env, path, arg);
	return (0);
}
