/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:20:50 by yachen            #+#    #+#             */
/*   Updated: 2023/07/31 14:41:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_check_format(va_list argp, const char str, int *len)
{
	if (str == 'c')
		*len += ft_printf_char(va_arg(argp, int));
	else if (str == 's')
		*len += ft_printf_str(va_arg(argp, char *));
	else if (str == 'i' || str == 'd')
		*len += ft_printf_nbr(va_arg(argp, int));
	else if (str == 'u')
		*len += ft_printf_unsi(va_arg(argp, unsigned int));
	else if (str == 'x')
		*len += ft_printf_hexa(va_arg(argp, unsigned int), 0);
	else if (str == 'X')
		*len += ft_printf_hexa(va_arg(argp, unsigned int), 1);
	else if (str == 'p')
		*len += ft_printf_ptr(va_arg(argp, unsigned long long));
	else if (str == '%')
		*len += ft_printf_char('%');
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		total_len;
	va_list	argp;

	i = 0;
	total_len = 0;
	if (!str)
		return (0);
	va_start(argp, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_check_format(argp, str[i + 1], &total_len);
			i++;
		}
		else
			total_len += ft_printf_char(str[i]);
		i++;
	}
	va_end(argp);
	return (total_len);
}
