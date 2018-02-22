/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:03:29 by omiroshn          #+#    #+#             */
/*   Updated: 2017/10/26 16:03:30 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*str;
	unsigned char	*dest;
	size_t			i;

	i = -1;
	str = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (str < dest)
		while ((int)(--len) >= 0)
			dest[len] = str[len];
	else
		while (++i < len)
			dest[i] = str[i];
	return (dst);
}
