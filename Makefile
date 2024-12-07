# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 10:42:01 by pnaessen          #+#    #+#              #
#    Updated: 2024/12/07 14:52:01 by pnaessen         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME    =  FDF

CC := gcc
CCFLAGS := -Wextra -Wall -Werror

SRC_DIR := SRC/
SRC := $(addprefix $(SRC_DIR), main.c parse.c algo.c)

OBJ := $(SRC:$(SRC_DIR)%.c=%.o)
	
MLX_DIR := minilibx-linux/
MLX := minilibx-linux/libmlx_Linux.a
MLX_FLAG := -L $(MLX_DIR) -lmlx_Linux -L/usr/lib -I $(MLX_DIR) -lX11 -lm -lz -lXext $(MLX)

LIBFT_DIR := Libft/
LIBFT := $(LIBFT_DIR)libft.a 
LIBFT_FLAG := -L$(LIBFT_DIR) $(LIBFT)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CCFLAGS) $(OBJ) $(LIBFT_FLAG) $(MLX_FLAG)  -o $(NAME)
	
all: $(NAME)

print:
#@echo $(OBJ)

%.o: $(SRC_DIR)%.c
	$(CC) $(CCFLAGS) -I . -I $(MLX_DIR) -I $(SRC_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C Libft/
	$(MAKE) clean -C minilibx-linux/
	rm -f $(NAME)

re: fclean all