/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:44:57 by yachen            #+#    #+#             */
/*   Updated: 2023/11/06 17:58:57 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int	ft_pwd(void)
{
	char	*current_path;
	char	buffer[GETCWD_SIZE];

	current_path = NULL;
	current_path = getcwd(buffer, GETCWD_SIZE);
	if (!current_path)
	{
		perror("minishell: pwd");
		return (-1);
	}
	printf("%s\n", current_path);
	return (0);
}

/*int	main(void)
{
	ft_pwd();
}*/