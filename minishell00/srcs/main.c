/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nap <nap@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:43:31 by nap               #+#    #+#             */
/*   Updated: 2023/10/26 17:03:57 by nap              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
	char *input;
	t_process	process;
    
	(void)ac;
	(void)av;
	(void)env;
	process_init(&process);
	while (1)
	{
		input = readline("minishell > ");
		ft_parse(input);
		printf("%s\n", input);
		free(input);
	}
}

