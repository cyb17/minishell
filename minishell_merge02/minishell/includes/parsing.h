/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:06:32 by nap               #+#    #+#             */
/*   Updated: 2023/12/11 17:20:54 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "builtins.h"

# define ERROR_MSG "Error:\n"
# define ERROR_QUOTES "syntax error unexpected token : quotes\n"
# define ERROR_PROCESS "syntax error near unexpected token `|'\n"
# define ERROR_PROCESS2 "syntax error near unexpected token `||'\n"
# define ERROR_REDIR1 "syntax error near unexpected token `>>'\n"
# define ERROR_REDIR2 "syntax error near unexpected token `<<'\n"
# define ERROR_REDIR3 "syntax error near unexpected token `>'\n"
# define ERROR_REDIR4 "syntax error near unexpected token `<'\n"
# define ERROR_REDIR5 "syntax error near unexpected token `<>'\n"
# define ERROR_NEWLINE "syntax error near unexpected token `newline'\n"
# define ERROR_HSTRING "syntax error unexpected token `<<<'\n"
# define ERROR_M1 "error: create_process: malloc failed\n"
# define ERROR_M2 "error: delete_quote: malloc failed\n"
# define ERROR_M3 "error: add_space: malloc failed\n"
# define ERROR_M4 "error: create_process: malloc failed\n"
# define ERROR_M5 "error: create_tokens: malloc failed\n"
# define ERROR_M6 "error: make_token_list: malloc failed\n"
# define ERROR_M7 "error: token_list: malloc failed\n"
# define ERROR_M8 "error: map_list: malloc failed\n"

/* parsing.c */
bool		first_readind(char *input, t_all *all);
int			ft_parse(char *line, t_all *all);
bool		chk_rdi(char *s, t_all *all);
bool		chk_prc(char *s, t_all *all);
bool		is_only_space(char *s, t_all *all);
int			end_parse(t_all *all, t_list *envlist);

/* utils_parsing.c*/
int			check_quotes(char *input, char c, int i);
int			b_q(char *l, int i);
char		*ft_strdup_section(char *s, int start, int end);
void		ft_procsadd_back(t_process **lst, t_process *new);
void		ft_tokenadd_back(t_tokens **lst, t_tokens *new);

/* utils_parsing2.c */
char		*cpychar2(char *s, int i, char *cpy);
char		*cpychar3(char *s, int i, char *cpy);
char		*add_space(char *s);
char		*add_blank(char *cpy);
int			manage_num(char *s, int i);

/* utils_parsing3.c */
char		*manage_expand(t_p *p, t_list **envlist, char *cpy);
char		*manage_words_p1(t_p *p, t_list **envlist);
char		*manage_words_p2(t_p *p);
char		*manage_words_p3(t_p *p, t_list **envlist);
char		*manage_words_p4(t_p *p, char *cpy);

/* init.c */
void		process_init(t_process *process);
int			pars_init(t_p *p, char *line, t_all *all);
void		token_init(t_tokens *tokens);
void		init_in_write_in(t_p *p);

/* split_input.c */
void		make_process_list(t_p *p, t_process **list_process);
bool		map_list(t_p *p, t_process **list_process, t_process *new, int i);
t_process	*create_process(t_p *p, int end);
bool		make_token_list(t_process *process, t_list *envlist, t_p *p);
t_tokens	*create_tokens(char *str, int id, t_p *p);

/* expand .c */
char		*find_var(char *var, t_list *list);
char		*my_getenv(char *var, t_list *list);
void		expand_value_end(int i, char **tmp, int *j);
char		*expand_value(char *s, int i, t_list **envlist);
char		*get_var_to_exp(char *s);

/* expand_utils.c */
bool		varcmp(char *model, char *str);
bool		is_exp_char(char c);

/* clean_words.c */
char		*clean_word(char *s, t_p *p, t_list **envlist);
char		*cpychar(char *s, int i, char *cpy);
void		deep_clean_in(char *s, int *i, char **cpy);
char		*deepclean(char *s);
char		*delete_quotes(char *s);

/* ft_split_minishell.c */
int			nb_words(char *s, char c);
int			size_words(char *s, char c);
char		**write_in(char **tab, char *s, char c, t_p *p);
void		freetab(char **tab);
char		**ft_split_minishell(char *s, char c, t_p *p);

/* utils_split_minishel.c */
int			nb_words_end(char *s, int *i, char **s0, char c);
void		size_word_end(char *s, int *l, char **s1, char c);
bool		split_mini_loop(char ***tab, t_p *p, char **s3, char *s);
void		end_split_mini(char **s3, char *s, t_p *p);

/* utils_write_in.c */
void		first_loop(t_p *p, char ***tab, char **s2, char *s);
void		second_loop(t_p *p, char ***tab, char **s2, char *s);

/* utils_cleaning.c */
char		*ft_strdup_checking(char *s, int start, int end);
char		*my_strjoin(char *s1, char *s2);
bool		is_ok(char c);
char		*ft_cpy(char *str, char *s, int *i);
/* void		print_tab(char **tab); */

/* garbage_collector.c */
void		clear_process_list(t_process *process);
void		clear_tokens_list(t_tokens *list);
void		clean_loop(t_all *all);
void		clean_pars(t_p *p);
bool		ft_error(char *s, t_all *all, int code);

/* token.c */
void		ft_token(t_process *process);
void		read_value(char *value, t_tokens *token);
void		cmd_value(t_tokens *token);
bool		syntax_token(t_process *process, t_all *all);

/* redir.c */
bool		three_redir(char *s, t_all *all);
bool		four_redir(char *s, t_all *all);
bool		four_redir_end(char *s, t_all *all);
bool		more_redir(char *s, t_all *all);
bool		pick_redir_error(char *s, t_all *all, int i);

/* utils_redir.c */
bool		my_strnstr(char *big, char *little, int len);
bool		redir_err1(char *s, t_all *all, int i);
bool		redir_err2(char *s, t_all *all, int i, bool *flag);
bool		redir_err3(char *s, t_all *all, int *i, bool *flag);

#endif