/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/11/28 17:18:26 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	g_signal[2];

static void	init_structure(t_res *res)
{
	res->prcs = NULL;
	res->blt = NULL;
	res->tab = NULL;
	res->input = NULL;
}

void	print_process(t_process *prcs)
{
	t_process	*tmp1;
	t_tokens	*tmp2;

	tmp1 = prcs;
	while (tmp1)
	{
		tmp2 = prcs->list_tokens;
		while (tmp2)
		{
			printf("%s ", tmp2->value);
			tmp2 = tmp2->next;
		}
		tmp1 = prcs->next;
		printf("\n");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_res		res;
	t_all		all;

	(void)argc;
	(void)argv;
	(void)env;
	ft_memset(g_signal, 0, 2);
	all_init(&all, env);
	while (1)
	{
		init_structure(&res);
		res.input = readline("\e[34;1mminishell> \e[0m");
		if (!res.input || res.input[0] == '\0')
			garbage_collector(&res, &all);
		else
		{
			add_history(res.input);
			if (ft_parse(res.input, &all) == 0)
			{
				res.blt = fill_builtins(env);
				if (env && !res.blt)
				{
					garbage_collector(&res, &all);
					ft_putstr_fd("Error: fill_builtins failed\n", 2);
					g_signal[0] = 1;
				}
				res.prcs = all.process;
				print_process(res.prcs);
				// if (find_nb_process(res.prcs) > 1)
				// 	multi_prcs(&res, env);
				// else
					single_prcs(&res, env);
			}
			garbage_collector(&res, &all);
			printf("$? = %d\n", g_signal[0]);
		}
	}
	return (0);
}
