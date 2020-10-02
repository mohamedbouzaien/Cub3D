/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:10:46 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/02 11:30:41 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include "mlx.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

typedef struct s_img
{
    void    *img_ptr;
    int     *data;
    int     size_l;
    int     bpp;
    int     endian;
}              t_img;
typedef struct s_mapvector
{
	int		x;
	int		y;
}				t_mapvector;

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_params
{
	t_mapvector	posmap;
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	raydir;
	t_vector	sidedist;
	t_vector	deltadist;
}				t_params;

typedef struct s_mlx
{
    void    	*mlx_ptr;
    void    	*win;
    t_img   	img;
	t_params	params;
}               t_mlx;

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int     deal_key(int key, void *param)
{
	t_mlx *mlx;
	double oldDirX;
	double oldPlaneX;

	mlx = (t_mlx *)param;
    if (key == 65363)
	{
		oldDirX = mlx->params.dir.x;
		mlx->params.dir.x = mlx->params.dir.x * cosf(-0.33) - mlx->params.dir.y * sinf(-0.33);
		mlx->params.dir.y = oldDirX * sinf(-0.33) + mlx->params.dir.y * cosf(-0.33);
		oldPlaneX = mlx->params.plane.x;
		mlx->params.plane.x = mlx->params.plane.x * cosf(-0.33) - mlx->params.plane.y * sinf(-0.33);
		mlx->params.plane.y = oldPlaneX * sinf(-0.33) + mlx->params.plane.y * cosf(-0.33);
	}
	if (key == 65361)
	{
		oldDirX = mlx->params.dir.x;
		mlx->params.dir.x = mlx->params.dir.x * cosf(0.33) - mlx->params.dir.y * sinf(0.33);
		mlx->params.dir.y = oldDirX * sinf(0.33) + mlx->params.dir.y * cosf(0.33);
		oldPlaneX = mlx->params.plane.x;
		mlx->params.plane.x = mlx->params.plane.x * cosf(0.33) - mlx->params.plane.y * sinf(0.33);
		mlx->params.plane.y = oldPlaneX * sinf(0.33) + mlx->params.plane.y * cosf(0.33);
	}
	if (key == 65362)
	{
		if (worldMap[(int)(mlx->params.pos.x + mlx->params.dir.x * 1)][(int)mlx->params.pos.y] == 0)
			mlx->params.pos.x += mlx->params.dir.x * 1;
		if (worldMap[(int)mlx->params.pos.x][(int)(mlx->params.pos.y + mlx->params.dir.y * 1)] == 0)
			mlx->params.pos.y += mlx->params.dir.y * 1;			
	}
	if (key == 65364)
	{
		if (worldMap[(int)(mlx->params.pos.x - mlx->params.dir.x * 1)][(int)mlx->params.pos.y] == 0)
			mlx->params.pos.x -= mlx->params.dir.x * 1;
		if (worldMap[(int)mlx->params.pos.x][(int)(mlx->params.pos.y - mlx->params.dir.y * 1)] == 0)
			mlx->params.pos.y -= mlx->params.dir.y * 1;			
	}
    return(0);
}

int close_event(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	//if (mlx->img.img_ptr)
	//	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
    if(mlx->win)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	return (0);
}

int	digital_differential_alg(t_params *params, t_mapvector step)
{
	int hit;
	int side;

	hit = 0;
	while (hit == 0)
	{
		if (params->sidedist.x < params->sidedist.y)
		{
			params->sidedist.x += params->deltadist.x;
			params->posmap.x += step.x;
			side = 0;
		}
		else
		{
			params->sidedist.y += params->deltadist.y;
			params->posmap.y += step.y;
			side = 1;
		}
		if (worldMap[params->posmap.x][params->posmap.y] > 0)
			hit = 1;
	}
	return (side);
}

t_mapvector calculate_step_sidedist(t_params *params)
{
	t_mapvector step;
	
	if (params->raydir.x< 0)
	{
		step.x = -1;
		params->sidedist.x = (params->pos.x - params->posmap.x) * params->deltadist.x;
	}
	else
	{
		step.x = 1;
		params->sidedist.x = (params->posmap.x + 1.0 - params->pos.x) * params->deltadist.x;
	}
	if (params->raydir.y < 0)
	{
		step.y = -1;
		params->sidedist.y = (params->pos.y - params->posmap.y) * params->deltadist.y;
	}
	else
	{
		step.y = 1;
		params->sidedist.y = (params->posmap.y + 1.0 - params->pos.y ) * params->deltadist.y;
	}
	return (step);
}

int		color_walls(t_params params, int side)
{
	int	color;

	switch(worldMap[params.posmap.x][params.posmap.y])
	{
		case 1:  color = 0xFF0000;  break;
		case 2:  color = 0x008000;  break;
		case 3:  color = 0x00FFFF;   break;
		case 4:  color = 0xFFFFFF;  break;
		default: color = 0xFFFF00; break;
	}
	if (side == 1)
		color = color / 2;
	return (color);
}

int		main_loop(t_mlx *mlx)
{
	double  time;
    double  oldTime;
	int     count_w;
	int     count_h;
	double	cameraX;
	double	perpWallDist;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	t_params	params;
	t_mapvector	step;

    time = 0;
    oldTime = 0;
	count_w = -1;
	params = mlx->params;
    while (++count_w < screenWidth)
	{
		cameraX = 2 * count_w / (double)screenWidth - 1;
		params.raydir.x = params.dir.x + params.plane.x * cameraX;
		params.raydir.y = params.dir.y + params.plane.y * cameraX;
		params.posmap.x = (int)params.pos.x;
		params.posmap.y = (int)params.pos.y;
		params.deltadist.x = (params.raydir.y == 0) ? 0 : ((params.raydir.x == 0) ? 1 : fabs(1 / params.raydir.x));
		params.deltadist.y = (params.raydir.x == 0) ? 0 : ((params.raydir.y == 0) ? 1 : fabs(1 / params.raydir.y));
		step = calculate_step_sidedist(&params);
		side = digital_differential_alg(&params, step);
		if (side == 0)
			perpWallDist = (params.posmap.x - params.pos.x + (1 - step.x) / 2) / params.raydir.x;
		else
			perpWallDist = (params.posmap.y - params.pos.y + (1 - step.y) / 2) / params.raydir.y;
		lineHeight = (int) (screenHeight / perpWallDist);
		drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		count_h = -1;
		color = color_walls(params,side);
		while (++count_h < screenHeight)
    	{
			if (count_h < drawStart || count_h > drawEnd)
                mlx->img.data[count_h * screenWidth + count_w] = 0x000000;
            else
                mlx->img.data[count_h * screenWidth + count_w] = color;
		}
	}
	mlx->params = params;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	return (0);
}
t_params	init_params()
{
	t_params params;

	params.pos.x = 22;
    params.pos.y = 12;
    params.dir.x = -1;
    params.dir.y = 0;
    params.plane.x = 0;
    params.plane.y = 0.66;
	return(params);
}
int     main()
{
    t_mlx   mlx;

    mlx.mlx_ptr = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx_ptr, screenWidth, screenHeight, "Wolfstein3D");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, screenWidth, screenHeight);
    mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l,
                    &mlx.img.endian);
	mlx.params = init_params();
	mlx_hook(mlx.win, 2, 1L << 0, deal_key, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &main_loop, &mlx);
	mlx_hook(mlx.win, 17, 1L << 17, close_event, &mlx);
    mlx_loop(mlx.mlx_ptr);
	return (0);
}