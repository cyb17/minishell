/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/11/08 15:01:26 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_process	**process;
	t_tab		tab;

	process = NULL;
	tab.fdin = 0;
	tab.fdout = 0;
	while (1)
	{
		input = readline("minishell > ");
	//	ft_parse(input, process);
		printf("%s\n", input);
		if (make_inoutfile(&tab.fdin, &tab.fdout, *process) == -1)
		{
			if (input)
				free(input);
			return (1);
		}
		pipex();
		if (input)
			free(input);
	}
	return (0);
}