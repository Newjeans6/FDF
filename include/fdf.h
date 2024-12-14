/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:48:31 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/14 13:22:04 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

# define MLX_ERROR 1
# define ESC_KEY 65307
# define DESTROY 17
# define KeyPress 02
# define Angle 0.523599
# define WinHeight 1500
# define WinWidth 1500
# define ZOOM_IN 4
# define ZOOM_OUT 5

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	float			scale;
	int				flag;
	struct s_map	*map;
}					t_data;

typedef struct s_map
{
	int				**grid;
	int				width;
	int				height;
	int				min_z;
	int				max_z;
}					t_map;

typedef struct s_point
{
	int				x;
	int				y;
	int				color;
}					t_point;

typedef struct s_line
{
	int				dx;
	int				dy;
	int				x;
	int				y;
	int				err;
	int				sx;
	int				sy;
}					t_line;

int					close_window(t_data *data);
t_map				*read_map(const char *maps);
void				draw_map(t_data *data, t_map *map);
t_point				project_iso(int x, int y, int z, float scale);
int					key_hook(int keycode, t_data *data);
int					calculate_color(int z, int min_z, int max_z);
void				put_pixel(t_data *data, int x, int y, int color);
void				update_min_max(t_map *map, int z);
int					*parse_line_with_minmax(char *line, int *width, t_map *map);
void				grid_alloc_with_minmax(t_map *map, const char *maps,
						int height);
void				draw_line(t_data *data, t_point p1, t_point p2);
void				draw_map_line(t_data *data, t_map *map, int x, int y,
						float scale);
void				initialize_line(t_line *line, t_point p1, t_point p2);
void				update_line_position(t_line *line, t_point *p1);
void				free_split(char **split);
float				calculate_scale(t_map *map, int width, int height);
#endif