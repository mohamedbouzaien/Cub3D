/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:37:54 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/23 13:18:15 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

int				close_event(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	ft_lstclear(&mlx->map, free);
	ft_lstclear(&mlx->sprites, free);
	free(mlx->params.zbuffer);
	mlx->params.zbuffer = NULL;
	if (mlx->img.img_ptr)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
		mlx->img.img_ptr = NULL;
		mlx->img.data = NULL;
	}
	if (mlx->win)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
		mlx->win = NULL;
	}
	clear_textures(mlx);
	exit(0);
	return (0);
}

int				deal_key(int key, void *param)
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
		walk(&mlx->params, -SPEED_MOV, AXIS_VERT, mlx->map);
	if (key == KEY_D)
		walk(&mlx->params, SPEED_MOV, AXIS_HORI, mlx->map);
	if (key == KEY_A)
		walk(&mlx->params, -SPEED_MOV, AXIS_HORI, mlx->map);
	if (key == KEY_ESC)
		close_event(param);
	return (0);
}

static	void	draw_line(t_mlx *mlx, t_params *params, int card, int countx)
{
	double		step;
	double		texposd;
	int			county;

	county = -1;
	step = 1.0 * mlx->tex[card].height / params->lheight;
	texposd = (params->line.start - params->res.y / 2 +\
	params->lheight / 2) * step;
	while (++county < params->res.y)
		if (county > params->line.end)
			mlx->img.data[county * params->res.x + countx] =\
			create_rgb(mlx->floor.r, mlx->floor.g, mlx->floor.b);
		else if (county < params->line.start)
			mlx->img.data[county * params->res.x + countx] =\
			create_rgb(mlx->ceiling.r, mlx->ceiling.g, mlx->ceiling.b);
		else
		{
			params->texpos.y = (int)texposd & (mlx->tex[card].height - 1);
			texposd += step;
			mlx->img.data[county * params->res.x + countx] =\
			get_pixel_color(mlx->tex[card], params->texpos);
		}
}

static	int		init_side_card(t_mlx *mlx, t_params *params)
{
	int	card;

	if (params->side == 0)
		params->wallx = params->pos.y + params->perpwalldist * params->raydir.y;
	else
		params->wallx = params->pos.x + params->perpwalldist * params->raydir.x;
	params->wallx -= floor(params->wallx);
	if (params->side == 0 && params->raydir.x > 0)
		card = SOUTH;
	if (params->side == 0 && params->raydir.x < 0)
		card = NORTH;
	if (params->side == 1 && params->raydir.y > 0)
		card = EAST;
	if (params->side == 1 && params->raydir.y < 0)
		card = WEST;
	params->texpos.x = (int)(params->wallx * (double)mlx->tex[card].width);
	if (params->side == 0 && params->raydir.x > 0)
		params->texpos.x = mlx->tex[card].width - params->texpos.x - 1;
	if (params->side == 1 && params->raydir.y < 0)
		params->texpos.x = mlx->tex[card].width - params->texpos.x - 1;
	return (card);
}

int				main_loop(t_mlx *mlx)
{
	int			color;
	int			card;
	int			countx;

	countx = -1;
	while (++countx < mlx->params.res.x)
	{
		calculate_params(&mlx->params, countx);
		calculate_step_sidedist(&mlx->params);
		digital_differential_alg(&mlx->params, mlx->map);
		calculate_stripe_borders(&mlx->params, mlx->params.side);
		card = init_side_card(mlx, &mlx->params);
		draw_line(mlx, &mlx->params, card, countx);
		mlx->params.zbuffer[countx] = mlx->params.perpwalldist;
	}
	handle_sprites(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	if (mlx->params.save)
	{
		save_screen(*mlx);
		close_event(mlx);
	}
	return (0);
}
