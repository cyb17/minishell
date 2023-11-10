/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/11/10 14:40:45 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_structure(t_tab *tab, t_builtins *blt, t_process **pc, char *inpt)
{
	tab->fdin = 0;
	tab->fdout = 0;
	tab->nb_pipe = 0;
	tab->pipefd = NULL;
	tab->tab_pid = NULL;
	tab->process = NULL;
	tab->builtins = NULL;
	tab->input = NULL;
	blt->envlist = NULL;
	blt->explist = NULL;
	blt->arg = NULL;
	pc = NULL;
	inpt = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_process	**process;
	char		*input;
	//t_tab		tab;
	//t_builtins	builtins;

	while (1)
	{
		init_structure(tab, builtins, process, input);
		input = readline("\e[34;1mminishell > \e[0m");
		 ft_parse(input, process);
		// if (fill_builtins(&builtins, env) == -1
		//	|| fill_tab(&tab, *process) == -1
		// 	|| pipex(&builtins, &tab, *process, env) == -1)
		// {
		// 	garbage_collector(process, &tab, &builtins);
		// 	return (1);
		// }
		garbage_collector(process, &tab, &builtins, input);
	}
	return (0);
}
