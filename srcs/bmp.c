/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:32:50 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/19 16:13:11 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

static void	int_in_string(unsigned char *str, int n)
{
	str[0] = (unsigned char)(n);
	str[1] = (unsigned char)(n >> 8);
	str[2] = (unsigned char)(n >> 16);
	str[3] = (unsigned char)(n >> 24);
}

static int	get_color(t_mlx mlx, int x, int y)
{
	int	c;

	c = *(int *)(mlx.img.img_ptr + (4 * mlx.params.res.x * (mlx.params.res.y\
		- 1 - y)) + (4 * x));
	return ((c & 0xFF0000) | (c & 0x00FF00) | (c & 0x0000FF));
}

static int	write_header(int fd, int size, t_params params)
{
	int				i;
	unsigned char	fileheader[54];

	ft_bzero(fileheader, 54);
	fileheader[0] = (unsigned char)('B');
	fileheader[1] = (unsigned char)('M');
	int_in_string(fileheader + 2, size);
	fileheader[10] = (unsigned char)(54);
	fileheader[14] = (unsigned char)(40);
	int_in_string(fileheader + 18, params.pos.x);
	int_in_string(fileheader + 22, params.pos.y);
	fileheader[27] = (unsigned char)(1);
	fileheader[28] = (unsigned char)(24);
	if (write(fd, fileheader, 54) < 0)
		return (0);
	return (1);
}

static int	write_data(int fd, t_mlx mlx, int padding)
{
	int					i;
	int					j;
	int					color;
	const unsigned char bmppad[3];

	i = -1;
	ft_bzero(bmppad, 3);
	while (++i < mlx.params.res.y)
	{
		j = -1;
		while (++j < mlx.params.res.x)
		{
			color = get_color(mlx, j, i);
			if (write(fd, &color, 3) < 0)
				return (0);
			if (padding > 0 && write(fd, &bmppad, padding))
				return (0);
		}
	}
	return (1);
}

int			save_screen(t_mlx mlx)
{
	int		fd;
	int		padding;
	int		filesize;

	padding = (4 - (mlx.params.res.x * 3) % 4) % 4;
	filesize = 54 + (3 * (mlx.params.res.x + padding) * mlx.params.res.y);
	if ((fd = open("fordeepthout.bmp", O_WRONLY | O_TRUNC | O_APPEND\
	| O_CREAT)) < 0)
		return (0);
	if (!write_header(fd, filesize, mlx.params))
		return (0);
	if (!write_data(fd, mlx, padding))
		return (0);
	close(fd);
	return (1);
}
