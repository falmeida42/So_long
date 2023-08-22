/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 20:47:19 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/20 18:39:28 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	conditions_change_map(t_data *img, char **map, int pi, int pj)
{
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == 'C')
		img->bag--;
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == 'E')
		check_exit(img, map, pi, pj);
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == '1'
		|| map[pi + img->playerx / 100][pj + img->playery / 100]
			== 'E' && img->bag > 0)
		return ;
	printf("Moviments %d\n", img->index);
	img->index++;
	map[pi][pj] = '0';
	map[pi + img->playerx / 100][pj + img->playery / 100] = 'P';
}

void	change_map(t_data *img, char **map)
{
	int	i;
	int	j;
	int	pi;
	int	pj;

	img->bag = count_bag(img, map);
	i = 0;
	while (i < img->size_y)
	{
		j = 0;
		while (j < img->size_x)
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
	conditions_change_map(img, map, pi, pj);
}

void	conditions_build_map(t_data *img, char **map, int i, int j)
{
	draw_image(img, img->floor, i, j);
	if (map[i][j] == '1')
		draw_image(img, img->wall, i, j);
	else if (map[i][j] == 'P')
		draw_image(img, img->player, i, j);
	else if (map[i][j] == 'C')
		draw_image(img, img->collect, i, j);
	else if (map[i][j] == 'E')
		draw_image(img, img->door, i, j);
	else if (map[i][j] != '0')
	{
		printf("Error\nInvalid caracther\n");
		close_win(img);
	}
}

void	build_map(t_data *img)
{
	int		i;
	int		j;
	int		p;
	char	**map;

	p = 100;
	map = img->map;
	change_map(img, map);
	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			conditions_build_map(img, map, i, j);
			j++;
		}
		i++;
	}
}

int	key_print(int key, t_data *img)
{

	img->playerx = 0;
	img->playery = 0;
	if (key == ESC)
		close_win(img);
	if (key == W)
		img->playerx = -100;
	else if (key == S)
		img->playerx = 100;
	else if (key == A)
		img->playery = -100;
	else if (key == D) {
		printf("inside\n");
		img->playery = 100;
	}
		
	else
		return (-1);
	build_map(img);
	return (0);
}
