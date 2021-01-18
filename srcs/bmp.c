/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:32:50 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/18 17:24:07 by mbouzaie         ###   ########.fr       */
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
		return (1);
	return(0);
}

static int	write_data(int file, t_mlx mlx)
{
	return (0);
}