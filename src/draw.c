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

void	sprite_line(t_map *m, t_vec transf, t_ivec draw_se, int x)
{
	t_ivec	tex;
	int		y;

	tex.x = (int)(256 * (x - (-abs((int)(m->screen->h
		/ (transf.y))) / 2 + (int)((m->screen->w / 2)
		* (1 + transf.x / transf.y)))) * m->w_t[m->s_tex]->w
		/ abs((int)(m->screen->h / (transf.y)))) / 256;
	y = draw_se.y - 1;
	m->bufp = (t_uint *)m->screen->pixels + draw_se.y * m->w + x;
	while (++y < draw_se.x)
	{
		tex.y = (((y * 2 - m->screen->h + m->sprite_h)
			* m->w_t[m->s_tex]->h) / m->sprite_h) / 2;
		if (!*m->bufp && tex.x >= 0 && tex.y >= 0 && tex.x < m->w_t
			[m->s_tex]->w && tex.y < m->w_t[m->s_tex]->w)
			*m->bufp = ((t_uint *)m->w_t[m->s_tex]->pixels)
		[m->w_t[m->s_tex]->w * tex.y + tex.x] & 0xFFFFFF;
		m->bufp += m->w;
	}
}

void	draw_sprite(t_map *m, t_uint **data, int x)
{
	t_ivec	draw_se;
	t_vec	sprite;
	t_vec	transf;
	double	inv_det;

	m->s_tex = SPRITE(data[(int)m->map.x][(int)m->map.y]);
	sprite.x = m->map.x + 0.5 - m->pos.x;
	sprite.y = m->map.y + 0.5 - m->pos.y;
	inv_det = 1.0 / (m->plane.x * m->dir.y - m->dir.x * m->plane.y);
	transf.x = inv_det * (m->dir.y * sprite.x - m->dir.x * sprite.y);
	transf.y = inv_det * (-m->plane.y * sprite.x + m->plane.x * sprite.y);
	m->sprite_h = abs((int)(m->screen->h / (transf.y)));
	draw_se.y = -m->sprite_h / 2 + m->screen->h / 2;
	draw_se.x = m->sprite_h / 2 + m->screen->h / 2;
	draw_se.x = draw_se.x >= m->screen->h ? m->screen->h - 1 : draw_se.x;
	draw_se.y = draw_se.y < 0 ? 0 : draw_se.y;
	sprite_line(m, transf, draw_se, x);
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

void	draw_screen_wall(t_map *m, int texture, int line_height, int x)
{
	int y;
	int	d;

	y = m->draw_start - 1;
	m->bufp = (t_uint *)m->screen->pixels + m->draw_start * m->w + x;
	while (++y <= m->draw_end)
	{
		d = y * 2 - m->h + line_height;
		m->tex.y = ((d * m->w_t[texture]->w / line_height) / 2);
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
	m->line_height = (int)(m->h / m->wall_dist);
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
	if (!ft_strcmp(m->name, MAPS_FOLDER"map2.map"))
	{
		SDL_BlitScaled(m->weapon, NULL, m->screen,
			&(SDL_Rect){m->screen->w + 150 - m->weapon->w,
				m->screen->h + 150 - m->weapon->h,
				m->weapon->w, m->weapon->h});
	}
	else
	{
		SDL_BlitScaled(m->weapon, NULL, m->screen,
			&(SDL_Rect){m->screen->w + 150 - m->weapon->w,
				m->screen->h + 150 - m->weapon->h,
				m->weapon->w * 3 / 4, m->weapon->h * 3 / 4});
	}
}
