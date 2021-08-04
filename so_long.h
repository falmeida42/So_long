/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:59 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/04 20:14:20 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     img_width;
    int     img_height;

    char    *player;
    int x;
    int y;
}               t_data;

typedef struct s_wall {
    char    *wall;
    int     wallx;
    int     wally;
} t_wall;

typedef struct s_floor {
    char    *floor;
    int floorx;
    int floory;
} t_floor;

# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    mlx_line(t_data *data, int x, int y, int p, int color);
void    mlx_block(t_data *data, int x, int y, int p, int color);
void    build_block(t_data *img, int x, int y, int p, int color);

# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
#endif