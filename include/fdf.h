/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:48:31 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/11 14:23:55 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
//# include <../minilibx-linux/X11/keysym.h>
# include "libft.h"
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

# define MLX_ERROR 1
# define ESC_KEY 65307
# define DESTROY 17
# define KeyPress 02
# define Angle 0.523599
//////Windows
# define WinHeight 1500
# define WinWidth 1500

typedef struct s_data // img + Window + ptr
{
	void *mlx_ptr;
	void *win_ptr;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}		t_data;

typedef struct s_map //  Matrice de projection
{
	int **grid;
	int width;
	int height;
	int min_z;
	int max_z;
}		t_map;

typedef struct s_point // vue iso
{
	int x;
	int y;
}		t_point;

typedef struct s_line // Bresenham
{
	int dx;
	int dy;
	int x;
	int y;
	int err;
	int sx;
	int sy;
}		t_line;

int		close_window(t_data *data);
t_map	*read_map(const char *maps);
int		*parse_line(char *line, int *width);
void	draw_map(t_data *data, t_map *map);
t_point	project_iso(int x, int y, int z, t_map *map);
int		key_hook(int keycode, t_data *data);
int		ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
void	free_split(char **split);
int		draw_line(t_data *data, t_point p1, t_point p2);
void	change_color(int z, t_data *data, int x, int y);
int		calculate_color(int z, int min_z, int max_z);
void	init_line(t_line *line, t_point p1, t_point p2);
int		update_line_position(t_line *line, t_point p2);
int		calculate_progress(int start, int end, int current);
int		draw_line(t_data *data, t_point p1, t_point p2);
void	grid_alloc(t_map *map, const char *maps, int height);
#endif