/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:11:25 by yachen            #+#    #+#             */
/*   Updated: 2023/12/09 14:33:29 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// void	ft_error(char *where, char *what)
// {
// 	char	*tmp;
// 	char	*err;

// 	tmp = ft_strjoin(where, what);
// 	if (!tmp)
// 	{
// 		ft_putstr_fd(where, 2);
// 		ft_putstr_fd(what, 2);
// 		ft_putchar_fd('\n', 2);
// 		return ;
// 	}
// 	err = ft_strjoin(tmp, "\n");
// 	if (!err)
// 	{
// 		free(tmp);
// 		ft_putstr_fd(where, 2);
// 		ft_putstr_fd(what, 2);
// 		ft_putchar_fd('\n', 2);
// 		return ;
// 	}
// 	free(tmp);
// 	ft_putstr_fd(err, 2);
// 	free(err);
// }
