/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:35:52 by omiroshn          #+#    #+#             */
/*   Updated: 2018/02/22 19:35:53 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	scan_ws(t_map *m, double d)
{
	double	w;
	long	path;
	long	path2;

	w = d > 0 ? 0.25 : -0.25;
	path = m->karta.data[(int)(m->pos.x + m->dir.x *
		(w + d))][(int)m->pos.y - (int)(m->dir.y * w)];
	path2 = m->karta.data[(int)m->pos.x -
		(int)(m->dir.x * w)][(int)(m->pos.y + m->dir.y
		* (w + d))];
	if (!ft_strcmp(m->name, MAPS_FOLDER"map1.map"))
	{
		if (!IS_WALL(path) && !IS_SPRITE(path))
			m->pos.x += m->dir.x * d;
		if (!IS_WALL(path2) && !IS_SPRITE(path2))
			m->pos.y += m->dir.y * d;
	}
	if (!ft_strcmp(m->name, MAPS_FOLDER"map2.map"))
	{
		if (!IS_WALL(path))
			m->pos.x += m->dir.x * d;
		if (!IS_WALL(path2))
			m->pos.y += m->dir.y * d;
	}
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

void	key_down(SDL_Scancode key, t_map *map)
{
	key == SDL_SCANCODE_W ? map->move = 1 : 0;
	key == SDL_SCANCODE_S ? map->move = -1 : 0;
	key == SDL_SCANCODE_A ? map->rotate = 1 : 0;
	key == SDL_SCANCODE_D ? map->rotate = -1 : 0;
	key == SDL_SCANCODE_UP ? map->move = 1 : 0;
	key == SDL_SCANCODE_DOWN ? map->move = -1 : 0;
	key == SDL_SCANCODE_LEFT ? map->rotate = 1 : 0;
	key == SDL_SCANCODE_RIGHT ? map->rotate = -1 : 0;
	key == SDL_SCANCODE_LSHIFT ? (map->mov_speed = 0.13)
								&& (map->rot_speed = 0.07) : 0;
	key == SDL_SCANCODE_RSHIFT ? (map->mov_speed = 0.13)
								&& (map->rot_speed = 0.07) : 0;
}

void	key_up(SDL_Event e, SDL_Scancode key, t_map *map)
{
	SDL_Window	*win;
	static int	full_screen;

	key == SDL_SCANCODE_W || key == SDL_SCANCODE_S ? map->move = 0 : 0;
	key == SDL_SCANCODE_A || key == SDL_SCANCODE_D ? map->rotate = 0 : 0;
	key == SDL_SCANCODE_UP || key == SDL_SCANCODE_DOWN ? map->move = 0 : 0;
	key == SDL_SCANCODE_LEFT || key == SDL_SCANCODE_RIGHT ? map->rotate = 0 : 0;
	key == SDL_SCANCODE_LSHIFT ? (map->mov_speed = 0.08)
												&& (map->rot_speed = 0.05) : 0;
	key == SDL_SCANCODE_RSHIFT ? (map->mov_speed = 0.08)
												&& (map->rot_speed = 0.05) : 0;
	if (key == SDL_SCANCODE_TAB)
		full_screen && !(full_screen = 0)
		? SDL_SetWindowFullscreen(map->window, 0) : (full_screen = 1)
		&& SDL_SetWindowFullscreen(map->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void	resize_window(t_map *m, int new_width, int new_height)
{
	m->w = new_width;
	m->h = new_height;
	!(m->screen = SDL_GetWindowSurface(m->window))
		? put_error(SDL_GetError()) : 0;
	m->image = m->screen->pixels;
}

int		key_function(t_map *map)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN
						&& e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			return (0);
		else if (e.window.event == SDL_WINDOWEVENT_RESIZED)
			resize_window(map, e.window.data1, e.window.data2);
		else if (e.type == SDL_KEYDOWN)
			key_down(e.key.keysym.scancode, map);
		else if (e.type == SDL_KEYUP)
			key_up(e, e.key.keysym.scancode, map);
	}
	return (1);
}
