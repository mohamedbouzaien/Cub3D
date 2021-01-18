/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 11:23:37 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/18 14:30:32 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

void	rotate(t_params *params, double degree)
{
	double		olddirx;
	double		oldplanex;

	olddirx = params->dir.x;
	params->dir.x = params->dir.x * cosf(degree) - params->dir.y * sinf(degree);
	params->dir.y = olddirx * sinf(degree) + params->dir.y * cosf(degree);
	oldplanex = params->plane.x;
	params->plane.x = params->plane.x * cosf(degree) - params->plane.y\
						* sinf(degree);
	params->plane.y = oldplanex * sinf(degree) + params->plane.y * cosf(degree);
}

void	walk(t_params *params, double step, int axis, t_list *map)
{
	char	*l;
	int		index;

	if (axis == AXIS_PERP)
	{
		index = (int)(params->pos.x + params->dir.x * step);
		l = (char *)ft_lstfind_index(map, index)->content;
		if (l[(int)params->pos.y] == '0' || is_dir_flag(l[(int)params->pos.y]))
			params->pos.x += params->dir.x * step;
		index = (int)(params->pos.y + params->dir.y * step);
		l = (char *)ft_lstfind_index(map, (int)params->pos.x)->content;
		if (l[index] == '0' || is_dir_flag(l[index]))
			params->pos.y += params->dir.y * step;
	}
	else
	{
		index = (int)(params->pos.x + params->plane.x * step);
		l = (char *)ft_lstfind_index(map, index)->content;
		if (l[(int)params->pos.y] == '0' || is_dir_flag(l[(int)params->pos.y]))
			params->pos.x += params->plane.x * step;
		index = (int)(params->pos.y + params->plane.y * step);
		l = (char *)ft_lstfind_index(map, (int)params->pos.x)->content;
		if (l[index] == '0' || is_dir_flag(l[index]))
			params->pos.y += params->plane.y * step;
	}
}
