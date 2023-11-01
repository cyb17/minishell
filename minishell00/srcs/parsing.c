/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:12:48 by nap               #+#    #+#             */
/*   Updated: 2023/11/01 16:09:39 by achevala         ###   ########.fr       */
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
	while (input[i] && i <= (int)ft_strlen(input))
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

bool	is_valid(char *l)
{
	int	i;

	i = 0;
	while (l[i] && i <= (int)ft_strlen(l))
	{
		if (valid_char(l[i]) == false)
		{
			if (between_quotes(l, i) == i)
				return (false);
			else 
				i = between_quotes(l, i);
		}
		i++;
	}
	return (true);
}

int	check_quotes(char *input, char c, int i)
{
	bool inside_quote;
	int j;

	inside_quote = false;
	j = i;
	i++;
    while (input[i] && i <= (int)ft_strlen(input))
	{
        if (input[i] == c) 
		{
            if (inside_quote == false)
			{
                inside_quote = true;
				return (i);
			}
        }
		i++;
	}
	return (j);
}

int	ft_parse(char *line)
{
	t_data	data;
	
	if (first_readind(line) == false)
	{
		printf("erreur : ");
		return (1);
	}
	data_init(&data, line);
	find_process(&data);
	return (0);
}