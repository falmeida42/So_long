/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 21:11:37 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/19 20:21:36 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"
#include <string.h>

int	check_walls(t_data *img)
{
	char	**map;
	int		i;
	int		j;
	int		result;

	map = img->map;
	i = 0;
	result = 0;
	while (i < img->size_y)
	{
		j = 0;
		while (j < img->size_x)
		{
			if (map[0][j] != '1' || map[i][0] != '1')
				result = 1;
			if (map[img->size_y - 1][j] == '0'
				|| map[i][img->size_x - 1] == '0')
				result = 1;
			j++;
		}
		i++;
	}
	if (result == 1)
		error_walls();
	return (result);
}

void	init_elements(t_data *img)
{
	img->e = 0;
	img->c = 0;
	img->p = 0;
}

int	check_elements(t_data *img)
{
	char	**map;
	int		i;
	int		j;

	map = img->map;
	i = 0;
	init_elements(img);
	while (i < img->size_y)
	{
		j = 0;
		while (j < img->size_x)
		{
			if (map[i][j] == 'E')
				img->e++;
			if (map[i][j] == 'C')
				img->c++;
			if (map[i][j] == 'P')
				img->p++;
			j++;
		}
		i++;
	}
	if (img->e < 1 || img->c < 1 || img->p != 1)
		return (error_elements());
	return (0);
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
		{
			write(1, "Error\n", 6);
			write(1, "This is not a rectangle\n", 24);
			return (1);
		}
		i++;
	}
	return (0);
}
