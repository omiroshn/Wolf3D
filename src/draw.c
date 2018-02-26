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

void	draw_camera(t_map *m, int x)
{
	m->camera.x = 2 * x / (double)(m->w) - 1;
	m->ray_dir.x = m->dir.x + m->plane.x * m->camera.x;
	m->ray_dir.y = m->dir.y + m->plane.y * m->camera.x;
	m->map.x = (int)(m->pos.x);
	m->map.y = (int)(m->pos.y);
	m->delta_dist.x = fabs(1 / m->ray_dir.x);
	m->delta_dist.y = fabs(1 / m->ray_dir.y);
	m->step.x = -1;
	m->side_dist.x = (m->pos.x - m->map.x) * m->delta_dist.x;
	if (m->ray_dir.x >= 0)
	{
		m->step.x = 1;
		m->side_dist.x = (m->map.x + 1.0 - m->pos.x) * m->delta_dist.x;
	}
	m->step.y = -1;
	m->side_dist.y = (m->pos.y - m->map.y) * m->delta_dist.y;
	if (m->ray_dir.y >= 0)
	{
		m->step.y = 1;
		m->side_dist.y = (m->map.y + 1.0 - m->pos.y) * m->delta_dist.y;
	}
}

void	sgl_plot(t_vec p, t_uint color, SDL_Surface *surface)
{
	int		dx;
	int		dy;
	t_uint	*pixels;

	pixels = (t_uint *)surface->pixels;
	dx = round(p.x);
	dy = round(p.y);
	if (dx >= 0 && dx < surface->w && dy >= 0 && dy < surface->h)
		if (!pixels[dy * surface->w + dx])
			pixels[dy * surface->w + dx] = color;
}


inline t_uint	sgl_get(SDL_Surface *surface, int x, int y)
{
	t_uint	pixel;
	int		width;
	int		height;

	width = surface->w;
	height = surface->h;
	if (y >= 0 && y < height && x >= 0 && x < width)
		pixel = *((t_uint *)surface->pixels + y * width + x);
	else
		pixel = 0x000000;
	return (pixel);
}


void	sgl_blit_line(SDL_Surface *sur[2], SDL_Rect src_r,
						SDL_Rect dst_r)
{
	int		y;
	int		limit;
	int		surface_y;
	long	pixel;

	y = dst_r.y - 1;
	limit = dst_r.y + dst_r.h;
	limit >= sur[1]->h ? limit = sur[1]->h : 0;
	y < 0 ? y = 0 : 0;
	while (++y < limit)
	{
		surface_y = (y - dst_r.y) * ((double)sur[0]->h / dst_r.h);
		pixel = sgl_get(sur[0], src_r.x, surface_y);
		// mask ? pixel &= mask : 0;
		sgl_plot((t_vec){dst_r.x, y}, pixel, sur[1]);
	}
}


void		draw_sprite(t_map *m, int x)
{
	t_vec	sprite;
	t_vec	transf;
	double	inverse;
	int		s_width;
	int		t_d[2];

	sprite.x = m->map.x + 0.5 - m->pos.x;
	sprite.y = m->map.y + 0.5 - m->pos.y;
	inverse = 1.0 / (m->plane.x * m->dir.y - m->dir.x * m->plane.y);
	transf.x = inverse * (m->dir.y * sprite.x - m->dir.x * sprite.y);
	transf.y = inverse * (-m->plane.y * sprite.x + m->plane.x * sprite.y);
	s_width = abs((int)(m->screen->h / transf.y));
	t_d[0] = SPRITE(m->karta.data[m->map.x][m->map.y]) - 1;
	// printf("%i \n", t_d[0]);
	t_d[1] = (int)(256 * (x - (-s_width / 2 + (m->screen->w / 2) * (1 + transf.x / transf.y))) * m->st_t[t_d[0]]->w / s_width) / 256;
	*m->bufp = ((t_uint *)m->st_t[t_d[0]]->pixels)[m->st_t[t_d[0]]->w * m->floor_tex.y + m->floor_tex.x];
		m->bufp += m->w;
	// sgl_blit_line((SDL_Surface *[2]){m->st_t[t_d[0]], m->screen},
	// 	(SDL_Rect){d, 0, 0, 0},
	// 	(SDL_Rect){x, -s_width / 2 + m->screen->h / 2, 0, s_width});

	// t_d[1] = (int)(256 * (map[2] - (-s_width / 2 + (gd->screen->w / 2) *
	// 		(1 + transf.x / transf.y))) * gd->st_t[t_d[0]]->w / s_width) / 256;
	// sgl_blit_line((SDL_Surface *[2]){gd->st_t[t_d[0]], gd->screen},
	// 	(SDL_Rect){t_d[1], 0, 0, 0},
	// 	(SDL_Rect){map[2], -s_width / 2 + gd->screen->h / 2, 0, s_width}
	// 	, 0xFFFFFF);
}

