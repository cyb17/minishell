/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:18:57 by yachen            #+#    #+#             */
/*   Updated: 2023/11/02 15:22:35 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
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
# include <readline/readline.h>
# include "../srcs/builtins/builtins.h"


enum tokens_type
{
	CMD = 0
	WORD = 1,
	INFILE = 2,
	OUTFILE = 3,
	REDIR_IN = 4,
	REDIR_OUT = 5,
	APPEN = 6,
	HEREDOC = 7
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

#endif
