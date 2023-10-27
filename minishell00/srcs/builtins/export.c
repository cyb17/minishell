/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:02:28 by yachen            #+#    #+#             */
/*   Updated: 2023/10/27 14:01:34 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// fonction retourne l'indice du caractere trouve
int	find_caracter(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	stringcmp(char *model, char *str)
{
	int	i;

	i = 0;
	while (model[i] && model[i] != '=')
	{
		if (model[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}

t_list	*find_oldvar(char *var, t_list *list, int *i)
{
	t_list	*current;

	current = list;
	while (current)
	{
		if (stringcmp(var, current->content) == 1)
			return (current);
		(*i)++;
		current = current->next;
	}
	return (NULL);
}

void	replace(t_list *list, t_list *newvar, int oldvar_i)
{
	int	i;
	t_list	*tmp;
	t_list	*current;

	i = 0;
	tmp = NULL;
	current = list;
	if (oldvar_i == 0)
	{
		list = newvar;
		newvar->next = current->next;
		free(current);
		return ;
	}
	while (i < oldvar_i)
	{
		tmp = current;
		current = current->next;
		i++;
	}
	tmp->next = newvar;
	newvar->next = current->next;
	free(current);
}

t_list	*create_newvar(char *arg)
{
	t_list	*newvar;

	newvar = ft_lstnew(arg);
	if (!newvar)
	{
		free(newvar);
		write(2, "export: create_newvar: malloc failed", 31);
		return (NULL);
	}
	return (newvar);
}

int	ft_export(t_list *envlist, t_list *explist, char *arg)
{
	t_list	*newvar_exp;
	t_list	*newvar_env;
	t_list	*oldvar_env;
	t_list	*oldvar_exp;
	int		oldvarenv_i;
	int		oldvarexp_i;

	oldvarenv_i = 0;
	oldvarexp_i = 0;
	if (!arg)
	{
		ft_env(explist);
		return (0);
	}
	newvar_exp = create_newvar(arg);
	if (!newvar_exp)
		return (1);
	newvar_env = create_newvar(arg);
	if (!newvar_env)
	{
		free(newvar_exp);
		return (1);
	}
	oldvar_exp = find_oldvar(arg, explist, &oldvarexp_i);
	if (!oldvar_exp)
	{	
		ft_lstadd_back(&explist, newvar_exp);
		if (find_caracter(arg, '=') >= 0)
			ft_lstadd_back(&envlist, newvar_env);
		else
			free(newvar_env);
	}
	else if (oldvar_exp && find_caracter(arg, '=') >= 0)
	{
		oldvar_env = find_oldvar(arg, envlist, &oldvarenv_i);
		replace(envlist, newvar_env, oldvarenv_i);
		replace(explist, newvar_exp, oldvarexp_i);
	}
	else
	{
		free(newvar_exp);
		free(newvar_env);
	}
	return (0);
}

/*int	main(int argc, char **argv, char **env)
{
	t_list	*envlist;
	t_list	*explist;

	printf("teste : %d %s\n", argc, argv[0]);
	envlist = env_to_envlist(env);
	explist = env_to_envlist(env);

	printf("print env list : \n");
	ft_env(envlist);
	printf("\n\n");
	ft_export(envlist, explist, "test");
	printf("\n\n");
	ft_export(envlist, explist, "test1=");
	ft_export(envlist, explist, "test2");
	ft_export(envlist, explist, "LSCOLORS=valeur");
	ft_export(envlist, explist, "test");
	ft_export(envlist, explist, "test3=");
	ft_env(envlist);
	printf("\n\n");
	ft_env(explist);
	free(envlist);
	free(explist);
	return (0);
}*/

/*void	ft_unset(t_list *envlist, char *varto_unset)
{
	t_list	*current;
	t_list	*tmp;

	if ((!varto_unset) || (find_equal(varto_unset, '=')) > 0)
		return ;
	current = NULL;
	current = envlist;
	printf("%s\n", (char *)current->content);
	if (str_cmp(varto_unset, current->content) == 1 && current->next == NULL)
	{
		envlist = NULL;
		free(current);
		return ;
	}
	tmp = NULL;
	while (current)
	{
		if (str_cmp(varto_unset, current->content) == 1
			&& find_equal(current->content, '=') == 0)
		{
			tmp->next = current->next;
			if (tmp->content == NULL)
				envlist = tmp->next;
			else
				envlist = tmp;
			free(current);
			return ;
		}
		tmp = current;
		current = current->next;
	}
}*/


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
