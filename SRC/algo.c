/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:06:35 by aviscogl          #+#    #+#             */
/*   Updated: 2024/12/06 10:18:44 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
			p1 = project_iso(x, y, map->grid[y][x]);// Projette le point actuel en iso
			if (x < map->width - 1)// si pas last colonne draw line vers le pts a droite
			{
				p2 = project_iso(x + 1, y, map->grid[y][x + 1]);
				draw_line(data, p1, p2);
			}
			if (y < map->height - 1)	// si pas last ligne draw line vers le dessous
			{
				p2 = project_iso(x, y + 1, map->grid[y + 1][x]);
				draw_line(data, p1, p2);
			}
			x++;
		}
		y++;
	}
}
