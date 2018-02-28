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

void	delete_sprite(t_uint *cell, t_uint type)
{
	if (type)
	{
		type == 12 ? EREASE_SPRITE(*cell) : 0;
		type == 15 ? EREASE_SPRITE(*cell) : 0;
	}
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
			key_up(e.key.keysym.scancode, map);
	}
	return (1);
}
