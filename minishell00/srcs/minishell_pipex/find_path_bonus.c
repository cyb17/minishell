/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:13:38 by yachen            #+#    #+#             */
/*   Updated: 2023/11/08 10:27:34 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

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
char	**find_path(char **env, char *cmd)
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
