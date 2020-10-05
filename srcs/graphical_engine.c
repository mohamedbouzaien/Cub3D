/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:32:59 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/05 11:19:13 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

t_mapvector	calculate_step_sidedist(t_params *params)
{
	t_mapvector step;

	if (params->raydir.x < 0)
	{
		step.x = -1;
		params->sidedist.x = (params->pos.x - params->posmap.x) \
								* params->deltadist.x;
	}
	else
	{
		step.x = 1;
		params->sidedist.x = (params->posmap.x + 1.0 - params->pos.x) \
							* params->deltadist.x;
	}
	if (params->raydir.y < 0)
	{
		step.y = -1;
		params->sidedist.y = (params->pos.y - params->posmap.y) \
							* params->deltadist.y;
	}
	else
	{
		step.y = 1;
		params->sidedist.y = (params->posmap.y + 1.0 - params->pos.y) \
							* params->deltadist.y;
	}
	return (step);
}

int			digital_differential_alg(t_params *params, t_mapvector step)
{
	int hit;
	int side;

	hit = 0;
	while (hit == 0)
	{
		if (params->sidedist.x < params->sidedist.y)
		{
			params->sidedist.x += params->deltadist.x;
			params->posmap.x += step.x;
			side = 0;
		}
		else
		{
			params->sidedist.y += params->deltadist.y;
			params->posmap.y += step.y;
			side = 1;
		}
		if (worldMap[params->posmap.x][params->posmap.y] > 0)
			hit = 1;
	}
	return (side);
}
