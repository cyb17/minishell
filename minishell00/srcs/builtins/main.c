/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:18:22 by yachen            #+#    #+#             */
/*   Updated: 2023/11/01 11:31:12 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

void	free_list(t_list **list)
{
	t_list *current;
	
	current = NULL;
	while (*list)
	{
		current = *list;
		*list = (*list)->next;
		free(current);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_list	*envlist;
	t_list	*explist;

	envlist = NULL;
	explist = NULL;
	printf("teste : %d %s\n", argc, argv[0]);
	envlist = env_to_envlist(env);
	explist = env_to_envlist(env);

	/*printf("print env list : \n");
	ft_env(envlist);
	printf("\n\n");
	ft_export(&envlist, &explist, "test");
	printf("\n\n");
	ft_export(&envlist, &explist, "test1=");
	ft_export(&envlist, &explist, "test2");
	ft_export(&envlist, &explist, "LSCOLORS=test");
	ft_export(&envlist, &explist, "USER=test");
	ft_export(&envlist, &explist, "SHELL=test");
	ft_export(&envlist, &explist, "LOGNAME=test");
	ft_export(&envlist, &explist, "TERM_PROGRAM=");
	ft_export(&envlist, &explist, "test3=");
	ft_export(&envlist, &explist, "test");
	ft_unset(&envlist, &explist, "test");
	ft_unset(&envlist, &explist, "test1=");
	ft_unset(&envlist, &explist, "te");
	ft_unset(&envlist, &explist, "SHELL");
	ft_env(envlist);
	printf("\n\n");
	ft_unset(&envlist, &explist, NULL);
	ft_export(&envlist, &explist, NULL);*/
	ft_pwd();
	free_list(&envlist);
	free_list(&explist);
	return (0);
}
