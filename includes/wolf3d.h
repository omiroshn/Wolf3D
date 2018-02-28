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

# include <time.h>
# include <fcntl.h>
# include <SDL2/SDL.h>
# include "libft.h"
# include "SDL_ttf.h"
# include "SDL_image.h"
# include "SDL_mixer.h"

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
# define EREASE_SPRITE(n)(n &= 0xFFFFFFFF00FFFFFFL)

# define MAPS_FOLDER "resources/maps/"
# define HUD_FOLDER "resources/images/hud/"
# define W_TEX_FOLDER "resources/images/wolf/"
# define M_TEX_FOLDER "resources/images/minecraft/"
# define MUSIC_FOLDER "resources/sounds/"

typedef unsigned int	t_uint;

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
	SDL_Surface	*gunfire;
	Mix_Music	*game_sound;
	Mix_Chunk	*shoot_sound;
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
	int			sprite_h;
	int			sprite_w;
	double		wall_dist;
	double		mov_speed;
	double		rot_speed;
	double		wall;
	double		dist_wall;
	double		current_dist;
	t_uint		*image;
	t_uint		*bufp;
	t_uint		shoot;
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
**				load_textures.c
*/

void			load_textures_minecraft(t_map *m);
void			load_textures_minecraft2(t_map *m);
void			load_textures_wolf(t_map *m);
void			load_textures_anime(t_map *m);
void			define_textures(t_map *m);

/*
**				draw.c
*/

void			draw_camera(t_map *m, int x);
void			perform_dda(t_map *m, int x);
void			draw_cursor(t_map *m);
void			draw_weapon(t_map *m);

/*
**				draw_wall.c
*/

void			draw_wall(t_map *m, int x, t_uint **data);
void			draw_screen_wall(t_map *m, int texture, int line_height, int x);

/*
**				draw_floor.c
*/

void			draw_floor(t_map *m, t_uint **data);
void			floor_wall_dist(t_map *m, t_vec *floor_wall);
void			env_textures(t_map *m, t_vec *c_f, t_uint **data);
t_vec			current_floor(t_map *m, t_vec *cur_floor,
										t_vec *floor_wall, int y);

/*
**				draw_sprite.c
*/

void			draw_sprite(t_map *m, t_uint **data, int x);
void			sprite_line(t_map *m, t_vec transf, t_ivec draw_se, int x);

/*
**				event.c
*/

int				key_function(t_map *map);
void			delete_sprite(t_uint *cell, t_uint type);

/*
**				draw.c
*/

void			put_error(const char *msg);
void			put_usage(void);
int				quit(t_map *m);

/*
**				read_map.c
*/

void			read_map(t_map *m, char *filename);
void			check_sprites(t_map *m, t_uint **data);
void			check_textures(t_map *m, t_uint **data);
void			alloc_map(t_map *m, int fd, char *lol, char **numbers);

/*
**				system.c
*/

void			draw(t_wolf *w);
void			threads_create(SDL_Surface *screen, t_map map);
void			lsync(void);
void			display_fps(void);

/*
**				keys.c
*/

void			scan_ws(t_map *m, double d);
void			scan_ad(t_map *map, double alpha);
void			key_down(SDL_Scancode key, t_map *m);
void			key_up(SDL_Scancode key, t_map *m);

#endif
