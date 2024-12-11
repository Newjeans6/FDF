/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:40:33 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/11 14:07:52 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_data *data, t_map *map)
{
	int		x;
	int		y;
	t_point	p1;
	t_point	p2;

	y = 0;
	while (y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			p1 = project_iso(x, y, map->grid[y][x], map);
			if (x < map->width - 1)
			{
				p2 = project_iso(x + 1, y, map->grid[y][x + 1], map);
				draw_line(data, p1, p2);
			}
			if (y < map->height - 1)
			{
				p2 = project_iso(x, y + 1, map->grid[y + 1][x], map);
				draw_line(data, p1, p2);
			}
		}
		y++;
	}
}

void	init_line(t_line *line, t_point p1, t_point p2)
{
	line->dx = abs(p2.x - p1.x); // distance horizontale
	line->dy = abs(p2.y - p1.y);
	line->x = p1.x; // positions de départ
	line->y = p1.y;
	if (p1.x < p2.x)  // si point final  à droite
		line->sx = 1; // Incrémenter x vers la droite
	else
		line->sx = -1; //  x vers la gauche
	if (p1.y < p2.y)   // si point final en bas
		line->sy = 1;  // Incrémenter y vers le bas
	else
		line->sy = -1; //  y vers le haut
	if (line->dx > line->dy)
		// calcul de l'erreur si plus horizontal erreur basee sur dx
		line->err = line->dx / 2;
	else
		line->err = -line->dy / 2;
}

int	update_line_position(t_line *line, t_point p2)
{
	int	e2;

	e2 = line->err;
	if (e2 > -line->dx)
	{
		line->err -= line->dy; // ajuste l'erreur
		line->x += line->sx;   // ajuste en horizontale
	}
	if (e2 < line->dy)
	{
		line->err += line->dx;
		line->y += line->sy; // ajuste verticale
	}
	return (line->x != p2.x || line->y != p2.y);
}

int	draw_line(t_data *data, t_point p1, t_point p2)
{
	t_line	line;
	int		progress;
	int		color;

	init_line(&line, p1, p2);
	while (1)
	{
		if (line.x >= 0 && line.x < WinWidth && line.y >= 0
			&& line.y < WinHeight) // verif si dans fenetre
		{
			if (line.dx > line.dy)
				progress = calculate_progress(p1.x, p2.x, line.x);
			else
				progress = calculate_progress(p1.y, p2.y, line.y);
			color = calculate_color(progress, p1.x, p2.x);
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, line.x, line.y, color);
		}
		if (!update_line_position(&line, p2))
			break ;
	}
	return (0);
}

int	calculate_progress(int start, int end, int current)
{
	if (start == end)
		return (0);
	return ((int)(current - start) / (end - start));
}
