/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:10:46 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/08/20 20:51:18 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include "mlx.h"

typedef struct s_img
{
    void    *img_ptr;
    int     *data;
    int     size_l;
    int     bpp;
    int     endian;
}              t_img;

typedef struct s_mlx
{
    void    *mlx_ptr;
    void    *win;
    t_img   img;
}               t_mlx;

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_params
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	raydir;
	t_vector	sidedist;
	t_vector	deltadist;
}				t_params;


void    ft_putchar(char c)
{
    write(1, &c, 1);
}

int     deal_key(int key, void *param)
{
    
    return(0);
}

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

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

int     main()
{
    double  time;
    double  oldTime;
	int     count_w;
	int     count_h;
	double	cameraX;
	int		mapX;
	int		mapY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
    t_mlx   mlx;
	t_params	params;

    mlx.mlx_ptr = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx_ptr, screenWidth, screenHeight, "Wolfstein3D");
    mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, screenWidth, screenHeight);
    mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l,
                    &mlx.img.endian);
    params.pos.x = 22;
    params.pos.y = 12;
    params.dir.x = -1;
    params.dir.y = 0;
    params.plane.x = 0;
    params.plane.y = 0.66;
    time = 0;
    oldTime = 0;
	count_w = -1;
    while (++count_w < screenWidth)
	{
		cameraX = 2 * count_w / (double)screenWidth - 1;
		params.raydir.x = params.dir.x + params.plane.x *cameraX;
		params.raydir.y = params.dir.y + params.plane.y * cameraX;
		mapX = (int)params.pos.x;
		mapY = (int)params.pos.y;
		params.deltadist.x = (params.raydir.y == 0) ? 0 : ((params.raydir.y == 0) ? 1 : fabs(1 / params.raydir.x));
		params.deltadist.y = (params.raydir.x == 0) ? 0 : ((params.raydir.y == 0) ? 1 : fabs(1 / params.raydir.y));
		hit = 0;
		if (params.raydir.x< 0)
		{
			stepX = -1;
			params.sidedist.x = (params.pos.x - mapX) * params.deltadist.x;
		}
		else
		{
			stepX = 1;
			params.sidedist.x = (mapX + 1.0 - params.pos.x) * params.deltadist.x;
		}
		if (params.raydir.y < 0)
		{
			stepY = -1;
			params.sidedist.y = (params.pos.y - mapY) * params.deltadist.y;
		}
		else
		{
			stepY = 1;
			params.sidedist.y = (mapY + 1.0 - params.pos.y ) * params.deltadist.y;
		}
		while (hit == 0)
		{
			if (params.sidedist.x < params.sidedist.y)
			{
				params.sidedist.x += params.deltadist.x;
				mapX += stepX;
				side = 0;
			}
			else
			{
				params.sidedist.y += params.deltadist.y;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - params.pos.x + (1 - stepX) / 2) / params.raydir.x;
		else
			perpWallDist = (mapY - params.pos.x + (1 - stepY) / 2) / params.raydir.y;
		lineHeight = (int) (screenHeight / perpWallDist);
		drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		count_h = -1;
		switch(worldMap[mapX][mapY])
      {
        case 1:  color = 0xFF0000;  break;
        case 2:  color = 0x008000;  break;
        case 3:  color = 0x00FFFF;   break;
        case 4:  color = 0xFFFFFF;  break;
        default: color = 0xFFFF00; break;
      }
      //if (side == 1) {color = color / 2;}
		while (++count_h < screenHeight)
    	{
			if (count_h < drawStart || count_h > drawEnd)
                mlx.img.data[count_h * screenWidth + count_w] = 0x000000;
            else
                mlx.img.data[count_h * screenWidth + count_w] = color;
		}
	}
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
    //mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0x222222);
    mlx_key_hook(mlx.win, deal_key, (void *)0);
    mlx_loop(mlx.mlx_ptr);
	return (0);
}