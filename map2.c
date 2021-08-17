/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 20:14:00 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/17 21:54:50 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

t_list	*content_map(t_data *img, char *argv)
{
	t_list	*link;
	t_list	*tmp;
	int		fd;
	char	*line;
	int		ret;
	int		y;
	int		i;
	int		z;

	link = NULL;
	y = 0;
	i = 1;
	tmp = link;
	fd = open(argv, O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		tmp = ft_lstnew(line);
		ft_lstadd_back(&link, tmp);
		if (i > 0)
		{
			img->size_x = ft_strlen(line);
			i--;
		}
		y++;
	}
	img->size_y = y - 1;
	return (link);
}
