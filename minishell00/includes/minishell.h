/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:06:32 by nap               #+#    #+#             */
/*   Updated: 2023/11/08 17:47:28 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include <curses.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

enum 	e_tokens_type
{
	CMD = 1,
	WORD = 2,
	INFILE = 3,
	OUTFILE = 4,
	REDIR_IN = 5,
	REDIR_OUT = 6,
	APPEN = 7,
	HEREDOC = 8
};


typedef struct s_tokens
{
	int				token_id;
	int				type;
	char 			*value;
	struct s_tokens	*next; 
}					t_tokens;

typedef struct s_process
{
    char				*section_cmd;
	int					section_cmd_id;
	t_tokens			*list_tokens;
	pid_t				pid;
	struct s_process	*next;
}						t_process;

typedef struct s_data
{
	char				*s;
	int					len;
	struct s_process	*process;
}						t_data;

/* main.c */
int		main(int ac, char **av, char **env);

/* parsing.c */
int		ft_parse(char *line, t_process **process, t_list *envlist);
// bool	is_valid(char *l);
bool	first_readind(char *input);

/* utilis_parsing.c*/
int		check_quotes(char *input, char c, int i);
int		between_quotes(char *l, int i);
char	*ft_strdup_section(char *s, int start, int end);
void	ft_procsadd_back(t_process **lst, t_process *new);
void	ft_tokenadd_back(t_tokens **lst, t_tokens *new);
//t_process	*ft_proclast(t_process *lst);

/* init.c */
void	process_init(t_process *process);
//void	*data_init(t_data *data, char *line);
void	token_init(t_tokens *tokens);

/* split_input.c */
t_process	**make_proces_list(char *line);
t_process	*create_process(char *s, int start, int end, int id);
void		make_token_list(t_process *process, t_list *envlist);

/* expand .c */
bool	varcmp(char *model, char *str);
char	*find_var(char *var, t_list *list);
char	*my_getenv(char *var, t_list *list);
char	*expand_value(char *s, int i, t_list **envlist);
char	*get_var_to_exp(char *s);

/* clean_words.c */
char	*clean_word(char *s, t_list **envlist);
size_t	my_strlen(const char *s);

/* ft_split_minishell.c */
int		nb_words(char *s, char c);
int		size_words(char *s, char c);
char	**write_in(char **tab, char *s, char c);
void	freetab(char **tab);
char	**ft_split_minishell(char *s, char c);

/* utils_double.c */
t_list	*env_to_envlist(char **env);

/* utils_cleaning.c */
char	*ft_strdup_checking(char *s, int start, int end);
char	*my_strjoin(char *s1, char *s2);
bool	is_ok(char c);

#endif