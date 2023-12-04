/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:32:42 by achevala          #+#    #+#             */
/*   Updated: 2023/12/04 16:53:05 by yachen           ###   ########.fr       */
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

// char	*expand_value(char *s, int i, t_list **envlist)
// {
// 	char	*to_expand;
// 	char	*expanded;
// 	char	*tmp;
// 	int		j;

// 	if (s[i + 1] == ' '
// 		|| (s[i + 1] == '"' && between_quotes(s, i) > i))
// 		return (ft_strdup_section(s, i, i + 1));
// 	else if (s[i + 1] == '?' && ((s[i + 2] == '\0')
// 		|| (s[i + 2] == '$')
// 		|| ((s[i + 2] == '"' && between_quotes(s, i) > i))))
// 		return (ft_strdup_section(s, i, i + 2));
// 	j = 0;
// 	tmp = s;
// 	while (j <= i)
// 	{
// 		tmp++;
// 		j++;
// 	}
// 	to_expand = get_var_to_exp(tmp);
// 	expanded = my_getenv(to_expand, *envlist);
// 	free(to_expand);
// 	if (!expanded)
// 		return (NULL);
// 	return (expanded);
// }
char	*expand_value(char *s, int i, t_list **envlist)
{
	char	*to_expand;
	char	*expanded;
	char	*tmp;
	int		j;

	if (s[i + 1] == ' ' || s[i + 1] == '\0'
		|| (s[i + 1] == '"' && between_quotes(s, i) > i))
		return (ft_strdup_section(s, i, i + 1));
	else if (s[i + 1] == '?' && ((s[i + 2] == '\0') || (s[i + 2] == ' '
			|| (s[i + 2] == '$')) || ((s[i + 2] == '"'
			&& between_quotes(s, i) > i))))
		return (ft_strdup_section(s, i, i + 2));
	j = 0;
	tmp = s;
	while (j <= i)
	{
		tmp++;
		j++;
	}
	to_expand = get_var_to_exp(tmp);
	expanded = my_getenv(to_expand, *envlist);
	free(to_expand);
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
	while (is_ok(*s0) == true)
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
