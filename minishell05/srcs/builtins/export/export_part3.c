/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:32:13 by yachen            #+#    #+#             */
/*   Updated: 2023/12/16 17:21:07 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

void	free_newvar(t_var *export, t_var *env)
{
	if(export->newvar)
	{
		if (export->newvar->content)
			free(export->newvar->content);
		free(export->newvar);
	}
	if (env->newvar)
	{
		if (env->newvar->content)
			free(env->newvar->content);
		free(env->newvar);
	}
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