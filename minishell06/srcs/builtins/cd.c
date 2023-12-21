/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:17:35 by yachen            #+#    #+#             */
/*   Updated: 2023/12/21 15:13:28 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	go_to(t_list **envlist, char *var_name)
{
	t_list	*var;
	t_list	*tmp;

	tmp = *envlist;
	var = find_oldvar(var_name, tmp, NULL);
	if (!var)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(var_name, 2);
		ft_putstr_fd(" not set\n", 2);
		return (1);
	}
	if (chdir(var->content + (ft_strlen(var_name) + 1)) == -1)
	{
		perror("minishell: cd: go_to: chdir");
		return (1);
	}
	return (0);
}

static int	check_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: too any arguments\n", 2);
		return (1);
	}
	return (0);
}

// If getcwd == NULL, return a empty string "\0"
static char	*ft_getcwd(void)
{
	char	*tmp;
	char	*current_path;
	char	buffer[GETCWD_SIZE];

	tmp = getcwd(buffer, GETCWD_SIZE);
	if (!tmp)
		current_path = ft_strdup("");
	else
		current_path = ft_strdup(tmp);
	return (current_path);
}

static void	update_path(t_list **list, char *oldpwd, char *pwd)
{
	t_list	*oldpwd_found;
	t_list	*pwd_found;

	if (oldpwd && oldpwd[0] != '\0')
	{
		oldpwd_found = find_oldvar("OLDPWD", *list, NULL);
		if (oldpwd_found)
		{
			free(oldpwd_found->content);
			oldpwd_found->content = ft_strjoin("OLDPWD=", oldpwd);
			if (!oldpwd_found->content)
				ft_putstr_fd("Error: update OLDPWD: malloc failed\n", 2);
		}
	}
	if (pwd && pwd[0] != '\0')
	{
		pwd_found = find_oldvar("PWD", *list, NULL);
		if (pwd_found)
		{
			free(pwd_found->content);
			pwd_found->content = ft_strjoin("PWD=", pwd);
			if (!pwd_found->content)
				ft_putstr_fd("Error: update PWD: malloc failed\n", 2);
		}
	}
}

// Error = 1 || succes = 0
int	ft_cd(t_list **envlist, t_list **explist, t_builtins *blt)
{
	int		rslt;

	rslt = 0;
	if (check_arg(blt->arg) == -1)
		return (1);
	blt->oldpwd = ft_getcwd();
	if (blt->arg[1] == NULL)
		rslt = go_to(envlist, "HOME");
	else if (blt->arg[1][0] == '-')
		rslt = go_to(envlist, "OLDPWD");
	else
	{
		rslt = chdir(blt->arg[1]);
		if (rslt == -1)
			perror("Error: ft_cd: chdir");
	}
	if (rslt == 0)
	{
		blt->pwd = ft_getcwd();
		update_path(envlist, blt->oldpwd, blt->pwd);
		update_path(explist, blt->oldpwd, blt->pwd);
		free(blt->pwd);
	}
	free(blt->oldpwd);
	return (rslt);
}
