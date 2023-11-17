/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/11/17 16:23:23 by yachen           ###   ########.fr       */
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

// static void	clear_process(t_process *process)
// {
// 	t_tokens	*tokenslist;
// 	t_tokens	*tmp;

// 	tokenslist = process->list_tokens;
// 	tmp = NULL;
// 	if (process->section_cmd)
// 		free(process->section_cmd);
// 	while (tokenslist)
// 	{
// 		tmp = tokenslist->next;
// 		if (tokenslist->value)
// 			free(tokenslist->value);
// 		free(tokenslist);
// 		tokenslist = tmp;
// 	}
// 	free(process);
// }

int	main(int argc, char **argv, char **env)
{
	t_res		res;
	t_process	*process;

	(void)argc;
	(void)argv;
	//(void)env;
	while (1)
	{
		init_structure(&res);
		res.input = readline("\e[34;1mminishell> \e[0m");
		process = create_list_process(res.input);
		//ft_parse(res.input, process);
		res.prcs = process;
		res.blt = fill_builtins(env);
		res.tab = fill_tab(process);
		// while (process)
		// {
		// 	while (process->list_tokens)
		// 	{
		// 		printf("value = %s\n", process->list_tokens->value);
		// 		printf("type = %d\n", process->list_tokens->type);
		// 		process->list_tokens = process->list_tokens->next;
		// 	}
		// 	process = process->next;
		// }
		printf("nb_pipe = %d\n", res.tab->nb_pipe);
		printf("1er valeur envlist = %s\n", (char *)res.blt->envlist->content);
		// if (!res.blt || !res.tab)
		// {
		garbage_collector(&res);
		//clear_process(process->next);
		//clear_process(process);
		//  	return (1);
		// }
		// pipex(&res, env)
		// {
		// 	garbage_collector(process, &tab, &builtins);
		// 	return (1);
		// }
		// garbage_collector(process, &tab, &builtins, input);
	}
	return (0);
}
