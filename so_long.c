/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:45 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/16 19:59:40 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int    close_win(t_data *img)
{
	(void)img;
	exit(0);
}

void    draw_image(t_data *img, char *image, int i, int j)
{
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
	img->img = mlx_xpm_file_to_image(img->mlx, image, &img->img_width, &img->img_height);
	mlx_put_image_to_window(img->mlx, img->win, img->img, j * 100, i * 100);
}

void	pick_images(t_data *img)
{
	img->player = "./cowboy.xpm";
	img->floor = "./wood.xpm";
	img->wall = "./wall.xpm";
	img->door = "./door.xpm";
	img->collect = "./collect.xpm";
	img->addr = NULL;
}

size_t	ft_strlen(const char *src)
{
	size_t i;

	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!*lst)
    {
        *lst = new;
        return ;
    }
	(ft_lstlast(*lst))->next = new;
}


t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
	{
		return (NULL);
	}
	new->content = content;
	new->next = NULL;
	return (new);
}

char    **map_builder(t_list *list, int i, int j)
{
    char **map;
    int y = 0;
    map = (char**)malloc(sizeof(char*) * (j + 1));
    while (y < j)
    {
        map[y] = (char*)malloc(sizeof(char*) * (i + 1));
        map[y] = list->content;
        list = list->next;
        y++;
    }
    map[y] = (char*)malloc(sizeof(char*) * 8);
    map[y] = NULL;
    y = 0;
    return (map);
}

t_list	*content_map(t_data *img, char *argv)
{
	t_list *link;
	t_list *tmp;
	int fd;
	char *line;
	int ret;
	int y;
	int i;

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
	img->size_y = y;
	return (link);
}

int main(int argc, char **argv)
{
	t_data  img;
	t_list	*list;
	int     img_width;
	int     img_height;

	if (argc != 2)
		return (1);
	list = content_map(&img, argv[1]);
	img.map = map_builder(list, img.size_x, img.size_y);
	img.width = img.size_x;
	img.height = img.size_y -1;
	img_width = img.width * 100;
	img_height = img.height * 100;
	pick_images(&img);
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img_width, img_height, "So Long");
	img.img = mlx_new_image(img.mlx, img_width, img_height);
	build_map(&img);
	mlx_hook(img.win, 2, 1L<<0, key_print, &img);
	mlx_hook(img.win, 17, 0, close_win, &img);
	mlx_loop(img.mlx);
}
