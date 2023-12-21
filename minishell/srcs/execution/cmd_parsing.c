/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:59:17 by yachen            #+#    #+#             */
/*   Updated: 2023/12/21 15:07:03 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

/* join str to each tab[i] of char **tab 
return -1 if ft_strjoin failed */
static int	tab_strjoin(char **tab, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		tmp = tab[i];
		tab[i] = ft_strjoin(tab[i], str);
		if (!tab[i])
		{
			free(tmp);
			free_tab(tab);
			return (-1);
		}
		free(tmp);
		i++;
	}
	return (0);
}

/* find and split environnement variable PATH, than join each path with "/cmd"
return NULL if (PATH don't find | ft_split failed * | tab_join failed */
static char	**find_path(char **env, char *cmd)
{
	int		i;
	char	**path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (!env[i])
		return (NULL);
	path = ft_split(env[i] + 5, ':');
	if (!path)
		return (NULL);
	if ((tab_strjoin(path, "/") == -1)
		|| (tab_strjoin(path, cmd) == -1))
	{
		free_tab(path);
		return (NULL);
	}
	return (path);
}

// Check if cmd[0] is accessible and executable
static char	*sub_parsing_cmd1(char *cmd)
{
	char	*path;

	if (!cmd)
		return (NULL);
	path = NULL;
	if (access(cmd, F_OK | R_OK | X_OK) == -1)
	{
		g_signal = 126;
		perror("Error");
	}
	else
		path = ft_strdup(cmd);
	return (path);
}

static char	*sub_parsing_cmd2(char **env_main, char *cmd)
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
char	*parsing_cmd(char **env_main, char **cmd)
{
	char	*path;

	path = NULL;
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
	{
		path = sub_parsing_cmd1(cmd[0]);
		return (path);
	}
	path = sub_parsing_cmd2(env_main, cmd[0]);
	if (!path)
		g_signal = 1;
	return (path);
}
