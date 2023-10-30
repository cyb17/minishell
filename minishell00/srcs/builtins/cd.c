/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:17:35 by yachen            #+#    #+#             */
/*   Updated: 2023/10/30 16:29:44 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

char	*get_envhome(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("-minishell: ft_cd: HOME not set\n", 2);
		return (NULL);
	}
	return (home += 5);1
}

char	*get_envpwd(char *oldpwd)
{
	char	*pwd;

	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
	{
	}
	pwd = getenv("PWD");
}

int	ft_cd(char *path)
{
	char	*home;
	char	*oldpwd;
	char	*pwd;

	oldpwd = NULL;
	if (!path)
	{
		home = get_envhome();
		if (!home)
			return (1);
		chdir(home);
		return (0);
	}
	pwd = get_envpwd(oldpwd);
	return (0);
}