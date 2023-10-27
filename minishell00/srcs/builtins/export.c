/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:02:28 by yachen            #+#    #+#             */
/*   Updated: 2023/10/27 20:06:45 by yachen           ###   ########.fr       */
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

static void	initialize_var(t_var *export, t_var *env)
{
	export->oldvar = NULL;
	export->newvar = NULL;
	export->oldvar_i = 0;
	env->oldvar = NULL;
	env->newvar = NULL;
	env->oldvar_i = 0;
}

static void	print_explist(t_list *explist)
{
	t_list	*tmp;
	
	tmp = explist;
	while (tmp)
	{
		printf("export : %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

static int	create_newvar(char *arg, t_var *env, t_var *export)
{
	export->newvar = ft_lstnew(arg);
	if (!export->newvar)
	{
		write(2, "export: create_newvar: malloc failed", 31);
		return (-1);
	}
	env->newvar = ft_lstnew(arg);
	if (!env->newvar)
	{
		free(export->newvar);
		write(2, "export: create_newvar: malloc failed", 31);
		return (-1);
	}
	return (0);
}

static void	free_var(t_var *export, t_var *env)
{
	free(export->newvar);
	free(env->newvar);
}

static void	add_tolist(t_list *envlist, t_var *env, char *arg)
{
	if (find_caracter(arg, '=') >= 0)
		ft_lstadd_back(&envlist, env->newvar);
	else
		free(env->newvar);
}
static void	replace_var(t_list *envlst, t_list *explst, t_var *env, t_var *exp)
{
	replace(envlst, env->newvar, env->oldvar_i);
	replace(explst, exp->newvar, exp->oldvar_i);
}

int	ft_export(t_list *envlist, t_list *explist, char *arg)
{
	t_var	export;
	t_var	env;
	
	initialize_var(&export, &env);
	if (!arg)
		print_explist(explist);
	else
	{
		if (create_newvar(arg, &export, &env) == -1)
			return (1);
		export.oldvar = find_oldvar(arg, explist, &export.oldvar_i);
		if (!export.oldvar)
		{	
			ft_lstadd_back(&explist, export.newvar);
			add_tolist(envlist, &env, arg);
		}
		else if (export.oldvar && find_caracter(arg, '=') >= 0)
		{
			env.oldvar = find_oldvar(arg, envlist, &env.oldvar_i);
			replace_var(envlist, explist, &env, &export);
		}
		else
			free_var(&export, &env);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
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
	ft_export(envlist, explist, "SHELL=valeur");
	ft_export(envlist, explist, "test3=");
	ft_unset(envlist, explist, "test");
	ft_unset(envlist, explist, "test1=");
	ft_unset(envlist, explist, "te");
	ft_env(envlist);
	printf("\n\n");
	ft_env(explist);
	free(envlist);
	free(explist);
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
