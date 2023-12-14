/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:58:19 by yachen            #+#    #+#             */
/*   Updated: 2023/05/12 13:37:39 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_lenstr(long nb, int sign)
{
	int		c;

	c = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		c++;
	}
	if (sign == 0)
		c++;
	return (c);
}

static void	ft_convert(long nb, char *str, size_t len, int sign)
{
	str[len] = '\0';
	str[--len] = nb % 10 + 48;
	nb /= 10;
	while (nb > 0)
	{
		str[--len] = nb % 10 + 48;
		nb /= 10;
	}
	if (sign == 0)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		sign;

	nb = n;
	sign = 1;
	if (n < 0)
	{
		sign = 0;
		nb *= -1;
	}
	str = (char *)malloc((ft_lenstr(nb, sign) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_convert(nb, str, ft_lenstr(nb, sign), sign);
	return (str);
}
/*
#include <stdio.h>

int	main()
{
	printf("%s\n", ft_itoa(-0));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(-123));
	printf("%s\n", ft_itoa(123));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-2147483648));
}
*/
