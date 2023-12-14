/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:20:39 by yachen            #+#    #+#             */
/*   Updated: 2023/07/31 14:41:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_unsi(unsigned int nb)
{
	long		nbr;
	static int	len;

	nbr = nb;
	len = 0;
	if (nbr > 9)
		ft_printf_unsi(nbr / 10);
	len += ft_printf_char(nbr % 10 + 48);
	return (len);
}
