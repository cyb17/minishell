/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:50:16 by achevala          #+#    #+#             */
/*   Updated: 2023/12/09 13:05:18 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

bool	my_strnstr(char *big, char *little, int len)
{
	int		i;
	int		j;
	char	*src;
	char	*tofind;

	src = big;
	tofind = little;
	i = 0;
	if (little[0] == '\0')
		return (src);
	while (src[i] && i < len)
	{
		j = 0;
		while (src[i + j] == tofind[j])
		{	
			j++;
			if (tofind[j] == '\0' && (i + j <= len))
				return (true);
		}
		i++;
	}	
	return (false);
}

bool	redir_err1(char *s, t_all *all, int i)
{
	if (s[i] != '\0' && s[i + 1] != '\0' && s[i + 2] != '\0'
		&& (s[i] == '<' || s[i] == '>') && (s[i + 1] == '<'
			|| s[i + 1] == '>') && (s[i + 2] == '<' || s[i + 2] == '>')
		&& b_q(s, i) == i)
		return (pick_redir_error(s, all, i));
	if (b_q(s, i) == i && s[i] != '\0' && s[i + 1] != '\0'
		&& (s[i] == '<' && s[i + 1] == '>'))
		return (ft_error(ERROR_NEWLINE, all, 2));
	if (b_q(s, i) == i && s[i] != '\0' && s[i + 1] != '\0'
		&& (s[i] == '>' && s[i + 1] == '<'))
		return (ft_error(ERROR_REDIR4, all, 2));
	return (true);
}

bool	redir_err2(char *s, t_all *all, int i, bool *flag)
{
	if (b_q(s, i) == i && s[i] != '\0'
		&& ((s[i] == '<' && (s[i + 1] != '<')) || (s[i] == '>'
				&& s[i + 1] != '>')))
	{
		if ((*flag) == true)
		{
			if (s[i] == '<')
				return (ft_error(ERROR_REDIR4, all, 2));
			if (s[i] == '>')
				return (ft_error(ERROR_REDIR3, all, 2));
		}
		(*flag) = true;
		if ((s[i + 1] == '\0' && i == 0) || (s[i + 1] == '\0'))
		{
			if (s[i] == '<')
				return (ft_error(ERROR_REDIR4, all, 2));
			if (s[i] == '>')
				return (ft_error(ERROR_REDIR3, all, 2));
		}
	}
	return (true);
}

bool	redir_err3(char *s, t_all *all, int *i, bool *flag)
{
	if (b_q(s, (*i)) == (*i) && s[(*i)] != '\0' && s[(*i) + 1] != '\0'
		&& ((s[(*i)] == '<' && (s[(*i) + 1] == '<')) || (s[(*i)] == '>'
				&& s[(*i) + 1] == '>')))
	{
		if ((*flag) == true)
		{
			if (s[(*i)] == '<' && (s[(*i) + 1] == '<'))
				return (ft_error(ERROR_REDIR2, all, 2));
			if (s[(*i)] == '>' && (s[(*i) + 1] == '>'))
				return (ft_error(ERROR_REDIR1, all, 2));
		}
		(*flag) = true;
		if ((s[(*i) + 2] == '\0' && (*i) == 0) || s[(*i) + 2] == '\0')
		{
			if (s[(*i)] == '<')
				return (ft_error(ERROR_REDIR2, all, 2));
			if (s[(*i)] == '>')
				return (ft_error(ERROR_REDIR1, all, 2));
		}
		(*i)++;
	}
	return (true);
}
