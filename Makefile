# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 13:21:21 by falmeida          #+#    #+#              #
#    Updated: 2021/08/16 16:10:22 by falmeida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g

NAME = so_long

SRC = so_long.c					\
		map.c					\
		error.c 				\
		get_next_line.c			\
		get_next_line_utils.c	\

%.o: %.c
	gcc -Imlx -c $< -o $@

OBJS = $(SRC:.c=.o)

$(NAME) : $(OBJS)
	gcc $(OBJS) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)


all: $(NAME)

clean:
	/bin/rm -rf $(OBJS)

fclean:
	/bin/rm -f $(NAME)

re: fclean all
