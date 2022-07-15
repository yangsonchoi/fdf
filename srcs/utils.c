/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:43:20 by yachoi            #+#    #+#             */
/*   Updated: 2022/07/14 12:43:24 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include "parse.h"
#include "../libft/libft.h"

void	exit_msg(const char *str)
{
	ft_putstr_fd((char *)str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

unsigned int	parse_color(const char *str, t_table *tab)
{
	char			*ptr;
	unsigned int	color;

	ptr = ft_strchr(str, ',');
	if (ptr == NULL)
		return (0x00FFFFFF);
	if (tab->color_use == 0)
		tab->color_use = 1;
	ptr += 3;
	color = 0;
	while (*ptr != '\0')
	{
		color *= 16;
		if (ft_isdigit(*ptr))
			color += *ptr - '0';
		else if ('a' <= *ptr && *ptr <= 'f')
			color += *ptr - 'a' + 10;
		else if ('A' <= *ptr && *ptr <= 'F')
			color += *ptr - 'A' + 10;
		else
			break ;
		++ptr;
	}
	return (color);
}

void	color_update(t_point *p, const t_point *p0, const t_point *p1)
{
	int	grad;
	int	dt;
	int	dr;
	int	dg;
	int	db;

	dt = (int)p1->color.trgb[3] - (int)p0->color.trgb[3];
	dr = (int)p1->color.trgb[2] - (int)p0->color.trgb[2];
	dg = (int)p1->color.trgb[1] - (int)p0->color.trgb[1];
	db = (int)p1->color.trgb[0] - (int)p0->color.trgb[0];
	if (abs(p1->x - p0->x) < abs(p1->y - p0->y))
		grad = abs(p->y - p0->y) / abs(p1->y - p0->y);
	else
		grad = abs(p->x - p0->x) / abs(p1->x - p0->x);
	p->color.trgb[3] = p0->color.trgb[3] + grad * dt;
	p->color.trgb[2] = p0->color.trgb[2] + grad * dr;
	p->color.trgb[1] = p0->color.trgb[1] + grad * dg;
	p->color.trgb[0] = p0->color.trgb[0] + grad * db;
}

void	free_points(t_table *tab)
{
	int	i;

	i = 0;
	while (i < tab->col_size)
	{
		free(tab->points[i]);
		++i;
	}
	free(tab->points);
}
