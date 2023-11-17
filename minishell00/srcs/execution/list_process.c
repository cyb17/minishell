/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:45:22 by yachen            #+#    #+#             */
/*   Updated: 2023/11/17 17:26:46 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_lstadd_tokens(t_tokens **lst, t_tokens *new_l)
{
	t_tokens	*tmp;

	if (*lst == NULL)
	{
		*lst = new_l;
		return ;
	}
	tmp = *lst;
	while (tmp -> next != NULL)
		tmp = tmp -> next;
	tmp -> next = new_l;
}

static void	ft_lstadd_process(t_process **lst, t_process *new_l)
{
	t_process	*tmp;

	if (*lst == NULL)
	{
		*lst = new_l;
		return ;
	}
	tmp = *lst;
	while (tmp -> next != NULL)
		tmp = tmp -> next;
	tmp -> next = new_l;
}

static t_tokens	*create_tokens(char *va, int ty)
{
	t_tokens	*tokens;

	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	tokens->token_id = 0;
	tokens->value = va;
	tokens->type = ty;
	tokens->next = NULL;
	return (tokens);
}

static t_tokens	*make_list_tokens(char *cmd, char *op)
{
	t_tokens	*lst;

	lst = NULL;
	ft_lstadd_tokens(&lst, (create_tokens("<", REDIR_IN)));
	ft_lstadd_tokens(&lst, (create_tokens("infile", INFILE)));
	ft_lstadd_tokens(&lst, (create_tokens(cmd, CMD)));
	ft_lstadd_tokens(&lst, (create_tokens(op, WORD)));
	ft_lstadd_tokens(&lst, (create_tokens(">", REDIR_OUT)));
	ft_lstadd_tokens(&lst, (create_tokens("outfile", OUTFILE)));
	return (lst);
}

static t_process	*create_process(char *cmd, char *op)
{
	t_process	*process;

	process = (t_process *)malloc(sizeof(t_process));
	process->section_cmd = NULL;
	process->section_cmd_id = 0;
	process->list_tokens = make_list_tokens(cmd, op);
	process->pid = 0;
	process->next = NULL;
	return (process);
}

t_process	*create_list_process(char **arg)
{
	//char		**arg;
	t_process	*list;

	//arg = ft_split(input, ' ');
	list = NULL;
	ft_lstadd_process(&list, create_process(arg[0], arg[1]));
	ft_lstadd_process(&list, create_process(arg[2], arg[3]));
	//ft_lstadd_process(&list, create_process(arg[5], arg[6]));
	//free(arg);
	return (list);
}

static void	clear_tokens_lst(t_tokens **list)
{
	t_tokens	*current;

	current = NULL;
	while (*list)
	{
		current = *list;
		*list = (*list)->next;
		if (current->value)
			free(current->value);
		free(current);
	}
}

static void	clear_process(t_process **process)
{
	t_process	*current;

	current = NULL;
	while (*process)
	{
		current = *process;
		*process = (*process)->next;
		if (current->section_cmd)
			free(current->section_cmd);
		clear_tokens_lst(&current->list_tokens);
		free(current);
	}
}

int	main(int argc, char **argv)
{
	t_process	*list;
	
	(void)argc;
	list = create_list_process(argv + 1);
	while (list)
	{
		while (list->list_tokens)
		{
			printf("value = %s\n", list->list_tokens->value);
			printf("type = %d\n", list->list_tokens->type);
			list->list_tokens = list->list_tokens->next;
		}
		list = list->next;
	}
	clear_process(&list);
	return (0);
}