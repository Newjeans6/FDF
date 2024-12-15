/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:42:14 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/15 16:46:30 by pnaessen         ###   ########lyon.fr   */
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
	return ((fmin(scale_x, scale_y) * 0.7));
}

t_point	project_iso(int x, int y, int z, t_data *data)
{
	t_point	p;

	p.x = (x - y) * cos(data->angle) * data->scale;
	p.y = (x + y) * sin(data->angle) * data->scale - z * data->deep
		* data->scale;
	p.x += WinWidth / 2 + data->cam_x;
	p.y += WinHeight / 2 + data->cam_y;
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
