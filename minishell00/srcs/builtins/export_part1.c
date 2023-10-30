/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:08:24 by yachen            #+#    #+#             */
/*   Updated: 2023/10/30 16:30:11 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

void	initialize_var(t_var *export, t_var *env)
{
	export->oldvar = NULL;
	export->newvar = NULL;
	export->oldvar_i = 0;
	env->oldvar = NULL;
	env->newvar = NULL;
	env->oldvar_i = 0;
}

void	print_explist(t_list *explist)
{
	t_list	*tmp;

	tmp = explist;
	while (tmp)
	{
		printf("export : %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

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
int	ft_export(t_list **envlist, t_list **explist, char *arg)
{
	t_var	export;
	t_var	env;

	initialize_var(&export, &env);
	if (!arg)
		print_explist(*explist);
	else
	{
		if (create_newvar(arg, &export, &env) == -1)
			return (1);
		export.oldvar = find_oldvar(arg, *explist, &export.oldvar_i);
		if (!export.oldvar)
		{	
			ft_lstadd_back(explist, export.newvar);
			add_tolist(envlist, &env, arg);
		}
		else if (export.oldvar && find_caracter(arg, '=') >= 0)
		{
			env.oldvar = find_oldvar(arg, *envlist, &env.oldvar_i);
			replace_var(envlist, explist, &env, &export);
		}
		else
			free_var(&export, &env);
	}
	return (0);
}