/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:00:34 by yachen            #+#    #+#             */
/*   Updated: 2023/10/27 16:25:17 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	delete_var(t_list *list, int oldvar_i)
{
	int		j;
	t_list	*current;
	t_list	*tmp;

	j = 0;
	if (oldvar_i == 0)
	{
		free(list);
		list = NULL;
		return ;
	}
	current = list;
	tmp = NULL;
	while (j < oldvar_i)
	{
		tmp = current;
		current = current->next;
		j++;
	}
	tmp->next = current->next;
	free(current);
}

void	ft_unset(t_list *envlist, t_list *explist, char *arg)
{
	t_list	*env_oldvar;
	t_list	*exp_oldvar;
	int		oldvar_i[2];
	
	oldvar_i[0] = 0;
	oldvar_i[1] = 0;
	if (find_caracter(arg, '=') >= 0)
		env_oldvar = find_oldvar(arg, envlist, oldvar_i + 1);
	exp_oldvar = find_oldvar(arg, explist, oldvar_i + 0);
	if (!exp_oldvar)
		return ;
	else
	{
		delete_var(explist, oldvar_i[0]);
		if (env_oldvar)
			delete_var(envlist, oldvar_i[1]);
	}
}