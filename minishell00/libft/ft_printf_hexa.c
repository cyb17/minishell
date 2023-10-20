/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:19:59 by yachen            #+#    #+#             */
/*   Updated: 2023/07/31 14:41:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_hexa(unsigned int nbr, int indice)
{
	unsigned long	nb;
	static int		count;
	char			*hexa;

	nb = nbr;
	count = 0;
	hexa = "0123456789abcdef";
	if (indice == 1)
		hexa = "0123456789ABCDEF";
	if (nb >= 16)
	{
		ft_printf_hexa(nb / 16, indice);
	}
	count += ft_printf_char(hexa[nb % 16]);
	return (count);
}
