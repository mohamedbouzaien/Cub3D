/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:34:51 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/16 12:54:44 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstfind_index(t_list *lst, int index)
{
	int	i;

	i = -1;
	while (++i < index && lst->next)
		lst = lst->next;
	if (i == index)
		return (lst);
	return (NULL);
}
