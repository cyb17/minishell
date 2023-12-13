/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:11:25 by yachen            #+#    #+#             */
/*   Updated: 2023/12/13 14:03:27 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	signal_handler_main(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 130;
	}
}

void	signal_handler_hd(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 130;
		close(STDIN_FILENO);
		printf("\n");
	}
}

void	ft_ctrl_d(void)
{
	g_signal = 0;
	printf("exit\n");
	exit(g_signal);
}

void	waitpid_and_fixe_exit_code(t_res *res)
{
	t_process	*tmp2;
	int			status;
	
	tmp2 = res->prcs;
	status = 0;
	while (tmp2)
	{
		if (tmp2->pid != -1)
			waitpid(tmp2->pid, &status, 0);
		tmp2 = tmp2->next;
	}
	if (WIFEXITED(status))
		g_signal = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal = WTERMSIG(status);
}
