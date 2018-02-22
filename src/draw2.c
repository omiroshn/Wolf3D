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
														int color, int texture, int side)
{
	unsigned int *bufp;
	int y;
	int	texY;
	int texX;
	double wallX;

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
	//where exactly the wall was hit
	if (side == 0)
		wallX = map->pos.y + map->wall_dist * map->ray_dir.y;
	else
		wallX = map->pos.x + map->wall_dist * map->ray_dir.x;
	wallX -= floor(wallX);
	//x coordinate on the texture
	texX = (int)(wallX * (double)(map->w_t[texture]->w));
	if (side == 0 && map->ray_dir.x > 0)
		texX = map->w_t[texture]->w - texX - 1;
	if (side == 1 && map->ray_dir.y < 0)
		texX = map->w_t[texture]->w - texX - 1;
	bufp = (unsigned int *)map->screen->pixels + draw_start * map->screen->w + x;

	y = draw_start;
	while (y <= draw_end)
	{
		texY = (y - draw_start) * (map->w_t[texture]->h / (draw_end - draw_start));
		if (texY >= 0 && texY < map->w_t[texture]->h && texX >= 0 && texX < map->w_t[texture]->w)
			*bufp = ((unsigned int *)map->w_t[texture]->pixels)[map->w_t[texture]->w * texY + texX];
		bufp += WIDTH;
		y++;
	}
	return (1);
}
