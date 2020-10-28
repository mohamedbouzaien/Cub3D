/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:13:40 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/28 14:28:15 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"


void	ft_putstr(void* s)
{
	int 	len;
	char	*str;
	char	n;

	str = (char *)s;
	n = '\n';
	if (str)
	{
		len = ft_strlen(str);
		write(0, str, len);
		write(0, &n, 1);
	}
}

int			check_border_line(char *line, char *previous)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if ((line[i] != '1' && line[i] != ' ') 
		|| (line[i] == ' ' && previous && (previous[i] != '1' && previous[i] != ' ')))
		{
			ft_putstr_fd(line + i, 0);
			return (0);
		}
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

t_list		*read_map(int fd, char *line)
{
	t_list	*map;
	int		i;
	int		dir;

	i = 1;
	map = NULL;
	if (map == NULL && !check_border_line(line, NULL))
		throw_error("The northern border of the map is incorrect");
	ft_lstadd_back(&map, ft_lstnew(line));
	while (ft_get_next_line(fd, &line))
	{
		if (map != NULL && !check_internal_line(line, ft_lstlast(map)->content))
			throw_error("The map content lines are incorrect");
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
	int			i;
	t_intvector	res;
	char		**line_array;

	line_array = ft_split(line, ' ');
	res.x = ft_atoi(line_array[1]);
	res.y = ft_atoi(line_array[2]);
	return res;
	
}

void		parse_cub(char *file_path, t_mlx *mlx)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	while (ft_get_next_line(fd, &line) && !check_border_line(line, NULL))
	{
		if (line[0] == 'R' && line[1] == ' ')
		{
			mlx->params.resolution = parse_resolution(line);
			free(line);
		}
	}
	
	mlx->map = read_map(fd, line);
}
