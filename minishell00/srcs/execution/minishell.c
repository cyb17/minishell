/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:21:18 by yachen            #+#    #+#             */
/*   Updated: 2023/11/24 18:14:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_structure(t_res *res)
{
	res->prcs = NULL;
	res->blt = NULL;
	res->tab = NULL;
	res->input =NULL;
}

void	exe_no_builtins(t_res *res, char **env, t_tokens *cmd)
{
	char	*arg;
	char	*path;

	arg = make_cmdtk_to_arg(cmd);
	path = child_procs_part_1(res, env, arg);
	child_procs_part_3(res, path, arg);
}

t_tokens	*check_cmd_tk(t_tokens *list_tokens)
{
	t_tokens	*tmp;

	tmp = list_tokens;
	while (tmp)
	{
		if (tmp->type == CMD)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	single_prcs(t_res *res, char **env)
{
	int			fdin;
	int			fdout;
	t_tokens	*cmd;
	pid_t		pid;

	fdin = 0;
	fdout = 1;
	pid = fork();
	if (pid == -1)
	{
		perror("Error : fork");
		return ;
	}
	else if (pid == 0)
	{
		if (check_fdin_fdout(&fdin, &fdout, res->prcs->list_tokens) == -1)
		{
			garbage_collector(res);
			exit (1);
		}
		if (fdin > 2)
		{
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		if (fdout > 2)
		{
			dup2(fdout, STDIN_FILENO);
			close(fdout);
		}
		cmd = check_cmd_tk(res->prcs->list_tokens);
		if (!cmd)
			return ;
		if (isnot_builtins(cmd->value) == 1)
		{
			printf("not builtins\n");
			exe_no_builtins(res, env, cmd);
		}
		else
			printf("is builtins\n");
			// exe_builtins(cmd);
	}
	else
		waitpid(pid, NULL, 0);
}

void	prcs(t_res *res, char **env, t_process *prcs, int i)
{
	int			fdin;
	int			fdout;
	t_tokens	*cmd;
	pid_t		pid;

	fdin = 0;
	fdout = 1;
	pid = fork();
	if (pid == -1)
	{
		perror("Error : fork");
		return ;
	}
	else if (pid == 0)
	{
		if (check_fdin_fdout(&fdin, &fdout, prcs->list_tokens) == -1)
		{
			garbage_collector(res);
			exit (1);
		}
		// printf("i = %d\n", i);
		if (i == 0)
		{
			close(res->tab->pipefd[i][0]);
			if (fdin > 2)
			{
				// printf("1\n");
				dup2(fdin, STDIN_FILENO);
				close(fdin);
			}
			if (fdout > 2)
			{
				// printf("2\n");
				dup2(fdout, STDOUT_FILENO);
				close(fdout);
				close(res->tab->pipefd[i][1]);
			}
			else
			{
				// printf("3 ");
				// printf("fd : %d\n", res->tab->pipefd[i][1]);
				dup2(res->tab->pipefd[i][1], STDOUT_FILENO);
				close(res->tab->pipefd[i][1]);
			}
		}
		else if (i == res->tab->nb_pipe)
		{
			if (fdin > 2)
			{
				// printf("4\n");
				dup2(fdin, STDIN_FILENO);
				close(fdin);
				close(res->tab->pipefd[i - 1][0]);
			}
			else
			{
				// printf("5 ");
				// printf("fd : %d\n", res->tab->pipefd[i - 1][0]);
				dup2(res->tab->pipefd[i - 1][0], STDIN_FILENO);
				close(res->tab->pipefd[i - 1][0]);
			}
			if (fdout > 2)
			{
				dup2(fdout, STDOUT_FILENO);
				close(fdout);
			}
		}
		else
		{
			close(res->tab->pipefd[i][0]);
			if (fdin > 2)
			{
				// printf("7\n");
				dup2(fdin, STDIN_FILENO);
				close(fdin);
				close(res->tab->pipefd[i - 1][0]);
			}
			else
			{
				// printf("8: %d\n", res->tab->pipefd[i - 1][0]);
				dup2(res->tab->pipefd[i - 1][0], STDIN_FILENO);
				close(res->tab->pipefd[i - 1][0]);
			}
			if (fdout > 2)
			{
				// printf("9\n");
				dup2(fdout, STDOUT_FILENO);
				close(fdout);
				close(res->tab->pipefd[i][1]);
			}
			else
			{
				 printf("10: %d  %d\n", res->tab->pipefd[i][1], res->tab->pipefd[i][0]);
				dup2(res->tab->pipefd[i][1], STDOUT_FILENO);
				close(res->tab->pipefd[i][1]);
			}
		}
		cmd = check_cmd_tk(prcs->list_tokens);
		if (!cmd)
			return ;
		if (isnot_builtins(cmd->value) == 1)
		{
			printf("not builtins\n");
			exe_no_builtins(res, env, cmd);
		}
		else
			printf("is builtins\n");
			// exe_builtins(cmd);
	}
	else
	{
		if (i == 0)
		{
			//close(res->tab->pipefd[i][0]);
			close(res->tab->pipefd[i][1]);
		}
		else if (i == res->tab->nb_pipe)
		{
			close(res->tab->pipefd[i - 1][0]);
			// close(res->tab->pipefd[i][1]);
		}
		else
		{
			close(res->tab->pipefd[i][1]);
			close(res->tab->pipefd[i - 1][0]);
		}
		waitpid(pid, NULL, 0);
	}
}

void	multi_prcs(t_res *res, char **env)
{
	res->tab = fill_tab(res->prcs);
	t_process	*tmp;
	int			i;

	tmp = res->prcs;
	i = 0;
	while (tmp)
	{
		pipe_pipefd(res->tab, i);
		prcs(res, env, tmp, i);
		tmp = tmp->next;
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_res		res;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		init_structure(&res);
		res.input = readline("\e[34;1mminishell> \e[0m");
		//ft_parse(res.input, process);
		res.blt = fill_builtins(env);
		res.prcs = create_list_process();
		if (find_nb_process(res.prcs) > 1)
			multi_prcs(&res, env);
		else
			single_prcs(&res, env);
		// res.tab = fill_tab(process);
		// if (!res.blt || !res.tab)
		// {
		// 	garbage_collector(&res);
		// 	ft_putstr_fd("initialization of ressources failed\n", 2);
		//  	return (1);
		// }
		// int i = 0;
		// while (res.prcs)
		// {
		// 	pipe_pipefd(res.tab, i);
		// 	pipex(&res, env, i);
		// 	i++;
		// 	res.prcs = res.prcs->next;
		// }
		// {
		// 	garbage_collector(process, &tab, &builtins);
		// 	return (1);
		// }
		// garbage_collector(process, &tab, &builtins, input);
	}
	return (0);
}
