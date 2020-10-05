/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 22:26:21 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/05/12 18:52:35 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (alst && new)
	{
		if (*alst)
		{
			temp = *alst;
			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = new;
		}
		else
		{
			*alst = new;
		}
	}
}
