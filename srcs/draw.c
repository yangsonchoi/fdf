/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:29:02 by yachoi            #+#    #+#             */
/*   Updated: 2022/07/14 12:33:49 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "utils.h"

static void	draw_line(t_img *img, const t_point *p0, const t_point *p1);
static void	draw_line_low(t_img *img, const t_point *p0, const t_point *p1);
static void	draw_line_high(t_img *img, const t_point *p0, const t_point *p1);
static void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

void	draw_image(t_img *img, const t_table *tab)
{
	int	i;
	int	j;

	i = tab->row_size - 1;
	while (i > 0)
	{
		j = tab->col_size - 1;
		while (j > 0)
		{
			draw_line(img, &tab->points[i][j], &tab->points[i][j - 1]);
			draw_line(img, &tab->points[i][j], &tab->points[i - 1][j]);
			--j;
		}
		draw_line(img, &tab->points[i][j], &tab->points[i - 1][j]);
		--i;
	}
	j = tab->col_size -1;
	while (j > 0)
	{
		draw_line(img, &tab->points[i][j], &tab->points[i][j - 1]);
		j--;
	}
}

static void	draw_line(t_img *img, const t_point *p0, const t_point *p1)
{
	if (abs(p1->y - p0->y) < abs(p1->x - p0->x))
	{
		if (p0->x > p1->x)
			draw_line_low(img, p1, p0);
		else
			draw_line_low(img, p0, p1);
	}
	else
	{
		if (p0->y > p1->y)
			draw_line_high(img, p1, p0);
		else
			draw_line_high(img, p0, p1);
	}
}

static void	draw_line_low(t_img *img, const t_point *p0, const t_point *p1)
{
	int		dx;
	int		dy;
	int		determinant;
	int		move;
	t_point	p;

	dx = p1->x - p0->x;
	dy = abs(p1->y - p0->y);
	move = 1;
	if (p1->y - p0->y < 0)
		move = -1;
	determinant = (dy << 1) - dx;
	p = *(t_point *)p0;
	while (p.x < p1->x)
	{
		my_mlx_pixel_put(img, p.x, p.y, p.color.color);
		determinant += dy << 1;
		if (determinant >= 0)
		{
			determinant -= dx << 1;
			p.y += move;
		}
		++p.x;
		color_update(&p, p0, p1);
	}
}

static void	draw_line_high(t_img *img, const t_point *p0, const t_point *p1)
{
	int		dx;
	int		dy;
	int		determinant;
	int		move;
	t_point	p;

	dx = abs(p1->x - p0->x);
	dy = p1->y - p0->y;
	determinant = (dx << 1) - dy;
	move = 1;
	if (p1->x - p0->x < 0)
		move = -1;
	p = *(t_point *)p0;
	while (p.y < p1->y)
	{
		my_mlx_pixel_put(img, p.x, p.y, p.color.color);
		determinant += dx << 1;
		if (determinant >= 0)
		{
			determinant -= dy << 1;
			p.x += move;
		}
		++p.y;
		color_update(&p, p0, p1);
	}
}

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= IMAGE_WIDTH || y < 0 || y >= IMAGE_HEIGHT)
		return ;
	dst = img->addr + (y * img->size_len + (x * (img->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}
