/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:25:58 by achevala          #+#    #+#             */
/*   Updated: 2023/12/21 20:50:29 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*manage_exp_end(t_p *p, t_list **envlist)
{
	char	*tmp;

	tmp = NULL;
	tmp = expand_value(p->s3, p->i, envlist);
	p->i++;
	if (tmp != NULL && (p->i >= p->len1 || p->s3[p->i] == '\0'))
		return (tmp);
	if (is_exp_char(p->s3[p->i]) == true)
	{
		while (is_exp_char2(p->s3[p->i]) == true)
			p->i++;
		return (tmp);
	}
	else if (p->s3[p->i] == '0')
	{
		p->i++;
		return (ft_strdup_part(p->all->argv0, 2, ft_strlen(p->all->argv0)));
	}
	else if (p->s3[p->i] == '?')
	{
		p->i++;
		return (ft_itoa(g_signal));
	}
	return (ft_strdup_part(p->s3, p->i - 1, p->i));
}

char	*manage_expand(t_p *p, t_list **envlist)
{
	if ((p->s3[p->i + 1] == '\'' && p->s3[p->i + 2] == '\'')
		|| (p->s3[p->i + 1] == '"' && p->s3[p->i + 2] == '"'))
	{
		p->i = p->i + 3;
		return (NULL);
	}
	if (b_q_exp2(p->s3, p->i) == p->i && (p->s3[p->i + 1] == '\''
			|| p->s3[p->i + 1] == '"'))
	{
		p->i++;
		return (NULL);
	}
	if (p->s3[p->i + 1] >= '1' && p->s3[p->i + 1] <= '9')
	{
		p->i = p->i + 2;
		return (NULL);
	}
	if ((p->s3[p->i + 1] == '$' || p->s3[p->i + 1] == '\''
			|| p->s3[p->i + 1] == '"' || p->s3[p->i + 1] == '\0'))
	{
		p->i++;
		return (ft_strdup_part(p->s3, p->i - 1, p->i));
	}
	return (manage_exp_end(p, envlist));
}
