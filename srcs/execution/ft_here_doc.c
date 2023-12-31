/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:14:53 by yachen            #+#    #+#             */
/*   Updated: 2023/12/13 14:02:01 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// /dev/urandom est un fichier qui est genere avec un contenu aleatoire
// le choix du nom de fichier here_doc se fait a partir de ce fichier. 
static char	*create_hdname(void)
{
	int		urandom_fd;
	char	tmp[6];
	char	name[6];
	char	*here_doc;

	urandom_fd = 0;
	ft_strlcpy(tmp, "/tmp/", 6);
	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd == -1)
	{
		perror("Error: create_hdname: open");
		return (NULL);
	}
	if (read(urandom_fd, name, 5) == -1)
	{
		perror("Error: create_hdname: read");
		return (NULL);
	}
	name[5] = '\0';
	here_doc = ft_strjoin(tmp, name);
	close(urandom_fd);
	return (here_doc);
}

static int	ft_compare(char *limiter, char *str)
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

static int	mini_task(int *save_stdin, int task_num)
{
	if (task_num == 0)
	{
		*save_stdin = dup(STDIN_FILENO);
		if (*save_stdin == -1)
		{
			perror("Error: write_to_hd: dup");
			g_signal = 1;
			return (-1);
		}
	}
	else if (task_num == 1)
	{
		if (isatty(STDIN_FILENO) == 1)
			ft_putstr_fd("Error: write_to_hd: get_next_line\n", 2);
		if (dup2(*save_stdin, STDIN_FILENO) == -1)
		{
			perror("Error: write_to_hd: dup2");
			g_signal = 1;
		}
		close(*save_stdin);
	}
	return (0);
}

// cette fonction lit l'entree std et
// ecrit le contenu dans here_doc.
static int	write_to_hd(int here_doc, char *limiter)
{
	char	*line;
	int		save_stdin;

	line = NULL;
	if (mini_task(&save_stdin, 0) == -1)
		return (-1);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		signal(SIGINT, signal_handler_hd);
		signal(SIGQUIT, SIG_IGN);
		line = get_next_line(STDIN_FILENO);
		if (!line && mini_task(&save_stdin, 1) == 0)
			return (-1);
		close(save_stdin);
		if (ft_compare(limiter, line) == 1)
		{
			free(line);
			return (0);
		}
		write(here_doc, line, ft_strlen(line) + 1);
		free(line);
	}
	return (0);
}

// la fonction retourne le path du fichier here_doc a ouvrir en cas
// de reussite si non NULL.
char	*ft_here_doc(char *limiter)
{
	char	*hd_path;
	int		here_doc;

	hd_path = create_hdname();
	if (!hd_path)
	{
		ft_putstr_fd("Error: ft_here_doc: creat_hdname\n", 2);
		return (NULL);
	}
	here_doc = open(hd_path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (here_doc == -1)
	{
		perror("Error: ft_here_doc:");
		free(hd_path);
		return (NULL);
	}
	if (write_to_hd(here_doc, limiter) == -1)
	{
		close(here_doc);
		free(hd_path);
		return (NULL);
	}
	close(here_doc);
	return (hd_path);
}
