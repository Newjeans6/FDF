/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:30:13 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/02 16:39:58 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int main()
// {
//     void    *mlx;
//     void    *window;
//     mlx =mlx_init();
//     window = mlx_new_window(mlx, 800, 600, "FDF");
//     mlx_loop(mlx);
// }

int	main(void)
{
	t_data data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1080, 920, "First window !");
	if (data.win_ptr == NULL)
		return (MLX_ERROR);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	return (0);
}