/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <omiroshn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 22:45:40 by omiroshn          #+#    #+#             */
/*   Updated: 2018/01/05 17:01:21 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isupper(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	return (0);
}

int			check_characters(char *str, int value, int base)
{
	if (*str - 'A' >= 0 && ft_isupper(*str) == 1)
		value = value * base + (*str - 'A' + 10);
	else if (*str - 'A' < 0 && ft_isupper(*str) == 1)
		value = value * base + (*str - '0');
	else if (*str - 'a' >= 0 && ft_isupper(*str) == 0)
		value = value * base + (*str - 'a' + 10);
	else if (*str - 'a' < 0 && ft_isupper(*str) == 0)
		value = value * base + (*str - '0');
	return (value);
}

static int	is_inbase(char c, int base)
{
	if (base <= 10)
	{
		if (c >= '0' && c <= '9')
			return (1);
		return (0);
	}
	else
	{
		if ((c >= '0' && c <= '9')
			|| (c >= 'A' && c <= ('A' + base - 10))
			|| (c >= 'a' && c <= ('a' + base - 10)))
			return (1);
		return (0);
	}
}

static int	is_delimiter(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' ||
		c == '\f' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

int			ft_atoi_base(char *str, int base)
{
	int value;
	int minus;

	value = 0;
	if (base <= 1 || base > 36)
		return (0);
	str += 2;
	while (is_delimiter(*str))
		str++;
	minus = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (is_inbase(*str, base))
	{
		value = check_characters(str, value, base);
		str++;
	}
	return (value * minus);
}
