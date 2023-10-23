/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:02:28 by yachen            #+#    #+#             */
/*   Updated: 2023/10/23 18:42:53 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char *op, char *str)
{
	if (str)
		printf("%s", str);
	if (!op)
		printf("\n");
}

t_list	env_to_envlist(char **env)
{
	int	i;

	i = 0;

}

void	ft_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}

/*char	*get_envhome(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("-minishell: ft_cd: HOME not set\n", 2);
		return (NULL);
	}
	return (home += 5);
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
}*/

int	main(int argc, char **argv, char **env)
{
	printf("%d %s\n", argc, argv[0]);
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}
