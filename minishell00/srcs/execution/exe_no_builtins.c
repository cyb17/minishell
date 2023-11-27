/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_no_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:41:08 by yachen            #+#    #+#             */
/*   Updated: 2023/11/27 15:44:25 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// Parse cmd and find path for execution
char	*find_execve_path(t_res *res, char **env, char *argv_value)
{
	char	*path;
	char	*env_exev[2];

	env_exev[0] = "PATH=/mnt/nfs/homes/yachen/bin:/usr/local/sbin:\
	/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	env_exev[1] = NULL;
	path = parsing_cmd(env, argv_value, env_exev);
	if (!path)
	{
		garbage_collector(res);
		free(argv_value);
		exit (1);
	}
	return (path);
}

// Execute the command
void	ft_execve(t_res *res, char *path, char *argv_value)
{
	char	**cmd;

	cmd = make_cmd(argv_value);
	if (execve(path, cmd, NULL) == -1)
	{
		perror("Error: execve");
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
			return (NULL);
		tokens = tokens->next;
	}
	return (cmd);
}

void	exe_no_builtins(t_res *res, char **env, t_tokens *cmd)
{
	char	*arg;
	char	*path;

	arg = make_cmdtk_to_arg(cmd);
	path = find_execve_path(res, env, arg);
	ft_execve(res, path, arg);
}
