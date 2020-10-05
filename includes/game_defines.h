/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_defines.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:03:20 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/05 18:43:55 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_DEFINES_H
# define GAME_DEFINES_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "mlx.h"

# define mapWidth        24
# define mapHeight       24
# define screenWidth     640
# define screenHeight    480

# define KEY_LEFT        65361
# define KEY_RIGHT       65363
# define KEY_DOWN		65364
# define KEY_UP			65362

typedef struct	s_img
{
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	void		*img_ptr;
}				t_img;

typedef struct	s_line
{
	int			start;
	int			end;
}				t_line;

typedef struct	s_mapvector
{
	int			x;
	int			y;
}				t_mapvector;

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct	s_params
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	raydir;
	t_vector	sidedist;
	t_vector	deltadist;
	t_mapvector	posmap;
	t_mapvector	step;
}				t_params;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
	t_params	params;
}				t_mlx;

t_mapvector	calculate_step_sidedist(t_params *params);
int			digital_differential_alg(t_params *params);
int			close_event(void *param);
int			deal_key(int key, void *param);
int			main_loop(t_mlx *mlx);
void		rotate(t_params *params, double degree);
void		walk(t_params *params, double step);
int			color_walls(t_params params, int side);
void		calculate_params(t_params *params, int count_w);
t_line		calculate_line_area(t_params *params, int side);
int worldMap[mapWidth][mapHeight];

#endif
