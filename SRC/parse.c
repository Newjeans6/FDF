/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:26:34 by aviscogl          #+#    #+#             */
/*   Updated: 2024/12/08 12:33:57 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../Libft/libft.h"
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
t_map	*read_map(const char *maps) // grid tableau 2D dynamique
{
	char *line;

	int fd = open(maps, O_RDONLY);
	if (fd < 0)
		return (NULL);
	t_map *map = malloc(sizeof(t_map)); // mémoire pour la structure
	if (!map)
		return (NULL);
	int height = 0; // Compter le nombre de lignes
	while ((line = get_next_line(fd)) != NULL)
	{
		height++;
		free(line);
	}
	close(fd);
	map->grid = malloc(sizeof(int *) * height);
		// mémoire pour la grille (tableau 2D) map->grid correspond à une ligne de la map.
	if (!map->grid)
		return (free(map), NULL);
	map->height = height; // hauteur de la carte
	fd = open(maps, O_RDONLY);
	if (fd < 0)
		return (NULL);
	int y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->grid[y] = parse_line(line, &map->width);
			// grid[y] une ligne  de la map donc devient un tableau de int
		free(line);
		y++;
	}
	close(fd);
	return (map);
}


