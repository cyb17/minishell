/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:55:26 by yachen            #+#    #+#             */
/*   Updated: 2023/11/08 10:27:34 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

int	ft_compare(char *limiter, char *str)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] != str[i])
			return (0);
		i++;
	}
	if (limiter[i] == '\0' && str[i] == '\n')
		return (1);
	return (0);
}

void	create_tmpinfile(int *fd)
{
	fd[0] = open("/tmp/tmpinfile", O_CREAT | O_RDONLY, 0644);
	if (fd[0] == -1)
		ft_perror("tmpinfile", 1);
}

void	ft_here_doc(char *limiter)
{
	char	*line;
	int		here_doc;

	here_doc = open("/tmp/here_doc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (here_doc == -1)
		ft_perror("here_doc", 1);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			close(here_doc);
			ft_perror("here_doc", 0);
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
}

void	open_fd_bonus(t_tab *tab, char ***argv, char *outfile, int *argc)
{
	char	*infile;
	int		indice;

	infile = argv[0][1];
	indice = ft_strcmp("here_doc", argv[0][1]);
	if (indice == 1 && *argc >= 6)
	{
		ft_here_doc(argv[0][2]);
		infile = "/tmp/here_doc";
		tab->fdout = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else
		tab->fdout = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tab->fdout == -1)
		ft_perror(outfile, 1);
	tab->fdin = open(infile, O_RDONLY);
	if (tab->fdin == -1)
	{
		ft_printf("Error : %s : No such file or directory\n", infile);
		create_tmpinfile(&tab->fdin);
	}
	if (indice == 0)
		return ;
	*argv = *argv + 1;
	(*argc)--;
}
