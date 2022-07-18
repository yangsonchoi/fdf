/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:36:25 by yachoi            #+#    #+#             */
/*   Updated: 2022/07/18 12:57:53 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "isometric.h"
#include <math.h>
#include <draw.h>
#include <parse.h>

static void	isometric_point(t_point *p, const double angle);
static void	move_to_mid(t_point *p, int mid_x, int mid_y);

void	isometric_transformation(t_table *tab, int case_size)
{
	double	rotate_angle;
	int		mid_x;
	int		mid_y;
	int		i;
	int		j;

	rotate_angle = M_PI / 6;
	i = 0;
	mid_x = IMAGE_WIDTH / 2 + (int)round((tab->col_size - tab->row_size) \
			* sin(rotate_angle)) / 2 * case_size;
	mid_y = (IMAGE_HEIGHT / 2) - (int)round((tab->col_size + tab->row_size) \
			* sin(rotate_angle)) / 2 * case_size;
	while (i < tab->col_size)
	{
		j = 0;
		while (j < tab->row_size)
		{
			isometric_point(&tab->points[i][j], rotate_angle);
			move_to_mid(&tab->points[i][j], mid_x, mid_y);
			++j;
		}
		++i;
	}
}

static void	isometric_point(t_point *p, const double angle)
{
	int	x_before;
	int	y_before;

	x_before = p->x;
	y_before = p->y;
	p->x = (int)round((x_before - y_before) * cos(angle));
	p->y = ((int)round((x_before + y_before) * sin(angle))) + p->z;
}

static void	move_to_mid(t_point *p, int mid_x, int mid_y)
{
	p->x += mid_x;
	p->y += mid_y;
}
