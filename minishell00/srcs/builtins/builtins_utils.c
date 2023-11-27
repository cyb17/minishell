/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:06:41 by yachen            #+#    #+#             */
/*   Updated: 2023/11/27 15:49:23 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

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

int	find_caracter(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	stringcmp(char *model, char *str)
{
	int	i;

	i = 0;
	while (model[i] && model[i] != '=' && model[i] != '+')
	{
		if (model[i] != str[i])
			return (0);
		i++;
	}
	if (str[i] != '=' && str[i] != '\0' && model[i] != '+')
		return (0);
	return (1);
}

t_list	*find_oldvar(char *var, t_list *list, int *i)
{
	t_list	*current;

	current = list;
	while (current)
	{
		if (stringcmp(var, current->content) == 1)
			return (current);
		if (i)
			(*i)++;
		current = current->next;
	}
	return (NULL);
}
