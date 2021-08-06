/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:45 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/06 17:01:08 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int    close_win(t_data *img)
{
	(void)img;
	exit(0);
}

void    draw_image(t_data *img, char *image, int i, int j)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	img->img = mlx_xpm_file_to_image(img->mlx, image, &img->img_width, &img->img_height);
	mlx_put_image_to_window(img->mlx, img->win, img->img, j * 100, i * 100);
}

/*
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

void    build_collect(t_data *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	img->img = mlx_xpm_file_to_image(img->mlx, img->collect, &img->img_width, &img->img_height);
	mlx_put_image_to_window(img->mlx, img->win, img->img, img->collectx, img->collecty);
}
*/

void    change_map(t_data *img, char map[7][14])
{
	int i;
	int j;

	int pi;
	int pj;
	i = 0;

	while (i < 7)
	{
		j = 0;
		while (j < 14)
		{
			if (map[i][j] == 'P')
			{
				pi = i;
				pj = j;
			}
			j++;
		}
		i++;
	}
	map[pi][pj] = '0';
	map[pi + img->playerx / 100][pj + img->playery / 100] = 'P';
	img->playerx = 0;
	img->playery = 0;
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
	change_map(img, map);

	i = 0;
	j = 0;
	  while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == '0')
				draw_image(img, img->floor, i, j);
			else if (map[i][j] == '1')
				draw_image(img, img->wall, i, j);
			else if (map[i][j] == 'P')
				draw_image(img, img->player, i, j);
			else if (map[i][j] == 'C')
				draw_image(img, img->collect, i, j);
			else if (map[i][j] == 'E')
				draw_image(img, img->door, i, j);
			j++;
		}
		i++;
	}
}

int	key_print(int key, t_data *img)
{
	if (key == ESC)
		exit(0);
	if (key == W)
	{
		img->playerx = -100;
		//build_player(img);
	}
	else if (key == S)
	{
		img->playerx = 100;
		//build_player(img);
	}
	else if (key == A)
	{
		img->playery = -100;
		//build_player(img);
	}
	else if (key == D)
	{
		img->playery = 100;
		//build_player(img);
	}
	build_map(img);
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

	img.playerx = 0;
	img.playery = 0;

	img.player = "./cowboy.xpm";
	img.floor = "./wood.xpm";
	img.wall = "./wall.xpm";
	img.door = "./door.xpm";
	img.collect = "./collect.xpm";
	img.addr = NULL;
	img.mlx = mlx_init();

	img.win = mlx_new_window(img.mlx, width * 100, height * 100, "So Long");
	img.img = mlx_new_image(img.mlx, 1920, 1080);

	build_map(&img);
	mlx_hook(img.win, 2, 1L<<0, key_print, &img);
	mlx_hook(img.win, 17, 0, close_win, &img);
	mlx_loop(img.mlx);
}
