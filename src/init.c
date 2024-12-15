/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:30:13 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/15 16:55:04 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *map)
{
	int	i;

	if (map)
	{
		if (map->grid)
		{
			i = 0;
			while (i < map->height)
			{
				free(map->grid[i]);
				i++;
			}
			free(map->grid);
		}
		free(map);
	}
}

int	close_window(t_data *data)
{
	free_map(data->map);
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int	initialize_data(t_data *data, t_map *map)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	data->img = mlx_new_image(data->mlx_ptr, WIN_HEIGHT, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->scale = 1.0;
	data->map = map;
	data->angle = ANGLE;
	data->cam_x = 0;
	data->cam_y = 0;
	data->deep = 0.285;
	data->flag = 1;
	return (data->mlx_ptr && data->win_ptr && data->img && data->addr);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_data	data;

	if (argc != 2)
		return (error_handler(1, "Usage: ./fdf map_file"));
	map = read_map(argv[1]);
	if (!map)
		return (error_handler(2, "Failed to read map"));
	if (!initialize_data(&data, map))
		return (error_handler(3, "Failed to initialize data"));
	draw_map(&data, map);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_hook(data.win_ptr, DESTROY, 0, close_window, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

int	error_handler(int error_code, char *message)
{
	ft_putendl_fd(message, 2);
	return (error_code);
}
