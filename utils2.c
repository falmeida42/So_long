/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_so_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:46:24 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/18 18:48:06 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_walls(void)
{
	write(1, "Error\n", 6);
	write (1, "You need to build walls\n", 24);
}

int	error_elements(void)
{
	write(1, "Error\n", 6);
	write(1, "You forgot something\n", 21);
	return (1);
}
