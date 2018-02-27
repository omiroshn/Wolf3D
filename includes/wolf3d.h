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

# define WIDTH 1280
# define HEIGHT 1024
# define THREADS 8
# define TEXTURENUM 16
# define TRUE 1

# define IS_WALL(n)(n & 0xFFFFL)
# define TOP_WALL(n)((n & 0xFL) - 1)
# define BOT_WALL(n)(((n & 0xF0L) >> 4) - 1)
# define RIGHT_WALL(n)(((n & 0xF00L) >> 8) - 1)
# define LEFT_WALL(n)(((n & 0xF000L) >> 12) - 1)
# define FLOOR(n)(((n & 0xF00000L) >> 20))
# define CEIL(n)(((n & 0xF0000L) >> 16))
# define SPRITE(n)((n & 0xF000000L) >> 24)
# define IS_SPRITE(n)((n & 0xF0000000L) >> 28)

# define MAPS_FOLDER "resources/maps/"
# define W_TEX_FOLDER "resources/images/wolf/"
# define M_TEX_FOLDER "resources/images/minecraft/"

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
	t_uint		**data;
}				t_karta;

typedef	struct	s_map
{
	SDL_Surface	*screen;
	SDL_Window	*window;
	SDL_Surface	*w_t[TEXTURENUM];
	SDL_Surface	*st_t[TEXTURENUM];
	SDL_Surface *sprite_tex;
	SDL_Surface	*weapon;
	t_uint		*image;
	t_uint		*bufp;
	t_karta		karta;
	char		*name;
	int			w;
	int			h;
	int			pixels;
	int			cunt;
	int			end;
	int			move;
	int			rotate;
	int			draw_start;
	int			draw_end;
	int			s_tex;
	int			side;
	int			texture;
	int			line_height;
	double		wall_dist;
	double		mov_speed;
	double		rot_speed;
	double		wall;
	double		dist_wall;
	double		current_dist;
	int			sprite_h;
	int			sprite_w;
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
	t_map		map;
	int			start;
	int			end;
}				t_wolf;

/*
**		draw.c
*/

void	draw(t_wolf *w);
void	threads_create(SDL_Surface *screen, t_map map);
int		key_function(t_map *map);
void	draw_camera(t_map *m, int x);
void	perform_dda(t_map *m, int x);
void	draw_wall(t_map *m, int x, t_uint **data);
void	draw_floor(t_map *m, t_uint **data);
void	draw_cursor(t_map *m);
void	draw_weapon(t_map *m);
void	put_error(const char *msg);

/*
**		event.c
*/

int		key_function(t_map *map);
void	key_up(SDL_Event e, SDL_Scancode key, t_map *map);
void	key_down(SDL_Scancode key, t_map *map);
void	scan_ws(t_map *map, double alpha);
void	scan_ad(t_map *map, double alpha);



#endif