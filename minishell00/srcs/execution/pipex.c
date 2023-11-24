/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:45:45 by yachen            #+#    #+#             */
/*   Updated: 2023/11/24 16:31:31 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// check and open, if there is a infile or a outfile
int	check_fdin_fdout(int *fdin, int *fdout, t_tokens *tokens)
{
	char	*here_doc;

	while (tokens)
	{
		if (tokens->type == REDIR_IN && tokens->next->type == INFILE)
			redirect_in(fdin, tokens->next->value);
		else if (tokens->type == REDIR_OUT && tokens->next->type == OUTFILE)
			redirect_out(fdout, tokens->next->value, 'T');
		else if (tokens->type == APPEN && tokens->next->type == OUTFILE)
			redirect_out(fdout, tokens->next->value, 'A');
		else if (tokens->type == HEREDOC)
		{
			here_doc = ft_here_doc(tokens->next->value);
			redirect_in(fdin, here_doc);
			free(here_doc);
		}
		if ((*fdin == -1) || (*fdout == -1))
			return (-1);
		tokens = tokens->next;
	}
	return (0);
}

static void	redirection(t_res *res, int i)
{
	if (res->tab->fdin > 2 && i > 0)
	{
		dup2(res->tab->fdin, res->tab->pipefd[i - 1][0]);
		close(res->tab->fdin);
		res->tab->fdin = 0;
	}
	if (res->tab->fdout > 2 && i < res->tab->nb_pipe)
	{
		dup2(res->tab->fdout, res->tab->pipefd[i][1]);
		close(res->tab->fdout);
		res->tab->fdout = 1;
	}
}

static void	fixe_in_output(int *input, int *output, t_tab *tab, int i)
{
	if (i == 0)
	{
		*input = tab->fdin;
		*output = tab->pipefd[i][1];
	}
	else if (i == tab->nb_pipe)
	{
		*input = tab->pipefd[i - 1][0];
		*output = tab->fdout;
	}
	else
	{
		*input = tab->pipefd[i - 1][0];
		*output = tab->pipefd[i][1];
	}
}

void	print_allfd(t_tab *tab, int input, int output)
{
	int	i = 0;
	printf("fdin:%d   fdout:%d\n", tab->fdin, tab->fdout);
	printf("nb_pipe:%d\n", tab->nb_pipe);
	while (i < tab->nb_pipe)
	{
		printf("pipefd[%d][0]:%d  pipefd[%d][1]:%d\n", i, tab->pipefd[i][0], i, tab->pipefd[i][1]);
		i++;
	}
	printf("input:%d  output:%d\n", input, output);
}

int	make_child_process(t_tokens *cmd_tk, t_res *res, int i, char **env)
{
	char	*arg;
	char	*path;
	int		input;
	int		output;
	// (void)path;
	// (void)env;
	// (void)cmd_tk;

	input = 0;
	output = 1;
	arg = NULL;
	if (check_fdin_fdout(&res->tab->fdin, &res->tab->fdout, res->prcs->list_tokens) == -1)
		return (-1);
	redirection(res, i);
	fixe_in_output(&input, &output, res->tab, i);
	print_allfd(res->tab, input, output);
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
		child_procs_part_2(res, input, output, arg, i);
		child_procs_part_3(res, path, arg);
	}
	else
	{
		close(input);
		close(output);
	}
	return (0);
}

int	pipex(t_res *res, char **env, int i)
{
	t_tokens	*tmp;
	int			status;
	
	status = 0;
	tmp = res->prcs->list_tokens;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			if (isnot_builtins(tmp->value) == 1)
			{
				make_child_process(tmp, res, i, env);
				waitpid(res->tab->tab_pid[i], &status, 0);
			}
			// else
			// 	rslt = execute_builtins(res->prcs->list_tokens, &tab, i, builtins);
			// break;
		}
		tmp = tmp->next;
	}
	return (0);
}

// int	make_child_process(t_tokens *cmd_tk, t_res *res, int i, char **env)
// {
// 	char	*arg;
// 	char	*path;

// 	arg = NULL;
// 	res->tab->tab_pid[i] = fork();
// 	if (res->tab->tab_pid[i] == -1)
// 	{
// 		perror("Error : fork");
// 		return (-1);
// 	}
// 	else if (res->tab->tab_pid[i] == 0)
// 	{
// 		arg = make_cmdtk_to_arg(cmd_tk);
// 		path = child_procs_part_1(res, env, arg);
// 		child_procs_part_3(res, path, arg);
// 	}
// 	else
// 	{
// 		close(STDIN_FILENO);
// 		close(STDOUT_FILENO);
// 	}
// 	return (0);
// }

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

// int	setup_stdin_stdout(int *fdin, int *fdout, t_res *res, int i)
// {
// 	printf("avant redirection => i: %d stdin:%d  stdout:%d\n", i, STDIN_FILENO, STDOUT_FILENO);
// 	if (*fdout > 2)
// 		dup2(*fdout, STDOUT_FILENO);
// 	else
// 	{
// 		if (i == res->tab->nb_pipe)
// 			dup2(1, STDOUT_FILENO);
// 		else
// 			dup2(res->tab->pipefd[i][1], STDOUT_FILENO);
// 	}
// 	if (*fdin > 2)
// 		dup2(*fdin, STDIN_FILENO);
// 	else
// 	{
// 		if (i > 0)
// 			dup2(res->tab->pipefd[i - 1][0], STDIN_FILENO);
// 	}
// 	printf("apres redirection => i: %d stdin:%d  stdout:%d\n", i, STDIN_FILENO, STDOUT_FILENO);
// 	return (0);
// }

