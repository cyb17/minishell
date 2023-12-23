/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:20:21 by yachen            #+#    #+#             */
/*   Updated: 2023/07/31 14:41:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ptrhexa(unsigned long long ptr)
{
	static int	count;
	char		*hexa;

	count = 0;
	hexa = "0123456789abcdef";
	if (ptr >= 16)
		ft_ptrhexa(ptr / 16);
	count += ft_printf_char(hexa[ptr % 16]);
	return (count);
}

int	ft_printf_ptr(unsigned long long ptr)
{
	int	len;

	if (ptr == 0)
	{
		ft_printf_str("(nil)");
		return (5);
	}
	ft_printf_str("0x");
	len = ft_ptrhexa(ptr);
	return (len + 2);
}
