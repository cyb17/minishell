/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:20:09 by yachen            #+#    #+#             */
/*   Updated: 2023/07/31 14:41:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_nbr(int nb)
{
	int			sign;
	long		nbr;
	static int	len;

	sign = 0;
	nbr = nb;
	len = 0;
	if (nbr < 0)
	{
		ft_printf_char('-');
		nbr *= -1;
		sign = 1;
	}
	if (nbr > 9)
		ft_printf_nbr(nbr / 10);
	len += ft_printf_char(nbr % 10 + 48);
	return (len + sign);
}
