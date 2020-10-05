/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 00:03:44 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/05/12 18:51:47 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int				ft_chrloc(char *str, int ch)
{
	size_t		length;

	length = 0;
	if (str)
	{
		while (str[length] != ch && str[length] != '\0')
			length++;
	}
	return (length);
}
