/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:44:57 by yachen            #+#    #+#             */
/*   Updated: 2023/12/02 15:20:06 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// Error = 1 || succes = 0
int	ft_pwd(void)
{
	char	*current_path;
	char	buffer[GETCWD_SIZE];

	current_path = NULL;
	current_path = getcwd(buffer, GETCWD_SIZE);
	if (!current_path)
	{
		perror("minishell: pwd");
		return (1);
	}
	printf("%s\n", current_path);
	return (0);
}
