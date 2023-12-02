/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:08:24 by yachen            #+#    #+#             */
/*   Updated: 2023/12/02 15:19:53 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	initialize_var(t_list **list, t_var *var, char *arg)
{
	var->list = list;
	var->oldvar = NULL;
	var->newvar = NULL;
	var->oldvar_i = 0;
	var->equal_i = find_caracter(arg, '=');
	var->plus_i = find_caracter(arg, '+');
}

static int	create_newvar(t_var *export, t_var *env, char *arg)
{
	export->newvar = ft_lstnew(ft_strdup(arg));
	if (!export->newvar || !export->newvar->content)
	{
		if (export->newvar)
			free(export->newvar);
		ft_putstr_fd("Error: create_newvar: malloc failed\n", 2);
		return (-1);
	}
	env->newvar = ft_lstnew(ft_strdup(arg));
	if (!env->newvar || !env->newvar->content)
	{
		free(export->newvar);
		if (env->newvar)
			free(env->newvar);
		ft_putstr_fd("Error: create_newvar: malloc failed\n", 2);
		return (-1);
	}
	return (0);
}

static void	update_two_list(t_var *export, t_var *env)
{
	ft_lstadd_back(export->list, export->newvar);
	if (env->equal_i >= 0)
		ft_lstadd_back(env->list, env->newvar);
	else
		free(env->newvar);
}

int	export_arg(t_list **envlist, t_list **explist, char *arg)
{
	t_var	export;
	t_var	env;

	initialize_var(explist, &export, arg);
	initialize_var(envlist, &env, arg);
	if (create_newvar(&export, &env, arg) == -1)
		return (-1);
	export.oldvar = find_oldvar(arg, *explist, &export.oldvar_i);
	if (!export.oldvar)
		update_two_list(&export, &env);
	else if (export.oldvar && export.equal_i >= 0)
	{
		env.oldvar = find_oldvar(arg, *envlist, &env.oldvar_i);
		if (export.equal_i == export.plus_i + 1)
		{
			if (join_and_update(&env, &export) == -1)
				return (-1);
			return(0);
		}
		if (replace_and_update(&env, &export) == -1)
			return (-1);
	}
	else
		free_newvar(&export, &env);
	return (0);
}

// Error = 1 || succes = 0
int	ft_export(t_list **envlist, t_list **explist, char **arg)
{
	int		i;
	t_list	*tmp;

	i = 1;
	tmp = NULL;
	if (!arg[1])
	{
		tmp = *explist;
		while (tmp)
		{
			printf("export : %s\n", (char *)tmp->content);
			tmp = tmp->next;
		}
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
