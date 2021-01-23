/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 22:22:52 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/23 15:59:20 by mbouzaie         ###   ########.fr       */
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
	int	i;

	i = 0;
	if (char_array)
	{
		while (char_array[i])
		{
			free(char_array[i]);
			i++;
		}
		free(char_array);
	}
}

int		endwith(char const *str, char const *end)
{
	int	size;
	int	end_size;

	size = ft_strlen(str);
	end_size = ft_strlen(end);
	if (end_size > size)
		return (0);
	return (!ft_strncmp(str + size - end_size, end, size - end_size));
}

void	throw_error(t_mlx *mlx, char *msg)
{
	int	i;

	ft_putstr_fd("Error\n", 0);
	ft_putstr_fd(msg, 0);
	i = 1;
	while (i <= SPRITE)
	{
		if (mlx->tex[i].path)
			free(mlx->tex[i].path);
		i++;
	}
	if (mlx->map)
		ft_lstclear(&mlx->map, free);
	if (mlx->sprites)
		ft_lstclear(&mlx->sprites, free);
	if (mlx->params.zbuffer)
	{
		free(mlx->params.zbuffer);
		mlx->params.zbuffer = NULL;
	}
	exit(1);
}
