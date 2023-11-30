/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:06:32 by nap               #+#    #+#             */
/*   Updated: 2023/11/29 16:41:09 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "builtins.h"

/* main.c */
int			main(int ac, char **av, char **env);

/* parsing.c */
bool		first_readind(char *input);
int			ft_parse(char *line, t_all *all);


/* utils_parsing.c*/
int			check_quotes(char *input, char c, int i);
int			between_quotes(char *l, int i);
char		*ft_strdup_section(char *s, int start, int end);
void		ft_procsadd_back(t_process **lst, t_process *new);
void		ft_tokenadd_back(t_tokens **lst, t_tokens *new);
//t_process	*ft_proclast(t_process *lst);

/* utils_parsing2.c */
char		*delete_quotes(char *s);
char		*cpychar2(char *s, int i, char *cpy);
char		*cpychar3(char *s, int i, char *cpy);
char 		*add_space(char *s);
char		*add_blank(char *cpy);

/* utils_parsing3.c */
int			manage_num(char *s, int i);

/* init.c */
void		process_init(t_process *process);
int			pars_init(t_p *p, char *line);
void		token_init(t_tokens *tokens);
void		all_init(t_all *all, t_res* res);

/* split_input.c */
void		make_process_list(t_p *p, t_process **list_process);
void		map_list(t_p *p, t_process **list_process, t_process *new, int i);
t_process	*create_process(t_p *p, int end);
void		make_token_list(t_process *process, t_list *envlist, t_p *p);
t_tokens	*create_tokens(char *str, int id);
char 		*input_max(t_all *all, t_list	*envlist);


/* expand .c */
bool		varcmp(char *model, char *str);
char		*find_var(char *var, t_list *list);
char		*my_getenv(char *var, t_list *list);
char		*expand_value(char *s, int i, t_list **envlist);
char		*get_var_to_exp(char *s);

/* clean_words.c */
bool		is_exp_char(char c);
char		*clean_word(char *s, t_list **envlist);
size_t		my_strlen(const char *s);
char		*cpychar(char *s, int i, char *cpy);
char		*deepclean(char *s);


/* ft_split_minishell.c */
int			nb_words(char *s, char c);
int			size_words(char *s, char c);
char		**write_in(char **tab, char *s, char c);
void		freetab(char **tab);
char		**ft_split_minishell(char *s, char c);

/* utils_double.c */
// t_list		*env_to_envlist(char **env);

/* utils_cleaning.c */
char		*ft_strdup_checking(char *s, int start, int end);
char		*my_strjoin(char *s1, char *s2);
bool		is_ok(char c);
char		*ft_cpy(char *str, char *s, int *i);
void		print_tab(char **tab);

/* garbage.c */
void		clear_process_list(t_process *process);
void		clear_tokens_list(t_tokens *list);
void		clean_loop(t_all *all);
void 		clean_pars(t_p *p);

/* token.c */
void		ft_token(t_process *process);
void		read_value(char *value, t_tokens *token);
void		cmd_value(t_tokens *token);

#endif