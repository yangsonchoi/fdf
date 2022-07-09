#ifndef PARSE_H
# define PARSE_H

typedef union u_color
{
	unsigned int	color;
	unsigned char	trgb[4];
}	t_color;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	t_color	color;
}	t_point;

typedef struct s_table
{
	int		row_size;
	int		col_size;
	int		height;
	int		color_use;
	t_point	**points;
}	t_table;

void	parse_map_to_tab(int argc, char **argv, t_table *tab);

#endif
