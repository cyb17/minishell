/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:47:58 by achevala          #+#    #+#             */
/*   Updated: 2023/12/21 20:39:15 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	is_only_space2(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\0')
	{
		if (s[i] != ' ')
			return (true);
		i++;
	}
	return (false);
}
