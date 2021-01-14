/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:13:40 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/14 17:58:20 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

int			check_border_line(char *line, char *previous)
{
	int	i;

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

int			is_direction_flag(char c)
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

void		set_vector(t_vector *vector, double x, double y)
{
	vector->x = x;
	vector->y = y;
}

void		check_direction_flag(char *line, t_params *params, int pos)
{
	int	i;

	i = 0;
	while(line[i] != '\0' && params->cardinal == 0)
	{
		params->cardinal = is_direction_flag(line[i]);
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
			&& previous[i] != '2' && !is_direction_flag(previous[i]))
			|| (line[i + 1] != '0' && line[i + 1] != '1' && line[i + 1] != '2'
			&& !is_direction_flag(line[i + 1]))))
				return (0);
		if  (is_direction_flag(line[i]) && ((previous[i] != '0' 
			&& previous[i] != '1' && previous[i] != '2')
			|| (line[i + 1] != '0' && line[i + 1] != '1' && line[i + 1] != '2')))
				return (0);
		i++;
	}
	return (1);
}

t_list		*read_map(int fd, char *line, t_mlx *mlx)
{
	t_list	*map;
	int		i;
	int		dir;

	i = 0;
	map = NULL;
	if (map == NULL && !check_border_line(line, NULL))
		throw_error("The northern border of the map is incorrect");
	ft_lstadd_back(&map, ft_lstnew(line));
	while (ft_get_next_line(fd, &line))
	{
		if (map != NULL && !check_internal_line(line, ft_lstlast(map)->content))
			throw_error("The map content lines are incorrect");
		check_direction_flag(line, &mlx->params, i);
		i++;
		ft_lstadd_back(&map, ft_lstnew(line));
	}
	if (ft_strlen(line) > 0)
	{
		if (!check_border_line(line, ft_lstlast(map)->content))
			throw_error("The southern border of the map is incorrect");
		ft_lstadd_back(&map, ft_lstnew(line));
	}
	close(fd);
	return (map);
}

t_intvector	parse_resolution(char *line)
{
	t_intvector	res;
	char		**line_array;

	line_array = ft_split(line, ' ');
	res.x = ft_atoi(line_array[1]);
	res.y = ft_atoi(line_array[2]);
	free(line_array);
	return res;
}

static	char	*parse_texture(char *line)
{
	char	*str;
	char	**line_array;

	line_array = ft_split(line, ' ');
	str = ft_strdup(line_array[1]);
	free(line_array);
	return (str);
}

static t_color	parse_color(char *line)
{
	t_color color;
	char	**line_array;
	char	**color_array;

	line_array = ft_split(line, ' ');
	color_array = ft_split(line_array[1], ',');
	color.r = ft_atoi(color_array[0]);
	color.g = ft_atoi(color_array[1]);
	color.b = ft_atoi(color_array[2]);
	free(line_array);
	free(color_array);
	return (color);
}

void		parse_cub(char *file_path, t_mlx *mlx)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	while (ft_get_next_line(fd, &line) && !check_border_line(line, NULL))
	{
		if (line[0] == 'R' && line[1] == ' ')
			mlx->params.resolution = parse_resolution(line);
		else if (line[0] == 'N' && line[1] == 'O')
			mlx->tex[NORTH].path = parse_texture(line);
		else if (line[0] == 'S' && line[1] == 'O')
			mlx->tex[SOUTH].path = parse_texture(line);
		else if (line[0] == 'W' && line[1] == 'E')
			mlx->tex[WEST].path = parse_texture(line);
		else if (line[0] == 'E' && line[1] == 'A')
			mlx->tex[EAST].path = parse_texture(line);
		else if (line[0] == 'F' && line[1] == ' ')
			mlx->floor = parse_color(line);
		else if (line[0] == 'C' && line[1] == ' ')
			mlx->ceiling = parse_color(line);
		else if (line[0] == 'S' && line[1] == '1')
			mlx->tex[SPRITE1].path = parse_texture(line);
		else if (line[0] == 'S' && line[1] == '2')
			mlx->tex[SPRITE2].path = parse_texture(line);
		else if (line[0] == 'S' && line[1] == '3')
			mlx->tex[SPRITE3].path = parse_texture(line);
		free(line);
	}
	mlx->map = read_map(fd, line, mlx);
}
