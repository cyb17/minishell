/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_proces_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:19:46 by yachen            #+#    #+#             */
/*   Updated: 2023/11/02 10:56:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*typedef struct t_data
{
	int	start;
	int	end;
	int	id;
}				t_data;

void	init_data(t_data *data)
{
	data->start = 0;
	data->end = 0;
	data->id = 0;
}*/

t_proces	*create_process(char *start, int end, int id)
{
	t_proces	proces;
	
	proces_init(&proces);
	
}

t_proces	**make_proces_list(char *line)
{
//	t_data	data;
	t_proces	**list_proces;
	t_proces	**new_proces;
	int	quote_flag;
	int	i;
	int	start;

	list_proces = NULL;
	new_proces = NULL;
//	init_data(&data);
	quote_flag = 0;
	i = 0;
	start = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			quote_flag = 1;
		if (line[i] == '|' && quote_flag == 0)
		{
			id++;
			*new_proces = create_process(line + start, i, id);
			ft_lstadd_back(list_proces, *new_proces);
			start = i + 1;
		}
		i++;
	}
	return (list_proces);
}3