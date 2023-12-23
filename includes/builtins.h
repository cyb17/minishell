/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:58:07 by yachen            #+#    #+#             */
/*   Updated: 2023/12/22 12:34:54 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "execution.h"

# define GETCWD_SIZE 4096

// utils1
void	clear_lst(t_list **lst);
t_list	*env_to_envlist(char **env);
int		find_caracter(char *str, char c);
int		stringcmp(char *model, char *str);
t_list	*find_oldvar(char *var, t_list *list, int *i);
// utils2
int		go_to(t_list **envlist, char *var_name);

// echo
int		ft_echo(char **arg);

// cd
int		ft_cd(t_list **envlist, t_list **explist, t_builtins *blt);

// env
int		ft_env(char **arg, t_list *envlist);

// export
int		ft_export(t_list **envlist, t_list **explist, char **arg);
// export_tools
void	print_explist(t_list *explist);
int		check_var_name(char *arg);
int		mallc(char **name, char **value, int n_l, int v_l);
void	cpy_until_c(char *dest, char *src, char c);
int		split_arg(char *arg, t_var *var);

// unset
int		ft_unset(t_list **envlist, t_list **explist, char **arg);

// pwd
int		ft_pwd(void);

// exit
int		ft_exit(char **arg, t_res *res);

#endif