void	perform_dda(t_map *m, int x)
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
		if (IS_WALL(m->karta.data[m->map.x][m->map.y]))
			break ;
		if (SPRITE(m->karta.data[m->map.x][m->map.y]))
			draw_sprite(m, x);
	}
}

void	draw_screen_wall(t_map *m, int texture, int line_height, int x)
{
	int y;
	int	d;

	y = m->draw_start - 1;
	m->bufp = (t_uint *)m->screen->pixels + m->draw_start * m->w + x;
	while (++y <= m->draw_end)
	{
		d = y * 2 - m->h + line_height;
		m->tex.y = ((d * m->w_t[texture]->w / line_height) / 2);
		if (m->tex.x >= 0 && m->tex.x < m->w_t[texture]->h &&
			m->tex.y >= 0 && m->tex.y < m->w_t[texture]->w)
			*m->bufp = ((t_uint *)m->w_t[texture]->pixels)
						[m->w_t[texture]->h * m->tex.y + m->tex.x];
		m->bufp += m->w;
	}
}

// void	ft_swap(int f, int ff)
// {
// 	int t;

// 	t = f;
// 	f = ff;
// 	ff = t;
// }

// void	comb_sort(int *order, double *dist, int amount)
// {
// 	int i;
// 	int j;
// 	int gap;
// 	int swapped;

// 	gap = amount;
// 	swapped = 0;
// 	while (gap > 1 || swapped)
// 	{
// 		gap = (gap * 10) / 13;
// 		if (gap == 9 || gap == 10)
// 			gap = 11;
// 		gap = gap < 1 ? 1 : gap;
// 		swapped = 0;
// 		i = -1;
// 		while (++i < amount - gap)
// 		{
// 			j = i + gap;
// 			if (dist[i] < dist[j])
// 			{
// 				ft_swap(dist[i], dist[j]);
// 				ft_swap(order[i], order[j]);
// 				swapped = 1;
// 			}
// 		}
// 	}
// }

// void	draw_sprite(t_map *m, int x, t_uint **data)
// {
// 	t_vec sprite[numSprites] =
// 	{
// 	  {20.5, 11.5},
// 	  {18.5, 4.5},
// 	  {10.0, 4.5},
// 	  {10.0, 12.5},
// 	  {3.5, 6.5},
// 	  {3.5, 20.5},
// 	  {3.5, 14.5},
// 	  {14.5, 20.5},
// 	  {18.5, 10.5},
// 	  {18.5, 11.5},
// 	  {18.5, 12.5},
// 	  {21.5, 1.5},
// 	  {15.5, 1.5},
// 	  {16.0, 1.8},
// 	  {16.2, 1.2},
// 	  {3.5,  2.5},
// 	  {9.5, 15.5},
// 	  {10.0, 15.1},
// 	  {10.5, 15.8},
// 	};
// 	double ZBuffer[m->screen->w];
// 	int spriteOrder[numSprites];
// 	double spriteDistance[numSprites];
// 	int i;

// 	ZBuffer[x] = m->wall_dist;
// 	i = -1;
// 	while (++i < numSprites)
// 	{
// 		spriteOrder[i] = i;
// 		spriteDistance[i] = ((m->pos.x - sprite[i].x) * (m->pos.x - sprite[i].x)
// 							+ (m->pos.y - sprite[i].y) * (m->pos.y - sprite[i].y));
// 	}
// 	comb_sort(spriteOrder, spriteDistance, numSprites);
// 	i = -1;
// 	while (++i < numSprites)
//     {
// 		//translate sprite position to relative to camera
// 		double spriteX = sprite[spriteOrder[i]].x - m->pos.x;
// 		double spriteY = sprite[spriteOrder[i]].y - m->pos.y;

// 		//transform sprite with the inverse camera matrix
// 		double invDet = 1.0 / (m->plane.x * m->dir.y - m->dir.x * m->plane.y); //required for correct matrix multiplication

