/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 20:14:00 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/18 18:58:57 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	count_bag(t_data *img, char **map)
{
	int	i;
	int	j;
	int	bag;

	bag = 0;
	i = 0;
	j = 0;
	while (i < img->size_y)
	{
		j = 0;
		while (j < img->size_x)
		{
			if (map[i][j] == 'C')
				bag++;
			j++;
		}
		i++;
	}
	return (bag);
}

void	check_exit(t_data *img, char **map, int pi, int pj)
{
	if (img->bag == 0)
	{
		write(1, "You Win!\n", 9);
		img->you_win = true;
		draw_you_win(img, map);
	}
}

char	**map_builder(t_list *list, int i, int j)
{
	char	**map;
	int		y;

	y = 0;
	map = (char **)malloc(sizeof(char *) * (j + 1));
	while (y < j)
	{
		map[y] = (char *)malloc(sizeof(char *) * (i + 1));
		map[y] = list->content;
		list = list->next;
		y++;
	}
	map[y] = (char *)malloc(sizeof(char *) * 8);
	map[y] = NULL;
	y = 0;
	return (map);
}

int	check_ber(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0')
		i++;
	i--;
	if (argv[i] == 'r')
	{
		i--;
		if (argv[i] == 'e')
		{
			i--;
			if (argv[i] == 'b')
			{
				i--;
				if (argv[i] == '.')
					return (0);
			}
		}
	}
	write(1, "Error\n", 6);
	write(1, "The file need to be a .ber\n", 27);
	return (1);
}

t_list	*content_map(t_data *img, char *argv)
{
	t_list	*link;
	t_list	*tmp;
	char	*line;
	int		y;

	link = NULL;
	y = 0;
	tmp = link;
	img->fd = open(argv, O_RDONLY);
	if (img->fd == -1)
	{
		write(1, "Error\nInvalid file\n", 19);
		exit(-1);
	}
	img->ret = 1;
	while (img->ret > 0)
	{
		img->ret = get_next_line(img->fd, &line);
		tmp = ft_lstnew(line);
		ft_lstadd_back(&link, tmp);
		y++;
	}
	img->size_x = ft_strlen(link->content);
	img->size_y = y - 1;
	return (link);
}
