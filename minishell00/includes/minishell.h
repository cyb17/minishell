/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nap <nap@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:06:32 by nap               #+#    #+#             */
/*   Updated: 2023/10/20 16:54:03 by nap              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

enum tokens_type
{
	WORD = 1,
	INFILE = 2,
	OUTFILE = 3,
	REDIR_IN = 4,
	REDIR_OUT = 5,
	APPEN = 6,
	HEREDOC = 7,
	SPACE = 8
}

typedef struct s_tokens
{
	int				token_id;
	int				type;
	char 			*value;
	struct s_tokens	*next_tokens;
}				t_tokens;

typedef struct s_process
{
    char		**section_cmd;
	int			section_cmd_id;
	t_tokens	*list_tokens;
	pid_t		pid;
}               t_process;


#endif