/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:40:33 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/14 14:12:47 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_data *data, t_map *map)
{
	int	x;
	int	y;

	if (data->flag == 1)
	{
		data->scale = calculate_scale(map, WinWidth, WinHeight);
		data->flag = 0;
	}
	printf("scale = %f\n", data->scale);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			draw_map_line(data, map, x, y, data->scale);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

void	initialize_line(t_line *line, t_point p1, t_point p2)
{
	line->dx = abs(p2.x - p1.x);
	line->dy = abs(p2.y - p1.y);
	line->sx = 1;
	if (p1.x >= p2.x)
		line->sx = -1;
	line->sy = 1;
	if (p1.y >= p2.y)
		line->sy = -1;
	line->err = line->dx;
	if (line->dy > line->dx)
		line->err = -line->dy;
	line->err /= 2;
}

void	update_line_position(t_line *line, t_point *p1)
{
	if (line->err > -line->dx)
	{
		line->err -= line->dy;
		p1->x += line->sx;
	}
	if (line->err < line->dy)
	{
		line->err += line->dx;
		p1->y += line->sy;
	}
}

void	draw_line(t_data *data, t_point p1, t_point p2)
{
	t_line	line;

	initialize_line(&line, p1, p2);
	while (1)
	{
		put_pixel(data, p1.x, p1.y, p1.color);
		if ((line.sx > 0 && p1.x >= p2.x) || (line.sx < 0 && p1.x <= p2.x))
			if ((line.sy > 0 && p1.y >= p2.y) || (line.sy < 0 && p1.y <= p2.y))
				break ;
		update_line_position(&line, &p1);
	}
}

int	calculate_progress(int start, int end, int current)
{
	if (start == end)
		return (0);
	return ((int)(current - start) / (end - start));
}
