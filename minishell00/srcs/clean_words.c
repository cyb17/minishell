/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:02:21 by achevala          #+#    #+#             */
/*   Updated: 2023/11/10 21:05:07 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// bool	varcmp(char *model, char *str)
// {
// 	int	i;
// 	i = 0;
// 	while (model[i] && model[i] != '=')
// 	{
// 		if (model[i] != str[i])
// 			return (0);
// 		i++;
// 	}
// 	if (str[i] == '=')
// 		return (1);
// 	return (0);
// }

char    *clean_word(char *s, t_list **envlist)
{
    int     len;
    int     i;
    char    *tmp;
    char    *cpy;
	char	*cpy2;

	if (s)
    	len = my_strlen(s);
    i = 0;
	cpy = NULL;
    if (s && (s[i] == '"' && s[len - 1] == '"'))
    {
		i++;
        while (i < (len - 2))
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
				if (tmp != NULL)
				{
					cpy2 = cpy;
					cpy = my_strjoin(cpy2, tmp);
					if (cpy2)
						free(cpy2);
					i++;
				}
				while ((s[i] >= '0' && s[i] <= '9')|| s[i] == '_'
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
				if (tmp != NULL)
				{
					cpy2 = cpy;
					cpy = my_strjoin(cpy2, tmp);
					if (cpy2)
						free(cpy2);
					i++;
				}
				while ((s[i] >= '0' && s[i] <= '9')|| s[i] == '_'
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
		return (cpy);
	}
	return (cpy);
}

// char	*ft_strrchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	while (i >= 0)
// 	{
// 		if (s[i] == (unsigned char)c)
// 			return ((char *)&s[i]);
// 		i--;
// 	}
// 	return (NULL);
// }

// int	*ft_strrchr_pos(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	while (i >= 0)
// 	{
// 		if (s[i] == (unsigned char)c)
// 			return ((char *)&s[i]);
// 		i--;
// 	}
// 	return (NULL);
// }

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

