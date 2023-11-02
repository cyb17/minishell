/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:43:31 by nap               #+#    #+#             */
/*   Updated: 2023/11/02 12:31:31 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
	char 		*input;
	t_process	**process;
    
	(void)ac;
	(void)av;
	(void)env;
	//process_init(&process);
	process = NULL;
	while (1)
	{
		input = readline("minishell > ");
		ft_parse(input, process);
		printf("%s\n", input);
		free(input);
	}
}

