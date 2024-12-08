/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:06:35 by aviscogl          #+#    #+#             */
/*   Updated: 2024/12/08 15:29:34 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

float	calculate_scale(t_map *map, int width, int height)
{
	float	map_width;
	float	map_height;
	float	scale_x;
	float	scale_y;

	map_width = (map->width + map->height) * cos(0.523599);
	map_height = (map->width + map->height) * sin(0.523599) / 2;
	scale_x = width / map_width;
	scale_y = height / map_height;
	return (fmin(scale_x, scale_y) * 0.8); // Réduire pour dezoomer
}
t_point	project_iso(int x, int y, int z, t_map *map, t_window *window)
{
	t_point	p;
	float	scale;

	scale = calculate_scale(map, window->width, window->height);
	p.x = (x - y) * cos(0.523599) * scale;
	p.y = (x + y) * sin(0.523599) * scale - z * 0.1 * scale; //modif valeur pour profondeur
	p.x += window->width / 2;
	p.y += window->height / 5; // Ajustez  valeur pour centrer
	return (p);
}
void	draw_map(t_data *data, t_map *map, t_window *window)
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
			p1 = project_iso(x, y, map->grid[y][x], map, window);
			// Projette le point actuel en iso
			if (x < map->width - 1)
			// si pas last colonne draw line vers le pts a droite
			{
				p2 = project_iso(x + 1, y, map->grid[y][x + 1], map, window);
				draw_line(data, p1, p2);
			}
			if (y < map->height - 1)
			// si pas last ligne draw line vers le dessous
			{
				p2 = project_iso(x, y + 1, map->grid[y + 1][x], map, window);
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
	int		e2;

	line.dx = abs(p2.x - p1.x); // distance horizontale
	line.dy = abs(p2.y - p1.y);
	line.x = p1.x; // positions de départ
	line.y = p1.y;
	if (p1.x < p2.x)
		line.sx = 1; // Incrémenter x vers la droite
	else
		line.sx = -1; //  x vers la gauche
	if (p1.y < p2.y)
		line.sy = 1; // Incrémenter y vers le bas
	else
		line.sy = -1;      //  y vers le haut
	if (line.dx > line.dy) // calcul de l'erreur
		line.err = line.dx / 2;
	else
		line.err = -line.dy / 2;
	while (1)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, line.x, line.y, 0xFFFFFF);
		if (line.x == p2.x && line.y == p2.y)
			break ;
		e2 = line.err;
		if (e2 > -line.dx)
		{
			line.err -= line.dy;
			line.x += line.sx;
		}
		if (e2 < line.dy)
		{
			line.err += line.dx;
			line.y += line.sy;
		}
	}
	return (0);
}
