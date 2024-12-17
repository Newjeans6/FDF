/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:26:34 by aviscogl          #+#    #+#             */
/*   Updated: 2024/12/17 13:41:48 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_map	*read_map(const char *maps)
{
	char	*line;
	int		fd;
	int		height;
	t_map	*map;

	fd = open(maps, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	grid_alloc_with_minmax(map, maps, height);
	if (!map->grid)
		return (NULL);
	return (map);
}

void	process_row(int *row, char **split, int count, t_map *map)
{
	int	i;

	i = 0;
	while (i < count)
	{
		row[i] = ft_atoi(split[i]);
		if (row[i] < map->min_z)
			map->min_z = row[i];
		if (row[i] > map->max_z)
			map->max_z = row[i];
		i++;
	}
}

int	*parse_line_with_minmax(char *line, int *width, t_map *map)
{
	char	**split;
	int		count;
	int		*row;

	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	count = 0;
	while (split[count])
		count++;
	row = malloc(sizeof(int) * count);
	if (!row)
	{
		free_split(split);
		return (NULL);
	}
	*width = count;
	process_row(row, split, count, map);
	free_split(split);
	return (row);
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
	y = 0 - 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->grid[++y] = parse_line_with_minmax(line, &map->width, map);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
