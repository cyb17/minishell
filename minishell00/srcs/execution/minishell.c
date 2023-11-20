/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/11/20 15:10:48 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_structure(t_res *res)
{
	res->prcs = NULL;
	res->blt = NULL;
	res->tab = NULL;
	res->input =NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_res		res;
	t_process	*process;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		init_structure(&res);
		res.input = readline("\e[34;1mminishell> \e[0m");
		process = create_list_process();
		//ft_parse(res.input, process);
		res.prcs = process;
		res.blt = fill_builtins(env);
		res.tab = fill_tab(process);
		if (!res.blt || !res.tab)
		{
			garbage_collector(&res);
			ft_putstr_fd("initialization of ressources failed\n", 2);
		 	return (1);
		}
		int i = 0;
		while (res.prcs)
		{
			pipex(&res, env, i);
			i++;
			res.prcs = res.prcs->next;
		}
		// {
		// 	garbage_collector(process, &tab, &builtins);
		// 	return (1);
		// }
		// garbage_collector(process, &tab, &builtins, input);
	}
	return (0);
}
