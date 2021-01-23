/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_in_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:11:35 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/23 15:56:08 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_str_in_set(char *str, const char *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_char_in_set(str[i], set))
			return (0);
		i++;
	}
	return (1);
}
