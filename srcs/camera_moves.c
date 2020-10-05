/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 11:23:37 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/05 11:24:35 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"


void	rotate(t_params *params, double degree)
{
	double		oldDirX;
	double		oldPlaneX;

	oldDirX = params->dir.x;
	params->dir.x = params->dir.x * cosf(degree) - params->dir.y * sinf(degree);
	params->dir.y = oldDirX * sinf(degree) + params->dir.y * cosf(degree);
	oldPlaneX = params->plane.x;
	params->plane.x = params->plane.x * cosf(degree) - params->plane.y * sinf(degree);
	params->plane.y = oldPlaneX * sinf(degree) + params->plane.y * cosf(degree);
}

void	walk(t_params *params, double step)
{
		if (worldMap[(int)(params->pos.x + params->dir.x * step)][(int)params->pos.y] == 0)
			params->pos.x += params->dir.x * step;
		if (worldMap[(int)params->pos.x][(int)(params->pos.y + params->dir.y * step)] == 0)
			params->pos.y += params->dir.y * step;
}
