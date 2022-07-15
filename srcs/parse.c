/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:42:36 by yachoi            #+#    #+#             */
/*   Updated: 2022/07/14 12:42:49 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <fcntl.h>
#include "utils.h"
#include "get_next_line.h"
#include "../libft/libft.h"

#define CASE_CONSTANT 1000

static void		gnl_map_to_tab(int fd, t_table *tab);
static t_point	*new_point(char **words, t_table *tab);
static void		list_to_tab(t_table *tab, t_list *head);
static void		plot_point(t_table *tab, const int case_size, const int z_size);

int	parse_map_to_tab(int argc, char **argv, t_table *tab)
{
	int	fd;
	int	case_size;
	int	z_size;

	if (argc < 2 || argc == 3 || argc > 4)
		exit_msg("Usage : ./fdf <filename> [ case_size z_size ]");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_msg("open failed");
	gnl_map_to_tab(fd, tab);
	if (close(fd) == -1)
		exit_msg("close failed");
	if (tab->col_size > tab->row_size)
		case_size = CASE_CONSTANT / tab->col_size;
	else
		case_size = CASE_CONSTANT / tab->row_size;
	z_size = case_size;
	if (argc == 4)
	{
		case_size = ft_atoi(argv[2]);
		z_size = ft_atoi(argv[3]);
	}
	plot_point(tab, case_size, z_size);
	return (case_size);
}

static void	gnl_map_to_tab(int fd, t_table *tab)
{
	char	*line;
	char	**words;
	t_list	*point_list;
	t_list	*new_list;

	tab->col_size = 0;
	tab->row_size = 0;
	tab->color_use = 0;
	point_list = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		words = ft_split(line, ' ');
		free(line);
		if (words == NULL)
			exit_msg("ft_split failed");
		new_list = ft_lstnew(new_point(words, tab));
		free(words);
		if (new_list == NULL)
			exit_msg("ft_lstnew falied");
		ft_lstadd_back(&point_list, new_list);
		line = get_next_line(fd);
	}
	list_to_tab(tab, point_list);
}

static t_point	*new_point(char **words, t_table *tab)
{
	t_point	*point;
	int		i;

	i = 0;
	while (words[i] != NULL && ft_isdigit(*words[i]))
		++i;
	if (tab->row_size == 0)
		tab->row_size = i;
	else if (i != tab->row_size)
		exit_msg("Found worng line length. Exiting.");
	point = malloc(sizeof(*point) * i);
	if (point == NULL)
		exit_msg("new_point malloc failed");
	i = 0;
	while (words[i] != NULL && ft_isdigit(*words[i]))
	{
		point[i].z = ft_atoi(words[i]);
		point[i].color.color = parse_color(words[i], tab);
		free(words[i]);
		i++;
	}
	tab->col_size += 1;
	return (point);
}

static void	list_to_tab(t_table *tab, t_list *head)
{
	t_list	*curr;
	int		i;

	tab->points = malloc(sizeof(*tab->points) * tab->col_size);
	if (tab->points == NULL)
		exit_msg("list_to_tab malloc failed");
	curr = head;
	i = 0;
	while (curr != NULL)
	{
		tab->points[i] = curr->content;
		i++;
		head = curr->next;
		free(curr);
		curr = head;
	}
}

static void	plot_point(t_table *tab, const int case_size, const int z_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < tab->col_size)
	{
		j = 0;
		while (j < tab->row_size)
		{
			tab->points[i][j].x = j * case_size;
			tab->points[i][j].y = i * case_size;
			tab->points[i][j].z *= z_size * -1;
			j++;
		}
		i++;
	}
}


