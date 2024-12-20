/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:19:00 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/18 17:04:54 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_data *data, t_map *map)
{
	int	x;
	int	y;

	if (data->flag == 1)
	{
		data->scale = calculate_scale(map, WIN_WIDTH, WIN_HEIGHT);
		data->flag = 0;
	}
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			draw_map_line(data, map, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

void	draw_map_line(t_data *data, t_map *map, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1 = project_iso(x, y, map->grid[y][x], data);
	p1.color = calculate_color(map->grid[y][x], map->min_z, map->max_z);
	if (x < map->width - 1)
	{
		p2 = project_iso(x + 1, y, map->grid[y][x + 1], data);
		p2.color = calculate_color(map->grid[y][x + 1], map->min_z, map->max_z);
		draw_line(data, p1, p2);
	}
	if (y < map->height - 1)
	{
		p2 = project_iso(x, y + 1, map->grid[y + 1][x], data);
		p2.color = calculate_color(map->grid[y + 1][x], map->min_z, map->max_z);
		draw_line(data, p1, p2);
	}
}

void	draw_line(t_data *data, t_point p1, t_point p2)
{
	t_line	line;

	initialize_line(&line, p1, p2);
	while (1)
	{
		if (p1.x >= 0 && p1.x < WIN_HEIGHT && p1.y >= 0 && p1.y < WIN_HEIGHT)
		{
			put_pixel(data, p1.x, p1.y, p1.color);
		}
		if ((line.sx > 0 && p1.x >= p2.x) || (line.sx < 0 && p1.x <= p2.x))
			if ((line.sy > 0 && p1.y >= p2.y) || (line.sy < 0 && p1.y <= p2.y))
				break ;
		update_line_position(&line, &p1);
		if (p1.x < 0 || p1.x >= WIN_HEIGHT || p1.y < 0 || p1.y >= WIN_HEIGHT)
			break ;
	}
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT && data->addr)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}
