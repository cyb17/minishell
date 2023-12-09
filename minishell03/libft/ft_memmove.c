/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:26:44 by yachen            #+#    #+#             */
/*   Updated: 2023/05/06 13:32:20 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((char *)dest == NULL && (char *)src == NULL)
		return (NULL);
	if (dest <= src)
	{
		while (i < n)
		{
			*((char *)dest + i) = *((char *)src + i);
			i++;
		}
	}
	else
	{
		while (i < n)
		{
			*((char *)dest + (n - 1)) = *((char *)src + (n - 1));
			n--;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	char	str[10] = "aaabbbccc";

//	ft_memmove(str, str+4, 4);
//	printf("%s\n",str);
//	ft_memmove(str, str+4, 3);
//	printf("%s\n",str);
	ft_memmove(str+2, str, 4);
	printf("%s",str);
}*/
