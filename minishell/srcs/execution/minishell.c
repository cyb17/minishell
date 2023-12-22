/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/12/22 16:39:18 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	print_prcs(t_process *prcs)
{
	t_process	*tmp;
	t_tokens	*tmp2;

	tmp = prcs;
	while (tmp)
	{
		tmp2 = tmp->list_tokens;
		while (tmp2)
		{
			printf("value: %s  type ", tmp2->value);
			if (tmp2->type == 1)
				printf("CMD\n");
			else if (tmp2->type == 2)
				printf("WORD\n");
			else if (tmp2->type == 3)
				printf("INFILE\n");
			else if (tmp2->type == 4)
				printf("OUTFILE\n");
			else if (tmp2->type == 5)
				printf("REDIR_IN\n");
			else if (tmp2->type == 6)
				printf("REDIR_OUT\n");
			else if (tmp2->type == 7)
				printf("APPEN\n");
			else if (tmp2->type == 8)
				printf("HEREDOC\n");
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
		printf("\n");
	}
}

int	g_signal;

// Browse list_tokens of each process, if there a heredoc,
// prepare the heredoc and save it's path in process
static int	fill_heredoc(t_res *res)
{
	t_process	*prcs;
	t_tokens	*tk;

	prcs = res->prcs;
	while (prcs)
	{
		tk = prcs->list_tokens;
		while (tk)
		{
			if (tk->type == HEREDOC)
			{
				if (prcs->heredoc)
					free(prcs->heredoc);
				prcs->heredoc = ft_here_doc(tk->next->value);
				if (!prcs->heredoc)
					return (-1);
			}
			tk = tk->next;
		}
		prcs = prcs->next;
	}
	return (0);
}

static void	execution(t_res *res, t_all *all)
{
	clean_pars(all->p);
	res->prcs = all->process;
	if (fill_heredoc(res) == 0)
	{
		print_prcs(res->prcs);
		if (find_nb_process(res->prcs) > 1)
			multi_prcs(res);
		else
			single_prcs(res);
	}
	garbage_collector_parent(res);
}

int	main(int argc, char **argv, char **env)
{
	t_res		res;
	t_all		all;

	(void)argc;
	(void)argv;
	start_data_init(&res, &all, env, argv);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, signal_handler_main);
		res.input = readline("minishell> ");
		add_history(res.input);
		if (!res.input)
		{
			garbage_collector_child(&res);
			ft_ctrl_d();
		}
		if (res.input[0] != '\0')
		{
			if (ft_parse(res.input, &all) == 0)
				execution(&res, &all);
		}
	}
	return (0);
}
