/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:30:13 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/08 14:45:37 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	key_hook(int keycode, t_data *data)
{
	//t_map	*map;

	if (keycode == ESC_KEY)
	{
		mlx_destroy_image(data->mlx_ptr, data->img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		// for (int y = 0; y < map->height; y++)
		// {
		// 	free(map->grid[y]);
		// }
		// free(map->grid);
		// free(map);
		exit(0);
	}
	return (0);
}

int	close_window(t_data *data)
{
	//t_map	*map;

	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	// for (int y = 0; y < map->height; y++)
	// {
	// 	free(map->grid[y]);
	// }
	// free(map->grid);
	// free(map);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_map		*map;
	t_window	window = {1920, 1080};
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
	// printf("Map dimensions: %d x %d\n", map->width, map->height);
	// for (int y = 0; y < map->height; y++)
	// {
	//     for (int x = 0; x < map->width; x++)
	//     {
	//         printf("%2d ", map->grid[y][x]);
	//     }
	//     printf("\n");
	// }
	// for (int y = 0; y < map->height; y++)
	// {
	//     free(map->grid[y]);
	// }
	// free(map->grid);
	// free(map);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, window.width, window.height,
			"FDF");
	draw_map(&data, map, &window);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_hook(data.win_ptr, DESTROY, 0, close_window, &data);
	mlx_loop(data.mlx_ptr);
	free(map);
	return (0);
}
