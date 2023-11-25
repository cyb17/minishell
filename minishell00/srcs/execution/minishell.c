/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/11/25 18:15:15 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_structure(t_res *res)
{
	res->prcs = NULL;
	res->blt = NULL;
	res->tab = NULL;
	res->input = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_res		res;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		init_structure(&res);
		res.input = readline("\e[34;1mminishell> \e[0m");
		//ft_parse(res.input, process);
		res.blt = fill_builtins(env);
		res.prcs = create_list_process();
		if (find_nb_process(res.prcs) > 1)
			multi_prcs(&res, env);
		else
			single_prcs(&res, env);
		// if (!res.blt)
		// {
		// 	garbage_collector(&res);
		// 	ft_putstr_fd("initialization of ressources failed\n", 2);
		//  	return (1);
		// }
		garbage_collector(&res);
	}
	return (0);
}
