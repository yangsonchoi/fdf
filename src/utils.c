#include "utils.h"
#include "parse.h"
#include "../libft/libft.h"

void	exit_msg(const char *str)
{
	write(STDERR, str, ft_strlen(str));
	exit(EXIT_FAILURE);
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
