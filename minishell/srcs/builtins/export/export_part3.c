/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:32:13 by yachen            #+#    #+#             */
/*   Updated: 2023/12/19 16:22:45 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

void	free_newvar(t_var *export, t_var *env)
{
	if(export->newvar)
	{
		if (export->newvar->content)
			free(export->newvar->content);
		free(export->newvar);
	}
	if (env->newvar)
	{
		if (env->newvar->content)
			free(env->newvar->content);
		free(env->newvar);
	}
}

int	check_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

char	*revome_plus(char *str)
{
	int	i;
	char	*newstr;

	i = 0;
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(str)));
	if (!newstr)
		return (NULL);
	while (str[i] && str[i] != '+')
	{
		newstr[i] = str[i];
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		newstr[i -1] = str[i];
		i++;
	}
	newstr[i - 1] = '\0';
	free(str);
	return (newstr);
}

void	print_explist(t_list *explist)
{
	t_list	*tmp;

	tmp = explist;
	while (tmp)
	{
		printf("export : %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}