/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:37:54 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/05 11:22:06 by mbouzaie         ###   ########.fr       */
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
	int     count_w;
	int     count_h;
	double	cameraX;
	double	perpWallDist;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	t_params	params;
	t_mapvector	step;

	count_w = -1;
	params = mlx->params;
    while (++count_w < screenWidth)
	{
		cameraX = 2 * count_w / (double)screenWidth - 1;
		params.raydir.x = params.dir.x + params.plane.x * cameraX;
		params.raydir.y = params.dir.y + params.plane.y * cameraX;
		params.posmap.x = (int)params.pos.x;
		params.posmap.y = (int)params.pos.y;
		params.deltadist.x = (params.raydir.y == 0) ? 0 : ((params.raydir.x == 0) ? 1 : fabs(1 / params.raydir.x));
		params.deltadist.y = (params.raydir.x == 0) ? 0 : ((params.raydir.y == 0) ? 1 : fabs(1 / params.raydir.y));
		step = calculate_step_sidedist(&params);
		side = digital_differential_alg(&params, step);
		if (side == 0)
			perpWallDist = (params.posmap.x - params.pos.x + (1 - step.x) / 2) / params.raydir.x;
		else
			perpWallDist = (params.posmap.y - params.pos.y + (1 - step.y) / 2) / params.raydir.y;
		lineHeight = (int) (screenHeight / perpWallDist);
		drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		count_h = -1;
		color = color_walls(params,side);
		while (++count_h < screenHeight)
    	{
			if (count_h < drawStart || count_h > drawEnd)
                mlx->img.data[count_h * screenWidth + count_w] = 0x000000;
            else
                mlx->img.data[count_h * screenWidth + count_w] = color;
		}
	}
	mlx->params = params;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	return (0);
}
