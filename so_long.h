/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:59 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/20 18:40:03 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include "get_next_line.h"

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;

	char	*door;
	char	*floor;
	char	*wall;

	char	*player;
	int		playerx;
	int		playery;

	char	*collect;
	char	*zombie;
	int		bag;

	int		width;
	int		height;

	int		size_x;
	int		size_y;

	char	**map;

	int		e;
	int		c;
	int		p;

	int		fd;
	int		ret;

	int		moviment;
	int		index;

	int		piz;
	int		pjz;

	int		pi;
	int		pj;
}	t_data;

# define W 119
# define S 115
# define A 97
# define D 100
# define ESC 65307

void	draw_image(t_data *img, char *image, int i, int j);
int		close_win(t_data *img);

// map.c
void	change_map(t_data *img, char **map);
void	build_map(t_data *img);
int		key_print(int key, t_data *img);
// map.c

// map2.c
t_list	*content_map(t_data *img, char *argv);
void	check_exit(t_data *img, char **map, int pi, int pj);
char	**map_builder(t_list *list, int i, int j);
int		count_bag(t_data *img, char **map);
int		check_ber(char *argv);
// map2.c

// utils.c
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
size_t	ft_strlen(const char *src);
void	ft_lstadd_back(t_list **lst, t_list *new);
// utils.c

//error.c
int		check_elements(t_data *img);
int		check_walls(t_data *img);
int		check_square(t_data *img);
//error.c

//utils2.c
void	error_walls(void);
char	*ft_itoa(int n);
int		error_elements(void);
//utils2.c

//zombie.c
void	zombie(t_data *img);
void	zombie_mov(t_data *img, char **map);
int		check_zombie(t_data *img);
//zombie.c
#endif
