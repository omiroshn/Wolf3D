/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:40:42 by omiroshn          #+#    #+#             */
/*   Updated: 2018/02/28 21:40:45 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface	*img_load(char *path)
{
	SDL_Surface	*ret;
	SDL_Surface	*tmp;
	SDL_RWops	*rwops;

	if (!(rwops = SDL_RWFromFile(path, "r")))
		return (NULL);
	if (!(tmp = IMG_Load_RW(rwops, 1)))
		return (NULL);
	ret = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(tmp);
	return (ret);
}

void	load_textures_minecraft(t_map *m)
{
	if (!(m->w_t[0] = IMG_Load(M_TEX_FOLDER"dirt.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[1] = IMG_Load(M_TEX_FOLDER"sand.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[2] = IMG_Load(M_TEX_FOLDER"cobblestone_mossy.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[3] = IMG_Load(M_TEX_FOLDER"stone.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[4] = IMG_Load(M_TEX_FOLDER"coal_ore.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[5] = IMG_Load(M_TEX_FOLDER"diamond_ore.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[6] = IMG_Load(M_TEX_FOLDER"brick.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[7] = IMG_Load(M_TEX_FOLDER"bookshelf.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[8] = IMG_Load(M_TEX_FOLDER"crafting_table_front.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[9] = IMG_Load(M_TEX_FOLDER"obsidian.png")))
		put_error(IMG_GetError());
}

void	load_textures_minecraft2(t_map *m)
{
	if (!(m->w_t[10] = IMG_Load(M_TEX_FOLDER"farmland_wet.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[11] = IMG_Load(M_TEX_FOLDER"sandstone_normal.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[12] = IMG_Load(M_TEX_FOLDER"carrot.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[13] = IMG_Load(M_TEX_FOLDER"wheat.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[14] = IMG_Load(M_TEX_FOLDER"torch.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[15] = IMG_Load(M_TEX_FOLDER"cookie.png")))
		put_error(IMG_GetError());
}

void	load_textures_wolf(t_map *m)
{
	if (!(m->w_t[0] = IMG_Load(W_TEX_FOLDER"eagle.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[1] = IMG_Load(W_TEX_FOLDER"redbrick.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[2] = IMG_Load(W_TEX_FOLDER"purplestone.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[3] = IMG_Load(W_TEX_FOLDER"greystone.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[4] = IMG_Load(W_TEX_FOLDER"colorstone.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[5] = IMG_Load(W_TEX_FOLDER"mossy.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[6] = IMG_Load(W_TEX_FOLDER"wood.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[7] = IMG_Load(W_TEX_FOLDER"hitler.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[8] = IMG_Load(W_TEX_FOLDER"torch.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[9] = IMG_Load(W_TEX_FOLDER"sand.jpg")))
		put_error(IMG_GetError());
}

void	load_textures_anime(t_map *m)
{
	if (!(m->w_t[10] = IMG_Load(W_TEX_FOLDER"barrel.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[11] = IMG_Load(W_TEX_FOLDER"pillar.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[12] = IMG_Load(W_TEX_FOLDER"greenlight.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[13] = IMG_Load(W_TEX_FOLDER"pain.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[14] = IMG_Load(W_TEX_FOLDER"kakashi.png")))
		put_error(IMG_GetError());
	if (!(m->w_t[15] = IMG_Load(W_TEX_FOLDER"narutoramen.jpg")))
		put_error(IMG_GetError());
}

void	convert_format(t_map *m)
{
	int i;

	i = -1;
	while (++i < TEXTURENUM)
		m->w_t[i] = SDL_ConvertSurfaceFormat
				(m->w_t[i], SDL_PIXELFORMAT_ARGB8888, 0);
}

void	define_textures(t_map *m)
{
	if (!ft_strcmp(m->name, MAPS_FOLDER"map2.map"))
	{
		load_textures_minecraft(m);
		load_textures_minecraft2(m);
		convert_format(m);
		if (!(m->weapon = IMG_Load(HUD_FOLDER"pickaxe.png")))
			put_error(IMG_GetError());
		if (!(m->sprite_tex = IMG_Load(W_TEX_FOLDER"barrel.png")))
			put_error(IMG_GetError());
	}
	else
	{
		load_textures_wolf(m);
		load_textures_anime(m);
		convert_format(m);
		if (!(m->weapon = IMG_Load(HUD_FOLDER"weapon.png")))
			put_error(IMG_GetError());
		if (!(m->gunfire = IMG_Load(HUD_FOLDER"fire.png")))
			put_error(IMG_GetError());
		if (!(m->sprite_tex = IMG_Load(W_TEX_FOLDER"barrel.png")))
			put_error(IMG_GetError());
	}
}
