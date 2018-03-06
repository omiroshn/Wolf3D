/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:50:21 by omiroshn          #+#    #+#             */
/*   Updated: 2018/02/28 21:50:22 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	threads_create(SDL_Surface *screen, t_map map)
{
	SDL_Thread	*threads[THREADS];
	t_wolf		data[THREADS];
	double		coef;
	int			i;

	ft_bzero(screen->pixels, screen->w * screen->h * 4);
	coef = screen->w / THREADS;
	i = -1;
	while (++i < THREADS)
	{
		data[i] = (t_wolf){map, (int)i * coef, (int)(i + 1) * coef};
		threads[i] = SDL_CreateThread((int(*)())draw, NULL, &data[i]);
	}
	i = -1;
	while (++i < THREADS)
		SDL_WaitThread(threads[i], NULL);
}

void	lsync(void)
{
	int					delay;
	static unsigned int	time;
	static char			vsync = 1;

	vsync == 1 ? SDL_GL_SetSwapInterval(1) : 0;
	if (vsync)
	{
		delay = 16 - (SDL_GetTicks() - time);
		if (delay < 0)
			SDL_Delay(0);
		else
			SDL_Delay(delay);
		time = SDL_GetTicks();
	}
}

void	display_fps(t_map *m)
{
	static t_uint	fps;
	static t_uint	time_current;
	static t_uint	time_past;
	static t_uint	ticks;
	TTF_Font		*ttf;
	char			*fps_str;

	time_current = time(NULL);
	if (time_current - time_past && (time_past = time_current))
		fps = 1000 / (SDL_GetTicks() - ticks);
	ticks = SDL_GetTicks();
	fps_str = ft_itoa(fps);
	if (!(ttf = TTF_OpenFont(FONTS_FOLDER"arcadeclassic.regular.ttf", 30)))
		put_error(IMG_GetError());
	m->fps = TTF_RenderText_Solid(ttf, fps_str,
					(SDL_Color){255, 255, 255, 255});
	SDL_BlitSurface(m->fps, NULL, m->screen,
		&(SDL_Rect){ 10, 0, m->fps->w, m->fps->h});
	TTF_CloseFont(ttf);
	SDL_FreeSurface(m->fps);
	ft_memdel((void**)&fps_str);
	// 	printf("FPS: %d\n", (int)(fps));
}
