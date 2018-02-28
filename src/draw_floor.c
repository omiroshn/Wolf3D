/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:55:58 by omiroshn          #+#    #+#             */
/*   Updated: 2018/02/28 21:55:59 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	floor_wall_dist(t_map *m, t_vec *floor_wall)
{
	if (m->side == 0 && m->ray_dir.x > 0)
	{
		floor_wall->x = m->map.x;
		floor_wall->y = m->map.y + m->wall;
	}
	else if (m->side == 0 && m->ray_dir.x < 0)
	{
		floor_wall->x = m->map.x + 1.0;
		floor_wall->y = m->map.y + m->wall;
	}
	else if (m->side == 1 && m->ray_dir.y > 0)
	{
		floor_wall->x = m->map.x + m->wall;
		floor_wall->y = m->map.y;
	}
	else
	{
		floor_wall->x = m->map.x + m->wall;
		floor_wall->y = m->map.y + 1.0;
	}
}

t_vec	current_floor(t_map *m, t_vec *cur_floor, t_vec *floor_wall, int y)
{
	double	weight;

	weight = m->h / (2.0 * y - m->h) / m->dist_wall;
	cur_floor->x = weight * floor_wall->x + (1.0 - weight) * m->pos.x;
	cur_floor->y = weight * floor_wall->y + (1.0 - weight) * m->pos.y;
	return (*cur_floor);
}

void	env_textures(t_map *m, t_vec *c_f, t_uint **data)
{
	m->floor_tex.x = (int)(c_f->x * m->w_t[FLOOR(data[(int)c_f->x]
		[(int)c_f->y])]->w) % m->w_t[FLOOR(data[(int)c_f->x][(int)c_f->y])]->w;
	m->floor_tex.y = (int)(c_f->y * m->w_t[FLOOR(data[(int)c_f->x]
		[(int)c_f->y])]->h) % m->w_t[FLOOR(data[(int)c_f->x][(int)c_f->y])]->h;
	m->ceil_tex.x = (int)(c_f->x * m->w_t[CEIL(data[(int)c_f->x]
		[(int)c_f->y])]->w) % m->w_t[CEIL(data[(int)c_f->x][(int)c_f->y])]->w;
	m->ceil_tex.y = (int)(c_f->y * m->w_t[CEIL(data[(int)c_f->x]
		[(int)c_f->y])]->h) % m->w_t[CEIL(data[(int)c_f->x][(int)c_f->y])]->h;
}

void	draw_floor(t_map *m, t_uint **data)
{
	t_vec	floor_wall;
	t_vec	c_f;
	int		y;

	floor_wall_dist(m, &floor_wall);
	m->dist_wall = m->wall_dist;
	y = m->draw_end;
	while (++y < m->h)
	{
		c_f = current_floor(m, &c_f, &floor_wall, y);
		env_textures(m, &c_f, data);
		if (!*(m->bufp - m->w))
			*(m->bufp - m->w) = ((t_uint *)m->w_t[FLOOR(data[(int)c_f.x]
			[(int)c_f.y])]->pixels)[m->w_t[FLOOR(data[(int)c_f.x]
			[(int)c_f.y])]->w * m->floor_tex.y + m->floor_tex.x];
		if (!*(m->bufp + (m->h - 2 * y) * m->w))
			*(m->bufp + (m->h - 2 * y) * m->w) = ((t_uint *)m->w_t[CEIL(data
			[(int)c_f.x][(int)c_f.y])]->pixels)[m->w_t[CEIL(data[(int)c_f.x]
			[(int)c_f.y])]->w * m->ceil_tex.y + m->ceil_tex.x];
		m->bufp += m->w;
	}
}
