/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/12/11 17:14:38 by yachen           ###   ########.fr       */
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

static void	execution(t_res *res, t_all *all)
{
	clean_pars(all->p);
	res->prcs = all->process;
	// print_prcs(res->prcs);
	if (find_nb_process(res->prcs) > 1)
		multi_prcs(res);
	else
		single_prcs(res);
	garbage_collector_parent(res);
}

int	main(int argc, char **argv, char **env)
{
	t_res		res;
	t_all		all;

	(void)argc;
	(void)argv;
	start_data_init(&res, &all, env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		res.input = readline("minishell> ");
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		add_history(res.input);
		if (!res.input)
			ft_ctrl_d();
		if (res.input[0] != '\0')
		{
			if (ft_parse(res.input, &all) == 0)
				execution(&res, &all);
		}
	}
	return (0);
}
