/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:38:39 by yachen            #+#    #+#             */
/*   Updated: 2023/05/09 15:55:29 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ldst;

	i = 0;
	if (!dst && size == 0)
		return (ft_strlen(src));
	ldst = ft_strlen(dst);
	if (size <= ldst)
		return (size + ft_strlen(src));
	while (src[i] && i < size - ldst - 1)
	{
		dst[ldst + i] = src[i];
		i++;
	}
	dst[ldst + i] = '\0';
	return (ldst + ft_strlen(src));
}
