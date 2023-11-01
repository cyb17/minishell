/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:58:13 by nap               #+#    #+#             */
/*   Updated: 2023/11/01 17:03:52 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_init(t_process *process)
{
	process->section_cmd = NULL;
	process->section_cmd_id = -1;
	process->list_tokens = NULL;
	process->pid = -1;
	process->next_process = NULL;
	
}

void	*data_init(t_data *data, char *line)
{
	data->s = ft_strdup(line);
	if (!data->s)
		return (NULL);
	data->len = ft_strlen(line);
	return (0);
}