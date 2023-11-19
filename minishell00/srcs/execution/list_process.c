/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:45:22 by yachen            #+#    #+#             */
/*   Updated: 2023/11/19 10:19:40 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_tokens	*create_tokens(char *va, int ty)
{
	t_tokens	*tokens;

	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	tokens->token_id = 0;
	tokens->value = ft_strdup(va);
	tokens->type = ty;
	tokens->next = NULL;
	return (tokens);
}

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

static t_tokens	*make_list_tokens(char *cmd, char *op)
{
	t_tokens	*lst;

	lst = NULL;
	//ft_lstadd_tokens(&lst, (create_tokens("<", REDIR_IN)));
	//ft_lstadd_tokens(&lst, (create_tokens("infile", INFILE)));
	ft_lstadd_tokens(&lst, (create_tokens(cmd, CMD)));
	ft_lstadd_tokens(&lst, (create_tokens(op, WORD)));
	//ft_lstadd_tokens(&lst, (create_tokens(">", REDIR_OUT)));
	//ft_lstadd_tokens(&lst, (create_tokens("outfile", OUTFILE)));
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

t_process	*create_list_process(char *input)
{
	char		**arg;
	t_process	*list;
	int			i;

	arg = ft_split(input, ' ');
	list = NULL;
	i = 0;
	while (arg[i])
	{
		ft_lstadd_process(&list, create_process(arg[i], arg[i + 1]));
		i += 2;
	}
	free_tab(arg);
	return (list);
}

/*int	main(void)
{
	t_process	*list;
	
	list = create_list_process("ls -l wc -l");
	clear_process(&list);
	return (0);
}*/