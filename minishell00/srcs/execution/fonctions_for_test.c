/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions_for_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:57:49 by yachen            #+#    #+#             */
/*   Updated: 2023/11/25 17:53:50 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_lst(t_list **list)
{
	t_list	*current;

	current = NULL;
	while (*list)
	{
		current = *list;
		*list = (*list)->next;
		free(current);
	}
}

t_list	*env_to_envlist(char **env)
{
	int		i;
	t_list	*envlist;
	t_list	*tmp;

	i = 0;
	envlist = NULL;
	while (env[i])
	{
		tmp = ft_lstnew(env[i]);
		if (!tmp)
		{
			clear_lst(&envlist);
			return (NULL);
		}
		ft_lstadd_back(&envlist, tmp);
		i++;
	}
	return (envlist);
}

int	ft_compare(char *limiter, char *str)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] != str[i])
			return (0);
		i++;
	}
	if (limiter[i] == '\0' && str[i] == '\n')
		return (1);
	return (0);
}
