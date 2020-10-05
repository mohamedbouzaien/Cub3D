/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 22:50:16 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/05/12 18:51:39 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*allocated;

	i = 0;
	allocated = malloc(size * count);
	if (allocated == NULL)
		return (NULL);
	while (i < (count * size))
	{
		((char*)allocated)[i] = 0;
		i++;
	}
	return (allocated);
}
