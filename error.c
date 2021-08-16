/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 21:11:37 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/16 21:30:55 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (e > 0 && c > 0 && p > 0)
		result = 1;
	return (result);
}
