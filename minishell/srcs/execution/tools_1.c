/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:17:31 by yachen            #+#    #+#             */
/*   Updated: 2023/12/22 19:12:00 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// Ouvre infile en fdin
void	redirect_in(int *fdin, char *infile)
{
	if (*fdin != STDIN_FILENO && *fdin != -1)
		close(*fdin);
	*fdin = open(infile, O_RDONLY);
	if (*fdin == -1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(infile, 2);
		perror(" ");
		return ;
	}
}

// Ouvre fdout en outfile et possede 2 mode :
// T pour O_TRUNC pour >
// A pour O_APPEND pour >>
void	redirect_out(int *fdout, char *outfile, char mode)
{
	if (*fdout != STDOUT_FILENO && *fdout != -1)
		close(*fdout);
	if (mode == 'T')
		*fdout = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (mode == 'A')
		*fdout = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (*fdout == -1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(outfile, 2);
		perror(" ");
		return ;
	}
}

static void	loop_redir_in(t_tokens *tokens, int *fdin)
{
	while (tokens->next && tokens->next->type == INFILE)
	{
		redirect_in(fdin, tokens->next->value);
		if (*fdin == -1)
			break ;
		if (tokens->next)
			tokens = tokens->next;
	}
}

// Browse tokens list, and fixe the fdin and fdout at the end of browse
// if <infile is found it's will be opened
// if there is another <infile the precedent will be closed and fdin=newone
// same for outfile
int	open_fdin_fdout(int *fdin, int *fdout, t_process *prcs)
{
	t_tokens	*tokens;

	tokens = prcs->list_tokens;
	while (tokens)
	{
		if (tokens->type == REDIR_IN)
			loop_redir_in(tokens, fdin);
		else if (tokens->type == REDIR_OUT && tokens->next->type == OUTFILE)
			redirect_out(fdout, tokens->next->value, 'T');
		else if (tokens->type == APPEN && tokens->next->type == OUTFILE)
			redirect_out(fdout, tokens->next->value, 'A');
		else if (tokens->type == HEREDOC)
			redirect_in(fdin, prcs->heredoc);
		if ((*fdin == -1) || (*fdout == -1))
			return (-1);
		tokens = tokens->next;
	}
	return (0);
}
