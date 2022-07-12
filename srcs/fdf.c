/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:47:00 by yachoi            #+#    #+#             */
/*   Updated: 2022/07/09 14:21:04 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include "mlx.h"
#include "parse.h"
#include "isometric.h"
#include "draw.h"
#include "utils.h"

#define ESC_KEY 53

static int	terminate(int key_input, t_vars *vars);

int	main(int argc, char **argv)
{
	t_table	tab;
	t_vars	vars;
	t_img	img;

	parse_map_to_tab(argc, argv, &tab);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, IMAGE_WIDTH, IMAGE_HEIGHT, "tothemoon");
	img.img = mlx_new_image(vars.mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_len, &img.endian);
	isometric_transformation(&tab);
	draw_image(&img, &tab);
	free_points(&tab);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_destroy_image(vars.mlx, img.img);
	mlx_key_hook(vars.win, terminate, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

static int	terminate(int key_input, t_vars *vars)
{
	if (key_input == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
