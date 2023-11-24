/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:45:22 by yachen            #+#    #+#             */
/*   Updated: 2023/11/24 17:57:19 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	clear_tokens_list(t_tokens **list)
// {
// 	t_tokens	*tmp;

// 	tmp = NULL;
// 	while (*list)
// 	{
// 		tmp = *list;
// 		*list = (*list)->next;
// 		if (tmp->value)
// 			free(tmp->value);
// 		free(tmp);
// 	}
// }

// static void	clear_process_list(t_process **process)
// {
// 	t_process	*tmp;

// 	tmp = NULL;
// 	while (*process)
// 	{
// 		tmp = *process;
// 		*process = (*process)->next;
// 		if (tmp->section_cmd)
// 			free(tmp->section_cmd);
// 		if (tmp->list_tokens)
// 			clear_tokens_list(&tmp->list_tokens);
// 		free(tmp);
// 	}
// }

static void	ft_lstadd_tokens(t_tokens **lst, t_tokens *new_l)
{
	t_tokens	*tmp;

	if (new_l == NULL)
		return ;
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

	if (va == NULL)
		return (NULL);
	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	tokens->token_id = 0;
	tokens->value = ft_strdup(va);
	tokens->type = ty;
	tokens->next = NULL;
	return (tokens);
}

static t_tokens	*make_list_tokens(char infile[2][10], char cmd[2][10], char outfile[2][10])
{
	t_tokens	*lst;

	lst = NULL;
	if (infile)
	{
		ft_lstadd_tokens(&lst, (create_tokens(infile[0], REDIR_IN)));
		ft_lstadd_tokens(&lst, (create_tokens(infile[1], INFILE)));
	}
	ft_lstadd_tokens(&lst, (create_tokens(cmd[0], CMD)));
	ft_lstadd_tokens(&lst, (create_tokens(cmd[1], WORD)));
	if (outfile)
	{
		ft_lstadd_tokens(&lst, (create_tokens(outfile[0], REDIR_OUT)));
		ft_lstadd_tokens(&lst, (create_tokens(outfile[1], OUTFILE)));
	}
	return (lst);
}

static t_process	*create_process(char infile[2][10], char cmd[2][10], char outfile[2][10])
{
	t_process	*process;

	process = (t_process *)malloc(sizeof(t_process));
	process->section_cmd = NULL;
	process->section_cmd_id = 0;
	process->list_tokens = make_list_tokens(infile, cmd, outfile);
	process->pid = 0;
	process->next = NULL;
	return (process);
}

t_process	*create_list_process(void)
{
	//char	infile[2][10] = {"<", "infile"};
	//char	outfile[2][10] = {">", "outfile"};
	//char	outfile2[2][10] = {">", "outfile2"};
	char	cmd1[2][10] = {"ls", "-l"};
	char	cmd3[2][10] = {"wc", "-l"};
	char	cmd2[2][10] = {"ls", "-l"};
	t_process	*proces1;
	t_process	*proces2;
	t_process	*proces3;
	t_process	*list;

	list = NULL;
	proces1 = create_process(NULL, cmd1, NULL);
	proces2 = create_process(NULL, cmd2, NULL);
	proces3 = create_process(NULL, cmd3, NULL);
	
	ft_lstadd_process(&list, proces1);
	ft_lstadd_process(&list, proces2);
	ft_lstadd_process(&list, proces3);
	return (list);	
}

// int	main(void)
// {
// 	t_process	*list;
// 	t_process	*current;
// 	t_tokens	*tmp;
	
// 	list = create_list_process();
// 	current = list;
// 	while (current)
// 	{
// 		tmp = current->list_tokens;
// 		while (tmp)
// 		{
// 			printf("%s ", tmp->value);
// 			tmp = tmp->next;
// 		}
// 		printf("\n");
// 		current = current->next;
// 	}
// 	clear_process_list(&list);
// 	return (0);
// }