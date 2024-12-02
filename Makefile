# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 10:42:01 by pnaessen          #+#    #+#              #
#    Updated: 2024/12/02 11:17:09 by pnaessen         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME    =  FDF


CC:= gcc

CCFLAGS:= -Werror -Wextra -Wall

SRC:= main.c

OBJ:= $(SRC:%.c=%.o)

all: $(NAME)
MLX_DIR:= minilibx-linux/
MLX:= minilibx-linux/libmlx_Linux.a
MLX_FLAG:= -L $(MLX_DIR) -lmlx_Linux -L/usr/lib -I $(MLX_DIR) -lX11 -lm -lz -lXext $(MLX)

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	$(CC) $(CCFLAGS) $(OBJ) $(MLX_FLAG) -o $(NAME)

print:
	@echo $(OBJ)
# echo $(MLX)

%.o: %.c
	$(CC) $(CCFLAGS) -I . -I $(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	make clean -C minilibx-linux/
	rm -f $(NAME)

re : fclean all