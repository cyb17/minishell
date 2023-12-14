/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nap <nap@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:32:42 by achevala          #+#    #+#             */
/*   Updated: 2023/12/13 14:02:46 by nap              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*find_var(char *var, t_list *list)
{
	t_list	*current;

	current = list;
	while (current)
	{
		if (varcmp(var, current->content) == 1)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

char	*my_getenv(char *var, t_list *list)
{
	char	*str;
	char	*tmp;

	tmp = NULL;
	str = find_var(var, list);
	if (str == NULL)
		return (NULL);
	else
		return (my_strjoin((str + (ft_strlen(var) + 1)), tmp));
}

void	expand_value_end(int i, char **tmp, int *j)
{
	(*j) = 0;
	while ((*j) <= i)
	{
		(*tmp)++;
		(*j)++;
	}
}

char	*expand_value(char *s, int i, t_list **envlist)
{
	char	*to_expand;
	char	*expanded;
	char	*tmp;
	int		j;

	j = 1;
	/* while (s[i + j] == '$' || s[i + j] == '?')
		j++;
	if (j > 1)
		return (ft_strdup_section(s, i, i + j)); */
	if (s[i + 1] == ' ' || s[i + 1] == '\0'
		|| (s[i + 1] == '"' && b_q(s, i) > i))
		return (ft_strdup_section(s, i, i + 1));
	else if (s[i + 1] == '?' && ((s[i + 2] == '\0') || (s[i + 2] == ' ')
			|| ((s[i + 2] == '"' && b_q(s, i) > i))))
		return (ft_strdup_section(s, i, i + 2));
	tmp = s;
	expand_value_end(i, &tmp, &j);
	to_expand = get_var_to_exp(tmp);
	expanded = my_getenv(to_expand, *envlist);
	free(to_expand);
	to_expand = NULL;
	if (!expanded)
		return (NULL);
	return (expanded);
}

char	*get_var_to_exp(char *s)
{
	int			i;
	int			j;
	char		*res;
	char		*s0;

	i = 0;
	j = 0;
	s0 = s;
	while (is_exp_char(*s0) == true)
	{
		s0++;
		i++;
	}
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	s0 = s;
	while (j < i)
	{
		res[j] = *s0;
		j++;
		s0++;
	}
	res[j] = '\0';
	return (res);
}
