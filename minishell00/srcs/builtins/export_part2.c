/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:02:28 by yachen            #+#    #+#             */
/*   Updated: 2023/10/30 16:30:15 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

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

void	free_var(t_var *export, t_var *env)
{
	free(export->newvar);
	free(env->newvar);
}

void	add_tolist(t_list **envlist, t_var *env, char *arg)
{
	if (find_caracter(arg, '=') >= 0)
		ft_lstadd_back(envlist, env->newvar);
	else
		free(env->newvar);
}

void	replace_var(t_list **envlst, t_list **explst, t_var *env, t_var *exp)
{
	replace(envlst, env->newvar, env->oldvar_i);
	replace(explst, exp->newvar, exp->oldvar_i);
}
