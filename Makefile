# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 10:42:01 by pnaessen          #+#    #+#              #
#    Updated: 2024/12/18 10:37:48 by pnaessen         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := fdf

SRC:= $(addprefix $(SRC_DIR), init.c parse.c algo.c dots.c line.c hook.c)
OBJ_DIR:= .obj/
OBJ:= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPS:= $(OBJ:%.o=%.d)

CC:= gcc
CCFLAGS:= -Wextra -Wall -Werror
CPPFLAGS = -MMD -MP
SRC_DIR:= src/
INCLUDES:= include/


MLX_DIR:= minilibx-linux/
MLX:= $(MLX_DIR)libmlx_Linux.a
MLX_FLAG:= -L $(MLX_DIR) -lmlx_Linux -L/usr/lib -I $(MLX_DIR) -lX11 -lm -lz -lXext $(MLX)

LIBFT_DIR := libft/
LIBFT := $(LIBFT_DIR)libft.a 
LIBFT_FLAG := -L $(LIBFT_DIR) $(LIBFT)

HEADERS:= -I $(INCLUDES) -I $(MLX_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CCFLAGS) $(OBJ) $(MLX_FLAG) $(LIBFT_FLAG) -o $(NAME)
	@echo "👉 ༼☉ɷ⊙༽ $(BLUE)$(CC) $(CCFLAGS) $(OBJ)  $(MLX_FLAG) $(LIBFT_FLAG) -o $(NAME)$(DEF_COLOR)"
	@echo "$(GREEN)✨✨✨✨✨✨✨✨ ¯\(◉◡◔)/¯ FDF compiled! ¯\(◉◡◔)/¯ ✨✨✨✨✨✨✨✨✨✨✨✨✨🐷 $(DEF_COLOR)"
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "🍩 $(MAGENTA)Compiling: $< $(DEF_COLOR)"
	$(CC) $(CCFLAGS) $(CPPFLAGS)  $(HEADERS) -o $@ -c $<

-include $(DEPS)
# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m




clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	@echo "$(RED)🧨💥🧨💥🧨🧨🧨🧨🧨🧨🧨🧨🧨 FDF removed! 🧨💥🧨💥🧨🧨🧨🧨🧨🧨🧨🧨🧨$(DEF_COLOR)"
	rm -f $(NAME)

re: fclean all

info:
	@echo "OBJ": $(OBJ)
	@echo "DEPS": $(DEPS)

.PHONY: all clean fclean re