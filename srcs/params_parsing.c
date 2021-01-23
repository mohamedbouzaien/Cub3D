/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:56:21 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/23 16:01:03 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

static	void	throw_error_color(t_mlx *mlx, char **line, char **ar, char *msg)
{
	free_char_array(ar);
	free(*line);
	throw_error(mlx, msg);
}

void			parse_color(char **line, t_mlx *mlx, t_color *color)
{
	char	**line_array;
	char	**color_array;

	line_array = ft_split(*line, ' ');
	if (color->r >= 0 && color->g >= 0 && color->b >= 0)
		throw_error_color(mlx, line, line_array, "Multiple color");
	color_array = ft_split(line_array[1], ',');
	if (!(line_array[1] && color_array[0] && color_array[1] && color_array[2])\
	|| !(ft_str_in_set(color_array[0], ",0123456789") &&\
	ft_str_in_set(color_array[1], ",0123456789") && ft_str_in_set(\
	color_array[2], ",0123456789")) || line_array[2] || color_array[3])
	{
		free_char_array(color_array);
		throw_error_color(mlx, line, line_array, "Incorrect color");
	}
	color->r = ft_atoi(color_array[0]);
	color->g = ft_atoi(color_array[1]);
	color->b = ft_atoi(color_array[2]);
	if (color->r > 255 || color->g > 255 || color->b > 255)
	{
		free_char_array(color_array);
		throw_error_color(mlx, line, line_array, "color has more than 255");
	}
	free_char_array(line_array);
	free_char_array(color_array);
}

void			parse_texture(char **line, t_mlx *mlx, int card)
{
	char	**line_array;

	if (mlx->tex[card].path != NULL)
	{
		free(*line);
		throw_error(mlx, "Multiple texture");
	}
	line_array = ft_split(*line, ' ');
	if (!line_array[1] || line_array[2])
	{
		free(*line);
		free_char_array(line_array);
		throw_error(mlx, "Incorrect texture");
	}
	mlx->tex[card].path = ft_strdup(line_array[1]);
	free_char_array(line_array);
}

void			parse_resolution(char **line, t_mlx *mlx)
{
	char	**line_array;

	if (mlx->params.res.x && mlx->params.res.y)
	{
		free(*line);
		throw_error(mlx, "Multiple resolutions!");
	}
	line_array = ft_split(*line, ' ');
	if (!(line_array[1] && line_array[2]) || !(ft_str_in_set(line_array[1],\
	",0123456789") && ft_str_in_set(line_array[2], ",0123456789"))\
	|| line_array[3])
	{
		free(*line);
		free_char_array(line_array);
		throw_error(mlx, "Incorrect resolution");
	}
	mlx->params.res.x = ft_atoi(line_array[1]);
	mlx->params.res.y = ft_atoi(line_array[2]);
	free_char_array(line_array);
}
