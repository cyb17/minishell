/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:02:28 by yachen            #+#    #+#             */
/*   Updated: 2023/12/16 17:19:46 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

// Joint newvar's value to oldvar's value, but need condition: oldvar != NULL
static int	join_newvar_oldvar(t_var *var, int i)
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
		free(var->newvar->content);
	}
	return (0);
}

// Dup export->newvar->content to env->newvar->content and lstaddback to envlist
static int	add_var_to_envlist(t_var *env, t_var *export)
{
	free(env->newvar->content);
	env->newvar->content = ft_strdup(export->newvar->content);
	if (!env->newvar->content)
	{
		ft_putstr_fd("Error: add_var_to_envlist: malloc failed\n", 2);
		free_newvar(export, env);
		return (-1);
	}
	ft_lstadd_back(env->list, env->newvar);
	return (0);
}

// Find oldvar in list and replace it by newvar
static void	replace_var(t_list **list, t_list *newvar, int oldvar_i)
{
	int		i;
	t_list	*tmp;
	t_list	*current;

	i = 0;
	current = *list;
	if (oldvar_i == 0)
	{
		newvar->next = (current)->next;
		*list = newvar;
		free(current->content);
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
	free(current->content);
	free(current);
}

int	join_and_update(t_var *env, t_var *export)
{
	if (join_newvar_oldvar(export, export->equal_i + 1) == -1)
	{
		free_newvar(export, env);
		return (-1);
	}
	if (env->oldvar)
	{
		if (join_newvar_oldvar(env, env->equal_i + 1) == -1)
		{
			free_newvar(export, env);
			return (-1);
		}
	}
	else
	{
		if (add_var_to_envlist(env, export) == -1)
			return (-1);
	}
	return (0);
}

int	replace_and_update(t_var *env, t_var *export)
{
	replace_var(export->list, export->newvar, export->oldvar_i);
	if (env->oldvar)
		replace_var(env->list, env->newvar, env->oldvar_i);
	else
	{
		if (add_var_to_envlist(env, export) == -1)
			return (-1);
	}
	return (0);
}