/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:46:24 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/18 22:32:20 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

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

static size_t	ft_len(int n)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_signal(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

char	*ft_itoa(int n)
{
	size_t	i;
	size_t	k;
	char	*str;

	i = ft_len(n);
	str = (char *)malloc(i + 1);
	if (!(str))
		return (NULL);
	str[i] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		k = 1;
	}
	else
		k = 0;
	while (i > k)
	{
		i--;
		str[i] = '0' + n % 10 * ft_signal(n);
		n = n / 10;
	}
	return (str);
}
