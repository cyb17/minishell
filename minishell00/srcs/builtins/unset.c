/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:00:34 by yachen            #+#    #+#             */
/*   Updated: 2023/11/09 12:05:37 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

static void	delete_var(t_list **list, int oldvar_i)
{
	int		j;
	t_list	*current;
	t_list	*tmp;

	j = 0;
	current = *list;
	tmp = NULL;
	if (oldvar_i == 0)
	{
		if ((*list)->next != NULL)
			*list = (*list)->next;
		else
			*list = NULL;
		free(current);
		return ;
	}
	while (j < oldvar_i)
	{
		tmp = current;
		current = current->next;
		j++;
	}
	tmp->next = current->next;
	free(current);
}

int	ft_unset(t_list **envlist, t_list **explist, char *arg)
{
	t_list	*env_oldvar;
	t_list	*exp_oldvar;
	int		oldvar_i[2];

	oldvar_i[0] = 0;
	oldvar_i[1] = 0;
	env_oldvar = NULL;
	exp_oldvar = NULL;
	if (!arg)
		return (0);
	exp_oldvar = find_oldvar(arg, *explist, oldvar_i + 0);
	if (!exp_oldvar)
		return (0);
	else
	{
		delete_var(explist, oldvar_i[0]);
		env_oldvar = find_oldvar(arg, *envlist, oldvar_i + 1);
		if (env_oldvar)
			delete_var(envlist, oldvar_i[1]);
	}
	return (0);
}
