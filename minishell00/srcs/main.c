/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:43:31 by nap               #+#    #+#             */
/*   Updated: 2023/12/04 14:39:15 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_process	*process;
	t_all		all;

	(void)ac;
	(void)av;
	process = NULL;
	all_init(&all, env);
	while (1)
	{
		input = readline("minishell > ");
		if (input[0] != '\0')
		{
			ft_parse(input, &all);
			process = all.process;
			while (process)
			{
				printf("Contenu de section_cmd : %s id = %d\n", process->section_cmd, process->section_cmd_id);
				while (process->list_tokens)
				{
					printf("tkn %s : %d,\n", process->list_tokens->value, process->list_tokens->type);
					process->list_tokens = process->list_tokens->next;
				}
				process = process->next ;
			}
			clean_loop(&all);
		}
	}
}