/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:55:50 by omiroshn          #+#    #+#             */
/*   Updated: 2018/02/28 21:55:52 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
