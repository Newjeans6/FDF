/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:40:33 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/15 12:32:18 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	calculate_progress(int start, int end, int current)
{
	if (start == end)
		return (0);
	return ((int)(current - start) / (end - start));
}
