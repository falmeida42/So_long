# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 13:21:21 by falmeida          #+#    #+#              #
#    Updated: 2021/08/20 18:29:07 by falmeida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g

NAME = so_long

INCLUDE_PATH = includes

BONUS = so_long_bonus

SRC = so_long.c					\
		map.c					\
		map2.c					\
		error.c 				\
		get_next_line/get_next_line.c			\
		get_next_line/get_next_line_utils.c	\
		utils.c					\
		utils2.c				\

SRCB = so_long.c				\
		map_bonus.c				\
		map2.c					\
		error.c 				\
		get_next_line.c			\
		get_next_line_utils.c	\
		utils.c					\
		utils2.c				\
		zombie.c				\

OBJS = $(SRC:%.c=%.o)

%.o: %.c
	gcc -I/usr/include -Imlx_linux -O3 -c $< -o $@


$(NAME) : $(OBJS)
	gcc $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -I $(INCLUDE_PATH) -o $(NAME)


all: $(NAME)

bonus: $(BONUS)

clean:
	/bin/rm -rf $(OBJS)
	/bin/rm -rf $(OBJSB)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(BONUS)

re: fclean all
