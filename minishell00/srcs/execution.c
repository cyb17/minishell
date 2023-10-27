/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:02:06 by yachen            #+#    #+#             */
/*   Updated: 2023/10/27 14:22:58 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	while (1)
	{
		printf("argc :%d  argv :%s env:%s\n", argc, argv[0], env[0]);
		readline("\e[32;1mminishell>\e[0m");
	}
}