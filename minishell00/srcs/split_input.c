/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:58:07 by nap               #+#    #+#             */
/*   Updated: 2023/11/01 17:03:31 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_process(&data)
{
	int	i;
	int start;
	int id;
	
	start = 0;
	i = 0;
	id = 0;
	while (i <= data->len && data->s[i])
	{
		if (data->s[i] == '|')
		{
			if (between_quotes(data->s, i) == i)
				process_init(data->s, start, i, id);
				id++;
		}
		i++;
	}
}