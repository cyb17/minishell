/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:02:28 by yachen            #+#    #+#             */
/*   Updated: 2023/10/25 17:36:06 by yachen           ###   ########.fr       */
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
}

int	str_cmp(char *model, char *str_tocmp)
{
	int	i;

	i = 0;
	while (model[i] && model[i - 1] != '=')
	{
		if (str_tocmp[i] != model[i])
			return (0);
		i++;
	}
	return (1);
}

int	find_equal(char *str, char equal)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == equal)
			return (i);
		i++;
	}
	return (0);
}

t_list	*ft_unset(t_list *envlist, char *varto_unset)
{
	t_list	*current;
	t_list	*tmp;

	if ((!varto_unset) || (find_equal(varto_unset, '=')) > 0)
		return (envlist);
	current = envlist;
	if (str_cmp(varto_unset, current->content) == 1 && current->next == NULL)
	{
		free(current);
		return (NULL);
	}
	tmp = NULL;
	while (current)
	{
		if (str_cmp(varto_unset, current->content) == 1)
		{
			tmp->next = current->next;
			free(current);
			if (tmp->content == NULL)
				return (tmp->next);
			return (tmp);
		}
		tmp = current;
		current = current->next;
	}
	return (envlist);
}

int	ft_export(t_list *envlist, t_list *explist, char *exp_content)
{
	t_list	*new_var;
	t_list	*current;
	t_list	*tmp;
	
	if (!exp_content)
	{
		ft_env(explist);
		return (0);
	}
	new_var = ft_lstnew(exp_content);
	if (!new_var)
	{
		write(2, "export: new_var: malloc failed", 32);
		return (1);
	}
	current = envlist;
	if (find_equal(exp_content, '=') > 0)
	{
		while (current)
		{
			if(str_cmp(exp_content, current->content) == 1)
			{
				new_var->next = current->next;
				tmp->next = new_var;
				free(current);
				break ;
			}
			tmp = current;
			current = current->next;
		}
		if (!current)
			ft_lstadd_back(&envlist, new_var);
	}
	ft_lstadd_back(&explist, new_var);
	return (0);
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
}*/

int	main(int argc, char **argv, char **env)
{
	t_list	*envlist;
	t_list	*explist;

	printf("teste : %d %s\n", argc, argv[0]);
	envlist = env_to_envlist(env);
	explist = env_to_envlist(env);
	/*printf("print env list : \n\n");
	ft_env(envlist);
	printf("---------------------------------------------");
	printf("\n");
	printf("print env with unset SHELL\n\n");
*/	envlist = ft_unset(envlist, "SHELL");
	ft_env(envlist);
//	printf("---------------------------------------------");
//	printf("\n");
/*	ft_export(envlist, explist, "HOME=valeur");
	ft_env(envlist);
	printf("print env list with export HOME=valeur\n");
	printf("---------------------");
	printf("\n");
	printf("print env list with export ""\n");
	ft_export(envlist, explist, NULL);
*/	return (0);
}
