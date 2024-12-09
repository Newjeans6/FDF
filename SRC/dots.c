/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:42:14 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/11 08:33:33 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	calculate_scale(t_map *map, int width, int height)
{
	float	map_width;
	float	map_height;
	float	scale_x;
	float	scale_y;

	map_width = (map->width + map->height) * cos(0.523599);
	map_height = (map->width + map->height) * sin(0.523599) / 7;
	scale_x = width / map_width;
	scale_y = height / map_height;
	return ((fmin(scale_x, scale_y) * 0.7)); // reduire = dezoom
}

t_point	project_iso(int x, int y, int z, t_map *map, t_window *window)
{
	t_point	p;
	float	scale;

	scale = calculate_scale(map, window->width, window->height);
	p.x = (x - y) * cos(0.523599) * scale;
	p.y = (x + y) * sin(0.523599) * scale - z * 0.2 * scale; // pour pronfondeur
	p.x += window->width / 2.2; // de gauche a droite
	p.y += window->height / 2.8; // de bas em haut
	p.color = calculate_color(z, map->min_z, map->max_z);
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
	if (ratio < 0.25)
		return (0x48c9b0);
	else if (ratio < 0.5)
		return (0xd68910);
	else if (ratio < 0.75)
		return (0x8e44ad);
	else
		return (0x4a235a);
}
