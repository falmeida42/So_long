/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 21:11:03 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/03 21:58:26 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    mlx_line(t_data *data, int x, int y, int p, int color)
{
    int xp;

    xp = x + p;
    while (x < xp)
    {
        my_mlx_pixel_put(data, x, y, color);
        x++;
    }
}

void    mlx_block(t_data *data, int x, int y, int p, int color)
{
    int yp;

    yp = y + p;
    while (y < yp)
    {
        mlx_line(data, x, y, p, color);
        y++;
    }
}

void    build_block(t_data *img, int x, int y, int p, int color)
{
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    mlx_block(img, x, y, p, color);
    mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}