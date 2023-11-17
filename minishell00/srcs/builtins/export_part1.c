/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:08:24 by yachen            #+#    #+#             */
/*   Updated: 2023/11/17 11:39:07 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int	create_newvar(char *arg, t_var *env, t_var *export)
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

void	modifie_var(t_var *env, t_var *exp, int i)
{
	char	*tmp;

	tmp = env->oldvar->content;
	if (*(char *)(env->newvar->content + i) != '\0')
	{
		env->oldvar->content = ft_strjoin(tmp, env->newvar->content + i);
		if (!env->oldvar->content)
		{
			ft_putstr_fd("Error: modfie_var: malloc failed\n", 2);
			return ;
		}
		free(tmp);
	}
	tmp = exp->oldvar->content;
	if (*(char *)(exp->newvar->content + i) != '\0')
	{
		exp->oldvar->content = ft_strjoin(tmp, exp->newvar->content + i);
		if (!exp->oldvar->content)
		{
			ft_putstr_fd("Error: modfie_var: malloc failed\n", 2);
			return ;
		}
		free(tmp);
	}
	free_newvar(exp, env);
}

void	replace(t_list **list, t_list *newvar, int oldvar_i)
{
	int		i;
	t_list	*tmp;
	t_list	*current;

	i = 0;
	tmp = NULL;
	current = *list;
	if (oldvar_i == 0)
	{
		newvar->next = (current)->next;
		*list = newvar;
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

int	export_arg(t_list **envlist, t_list **explist, char *arg)
{
	t_var	export;
	t_var	env;

	initialize_var(&export, &env);
	if (create_newvar(arg, &export, &env) == -1)
		return (-1);
	export.oldvar = find_oldvar(arg, *explist, &export.oldvar_i);
	if (!export.oldvar)
	{	
		ft_lstadd_back(explist, export.newvar);
		if_addto_env(envlist, &env, arg);
	}
	else if (export.oldvar && find_caracter(arg, '=') >= 0)
	{
		env.oldvar = find_oldvar(arg, *envlist, &env.oldvar_i);
		if (find_caracter(arg, '=') == find_caracter(arg, '+') + 1)
			modifie_var(&env, &export, find_caracter(arg, '=') + 1);
		else
			replace_var(envlist, explist, &env, &export);
	}
	else
		free_newvar(&export, &env);
	return (0);
}

int	ft_export(t_list **envlist, t_list **explist, char **arg)
{
	int	i;

	i = 1;
	if (!arg[1])
	{
		print_explist(*explist);
		return (0);
	}
	while (arg[i])
	{
		if (export_arg(envlist, explist, arg[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

/*int	main(int argc, char **argv, char **env)
{
	t_list	*envlist;
	t_list	*explist;

	envlist = NULL;
	explist = NULL;
	(void)argc;
	envlist = env_to_envlist(env);
	explist = env_to_envlist(env);

	printf("print env list : \n");
	ft_env(argv + (argc - 1), envlist);
	printf("\n\n");
	ft_export(&envlist, &explist, argv + 1);
	printf("\n\n");
	// ft_unset(&envlist, &explist, "test");
	// ft_unset(&envlist, &explist, "test1=");
	// ft_unset(&envlist, &explist, "te");
	// ft_unset(&envlist, &explist, "SHELL");
	ft_env(argv + (argc - 1), envlist);
	// printf("\n\n");
	// ft_unset(&envlist, &explist, NULL);
	// ft_export(&envlist, &explist, NULL);
	// ft_pwd();
	clear_lst(&envlist);
	clear_lst(&explist);
	return (0);
}*/