# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 13:21:21 by falmeida          #+#    #+#              #
#    Updated: 2021/08/18 22:22:42 by falmeida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g

NAME = so_long

BONUS = so_long_bonus

SRC = so_long.c					\
		map.c					\
		map2.c					\
		error.c 				\
		get_next_line.c			\
		get_next_line_utils.c	\
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

%.o: %.c
	gcc -Imlx -c $< -o $@

OBJS = $(SRC:.c=.o)

OBJSB = $(SRCB:.c=.o)

$(NAME) : $(OBJS)
	gcc $(OBJS) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(BONUS) : $(OBJSB)
	gcc $(OBJSB) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(BONUS)

all: $(NAME)

bonus: $(BONUS)

clean:
	/bin/rm -rf $(OBJS)

fclean:
	/bin/rm -f $(NAME)

re: fclean all
