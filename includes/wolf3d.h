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
# include <errno.h>
# include <fcntl.h>
# include "SDL_ttf.h"
# include "SDL_image.h"

# define mapWidth 24
# define mapHeight 24
# define WIDTH 1280
# define HEIGHT 1024
# define THREADS 8
# define TEXTURENUM 11

typedef unsigned int t_uint;

typedef struct	s_font
{
	char		*name;
	int			size;
	t_uint		color;
	TTF_Font	*ttf;
}				t_font;

typedef	struct	s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef	struct	s_ivec
{
	int			x;
	int			y;
}				t_ivec;

typedef	struct	s_karta
{
	int			rows;
	int			cols;
	int			**data;
}				t_karta;

typedef	struct	s_map
{
	SDL_Surface	*screen;
	SDL_Window	*window;
	SDL_Surface	*w_t[TEXTURENUM];
	t_uint		*image;
	t_uint		*bufp;
	t_karta		karta;
	int			pixels;
	int			cunt;
	int			end;
	int			move;
	int			rotate;
	int			draw_start;
	int			draw_end;
	int			side;
	double		wall_dist;
	double		mov_speed;
	double		rot_speed;
	double		wall;
	double		dist_wall;
	double		dist_player;
	double		current_dist;
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;
	t_vec		ray_dir;
	t_vec		side_dist;
	t_vec		delta_dist;
	t_vec		camera;
	t_ivec		tex;
	t_ivec		map;
	t_ivec		step;
	t_ivec		floor_tex;
	t_ivec		ceil_tex;
}				t_map;

typedef struct	s_wolf
{
	int			start;
	int			end;
	t_map		map;
}				t_wolf;

/*
**		draw.c
*/

void	draw(t_wolf *w);
void	threads_create(SDL_Surface *screen, t_map map);
int		key_function(t_map *map);
void	draw_camera(t_map *m, int x);
void	perform_dda(t_map *m);
void	draw_wall(t_map *m, int x);
void	draw_floor(t_map *m);
void	draw_cursor(t_map *m);

/*
**		event.c
*/

int		key_function(t_map *map);
void	key_up(SDL_Scancode key, t_map *map);
void	key_down(SDL_Scancode key, t_map *map);
void	scan_ws(t_map *map, double alpha);
void	scan_ad(t_map *map, double alpha);



#endif