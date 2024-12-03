/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:30:13 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/03 16:11:29 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
        mlx_destroy_image(data->mlx_ptr, data->img_ptr);
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);    
		exit(0);
	}
	printf("Key code : %d\n", keycode);
	return (0);
}

int	close_window(t_data *data)
{
    mlx_destroy_image(data->mlx_ptr, data->img_ptr);
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr); 
    exit(0);
	return (0);
}
int	main(void)
{
	t_data	data;
	img_t	img;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (free(data.mlx_ptr), MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1080, 920, "First window !");
	if (data.win_ptr == NULL)
		return (MLX_ERROR);
    img.img_path = "pnaessen.xpm";
	img.img = mlx_xpm_file_to_image(data.mlx_ptr, img.img_path, &img.img_width,
			&img.img_height);
    if (img.img == NULL)
         return (free(data.mlx_ptr), MLX_ERROR);    
	//data.img_ptr = mlx_new_image(data.mlx_ptr, 1080, 920);
	//data.addr_ptr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel,
	//		&data.line_lenght, &data.endian);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_hook(data.win_ptr, DESTROY, 0, close_window, &data);
	mlx_hook(data.win_ptr, KeyPress, 0, key_hook, &data);
	mlx_loop(data.mlx_ptr);
    free(data.mlx_ptr); 
	return (0);
}
