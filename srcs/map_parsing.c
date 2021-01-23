/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:13:40 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/23 16:00:38 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

int		is_dir_flag(char c)
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

void	read_internal_map(int fd, char **line, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (ft_get_next_line(fd, line))
	{
		if (mlx->map != NULL &&\
		!check_internal_line(*line, ft_lstlast(mlx->map)->content))
		{
			free(*line);
			throw_error(mlx, "The map content lines are incorrect");
		}
		check_direction_flag(*line, &mlx->params, i);
		i++;
		ft_lstadd_back(&mlx->map, ft_strlstnew(*line));
	}
}

void	read_map(int fd, char **line, t_mlx *mlx)
{
	int		dir;

	if (mlx->map == NULL && *line && !check_border_line(*line, NULL))
	{
		free(*line);
		throw_error(mlx, "The northern border of the map is incorrect");
	}
	ft_lstadd_back(&mlx->map, ft_strlstnew(*line));
	read_internal_map(fd, line, mlx);
	if (ft_strlen(*line) > 0)
	{
		if (!check_border_line(*line, ft_lstlast(mlx->map)->content))
		{
			free(*line);
			throw_error(mlx, "The southern border of the map is incorrect");
		}
		ft_lstadd_back(&mlx->map, ft_strlstnew(*line));
	}
	else
		free(*line);
	close(fd);
}

void	parse_cub(char *file_path, t_mlx *mlx)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	while ((ft_get_next_line(fd, &line) >= 0) && !check_border_line(line, NULL))
	{
		if (line[0] == 'R' && line[1] == ' ')
			parse_resolution(&line, mlx);
		else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
			parse_texture(&line, mlx, NORTH);
		else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
			parse_texture(&line, mlx, SOUTH);
		else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
			parse_texture(&line, mlx, WEST);
		else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
			parse_texture(&line, mlx, EAST);
		else if (line[0] == 'F' && line[1] == ' ')
			parse_color(&line, mlx, &mlx->floor);
		else if (line[0] == 'C' && line[1] == ' ')
			parse_color(&line, mlx, &mlx->ceiling);
		else if (line[0] == 'S' && line[1] == ' ')
			parse_texture(&line, mlx, SPRITE);
		free(line);
	}
	read_map(fd, &line, mlx);
}
