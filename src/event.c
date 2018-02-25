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

void	scan_ws(t_map *map, double d)
{
	double	w;

	w = d > 0 ? 0.25 : -0.25;
	if (!IS_WALL(map->karta.data[(int)(map->pos.x + map->dir.x *
		(w + d))][(int)map->pos.y - (int)(map->dir.y * w)]))
		map->pos.x += map->dir.x * d;
	if (!IS_WALL(map->karta.data[(int)map->pos.x -
		(int)(map->dir.x * w)][(int)(map->pos.y + map->dir.y
		* (w + d))]))
		map->pos.y += map->dir.y * d;
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
	{
		// full_screen && !(full_screen = 0) ? SDL_SetWindowFullscreen(map->window, 0)
		// : (full_screen = 1) && SDL_SetWindowFullscreen(map->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		if (!full_screen)
		{
			int i = SDL_GetWindowDisplayIndex(map->window);
			SDL_Rect j;
			SDL_GetDisplayBounds(i, &j);
			// screenWidth = j.w;
			// screenHeight = j.h;
			SDL_SetWindowFullscreen(map->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			full_screen = 1;
		}
		else
		{
			int i = SDL_GetWindowDisplayIndex(map->window);
			// screenWidth = windowedWidth;
			// screenHeight = windowedHeight;
			SDL_SetWindowFullscreen(map->window, 0);
			full_screen = 0;
		}
	}
}

void	sgl_resize_window(t_map *m, t_uint wind_id, int new_width, int new_height)
{
	// if (!(win = sgl_get_window_by_id(win_id)))
	// 	return ;
	m->w = new_width;
	m->h = new_height;
	!(m->screen = SDL_GetWindowSurface(m->window))
		? put_error(SDL_GetError()) : 0;
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
			sgl_resize_window(map, e.window.windowID, e.window.data1,
										e.window.data2);
		else if (e.type == SDL_KEYDOWN)
			key_down(e.key.keysym.scancode, map);
		else if (e.type == SDL_KEYUP)
			key_up(e, e.key.keysym.scancode, map);
	}
	return (1);
}
