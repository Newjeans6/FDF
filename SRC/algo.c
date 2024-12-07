/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:06:35 by aviscogl          #+#    #+#             */
/*   Updated: 2024/12/07 15:50:41 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
void	draw_map(t_data *data, t_map *map)
{
	int x; // colonne
	int y; // ligne
	t_point p1, p2;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			p1 = project_iso(x, y, map->grid[y][x]);
			// Projette le point actuel en iso
			if (x < map->width - 1)
			// si pas last colonne draw line vers le pts a droite
			{
				p2 = project_iso(x + 1, y, map->grid[y][x + 1]);
				draw_line(data, p1, p2);
			}
			if (y < map->height - 1)
			// si pas last ligne draw line vers le dessous
			{
				p2 = project_iso(x, y + 1, map->grid[y + 1][x]);
				draw_line(data, p1, p2);
			}
			x++;
		}
		y++;
	}
}

int	draw_line(t_data *data, t_point p1, t_point p2)
{
	t_line	line;

	line.dx = abs(p2.x - p1.x);//distance horizontale
	line.dy = abs(p2.y - p1.y);
	line.x = p1.x;	//positions de départ
	line.y = p1.y;
	line.err = line.dx - line.dy; 	// Calcul de l'erreur
	if (p1.x < p2.x)
		line.sx = 1; // Incrémenter x vers la droite
	else
		line.sx = -1; //  x vers la gauche
	if (p1.y < p2.y)
		line.sy = 1; // Incrémenter y vers le bas
	else
		line.sy = -1; //  y vers le haut
	while (line.x != p2.x || line.y != p2.y)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, line.x, line.y, 0xFFFFFF);
		line.err += line.dy;
		if (2 * line.err >= line.dx)
		{
			line.y += line.sy;
			line.err -= line.dx;
		}
		if (2 * line.err <= line.dy)
		{
			line.x += line.sx;
			line.err -= line.dy;
		}
	}
	return (0);
}
