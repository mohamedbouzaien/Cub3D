/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 23:28:09 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/18 00:34:13 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game_defines.h"

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

t_list	*get_sprites_coords(t_list *map)
{
	int			i;
	int			j;
	t_list		*sprites;
	t_intvector	*sprite;

	i = 0;
	sprites = NULL;
	while (map != NULL)
	{
		j = -1;
		while (((char *)map->content)[++j] != '\0')
		{
			if (((char *)map->content)[j] == '2')
			{
				sprite = (t_intvector *)malloc(sizeof(t_intvector) + 1);
				sprite->x = i;
				sprite->y = j;
				ft_lstadd_back(&sprites, ft_lstnew(sprite));
			}
		}
		i++;
		map = map->next;
	}
	return (sprites);
}

void	draw_sprites(t_mlx *mlx)
{
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
	t_params	params;
	t_intvector	texPos;
	int			color;
	int			count_w;
	int			count_h;

	params = mlx->params;
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
		sprite = (t_intvector *)(ft_lstfind_index(mlx->sprites, spriteOrder[i])->content);
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
			if (transformY > 0 && count_w > 0 && count_w < params.resolution.x && transformY < params.zbuffer[count_w])
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
}
