/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:45 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/20 15:13:28 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	close_win(t_data *img)
{
	int	i;

	i = img->size_y;
	while (i >= 0)
	{
		if (img->map[i])
		{
			free(img->map[i]);
			img->map[i] = NULL;
		}
		i--;
	}
	free(img->map);
	img->map = NULL;
	exit(0);
}

void	draw_image(t_data *img, char *image, int i, int j)
{
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_length, &img->endian);
	img->img = mlx_xpm_file_to_image(img->mlx, image,
			&img->img_width, &img->img_height);
	mlx_put_image_to_window(img->mlx, img->win, img->img, j * 100, i * 100);
}

void	pick_images(t_data *img)
{
	img->player = "./textures/cowboy.xpm";
	img->floor = "./textures/wood.xpm";
	img->wall = "./textures/wall.xpm";
	img->door = "./textures/door.xpm";
	img->collect = "./textures/collect.xpm";
	img->zombie = "./textures/zombie.xpm";
	img->addr = NULL;
	img->index = 0;
}

int	main(int argc, char **argv)
{
	t_data	img;
	t_list	*list;

	if (argc != 2)
		return (1);
	if (check_ber(argv[1]) == 1)
		return (1);
	list = content_map(&img, argv[1]);
	if (!list)
		return (1);
	img.map = map_builder(list, img.size_x, img.size_y);
	if (check_elements(&img) == 1 || check_walls(&img) == 1
		|| check_square(&img) == 1)
		close_win(&img);
	img.width = img.size_x;
	img.height = img.size_y;
	pick_images(&img);
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.width * 100, img.height * 100, "S_L");
	img.img = mlx_new_image(img.mlx, img.width * 100, img.height * 100);
	build_map(&img);
	mlx_hook(img.win, 2, 1L << 0, main_loop, &img);
	mlx_hook(img.win, 17, 0, close_win, &img);
	mlx_loop(img.mlx);
}
