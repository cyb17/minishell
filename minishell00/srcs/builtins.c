/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:02:28 by yachen            #+#    #+#             */
/*   Updated: 2023/10/26 17:48:40 by yachen           ###   ########.fr       */
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

// fonction transforme le tableau d'env en liste chaine
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

int	stringncmp(char *model, char *str, int n)
{
	int	i;

	i = 0;
	while (((model[i]) || (str[i])) && i <= n)
	{
		if (model[i] != str[i])
			return (-1);
		i++;
	}
	return (1);
}

/* fonction retourne la place de la variable a ajouter dans la liste
si il la trouve */
int	find_var(char *var, t_list *list)
{
	t_list	*current;
	int		i;
	int		n;

	current = list;
	i = 0;
	n = find_caracter(var, '=');
	if (n < 0)
		n = ft_strlen(var);
	while (current)
	{
		if (stringncmp(var, current->content, n) == 1)
			return (i);
		i++;
		current = current->next;
	}
	return (-1);
}

void	replace(t_list *list, t_list *new_var, int old_var)
{
	t_list	*current;
	t_list	*tmp;
	int		j;

	current = list;
	j = 0;
	if (old_var == 0)
	{
		new_var->next = list->next;
		list = new_var;
		free(current);
		return ;
	}
	while (j++ < old_var - 1)
		current = current->next;
	tmp = current->next;
	new_var->next = tmp->next;
	current->next = new_var;
	free(tmp);
}

void	add_to_list(char *exp_content, t_list *list, t_list *new_var)
{
	int		i;

	i = 0;
	i = find_var(exp_content, list);
	if (i == -1)
		ft_lstadd_back(&list, new_var);
	else
		replace(list, new_var, i);
}

int	ft_export(t_list *envlist, t_list *explist, char *exp_content)
{
	t_list	*new_var;
	int		equal;
	int		i;

	equal = 0;
	i = 0;
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
	equal = find_caracter(exp_content, '=');
	if (equal != -1)
		add_to_list(exp_content, envlist, new_var);
	if (find_var(exp_content, explist) == -1)
		add_to_list(exp_content, explist, new_var);
	return (0);
}

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

int	main(int argc, char **argv, char **env)
{
	t_list	*envlist;
	t_list	*explist;
	int		i;

	i = 0;
	printf("teste : %d %s\n", argc, argv[0]);
	envlist = env_to_envlist(env);
	explist = env_to_envlist(env);

	printf("print env list : \n");
	ft_env(envlist);
	printf("\n\n");
	ft_export(envlist, explist, "test=valeur");
	printf("\n\n");
	ft_export(envlist, explist, "test1=");
	ft_export(envlist, explist, "test2");
	ft_env(envlist);
	printf("\n\n");
	ft_env(explist);
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
