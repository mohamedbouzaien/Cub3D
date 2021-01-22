/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:13:40 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/22 02:51:57 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

int			check_border_line(char *line, char *previous)
{
	int	i;

	if (!line || !line[0])
		return(0);
	i = 0;
	while(line[i])
	{
		if ((line[i] != '1' && line[i] != ' ') 
		|| (line[i] == ' ' && previous && (previous[i] != '1' && previous[i] != ' ')))
			return (0);
		i++;
	}
	return (1);
}

int			is_dir_flag(char c)
{
	if (c == 'N')
		return (NORTH);
	if (c == 'S')
		return (SOUTH);
	if (c == 'W')
		return (WEST);
	if (c == 'E')
		return (EAST);
	return (0);
}

void		check_direction_flag(char *line, t_params *params, int pos)
{
	int	i;

	i = 0;
	while(line[i] != '\0' && params->cardinal == 0)
	{
		params->cardinal = is_dir_flag(line[i]);
		if(params->cardinal != 0)
		{
			set_vector(&params->pos, pos + 1.5, i + .5);
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
		i++;
	}
}

int			check_internal_line(char *line, char *previous)
{
	int i;

	i = 0;
	while(line[i] == ' ' && (previous[i] == ' ' || previous[i] == '1'))
		i++;
	if (line[i] != '1')
		return (0);
	while(line[i])
	{
		if (line[i] == ' ' && (previous[i] != ' ' && previous[i] != '1'))
			return (0);
		if  (line[i] == '0' && ((previous[i] != '0' && previous[i] != '1' 
			&& previous[i] != '2' && !is_dir_flag(previous[i]))
			|| (line[i + 1] != '0' && line[i + 1] != '1' && line[i + 1] != '2'
			&& !is_dir_flag(line[i + 1]))))
				return (0);
		if  (is_dir_flag(line[i]) && ((previous[i] != '0' 
			&& previous[i] != '1' && previous[i] != '2')
			|| (line[i + 1] != '0' && line[i + 1] != '1' && line[i + 1] != '2')))
				return (0);
		if (line[i] == '2' && !line[i + 1])
			return (0);
		i++;
	}
	return (1);
}

void	read_map(int fd, char *line, t_mlx *mlx)
{
	int		i;
	int		dir;

	i = 0;
	if (mlx->map == NULL && !check_border_line(line, NULL))
		throw_error("The northern border of the map is incorrect");
	ft_lstadd_back(&mlx->map, ft_lstnew(line));
	while (ft_get_next_line(fd, &line))
	{
		if (mlx->map != NULL && !check_internal_line(line, ft_lstlast(mlx->map)->content))
			throw_error("The map content lines are incorrect");
		check_direction_flag(line, &mlx->params, i);
		i++;
		ft_lstadd_back(&mlx->map, ft_lstnew(line));
	}
	if (ft_strlen(line) > 0)
	{
		if (!check_border_line(line, ft_lstlast(mlx->map)->content))
			throw_error("The southern border of the map is incorrect");
		ft_lstadd_back(&mlx->map, ft_lstnew(line));
	}
	close(fd);
}

void	parse_resolution(char *line, t_params *params)
{
	char	**line_array;

	line_array = ft_split(line, ' ');
	if (params->res.x && params->res.y)
		throw_error("Multiple resolutions!");
	if (!(line_array[1] && line_array[2]) || !(ft_str_in_set(line_array[1],\
	",0123456789") && ft_str_in_set(line_array[2], ",0123456789"))\
	|| line_array[3])
		throw_error("Incorrect resolution");
	params->res.x = ft_atoi(line_array[1]);
	params->res.y = ft_atoi(line_array[2]);
	free_char_array(line_array);
}

static	void	parse_texture(char *line, t_tex *tex, int card)
{
	char	**line_array;

	if (tex[card].path != NULL)
		throw_error("Multiple texture");
	line_array = ft_split(line, ' ');
	if (!line_array[1] || line_array[2])
		throw_error("Incorrect texture");
	tex[card].path = ft_strdup(line_array[1]);
	free_char_array(line_array);
}

static void	parse_color(char *line, t_color *color)
{
	char	**line_array;
	char	**color_array;

	line_array = ft_split(line, ' ');
	color_array = ft_split(line_array[1], ',');
	if (color->r >= 0 && color->g >= 0 && color->b >= 0)
		throw_error("Multiple color");
	if (!(line_array[1] && color_array[0] && color_array[1] && color_array[2])\
	|| !(ft_str_in_set(color_array[0], ",0123456789") &&\
	ft_str_in_set(color_array[1], ",0123456789") && ft_str_in_set(color_array[2],\
	",0123456789")) || line_array[2] || color_array[3])
		throw_error("Incorrect color");
	color->r = ft_atoi(color_array[0]);
	color->g = ft_atoi(color_array[1]);
	color->b = ft_atoi(color_array[2]);
	if (color->r > 255 || color->g > 255 || color->b > 255)
		throw_error("color has more than 255 value");
	free_char_array(line_array);
	free_char_array(color_array);
}

void		parse_cub(char *file_path, t_mlx *mlx)
{
	int		fd;
	char	*line;
	int		tst;

	fd = open(file_path, O_RDONLY);
	while ((tst = ft_get_next_line(fd, &line) >= 0) && !check_border_line(line, NULL))
	{
		if (line[0] == 'R' && line[1] == ' ')
			parse_resolution(line, &mlx->params);
		else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
			parse_texture(line, mlx->tex, NORTH);
		else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
			parse_texture(line, mlx->tex, SOUTH);
		else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
			parse_texture(line, mlx->tex, WEST);
		else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
			parse_texture(line, mlx->tex, EAST);
		else if (line[0] == 'F' && line[1] == ' ')
			parse_color(line, &mlx->floor);
		else if (line[0] == 'C' && line[1] == ' ')
			parse_color(line, &mlx->ceiling);
		else if (line[0] == 'S' && line[1] == ' ')
			parse_texture(line, mlx->tex, SPRITE);
		free(line);
		line = NULL;
	}
	read_map(fd, line, mlx);
}
