/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:37:54 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/05 18:44:19 by mbouzaie         ###   ########.fr       */
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
	t_params	*params;

	params = (t_params *)param;
	if (key == KEY_RIGHT)
		rotate(params, -0.33);
	if (key == KEY_LEFT)
		rotate(params, 0.33);
	if (key == KEY_UP)
		walk(params, 1);
	if (key == KEY_DOWN)
		walk(params, -1);
	return (0);
}

int		main_loop(t_mlx *mlx)
{
	int			count_w;
	int			count_h;
	int			side;
	int			color;
	t_line		line;
	t_params	params;

	count_w = -1;
	params = mlx->params;
    while (++count_w < screenWidth)
	{
		calculate_params(&params, count_w);
		params.step = calculate_step_sidedist(&params);
		side = digital_differential_alg(&params);
		line = calculate_line_area (&params, side);
		count_h = -1;
		color = color_walls(params,side);
		while (++count_h < screenHeight)
			if (count_h < line.start || count_h > line.end)
                mlx->img.data[count_h * screenWidth + count_w] = 0x000000;
            else
                mlx->img.data[count_h * screenWidth + count_w] = color;
	}
	mlx->params = params;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	return (0);
}
