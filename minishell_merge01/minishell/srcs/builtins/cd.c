/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:17:35 by yachen            #+#    #+#             */
/*   Updated: 2023/11/27 15:49:23 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	go_to(t_list **envlist, char *var_name)
{
	t_list	*var;

	var = find_oldvar(var_name, *envlist, NULL);
	if (!var)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(var_name, 2);
		ft_putstr_fd(" not set", 2);
		return (-1);
	}
	if (chdir(var->content + (ft_strlen(var_name) + 1)) == -1)
	{
		perror("minishell: cd: go_to: chdir");
		return (-1);
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
		ft_putstr_fd("minishell: cd: too any arguments", 2);
		return (-1);
	}
	return (0);
}

static char	*ft_getcwd(void)
{
	char	*current_path;
	char	buffer[GETCWD_SIZE];

	current_path = NULL;
	current_path = ft_strdup(getcwd(buffer, GETCWD_SIZE));
	if (!current_path)
	{
		perror("minishell: cd: ft_getcwd");
		return (NULL);
	}
	return (current_path);
}

static void	update_path(t_list **list)
{
	t_list	*oldpwd_found;
	t_list	*pwd_found;

	oldpwd_found = find_oldvar("OLDPWD", *list, NULL);
	if (!oldpwd_found)
		return ;
	pwd_found = find_oldvar("PWD", *list, NULL);
	if (!pwd_found)
		return ;
	oldpwd_found->content = pwd_found->content;
	pwd_found->content = ft_getcwd();
}

int	ft_cd(t_list **envlist, t_list **explist, char **arg)
{
	if (check_arg(arg) == -1)
		return (1);
	else if (arg[1] == NULL)
	{
		if (go_to(envlist, "HOME") == -1)
			return (1);
	}
	else if (arg[1][0] == '-')
	{
		if (go_to(envlist, "OLDPWD") == -1)
			return (1);
	}
	else
	{
		if (chdir(arg[1]) == -1)
		{
			perror("minishell: cd: chdir");
			return (1);
		}
	}
	update_path(envlist);
	update_path(explist);
	return (0);
}

/*int	main(int argc, char **argv, char **env)
{
	t_list	*envlist;
	t_list	*explist;

	argc = argc + 1;
	envlist	= env_to_envlist(env);
	explist	= env_to_envlist(env);
	ft_cd(&envlist, &explist, argv);
	clear_lst(&envlist);
	clear_lst(&explist);
}*/