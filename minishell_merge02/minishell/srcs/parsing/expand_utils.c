/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:19:51 by achevala          #+#    #+#             */
/*   Updated: 2023/12/09 14:36:00 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	varcmp(char *model, char *str)
{
	int	i;

	i = 0;
	while (model[i] && model[i] != '=')
	{
		if (model[i] != str[i])
			return (0);
		i++;
	}
	if (str[i] == '=')
		return (1);
	return (0);
}

bool	is_exp_char(char c)
{
	if ((c >= '0' && c <= '9') || c == '_' || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (true);
	else
		return (false);
}
