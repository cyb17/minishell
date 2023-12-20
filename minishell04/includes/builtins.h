/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:58:07 by yachen            #+#    #+#             */
/*   Updated: 2023/12/02 14:59:29 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "execution.h"

# define GETCWD_SIZE 4096

// builtins_utils1
void	clear_lst(t_list **lst);
t_list	*env_to_envlist(char **env);
int		find_caracter(char *str, char c);
int		stringcmp(char *model, char *str);
t_list	*find_oldvar(char *var, t_list *list, int *i);

// echo
int		ft_echo(char **arg);

// cd
int		ft_cd(t_list **envlist, t_list **explist, char **arg);

// env
int		ft_env(char **arg, t_list *envlist);

// export_part_1
int		export_arg(t_list **envlist, t_list **explist, char *arg);
int		ft_export(t_list **envlist, t_list **explist, char **arg);
//export_part_2
int		join_and_update(t_var *env, t_var *export);
int		replace_and_update(t_var *env, t_var *export);
// export_part_3
void	free_newvar(t_var *export, t_var *env);

// unset
int		ft_unset(t_list **envlist, t_list **explist, char **arg);

// pwd
int		ft_pwd(void);

// exit
int	ft_exit(char **arg, t_res *res);

#endif