/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombie.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:24:40 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/20 18:39:48 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	zombie(t_data *img)
{
	printf("You Lose\n");
	close_win(img);
}

int	check_zombie(t_data *img)
{
	int	piz;
	int	pjz;

	piz = img->piz + (img->playerx / 100);
	if (img->playery == -100)
		pjz = img->pjz + (img->playery / 100);
	else
		pjz = img->pjz + (img->playery / 100) * -1;
	if (piz < 0 || pjz < 0)
		return (1);
	if (img->map[piz][pjz] == '1' || img->map[piz][pjz] == 'C'
			|| img->map[piz][pjz] == 'E')
		return (1);
	if (img->map[piz][pjz] == 'P')
		zombie(img);
	return (0);
}

void	zombie_mov(t_data *img, char **map)
{
	int	piz;
	int	pjz;

	piz = img->piz;
	pjz = img->pjz;
	if (check_zombie(img) == 1)
		return ;
	if (img->playerx == -100)
		img->map[piz - 1][pjz] = 'Z';
	if (img->playerx == 100)
		img->map[piz + 1][pjz] = 'Z';
	if (img->playery == 100)
		img->map[piz][pjz - 1] = 'Z';
	if (img->playery == -100)
		img->map[piz][pjz - 1] = 'Z';
	img->map[piz][pjz] = '0';
}
