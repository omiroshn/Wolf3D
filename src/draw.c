/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <omiroshn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 06:37:48 by omiroshn          #+#    #+#             */
/*   Updated: 2018/01/05 17:01:08 by omiroshn         ###   ########.fr       */
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

void	scan_ws(t_map *map, double d)
{
	if (!worldMap[(int)(map->pos.x + map->dir.x * (map->mov_speed * map->move))][(int)map->pos.y])
		map->pos.x += map->dir.x * d;
	if (!worldMap[(int)map->pos.x][(int)(map->pos.y + map->dir.y * (map->mov_speed * map->move))])
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

void	pull_down(SDL_Scancode key, t_map *map)
{
	key == SDL_SCANCODE_W ? map->move =  1 : 0;
	key == SDL_SCANCODE_S ? map->move =  -1 : 0;
	key == SDL_SCANCODE_A ? map->rotate = 1 : 0;
	key == SDL_SCANCODE_D ? map->rotate = -1 : 0;
	key == SDL_SCANCODE_UP ? map->move =  1 : 0;
	key == SDL_SCANCODE_DOWN ? map->move =  -1 : 0;
	key == SDL_SCANCODE_LEFT ? map->rotate = 1 : 0;
	key == SDL_SCANCODE_RIGHT ? map->rotate = -1 : 0;
	key == SDL_SCANCODE_LSHIFT ? (map->mov_speed = 0.13) && (map->rot_speed = 0.07) : 0;
	key == SDL_SCANCODE_RSHIFT ? (map->mov_speed = 0.13) && (map->rot_speed = 0.07) : 0;
}

void	pull_up(SDL_Scancode key, t_map *map)
{
	key == SDL_SCANCODE_W || key == SDL_SCANCODE_S ? map->move =  0 : 0;
	key == SDL_SCANCODE_A || key == SDL_SCANCODE_D ? map->rotate = 0 : 0;
	key == SDL_SCANCODE_UP || key == SDL_SCANCODE_DOWN ? map->move =  0 : 0;
	key == SDL_SCANCODE_LEFT || key == SDL_SCANCODE_RIGHT ? map->rotate = 0 : 0;
	key == SDL_SCANCODE_LSHIFT ? (map->mov_speed = 0.08) && (map->rot_speed = 0.05) : 0;
	key == SDL_SCANCODE_RSHIFT ? (map->mov_speed = 0.08) && (map->rot_speed = 0.05) : 0;
}

int		key_function(t_map *map)
{
	SDL_Event	e;

	while(SDL_PollEvent(&e))
	{
		if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN
						&& e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			return (0);
		else if (e.type == SDL_KEYDOWN)
			pull_down(e.key.keysym.scancode, map);
		else if (e.type == SDL_KEYUP)
			pull_up(e.key.keysym.scancode, map);
	}
	return (1);
}

void	draw_camera(t_map *m, int x)
{
	m->camera.x = 2 * x / (double)(WIDTH) - 1;
	m->ray_dir.x = m->dir.x + m->plane.x * m->camera.x;
	m->ray_dir.y = m->dir.y + m->plane.y * m->camera.x;
	m->map.x = (int)(m->pos.x);
	m->map.y = (int)(m->pos.y);
	m->delta_dist.x = fabs(1 / m->ray_dir.x);
	m->delta_dist.y = fabs(1 / m->ray_dir.y);
	if (m->ray_dir.x < 0)
	{
		m->step.x = -1;
		m->side_dist.x = (m->pos.x - m->map.x) * m->delta_dist.x;
	}
	else
	{
		m->step.x = 1;
		m->side_dist.x = (m->map.x + 1.0 - m->pos.x) * m->delta_dist.x;
	}
	if (m->ray_dir.y < 0)
	{
		m->step.y = -1;
		m->side_dist.y = (m->pos.y - m->map.y) * m->delta_dist.y;
	}
	else
	{
		m->step.y = 1;
		m->side_dist.y = (m->map.y + 1.0 - m->pos.y) * m->delta_dist.y;
	}
}

void	perform_dda(t_map *m)
{
	while (1)
	{
		if (m->side_dist.x < m->side_dist.y)
		{
			m->side_dist.x += m->delta_dist.x;
			m->map.x += m->step.x;
			m->side = 0;
		}
		else
		{
			m->side_dist.y += m->delta_dist.y;
			m->map.y += m->step.y;
			m->side = 1;
		}
		if (worldMap[m->map.x][m->map.y] > 0)
			break ;
	}
}

void	draw_wall(t_map *m, int x)
{
	int texture;
	int lineHeight;

	//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
	if (m->side == 0)
		m->wall_dist = (m->map.x - m->pos.x + (1 - m->step.x) / 2) / m->ray_dir.x;
	else
		m->wall_dist = (m->map.y - m->pos.y + (1 - m->step.y) / 2) / m->ray_dir.y;

	//Calculate height of line to draw on screen
	lineHeight = (int)(HEIGHT / m->wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	m->draw_start = -lineHeight / 2 + HEIGHT / 2;
	m->draw_end = lineHeight / 2 + HEIGHT / 2;
	if (m->draw_start < 0)
		m->draw_start = 0;
	if (m->draw_end >= HEIGHT)
		m->draw_end = HEIGHT - 1;

	//calculate value of m->wall
	//where exactly the wall was hit
	if (m->side == 0)
		m->wall = m->pos.y + m->wall_dist * m->ray_dir.y;
	else
		m->wall = m->pos.x + m->wall_dist * m->ray_dir.x;
	m->wall -= floor((m->wall));
	//x coordinate on the texture
	texture = worldMap[m->map.x][m->map.y] - 1;
	m->tex.x = (int)(m->wall * (double)(m->w_t[texture]->w));
	if (m->side == 0 && m->ray_dir.x > 0)
		m->tex.x = m->w_t[texture]->w - m->tex.x - 1;
	if (m->side == 1 && m->ray_dir.y < 0)
		m->tex.x = m->w_t[texture]->w - m->tex.x - 1;
	int y = m->draw_start;
	m->bufp = (unsigned int *)m->screen->pixels + m->draw_start * m->screen->w + x;
	while (y <= m->draw_end)
	{
		int d = y * 2 - HEIGHT + lineHeight;
		m->tex.y = ((d * m->w_t[texture]->w / lineHeight) / 2);
		if (m->tex.x >= 0 && m->tex.x < m->w_t[texture]->h && m->tex.y >= 0 && m->tex.y < m->w_t[texture]->w)
			*m->bufp = ((unsigned int *)m->w_t[texture]->pixels)[m->w_t[texture]->h * m->tex.y + m->tex.x];
		m->bufp += WIDTH;
		y++;
	}
}

void	draw_floor(t_map *m)
{
	t_vec	current_floor;
	t_vec	floor_wall;
	int		y;
	double weight;
	int floorTexX, floorTexY;
	int ceilTexX, ceilTexY;

	if (m->side == 0 && m->ray_dir.x > 0)
	{
		floor_wall.x = m->map.x;
		floor_wall.y = m->map.y + m->wall;
	}
	else if (m->side == 0 && m->ray_dir.x < 0)
	{
		floor_wall.x = m->map.x + 1.0;
		floor_wall.y = m->map.y + m->wall;
	}
	else if (m->side == 1 && m->ray_dir.y > 0)
	{
		floor_wall.x = m->map.x + m->wall;
		floor_wall.y = m->map.y;
	}
	else
	{
		floor_wall.x = m->map.x + m->wall;
		floor_wall.y = m->map.y + 1.0;
	}
	m->dist_wall = m->wall_dist;
	m->dist_player = 0.0;

	if (m->draw_end < 0)
		m->draw_end = HEIGHT;
	y = m->draw_end + 1;
	while (y < HEIGHT)
	{
		m->current_dist = HEIGHT / (2.0 * y - HEIGHT);
		weight = (m->current_dist - m->dist_player) / (m->dist_wall - m->dist_player);
		current_floor.x = weight * floor_wall.x + (1.0 - weight) * m->pos.x;
		current_floor.y = weight * floor_wall.y + (1.0 - weight) * m->pos.y;
		floorTexX = (int)(current_floor.x * m->w_t[10]->w) % m->w_t[10]->w;
		floorTexY = (int)(current_floor.y * m->w_t[10]->h) % m->w_t[10]->h;
		ceilTexX = (int)(current_floor.x * m->w_t[10]->w / 4) % m->w_t[10]->w;
		ceilTexY = (int)(current_floor.y * m->w_t[10]->h / 4) % m->w_t[10]->h;
		//floor
		*m->bufp = ((unsigned int *)m->w_t[10]->pixels)[m->w_t[10]->w * floorTexY + floorTexX];
		//ceiling (symmetrical!)
		*(m->bufp + (HEIGHT - 2 * y) * WIDTH) = ((unsigned int *)m->w_t[10]->pixels)[m->w_t[10]->w * ceilTexY + ceilTexX];
		m->bufp += WIDTH;
		y++;
	}
}

void	draw_cursor(t_map *m)
{
	int z;

	z = -5;
	while (++z < 5)
	{
		m->image[HEIGHT * WIDTH / 2 + WIDTH / 2 + z] = 0xFFFFFF;
		m->image[HEIGHT * WIDTH / 2 + (z * WIDTH + WIDTH / 2)] = 0xFFFFFF;
			// tipa proverka
		// if (m->image[HEIGHT * WIDTH / 2 + WIDTH / 2 + z] == 0xFFFFFF)
		// 	m->image[HEIGHT * WIDTH / 2 + WIDTH / 2 + z] = 0x000000;
		// else
		// 	m->image[HEIGHT * WIDTH / 2 + WIDTH / 2 + z] = 0xFFFFFF;
		// if (m->image[HEIGHT * WIDTH / 2 + (z * WIDTH + WIDTH / 2)] == 0xFFFFFF)
		// 	m->image[HEIGHT * WIDTH / 2 + (z * WIDTH + WIDTH / 2)] = 0x000000;
		// else
		// 	m->image[HEIGHT * WIDTH / 2 + (z * WIDTH + WIDTH / 2)] = 0xFFFFFF;
	}
}
