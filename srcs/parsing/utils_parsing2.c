/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:41:15 by achevala          #+#    #+#             */
/*   Updated: 2023/12/22 19:46:39 by yachen           ###   ########.fr       */
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

char	*cpychar3(char *s, int i, char *cpy)
{
	if (*s && (i > 0) && i < my_strlen(s) && s[i - 1]
		&& (s[i - 1] == '>' || s[i - 1] == '<') && (s[i] != '>'
			&& s[i] != '<') && ((s[i] != '\'' && s[i] != '"')
			|| b_q(s, i + 1) > i + 1)
		&& (i - 1 >= 0) && b_q(s, i) == i)
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

	i = 0;
	cpy = NULL;
	while (i <= ((int)ft_strlen(s)) && *s && s[i] != '\0')
	{
		if (b_q(s, i) == i && (s[i] >= '0' && s[i] <= '9'))
			i = manage_num(s, i);
		if ((s[i] == '<' || s[i] == '>') && (i - 1 >= 0)
			&& b_q(s, i) == i && s[i - 1] != ' '
			&& (s[i - 1] != '<') && (s[i - 1] != '>'))
		{
			cpy = cpychar2(s, i, cpy);
			i++;
		}
		if (i + 1 <= ((int)ft_strlen(s)) && (i - 1 >= 0) && ((s[i] == '<'
					|| s[i] == '>') && (s[i + 1] != ' ' && s[i + 1] != '<'
					&& s[i + 1] != '>' && s[i - 1] != '<'
					&& s[i - 1] != '>') && b_q(s, i) == i))
			cpy = add_blank(cpy);
		cpy = cpychar3(s, i, cpy);
		i++;
	}
	return (cpy);
}
