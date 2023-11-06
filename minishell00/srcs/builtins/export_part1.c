/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:08:24 by yachen            #+#    #+#             */
/*   Updated: 2023/11/06 17:15:10 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

void	initialize_var(t_var *export, t_var *env)
{
	export->oldvar = NULL;
	export->newvar = NULL;
	export->oldvar_i = 0;
	env->oldvar = NULL;
	env->newvar = NULL;
	env->oldvar_i = 0;
}

void	print_explist(t_list *explist)
{
	t_list	*tmp;

	tmp = explist;
	while (tmp)
	{
		if (printf("export : %s\n", (char *)tmp->content) < 0)
		{
			ft_error("Error: export: print_explist ", strerror(errno));
			return ;
		}	
		tmp = tmp->next;
	}
}

int	create_newvar(char *arg, t_var *env, t_var *export)
{
	export->newvar = ft_lstnew(arg);
	if (!export->newvar)
	{
		write(2, "export: create_newvar: malloc failed", 31);
		return (-1);
	}
	env->newvar = ft_lstnew(arg);
	if (!env->newvar)
	{
		free(export->newvar);
		write(2, "export: create_newvar: malloc failed", 31);
		return (-1);
	}
	return (0);
}
int	ft_export(t_list **envlist, t_list **explist, char *arg)
{
	t_var	export;
	t_var	env;

	initialize_var(&export, &env);
	if (!arg)
		print_explist(*explist);
	else
	{
		if (create_newvar(arg, &export, &env) == -1)
			return (1);
		export.oldvar = find_oldvar(arg, *explist, &export.oldvar_i);
		if (!export.oldvar)
		{	
			ft_lstadd_back(explist, export.newvar);
			add_tolist(envlist, &env, arg);
		}
		else if (export.oldvar && find_caracter(arg, '=') >= 0)
		{
			env.oldvar = find_oldvar(arg, *envlist, &env.oldvar_i);
			replace_var(envlist, explist, &env, &export);
		}
		else
			free_var(&export, &env);
	}
	return (0);
}

/*int	main(int argc, char **argv, char **env)
{
	t_list	*envlist;
	t_list	*explist;

	envlist = NULL;
	explist = NULL;
	printf("teste : %d %s\n", argc, argv[0]);
	envlist = env_to_envlist(env);
	explist = env_to_envlist(env);

	printf("print env list : \n");
	ft_env(envlist);
	printf("\n\n");
	ft_export(&envlist, &explist, "test");
	printf("\n\n");
	ft_export(&envlist, &explist, "test1=");
	ft_export(&envlist, &explist, "test2");
	ft_export(&envlist, &explist, "LSCOLORS=test");
	ft_export(&envlist, &explist, "USER=test");
	ft_export(&envlist, &explist, "SHELL=test");
	ft_export(&envlist, &explist, "LOGNAME=test");
	ft_export(&envlist, &explist, "TERM_PROGRAM=");
	ft_export(&envlist, &explist, "test3=");
	ft_export(&envlist, &explist, "test");
	ft_unset(&envlist, &explist, "test");
	ft_unset(&envlist, &explist, "test1=");
	ft_unset(&envlist, &explist, "te");
	ft_unset(&envlist, &explist, "SHELL");
	ft_env(envlist);
	printf("\n\n");
	ft_unset(&envlist, &explist, NULL);
	ft_export(&envlist, &explist, NULL);
	ft_pwd();
	clear_lst(&envlist);
	clear_lst(&explist);
	return (0);
}*/