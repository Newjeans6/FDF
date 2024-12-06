/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:48:31 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/06 09:26:37 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx-linux/mlx.h"
//# include <./X11/Keysym.h>
# include "get_next_line.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

# define MLX_ERROR 1
# define ESC_KEY 65307
# define DESTROY 17
# define KeyPress 02

typedef struct s_data // img + Window + ptr
{
	void *mlx_ptr;
	void *win_ptr;
	void *img;
	char *img_path;
	int img_width;
	int img_height;
}		t_data;

typedef struct s_map // Map 2d stoker
{
	int **grid;
	int width;
	int height;
}		t_map;

typedef struct s_point // iso
{
	int x;
	int y;
}		t_point;

int		close_window(t_data *data);
t_map	*read_map(const char *maps);
int		*parse_line(char *line, int *width);
void	draw_map(t_data *data, t_map *map);
t_point	project_iso(int x, int y, int z);
int		key_hook(int keycode, t_data *data);
int	ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
void free_split(char **split);

#endif