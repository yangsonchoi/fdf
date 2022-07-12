#ifndef DRAW_H
# define DRAW_H
# define IMAGE_WIDTH 1920
# define IMAGE_HEIGHT 1080
# include "parse.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_len;
	int		endian;
}	t_img;

void	draw_image(t_img *img, const t_table *tab);

#endif