/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:45 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/03 22:15:50 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void    build_map(t_data *img, char *argv, int p)
{
    int i;
    int x;
    int y;

    i = 0;
    x = 0;
    y = 0;
    while (argv[i] != '\0')
    {
        if (argv[i] == "1")
        {
            build_block(img, x, y, p, 0xDDFFCC99);
            x = x + p;
        }
        i++;
    }
}

int main(int argc, char **argv)
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
    
    build_map(&img, argv[1], 100);

    build_block(&img, 0, 0, 100, 0xDDFFCC99);
    build_block(&img, 100, 0, 100, 0xDDFFCC99);

    build_player(&img);

    mlx_hook(img.win, 2, 1L<<0, key_print, &img);
    mlx_loop(img.mlx);
}