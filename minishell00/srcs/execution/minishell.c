/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/11/09 16:56:25 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_process	**process;
	char		*input;
	t_tab		tab;
	t_builtins	builtins;

	while (1)
	{
		input = readline("minishell > ");
		ft_parse(input, process);
		if (init_tab(&tab, *process) == -1
			|| init_builtins(&builtins, env) == -1
			|| pipex(&builtins, &tab, *process, env) == -1)
		{
			free(input);
			garbage_collector(process, &tab, &builtins);
			return (1);
		}
	}
	return (0);
}
