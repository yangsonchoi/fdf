#ifndef UTILS_H
# define UTILS_H

# include "parse.h"

void			exit_msg(const char *str);
int				abs(int n);
unsigned int	parse_color(const char *str, t_table *tab);
void			color_update(t_point *p, const t_point *p0, const t_point *p1);
void			free_points(t_table *tab);

#endif