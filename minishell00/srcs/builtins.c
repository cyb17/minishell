/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:02:28 by yachen            #+#    #+#             */
/*   Updated: 2023/10/24 18:05:42 by yachen           ###   ########.fr       */
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

void	clear_lst(t_list **lst)
{
	t_list	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}

t_list	*env_to_envlist(char **env)
{
	int		i;
	t_list	*envlist;
	t_list	*tmp;

	i = 0;
	envlist = NULL;
	while (env[i])
	{
		tmp = ft_lstnew(env[i]);
		if (!tmp)
		{
			clear_lst(&envlist);
			return (NULL);
		}
		ft_lstadd_back(&envlist, tmp);
		i++;
	}
	return (envlist);
}

void	ft_env(t_list *envlist)
{
	t_list	*tmp;

	tmp = envlist;
	while (tmp != NULL)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	clear_lst(&envlist);
}

int	str_cmp(char *model, char *str_tocmp)
{
	int	i;

	i = 0;
	while (model[i])
	{
		if (str_tocmp[i] != model[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(t_list *envlist, char *varto_unset)
{
	int		i;
	t_list	*tmp;
	t_list	*tmp2;

	if (!varto_unset)
		return ;
	i = 0;
	tmp = envlist;
	tmp2 = envlist;
	while (tmp != NULL)
	{
		if (str_cmp(varto_unset, (char *)(tmp)->content) == 1)
		{
			while (i-- > 0)
				(tmp2)++;
			(tmp2)->next = tmp->next;
			printf("%s\n", (char *)tmp->content);
			free(tmp);
			return ;
		}
		tmp = tmp->next;
		i++;
	}
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
	t_list	*envlist;

	printf("teste : %d %s\n", argc, argv[0]);
	envlist = env_to_envlist(env);
	ft_env(envlist);
	printf("\n");
	ft_unset(envlist, "HOME");
	printf("\n");
	ft_env(envlist);
	return (0);
}
