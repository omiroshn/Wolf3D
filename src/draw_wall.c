/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:55:44 by omiroshn          #+#    #+#             */
/*   Updated: 2018/02/28 21:55:46 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_screen_wall(t_map *m, int texture, int line_height, int x)
{
	int y;
	int	d;

	y = m->draw_start - 1;
	m->bufp = (t_uint *)m->screen->pixels + m->draw_start * m->w + x;
	while (++y <= m->draw_end)
	{
		d = y * 2 - m->h + line_height;
		m->tex.y = line_height == 0 ? 0 : ((d * m->w_t[texture]->w
			/ line_height) / 2);
		if (m->tex.x >= 0 && m->tex.x < m->w_t[texture]->h &&
			m->tex.y >= 0 && m->tex.y < m->w_t[texture]->w && !*m->bufp)
			*m->bufp = ((t_uint *)m->w_t[texture]->pixels)
						[m->w_t[texture]->h * m->tex.y + m->tex.x];
		m->bufp += m->w;
	}
}

void	draw_wall(t_map *m, int x, t_uint **data)
{
	m->wall_dist = m->side == 0 ?
		(m->map.x - m->pos.x + (1 - m->step.x) / 2) / m->ray_dir.x :
		(m->map.y - m->pos.y + (1 - m->step.y) / 2) / m->ray_dir.y;
	m->line_height = m->wall_dist == 0 ? 0 : (int)(m->h / m->wall_dist);
	m->draw_start = -m->line_height / 2 + m->h / 2;
	m->draw_end = m->line_height / 2 + m->h / 2;
	m->draw_start < 0 ? m->draw_start = 0 : m->draw_start;
	m->draw_end >= m->h ? m->draw_end = m->h - 1 : m->draw_end;
	m->draw_end < 0 ? m->draw_end = m->h : m->draw_end;
	m->wall = m->side == 0 ? m->pos.y + m->wall_dist * m->ray_dir.y :
	m->pos.x + m->wall_dist * m->ray_dir.x;
	m->wall -= floor((m->wall));
	if (m->side)
		m->texture = m->ray_dir.y > 0 ? BOT_WALL(data[m->map.x][m->map.y])
									: TOP_WALL(data[m->map.x][m->map.y]);
	else
		m->texture = m->ray_dir.x > 0 ? RIGHT_WALL(data[m->map.x][m->map.y])
									: LEFT_WALL(data[m->map.x][m->map.y]);
	m->tex.x = (int)(m->wall * (double)(m->w_t[m->texture]->w));
	if (m->side == 0 && m->ray_dir.x > 0)
		m->tex.x = m->w_t[m->texture]->w - m->tex.x - 1;
	if (m->side == 1 && m->ray_dir.y < 0)
		m->tex.x = m->w_t[m->texture]->w - m->tex.x - 1;
	draw_screen_wall(m, m->texture, m->line_height, x);
}
