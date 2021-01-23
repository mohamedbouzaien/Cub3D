/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:10:46 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/23 00:56:47 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

t_params	init_params(void)
{
	t_params	params;

	params.res.x = 0;
	params.res.y = 0;
	params.pos.x = 10;
	params.pos.y = 11.5;
	params.dir.x = 0.;
	params.dir.y = 1.;
	params.plane.x = 0.66;
	params.plane.y = 0;
	params.cardinal = 0;
	params.save = 0;
	params.zbuffer = NULL;
	return (params);
}

void		finish_init(t_mlx *mlx)
{
	if (!mlx->params.res.x || !mlx->params.res.y)
		throw_error(mlx, "Resolution not found");
	if (mlx->floor.r == -1 || mlx->ceiling.r == -1)
		throw_error(mlx, "Color not found");
	mlx->params.zbuffer = (double *)malloc(sizeof(double)\
						* mlx->params.res.x + 1);
	if (!check_texture_paths(mlx->tex))
		throw_error(mlx, "texture path missing");
	if (mlx->params.cardinal == 0)
		throw_error(mlx, "Cardinal error");
	if (mlx->params.res.x > 1920)
		mlx->params.res.x = 1920;
	if (mlx->params.res.y > 1080)
		mlx->params.res.y = 1080;
	if (mlx->params.res.x < 848)
		mlx->params.res.x = 848;
	if (mlx->params.res.y < 480)
		mlx->params.res.y = 480;
}

void		throw_error(t_mlx *mlx, char *msg)
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

int			main(int ac, char **av)
{
	t_mlx	mlx;
	int		i;

	mlx.params = init_params();
	mlx.floor.r = -1;
	mlx.floor.g = -1;
	mlx.floor.b = -1;
	mlx.ceiling.r = -1;
	mlx.ceiling.g = -1;
	mlx.ceiling.b = -1;
	mlx.map = NULL;
	mlx.sprites = NULL;
	i = 0;
	while (++i < 6)
		mlx.tex[i].path = NULL;
	parse_cub(av[1], &mlx);
	finish_init(&mlx);
	mlx.mlx_ptr = mlx_init();
	mlx.sprites = get_sprites_coords(mlx.map);
	mlx.win = mlx_new_window(mlx.mlx_ptr, mlx.params.res.x,\
	mlx.params.res.y, "Wolfstein3D");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, mlx.params.res.x,\
	mlx.params.res.y);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp,\
	&mlx.img.size_l, &mlx.img.endian);
	if (!load_textures(&mlx))
		throw_error(&mlx, "Incorrect texture path!");
	mlx_hook(mlx.win, 2, 1L << 0, deal_key, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &main_loop, &mlx);
	mlx_hook(mlx.win, 17, 1L << 17, close_event, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
