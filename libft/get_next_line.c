/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 21:10:01 by omiroshn          #+#    #+#             */
/*   Updated: 2017/11/26 17:55:42 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strramen(char **line, t_kek *arrfd, char *end)
{
	char	*temp;
	char	*temp2;

	if (end)
	{
		temp = ft_strsub(arrfd->content, 0, end - arrfd->content);
		arrfd->size -= (end - arrfd->content) + 1;
		ft_memmove(arrfd->content, end + 1, arrfd->size + 1);
	}
	else
	{
		temp = ft_strdup(arrfd->content);
		arrfd->size = 0;
	}
	temp2 = *line;
	if (temp2)
	{
		*line = ft_strjoin(temp2, temp);
		free(temp2);
		free(temp);
	}
	else
		*line = temp;
}

int		get_next_line(const int fd, char **line)
{
	static t_kek	arr[4500];
	char			*end;

	end = NULL;
	if (!line || (!(*line = 0) && (fd < 0 || fd > 4499))
		|| read(fd, NULL, 0) < 0)
		return (-1);
	while (!end)
	{
		if (!arr[fd].size &&
			(arr[fd].size = read(fd, arr[fd].content, BUFF_SIZE)) < 1)
		{
			if (*line)
				return (1);
			else
				return (arr[fd].size);
		}
		arr[fd].content[arr[fd].size] = '\0';
		end = ft_memchr(arr[fd].content, '\n', arr[fd].size);
		ft_strramen(line, &arr[fd], end);
	}
	return (1);
}
