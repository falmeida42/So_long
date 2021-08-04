/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:45 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/04 21:19:29 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    build_player(t_data *img)
{
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    img->img = mlx_xpm_file_to_image(img->mlx, img->player, &img->img_width, &img->img_height);
    mlx_put_image_to_window(img->mlx, img->win, img->img, img->x, img->y);
}

void    build_floor(t_data *img, t_floor *floor)
{
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    img->img = mlx_xpm_file_to_image(img->mlx, floor->floor, &img->img_width, &img->img_height);
    mlx_put_image_to_window(img->mlx, img->win, img->img, floor->floorx, floor->floory);
}

void    build_wall(t_data *img, t_wall *wall)
{
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    img->img = mlx_xpm_file_to_image(img->mlx, wall->wall, &img->img_width, &img->img_height);
    mlx_put_image_to_window(img->mlx, img->win, img->img, wall->wallx, wall->wally);
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

void    build_map(t_data *img, t_floor *floor, t_wall *wall, char **map, int p, int width, int height)
{
    int i;
    int j;

    i = 0;
    j = 0;
      while (i < 10)
    {
        j = 0;
        floor->floorx = 0;
        while (j < 18)
        {
            if (map[i][j] == '0')
                build_floor(img, floor);
            else if (map[i][j] == '1')
                build_wall(img, wall);
            floor->floorx = floor->floorx + p;
            wall->wallx = wall->wallx + p;
            j++;
        }
        floor->floory = floor->floory + p;
        wall->wally = wall->wally + p;
        i++;
    }
}

int main(void)
{
    t_data  img;
    t_floor floor;
    t_wall  wall;
    int     img_width;
    int     img_height;
    char    **map;
    int     i;
    int     j;
    int     width;
    int     height;

    width = 16;
    height = 8;

    floor.floorx = 0;
    floor.floory = 0;
    img.x = 460;
    img.y = 270;
    img.player = "./zombie.xpm";
    floor.floor = "./wood.xpm";
    wall.wall = "./wall.xpm";
    
    img.mlx = mlx_init();

    img.win = mlx_new_window(img.mlx, width * 100, height * 100, "So Long");
    img.img = mlx_new_image(img.mlx, 1920, 1080);
    
    map = (char **)malloc(height * sizeof(char *) + 1);
    i = 0;
    while (i < 18)
    {
        map[i] = (char *)malloc(width * sizeof(char) + 1);
        i++;
    }
    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            if (i == 0)
                map[i][j] = '1';
            else
                map[i][j] = '0';
            j++;
        }
        i++;
    }

    build_map(&img, &floor, &wall, map, 100, width, height);

    build_player(&img);

    mlx_hook(img.win, 2, 1L<<0, key_print, &img);
    mlx_loop(img.mlx);
    free(map);
}