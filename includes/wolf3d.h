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

typedef	struct	s_vec
{
	double	x;
	double	y;
}				t_vec;

typedef	struct	s_ivec
{
	int		x;
	int		y;
}				t_ivec;

typedef	struct	s_map
{
	SDL_Surface	*screen;
	SDL_Window	*window;
	SDL_Surface	*w_t[16];

	int			pixels;
	int			cunt;
	int			end;
	double		wall_dist;
	int			*image;
	unsigned int *bufp;
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;
	t_vec		ray_dir;
	double		dist_wall;
	double		dist_player;
	double		current_dist;
	int			draw_start;
	int			draw_end;
	int			side;
	t_ivec		map;
	t_ivec		step;
	t_vec		side_dist;
	t_vec		delta_dist;
	t_vec		camera;
	double		wall;
	t_ivec		tex;
}				t_map;

typedef struct	s_thread
{
	t_map		map;
	int			start;
	int			end;
}				t_thread;

void	draw(t_thread *t);
void	threads_create(SDL_Surface *screen, t_map map);
int		key_function(t_map *map);
void	draw_camera(t_map *m, int x);
void	perform_dda(t_map *m);
void	draw_wall(t_map *m, int x);
void	draw_floor(t_map *m);
void	draw_cursor(t_map *m);

#endif