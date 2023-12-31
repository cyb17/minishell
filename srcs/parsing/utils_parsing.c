/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:50:56 by nap               #+#    #+#             */
/*   Updated: 2023/12/18 20:34:46 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	check_quotes(char *input, char c, int i)
{
	bool	inside_quote;
	int		j;

	inside_quote = false;
	j = i;
	i++;
	while (input[i] && i <= (int)ft_strlen(input))
	{
		if (input[i] == c)
		{
			if (inside_quote == false)
			{
				inside_quote = true;
				return (i);
			}
		}
		i++;
	}
	return (j);
}

int	b_q(char *l, int i)
{
	int		j;

	j = 0;
	if (i < 0)
		return (i);
	while (l[j] && j <= (int)ft_strlen(l) && j < i)
	{
		if (l[j] == '"' || l[j] == '\'')
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
/* b_q returns the position of the second quote, after i, 
if l[i] is between quotes, otherwise, it returns i and the char is not
between quotes  */

char	*ft_strdup_part(char *s, int start, int end)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((end - start + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[start] && start < end)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_procsadd_back(t_process **lst, t_process *new)
{
	t_process	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp -> next != NULL)
		tmp = tmp -> next;
	tmp->next = new;
}

void	ft_tokenadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*tmp;

	tmp = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp -> next != NULL)
		tmp = tmp -> next;
	tmp -> next = new;
}
