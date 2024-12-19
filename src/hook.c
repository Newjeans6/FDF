/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:47:09 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/19 12:13:43 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_hook(int button, int x, int y, t_data *data)
{
	(void)y;
	(void)x;
	if (button == CLICK)
		data->deep *= 1.2;
	else if (button == RIGHT_CLICK)
		data->deep *= 0.7;
	if (button == ZOOM_IN)
		data->scale *= 1.1;
	else if (button == ZOOM_OUT)
		data->scale /= 1.1;
	ft_memset(data->addr, 0, (data->line_length * WIN_HEIGHT));
	draw_map(data, data->map);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	key_mouv(keycode, data);
	if (keycode == ESC_KEY)
	{
		free_map(data->map);
		mlx_destroy_image(data->mlx_ptr, data->img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(0);
	}
	if (keycode == A || keycode == D)
	{
		if (keycode == A)
			data->angle = 0;
		if (keycode == D)
			data->angle = ANGLE;
		ft_memset(data->addr, 0, (data->line_length * WIN_HEIGHT));
		draw_map(data, data->map);
		return (0);
	}
	return (0);
}

int	key_mouv(int keycode, t_data *data)
{
	if (keycode == DOWN)
		data->cam_y -= 50;
	if (keycode == UP)
		data->cam_y += 50;
	if (keycode == LEFT)
		data->cam_x += 50;
	if (keycode == RIGHT)
		data->cam_x -= 50;
	ft_memset(data->addr, 0, (data->line_length * WIN_HEIGHT));
	draw_map(data, data->map);
	return (0);
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

void	cleanup_data(t_data *data, t_map *map)
{
	if (data)
	{
		if (data->img)
		{
			mlx_destroy_image(data->mlx_ptr, data->img);
			data->img = NULL;
		}
		if (data->win_ptr)
		{
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
			data->win_ptr = NULL;
		}
		if (data->mlx_ptr)
		{
			mlx_destroy_display(data->mlx_ptr);
			free(data->mlx_ptr);
			data->mlx_ptr = NULL;
		}
	}
	if (map)
		free_map(map);
}
