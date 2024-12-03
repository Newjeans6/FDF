/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:48:31 by pnaessen          #+#    #+#             */
/*   Updated: 2024/12/03 16:03:10 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
//# include <./X11/Keysym.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

# define MLX_ERROR 1
# define ESC_KEY 65307
# define DESTROY 17
# define KeyPress 02

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr_ptr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}			t_data;

typedef struct img_s
{
	void	*img;
	char	*./pnaessen.xpm;
	int		img_width;
	int		img_height;
}			img_t;

#endif