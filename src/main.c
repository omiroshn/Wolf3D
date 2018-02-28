/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:50:22 by omiroshn          #+#    #+#             */
/*   Updated: 2018/02/07 18:50:24 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_strsplit(t_uint **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	draw(t_wolf *w)
{
	int x;

	x = w->start - 1;
	while (++x < w->end)
	{
		draw_camera(&w->map, x);
		perform_dda(&w->map, x);
		draw_wall(&w->map, x, w->map.karta.data);
		draw_floor(&w->map, w->map.karta.data);
	}
}

void	init(t_map *m)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		put_error(SDL_GetError());
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
		put_error(SDL_GetError());
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		put_error(SDL_GetError());
	m->window = SDL_CreateWindow("Wolf3d",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	if (!m->window)
		exit(1);
	m->screen = SDL_GetWindowSurface(m->window);
	m->image = m->screen->pixels;
	m->dir.x = -1;
	m->dir.y = 0;
	m->plane.x = 0;
	m->plane.y = 0.77;
	m->move = 0;
	m->rotate = 0;
	m->mov_speed = 0.08;
	m->rot_speed = 0.05;
	m->shoot = -1000;
	m->w = WIDTH;
	m->h = HEIGHT;
}

void	load_music(t_map *m)
{
	if (!ft_strcmp(m->name, MAPS_FOLDER"map1.map"))
	{
		if (!(m->game_sound = Mix_LoadMUS(MUSIC_FOLDER"Wolfenstein_3D.ogg")))
			put_error(IMG_GetError());
		if (!(m->shoot_sound = Mix_LoadWAV(MUSIC_FOLDER"gun-gunshot-02.wav")))
			put_error(IMG_GetError());
	}
	else if (!ft_strcmp(m->name, MAPS_FOLDER"map2.map"))
		if (!(m->game_sound = Mix_LoadMUS(MUSIC_FOLDER"Mutation.ogg")))
			put_error(IMG_GetError());
	Mix_PlayMusic(m->game_sound, -1);
}

int		main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		put_usage();
	read_map(&map, argv[1]);
	init(&map);
	define_textures(&map);
	load_music(&map);

	while (TRUE)
	{
		if (!key_function(&map))
			break ;
		map.move ? scan_ws(&map, map.move * map.mov_speed) : 0;
		map.rotate ? scan_ad(&map, map.rotate * map.rot_speed) : 0;
		threads_create(map.screen, map);
		draw_cursor(&map);
		draw_weapon(&map);
		display_fps();
		lsync();
		SDL_UpdateWindowSurface(map.window);
	}
	return (quit(&map));
}
