/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:45 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/03 21:08:46 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;

    char    *relative_path;
    int     img_width;
    int     img_height;
    int x;
    int y;

    
}               t_data;

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

void    build_block(t_data *img, int x, int y, int color)
{
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    mlx_block(img, x, y, 100, color);
    mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

void    build_player(t_data *img)
{
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    img->img = mlx_xpm_file_to_image(img->mlx, img->relative_path, &img->img_width, &img->img_height);
    mlx_put_image_to_window(img->mlx, img->win, img->img, img->x, img->y);
}

int    key_print(int key, t_data *img)
{
    if (key == UP)
    {
        img->y -= 20;
        build_player(img);
    }
    else if (key == DOWN)
    {
        img->y += 20;
        build_player(img);
    }
    else if (key == LEFT)
    {
        img->x -= 20;
        build_player(img);
    }
    else if (key == RIGHT)
    {
        img->x += 20;
        build_player(img);
    }
    return (0);
}

int main()
{
    t_data  img;
    t_data  img2;
    int     img_width;
    int     img_height;
    img.x = 460;
    img.y = 270;
    img.relative_path = "./zombie.xpm";

    img.mlx = mlx_init();

    img.win = mlx_new_window(img.mlx, 1920, 1080, "So Long");
    img.img = mlx_new_image(img.mlx, 1920, 1080);
    
    build_block(&img, 0, 0, 0xDDFFCC99);
    build_block(&img, 100, 0, 0xDDFFCC99);

    build_player(&img);

    mlx_hook(img.win, 2, 1L<<0, key_print, &img);
    mlx_loop(img.mlx);
}