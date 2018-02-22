/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:49:55 by omiroshn          #+#    #+#             */
/*   Updated: 2018/02/07 18:49:57 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <time.h> 
# include "libft.h"
# include <SDL2/SDL.h>
# include "SDL_ttf.h"
# include "SDL_image.h"

# define mapWidth 24
# define mapHeight 24
# define WIDTH 1280
# define HEIGHT 1024
# define THREADS 8

typedef unsigned int	t_uint;

typedef struct	s_font
{
	char		*name;
	int			size;
	t_uint		color;
	TTF_Font	*ttf;
}				t_font;

typedef	struct	s_fps
{
	double	time;
	double	old_time;
	double	frame_time;
}				t_fps;

typedef	struct	s_vec
{
	float	x;
	float	y;
	float	a;
}				t_vec;

typedef	struct	s_ivec
{
	int		x;
	int		y;
	int		a;
}				t_ivec;

typedef	struct	s_map
{
	SDL_Surface *screen;
	
	int			pixels;

	int			cunt;
	int			end;
	double		wall_dist;
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;
	t_fps		fps;
	t_vec		ray_dir;
	SDL_Surface	*w_t[16];
}				t_map;

typedef struct	s_thread
{
	SDL_Surface *screen;
	t_map		map;
	int			start;
	int			end;
}				t_thread;

void	draw(t_thread *t);
void	threads_create(SDL_Surface *screen, t_map map);
// int		vert_line(t_map *map, int x, int draw_start, int draw_end, int color, int texture, int side);

#endif