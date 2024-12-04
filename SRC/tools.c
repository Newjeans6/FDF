/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:26:34 by aviscogl          #+#    #+#             */
/*   Updated: 2024/12/04 21:26:34 by aviscogl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>

t_map *read_map(const char *maps)
{
    int fd = open(maps, O_RDONLY);
    if (fd < 0)
        return (NULL);  
    char *line = NULL;
    t_map *map = malloc(sizeof(t_map)); // mémoire pour la structure 
    if (!map)
        return (NULL);
    int height = 0; // Compter le nombre de lignes  
    while (get_next_line(fd, &line) > 0) {
        height++;
        free(line);
    }
    close(fd);    
    map->grid = malloc(sizeof(int *) * height); // mémoire pour la grille (tableau 2D) map->grid correspond à une ligne de la mqp.
    if (!map->grid)
        return (free(map), NULL);
    map->height = height; // hauteur de la carte
    fd = open(maps, O_RDONLY);
    if (fd < 0)
        return (NULL);
    int y = 0;
    while (y < height) {
        if (get_next_line(fd, &line) <= 0) // Remplir la grille 
            break;
        map->grid[y] = parse_line(line, &map->width);
        free(line);
        y++;
    }
    close(fd);
    return (map);
}


int *parse_line(char *line, int *width)
{
    char **split = ft_split(line, ' ');
    if (!split)
        return (NULL);
    int count = count_words(split);
    int *row = malloc(sizeof(int) * count);
    if (!row)
        return (free_split(split), NULL);
    *width = count;
    int i = 0;
    while (split[i]) {
        row[i] = ft_atoi(split[i]);
        free(split[i]);
        i++;
    }
    free(split);
    return (row);
}
t_point project_iso(int x, int y, int z)
{
    t_point point;

    point.x = (x - y) * 0.866; //(cos)
    point.y = (x + y) * 0.5 - z; //z = profondeur (sinus)
    return (point);
}