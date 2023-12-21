/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:44:32 by yachen            #+#    #+#             */
/*   Updated: 2023/12/21 12:53:20 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

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

// Check if var's name is correct to be exported
int	check_var_name(char *arg)
{
	int	i;

	i = 0;
	if (!arg || (ft_isalpha(arg[0]) == 0 && arg[0] != '_'))
		return (-1);
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalpha(arg[i]) == 0 && arg[i] != '_'
			&& ft_isdigit(arg[i]) == 0)
		{
			if (arg[i] == '+' && arg[i + 1] == '=')
				return (0);
			return (-1);
		}
		i++;
	}
	return (0);
}

// Malloc espace to stock the name and the value of the var to be exported
int	mallc(char **name, char **value, int n_l, int v_l)
{
	*name = (char *)malloc(sizeof(char) * n_l + 1);
	if (!(*name))
		return (-1);
	*value = (char *)malloc(sizeof(char) * v_l + 1);
	if (!(*value))
	{
		free(*name);
		return (-1);
	}
	return (0);
}

// Copy src to dest until caracter given 
void	cpy_until_c(char *dest, char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

// Split arg's name and value than stock them in different str
int	split_arg(char *arg, t_var *var)
{
	if (var->pl == -1 && var->eq == -1)
	{
		var->nm = ft_strdup(arg);
		if (var->nm)
			return (0);
	}
	else if (var->pl != -1)
	{
		if (mallc(&var->nm, &var->val, var->pl, var->len - var->pl - 1) == 0)
		{
			cpy_until_c(var->nm, arg, '+');
			cpy_until_c(var->val, arg + (var->pl + 1), '\0');
			return (0);
		}
	}
	else if (var->eq != -1)
	{
		if (mallc(&var->nm, &var->val, var->eq, var->len - var->eq) == 0)
		{
			cpy_until_c(var->nm, arg, '=');
			cpy_until_c(var->val, arg + var->eq, '\0');
			return (0);
		}
	}
	return (-1);
}
