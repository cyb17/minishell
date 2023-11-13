/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:43:31 by nap               #+#    #+#             */
/*   Updated: 2023/11/13 16:06:14 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_process	*process;
	t_list		*envlist;

	(void)ac;
	(void)av;
	process = NULL;
	while (1)
	{
		envlist = NULL;
		envlist = env_to_envlist(env);
		input = readline("minishell > ");
		ft_parse(input, &process, envlist);
		while (process)
		{
			printf("Contenu de section_cmd : %s\n", process->section_cmd);
			process = process->next ;
		}
	}
}
