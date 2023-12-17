/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:17:35 by yachen            #+#    #+#             */
/*   Updated: 2023/12/16 15:58:47 by yachen           ###   ########.fr       */
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
		ft_putstr_fd("minishell: cd: too any arguments\n", 2);
		return (-1);
	}
	return (0);
}

static char	*ft_getcwd(void)
{
	char	*tmp;
	char	*current_path;
	char	buffer[GETCWD_SIZE];

	tmp = getcwd(buffer, GETCWD_SIZE);
	if (!tmp)
	{
		perror("Error: cd: ft_getcwd");
		return (NULL);
	}
	current_path = ft_strdup(tmp);
	if (!current_path)
	{
		perror("Error: cd: ft_getcwd");
		return (NULL);
	}
	return (current_path);
}

static void	update_path(t_list **list, char *oldpwd)
{
	t_list	*oldpwd_found;
	t_list	*pwd_found;

	oldpwd_found = find_oldvar("OLDPWD", *list, NULL);
	if (!oldpwd_found)
		ft_putstr_fd("OLDPWD not update because variable not found\n", 2);
	else
	{
		oldpwd_found->content = ft_strjoin("OLDPWD=", oldpwd);
		if (!oldpwd_found->content)
			ft_putstr_fd("Error: update OLDPWD: ft_strjoin: malloc failed\n",2);
	}
	pwd_found = find_oldvar("PWD", *list, NULL);
	if (!pwd_found)
		ft_putstr_fd("PWD not update because variable not found\n", 2);
	else
	{
		pwd_found->content = ft_strjoin("PWD=", ft_getcwd());
		if (!pwd_found->content)
			ft_putstr_fd("Error: update PWD: ft_strjoin: malloc failed\n",2);
	}
}

// Error = 1 || succes = 0
int	ft_cd(t_list **envlist, t_list **explist, char **arg)
{
	int		rslt;
	char	*oldpwd;

	oldpwd = ft_getcwd();
	if (check_arg(arg) == -1 || !oldpwd)
		return (1);
	if (arg[1] == NULL)
		rslt = go_to(envlist, "HOME");
	else if (arg[1][0] == '-')
		rslt = go_to(envlist, "OLDPWD");
	else
	{
		rslt = chdir(arg[1]);
		if (rslt == -1)
			perror("minishell: cd: chdir");
	}
	if (rslt == -1)
		return (1);
	update_path(envlist, oldpwd);
	update_path(explist, oldpwd);
	return (0);
}
