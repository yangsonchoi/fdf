#include "color_utils.h"
#include <stdlib.h>
#include "parse.h"
#include "../libft/libft.h"

static void	trans_update(t_point *p, const t_point *p0, const t_point *p1);

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
	int	step;
	int	grad;
	int	dr;
	int	dg;
	int	db;

	dr = (int)p1->color.trgb[2] - (int)p0->color.trgb[2];
	dg = (int)p1->color.trgb[1] - (int)p0->color.trgb[1];
	db = (int)p1->color.trgb[0] - (int)p0->color.trgb[0];
	if (abs(p1->x - p0->x) < abs(p1->y - p0->y))
	{
		step = abs(p->y - p0->y);
		grad = abs(p1->y - p0->y);
	}
	else
	{
		step = abs(p->x - p0->x);
		grad = abs(p1->x - p0->x);
	}
	p->color.trgb[2] = p0->color.trgb[2] + (step * dr) / grad;
	p->color.trgb[1] = p0->color.trgb[1] + (step * dg) / grad;
	p->color.trgb[0] = p0->color.trgb[0] + (step * db) / grad;
	trans_update(p, p0, p1);
}

static void	trans_update(t_point *p, const t_point *p0, const t_point *p1)
{
	int	step;
	int	grad;
	int	dt;

	dt = (int)p1->color.trgb[3] - (int)p0->color.trgb[3];
	if (abs(p1->x - p0->x) < abs(p1->y - p0->y))
	{
		step = abs(p->y - p0->y);
		grad = abs(p1->y - p0->y);
	}
	else
	{
		step = abs(p->x - p0->x);
		grad = abs(p1->x - p0->x);
	}
	p->color.trgb[3] = p0->color.trgb[3] + (step * dt) / grad;
}
