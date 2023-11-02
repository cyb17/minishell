/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:14:53 by yachen            #+#    #+#             */
/*   Updated: 2023/11/02 17:28:13 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_perror(char *str, int indice)
{
	if (indice == 1)
		perror("Error");
	if (str)
		ft_printf(": %s\n", str);
	exit(EXIT_FAILURE);
}

int	redirect_in(char *infile)
{
	int	fdin;

	fdin = 0;
	fdin = open(infile, O_RDONLY);
	if (fdin == -1)
	{
		perror("Error: open fdin");
		return (-1);
	}
	return (fdin);
}

int	redirect_out(char *outfile, char mode)
{
	int	fdout;

	fdout = 0;
	if (mode == 'T');
		fdout = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (mode == 'A')
		fdout = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fdout == -1)
	{
		perror("Error: open fdout");
		return (-1);
	}
	return (fdout);
}

char	*create_hdpath(void)
{
	int		urandom_fd;
	char	tmp[6];
	char	name[6];
	char	*here_doc;
	
	urandom_fd = 0;
	tmp = "/tmp/";
	urandom_fd = ("dev/urandom", O_RDONLY);
	if (urandom_fd == -1)
	{
		perror("Error: create_hdname");
		return (NULL);
	}
	if (read(urandom_fd, name, 5) == -1)
	{
		perror("Error: create_hdname: read");
		return (NULL);
	}
	name[5] = '\0';
	here_doc = ft_strjoin(tmp, name);
	return (here_doc);
}

void	ft_here_doc(char *limiter, int *infile)
{
	char	*line;
	char	*hd_path;
	int		here_doc;

	hd_path = create_hdname();
	if(!hd_path)
		return ;
	here_doc = open(hd_path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (here_doc == -1)
	{
		perror("Error: ft_here_doc");
		return ;
	}
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			perror("Error: ft_here_doc: get_next_line");
			return ;
		}
		write(here_doc, line, ft_strlen(line) + 1);
		if (ft_compare(limiter, line) == 1)
		{
			close(here_doc);
			free(line);
			break ;
		}
		free(line);
	}
	infile = hd_path; // attention a liberer hd_path une fois fini d'utiliser
}
