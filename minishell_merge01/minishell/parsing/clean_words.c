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

#include "../../../includes/parsing.h"

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

char	*deepclean(char *s)
{
	char	*cpy;
	int		j;
	int		i;

	j = 0;
	i = 0;
	cpy = NULL;
	while (*s && s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (check_quotes(s, s[i], i) > i)
			{
				j = check_quotes(s, s[i], i);
				i++;
				while (i < j)
				{
					cpy = cpychar(s, i, cpy);
					i++;
				}
			}
		}
		else
			cpy = cpychar(s, i, cpy);
		i++;
	}
	return (cpy);
}

bool	is_exp_char(char c)
{
	if ((c >= '0' && c <= '9') || c == '_' || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (true);
	else
		return (false);
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
	if (s && (s[i] == '"' && s[len - 1] == '"')
		&& (check_quotes(s, s[i], i) == (len - 1)))
	{
		i++;
		while (i < (len - 1))
		{
			if (s[i] != '$')
			{
				cpy = cpychar(s, i, cpy);
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
				while (is_exp_char(s[i]) == true)
					i++;
			}
		}
		return (cpy);
	}
	if (s && (s[i] == '\'' && s[len - 1] == '\'') 
		&& (check_quotes(s, s[i], i) == (len - 1)))
	{
		i++;
		while (i < (len - 1))
		{
			cpy = cpychar(s, i, cpy);
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
				while (is_exp_char(s[i]) == true)
					i++;
			}
			if (cpy == NULL && i < len)
				cpy = ft_strdup_section(s, i, i + 1);
			else if (i < len)
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
		if (cpy != NULL)
		{
			cpy2 = deepclean(cpy);
			free(cpy);
			return (cpy2);
		}
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
