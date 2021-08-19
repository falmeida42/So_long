/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 20:47:19 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/19 22:17:03 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	zombie(t_data *img)
{
	printf("You Lose\n");
	close_win(img);
}

void	zombie_col(t_data *img, int pi, int pj)
{
	if (img->map[pi - 1][pj] == '0')
		img->map[pi - 1][pj] = 'Z';
	else if (img->map[pi + 1][pj] == '0')
		img->map[pi + 1][pj] = 'Z';
	img->map[pi][pj] = '0';
}

void	zombie_mov(t_data *img, char **map)
{
	int	pi;
	int	pj;
	static int	i;

	pi = img->piz;
	pj = img->pjz;
	if (map[pi][pj - 1] == '1' || map[pi][pj + '1'] == '1')
	{
		zombie_col(img, pi, pj);
		return ;
	}
	if (map[pi][pj - 1] == 'C' || map[pi][pj + '1'] == 'C')
	{
		zombie_col(img, pi, pj);
		return ;
	}
	if (map[pi][pj - 1] == 'P' || map[pi][pj + '1'] == 'P')
	img->map[pi][pj] = '0';
	if (i % 2 == 0)
		img->map[pi][pj - 1] = 'Z';
	else
		img->map[pi][pj + 1] = 'Z';
	i++;
}

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
	printf("Moviments %d\n", img->index);
	img->moviment = img->index;
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
			if (map[i][j] == 'Z')
			{
				img->piz = i;
				img->pjz = j;
			}
			j++;
		}
		i++;
	}
	conditions_change_map(img, map, pi, pj);
}

void	conditions_build_map(t_data *img, char **map, int i, int j)
{
	char	*num;

	num = ft_itoa(img->moviment);
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
	else if (map[i][j] == 'Z')
		draw_image(img, img->zombie, i, j);
	mlx_string_put(img->mlx, img->win, 50, 50, 0xFFFFFF, num);
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
