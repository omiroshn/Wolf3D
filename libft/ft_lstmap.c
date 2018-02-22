/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 13:25:03 by omiroshn          #+#    #+#             */
/*   Updated: 2017/11/05 13:25:04 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*result;
	t_list	*tmpresult;
	t_list	*tmplst;

	if (lst == NULL || f == NULL)
		return (NULL);
	tmplst = f(lst);
	if ((result = ft_lstnew(tmplst->content, tmplst->content_size)))
	{
		tmpresult = result;
		lst = lst->next;
		while (lst != NULL)
		{
			tmplst = (*f)(lst);
			if (!(tmpresult->next = ft_lstnew(tmplst->content,
										tmplst->content_size)))
				return (NULL);
			tmpresult = tmpresult->next;
			lst = lst->next;
		}
	}
	return (result);
}
