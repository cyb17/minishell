/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:12:48 by nap               #+#    #+#             */
/*   Updated: 2023/11/13 17:36:13 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	first_readind(char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i] && i <= (int)my_strlen(input))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			j = check_quotes(input, input[i], i);
			if (i == j)
				return (false);
			else
				i = j;
		}
		i++;
	}
	return (true);
}

// bool	is_valid(char *l)
// {
// 	int	i;

// 	i = 0;
// 	while (l[i] && i <= (int)ft_strlen(l))
// 	{
// 		if (valid_char(l[i]) == false)
// 		{
// 			if (between_quotes(l, i) == i)
// 				return (false);
// 			else 
// 				i = between_quotes(l, i);
// 		}
// 		i++;
// 	}
// 	return (true);
// }

char	*delete_quotes(char *s)
{
	int		i;
	char	*cpy;
	char	*tmp;
	char	*cpy2;

	i = 0;
	cpy = NULL;
	while (*s && s[i] != '\0' && i < ((int)ft_strlen(s) - 1))
	{
		if (s && (s[i] == '\'' && s[i + 1] == '\''))
			i = i + 2;
		else if (s && (s[i] == '"' && s[i + 1] == '"'))
			i = i + 2;
		else 
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
	}
	return (cpy);
}

int	ft_parse(char *line, t_process **process, t_list *envlist)
{
	char	*str;
	if (first_readind(line) == false)
	{
		printf("erreur : ");
		return (1);
	}
	str = delete_quotes(line);
	free(line);
	make_process_list(str, process);
	make_token_list(*process, envlist);
	/* while ((*process))
		{
			printf("Contenu de section_cmd : %s\n", (*process)->section_cmd);
			(*process) = (*process)->next ;
		} */
	return (0);
}
