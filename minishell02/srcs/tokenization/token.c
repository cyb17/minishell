/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:53:25 by achevala          #+#    #+#             */
/*   Updated: 2023/12/06 18:42:46 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	read_value(char *value, t_tokens *token)
{
	if (ft_strcmp(value, "<") == 1)
	{
		token->type = 5;
		if (token->next)
			token->next->type = 3;
	}
	if (ft_strcmp(value, ">") == 1)
	{
		token->type = 6;
		if (token->next)
			token->next->type = 4;
	}
	if (ft_strcmp(value, ">>") == 1)
	{
		token->type = 7;
		if (token->next)
			token->next->type = 3;
	}
	if (ft_strcmp(value, "<<") == 1)
	{
		token->type = 8;
		if (token->next)
			token->next->type = 4;
	}
}

void	cmd_value(t_tokens *token)
{
	bool	flag;

	flag = false;
	while (token)
	{
		if (token->type == -1)
		{
			if (flag == false)
			{
				flag = true;
				token->type = 1;
			}
			else
				token->type = 2;
		}
		token = token->next;
	}
}

void	ft_token(t_process *process)
{
	char		*s;
	t_tokens	*head;

	while (process)
	{
		head = process->list_tokens;
		while (process->list_tokens)
		{
			s = process->list_tokens->value;
			read_value(s, process->list_tokens);
			process->list_tokens = process->list_tokens->next;
		}
		process->list_tokens = head;
		while (process->list_tokens)
		{
			s = process->list_tokens->value;
			cmd_value(process->list_tokens);
			process->list_tokens = process->list_tokens->next;
		}
		process->list_tokens = head;
		process = process->next;
	}
}
