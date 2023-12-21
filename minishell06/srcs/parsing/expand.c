/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:32:42 by achevala          #+#    #+#             */
/*   Updated: 2023/12/21 20:30:12 by achevala         ###   ########.fr       */
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
	if (s[i + 1] == ' ')
		return (ft_strdup_part(s, i, i + 2));
	if (s[i + 1] == '?' || s[i + 1] == '0')
		return (NULL);
	tmp = s;
	expand_value_end(i, &tmp, &j);
	to_expand = get_var_to_exp(tmp);
	expanded = my_getenv(to_expand, *envlist);
	free(to_expand);
	to_expand = NULL;
	if (!expanded || is_only_space2(expanded) == false)
	{
		if (expanded)
			free(expanded);
		expanded = NULL;
		return (NULL);
	}
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
	while (is_exp_char2(*s0) == true)
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
