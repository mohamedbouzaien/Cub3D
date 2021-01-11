/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:23:50 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/28 13:55:01 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

void	load_textures(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (++i <= EAST){
		if (mlx->tex[i].path != NULL)
			if ((mlx->tex[i].data = mlx_xpm_file_to_image(mlx->mlx_ptr, mlx->tex[i].path, &mlx->tex[i].width, &mlx->tex[i].height)))
				mlx->tex[i].tex_ptr = mlx_get_data_addr(mlx->tex[i].data, &mlx->tex[i].bpp, &mlx->tex[i].size_l, &mlx->tex[i].endian);
}
}

int		get_pixel_color(t_tex tex, t_intvector pos)
{
	if (pos.x >= 0 && pos.x < tex.width && pos.y >= 0 && pos.y < tex.height)
	{
		return (*(int *)(tex.tex_ptr + (4 * tex.width * pos.y) + (4 * pos.x)));
	}
	return (0x0);
}