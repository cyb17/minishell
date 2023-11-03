/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:14:53 by yachen            #+#    #+#             */
/*   Updated: 2023/11/03 11:54:02 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_in(char *infile)
{
	int	fdin;

	fdin = 0;
	fdin = open(infile, O_RDONLY);
	if (fdin == -1)
	{
		printf("Error: %s: %s", infile, strerror(errno));
		return (-1);
	}
	return (fdin);
}

// cette fontion possede 2 mode :
// T pour O_TRUNC pour >
// A pour O_APPEND pour >>
int	redirect_out(char *outfile, char mode)
{
	int	fdout;

	fdout = 0;
	if (mode == 'T')
		fdout = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (mode == 'A')
		fdout = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fdout == -1)
	{
		printf("Error: %s: %s", outfile, strerror(errno));
		return (-1);
	}
	return (fdout);
}

// /dev/urandom est un fichier qui est genere avec un contenu aleatoire
// le choix du nom de fichier here_doc se fait a partir de ce fichier. 
char	*create_hdname(void)
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

// cette fonction lit l'entree std et
// ecrit e contenu dans here_doc.
int	write_to_hd(int here_doc, char *limiter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_putstr_fd("Error: write_to_hd: get_next_line", 2);
			return (-1);
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
	return (0);
}

// la fonction retourne le path du fichier
// here_doc a ouvrir en cas de reussite si non NULL.
char	*ft_here_doc(char *limiter)
{
	char	*hd_path;
	int		here_doc;

	hd_path = create_hdname();
	if(!hd_path)
	{
		ft_putstr_fd("Error: ft_here_doc: creat_hdname", 2);
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
		free(hd_path);
		return (NULL);
	}
	return (hd_path);
}

/*
int	main(void)
{
	char	buffer[10];
	char	*infile;
	
	infile = ft_here_doc("end");

	read(redirect_in(infile), buffer, 5);
	printf("%s\n", buffer);
	//ft_putstr_fd("\ntest\n", redirect_out("test", 'A'));
	free(infile);
	return (0);
}*/