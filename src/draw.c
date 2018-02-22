/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <omiroshn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 06:37:48 by omiroshn          #+#    #+#             */
/*   Updated: 2018/01/05 17:01:08 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		vert_line(t_map *map, int x, int draw_start, int draw_end,
														int color, int texture)
{
	int *bufp;
	int y;

	if (draw_end < draw_start)
	{
		draw_start += draw_end;
		draw_end = draw_start - draw_end;
		draw_start -= draw_end;
	}
	if (draw_end < 0 || draw_end >= HEIGHT  || x < 0 || x >= WIDTH)
		return (0);
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIDTH)
		draw_end = HEIGHT - 1;
	bufp = (int *)map->screen->pixels + draw_start * WIDTH + x;
	y = draw_start;
	while (y <= draw_end)
	{
		*bufp = color;
		bufp += WIDTH;
		y++;
	}
	return (1);
}
