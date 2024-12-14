/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:42:14 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/13 11:50:51 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	calculate_scale(t_map *map, int width, int height)
{
	float	map_width;
	float	map_height;
	float	scale_x;
	float	scale_y;

	map_width = (map->width + map->height) * cos(Angle);
	map_height = (map->width + map->height) * sin(Angle) / 2;
	scale_x = width / map_width;
	scale_y = height / map_height;
	return ((fmin(scale_x, scale_y) * 0.7)); // reduire = dezoom
}

t_point project_iso(int x, int y, int z, float scale)
{
    t_point p;

    p.x = (x - y) * cos(Angle) * scale;
    p.y = (x + y) * sin(Angle) * scale - z * 0.280 * scale;
    p.x += WinWidth / 2;
    p.y += WinHeight / 2 ;
    return (p);
}

int	calculate_color(int z, int min_z, int max_z)
{
	float	ratio;
	int		range;

	range = max_z - min_z;
	if (range == 0)
		return (0xFFFFFF);
	ratio = (float)(z - min_z) / range;
	if (ratio < 0.33)
		return (0xFFB6C1);
	else if (ratio < 0.66)
		return (0x4A235A);
	else
		return (0x7FDD4C);
}


void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WinWidth && y >= 0 && y < WinHeight && data->addr)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
	}
}
