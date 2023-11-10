/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:59:17 by yachen            #+#    #+#             */
/*   Updated: 2023/11/08 10:27:34 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

/* split cmd and options in char **
return NULL if ft_split failed */
char	**make_cmd(char *str)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	if (!cmd)
		return (NULL);
	return (cmd);
}

/* return 0 if cmd is "" | "   " */
int	check_cmd(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (!cmd[i])
		return (0);
	return (1);
}

char	*sub_parsing_cmd1(char **split_cmd)
{
	char	*path;

	if (!split_cmd)
		return (NULL);
	path = NULL;
	if (access(split_cmd[0], F_OK | R_OK | X_OK) == -1)
		ft_printf("Error: %s: no such file or directory\n", split_cmd[0]);
	else
		path = ft_strdup(split_cmd[0]);
	free_tab(split_cmd);
	return (path);
}

char	*sub_parsing_cmd2(char **env_main, char **env_exev, char *cmd)
{
	int		i;
	char	*path;
	char	**env_path;

	env_path = find_path(env_main, cmd);
	if (!env_path)
		env_path = find_path(env_exev, cmd);
	i = 0;
	while (env_path[i] && access(env_path[i], F_OK | R_OK | X_OK) == -1)
		i++;
	if (!(env_path[i]))
	{
		ft_printf("Error: %s: Command not found\n", cmd);
		free_tab(env_path);
		return (NULL);
	}
	path = ft_strdup(env_path[i]);
	free_tab(env_path);
	return (path);
}

/* if cmd start with /../..cmd, use sub_parsing_cmd1
else use sub_parsing_cmd2 
return NULL if there is any error*/
char	*parsing_cmd(char **env_main, char *cmd, char **env_exev)
{
	char	**split_cmd;
	char	*path;

	if (check_cmd(cmd) == 0)
	{
		ft_printf("Error : %s: Command not found\n", cmd);
		return (NULL);
	}
	split_cmd = make_cmd(cmd);
	path = NULL;
	if (cmd[0] == '/')
	{
		path = sub_parsing_cmd1(split_cmd);
		return (path);
	}
	path = sub_parsing_cmd2(env_main, env_exev, split_cmd[0]);
	free_tab(split_cmd);
	return (path);
}
