/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 21:11:37 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/17 19:43:37 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <string.h>

int	check_walls(t_data *img)
{
	char	**map;
	int		i;
	int		j;

	map = img->map;
	i = 0;
	while (i < img->size_y)
	{
		j = 0;
		while (j < img->size_x)
		{
			if (map[0][j] != '1' || map[i][0] != '1')
				return (1);
			if (map[img->size_y -1][j] == '0' || map[i][img->size_x -1] == '0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_elements(t_data *img)
{
	char	**map;
	int		i;
	int		j;
	int		e;
	int		c;
	int		p;
	int		result;

	map = img->map;
	i = 0;
	e = 0;
	c = 0;
	p = 0;
	result = 0;
	while (i < img->size_y)
	{
		j = 0;
		while (j < img->size_x)
		{
			if (map[i][j] == 'E')
				e++;
			if (map[i][j] == 'C')
				c++;
			if (map[i][j] == 'P')
				p++;
			j++;
		}
		i++;
	}

	if (e < 1 || c < 1 || p != 1)
		result = 1;

	return (result);
}

int	check_square(t_data *img)
{
	char	**map;
	int		i;
	int		j;
	int		len;

	map = img->map;
	i = 0;
	len = ft_strlen(map[i]);
	while (i < img->size_y)
	{
		if (ft_strlen(map[i]) != len)
			return (1);
		i++;
	}
	return (0);
}
