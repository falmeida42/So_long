/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:45 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/04 19:57:26 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    build_player(t_data *img)
{
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    img->img = mlx_xpm_file_to_image(img->mlx, img->relative_path, &img->img_width, &img->img_height);
    mlx_put_image_to_window(img->mlx, img->win, img->img, img->x, img->y);
}

void    build_floor(t_data *img)
{
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    img->img = mlx_xpm_file_to_image(img->mlx, img->floor, &img->img_width, &img->img_height);
    mlx_put_image_to_window(img->mlx, img->win, img->img, img->floorx, img->floory);
}

void    build_wall(t_data *img)
{
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    img->img = mlx_xpm_file_to_image(img->mlx, img->wall, &img->img_width, &img->img_height);
    mlx_put_image_to_window(img->mlx, img->win, img->img, img->floorx, img->floory);
}

int    key_print(int key, t_data *img)
{
    if (key == UP)
    {
        img->y -= 100;
        build_player(img);
    }
    else if (key == DOWN)
    {
        img->y += 100;
        build_player(img);
    }
    else if (key == LEFT)
    {
        img->x -= 100;
        build_player(img);
    }
    else if (key == RIGHT)
    {
        img->x += 100;
        build_player(img);
    }
    return (0);
}

void    build_map(t_data *img, char **map, int p)
{
    int i;
    int j;

    i = 0;
    j = 0;
      while (i < 10)
    {
        j = 0;
        img->floorx = 20;
        while (j < 18)
        {
            if (map[i][j] == '1')
            {
                //build_block(img, x, y, p, 0xDDFFCC00);
                build_floor(img);
            }
            img->floorx = img->floorx + p;
            j++;
        }
        img->floory = img->floory + p;
        i++;
    }
}

int main(void)
{
    t_data  img;
    int     img_width;
    int     img_height;
    char    **map;
    int     i;
    int     j;

    img.floorx = 20;
    img.floory = 20;
    img.x = 460;
    img.y = 270;
    img.relative_path = "./zombie.xpm";
    img.floor = "./wood.xpm";
    img.wall = "./wall.xpm";
    
    img.mlx = mlx_init();

    img.win = mlx_new_window(img.mlx, 1920, 1080, "So Long");
    img.img = mlx_new_image(img.mlx, 1920, 1080);
    
    map = (char **)malloc(10 * sizeof(char *) + 1);
    i = 0;
    while (i < 18)
    {
        map[i] = (char *)malloc(17 * sizeof(char) + 2);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        j = 0;
        while (j < 18)
        {
            map[i][j] = '1';
            j++;
        }
        i++;
    }

    build_map(&img, map, 100);

    build_player(&img);

    mlx_hook(img.win, 2, 1L<<0, key_print, &img);
    mlx_loop(img.mlx);
}