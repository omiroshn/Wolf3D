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
	m->camera.x = 2 * x / (double)(m->w) - 1;
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

void	perform_dda(t_map *m, int x)
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
		if (IS_WALL(m->karta.data[m->map.x][m->map.y]))
			break ;
		if (SPRITE(m->karta.data[m->map.x][m->map.y]))
			draw_sprite(m, m->karta.data, x);
	}
}

void	draw_cursor(t_map *m)
{
	int z;

	z = -5;
	while (++z < 5)
	{
		m->image[m->h * m->w / 2 + m->w / 2 + z] = 0xFFFFFF;
		m->image[m->h * m->w / 2 + (z * m->w + m->w / 2)] = 0xFFFFFF;
	}
}

void	draw_weapon(t_map *m)
{
	t_uint ticks;

	ticks = SDL_GetTicks();
	if (!ft_strcmp(m->name, MAPS_FOLDER"map2.map"))
	{
		SDL_BlitScaled(m->weapon, NULL, m->screen,
			&(SDL_Rect){m->screen->w + 150 - m->weapon->w,
				m->screen->h + 150 - m->weapon->h,
				m->weapon->w, m->weapon->h});
	}
	else
	{
		if (ticks - m->shoot < 300)
			SDL_BlitScaled(m->gunfire, NULL, m->screen,
				&(SDL_Rect){m->screen->w - 390 - m->gunfire->w,
					m->screen->h - 280 - m->gunfire->h,
					m->gunfire->w, m->gunfire->h});
		SDL_BlitScaled(m->weapon, NULL, m->screen,
			&(SDL_Rect){m->screen->w + 150 - m->weapon->w,
				m->screen->h + 150 - m->weapon->h,
				m->weapon->w * 3 / 4, m->weapon->h * 3 / 4});
	}
}
