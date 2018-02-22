/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 16:48:33 by omiroshn          #+#    #+#             */
/*   Updated: 2017/10/27 16:48:35 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	size_t	i;
	size_t	n;
	size_t	m;

	n = ft_strlen(dst);
	m = ft_strlen(src);
	if (!size)
		return (n);
	i = 0;
	while (*src && (i + n < size - 1))
		dst[i++ + n] = *src++;
	dst[i + n] = '\0';
	return (m += n < size ? n : size);
}
