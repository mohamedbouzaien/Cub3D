/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:10:46 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/15 17:31:56 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

t_params	init_params(void)
{
	t_params	params;

	params.pos.x = 10;
	params.pos.y = 11.5;
	params.dir.x = 0.;
	params.dir.y = 1.;
	params.plane.x = 0.66;
	params.plane.y = 0;
	params.cardinal = 0;
	return (params);
}

void		throw_error(char *msg)
{
	ft_putstr_fd("Error\n", 0);
	ft_putstr_fd(msg, 0);
	exit(1);
}

int			main(void)
{
	t_mlx	mlx;

	mlx.params = init_params();
	parse_cub("map2.cub", &mlx);
	mlx.mlx_ptr = mlx_init();
	mlx.sprites = get_stripes_coords(mlx.map);
	mlx.win = mlx_new_window(mlx.mlx_ptr, mlx.params.resolution.x,\
	mlx.params.resolution.y, "Wolfstein3D");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, mlx.params.resolution.x,\
	mlx.params.resolution.y);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp,\
	&mlx.img.size_l, &mlx.img.endian);
	load_textures(&mlx);
	mlx_hook(mlx.win, 2, 1L << 0, deal_key, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &main_loop, &mlx);
	mlx_hook(mlx.win, 17, 1L << 17, close_event, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
