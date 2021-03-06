/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:23:50 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/23 00:32:07 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

int		load_textures(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (++i <= SPRITE)
	{
		if (mlx->tex[i].path != NULL)
			if ((mlx->tex[i].data = mlx_xpm_file_to_image(mlx->mlx_ptr,\
			mlx->tex[i].path, &mlx->tex[i].width, &mlx->tex[i].height)))
				mlx->tex[i].tex_ptr = mlx_get_data_addr(mlx->tex[i].data,\
				&mlx->tex[i].bpp, &mlx->tex[i].size_l, &mlx->tex[i].endian);
			else
				return (0);
			
	}
	return (1);
}

int		get_pixel_color(t_tex tex, t_intvector pos)
{
	if (pos.x >= 0 && pos.x < tex.width && pos.y >= 0 && pos.y < tex.height)
	{
		return (*(int *)(tex.tex_ptr + (4 * tex.width * pos.y) + (4 * pos.x)));
	}
	return (0x0);
}

void	clear_textures(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (++i <= SPRITE)
	{
		if (mlx->tex[i].data)
		{
			mlx_destroy_image(mlx->mlx_ptr, mlx->tex[i].data);
			free(mlx->tex[i].path);
			mlx->tex[i].path = NULL;
			mlx->tex[i].data = NULL;
			mlx->tex[i].tex_ptr = NULL;
		}
	}
}

int		check_texture_paths(t_tex tex[6])
{
	int	i;

	i = 1;
	while (i < 6)
	{
		if (tex[i].path == NULL)
			return (0);
		i++;
	}
	return (1);
}
