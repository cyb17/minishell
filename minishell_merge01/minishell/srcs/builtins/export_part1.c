/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:08:24 by yachen            #+#    #+#             */
/*   Updated: 2023/12/01 16:40:09 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	create_newvar(char *arg, t_var *env, t_var *export)
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

// Joint newvar's value to oldvar's value, but need condition: oldvar != NULL
int	join_newvar_oldvar(t_var *var, int i)
{
	char	*tmp;

	tmp = var->oldvar->content;
	if (*(char *)(var->newvar->content + i) != '\0')
	{
		var->oldvar->content = ft_strjoin(tmp, var->newvar->content + i);
		if (!var->oldvar->content)
		{
			ft_putstr_fd("Error: joint_newvar_oldvar: malloc failed\n", 2);
			return (-1);
		}
		free(tmp);
	}
	return (0);
}

// void	modifie_var(t_var *env, t_var *exp, int i)
// {
// 	char	*tmp;

// 	tmp = env->oldvar->content;
// 	if (*(char *)(env->newvar->content + i) != '\0')
// 	{
// 		env->oldvar->content = ft_strjoin(tmp, env->newvar->content + i);
// 		if (!env->oldvar->content)
// 		{
// 			ft_putstr_fd("Error: modfie_var: malloc failed\n", 2);
// 			return ;
// 		}
// 		free(tmp);
// 	}
// 	tmp = exp->oldvar->content;
// 	if (*(char *)(exp->newvar->content + i) != '\0')
// 	{
// 		exp->oldvar->content = ft_strjoin(tmp, exp->newvar->content + i);
// 		if (!exp->oldvar->content)
// 		{
// 			ft_putstr_fd("Error: modfie_var: malloc failed\n", 2);
// 			return ;
// 		}
// 		free(tmp);
// 	}
// 	free_newvar(exp, env);
// }

void	replace_var(t_list **list, t_list *newvar, int oldvar_i)
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
	int		i_equal;
	int		i_plus;

	initialize_var(&export, &env);
	if (create_newvar(arg, &export, &env) == -1)
		return (-1);
	i_equal = find_caracter(arg, '=');
	i_plus = find_caracter(arg, '+');
	export.oldvar = find_oldvar(arg, *explist, &export.oldvar_i);
	if (!export.oldvar)
	{	
		ft_lstadd_back(explist, export.newvar);
		if_addto_env(envlist, &env, arg);
	}
	else if (export.oldvar && i_equal >= 0)
	{
		env.oldvar = find_oldvar(arg, *envlist, &env.oldvar_i);
		if (i_equal == i_plus + 1)
		{
			if (join_newvar_oldvar(&export, i_equal + 1) == -1)
			{
				free_newvar(&export, &env);
				return (-1);
			}
			if (!env.oldvar)
			{
				free(env.newvar->content);
				env.newvar->content = ft_strdup(export.newvar->content);
				if (!env.newvar->content)
				{
					free_newvar(&export, &env);
					return (-1);
				}
				ft_lstadd_back(envlist, env.newvar);
			}
			else
			{
				if (join_newvar_oldvar(&env, i_equal + 1) == -1)
				{
					free_newvar(&export, &env);
					return (-1);
				}
			}
		}
		else
		{
			replace_var(explist, export.newvar, export.oldvar_i);
			if (!env.oldvar)
			{
				free(env.newvar->content);
				env.newvar->content = ft_strdup(export.newvar->content);
				if (!env.newvar->content)
				{
					free_newvar(&export, &env);
					return (-1);
				}
				ft_lstadd_back(envlist, env.newvar);
			}
			else
				replace_var(envlist, env.newvar, env.oldvar_i);
		}
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
