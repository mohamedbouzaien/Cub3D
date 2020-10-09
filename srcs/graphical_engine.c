/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:32:59 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/07 19:13:33 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

void		calculate_params(t_params *params, int count_w)
{
	double	camera_x;

	camera_x = 2 * count_w / (double)screenWidth - 1;
	params->raydir.x = params->dir.x + params->plane.x * camera_x;
	params->raydir.y = params->dir.y + params->plane.y * camera_x;
	params->posmap.x = (int)params->pos.x;
	params->posmap.y = (int)params->pos.y;
	if (params->raydir.y == 0)
		params->deltadist.x = 0;
	else if (params->raydir.x == 0)
		params->deltadist.x = 1;
	else
		params->deltadist.x = fabs(1 / params->raydir.x);
	if (params->raydir.x == 0)
		params->deltadist.y = 0;
	else if (params->raydir.y == 0)
		params->deltadist.y = 1;
	else
		params->deltadist.y = fabs(1 / params->raydir.y);
}

void	calculate_step_sidedist(t_params *params)
{
	if (params->raydir.x < 0)
	{
		params->step.x = -1;
		params->sidedist.x = (params->pos.x - params->posmap.x) \
								* params->deltadist.x;
	}
	else
	{
		params->step.x = 1;
		params->sidedist.x = (params->posmap.x + 1.0 - params->pos.x) \
							* params->deltadist.x;
	}
	if (params->raydir.y < 0)
	{
		params->step.y = -1;
		params->sidedist.y = (params->pos.y - params->posmap.y) \
							* params->deltadist.y;
	}
	else
	{
		params->step.y = 1;
		params->sidedist.y = (params->posmap.y + 1.0 - params->pos.y) \
							* params->deltadist.y;
	}
}

int		digital_differential_alg(t_params *params)
{
	int hit;
	int side;

	hit = 0;
	while (hit == 0)
	{
		if (params->sidedist.x < params->sidedist.y)
		{
			params->sidedist.x += params->deltadist.x;
			params->posmap.x += params->step.x;
			side = 0;
		}
		else
		{
			params->sidedist.y += params->deltadist.y;
			params->posmap.y += params->step.y;
			side = 1;
		}
		if (worldMap[params->posmap.x][params->posmap.y] > 0)
			hit = 1;
	}
	return (side);
}

t_line	calculate_stripe_borders(t_params *params, int side)
{
	t_line	line;

	if (side == 0)
		params->perpWallDist = (params->posmap.x - params->pos.x + (1 - params->step.x) / 2) / params->raydir.x;
	else
		params->perpWallDist = (params->posmap.y - params->pos.y + (1 - params->step.y) / 2) / params->raydir.y;
	params->lineHeight = (int) (screenHeight / params->perpWallDist);
	line.start = -params->lineHeight / 2 + screenHeight / 2;
	if (line.start < 0)
		line.start = 0;
	line.end = params->lineHeight / 2 + screenHeight / 2;
	if (line.end >= screenHeight)
		line.end = screenHeight - 1;
	return (line);
}