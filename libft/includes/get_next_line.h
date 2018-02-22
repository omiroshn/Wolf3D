/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <omiroshn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 21:10:13 by omiroshn          #+#    #+#             */
/*   Updated: 2018/01/11 17:39:19 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1000
# include "libft.h"
# include <fcntl.h>

typedef	struct	s_kek
{
	char		content[BUFF_SIZE + 1];
	size_t		size;
}				t_kek;

int				get_next_line(const int fd, char **line);

#endif
