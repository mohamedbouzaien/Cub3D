/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:32:50 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/23 13:47:37 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

static	void	write_header(t_mlx mlx, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * mlx.params.res.x * mlx.params.res.y;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &mlx.params.res.x, 4);
	write(fd, &mlx.params.res.y, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &mlx.img.bpp, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

static int		write_data(int fd, t_mlx mlx)
{
	int	i;
	int	j;

	i = mlx.params.res.y + 1;
	while (--i >= 0)
	{
		j = -1;
		while (++j < mlx.params.res.x)
			if (write(fd, &mlx.img.data[i * mlx.img.size_l / 4 + j], 4) < 0)
				return (0);
	}
	return (1);
}

int				save_screen(t_mlx mlx)
{
	int		fd;

	if ((fd = open("fordeepthout.bmp", O_CREAT | O_RDWR)) < 0)
		return (0);
	write_header(mlx, fd);
	if (!write_data(fd, mlx))
		return (0);
	close(fd);
	return (1);
}
