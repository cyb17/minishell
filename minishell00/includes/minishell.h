/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:18:57 by yachen            #+#    #+#             */
/*   Updated: 2023/10/27 12:40:17 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <errno.h>
# include <readline/readline.h>
# include "../libft/libft.h"

enum tokens_type
{
	WORD = 1,
	INFILE = 2,
	OUTFILE = 3,
	REDIR_IN = 4,
	REDIR_OUT = 5,
	APPEN = 6,
	HEREDOC = 7,
	SPACEE = 8
};

typedef struct s_tokens
{
	int				token_id;
	int				type;
	char 			*value;
	struct s_tokens	*next_tokens;
}					t_tokens;

typedef struct s_process
{
    char				**section_cmd;
	int					section_cmd_id;
	t_tokens			*list_tokens;
	pid_t				pid;
	struct s_process	*next_process;
}						t_process;

// builtins
void	ft_echo(char *op, char *str);

void	clear_lst(t_list **lst);
t_list	*env_to_envlist(char **env);
void	ft_env(t_list *envlist);

int	stringcmp(char *model, char *str);
t_list	*find_oldvar(char *var, t_list *list, int *i);
t_list	*create_newvar(char *arg);

#endif
