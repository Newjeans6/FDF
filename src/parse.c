/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:26:34 by aviscogl          #+#    #+#             */
/*   Updated: 2024/12/11 14:10:17 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>

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

int	*parse_line(char *line, int *width)
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
	*width = count; // Stocke le nombre d'éléments dans la ligne
	i = 0;
	while (i < count)
	{
		row[i] = ft_atoi(split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	return (row);
}

void	grid_alloc(t_map *map, const char *maps, int height)
{
	char	*line;
	int		fd;
	int		y;

	line = NULL;
	map->grid = malloc(sizeof(int *) * height);
	// mémoire pour la grille  map->grid = une ligne de la map.
	if (!map->grid)
	{
		free(map);
		return ;
	}
	map->height = height; // hauteur de la carte
	fd = open(maps, O_RDONLY);
	if (fd < 0)
		return ;
	y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->grid[y] = parse_line(line, &map->width);
		free(line);
		y++;
	}
	close(fd);
	return ;
}

t_map	*read_map(const char *maps) // grid tableau 2D dynamique
{
	char *line;
	int fd;
	int height;
	t_map *map;

	line = NULL;
	fd = open(maps, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_map)); // mémoire pour la structure
	if (!map)
		return (NULL);
	height = 0; // Compter le nombre de lignes
	while ((line = get_next_line(fd)) != NULL)
	{
		height++;
		free(line);
	}
	close(fd);
	grid_alloc(map, maps, height);
	if (!map->grid)
		return (NULL);
	return (map);
}
