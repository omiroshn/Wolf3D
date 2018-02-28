/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:44:56 by omiroshn          #+#    #+#             */
/*   Updated: 2018/02/28 21:44:57 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

inline static int	number_action(char **numbers, char *line, int mode)
{
	int		i;

	if (!numbers)
		return (0);
	if (mode == 0 && !(i = 0))
		while (numbers[i])
			i++;
	else if (mode == 1 && (i = -1))
	{
		while (numbers[++i])
			free(numbers[i]);
		free(numbers);
		free(line);
	}
	return (mode ? 0 : i);
}

void				read_map(t_map *m, char *filename)
{
	int		fd;
	char	*lol;
	char	**numbers;

	m->name = filename;
	if ((fd = open(filename, O_RDONLY)) < 0 || read(fd, NULL, 0) < 0)
		put_error("opening file.");
	get_next_line(fd, &lol);
	if (number_action((numbers = ft_strsplit(lol, ' ')), lol, 0) != 2)
		put_error("map invalid.");
	m->karta.rows = ft_atoi(numbers[0]);
	m->karta.cols = ft_atoi(numbers[1]);
	get_next_line(fd, &lol);
	if (number_action((numbers = ft_strsplit(lol, ' ')), lol, 0) != 2)
		put_error("map invalid.");
	m->pos.x = ft_atoi(numbers[0]) - 0.5;
	m->pos.y = ft_atoi(numbers[1]) - 0.5;
	number_action(numbers, 0, 1);
	if (m->pos.x <= 1 || m->pos.x > m->karta.rows - 1
		|| m->pos.y <= 1 || m->pos.y > m->karta.cols - 1)
		put_error("invalid player position.");
	alloc_map(m, fd, lol, numbers);
	check_textures(m, m->karta.data);
	check_sprites(m, m->karta.data);
}

void				alloc_map(t_map *m, int fd, char *lol, char **numbers)
{
	int		i;
	int		j;

	m->karta.data = ft_memalloc(sizeof(int *) * m->karta.rows);
	i = -1;
	while (++i < m->karta.cols)
		m->karta.data[i] = ft_memalloc(sizeof(int) * m->karta.cols);
	i = -1;
	while (get_next_line(fd, &lol) > 0 && ++i < m->karta.rows && (j = -1))
	{
		if (number_action((numbers = ft_strsplit(lol, ' ')), 0, 0) != m->karta.cols)
			put_error("opening file.");
		numbers = ft_strsplit(lol, ' ');
		while (++j < m->karta.cols)
			ft_atoi_base(numbers[j], 16) >= 0
					? m->karta.data[i][j] = ft_atoi_base(numbers[j], 16)
					: put_error("map invalid.");
		number_action(numbers, lol, 1);
	}
	close(fd);
	if (IS_WALL(m->karta.data[(int)m->pos.x][(int)m->pos.y]))
		put_error("invalid player position.");
}

void				check_sprites(t_map *m, t_uint **data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < m->karta.rows && (j = -1))
		while (++j < m->karta.cols)
			if (!ft_strcmp(m->name, MAPS_FOLDER"map1.map"))
			{
				if (SPRITE(data[i][j]))
					(SPRITE(data[i][j]) <= 9 || SPRITE(data[i][j]) >= 13) ?
						put_error("it's not a sprite, it's a texture!") : 0;
			}
			else if (!ft_strcmp(m->name, MAPS_FOLDER"map2.map"))
			{
				if (SPRITE(data[i][j]))
					(SPRITE(data[i][j]) <= 11) ?
						put_error("it's not a sprite, it's a texture!") : 0;
			}
}

void				check_textures(t_map *m, t_uint **data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < m->karta.rows && (j = -1))
		while (++j < m->karta.cols)
			if (IS_WALL(data[i][j]) || i == 0 || j == 0
				|| i == m->karta.rows - 1 || j == m->karta.cols - 1)
			{
				!(data[i][j] & 0xFL) ? data[i][j] |= 0x4L : 0;
				!(data[i][j] & 0xF0L) ? data[i][j] |= 0x40L : 0;
				!(data[i][j] & 0xF00L) ? data[i][j] |= 0x400L : 0;
				!(data[i][j] & 0xF000L) ? data[i][j] |= 0x4000L : 0;
			}
			else
			{
				!(data[i][j] & 0xF0000L) ? data[i][j] |= 0x30000L : 0;
				!(data[i][j] & 0xF00000L) ? data[i][j] |= 0x300000L : 0;
			}
}
