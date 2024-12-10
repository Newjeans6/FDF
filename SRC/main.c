/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:30:13 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/10 12:09:54 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(0);
	}
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_map		*map;
	t_window	window = {2000, 3000};
	int y;
	
	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	map = read_map(argv[1]);
	if (!map)
	{
		printf("Failed to read map.\n");
		return (1);
	}
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, window.width, window.height,
			"FDF");
	draw_map(&data, map, &window);
	y = -1;
	while (y++ < map->height -1)
		free(map->grid[y]);
	free(map->grid);
	free(map);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_hook(data.win_ptr, DESTROY, 0, close_window, &data);
	mlx_loop(data.mlx_ptr);
	free(map);
	return (0);
}
