/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:19:51 by achevala          #+#    #+#             */
/*   Updated: 2023/12/19 16:42:59 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	varcmp(char *model, char *str)
{
	int	i;

	i = 0;
	while (model[i] && model[i] != '=')
	{
		if (model[i] != str[i])
			return (0);
		i++;
	}
	if (str[i] == '=')
		return (1);
	return (0);
}

bool	is_exp_char2(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (true);
	else
		return (false);
}

bool	is_exp_char(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (true);
	else
		return (false);
}

int	b_q_exp(char *l, int i)
{
	int		j;

	j = 0;
	if (i < 0)
		return (i);
	while (l[j] && j <= (int)ft_strlen(l) && j < i)
	{
		if (l[j] == '\'')
		{
			if (check_quotes(l, l[j], j) > i)
				return (check_quotes(l, l[j], j));
			else
				j = check_quotes(l, l[j], j);
		}
		j++;
	}
	return (i);
}

int	b_q_exp2(char *l, int i)
{
	int		j;

	j = 0;
	if (i < 0)
		return (i);
	while (l[j] && j <= (int)ft_strlen(l) && j < i)
	{
		if (l[j] == '"')
		{
			if (check_quotes(l, l[j], j) > i)
				return (check_quotes(l, l[j], j));
			else
				j = check_quotes(l, l[j], j);
		}
		j++;
	}
	return (i);
}
