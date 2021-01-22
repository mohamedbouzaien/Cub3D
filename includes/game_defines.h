/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_defines.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:03:20 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/22 18:05:33 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_DEFINES_H
# define GAME_DEFINES_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "../mlx/mlx.h"
# include "libft.h"

# define KEY_LEFT		65361//123
# define KEY_RIGHT		65363//124
# define KEY_DOWN		65364//125
# define KEY_UP			65362//126
# define KEY_W			119//13
# define KEY_A			97//0
# define KEY_S			115//1
# define KEY_D			100//2
# define KEY_ESC		65307//53

# define NORTH			1
# define SOUTH			2
# define WEST			3
# define EAST			4
# define SPRITE			5

# define AXIS_VERT		0
# define AXIS_HORI		1

# define SPEED_ROT		0.1
# define SPEED_MOV		0.3

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_img
{
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	void		*img_ptr;
}				t_img;

typedef struct	s_tex
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

typedef struct	s_sprite
{
	int			*order;
	int			listsize;
	int			screenx;
	double		*dists;
	t_vector	transform;
	t_vector	pos;
	t_intvector	size;
	t_intvector	drawstart;
	t_intvector	drawend;
}				t_sprite;

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
	t_intvector	res;
	double		perpwalldist;
	double		*zbuffer;
	int			lineheight;
	int			cardinal;
	int			save;
}				t_params;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
	t_tex		tex[6];
	t_color		floor;
	t_color		ceiling;
	t_params	params;
	t_list		*map;
	t_list		*sprites;
	int			spritessize;
}				t_mlx;

void			calculate_step_sidedist(t_params *params);
int				digital_differential_alg(t_params *params, t_list *map);
int				close_event(void *param);
int				deal_key(int key, void *param);
int				main_loop(t_mlx *mlx);
void			rotate(t_params *params, double degree);
void			walk(t_params *params, double step, int axis, t_list *map);
void			calculate_params(t_params *params, int count_w);
t_line			calculate_stripe_borders(t_params *params, int side);
int				get_pixel_color(t_tex tex, t_intvector pos);
int				load_textures(t_mlx *mlx);
void			parse_cub(char *file_path, t_mlx *mlx);
void			throw_error(char *msg);
int				is_dir_flag(char c);
void			clear_window(t_mlx *mlx);
void			clear_textures(t_mlx *mlx);
void			set_vector(t_vector *vector, double x, double y);
t_list			*get_sprites_coords(t_list *map);
void			sort_sprites(int *order, double *dist, int amount);
int				create_rgb(int r, int g, int b);
void			handle_sprites(t_mlx *mlx);
int				save_screen(t_mlx mlx);
int				check_texture_paths(t_tex tex[6]);
void			free_char_array(char **char_array);
t_list			*ft_strlstnew(char *content);
t_list			*ft_vectlstnew(t_intvector *content);
#endif
