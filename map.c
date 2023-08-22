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
	printf("Moviments %d\n", img->index);
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == 'C')
		img->bag--;
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == 'E') {
		check_exit(img, map, pi, pj);
	}
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == '1'
		|| map[pi + img->playerx / 100][pj + img->playery / 100]
			== 'E' && img->bag > 0)
		return ;
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
	if (map[i][j] == '1')
		draw_image(img, img->wall, i, j);
	else if (map[i][j] == 'P')
		draw_image(img, img->player, i, j);
	else if (map[i][j] == 'C')
		draw_image(img, img->collect, i, j);
	else if (map[i][j] == 'E')
		draw_image(img, img->door, i, j);
	else if (map[i][j] == '0')
	{
		draw_image(img, img->floor, i, j);
	}
	else
	{
		draw_image(img, img->floor, i, j);
		printf("Error\nInvalid caracther\n");
		close_win(img);
	}
	
}

void 	draw_you_win_text(t_data *img, char **map)
{
	mlx_string_put(img->mlx, img->win, 100, 100, 0x00FF0000, "You Win!");
}


void	draw_image_in_all_window(t_data *img, char *image, char **map)
{
	int i = 0;
	int j = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			draw_image(img, img->floor, i, j);
			j++;
		}
		i++;
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
	if (img->you_win == true)
		return;
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

void	draw_you_win(t_data *img, char **map)
{
	draw_image_in_all_window(img, img->floor, map);
	draw_you_win_text(img, map);
}


int	main_loop(int key, t_data *img)
{

		
	printf("%d", key);
	img->playerx = 0;
	img->playery = 0;
	if (key == ESC)
		close_win(img);
	if (img->you_win == true)
		return (1);

	if (key == W)
		img->playerx = -100;
	else if (key == S)
		img->playerx = 100;
	else if (key == A)
		img->playery = -100;
	else if (key == D)
		img->playery = 100;
	else
		return (-1);
	
	build_map(img);
	return (0);
}