// 		double transformX = invDet * (m->dir.y * spriteX - m->dir.x * spriteY);
// 		double transformY = invDet * (-m->plane.y * spriteX + m->plane.x * spriteY);
// 		//this is actually the depth inside the screen, that what Z is in 3D
// 		int spriteScreenX = int((m->screen->w / 2) * (1 + transformX / transformY));//calculate height of the sprite on screen
// 		int spriteHeight = abs(int(m->screen->h / (transformY))); //using "transformY" instead of the real distance prevents fisheye
// 		//calculate lowest and highest pixel to fill in current stripe
// 		int drawStartY = -spriteHeight / 2 + m->screen->h / 2;
// 		if (drawStartY < 0) drawStartY = 0;
// 		int drawEndY = spriteHeight / 2 + m->screen->h / 2;
// 		if (drawEndY >= m->screen->h) drawEndY = m->screen->h - 1;

// 		//calculate width of the sprite
// 		int spriteWidth = abs( int (m->screen->h / (transformY)));
// 		int drawStartX = -spriteWidth / 2 + spriteScreenX;
// 		if (drawStartX < 0) drawStartX = 0;
// 		int drawEndX = spriteWidth / 2 + spriteScreenX;
// 		if (drawEndX >= m->screen->w) drawEndX = m->screen->w - 1;

// 		//loop through every vertical stripe of the sprite on screen
// 		int stripe = drawStartX - 1;
// 		while (++stripe < drawEndX)
// 		{
// 			m->tex.x = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * m->w_t[]->w / spriteWidth) / 256;
// 			//the conditions in the if are:
// 			//1) it's in front of camera plane so you don't see things behind you
// 			//2) it's on the screen (left)
// 			//3) it's on the screen (right)
// 			//4) ZBuffer, with perpendicular distance
// 			if (transformY > 0 && stripe > 0 && stripe < m->screen->w && transformY < ZBuffer[stripe])
// 			int y = drawStartY;
// 			while (++y < drawEndY) //for every pixel of the current stripe
// 			{
// 				int d = (y) * 256 - m->screen->h + spriteHeight;
// 				m->tex.y = ((d * m->w_t[texture]->w) / spriteHeight) / 2;
// 				Uint32 color = texture[sprite[spriteOrder[i]].texture][m->w_t[]->w * m->tex.y + m->tex.x];
// 				//get current color from the texture
// 				if ((color & 0x00FFFFFF) != 0)
// 					buffer[y][stripe] = color;
// 				//paint pixel if it isn't black, black is the invisible color
// 			}
// 			while (++y <= m->draw_end)
// 			{
// 				d = y * 2 - m->h + line_height;
// 				m->tex.y = ((d * m->w_t[texture]->w / line_height) / 2);
// 				if (m->tex.x >= 0 && m->tex.x < m->w_t[texture]->h &&
// 					m->tex.y >= 0 && m->tex.y < m->w_t[texture]->w)
// 					*m->bufp = ((t_uint *)m->w_t[texture]->pixels)
// 								[m->w_t[texture]->h * m->tex.y + m->tex.x];
// 				m->bufp += m->w;
// 			}
// 		}
// 	}
// }

void	draw_wall(t_map *m, int x, t_uint **data)
{
	m->wall_dist = m->side == 0 ?
	(m->map.x - m->pos.x + (1 - m->step.x) / 2) / m->ray_dir.x :
	(m->map.y - m->pos.y + (1 - m->step.y) / 2) / m->ray_dir.y;
	m->line_height = (int)(m->h / m->wall_dist);
	m->draw_start = -m->line_height / 2 + m->h / 2;
	m->draw_end = m->line_height / 2 + m->h / 2;
	m->draw_start < 0 ? m->draw_start = 0 : m->draw_start;
	m->draw_end >= m->h ? m->draw_end = m->h - 1 : m->draw_end;
	m->draw_end < 0 ? m->draw_end = m->h : m->draw_end;
	m->wall = m->side == 0 ? m->pos.y + m->wall_dist * m->ray_dir.y :
	m->pos.x + m->wall_dist * m->ray_dir.x;
	m->wall -= floor((m->wall));
	if (m->side)
		m->texture = m->ray_dir.y > 0 ? BOT_WALL(data[m->map.x][m->map.y])
									: TOP_WALL(data[m->map.x][m->map.y]);
	else
		m->texture = m->ray_dir.x > 0 ? RIGHT_WALL(data[m->map.x][m->map.y])
									: LEFT_WALL(data[m->map.x][m->map.y]);
	m->tex.x = (int)(m->wall * (double)(m->w_t[m->texture]->w));
	if (m->side == 0 && m->ray_dir.x > 0)
		m->tex.x = m->w_t[m->texture]->w - m->tex.x - 1;
	if (m->side == 1 && m->ray_dir.y < 0)
		m->tex.x = m->w_t[m->texture]->w - m->tex.x - 1;
	draw_screen_wall(m, m->texture, m->line_height, x);
}

