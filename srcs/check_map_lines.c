/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:55:46 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/23 15:46:08 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

static	void	set_cardinal_params(t_params *params)
{
	if (params->cardinal == NORTH)
	{
		set_vector(&params->dir, -1, 0);
		set_vector(&params->plane, 0, 0.66);
	}
	else if (params->cardinal == SOUTH)
	{
		set_vector(&params->dir, 1, 0);
		set_vector(&params->plane, 0, -0.66);
	}
	else if (params->cardinal == WEST)
	{
		set_vector(&params->dir, 0, -1);
		set_vector(&params->plane, -0.66, 0);
	}
	else if (params->cardinal == EAST)
	{
		set_vector(&params->dir, 0, 1);
		set_vector(&params->plane, 0.66, 0);
	}
}

int				check_border_line(char *line, char *prev)
{
	int	i;

	if (!line[0])
		return (0);
	i = 0;
	while (line[i])
	{
		if ((line[i] != '1' && line[i] != ' ')
		|| (line[i] == ' ' && prev && (prev[i] != '1' && prev[i] != ' ')))
			return (0);
		i++;
	}
	return (1);
}

void			check_direction_flag(char *line, t_params *params, int pos)
{
	int	i;

	i = -1;
	while (line[++i] != '\0' && params->cardinal == 0)
	{
		params->cardinal = is_dir_flag(line[i]);
		if (params->cardinal != 0)
		{
			set_vector(&params->pos, pos + 1.5, i + .5);
			set_cardinal_params(params);
		}
	}
}

int				check_internal_line(char *line, char *prev)
{
	int	i;

	i = 0;
	while (line[i] == ' ' && (prev[i] == ' ' || prev[i] == '1'))
		i++;
	if (line[i] != '1')
		return (0);
	while (line[i])
	{
		if (line[i] == ' ' && (prev[i] != ' ' && prev[i] != '1'))
			return (0);
		if (line[i] == '0' && ((prev[i] != '0' && prev[i] != '1' && prev[i]\
		!= '2' && !is_dir_flag(prev[i])) || (line[i + 1] != '0' && line[i + 1]\
		!= '1' && line[i + 1] != '2' && !is_dir_flag(line[i + 1]))))
			return (0);
		if (is_dir_flag(line[i]) && ((prev[i] != '0' && prev[i] != '1' &&\
		prev[i] != '2') || (line[i + 1] != '0' && line[i + 1] != '1' &&\
		line[i + 1] != '2')))
			return (0);
		if (line[i] == '2' && !line[i + 1])
			return (0);
		i++;
	}
	return (1);
}
