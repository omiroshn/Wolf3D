/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <omiroshn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:33:51 by omiroshn          #+#    #+#             */
/*   Updated: 2018/01/30 14:27:23 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delimiter(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\r' || c == '\f')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	size_t				i;
	unsigned long int	num;
	int					minus;

	i = 0;
	num = 0;
	minus = 1;
	while (is_delimiter(str[i]))
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i++] - 48);
		if (num >= 9223372036854775807 && minus == 1)
			return (-1);
		else if (num >= 9223372036854775807 && minus == -1)
			return (0);
	}
	return ((int)(num * minus));
}
