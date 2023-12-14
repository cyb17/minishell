/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:52:22 by yachen            #+#    #+#             */
/*   Updated: 2023/05/05 13:51:14 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c <= 'z' && c >= 'a')
		return (c -= 32);
	else
		return (c);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main()
{
	printf("%c", ft_toupper('-'));
}*/
