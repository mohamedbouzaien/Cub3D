/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 18:24:40 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/05/12 18:53:15 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_l;
	t_list	*new_e;

	new_l = NULL;
	if (lst && f)
	{
		while (lst)
		{
			if (!(new_e = ft_lstnew(f(lst->content))))
			{
				ft_lstclear(&new_l, del);
				return (NULL);
			}
			ft_lstadd_back(&new_l, new_e);
			lst = lst->next;
		}
		return (new_l);
	}
	return (NULL);
}
