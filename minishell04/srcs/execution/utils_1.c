/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:17:31 by yachen            #+#    #+#             */
/*   Updated: 2023/12/08 17:05:49 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// Free int **pipefd
void	free_pipefd(int **pipefd, int nb_pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
		free(pipefd[i++]);
	free(pipefd);
}

// Pipe() pipefd[i]
int	pipe_pipefd(t_tab *tab, int i)
{
	if (i < tab->nb_pipe)
	{
		if ((pipe(tab->pipefd[i])) < 0)
		{
			if (i != 0)
			{
				close(tab->pipefd[i - 1][0]);
				close(tab->pipefd[i - 1][1]);
			}
			return (-1);
		}
	}
	return (0);
}

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

// Browse tokens list, and fixe the fdin and fdout at the end of browse
// if <infile is found it's will be opened
// if there is another <infile the precedent will be closed and fdin=newone
// same for outfile
int	open_fdin_fdout(int *fdin, int *fdout, t_tokens *tokens)
{
	char	*here_doc;

	while (tokens)
	{
		if (tokens->type == REDIR_IN && tokens->next->type == INFILE)
			redirect_in(fdin, tokens->next->value);
		else if (tokens->type == REDIR_OUT && tokens->next->type == OUTFILE)
			redirect_out(fdout, tokens->next->value, 'T');
		else if (tokens->type == APPEN && tokens->next->type == OUTFILE)
			redirect_out(fdout, tokens->next->value, 'A');
		else if (tokens->type == HEREDOC)
		{
			here_doc = ft_here_doc(tokens->next->value);
			redirect_in(fdin, here_doc);
			free(here_doc);
		}
		if ((*fdin == -1) || (*fdout == -1))
			return (-1);
		tokens = tokens->next;
	}
	return (0);
}