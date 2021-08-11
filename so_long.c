/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:45 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/11 19:41:18 by falmeida         ###   ########.fr       */
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

void	build_my_map(t_data *img, t_list *link)
{
	char **map;
	int i;
	int y;
	i = img->size_y;
	map = (char **)malloc(sizeof(i + 1));
	while (i > 1)
	{
		map[y] = malloc(sizeof(img->size_x + 1));
		map[y] = link->content;
		link = link->next;
		i--;
	}
	map[y] = (char*)malloc(sizeof(char*) * 8);
    map[y] = NULL;
}

void	content_map(t_data *img, char *argv)
{
	t_list *link;
	t_list *tmp;
	int fd;
	char *line;
	int ret;
	int y;

	link = NULL;
	y = 1;
	tmp = link;
	fd = open(argv, O_RDONLY);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		y++;
		tmp = ft_lstnew(line);
		ft_lstadd_back(&link, tmp);
		ret = get_next_line(fd, &line);
	}
	img->size_x = ft_strlen(line);
	img->size_y = y;
}

int main(int argc, char **argv)
{
	t_data  img;
	int     img_width;
	int     img_height;

	if (argc != 2)
		return (1);
	content_map(&img, argv[1]);
	img.width = 13;
	img.height = 6;
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
