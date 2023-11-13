/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   clean_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:02:21 by achevala          #+#    #+#             */
/*   Updated: 2023/11/11 21:00:45 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cpychar(char *s, int i, char *cpy)
{
	char	*cpy2;
	char	*tmp; 

	if (cpy == NULL)
		cpy = ft_strdup_section(s, i, i + 1);
	else
	{
		tmp = ft_strdup_section(s, i, i + 1);
		cpy2 = cpy;
		cpy = my_strjoin(cpy2, tmp);
		if (cpy2)
			free(cpy2);
		if (tmp != NULL)
			free(tmp);
	}
	return (cpy);
}

/* void	deepclean(char *s)
{
	char	*cpy;
	int		j;
	int		i;

	j = 0;
	i = 0;
	cpy = NULL;
	while (*s && s[i] != '\0')
	{
		if (s[j] == '\'' || s[j] == '"')
		{
			if (check_quotes(s, s[j], j) > j)
			{
				i = check_quotes(s, s[j], j);
				while (j < i)
				{
					cpy = cpychar(s, j, cpy);
					j++;
				}
			else
				cpy = cpychar(s, j, cpy);

		}
		j++; */

void	deepclean(char *s)
{
	char	*cpy;
	int		j;
	int		i;

	j = 0;
	i = 0;
	cpy = NULL;
	while (*s && s[i] != '\0')
	{
		if (s[j] == '\'' || s[j] == '"')
		{
			if (between_quotes(s, i) == i)
				i++;
			else
				cpy = cpychar(s, i, cpy);

		}
		else
		{
			cpy = cpychar(s, i, cpy);
			i++;
		}
	}

}
char	*clean_word(char *s, t_list **envlist)
{
	int		len;
	int		i;
	char	*tmp;
	char	*cpy;
	char	*cpy2;

	if (s)
		len = my_strlen(s);
	i = 0;
	cpy = NULL;
	if (s && (s[i] == '"' && s[len - 1] == '"'))
	{
		i++;
		while (i < (len - 1))
		{
			if (s[i] != '$')
			{
				if (cpy == NULL)
					cpy = ft_strdup_section(s, i, i + 1);
				else
				{
					tmp = ft_strdup_section(s, i, i + 1);
					cpy2 = cpy;
					cpy = my_strjoin(cpy2, tmp);
					if (cpy2)
						free(cpy2);
					if (tmp != NULL)
						free(tmp);
				}
				i++;
			}
			if (s[i] == '$')
			{
				tmp = expand_value(s, i, envlist);
				i++;
				if (tmp != NULL)
				{
					cpy2 = cpy;
					cpy = my_strjoin(cpy2, tmp);
					if (cpy2)
						free(cpy2);
					i++;
				}
				while ((s[i] >= '0' && s[i] <= '9') || s[i] == '_'
					|| (s[i] >= 'a' && s[i] <= 'z')
					|| (s[i] >= 'A' && s[i] <= 'Z'))
					i++;
			}
		}
		return (cpy);
	}
	if (s && (s[i] == '\'' && s[len - 1] == '\''))
	{
		i++;
		while (i < (len - 1))
		{
			if (cpy == NULL)
				cpy = ft_strdup_section(s, i, i + 1);
			else
			{
				tmp = ft_strdup_section(s, i, i + 1);
				cpy2 = cpy;
				cpy = my_strjoin(cpy2, tmp);
				if (cpy2)
					free(cpy2);
				if (tmp != NULL)
					free(tmp);
			}
			i++;
		}
		return (cpy);
	}
	if (s)
	{
		while (i < len)
		{
			if (s[i] == '$')
			{
				tmp = expand_value(s, i, envlist);
				i++;
				if (tmp != NULL)
				{
					cpy2 = cpy;
					cpy = my_strjoin(cpy2, tmp);
					if (cpy2)
						free(cpy2);
					i++;
				}
				while ((s[i] >= '0' && s[i] <= '9') || s[i] == '_'
					|| (s[i] >= 'a' && s[i] <= 'z')
					|| (s[i] >= 'A' && s[i] <= 'Z'))
					i++;
			}
			if (cpy == NULL)
				cpy = ft_strdup_section(s, i, i + 1);
			else
			{
				tmp = ft_strdup_section(s, i, i + 1);
				cpy2 = cpy;
				cpy = my_strjoin(cpy2, tmp);
				if (cpy2)
					free(cpy2);
				if (tmp != NULL)
					free(tmp);
			}
			i++;
		}
		deepclean(&cpy);
		return (cpy);
	}
	return (cpy);
}

size_t	my_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
