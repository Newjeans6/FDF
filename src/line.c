/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:19:00 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/13 15:08:01 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map_line(t_data *data, t_map *map, int x, int y, float scale)
{
	t_point	p1;
	t_point	p2;

	p1 = project_iso(x, y, map->grid[y][x], scale);
	p1.color = calculate_color(map->grid[y][x], map->min_z, map->max_z);
	if (x < map->width - 1)
	{
		p2 = project_iso(x + 1, y, map->grid[y][x + 1], scale);
		p2.color = calculate_color(map->grid[y][x + 1], map->min_z, map->max_z);
		draw_line(data, p1, p2);
	}
	if (y < map->height - 1)
	{
		p2 = project_iso(x, y + 1, map->grid[y + 1][x], scale);
		p2.color = calculate_color(map->grid[y + 1][x], map->min_z, map->max_z);
		draw_line(data, p1, p2);
	}
}

int	*parse_line_with_minmax(char *line, int *width, t_map *map)
{
	char	**split;
	int		count;
	int		*row;
	int		i;

	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	count = 0;
	while (split[count] != NULL)
		count++;
	row = malloc(sizeof(int) * count);
	if (!row)
		return (free_split(split), NULL);
	*width = count;
	i = -1;
	while (++i < count)
	{
		row[i] = ft_atoi(split[i]);
		if (row[i] < map->min_z)
			map->min_z = row[i];
		if (row[i] > map->max_z)
			map->max_z = row[i];
		free(split[i]);
	}
	return (free(split), row);
}

void	grid_alloc_with_minmax(t_map *map, const char *maps, int height)
{
	char	*line;
	int		fd;
	int		y;

	map->grid = malloc(sizeof(int *) * height);
	if (!map->grid)
	{
		free(map);
		return ;
	}
	map->height = height;
	fd = open(maps, O_RDONLY);
	if (fd < 0)
		return ;
	map->min_z = INT_MAX;
	map->max_z = INT_MIN;
	y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->grid[y] = parse_line_with_minmax(line, &map->width, map);
		free(line);
		y++;
	}
	close(fd);
}
