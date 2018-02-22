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

const int worldMap[mapWidth][mapHeight]=
{
  {8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
  {8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
  {7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
  {7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
  {2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
  {2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
  {2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};

inline static void	scan_ws(SDL_Event e, SDL_Keycode key, t_map *map)
{
	double moveSpeed = 0.3;

	if (key == SDL_SCANCODE_W || key == SDL_SCANCODE_UP) //w
	{
		if (!worldMap[(int)(map->pos.x + map->dir.x * moveSpeed)][(int)(map->pos.y)])
			map->pos.x += map->dir.x * moveSpeed;
		if (!worldMap[(int)(map->pos.x)][(int)(map->pos.y + map->dir.y * moveSpeed)])
			map->pos.y += map->dir.y * moveSpeed;
	}
	if (key == SDL_SCANCODE_S || key == SDL_SCANCODE_DOWN)  //s
	{
		if (!worldMap[(int)(map->pos.x - map->dir.x * moveSpeed)][(int)(map->pos.y)])
			map->pos.x -= map->dir.x * moveSpeed;
		if (!worldMap[(int)(map->pos.x)][(int)(map->pos.y - map->dir.y * moveSpeed)])
			map->pos.y -= map->dir.y * moveSpeed;
	}
}

inline static void	scan_ad(SDL_Event e, SDL_Keycode key, t_map *map)
{
	double oldDirX;
	double oldPlaneX;
	double rotSpeed = 0.08;

	if (key == SDL_SCANCODE_A || key == SDL_SCANCODE_LEFT)  //a
	{
		oldDirX = map->dir.x;
		map->dir.x = map->dir.x * cos(rotSpeed) - map->dir.y * sin(rotSpeed);
		map->dir.y = oldDirX * sin(rotSpeed) + map->dir.y * cos(rotSpeed);
		oldPlaneX = map->plane.x;
		map->plane.x = map->plane.x * cos(rotSpeed) - map->plane.y * sin(rotSpeed);
		map->plane.y = oldPlaneX * sin(rotSpeed) + map->plane.y * cos(rotSpeed);
	}
	if (key == SDL_SCANCODE_D || key == SDL_SCANCODE_RIGHT)  //d
	{
		oldDirX = map->dir.x;
		map->dir.x = map->dir.x * cos(-rotSpeed) - map->dir.y * sin(-rotSpeed);
		map->dir.y = oldDirX * sin(-rotSpeed) + map->dir.y * cos(-rotSpeed);
		oldPlaneX = map->plane.x;
		map->plane.x = map->plane.x * cos(-rotSpeed) - map->plane.y * sin(-rotSpeed);
		map->plane.y = oldPlaneX * sin(-rotSpeed) + map->plane.y * cos(-rotSpeed);
	}
}

int		key_function(t_map *map)
{
	SDL_Event e;

	while(SDL_PollEvent(&e))
	{
		if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN
						&& e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			return (0);
		scan_ws(e, e.key.keysym.scancode, map);
		scan_ad(e, e.key.keysym.scancode, map);
	}
	return (1);
}

void	draw_floor()
{

}

void	draw(t_thread *t)
{
	int x;
	int texture;
	t_ivec map;
	t_ivec step;
	t_vec side_dist;
	t_vec delta_dist;
	t_vec camera;
	int side;
	int lineHeight;
	int draw_start;
	int draw_end;
	int color;
	unsigned int *bufp;

	x = t->start - 1;
	while (++x < t->end)
	{
		camera.x = 2 * x / (double)(WIDTH) - 1;
		t->map.ray_dir.x = t->map.dir.x + t->map.plane.x * camera.x;
		t->map.ray_dir.y = t->map.dir.y + t->map.plane.y * camera.x;
		map.x = (int)(t->map.pos.x);
		map.y = (int)(t->map.pos.y);
		delta_dist.x = fabs(1 / t->map.ray_dir.x);
		delta_dist.y = fabs(1 / t->map.ray_dir.y);
		if (t->map.ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (t->map.pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - t->map.pos.x) * delta_dist.x;
		}
		if (t->map.ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (t->map.pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - t->map.pos.y) * delta_dist.y;
		}
		//perform DDA
		while (1)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[map.x][map.y] > 0)
				break ;
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if (side == 0)
			t->map.wall_dist = (map.x - t->map.pos.x + (1 - step.x) / 2) / t->map.ray_dir.x;
		else
			t->map.wall_dist = (map.y - t->map.pos.y + (1 - step.y) / 2) / t->map.ray_dir.y;

		//Calculate height of line to draw on screen
		lineHeight = (int)(HEIGHT / t->map.wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		draw_start = -lineHeight / 2 + HEIGHT / 2;
		draw_end = lineHeight / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = t->map.pos.y + t->map.wall_dist * t->map.ray_dir.y;
		else
			wallX = t->map.pos.x + t->map.wall_dist * t->map.ray_dir.x;
		wallX -= floor((wallX));
		//x coordinate on the texture
		texture = worldMap[map.x][map.y] - 1;
		int texX = (int)(wallX * (double)(t->map.w_t[texture]->w));
		if (side == 0 && t->map.ray_dir.x > 0)
			texX = t->map.w_t[texture]->w - texX - 1;
		if (side == 1 && t->map.ray_dir.y < 0)
			texX = t->map.w_t[texture]->w - texX - 1;
		if (side == 1)
			color = color / 2;
		int y = draw_start;
		bufp = (unsigned int *)t->map.screen->pixels + draw_start * t->map.screen->w + x;
		while (y <= draw_end)
		{
			int d = y * 2 - HEIGHT + lineHeight;
			int texY = ((d * t->map.w_t[texture]->w / lineHeight) / 2);
			if (texX >= 0 && texX < t->map.w_t[texture]->h && texY >= 0 && texY < t->map.w_t[texture]->w)
				*bufp = ((unsigned int *)t->map.w_t[texture]->pixels)[t->map.w_t[texture]->h * texY + texX];
			bufp += WIDTH;
			y++;
		}

		t_vec floor_wall;
		if (side == 0 && t->map.ray_dir.x > 0)
		{
			floor_wall.x = map.x;
			floor_wall.y = map.y + wallX;
		}
		else if (side == 0 && t->map.ray_dir.x < 0)
		{
			floor_wall.x = map.x + 1.0;
			floor_wall.y = map.y + wallX;
		}
		else if (side == 1 && t->map.ray_dir.y > 0)
		{
			floor_wall.x = map.x + wallX;
			floor_wall.y = map.y;
		}
		else
		{
			floor_wall.x = map.x + wallX;
			floor_wall.y = map.y + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = t->map.wall_dist;
		distPlayer = 0.0;

		if (draw_end < 0)
			draw_end = HEIGHT;
		// draw_floor();
		t_vec current_floor;
		y = draw_end + 1;
		while (y < HEIGHT)
		{
			currentDist = HEIGHT / (2.0 * y - HEIGHT);
			double weight = (currentDist - distPlayer) / (distWall - distPlayer);
			current_floor.x = weight * floor_wall.x + (1.0 - weight) * t->map.pos.x;
			current_floor.y = weight * floor_wall.y + (1.0 - weight) * t->map.pos.y;
			int floorTexX, floorTexY;
			int ceilTexX, ceilTexY;
			floorTexX = (int)(current_floor.x * t->map.w_t[9]->w) % t->map.w_t[9]->w;
			floorTexY = (int)(current_floor.y * t->map.w_t[9]->h) % t->map.w_t[9]->h;
			ceilTexX = (int)(current_floor.x * t->map.w_t[10]->w / 4) % t->map.w_t[10]->w;
			ceilTexY = (int)(current_floor.y * t->map.w_t[10]->h / 4) % t->map.w_t[10]->h;
			//floor
			*bufp = (((unsigned int *)t->map.w_t[9]->pixels)[t->map.w_t[9]->w * floorTexY + floorTexX]);
			bufp += WIDTH;
			//ceiling (symmetrical!)
			t->map.image[(HEIGHT - y) * WIDTH + x] = ((unsigned int *)t->map.w_t[10]->pixels)[t->map.w_t[10]->w * ceilTexY + ceilTexX];
			y++;
		}
		// t->map.image[HEIGHT * WIDTH + x] = 0xFFFFFF;
		// bufp[HEIGHT * WIDTH + x] = 0xFFFFFF;
		// printf("%i\n", HEIGHT * WIDTH / 2);
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
		data[i] = (t_thread){screen, map, (int)i * coef, (int)(i + 1) * coef};
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
	m->fps.time = 0;
	m->fps.old_time = 0;
	m->pos.x = 22;
	m->pos.y = 12;
	m->dir.x = -1;
	m->dir.y = 0;
	m->plane.x = 0;
	m->plane.y = 0.66;
}

void	load_textures(t_map *m)
{
	m->w_t[0] = IMG_Load("./resources/uganda.jpg");
	m->w_t[1] = IMG_Load("./resources/akatski.jpg");
	m->w_t[2] = IMG_Load("./resources/anime.png");
	m->w_t[3] = IMG_Load("./resources/pain.png");
	m->w_t[4] = IMG_Load("./resources/kakashi.png");
	m->w_t[5] = IMG_Load("./resources/narutoramen.jpg");
	m->w_t[6] = IMG_Load("./resources/narutopixel.png");
	m->w_t[7] = IMG_Load("./resources/ugandaflag.png");
	m->w_t[8] = IMG_Load("./resources/eye.png");
	m->w_t[9] = IMG_Load("./resources/sand.jpg");
	m->w_t[10] = IMG_Load("./resources/wood.png");
}


// void	fps_initial(void)
// {
// 	int NextTick = 0;
// 	int FPS = 60;
// 	interval = 1 * 1000 / FPS;
// }

// void	fps_func(void)
// {
// 	if (NextTick > SDL_GetTicks())
// 		SDL_Delay(NextTick - SDL_GetTicks());
// 	NextTick = SDL_GetTicks() + interval;
// }

void	lsync(void)
{
	int					delay;
	static unsigned int	time;
	static char			vsync = 1;

	if (vsync)
		vsync = SDL_GL_SetSwapInterval(1);
	else
		vsync = 0;
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
	unsigned int		t_c;
	static unsigned int	t_p;
	static unsigned int	c_b;

	t_c = time(NULL);
	if (t_c - t_p && (t_p = t_c))
	{
		frame_rate = SDL_GetTicks() - c_b;
		printf("%d\n", (int)(1000.0 / frame_rate));
	}
	c_b = SDL_GetTicks();
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
			return (0);
		threads_create(map.screen, map);
		display_fps(map.screen);
		lsync();
		SDL_UpdateWindowSurface(map.window);
	}
	SDL_DestroyWindow(map.window);
	SDL_Quit();
	return (0);
}
