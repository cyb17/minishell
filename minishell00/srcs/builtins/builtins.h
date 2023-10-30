/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:58:07 by yachen            #+#    #+#             */
/*   Updated: 2023/10/30 16:28:24 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_var
{
	t_list	*oldvar;
	t_list	*newvar;
	int		oldvar_i;
}			t_var;

// utils1
void	clear_lst(t_list **lst);
t_list	*env_to_envlist(char **env);
int		find_caracter(char *str, char c);
int		stringcmp(char *model, char *str);
t_list	*find_oldvar(char *var, t_list *list, int *i);

// echo
void	ft_echo(char *op, char *str);

// env
void	ft_env(t_list *envlist);

// export
void	initialize_var(t_var *export, t_var *env);
void	print_explist(t_list *explist);
int		create_newvar(char *arg, t_var *env, t_var *export);
void	replace(t_list **list, t_list *newvar, int oldvar_i);
void	free_var(t_var *export, t_var *env);
void	add_tolist(t_list **envlist, t_var *env, char *arg);
void	replace_var(t_list **envlst, t_list **explst, t_var *env, t_var *exp);
int		ft_export(t_list **envlist, t_list **explist, char *arg);

// unset
void	ft_unset(t_list **envlist, t_list **explist, char *arg);


#endif
