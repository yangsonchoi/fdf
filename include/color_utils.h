#ifndef COLOR_UTILS_H
# define COLOR_UTILS_H
# include "parse.h"

int				abs(int n);
unsigned int	parse_color(const char *str, t_table *tab);
void			color_update(t_point *p, const t_point *p0, const t_point *p1);

#endif