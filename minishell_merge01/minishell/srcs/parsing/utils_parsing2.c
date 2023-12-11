/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nap <nap@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:41:15 by achevala          #+#    #+#             */
/*   Updated: 2023/12/09 22:37:36 by nap              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	manage_num(char *s, int i)
{
	int	j;

	j = i;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == '>' || s[i] == '<')
		return (i);
	else
		return (j);
}

char	*cpychar2(char *s, int i, char *cpy)
{
	char	*cpy2;
	char	*tmp;

	if (i > 0 && (s[i - 1] != '>' || s[i - 1] != '<'))
	{
		tmp = malloc(sizeof(char) * 2);
		if (!tmp)
		{
			ft_putstr_fd("error: cpychar2: malloc failed", 2);
			return (NULL);
		}
		tmp[0] = ' ';
		tmp[1] = '\0';
		cpy2 = cpy;
		cpy = my_strjoin(cpy2, tmp);
		if (cpy2)
			free(cpy2);
		if (tmp != NULL)
			free(tmp);
	}
	cpy = cpychar(s, i, cpy);
	return (cpy);
}

int	my_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*cpychar3(char *s, int i, char *cpy)
{
	if (*s && (i > 0) && i < my_strlen(s) && s[i - 1] 
		&& (s[i - 1] == '>' 
		|| s[i - 1] == '<')
		&& (s[i] != '>' && s[i] != '<') && (i - 1 >= 0) && s[i + 1]
		&& s[i + 1] != '\0')
		cpy = add_blank(cpy);
	if (i < my_strlen(s))
	cpy = cpychar(s, i, cpy);
	return (cpy);
}

char	*add_blank(char *cpy)
{
	char	*cpy2;
	char	*tmp;

	tmp = malloc(sizeof(char) * 2);
	if (!tmp)
	{
		ft_putstr_fd("error: add_blanc: malloc failed", 2);
		return (NULL);
	} 
	tmp[0] = ' ';
	tmp[1] = '\0';
	cpy2 = cpy;
	cpy = my_strjoin(cpy2, tmp);
	if (cpy2)
		free(cpy2);
	if (tmp != NULL)
		free(tmp);
	return (cpy);
}

char	*add_space(char *s)
{
	int		i;
	char	*cpy;
	int		len;

	len = my_strlen(s);
	i = 0;
	cpy = NULL;
	while (*s && s[i] != '\0' && i < len)
	{
		if (b_q(s, i) == i && (s[i] >= '0' && s[i] <= '9'))
			i = (manage_num(s, i) - 1);
		else if ((s[i] == '<' || s[i] == '>') && (i - 1 >= 0)
			&& b_q(s, i) == i && (s[i - 1] != ' ' || s[i + 1] != ' ')
			&& (s[i - 1] != '<') && (s[i - 1] != '>'))
			cpy = cpychar2(s, i, cpy);
		/* else if (s[i + 1] != '\0' && (i - 1 >= 0) && (s[i] == '<'
				|| s[i] == '>') && ((s[i + 1] != ' ') && (s[i + 1] != '<')
				&& (s[i + 1] != '>') && (s[i - 1] != '<') && (s[i - 1] != '>'))
				&& b_q(s, i) == i )
			cpy = add_blank(cpy); */
		else
			cpy = cpychar3(s, i, cpy);
		i++;
	}
	return (cpy);
}
