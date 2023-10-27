/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:23:24 by yachen            #+#    #+#             */
/*   Updated: 2023/10/27 12:58:12 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_lst(t_list **lst)
{
	t_list	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
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

void	ft_env(t_list *envlist)
{
	t_list	*tmp;

	tmp = envlist;
	while (tmp != NULL)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}