/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:52:52 by omiroshn          #+#    #+#             */
/*   Updated: 2018/02/28 21:52:54 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	scan_ws(t_map *m, double d)
{
	double	w;

	w = d > 0 ? 0.25 : -0.25;
	if (!IS_WALL(m->karta.data[(int)(m->pos.x + m->dir.x *
		(w + d))][(int)m->pos.y - (int)(m->dir.y * w)])
		&& !IS_SPRITE(m->karta.data[(int)(m->pos.x + m->dir.x *
			(w + d))][(int)m->pos.y - (int)(m->dir.y * w)]))
		m->pos.x += m->dir.x * d;
	if (!IS_WALL(m->karta.data[(int)m->pos.x - (int)(m->dir.x * w)]
		[(int)(m->pos.y + m->dir.y * (w + d))])
		&& !IS_SPRITE(m->karta.data[(int)m->pos.x - (int)(m->dir.x * w)]
			[(int)(m->pos.y + m->dir.y * (w + d))]))
		m->pos.y += m->dir.y * d;
	if (!ft_strcmp(m->name, MAPS_FOLDER"map2.map"))
		delete_sprite(&m->karta.data[(int)m->pos.x][(int)m->pos.y],
			SPRITE(m->karta.data[(int)m->pos.x - (int)(m->dir.x * w)]
				[(int)(m->pos.y + m->dir.y * (w + d))]));
}

void	scan_ad(t_map *map, double alpha)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = map->dir.x;
	map->dir.x = map->dir.x * cos(alpha) - map->dir.y * sin(alpha);
	map->dir.y = old_dir_x * sin(alpha) + map->dir.y * cos(alpha);
	old_plane_x = map->plane.x;
	map->plane.x = map->plane.x * cos(alpha) - map->plane.y * sin(alpha);
	map->plane.y = old_plane_x * sin(alpha) + map->plane.y * cos(alpha);
}

void	key_down(SDL_Scancode key, t_map *m)
{
	key == SDL_SCANCODE_W ? m->move = 1 : 0;
	key == SDL_SCANCODE_S ? m->move = -1 : 0;
	key == SDL_SCANCODE_A ? m->rotate = 1 : 0;
	key == SDL_SCANCODE_D ? m->rotate = -1 : 0;
	key == SDL_SCANCODE_UP ? m->move = 1 : 0;
	key == SDL_SCANCODE_DOWN ? m->move = -1 : 0;
	key == SDL_SCANCODE_LEFT ? m->rotate = 1 : 0;
	key == SDL_SCANCODE_RIGHT ? m->rotate = -1 : 0;
	key == SDL_SCANCODE_LSHIFT ? (m->mov_speed = 0.13)
								&& (m->rot_speed = 0.07) : 0;
	key == SDL_SCANCODE_RSHIFT ? (m->mov_speed = 0.13)
								&& (m->rot_speed = 0.07) : 0;
	if (key == SDL_SCANCODE_SPACE && SDL_GetTicks() - m->shoot > 400)
	{
		m->shoot = SDL_GetTicks();
		if (ft_strcmp(m->name, MAPS_FOLDER"map2.map"))
			Mix_PlayChannel(0, m->shoot_sound, 0);
	}
	if (key == SDL_SCANCODE_M)
		!Mix_PausedMusic() ? Mix_PauseMusic() : Mix_ResumeMusic();
}

void	key_up(SDL_Scancode key, t_map *m)
{
	static int	full_screen;

	key == SDL_SCANCODE_W || key == SDL_SCANCODE_S ? m->move = 0 : 0;
	key == SDL_SCANCODE_A || key == SDL_SCANCODE_D ? m->rotate = 0 : 0;
	key == SDL_SCANCODE_UP || key == SDL_SCANCODE_DOWN ? m->move = 0 : 0;
	key == SDL_SCANCODE_LEFT || key == SDL_SCANCODE_RIGHT ? m->rotate = 0 : 0;
	key == SDL_SCANCODE_LSHIFT ? (m->mov_speed = 0.08)
												&& (m->rot_speed = 0.05) : 0;
	key == SDL_SCANCODE_RSHIFT ? (m->mov_speed = 0.08)
												&& (m->rot_speed = 0.05) : 0;
	if (key == SDL_SCANCODE_TAB)
		full_screen && !(full_screen = 0)
		? SDL_SetWindowFullscreen(m->window, 0) : (full_screen = 1)
		&& SDL_SetWindowFullscreen(m->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}
