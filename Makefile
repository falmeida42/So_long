# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 13:21:21 by falmeida          #+#    #+#              #
#    Updated: 2021/08/03 14:02:15 by falmeida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g

NAME = so_long

SRC = so_long.c

%.o: %.c
	gcc -Wall -Wextra -Werror -Imlx -c $< -o $@

OBJS = $(SRC:.c=.o)

$(NAME) : $(OBJS)
	gcc $(OBJS) $(FLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)


all: $(NAME)

clean:
	/bin/rm -rf $(OBJS)

fclean:
	/bin/rm -f $(NAME)

re: fclean all
