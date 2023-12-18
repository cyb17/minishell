/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:45:45 by yachen            #+#    #+#             */
/*   Updated: 2023/12/18 15:12:42 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// Make cmd_tk a char ** to give builtins's fonctions as parameter
static int	builtin_cmd_arg(t_tokens *cmd_tk, t_builtins *builtins)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = cmd_tk;
	while (tmp && (tmp->type == CMD || tmp->type == WORD))
	{
		i++;
		tmp = tmp->next;
	}
	builtins->arg = (char **)malloc(sizeof(char *) * (i + 1));
	if (!builtins->arg)
		return (-1);
	i = 0;
	while (cmd_tk && (cmd_tk->type == CMD || cmd_tk->type == WORD))
	{
		builtins->arg[i] = ft_strdup(cmd_tk->value);
		if (!builtins->arg[i])
			return (-1);
		cmd_tk = cmd_tk->next;
		i++;
	}
	builtins->arg[i] = NULL;
	return (0);
}

// Find wich command is calling and excute it
static int	exe_which_cmd(t_res *res, t_tokens *cmd_tk)
{
	int	rslt;

	rslt = 0;
	if (ft_strcmp("echo", cmd_tk->value) == 1)
		rslt = ft_echo(res->blt->arg);
	else if (ft_strcmp("cd", cmd_tk->value) == 1)
		rslt = ft_cd(&res->blt->envlist, &res->blt->explist, res->blt);
	else if (ft_strcmp("env", cmd_tk->value) == 1)
		rslt = ft_env(res->blt->arg, res->blt->envlist);
	else if (ft_strcmp("export", cmd_tk->value) == 1)
		rslt = ft_export(&res->blt->envlist, &res->blt->explist, res->blt->arg);
	else if (ft_strcmp("unset", cmd_tk->value) == 1)
		rslt = ft_unset(&res->blt->envlist, &res->blt->explist, res->blt->arg);
	else if (ft_strcmp("pwd", cmd_tk->value) == 1)
		rslt = ft_pwd();
	else if (ft_strcmp("exit", cmd_tk->value) == 1)
		rslt = ft_exit(res->blt->arg, res);
	free_tab(res->blt->arg);
	res->blt->arg = NULL;
	return (rslt);
}

// Execute builtins and return their exit status
int	exe_builtins(t_res *res, t_tokens *cmd)
{
	if (builtin_cmd_arg(cmd, res->blt) == -1)
	{
		free_tab(res->blt->arg);
		ft_putstr_fd("Error: exe_builtins: builtin_cmd_arg: malloc failed\n", 2);
		return (1);
	}
	return (exe_which_cmd(res, cmd));
}
