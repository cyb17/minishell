/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:45:45 by yachen            #+#    #+#             */
/*   Updated: 2023/11/20 16:00:52 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	isnot_builtins(char *str)
{
	if ((strcmp("echo", str) == 1) || (strcmp("cd", str) == 1)
		|| (strcmp("env", str) == 1) || (strcmp("exit", str) == 1)
		|| (strcmp("export", str) == 1) || (strcmp("unset", str) == 1)
		|| (strcmp("pwd", str) == 1))
		return (0);
	return (1);
}

static char	*join_cmd_and_option(char *s1, char *s2)
{
	char	*tmp;
	char	*cmd;

	tmp = NULL;
	cmd = NULL;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	tmp = ft_strjoin(s1, " ");
	cmd = ft_strjoin(tmp, s2);
	if (tmp)
		free(tmp);
	return (cmd);
}

char	*make_cmdtk_to_arg(t_tokens *tokens)
{
	char		*tmp;
	char		*cmd;

	cmd = NULL;
	while (tokens && tokens->type != CMD)
		tokens = tokens->next;
	if (tokens == NULL)
		return (NULL);
	while (tokens && (tokens->type == CMD || tokens->type == WORD))
	{
		tmp = cmd;
		cmd = join_cmd_and_option(cmd, tokens->value);
		if (tmp)
			free(tmp);
		if (!cmd)
			return (NULL);
		tokens = tokens->next;
	}
	return (cmd);
}

// void	fixe_in_output(int *input, int *output, t_tab *tab, int i)
// {
// 	if (i == 0)
// 		*input = tab->fdin;
// 	else
// 		*input = tab->pipefd[i - 1][0];
// 	if (i == tab->nb_pipe)
// 		*output = tab->fdout;
// 	else
// 		*output = tab->pipefd[i][1];
// }

// static void	ft_close(int *input, int *output)
// {
// 	close(*input);
// 	close(*output);
// }

int	make_child_process(t_tokens *cmd_tk, t_res *res, int i, char **env)
{
	char	*arg;
	char	*path;

	arg = NULL;
	res->tab->tab_pid[i] = fork();
	if (res->tab->tab_pid[i] == -1)
	{
		perror("Error : fork");
		return (-1);
	}
	else if (res->tab->tab_pid[i] == 0)
	{
		arg = make_cmdtk_to_arg(cmd_tk);
		path = child_procs_part_1(res, env, arg);
		child_procs_part_3(res, path, arg);
	}
	else
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	return (0);
}

// int	builtin_cmd_arg(t_tokens *cmd_tk, t_builtins *builtins)
// {
// 	char		**arg;
// 	t_tokens	*tmp;
// 	int			i;

// 	i = 0;close(res->tab->pipef[i - 1][0]);
// 	tmp = cmd_tk;
// 	while (tmp && (tmp->type == CMD || tmp->type == WORD))
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	arg = (char **)malloc(sizeof(char *) * (i + 1));
// 	if (!arg)
// 		return (-1);
// 	i = 0;
// 	while (cmd_tk && (cmd_tk->type == CMD || cmd_tk->type == WORD))close(res->tab->pipef[i - 1][0]);
// 	{
// 		arg[i++] = cmd_tk->value;
// 		cmd_tk = cmd_tk->next;
// 	}
// 	arg[i] = NULL;
// 	builtins->arg = arg;
// 	return (0);
// }

// void	which_cmd(t_builtins *builtins, t_tokens *cmd_tk, int *rlt)
// {
// 	if (strcmp("echo", cmd_tk->value) == 1)
// 		*rlt = ft_echo(bultins->arg);
// 	else if (strcmp("cd", cmd_tk->value) == 1)
// 		*rlt = ft_cd(builtins->envlist, bultins->explist, builtins->arg);
// 	else if (strcmp("env", cmd_tk->value) == 1)
// 		*rlt = ft_env(builtins->envlist, builtins->arg);
// 	else if (strcmp("export", cmd_tk->value) == 1)
// 		*rlt = ft_export(builtins->envlist, builtins->explist, builtins->arg);
// 	else if (strcmp("unset", cmd_tk->value) == 1)
// 		*rlt = ft_unset(builtins->envlist, builtins->explist, builtins->arg[0]);
// 	else if (strcmp("pwd", cmd_tk->value) == 1)
// 		*rlt = ft_pwd();
// 	else if (strcmp("exit", cmd_tk->value) == 1)
// 		*rlt = ft_exit();
// 	free_tab(builtins->arg);
// 	builtins->arg = NULL;
// }

// int	execute_builtins(t_tokens *cmd_tk, t_tab *tab, int i, t_builtins *builtins)
// {
// 	int	rlt;
// 	int	input;
// 	int	output;

// 	result = 0;
// 	input = 0;
// 	output = 0;
// 	fixe_in_output(&input, &output, tab, i);
// 	if (dup2(input, STDIN_FILENO) < 0 || dup2(output, STDOUT_FILENO) < 0)
// 	{
// 		close(input);
// 		close(output);
// 		perror("dup2");
// 		return (-1);
// 	}
// 	close(input);
// 	close(output);
// 	if (builtin_cmd_arg(cmd_tk, builtins) == -1)
// 		return (-1);
// 	which_cmd(buitins, cmd_tk, &rlt);
// 	return (rlt);
// }


void	setup_pipe(t_res *res, int procs_i)
{
	if (i == 0)
	{
		dup2(res->tab->fdin, STDIN_FILENO);
		if (res->tab->fdout == 1)
			dup2(res->tab->pipefd[i][1], STDOUT_FILENO);
		else
			dup2(res->tab->fdout, STDOUT_FILENO);
	}
	else if (i == res->tab->nb_pipe)
	{
		dup2(res->tab->pipefd[i - 1][0], STDIN_FILENO);
		dup2(res->tab->fdout, STDOUT_FILENO);
	}
	else
	{
		dup2(res->tab->pipefd[i - 1][0], STDIN_FILENO);
		dup2(res->tab->pipefd[i][1], STDOUT_FILENO);
	}
}

int	setup_stdin_stdout(t_res *res, t_tokens *tokens, int i)
{
	char	*here_doc;

	while (tokens)
	{
		if (tokens->type == REDIR_IN && tokens->next->type == INFILE)
			redirect_in(&res->tab->fdin, tokens->next->value);
		else if (tokens->type == REDIR_OUT && tokens->next->type == OUTFILE)
			redirect_out(&res->tab->fdout, tokens->next->value, 'T');
		else if (tokens->type == APPEN && tokens->next->type == OUTFILE)
			redirect_out(&res->tab->fdout, tokens->next->value, 'A');
		else if (tokens->type == HEREDOC)
		{
			here_doc = ft_here_doc(tokens->next->value);
			redirect_in(&res->tab->fdin, here_doc);
			free(here_doc);
		}
		if ((res->tab->fdin == -1) || (res->tab->fdout == -1))
			return (-1);
		tokens = tokens->next;
	}
	printf("sortie tokens : %p\n", tokens);
	printf("fdin : %d fdout: %d i : %d\n", res->tab->fdin, res->tab->fdout, i);
	//setup_pipe(res, i);
	return (0);
}

int	pipex(t_res *res, char **env, int i)
{
	//t_tokens	*tmp;
	//int			status;
	
	//status = 0;
	(void)env;
	if (setup_stdin_stdout(res, res->prcs->list_tokens, i) == -1)
		return (-1);
	/*tmp = res->prcs->list_tokens;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			if (isnot_builtins(tmp->value) == 1)
			{
				make_child_process(tmp, res, i, env);
				waitpid(res->tab->tab_pid[i], &status, 0);
			}
			//else
				//rslt = execute_builtins(res->prcs->list_tokens, &tab, i, builtins);
			break;
		}
		tmp = tmp->next;
	}*/
	return (0);
}
