/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:00:34 by yachen            #+#    #+#             */
/*   Updated: 2023/12/16 17:10:23 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	delete_var(t_list **list, int oldvar_i)
{
	int		j;
	t_list	*current;
	t_list	*tmp;

	j = 0;
	current = *list;
	if (oldvar_i == 0)
	{
		if ((*list)->next != NULL)
			*list = (*list)->next;
		else
			*list = NULL;
		free(current->content);
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
	free(current->content);
	free(current);
}

static void	unset_arg(t_list **envlist, t_list **explist, char *arg)
{
	t_list	*env_oldvar;
	t_list	*exp_oldvar;
	int		oldvar_i[2];

	oldvar_i[0] = 0;
	oldvar_i[1] = 0;
	env_oldvar = NULL;
	exp_oldvar = NULL;
	exp_oldvar = find_oldvar(arg, *explist, oldvar_i + 0);
	if (!exp_oldvar)
		return ;
	else
	{
		delete_var(explist, oldvar_i[0]);
		env_oldvar = find_oldvar(arg, *envlist, oldvar_i + 1);
		if (env_oldvar)
			delete_var(envlist, oldvar_i[1]);
	}
}

// Return 0 anyway
int	ft_unset(t_list **envlist, t_list **explist, char **arg)
{
	int	i;

	i = 1;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		unset_arg(envlist, explist, arg[i]);
		i++;
	}
	return (0);
}
