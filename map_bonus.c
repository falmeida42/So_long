/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 20:47:19 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/20 18:39:34 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == 'Z')
		zombie(img);
	img->moviment = img->index;
	img->index++;
	map[pi][pj] = '0';
	map[pi + img->playerx / 100][pj + img->playery / 100] = 'P';
}

void	change_map(t_data *img, char **map)
{
	int	i;
	int	j;

	img->bag = count_bag(img, map);
	i = 0;
	while (i < img->size_y)
	{
		j = 0;
		while (j < img->size_x)
		{
			if (map[i][j] == 'P')
			{
				img->pi = i;
				img->pj = j;
			}
			if (map[i][j] == 'Z')
			{
				img->piz = i;
				img->pjz = j;
			}
			j++;
		}
		i++;
	}
	conditions_change_map(img, map, img->pi, img->pj);
}

void	conditions_build_map(t_data *img, char **map, int i, int j)
{
	char	*num;

	num = ft_itoa(img->moviment);
	draw_image(img, img->floor, i, j);
	if (map[i][j] == '1')
		draw_image(img, img->wall, i, j);
	else if (map[i][j] == 'P')
		draw_image(img, img->player, i, j);
	else if (map[i][j] == 'C')
		draw_image(img, img->collect, i, j);
	else if (map[i][j] == 'E')
		draw_image(img, img->door, i, j);
	else if (map[i][j] == 'Z')
		draw_image(img, img->zombie, i, j);
	else if (map[i][j] != '0')
	{
		printf("Error\nInvalid caracther\n");
		close_win(img);
	}
	mlx_string_put(img->mlx, img->win, 50, 50, 0xFFFFFF, num);
	free(num);
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
	while (i < img->size_y)
	{
		j = 0;
		while (j < img->size_x)
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
	img->player = "./cowboy.xpm";
	if (key == W)
	{
		img->player = "./cowboy_back.xpm";
		img->playerx = -100;
	}
	else if (key == S)
		img->playerx = 100;
	else if (key == A)
		img->playery = -100;
	else if (key == D)
		img->playery = 100;
	else
		return (-1);
	zombie_mov(img, img->map);
	build_map(img);
	return (0);
}
