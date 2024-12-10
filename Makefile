# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 10:42:01 by pnaessen          #+#    #+#              #
#    Updated: 2024/12/10 11:58:31 by cdomet-d         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := FDF

CC := cc
CCFLAGS := -Wextra -Wall -Werror 

SRC_DIR := SRC/
SRC := $(addprefix $(SRC_DIR), main.c parse.c algo.c dots.c)

OBJ_DIR := .obj/
OBJ := $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

MLX_DIR := minilibx-linux/
MLX := $(MLX_DIR)libmlx_Linux.a
MLX_FLAG := -L $(MLX_DIR) -lmlx_Linux -L/usr/lib -I $(MLX_DIR) -lX11 -lm -lz -lXext $(MLX)

LIBFT_DIR := Libft/
LIBFT := $(LIBFT_DIR)libft.a 
LIBFT_FLAG := -L $(LIBFT_DIR) $(LIBFT)

HEADERS:= -I . -I $(MLX_DIR) -I $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CCFLAGS) $(OBJ)  $(MLX_FLAG) $(LIBFT_FLAG) -o $(NAME)

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re