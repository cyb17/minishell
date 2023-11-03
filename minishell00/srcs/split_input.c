/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:58:07 by nap               #+#    #+#             */
/*   Updated: 2023/11/03 14:32:15 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_process	*create_process(char *start, int end, int id)
{
	t_process	*process;
	
	process = (t_process *)malloc(sizeof(t_process));
	if (!process)
	{
		ft_putstr_fd("error: create_process: malloc failed", 2);
		return (NULL);
	}
	process_init(process);
	process->section_cmd = ft_strdup_section(start, end, id);
	process->section_cmd_id = id;
	return (process);
}

t_process	**make_proces_list(char *line)
{
	t_process	**list_process;
	t_process	**new_process;
	int	i;
	int	start;
	int	id;

	list_process = NULL;
	new_process = NULL;
	i = 0;
	start = 0;
	id = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (between_quotes(line, i) == i)
			{
				id++;
				*new_process = create_process(line + start, i, id);
				ft_procsadd_back(list_process, *new_process);
				start = i + 1;
			}
		}
		i++;
	}
	return (list_process);
}

void	make_token_list(t_process *process)
{
	t_tokens	**list_token;
	t_tokens	**new_token;
	int	id;
	char **words;

	list_token = NULL;
	new_token = NULL;
	id = 0;
	while(process->next_process)
	{
		words = split_minishell(process->section_cmd);
		while (words)
		{
			if ()
			{
				
			}
			id++;
		}
	}
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	i = 0;
	while (s[i])
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}	