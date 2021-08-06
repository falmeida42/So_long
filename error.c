/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 21:11:37 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/06 21:33:22 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_error(t_data *img, char map[7][14])
{
	if (img->width == img->height)
	{
		printf("Error\n");
		printf("Invalid Map");
		close_win(img);
	}
}
