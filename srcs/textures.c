/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:23:50 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/08 00:40:34 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

t_tex	load_texture(t_mlx mlx)
{
	t_tex tex;
	tex.data = mlx_xpm_file_to_image(mlx.mlx_ptr, "textures/wall_1.xpm", &tex.width, &tex.height);
	tex.tex_ptr = mlx_get_data_addr(tex.data, &tex.bpp, &tex.size_l, &tex.endian);
	return (tex);
}

int		get_pixel_color(t_tex tex, t_mapvector pos)
{
	if (pos.x >= 0 && pos.x < tex.width && pos.y >= 0 && pos.y < tex.height)
	{
		return (*(int *)(tex.tex_ptr + (4 * tex.width * pos.y) + (4 * pos.x)));
	}
	return (0x0);
}