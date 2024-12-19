/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:30:13 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/19 12:13:50 by pnaessen         ###   ########lyon.fr   */
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

int	validate_file(const char *fd)
{
	const char	*extension = ".fdf";
	size_t		ext_len;
	size_t		len;
	int			file_descriptor;

	ext_len = ft_strlen(extension);
	len = ft_strlen(fd);
	if (len < ext_len || ft_strncmp(fd + len - ext_len, extension,
			ext_len) != 0)
	{
		return (error_handler(2, "File must have a .fdf extension"));
	}
	file_descriptor = open(fd, O_RDONLY);
	if (file_descriptor == -1)
		return (error_handler(2, "File does not exist or cannot be accessed"));
	close(file_descriptor);
	return (0);
}

t_data	initialize_data(t_map *map)
{
	t_data	data;

	data.img = NULL;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (free_map(map), data);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (!data.win_ptr)
		return (cleanup_data(&data, map), data);
	data.img = mlx_new_image(data.mlx_ptr, WIN_HEIGHT, WIN_HEIGHT);
	if (!data.img)
		return (cleanup_data(&data, map), data);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	if (!data.addr)
		return (cleanup_data(&data, map), data);
	data.scale = 1.0;
	data.map = map;
	data.angle = ANGLE;
	data.cam_x = 0;
	data.cam_y = 0;
	data.deep = 0.285;
	data.flag = 1;
	return (data);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_data	data;

	if (argc != 2)
		return (error_handler(1, "Usage: ./fdf map_file"));
	if (validate_file(argv[1]) != 0)
		return (2);
	map = read_map(argv[1]);
	if (!map)
		return (error_handler(2, "Failed to read map"));
	if (map->width == 0)
		return (free(map->grid), free(map), error_handler(2,
				"Failed to read map"));
	data = initialize_data(map);
	if (!data.mlx_ptr || !data.win_ptr || !data.img || !data.addr)
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