void	floor_wall_dist(t_map *m, t_vec *floor_wall)
{
	if (m->side == 0 && m->ray_dir.x > 0)
	{
		floor_wall->x = m->map.x;
		floor_wall->y = m->map.y + m->wall;
	}
	else if (m->side == 0 && m->ray_dir.x < 0)
	{
		floor_wall->x = m->map.x + 1.0;
		floor_wall->y = m->map.y + m->wall;
	}
	else if (m->side == 1 && m->ray_dir.y > 0)
	{
		floor_wall->x = m->map.x + m->wall;
		floor_wall->y = m->map.y;
	}
	else
	{
		floor_wall->x = m->map.x + m->wall;
		floor_wall->y = m->map.y + 1.0;
	}
}

t_vec	current_floor(t_map *m, t_vec *cur_floor, t_vec *floor_wall, int y)
{
	double	weight;

	weight = m->h / (2.0 * y - m->h) / m->dist_wall;
	cur_floor->x = weight * floor_wall->x + (1.0 - weight) * m->pos.x;
	cur_floor->y = weight * floor_wall->y + (1.0 - weight) * m->pos.y;
	return (*cur_floor);
}

void	env_textures(t_map *m, t_vec *c_f, t_uint **data)
{
	m->floor_tex.x = (int)(c_f->x * m->w_t[FLOOR(data[(int)c_f->x]
		[(int)c_f->y])]->w) % m->w_t[FLOOR(data[(int)c_f->x][(int)c_f->y])]->w;
	m->floor_tex.y = (int)(c_f->y * m->w_t[FLOOR(data[(int)c_f->x]
		[(int)c_f->y])]->h) % m->w_t[FLOOR(data[(int)c_f->x][(int)c_f->y])]->h;
	m->ceil_tex.x = (int)(c_f->x * m->w_t[CEIL(data[(int)c_f->x]
		[(int)c_f->y])]->w) % m->w_t[CEIL(data[(int)c_f->x][(int)c_f->y])]->w;
	m->ceil_tex.y = (int)(c_f->y * m->w_t[CEIL(data[(int)c_f->x]
		[(int)c_f->y])]->h) % m->w_t[CEIL(data[(int)c_f->x][(int)c_f->y])]->h;
}

void	draw_floor(t_map *m, t_uint **data)
{
	t_vec	floor_wall;
	t_vec	c_f;
	int		y;

	floor_wall_dist(m, &floor_wall);
	m->dist_wall = m->wall_dist;
	y = m->draw_end;
	while (++y < m->h)
	{
		c_f = current_floor(m, &c_f, &floor_wall, y);
		env_textures(m, &c_f, data);
		*(m->bufp - m->w) = ((t_uint *)m->w_t[FLOOR(data[(int)c_f.x]
			[(int)c_f.y])]->pixels)[m->w_t[FLOOR(data[(int)c_f.x]
				[(int)c_f.y])]->w * m->floor_tex.y + m->floor_tex.x];
		*(m->bufp + (m->h - 2 * y) * m->w) = ((t_uint *)m->w_t[CEIL(data
			[(int)c_f.x][(int)c_f.y])]->pixels)[m->w_t[CEIL(data[(int)c_f.x]
			[(int)c_f.y])]->w * m->ceil_tex.y + m->ceil_tex.x];
		m->bufp += m->w;
	}
}

void	draw_cursor(t_map *m)
{
	int z;

	z = -5;
	while (++z < 5)
	{
		m->image[m->h * m->w / 2 + m->w / 2 + z] = 0xFFFFFF;
		m->image[m->h * m->w / 2 + (z * m->w + m->w / 2)] = 0xFFFFFF;
	}
}

void	draw_weapon(t_map *m)
{
	if (!ft_strcmp(m->name, MAPS_FOLDER"map2.map"))
	{
		SDL_BlitScaled(m->weapon, NULL, m->screen,
			&(SDL_Rect){m->screen->w + 150 - m->weapon->w,
				m->screen->h + 150 - m->weapon->h,
				m->weapon->w, m->weapon->h});
	}
	else
	{
		SDL_BlitScaled(m->weapon, NULL, m->screen,
			&(SDL_Rect){m->screen->w + 150 - m->weapon->w,
				m->screen->h + 150 - m->weapon->h,
				m->weapon->w * 3 / 4, m->weapon->h * 3 / 4});
	}
}
