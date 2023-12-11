/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:11:25 by yachen            #+#    #+#             */
/*   Updated: 2023/12/11 16:06:30 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_ctrl_d(void)
{
	g_signal[0] = 0;
	printf("exit\n");
	exit(0);
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
		g_signal[0] = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal[0] = WTERMSIG(status);
}
