/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:18:59 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/19 21:48:49 by falmeida         ###   ########.fr       */
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
}	t_data;

# define W 13
# define S 1
# define A 0
# define D 2
# define ESC 53

void	draw_image(t_data *img, char *image, int i, int j);
int		close_win(t_data *img);

// map.c
void	change_map(t_data *img, char **map);
void	build_map(t_data *img);
int		key_print(int key, t_data *img);
// map.c

// map2.c
int		count_bag(t_data *img, char **map);
void	check_exit(t_data *img, char **map, int pi, int pj);
char	**map_builder(t_list *list, int i, int j);
t_list	*content_map(t_data *img, char *argv);
int		check_ber(char *argv);
// map2.c

// utils.c
size_t	ft_strlen(const char *src);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
// utils.c

//error.c
int		check_elements(t_data *img);
int		check_walls(t_data *img);
int		check_square(t_data *img);
//error.c

//utils2.c
void	error_walls(void);
int		error_elements(void);
char	*ft_itoa(int n);
//utils2.c
#endif
