	#include <math.h>
#include "isometric.h"
#include "draw.h"
#include "utils.h"

typedef enum e_axis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
}	t_axis;

static void	rotate_point(t_point *p, const double angle, const t_axis axis);
static void	translate_point(t_point *p, const int n, const t_axis axis);

void	transform_points_mandatory(t_table *tab)
{
	const double	angle_about_x = atan(M_SQRT2);
	const double	angle_about_z = -M_PI_4;
	int				i;
	int				j;

	i = 0;
	while (i < tab->row_size)
	{
		j = 0;
		while (j < tab->column_size)
		{
			rotate_point(&tab->points[i][j], angle_about_z, Z_AXIS);
			rotate_point(&tab->points[i][j], angle_about_x, X_AXIS);
			translate_point(&tab->points[i][j], IMAGE_WIDTH / 2, X_AXIS);
			translate_point(&tab->points[i][j], IMAGE_HEIGHT - 1, Y_AXIS);
			++j;
		}
		++i;
	}
}

static void	rotate_point(t_point *p, const double angle, const t_axis axis)
{
	int	new_val;

	if (axis == X_AXIS)
	{
		new_val = (int)round(p->y * cos(angle) - p->z * sin(angle));
		p->z = (int)round(p->y * sin(angle) + p->z * cos(angle));
		p->y = new_val;
	}
	else if (axis == Y_AXIS)
	{
		new_val = (int)round(p->z * cos(angle) - p->x * sin(angle));
		p->x = (int)round(p->z * sin(angle) + p->x * cos(angle));
		p->z = new_val;
	}
	else if (axis == Z_AXIS)
	{
		new_val = (int)round(p->x * cos(angle) - p->y * sin(angle));
		p->y = (int)round(p->x * sin(angle) + p->y * cos(angle));
		p->x = new_val;
	}
	else
		exit_with_message("Invalid axis");
}

static void	translate_point(t_point *p, const int distance, const t_axis axis)
{
	if (axis == X_AXIS)
	{
		p->x += distance;
	}
	else if (axis == Y_AXIS)
	{
		p->y += distance;
	}
	else if (axis == Z_AXIS)
	{
		p->z += distance;
	}
	else
		exit_with_message("Invalid axis");
}