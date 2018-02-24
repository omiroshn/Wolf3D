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

void	draw_camera(t_map *m, int x)
{
	m->camera.x = 2 * x / (double)(WIDTH) - 1;
	m->ray_dir.x = m->dir.x + m->plane.x * m->camera.x;
	m->ray_dir.y = m->dir.y + m->plane.y * m->camera.x;
	m->map.x = (int)(m->pos.x);
	m->map.y = (int)(m->pos.y);
	m->delta_dist.x = fabs(1 / m->ray_dir.x);
	m->delta_dist.y = fabs(1 / m->ray_dir.y);
	m->step.x = -1;
	m->side_dist.x = (m->pos.x - m->map.x) * m->delta_dist.x;
	if (m->ray_dir.x >= 0)
	{
		m->step.x = 1;
		m->side_dist.x = (m->map.x + 1.0 - m->pos.x) * m->delta_dist.x;
	}
	m->step.y = -1;
	m->side_dist.y = (m->pos.y - m->map.y) * m->delta_dist.y;
	if (m->ray_dir.y >= 0)
	{
		m->step.y = 1;
		m->side_dist.y = (m->map.y + 1.0 - m->pos.y) * m->delta_dist.y;
	}
}

void	perform_dda(t_map *m)
{
	while (1)
	{
		if (m->side_dist.x < m->side_dist.y)
		{
			m->side_dist.x += m->delta_dist.x;
			m->map.x += m->step.x;
			m->side = 0;
		}
		else
		{
			m->side_dist.y += m->delta_dist.y;
			m->map.y += m->step.y;
			m->side = 1;
		}
		if (m->karta.data[m->map.x][m->map.y] > 0)
			break ;
	}
}

void	draw_wall(t_map *m, int x)
{
	int	texture;
	int	line_height;
	int	y;
	int	d;

	m->wall_dist = m->side == 0 ?
	(m->map.x - m->pos.x + (1 - m->step.x) / 2) / m->ray_dir.x :
	(m->map.y - m->pos.y + (1 - m->step.y) / 2) / m->ray_dir.y;
	line_height = (int)(HEIGHT / m->wall_dist);
	m->draw_start = -line_height / 2 + HEIGHT / 2;
	m->draw_end = line_height / 2 + HEIGHT / 2;
	if (m->draw_start < 0)
		m->draw_start = 0;
	if (m->draw_end >= HEIGHT)
		m->draw_end = HEIGHT - 1;
	if (m->draw_end < 0)
		m->draw_end = HEIGHT;
	m->wall = m->side == 0 ? m->pos.y + m->wall_dist * m->ray_dir.y :
	m->pos.x + m->wall_dist * m->ray_dir.x;
	m->wall -= floor((m->wall));
	texture = m->karta.data[m->map.x][m->map.y] - 1;
	m->tex.x = (int)(m->wall * (double)(m->w_t[texture]->w));
	if (m->side == 0 && m->ray_dir.x > 0)
		m->tex.x = m->w_t[texture]->w - m->tex.x - 1;
	if (m->side == 1 && m->ray_dir.y < 0)
		m->tex.x = m->w_t[texture]->w - m->tex.x - 1;
	y = m->draw_start - 1;
	m->bufp = (t_uint *)m->screen->pixels + m->draw_start * m->screen->w + x;
	while (++y <= m->draw_end)
	{
		d = y * 2 - HEIGHT + line_height;
		m->tex.y = ((d * m->w_t[texture]->w / line_height) / 2);
		if (m->tex.x >= 0 && m->tex.x < m->w_t[texture]->h &&
			m->tex.y >= 0 && m->tex.y < m->w_t[texture]->w)
			*m->bufp = ((t_uint *)m->w_t[texture]->pixels)
						[m->w_t[texture]->h * m->tex.y + m->tex.x];
		m->bufp += WIDTH;
	}
}

void	draw_floor(t_map *m)
{
	t_vec	current_floor;
	t_vec	floor_wall;
	double	weight;
	int		y;

	if (m->side == 0 && m->ray_dir.x > 0)
	{
		floor_wall.x = m->map.x;
		floor_wall.y = m->map.y + m->wall;
	}
	else if (m->side == 0 && m->ray_dir.x < 0)
	{
		floor_wall.x = m->map.x + 1.0;
		floor_wall.y = m->map.y + m->wall;
	}
	else if (m->side == 1 && m->ray_dir.y > 0)
	{
		floor_wall.x = m->map.x + m->wall;
		floor_wall.y = m->map.y;
	}
	else
	{
		floor_wall.x = m->map.x + m->wall;
		floor_wall.y = m->map.y + 1.0;
	}
	m->dist_wall = m->wall_dist;
	m->dist_player = 0.0;

	
	y = m->draw_end;
	while (++y < HEIGHT)
	{
		m->current_dist = HEIGHT / (2.0 * y - HEIGHT);
		weight = (m->current_dist - m->dist_player) / (m->dist_wall - m->dist_player);
		current_floor.x = weight * floor_wall.x + (1.0 - weight) * m->pos.x;
		current_floor.y = weight * floor_wall.y + (1.0 - weight) * m->pos.y;
		m->floor_tex.x = (int)(current_floor.x * m->w_t[9]->w) % m->w_t[9]->w;
		m->floor_tex.y = (int)(current_floor.y * m->w_t[9]->h) % m->w_t[9]->h;
		m->ceil_tex.x = (int)(current_floor.x * m->w_t[10]->w) % m->w_t[10]->w;
		m->ceil_tex.y = (int)(current_floor.y * m->w_t[10]->h) % m->w_t[10]->h;
		*m->bufp = ((t_uint *)m->w_t[9]->pixels)
							[m->w_t[9]->w * m->floor_tex.y + m->floor_tex.x];
		*(m->bufp + (HEIGHT - 2 * y) * WIDTH) =
		((t_uint *)m->w_t[10]->pixels)[m->w_t[10]->w * m->ceil_tex.y + m->ceil_tex.x];
		m->bufp += WIDTH;
	}
}

void	draw_cursor(t_map *m)
{
	int z;

	z = -5;
	while (++z < 5)
	{
		m->image[HEIGHT * WIDTH / 2 + WIDTH / 2 + z] = 0xFFFFFF;
		m->image[HEIGHT * WIDTH / 2 + (z * WIDTH + WIDTH / 2)] = 0xFFFFFF;
	}
}
