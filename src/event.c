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
	if (!IS_WALL(map->karta.data[(int)(map->pos.x + map->dir.x *
		(map->mov_speed * map->move))][(int)map->pos.y]))
		map->pos.x += map->dir.x * d;
	if (!IS_WALL(map->karta.data[(int)map->pos.x][(int)(map->pos.y + map->dir.y
		* (map->mov_speed * map->move))]))
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

void	key_up(SDL_Scancode key, t_map *map)
{
	key == SDL_SCANCODE_W || key == SDL_SCANCODE_S ? map->move = 0 : 0;
	key == SDL_SCANCODE_A || key == SDL_SCANCODE_D ? map->rotate = 0 : 0;
	key == SDL_SCANCODE_UP || key == SDL_SCANCODE_DOWN ? map->move = 0 : 0;
	key == SDL_SCANCODE_LEFT || key == SDL_SCANCODE_RIGHT ? map->rotate = 0 : 0;
	key == SDL_SCANCODE_LSHIFT ? (map->mov_speed = 0.08)
												&& (map->rot_speed = 0.05) : 0;
	key == SDL_SCANCODE_RSHIFT ? (map->mov_speed = 0.08)
												&& (map->rot_speed = 0.05) : 0;
}

int		key_function(t_map *map)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN
						&& e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			return (0);
		else if (e.type == SDL_KEYDOWN)
			key_down(e.key.keysym.scancode, map);
		else if (e.type == SDL_KEYUP)
			key_up(e.key.keysym.scancode, map);
	}
	return (1);
}
