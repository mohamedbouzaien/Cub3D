/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapted_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:47:28 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/22 18:04:43 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

t_list	*ft_strlstnew(char *content)
{
	t_list *new;

	if (!(new = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
	}
	else
		new->content = content;
	new->next = NULL;
	return (new);
}

t_list	*ft_vectlstnew(t_intvector *content)
{
	t_list *new;

	if (!(new = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
	}
	else
		new->content = content;
	new->next = NULL;
	return (new);
}