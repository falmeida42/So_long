/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:59 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/06 22:05:19 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
    int     img_width;
    int     img_height;

    char    *door;
    char    *floor;
    char    *wall;

    char    *player;
    int playerx;
    int playery;

    char    *collect;
    int     bag;

    int     width;
	int     height;

}               t_data;

# define W 13
# define S 1
# define A 0
# define D 2
# define ESC 53

void    draw_image(t_data *img, char *image, int i, int j);
int    close_win(t_data *img);

void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    mlx_line(t_data *data, int x, int y, int p, int color);
void    mlx_block(t_data *data, int x, int y, int p, int color);
void    build_block(t_data *img, int x, int y, int p, int color);

void	check_exit(t_data *img, char map[7][14], int pi, int pj);
int		count_bag(t_data *img, char map[7][14]);
void    change_map(t_data *img, char map[7][14]);
void    build_map(t_data *img);
int     key_print(int key, t_data *img);

void    check_error(t_data *img, char map[7][14]);

# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include "get_next_line.h"
#endif
