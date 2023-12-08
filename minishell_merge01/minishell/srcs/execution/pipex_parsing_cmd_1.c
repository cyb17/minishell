/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing_cmd_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:59:17 by yachen            #+#    #+#             */
/*   Updated: 2023/12/08 16:23:47 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// Check if cmd[0] is accessible and executable
char	*sub_parsing_cmd1(char **split_cmd)
{
	char	*path;

	if (!split_cmd)
		return (NULL);
	path = NULL;
	if (access(split_cmd[0], F_OK | R_OK | X_OK) == -1)
	{
		g_signal[0] = 126;
		perror("Error");
	}
	else
		path = ft_strdup(split_cmd[0]);
	free_tab(split_cmd);
	return (path);
}

char	*sub_parsing_cmd2(char **env_main, char *cmd)
{
	int		i;
	char	*path;
	char	**env_path;

	env_path = find_path(env_main, cmd);
	if (!env_path)
	{
		ft_putstr_fd("Error: variable PATH not found\n", 2);
		return (NULL);
	}
	i = 0;
	while (env_path[i] && access(env_path[i], F_OK | R_OK | X_OK) == -1)
		i++;
	if (!(env_path[i]))
	{
		ft_putstr_fd("Error : ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Command not found\n", 2);
		free_tab(env_path);
		return (NULL);
	}
	path = ft_strdup(env_path[i]);
	free_tab(env_path);
	return (path);
}

/* if cmd start with /../..cmd or ./cmd, use sub_parsing_cmd1
else use sub_parsing_cmd2 
return NULL if there is any error*/
char	*parsing_cmd(char **env_main, char *cmd)
{
	char	**split_cmd;
	char	*path;

	if (check_cmd(cmd) == 0)
	{
		ft_putstr_fd("Error : ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Command not found\n", 2);
		g_signal[0] = 127;
		return (NULL);
	}
	split_cmd = make_cmd(cmd);
	path = NULL;
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		path = sub_parsing_cmd1(split_cmd);
		return (path);
	}
	path = sub_parsing_cmd2(env_main, split_cmd[0]);
	if (!path)
		g_signal[0] = 1;
	free_tab(split_cmd);
	return (path);
}
