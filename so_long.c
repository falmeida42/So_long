/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:45 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/03 16:31:34 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    mlx_line(t_data *data, int x, int y, int p, int color)
{
    int xp;

    xp = x + p;
    while (x < xp)
    {
        my_mlx_pixel_put(data, x, y, color);
        x++;
    }
}

void    mlx_block(t_data *data, int x, int y, int p, int color)
{
    int yp;

    yp = y + p;
    while (y < yp)
    {
        mlx_line(data, x, y, p, color);
        y++;
    }
}

int main()
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    //void    *imge;
    //char    *relative_path = "./zombie.xpm";
    //int     img_width;
    //int     img_height;

    mlx = mlx_init();
    //imge = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    mlx_win = mlx_new_window(mlx, 1920, 1080, "So Long");
    img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    //my_mlx_pixel_put(&img, 1000, 540, 0x00FF0000);
    mlx_block(&img, 480, 200, 50, 0x00FF0000);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}