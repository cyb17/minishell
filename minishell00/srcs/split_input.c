/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:58:07 by nap               #+#    #+#             */
/*   Updated: 2023/11/13 16:27:53 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_process	*create_process(char *s, int start, int end, int id)
{
	t_process	*process;

	process = (t_process *)malloc(sizeof(t_process));
	if (!process)
	{
		ft_putstr_fd("error: create_process: malloc failed", 2);
		return (NULL);
	}
	process_init(process);
	process->section_cmd = ft_strdup_section(s, start, end);
	process->section_cmd_id = id;
	return (process);
}

void	make_process_list(char *line, t_process **list_process)
{
	t_process	*new_process;
	int			i;
	int			start;
	int			id;

	// list_process = (t_process **)malloc(sizeof(t_process *));
	/* list_process = (t_process *)malloc(sizeof(t_process *));
	if (list_process == NULL)
	{
		ft_putstr_fd("error: make_proces_list: malloc failed", 2);
		return (NULL);
	} */
	new_process = NULL;
	i = 0;
	start = 0;
	id = 1;
	while (line[i] && i <= (int)my_strlen(line))
	{
		if (line[i] == '|')
		{
			if (between_quotes(line, i) == i)
			{
				new_process = create_process(line, start, i, id);
				ft_procsadd_back(list_process, new_process);
				start = i + 1;
			}
			id++;
		}
		i++;
	}
	if (id == 0)
	{
		new_process = create_process(line, 0, my_strlen(line), 1);
		ft_procsadd_back(list_process, new_process);
	}
	else
	{
		new_process = create_process(line, start, (int)my_strlen(line), id + 1);
		ft_procsadd_back(list_process, new_process);
	}
	//printf(" PROCESS 1 = %s\n", (*list_process)->section_cmd);
}

t_tokens	*create_tokens(char *str, int id)
{
	t_tokens	*tokens;

	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	if (!tokens)
	{
		ft_putstr_fd("error: create_tokens: malloc failed", 2);
		return (NULL);
	}
	token_init(tokens);
	tokens->value = ft_strdup(str);
	printf("token value = %s\n", tokens->value);
	tokens->token_id = id;
	return (tokens);
}

void	make_token_list(t_process *process, t_list *envlist)
{
	// t_tokens	**list_token;
	t_tokens	*new_token;
	int			id;
	int			i;
	char		**words;
	char		*cleaned;

	/* list_token = (t_tokens **)malloc(sizeof(t_tokens *));
	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (list_token == NULL)
	{
		ft_putstr_fd("error: make_proces_list: malloc failed", 2);
	} */
	//process->list_tokens;
	new_token = NULL;
	while (process != NULL)
	{
		id = 0;
		i = 0;
		words = ft_split_minishell(process->section_cmd, ' ');
		print_tab(words);
		while (words[i] != NULL)
		{
			id++;
			cleaned = clean_word(words[i], &envlist);
			new_token = create_tokens(cleaned, id);
			ft_tokenadd_back(&process->list_tokens, new_token);
			i++;
		}
		freetab(words);
		process = process->next;
	}
	//process = head;
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0' && s[i])
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
