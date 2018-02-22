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

void	draw(t_thread *t)
{
	int x;
	
	x = t->start - 1;
	while (++x < t->end)
	{
		draw_camera(&t->map, x);
		perform_dda(&t->map);
		draw_wall(&t->map, x);
		draw_floor(&t->map);
		draw_cursor(&t->map);
	}
}

void	threads_create(SDL_Surface *screen, t_map map)
{
	SDL_Thread	*threads[THREADS];
	t_thread	data[THREADS];
	int			i;
	double		coef;

	ft_bzero(screen->pixels, WIDTH * HEIGHT * 4);
	coef = WIDTH / THREADS;
	i = -1;
	while (++i < THREADS)
	{
		data[i] = (t_thread){map, (int)i * coef, (int)(i + 1) * coef};
		threads[i] = SDL_CreateThread((int(*)())draw, NULL, &data[i]);
	}
	i = -1;
	while (++i < THREADS)
		SDL_WaitThread(threads[i], NULL);
}

void 	init(t_map *m)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m->window = SDL_CreateWindow("Wolf3d",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	if (!m->window)
		exit (1);
	m->screen = SDL_GetWindowSurface(m->window);
	m->image = m->screen->pixels;
	m->pos.x = 22;
	m->pos.y = 12;
	m->dir.x = -1;
	m->dir.y = 0;
	m->plane.x = 0;
	m->plane.y = 0.66;
}

void	load_textures(t_map *m)
{
	m->w_t[0] = IMG_Load("./resources/images/uganda.jpg");
	m->w_t[1] = IMG_Load("./resources/images/akatski.jpg");
	m->w_t[2] = IMG_Load("./resources/images/anime.png");
	m->w_t[3] = IMG_Load("./resources/images/pain.png");
	m->w_t[4] = IMG_Load("./resources/images/kakashi.png");
	m->w_t[5] = IMG_Load("./resources/images/narutoramen.jpg");
	m->w_t[6] = IMG_Load("./resources/images/narutopixel.png");
	m->w_t[7] = IMG_Load("./resources/images/ugandaflag.png");
	m->w_t[8] = IMG_Load("./resources/images/eye.png");
	m->w_t[9] = IMG_Load("./resources/images/sand.jpg");
	m->w_t[10] = IMG_Load("./resources/images/wood.png");
}

void	lsync(void)
{
	int					delay;
	static unsigned int	time;
	static char			vsync = 1;

	vsync == 1 ? SDL_GL_SetSwapInterval(1) : 0;
	if (vsync)
	{
		delay = 17 - (SDL_GetTicks() - time);
		if (delay < 0)
			SDL_Delay(0);
		else
			SDL_Delay(delay);
		time = SDL_GetTicks();
	}
}

void	display_fps(SDL_Surface *surface)
{
	static unsigned int	frame_rate;
	static unsigned int	time_current;
	static unsigned int	time_past;
	static unsigned int	ticks;

	time_current = time(NULL);
	if (time_current - time_past && (time_past = time_current))
	{
		frame_rate = SDL_GetTicks() - ticks;
		printf("FPS: %d\n", (int)(1000.0 / frame_rate));
	}
	ticks = SDL_GetTicks();
}


int main(int argc, char **argv)
{
	t_map map;
	int running = 1;

	init(&map);
	load_textures(&map);
	while (running)
	{
		if (!key_function(&map))
			break ;
		threads_create(map.screen, map);
		display_fps(map.screen);
		lsync();
		SDL_UpdateWindowSurface(map.window);
	}
	SDL_DestroyWindow(map.window);
	SDL_Quit();
	return (0);
}
