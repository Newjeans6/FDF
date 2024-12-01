/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:48:31 by pnaessen          #+#    #+#             */
/*   Updated: 2024/11/30 12:42:34 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef fdf_h
# define fdf_h

#include "../minilibx-linux/mlx.h"

#define MLX_ERROR 1

typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
} t_data;

#endif