/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:43:31 by nap               #+#    #+#             */
/*   Updated: 2023/12/09 13:05:04 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	g_signal[2];

bool	ft_error(char *s, t_all *all, int code)
{
	g_signal[0] = code;
	printf("%s", s);
	clean_loop(all);
	return (false);
}

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
			if (ft_parse(input, &all) == 0)
				clean_pars(all.p);
		}
	}
}
