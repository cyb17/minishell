/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nap <nap@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/12/13 11:28:32 by nap              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// static void	print_prcs(t_process *prcs)
// {
// 	t_process	*tmp;
// 	t_tokens	*tmp2;

// 	tmp = prcs;
// 	if (tmp == NULL)
// 		printf("yes1\n");
// 	while (tmp)
// 	{
// 		tmp2 = tmp->list_tokens;
// 		printf("1=CMD, 2=W, 3=INFILE, 4=OUTFILE, 5=REDIR_IN, 6=REDIR_OUT\n");
// 		while (tmp2)
// 		{
// 			printf("value: %s type: %d\n", tmp2->value, tmp2->type);
// 			tmp2 = tmp2->next;
// 		}
// 		tmp = tmp->next;
// 		printf("\n");
// 	}
// }

int	g_signal[2];

static void	start_data_init(t_res *res, t_all *all, char **env, char **argv)
{
	ft_memset(g_signal, 0, 2);
	res->prcs = NULL;
	res->blt = fill_builtins(env);
	if (env && !res->blt)
	{
		ft_putstr_fd("Error: fill_builtins: malloc failed\n", 2);
		g_signal[0] = 1;
	}
	res->tab = NULL;
	res->input = NULL;
	res->io = NULL;
	all->process = NULL;
	all->envlist = res->blt->envlist;
	all->process = NULL;
	all->p = NULL;
	all->argv0 = argv[0];
}

// void	signal_handler(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 	}
// 	else if (signum == SIGQUIT)
// 		return ;
// }

int	main(int argc, char **argv, char **env)
{
	t_res		res;
	t_all		all;

	(void)argc;
	(void)argv;
	start_data_init(&res, &all, env, argv);
	while (1)
	{
		
		res.input = readline("\e[34;1mminishell> \e[0m");
		if (res.input && res.input[0] != '\0')
		{
			add_history(res.input);
			if (ft_parse(res.input, &all) == 0)
			{
				clean_pars(all.p);
				res.prcs = all.process;
				// print_prcs(res.prcs);
				if (find_nb_process(res.prcs) > 1)
					multi_prcs(&res);
				else
					single_prcs(&res);
			}
		}
		garbage_collector_parent(&res);
		// signal(SIGINT, signal_handler);
	}
	return (0);
}
