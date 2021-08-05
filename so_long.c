/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:45 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/05 18:28:59 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    build_player(t_data *img)
{
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    img->img = mlx_xpm_file_to_image(img->mlx, img->player, &img->img_width, &img->img_height);
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
    mlx_put_image_to_window(img->mlx, img->win, img->img, img->wallx, img->wally);
}

void    build_door(t_data *img)
{
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    img->img = mlx_xpm_file_to_image(img->mlx, img->door, &img->img_width, &img->img_height);
    mlx_put_image_to_window(img->mlx, img->win, img->img, img->doorx, img->doory);
}

void    build_map(t_data *img)
{
    int i;
    int j;
    int     width;
    int     height;
    int     p;

    p = 100;
    width = 14;
    height = 7;

    static char map[7][14] = {
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '\0'},
        {'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'C', '1', '\0'},
        {'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '\0'},
        {'1', 'P', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '1', '\0'},
        {'1', '0', '0', '0', '1', '1', 'E', '0', '0', '0', '0', '0', '1', '\0'},
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '\0'},
        {'\0'}};
    /*
    map = (char **)malloc((height + 10) * sizeof(char *));
    i = 0;
    while (i < 18)
    {
        map[i] = (char *)malloc((width + 10) * sizeof(char));
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
            else if (i == height - 1 || j == width - 1)
                map[i][j] = '1';
            else if (j == 0)
                map[i][j] = '1';
            else
                map[i][j] = '0';
            j++;
        }
        i++;
    }
    */
    i = 0;
    j = 0;
      while (i < height)
    {
        j = 0;
        img->wallx = 0;
        img->floorx = 0;
        img->x = 0;
        img->door = 0;
        while (j < width)
        {
            if (map[i][j] == '0')
                build_floor(img);
            else if (map[i][j] == '1')
                build_wall(img);
            else if (map[i][j] == 'P')
                build_player(img);
            else if (map[i][j] == 'E')
            {
                build_door(img);
            }
            img->floorx = img->floorx + p;
            img->wallx = img->wallx + p;
            img->x = img->x + p;
            img->doorx = img->doorx + p;
            j++;
        }
        img->floory = img->floory + p;
        img->wally = img->wally + p;
        img->y = img->y + p;
        img->doory = img->doory + p;
        i++;
    }
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
    //build_map(img);
    return (0);
}

int main(void)
{
    t_data  img;
    int     img_width;
    int     img_height;
    int     i;
    int     j;
    int     width;
    int     height;
    width = 13;
    height = 6;
    img.floorx = 0;
    img.floory = 0;
    //img.x = 460;
    //img.y = 270;
    img.player = "./cowboy.xpm";
    img.floor = "./wood.xpm";
    img.wall = "./wall.xpm";
    img.door = "./door.xpm";
    img.addr = NULL;
    img.mlx = mlx_init();

    img.win = mlx_new_window(img.mlx, width * 100, height * 100, "So Long");
    img.img = mlx_new_image(img.mlx, 1920, 1080);

    build_map(&img);

    //build_player(&img);

    mlx_hook(img.win, 2, 1L<<0, key_print, &img);
    mlx_loop(img.mlx);
}