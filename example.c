/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 17:05:45 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/08/19 17:37:00 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
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

int     main(void)
{
    t_mlx   mlx;
    int     count_w;
    int     count_h;

    count_h = -1;
    mlx.mlx_ptr = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx_ptr, 800, 600, "thank u keuhdall");
    mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, 800, 600);
    mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l,
                    &mlx.img.endian);
    while (++count_h < 600)
    {
        count_w = -1;
        while (++count_w < 800)
        {
            if (count_w % 2)
                mlx.img.data[count_h * 800 + count_w] = 0xFFFFFF;
            else
                mlx.img.data[count_h * 800 + count_w] = 0;
        }
    }
    mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
    mlx_loop(mlx.mlx_ptr);
    return (0);
}

