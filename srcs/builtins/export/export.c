/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:53:35 by yachen            #+#    #+#             */
/*   Updated: 2023/12/22 11:59:54 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

static int	replace_old_content(t_list *old, t_var *var)
{
	char	*content;

	content = NULL;
	if (find_caracter(old->content, '=') == -1 && var->val)
		content = ft_strjoin(var->nm, var->val);
	else if (find_caracter(old->content, '=') != -1 && var->pl != -1
		&& var->val && var->val[1] != '\0')
		content = ft_strjoin(old->content, var->val + 1);
	else if (find_caracter(old->content, '=') != -1 && var->pl == -1
		&& var->val)
		content = ft_strjoin(var->nm, var->val);
	if (!content)
		return (-1);
	free(old->content);
	old->content = content;
	return (0);
}

static int	add_to_explist(t_list **explist, t_var *var)
{
	t_list	*old;
	t_list	*new;
	char	*content;

	content = NULL;
	old = find_oldvar(var->nm, *explist, NULL);
	if (!old)
	{
		if (!var->val)
			content = ft_strdup(var->nm);
		else
			content = ft_strjoin(var->nm, var->val);
		new = ft_lstnew(content);
		if (!new)
		{
			if (content)
				free(content);
			return (-1);
		}
		ft_lstadd_back(explist, new);
	}
	else if (old)
		return (replace_old_content(old, var));
	return (0);
}

static int	add_to_envlist(t_list **envlist, t_var *var)
{
	t_list	*old;
	t_list	*new;
	char	*content;

	content = NULL;
	old = find_oldvar(var->nm, *envlist, NULL);
	if (!old)
	{
		content = ft_strjoin(var->nm, var->val);
		new = ft_lstnew(content);
		if (!new)
		{
			if (content)
				free(content);
			return (-1);
		}
		ft_lstadd_back(envlist, new);
	}
	else if (old)
		return (replace_old_content(old, var));
	return (0);
}

int	export_arg(t_list **envlist, t_list **explist, char *arg)
{
	t_var	var;
	int		rslt;

	rslt = 0;
	var.nm = NULL;
	var.val = NULL;
	var.eq = find_caracter(arg, '=');
	var.pl = find_caracter(arg, '+');
	var.len = ft_strlen(arg);
	if (split_arg(arg, &var) == -1)
		return (-1);
	if (var.eq != -1)
		rslt = add_to_envlist(envlist, &var);
	if (rslt != -1)
		add_to_explist(explist, &var);
	free(var.nm);
	free(var.val);
	return (rslt);
}

// Error = 1 || succes = 0
int	ft_export(t_list **envlist, t_list **explist, char **arg)
{
	int		i;
	int		rslt;

	i = 1;
	rslt = 0;
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
				rslt = 1;
			}
			else if (export_arg(envlist, explist, arg[i]) == -1)
				return (1);
			i++;
		}
	}
	return (rslt);
}
