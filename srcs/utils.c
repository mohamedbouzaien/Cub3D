/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 22:22:52 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/22 02:44:25 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

int		create_rgb(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void	set_vector(t_vector *vector, double x, double y)
{
	vector->x = x;
	vector->y = y;
}

void	free_char_array(char **char_array)
{
	int		i;
	i = 0;
	while (char_array[i])
	{
		free(char_array[i]);
		i++;
	}
	free(char_array);
}