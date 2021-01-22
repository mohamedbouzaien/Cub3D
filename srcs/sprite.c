/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 23:28:09 by mbouzaie          #+#    #+#             */
/*   Updated: 2021/01/22 18:05:47 by mbouzaie         ###   ########.fr       */
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
				ft_lstadd_back(&sprites, ft_vectlstnew(sprite));
			}
		}
		i++;
		map = map->next;
	}
	return (sprites);
}

void	draw_sprites(t_mlx *mlx, t_sprite sprite)
{
	int			d;
	int			c;
	t_intvector	count;
	t_intvector	texpos;

	count.x = sprite.drawstart.x - 1;
	while (++count.x < sprite.drawend.x)
	{
		texpos.x = (int)((256 * (count.x - (-sprite.size.x / 2 +\
			sprite.screenx)) * mlx->tex[SPRITE].width / sprite.size.x) / 256);
		if (sprite.transform.y > 0 && count.x > 0 && count.x <\
		mlx->params.res.x && sprite.transform.y < mlx->params.zbuffer[count.x])
		{
			count.y = sprite.drawstart.y - 1;
			while (++count.y < sprite.drawend.y)
			{
				d = count.y * 256 - (mlx->params.res.y - sprite.size.y) * 128;
				texpos.y = ((d * mlx->tex[SPRITE].height) / sprite.size.y)\
					/ 256;
				c = get_pixel_color(mlx->tex[SPRITE], texpos);
				if ((c & 0x00FFFFFF) != 0)
					mlx->img.data[count.y * mlx->params.res.x + count.x] = c;
			}
		}
	}
}

void	init_draw(t_sprite *s, t_params p, t_list *sprites, int i)
{
	double		id;
	t_intvector	*pos;

	pos = (t_intvector *)(ft_lstfind_index(sprites, s->order[i])->content);
	s->pos.x = pos->x - p.pos.x + .5;
	s->pos.y = pos->y - p.pos.y + .5;
	id = 1.0 / (p.plane.x * p.dir.y - p.dir.x * p.plane.y);
	s->transform.x = id * (p.dir.y * s->pos.x - p.dir.x * s->pos.y);
	s->transform.y = id * (-p.plane.y * s->pos.x + p.plane.x * s->pos.y);
	s->screenx = (int)((p.res.x / 2) * (1 + s->transform.x / s->transform.y));
	s->size.y = (int)fabs((p.res.y / s->transform.y) / 1);
	s->drawstart.y = -s->size.y / 2 + p.res.y / 2;
	if (s->drawstart.y < 0)
		s->drawstart.y = 0;
	s->drawend.y = s->size.y / 2 + p.res.y / 2;
	if (s->drawend.y >= p.res.y)
		s->drawend.y = p.res.y - 1;
	s->size.x = (int)fabs((p.res.x / s->transform.y) / 1);
	s->drawstart.x = -s->size.x / 2 + s->screenx;
	if (s->drawstart.x < 0)
		s->drawstart.x = 0;
	s->drawend.x = s->size.x / 2 + s->screenx;
	if (s->drawend.x >= p.res.x)
		s->drawend.x = p.res.x - 1;
}

void	handle_sprites(t_mlx *mlx)
{
	int			i;
	t_intvector	*pos;
	t_params	p;
	t_sprite	sprite;

	p = mlx->params;
	i = -1;
	sprite.listsize = ft_lstsize(mlx->sprites);
	sprite.order = (int *)malloc(sizeof(int) * sprite.listsize + 1);
	sprite.dists = (double *)malloc(sizeof(double) * sprite.listsize + 1);
	while (++i < sprite.listsize)
	{
		pos = (t_intvector *)(ft_lstfind_index(mlx->sprites, i)->content);
		sprite.order[i] = i;
		sprite.dists[i] = pow(p.pos.x - pos->x, 2) + pow(p.pos.y - pos->y, 2);
	}
	sort_sprites(sprite.order, sprite.dists, sprite.listsize);
	i = -1;
	while (++i < sprite.listsize)
	{
		init_draw(&sprite, p, mlx->sprites, i);
		draw_sprites(mlx, sprite);
	}
	free(sprite.order);
	free(sprite.dists);
}
