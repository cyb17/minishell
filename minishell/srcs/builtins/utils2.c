/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:29:25 by yachen            #+#    #+#             */
/*   Updated: 2023/12/22 12:38:31 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	go_to(t_list **envlist, char *var_name)
{
	t_list	*var;
	t_list	*tmp;

	tmp = *envlist;
	var = find_oldvar(var_name, tmp, NULL);
	if (!var)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(var_name, 2);
		ft_putstr_fd(" not set\n", 2);
		return (1);
	}
	if (chdir(var->content + (ft_strlen(var_name) + 1)) == -1)
	{
		perror("minishell: cd: go_to: chdir");
		return (1);
	}
	return (0);
}