/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_defines.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:03:20 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/28 17:52:32 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_DEFINES_H
# define GAME_DEFINES_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"

# define mapWidth		24
# define mapHeight		24

# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define KEY_DOWN		65364
# define KEY_UP			65362

# define NORTH			1
# define SOUTH			2
# define WEST			3
# define EAST			4

typedef struct	s_img
{
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	void		*img_ptr;
}				t_img;

typedef struct s_tex
{
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			width;
	int			height;
	char		*path;
	void		*tex_ptr;
}				t_tex;


typedef struct	s_line
{
	int			start;
	int			end;
}				t_line;

typedef struct	s_intvector
{
	int			x;
	int			y;
}				t_intvector;

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
	t_intvector	posmap;
	t_intvector	step;
	t_intvector	resolution;
	double		perpWallDist;
	int			lineHeight;
}				t_params;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
	t_tex		tex[4];
	t_params	params;
	t_list		*map;
}				t_mlx;

void		calculate_step_sidedist(t_params *params);
int			digital_differential_alg(t_params *params, t_list *map);
int			close_event(void *param);
int			deal_key(int key, void *param);
int			main_loop(t_mlx *mlx);
void		rotate(t_params *params, double degree);
void		walk(t_params *params, double step, t_list *map);
void		calculate_params(t_params *params, int count_w);
t_line		calculate_stripe_borders(t_params *params, int side);
int			get_pixel_color(t_tex tex, t_intvector pos);
t_tex		load_texture(t_mlx mlx);
void		parse_cub(char *file_path, t_mlx *mlx);
void		throw_error(char *msg);

#endif
