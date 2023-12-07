/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/12/07 16:49:36 by yachen           ###   ########.fr       */
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
	res->io = NULL;
}

static void	print_prcs(t_process *prcs)
{
	t_process	*tmp;
	t_tokens	*tmp2;

	tmp = prcs;
	if (tmp == NULL)
		printf("yes1\n");
	while (tmp)
	{
		tmp2 = prcs->list_tokens;
		printf("1=CMD, 2=W, 3=INFILE, 4=OUTFILE, 5=REDIR_IN, 6=REDIR_OUT\n");
		if (tmp2 == NULL)
			printf("yes2\n");
		while (tmp2)
		{
			printf("value: %s type: %d\n", tmp2->value, tmp2->type);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
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
	init_structure(&res);
	res.blt = fill_builtins(env);
	if (env && !res.blt)
	{
		ft_putstr_fd("Error: fill_builtins: malloc failed\n", 2);
		g_signal[0] = 1;
	}
	all_init(&all, &res);
	while (1)
	{
		res.input = readline("\e[34;1mminishell> \e[0m");
		if (res.input && res.input[0] != '\0')
		{
			add_history(res.input);
			ft_parse(res.input, &all);
			res.prcs = all.process;
			print_prcs(res.prcs);
			if (find_nb_process(res.prcs) > 1)
				multi_prcs(&res);
			else
				single_prcs(&res);
		}
		garbage_collector_parent(&res);
	}
	return (0);
}
