/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 20:47:19 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/11 19:41:53 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	check_exit(t_data *img, char map[7][14], int pi, int pj)
{
	if (img->bag == 0)
	{
		write(1, "You Win!\n", 9);
		exit (0);
	}
}

int		count_bag(t_data *img, char map[7][14])
{
	int i;
	int j;
	int bag;

	bag = 0;
	i = 0;
	j = 0;
	while (i < 7)
	{
		j = 0;
		while (j < 14)
		{
			if (map[i][j] == 'C')
				bag++;
			j++;
		}
		i++;
	}
	return (bag);
}

void    change_map(t_data *img, char map[7][14])
{
	int i;
	int j;
	int pi;
	int pj;
	int result;
	int bag;

	bag = count_bag(img, map);
	img->bag = bag;
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
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == 'C')
		img->bag--;
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == 'E')
		check_exit(img, map, pi, pj);
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == '1' || map[pi + img->playerx / 100][pj + img->playery / 100] == 'E' && img->bag > 0)
		return ;
	map[pi][pj] = '0';
	map[pi + img->playerx / 100][pj + img->playery / 100] = 'P';
}

void    build_map(t_data *img)
{
	int i;
	int j;
	int     p;

	p = 100;
	static char map[7][14] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', 'P', '0', '1', '0', '0', '0', '0', '0', 'C', '0', 'C', '1', '1'},
		{'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1'},
		{'1', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '1', '1'},
		{'1', '0', '0', '0', '1', '1', 'E', '0', '0', '0', '0', '0', '1', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1'}};
	change_map(img, map);

	i = 0;
	  while (i < img->height)
	{
		j = 0;
		while (j < img->width)
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
	static int i;
	img->playerx = 0;
	img->playery = 0;
	if (key == ESC)
		exit(0);
	if (key == W)
		img->playerx = -100;
	else if (key == S)
		img->playerx = 100;
	else if (key == A)
		img->playery = -100;
	else if (key == D)
		img->playery = 100;
	build_map(img);
	i++;
	printf("Moviments: %d\n", i);
	return (0);
}