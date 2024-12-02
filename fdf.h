/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:48:31 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/02 16:36:55 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef fdf_h
# define fdf_h

#include "minilibx-linux/mlx.h"
#include <stddef.h>


#define MLX_ERROR 1
#define ESC_KEY 27
#define DESTROY 17  

typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
} t_data;

#endif