/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:37:54 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/22 18:12:26 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

int		close_event(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	ft_lstclear(&mlx->map, free);
	ft_lstclear(&mlx->sprites, free);
	if (mlx->img.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	clear_textures(mlx);
	exit(0);
	return (0);
}

int		deal_key(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == KEY_RIGHT)
		rotate(&mlx->params, -SPEED_ROT);
	if (key == KEY_LEFT)
		rotate(&mlx->params, SPEED_ROT);
	if (key == KEY_W)
		walk(&mlx->params, SPEED_MOV, AXIS_VERT, mlx->map);
	if (key == KEY_S)
		walk(&mlx->params, -SPEED_MOV, AXIS_VERT,mlx->map);
	if (key == KEY_D)
		walk(&mlx->params, SPEED_MOV, AXIS_HORI, mlx->map);
	if (key == KEY_A)
		walk(&mlx->params, -SPEED_MOV, AXIS_HORI,mlx->map);
	if (key == KEY_ESC)
		close_event(param);
	return (0);
}

int		main_loop(t_mlx *mlx)
{
	int			side;
	int			color;
	int			cardinal;
	t_line		line;
	t_params	params;
	double		wallX;
	t_intvector	texPos;
	t_intvector	count;
	double		step;
	double		texPosd;

	count.x = -1;
	params = mlx->params;
    while (++count.x < params.res.x)
	{
		calculate_params(&params, count.x);
		calculate_step_sidedist(&params);
		side = digital_differential_alg(&params, mlx->map);
		line = calculate_stripe_borders(&params, side);
		count.y = -1;
		if (side == 0)
			wallX = params.pos.y + params.perpwalldist * params.raydir.y;
		else
			wallX = params.pos.x + params.perpwalldist * params.raydir.x;
		wallX -= floor(wallX);
		if (side == 0 && params.raydir.x > 0)
			cardinal = SOUTH;
		if (side == 0 && params.raydir.x < 0)
			cardinal = NORTH;
		if (side == 1 && params.raydir.y > 0)
			cardinal = EAST;
		if (side == 1 && params.raydir.y < 0)
			cardinal = WEST;
		texPos.x = (int)(wallX * (double)mlx->tex[cardinal].width);
		if (side == 0 && params.raydir.x > 0)
			texPos.x = mlx->tex[cardinal].width - texPos.x - 1;
		if (side == 1 && params.raydir.y < 0)
			texPos.x = mlx->tex[cardinal].width - texPos.x - 1;
		step = 1.0 * mlx->tex[cardinal].height / params.lineheight;
		texPosd = (line.start - params.res.y / 2 + params.lineheight / 2) * step;
		while (++count.y < params.res.y)
			if (count.y > line.end)
                mlx->img.data[count.y * params.res.x + count.x] = create_rgb(mlx->floor.r, mlx->floor.g, mlx->floor.b);
			else if (count.y < line.start)
				mlx->img.data[count.y * params.res.x + count.x] = create_rgb(mlx->ceiling.r, mlx->ceiling.g, mlx->ceiling.b);
            else
			{
				texPos.y = (int)texPosd & (mlx->tex[cardinal].height - 1);
				texPosd += step;
                mlx->img.data[count.y * params.res.x + count.x] = get_pixel_color(mlx->tex[cardinal], texPos);
			}
		params.zbuffer[count.x] = params.perpwalldist;
	}
	handle_sprites(mlx);
	mlx->params = params;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	if (params.save)
	{
		save_screen(*mlx);
		close_event(mlx);
	}
	return (0);
}
