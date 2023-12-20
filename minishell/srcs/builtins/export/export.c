/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:53:35 by yachen            #+#    #+#             */
/*   Updated: 2023/12/20 19:32:34 by yachen           ###   ########.fr       */
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

static int	check_var_name(char *arg)
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

static int	mallc(char **name, char **value, int n_l, int v_l)
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

static void	cpy_until_c(char *dest, char *src, char c)
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

static int	split_arg(char *arg, t_var *var)
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

static int	add_to_explist(t_list **explist, t_var *var)
{
	t_list	*old;
	t_list	*new;
	char	*content;

	old = find_oldvar(var->nm, *explist, NULL);
	if (!old)
	{
		if (!var->val)
		{
			content = ft_strdup(var->nm);
			new = ft_lstnew(content);
		}
		else
		{
			content = ft_strjoin(var->nm, var->val);
			new = ft_lstnew(content);
		}
		if (!new)
		{
			if (content)
				free(content);
			return (-1);
		}
		ft_lstadd_back(explist, new);
	}
	else if (old)
	{
		if (find_caracter(old->content, '=') == -1 && var->val)
		{
			content = ft_strjoin(var->nm, var->val);
			free(old->content);
			old->content = content;
		}
		else if (find_caracter(old->content, '=') != -1 && var->pl != -1
			&& var->val && var->val[1] != '\0')
		{
			content = ft_strjoin(old->content, var->val + 1);
			free(old->content);
			old->content = content;
		}
		else if (find_caracter(old->content, '=') != -1 && var->pl == -1
			&& var->val)
		{
			content = ft_strjoin(var->nm, var->val);
			free(old->content);
			old->content = content;
		}
	}
}

int	export_arg(t_list **envlist, t_list **explist, char *arg)
{
	t_var	var;

	var.nm = NULL;
	var.val = NULL;
	var.eq = find_caracter(arg, '=');
	var.pl = find_caracter(arg, '+');
	var.len = ft_strlen(arg);
	var.old = NULL;
	var.new = NULL;
	if (split_arg(arg, &var) == -1)
		return (-1);
	if (var.eq != -1)
		add_to_envlist(envlist, &var);
	add_to_explist(explist, &var);
	free(var.nm);
	free(var.val);
	return (0);
}


// Error = 1 || succes = 0
int	ft_export(t_list **envlist, t_list **explist, char **arg)
{
	int		i;

	i = 1;
	if (!arg[1])
		print_explist(*explist);
	else
	{
		while (arg[i])
		{
			if (check_var_name(arg[i]) == -1)
			{
				ft_putstr_fd("Error: export: ", 2);
				ft_putstr_fd(arg[i], 2);
				ft_putstr_fd(": not a valid identifier\n", 2);
				return (1);
			}
			if (export_arg(envlist, explist, arg[i]) == -1)
				return (1);
			i++;
		}
	}
	return (0);
}
