/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nap <nap@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:12:48 by nap               #+#    #+#             */
/*   Updated: 2023/11/09 14:57:38 by nap              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	first_readind(char *input)
{
	int	i;
	int j;

	i = 0;
	// if (is_valid(input) == false)
	// 	return (false);
	while (input[i] && i <= (int)my_strlen(input))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			j = check_quotes(input, input[i], i);
			if (i == j)
				return (false);
			else 
				i = j;
		}
		i++;
	}
	return (true);
}

// bool	is_valid(char *l)
// {
// 	int	i;

// 	i = 0;
// 	while (l[i] && i <= (int)ft_strlen(l))
// 	{
// 		if (valid_char(l[i]) == false)
// 		{
// 			if (between_quotes(l, i) == i)
// 				return (false);
// 			else 
// 				i = between_quotes(l, i);
// 		}
// 		i++;
// 	}
// 	return (true);
// }

int	ft_parse(char *line, t_process **process, t_list *envlist)
{
	if (first_readind(line) == false)
	{
		printf("erreur : ");
		return (1);
	}
	process = make_proces_list(line);
	make_token_list(*process, envlist);
	return (0);
}