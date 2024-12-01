/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:26:43 by pnaessen          #+#    #+#             */
/*   Updated: 2024/11/29 13:11:11 by pnaessen         ###   ########lyon.fr   */
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

int main (void)
{
    t_data  data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr)
        return (MLX_ERROR);
    data.win_ptr = mlx_new_window(data.mlx_ptr, 1080, 920, "First window !");
    if (data.win_ptr)
        return (MLX_ERROR);
    mlx_destroy_window(data.mlx_ptr, data.win_ptr);
    return (0);
}