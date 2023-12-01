/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:02:28 by yachen            #+#    #+#             */
/*   Updated: 2023/12/01 16:30:08 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	initialize_var(t_var *export, t_var *env)
{
	export->oldvar = NULL;
	export->newvar = NULL;
	export->oldvar_i = 0;
	env->oldvar = NULL;
	env->newvar = NULL;
	env->oldvar_i = 0;
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

void	free_newvar(t_var *export, t_var *env)
{
	if(export->newvar)
		free(export->newvar);
	if (env->newvar)
		free(env->newvar);
}

void	if_addto_env(t_list **envlist, t_var *env, char *arg)
{
	if (find_caracter(arg, '=') >= 0)
		ft_lstadd_back(envlist, env->newvar);
	else
		free(env->newvar);
}

// void	replace_var(t_list **envlst, t_list **explst, t_var *env, t_var *exp)
// {
// 	replace(explst, env->newvar, env->oldvar_i);
// 	replace(envlst, exp->newvar, exp->oldvar_i);
// }

// int	create_newvar(char *arg, t_var *var)
// {
// 	var->newvar = ft_lstnew(ft_strdup(arg));
// 	if (!var->newvar || !var->newvar->content)
// 	{
// 		if (var->newvar)
// 			free(var->newvar);
// 		ft_putstr_fd("Error: create_newvar: malloc failed\n", 2);
// 		return (-1);
// 	}
// 	return (0);
// }
