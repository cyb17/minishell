/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/12/12 17:55:41 by yachen           ###   ########.fr       */
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
// 		if(!tmp->heredoc)
// 			printf("heredoc null\n");
// 		else
// 			printf("%s\n", tmp->heredoc);
// 		tmp = tmp->next;
// 		printf("\n");
// 	}
// }

int	g_signal[2];

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
		// print_prcs(res->prcs);
		if (find_nb_process(res->prcs) > 1)
			multi_prcs(res);
		else
			single_prcs(res);
	}
	garbage_collector_parent(res);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal[0] = 130;
		// close(STDIN_FILENO);
	}
}

void	ft_ctrl_d(void)
{
	g_signal[0] = 0;
	printf("exit\n");
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	t_res		res;
	t_all		all;
	int			save_stdin;

	(void)argc;
	(void)argv;
	start_data_init(&res, &all, env);
	save_stdin = dup(STDIN_FILENO);
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
			dup2(save_stdin, STDIN_FILENO);
			close(save_stdin);
		}
	}
	return (0);
}
