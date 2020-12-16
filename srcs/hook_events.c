/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:37:54 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/28 15:41:41 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

int		close_event(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	//if (mlx->img.img_ptr)
	//	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	return (0);
}

int		deal_key(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == KEY_RIGHT)
		rotate(&mlx->params, -0.33);
	if (key == KEY_LEFT)
		rotate(&mlx->params, 0.33);
	if (key == KEY_UP)
		walk(&mlx->params, 1, mlx->map);
	if (key == KEY_DOWN)
		walk(&mlx->params, -1, mlx->map);
	return (0);
}

int		createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int		main_loop(t_mlx *mlx)
{
	int			count_w;
	int			count_h;
	int			side;
	int			color;
	t_line		line;
	t_params	params;
	double		wallX;
	t_intvector	texPos;
	double		step;
	double		texPosd;

	count_w = -1;
	params = mlx->params;
    while (++count_w < params.resolution.x)
	{
		calculate_params(&params, count_w);
		calculate_step_sidedist(&params);
		side = digital_differential_alg(&params, mlx->map);
		line = calculate_stripe_borders(&params, side);
		count_h = -1;
		if (side == 0)
			wallX = params.pos.y + params.perpWallDist * params.raydir.y;
		else
			wallX = params.pos.x + params.perpWallDist * params.raydir.x;
		wallX -= floor(wallX);
		texPos.x = (int)(wallX * (double)mlx->tex[0].width);
		if (side == 0 && params.raydir.x > 0)
			texPos.x = mlx->tex[0].width - texPos.x - 1;
		if (side == 1 && params.raydir.y < 0)
			texPos.x= mlx->tex[0].width - texPos.x - 1;
		step = 1.0 * mlx->tex[0].height / params.lineHeight;
		texPosd = (line.start - count_h / 2 + params.lineHeight / 2) * step;
		while (++count_h < params.resolution.y)
			if (count_h < line.start || count_h > line.end)
                mlx->img.data[count_h * params.resolution.x + count_w] = createRGB(220, 100, 100);
            else
			{
				texPos.y = (int)texPosd & (mlx->tex[0].height - 1);
				texPosd += step;
                mlx->img.data[count_h * params.resolution.x + count_w] = get_pixel_color(mlx->tex[0], texPos);
			}
	}
	mlx->params = params;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	return (0);
}
