/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:13:40 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/15 20:41:14 by mbouzaie         ###   ########.fr       */
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

t_list		*read_map(char *file_path)
{
	t_list	*map;
	t_list	*new;
	int		fd;
	int		i;
	char	*line;

	fd = open(file_path, O_RDONLY);
	i = 1;
	map = NULL;
	while (ft_get_next_line(fd, &line))
		ft_lstadd_back(&map, ft_lstnew(line));
	if ( ft_strlen(line) > 0)
		ft_lstadd_back(&map, ft_lstnew(line));
	close(fd);
	return (map);
}