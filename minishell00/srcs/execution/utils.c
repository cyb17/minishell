/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:57:17 by yachen            #+#    #+#             */
/*   Updated: 2023/11/06 17:45:25 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_compare(char *limiter, char *str)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] != str[i])
			return (0);
		i++;
	}
	if (limiter[i] == '\0' && str[i] == '\n')
		return (1);
	return (0);
}

void	ft_error(char *where, char *what)
{
	char	*tmp;
	char	*err;

	tmp = ft_strjoin(where, what);
	if (!tmp)
	{
		ft_putstr_fd(where, 2);
		ft_putstr_fd(what, 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
	err = ft_strjoin(tmp, "\n");
	if (!err)
	{
		free(tmp);
		ft_putstr_fd(where, 2);
		ft_putstr_fd(what, 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
	free(tmp);
	ft_putstr_fd(err, 2);
	free(err);
}

/*
int main(void)
{
	ft_error("Error: echo: ", strerror(errno));
}*/
