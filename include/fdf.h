/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:48:31 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/09 14:11:37 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx-linux/mlx.h"
//# include <../minilibx-linux/X11/keysym.h>
# include "../Libft/libft.h"
# include <math.h>
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
	int color;
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

typedef struct s_window // taille fenetre
{
	int width;
	int height;
}		t_window;

int		close_window(t_data *data);
t_map	*read_map(const char *maps);
int		*parse_line(char *line, int *width);
void	draw_map(t_data *data, t_map *map, t_window *window);
t_point	project_iso(int x, int y, int z, t_map *map, t_window *window);
int		key_hook(int keycode, t_data *data);
int		ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
void	free_split(char **split);
int		draw_line(t_data *data, t_point p1, t_point p2);
void	change_color(int z, t_data *data, int x, int y);
int		calculate_color(int z, int min_z, int max_z);
void	init_line(t_line *line, t_point p1, t_point p2);
int		update_line_position(t_line *line);
float	calculate_progress(int start, int end, int current);
int		draw_line(t_data *data, t_point p1, t_point p2);

#endif