/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:37:54 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/15 17:35:23 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

int		close_event(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	if (mlx->img.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	clear_textures(mlx);
	exit(0);
	return (0);
}

int		deal_key(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == KEY_RIGHT)
		rotate(&mlx->params, -0.33);
	if (key == KEY_LEFT)
		rotate(&mlx->params, 0.33);
	if (key == KEY_UP)
		walk(&mlx->params, 0.5, mlx->map);
	if (key == KEY_DOWN)
		walk(&mlx->params, -1, mlx->map);
	return (0);
}

int		createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void	sort_sprites(int *order, double *dist, int amount)
{
	int		i;
	int		j;
	int		tmporder;
	double	tmpdist;

	i = amount - 1;
	
	while (i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (dist[j] < dist[j + 1])
			{
				tmpdist = dist[j];
				tmporder = order[j];
				dist[j] = dist[j + 1];
				order[j] = order[j + 1];
				dist[j + 1] = tmpdist;
				order[j + 1] = tmporder;
			}
			j++;
		}
		i--;
	}
}

t_list	*get_stripes_coords(t_list *map)
{
	int			i;
	int			j;
	char		*mapline;
	t_list		*sprites;
	t_intvector	*sprite;

	i = 0;
	sprites = NULL;
	while (map != NULL)
	{
		j= 0;
		mapline = (char *)map->content;
		while (mapline[j] != '\0')
			{
				if (mapline[j] == '2')
				{
					sprite = (t_intvector *)malloc(sizeof(t_intvector) + 1);
					sprite->x = i;
					sprite->y = j;
					ft_lstadd_back(&sprites, ft_lstnew(sprite));
				}
				j++;
			}
		i++;
		map = map->next;
	}
	return (sprites);
}

int		main_loop(t_mlx *mlx)
{
	int			count_w;
	int			count_h;
	int			side;
	int			color;
	int			cardinal;
	t_line		line;
	t_params	params;
	double		wallX;
	t_intvector	texPos;
	double		step;
	double		texPosd;
	double		zbuffer[mlx->params.resolution.x];
	int			*spriteOrder;
	int			i;
	double		*spriteDistance;
	double		spriteX;
	double		spriteY;
	double		invDet;
	double		transformX;
	double		transformY;
	int			spriteScreenX;
	int			vMoveScreen;
	int			spriteWidth;
	int			spriteHeight;
	int			drawStartY;
	int			drawStartX;
	int			drawEndY;
	int			drawEndX;
	int			d;
	int			spritessize;
	t_intvector	*sprite;

	count_w = -1;
	params = mlx->params;
    while (++count_w < params.resolution.x)
	{
		calculate_params(&params, count_w);
		calculate_step_sidedist(&params);
		side = digital_differential_alg(&params, mlx->map);
		line = calculate_stripe_borders(&params, side);
		count_h = -1;
		if (side == 0)
			wallX = params.pos.y + params.perpWallDist * params.raydir.y;
		else
			wallX = params.pos.x + params.perpWallDist * params.raydir.x;
		wallX -= floor(wallX);
		if (side == 0 && params.raydir.x > 0)
			cardinal = SOUTH;
		if (side == 0 && params.raydir.x < 0)
			cardinal = NORTH;
		if (side == 1 && params.raydir.y > 0)
			cardinal = EAST;
		if (side == 1 && params.raydir.y < 0)
			cardinal = WEST;
		texPos.x = (int)(wallX * (double)mlx->tex[cardinal].width);
		if (side == 0 && params.raydir.x > 0)
			texPos.x = mlx->tex[cardinal].width - texPos.x - 1;
		if (side == 1 && params.raydir.y < 0)
			texPos.x= mlx->tex[cardinal].width - texPos.x - 1;
		step = 1.0 * mlx->tex[cardinal].height / params.lineHeight;
		texPosd = (line.start - count_h / 2 + params.lineHeight / 2) * step;
		while (++count_h < params.resolution.y)
			if (count_h > line.end)
                mlx->img.data[count_h * params.resolution.x + count_w] = createRGB(mlx->floor.r, mlx->floor.g, mlx->floor.b);
			else if (count_h < line.start)
				mlx->img.data[count_h * params.resolution.x + count_w] = createRGB(mlx->ceiling.r, mlx->ceiling.g, mlx->ceiling.b);
            else
			{
				texPos.y = (int)texPosd & (mlx->tex[cardinal].height - 1);
				texPosd += step;
                mlx->img.data[count_h * params.resolution.x + count_w] = get_pixel_color(mlx->tex[cardinal], texPos);
			}
		zbuffer[count_w] = params.perpWallDist;
	}
	i = 0;
	spritessize = ft_lstsize(mlx->sprites);
	spriteOrder = (int *) malloc(sizeof(int) * spritessize + 1);
	spriteDistance = (double *) malloc(sizeof(double) * spritessize + 1);
	while (i < spritessize)
	{
		sprite = (t_intvector *)ft_lstfind_index(mlx->sprites, i);
		spriteOrder[i] = i;
		spriteDistance[i] = (params.pos.x - sprite->x) * (params.pos.x - sprite->x) + (params.pos.y - sprite->y) * (params.pos.y - sprite->y);
		i++;
	}
	sort_sprites(spriteOrder, spriteDistance, spritessize);
	i = 0;
	while (i < spritessize)
	{
		sprite = (t_intvector *)ft_lstfind_index(mlx->sprites, spriteOrder[i]);
		spriteX = sprite->x - params.pos.x + .5;
		spriteY = sprite->y - params.pos.y + .5;
		invDet = 1.0 / (params.plane.x * params.dir.y - params.dir.x * params.plane.y);
		transformX = invDet * (params.dir.y * spriteX - params.dir.x * spriteY);
		transformY = invDet * (-params.plane.y * spriteX + params.plane.x * spriteY);
		spriteScreenX = (int)((params.resolution.x / 2) * (1 + transformX / transformY));
		vMoveScreen = (int)(0.0 / transformY);
		spriteHeight = (int)fabs((params.resolution.y / transformY) / 1);
		drawStartY = -spriteHeight / 2 + params.resolution.y / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		drawEndY = spriteHeight / 2 + params.resolution.y / 2 + vMoveScreen;
		if (drawEndY >= params.resolution.y)
			drawEndY = params.resolution.y - 1;
		spriteWidth = (int)fabs((params.resolution.x / transformY) / 1);
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= params.resolution.x)
			drawEndX = params.resolution.x - 1;
		count_w = drawStartX - 1;
		while (++count_w < drawEndX)
		{
			texPos.x = (int)((256 * (count_w - (-spriteWidth / 2 + spriteScreenX)) * mlx->tex[SPRITE].width / spriteWidth) / 256);
			if (transformY > 0 && count_w > 0 && count_w < params.resolution.x && transformY < zbuffer[count_w])
			{
				count_h = drawStartY - 1;
				while (++count_h < drawEndY)
				{
					d = (count_h - vMoveScreen) * 256 - params.resolution.y * 128 + spriteHeight * 128;
					texPos.y = ((d * mlx->tex[SPRITE].height) / spriteHeight ) / 256;
					color = get_pixel_color(mlx->tex[SPRITE], texPos);
					if ((color & 0x00FFFFFF) != 0)
						mlx->img.data[count_h * params.resolution.x + count_w] = color;
				}
			}
		}
		i++;
	}
	free(spriteOrder);
	free(spriteDistance);
	//ft_lstclear(&sprites, &free);
	mlx->params = params;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	return (0);
}
