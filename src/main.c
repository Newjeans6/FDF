/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:30:13 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/14 14:18:53 by pnaessen         ###   ########lyon.fr   */
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

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_image(data->mlx_ptr, data->img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(0);
	}
	printf("keycode = %d\n", keycode);
	return (0);
}
int	mouse_hook(int button, int x, int y, t_data *data)
{
	(void)y;
	(void)x;
	if (button == ZOOM_IN)
		data->scale *= 1.1;
	else if (button == ZOOM_OUT)
		data->scale /= 1.1;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	ft_memset(data->addr, 0, WinWidth * WinHeight * (data->bits_per_pixel / 8));
	draw_map(data, data->map);
	return (0);
}
int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_data	data;

	data.flag = 0;
	if (argc != 2)
		return (1);
	map = read_map(argv[1]);
	if (!map)
		return (1);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WinWidth, WinHeight, "FDF");
	data.img = mlx_new_image(data.mlx_ptr, WinWidth, WinHeight);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	data.scale = 1.0;
	data.map = map;
	if (data.map)
	{
		data.flag = 1;
		draw_map(&data, map);
	}
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 0, 0);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_mouse_hook(data.win_ptr, (int (*)(int, int, int, void *))mouse_hook,
		&data);
	mlx_hook(data.win_ptr, DESTROY, 0, close_window, &data);
	free_map(map);
	mlx_loop(data.mlx_ptr);
	return (0);
}
