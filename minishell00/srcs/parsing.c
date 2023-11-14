/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:12:48 by nap               #+#    #+#             */
/*   Updated: 2023/11/14 18:16:33 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	first_readind(char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i] && i <= (int)my_strlen(input))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			j = check_quotes(input, input[i], i);
			if (i == j)
				return (false);
			else
				i = j;
		}
		i++;
	}
	return (true);
}

char	*delete_quotes(char *s)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = NULL;
	while (*s && s[i] != '\0' && i < ((int)ft_strlen(s)))
	{
		if (s && (s[i] == '\'' && s[i + 1] == '\'') 
			&& between_quotes(s, i + 1) == i)
			i = i + 2;
		else if (s && (s[i] == '"' && s[i + 1] == '"'))
			i = i + 2;
		else 
		{
			if (cpy == NULL)
				cpy = ft_strdup_section(s, i, i + 1);
			else
				cpy = cpychar(s, i, cpy);
			i++;
		}
	}
	return (cpy);
}
bool	valid_char(char c)
{
	if (c == '>' || c == '<')
		return(false);
	else
		return(true);
		
}

/* bool	next_is_valid(char *l, int i, char c)
{
	i++;
	while (l[i] && i <= (int)ft_strlen(l))
	{
		while(l[i] == ' ');
			i++;
		if (valid_char(l[i]) == false)
		{
			if (between_quotes(l, i) == i)
				return (false);
			else 
				i = between_quotes(l, i);
		}
		i++;
	}
	return (true);
} */

/* char *manage_meta(char *s)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = NULL;
	while (*s && s[i] != '\0' && i < ((int)ft_strlen(s)))
	{
		if (s && (s[i] == '<' && s[i + 1] == '<') 
			&& between_quotes(s, i + 1) == i)
			{
				if (next_is_valid(s, i + 1, s[i]) == true)
			}
		else if (s && (s[i] == '"' && s[i + 1] == '"'))
			i = i + 2;
		else 
		{
			if (cpy == NULL)
				cpy = ft_strdup_section(s, i, i + 1);
			else
				cpy = cpychar(s, i, cpy);
			i++;
		}
	}
} */

int	ft_parse(char *line, t_process **process, t_list *envlist)
{
	char	*str;
	if (first_readind(line) == false)
	{
		printf("erreur : ");
		return (1);
	}
	str = delete_quotes(line);
	free(line);
	//line = manage_meta(str);
	make_process_list(str, process);
	make_token_list(*process, envlist);
	/* while ((*process))
		{
			printf("Contenu de section_cmd : %s\n", (*process)->section_cmd);
			(*process) = (*process)->next ;
		} */
	return (0);
}
