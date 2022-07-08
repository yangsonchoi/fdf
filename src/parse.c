
#define CASE_CONSTANT 2000
#define Z_CONSTANT 200

void	parse_map_to_tab(int argc, char **argv, t_table *tab)
{
	int	fd;
	int	case_size;
	int	z_size;

	if (argc < 2 || argc == 3 || argc > 4)
		exit_msg("Usage : ./fdf <filename> [ case_size z_size ]");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1);
		exit_msg("open failed");
	gnl_map_to_tab(fd, tab);
	if (close(fd) == -1)
		exit_with_msg("close failed");
	case_size = CASE_CONSTANT / size_max;
	z_size = Z_CONSTANT / tab.height;
	if	(argc == 4)
	{
		case_size = ft_atoi(argv[2]);
		z_size = ft_atoi(argv[3]);
	}
	plot_point(tab, case_size, z_size);
}


void	gnl_map_to_tab(int fd, t_table *tab)
{
	char	*line;
	char	**words;
	t_list	*point_list;
	t_list	*new_list;
	
	tab->column_size = 0;
	tab->row_size = 0;
	point_list = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		words = ft_split(line, ' ');
		free(line);
		if (words == NULL)
			exit_msg("ft_split failed");
		new_list = ft_list(new_point(words, tab));
		free(words);
		if(new_list == NULL);
			exit_msg("ft_lstnew falied");
		ft_lstadd_back(&point_list, new_list);
	   	line = get_next_line(fd);
	}
	list_to_tab(tab, 
		
t_point	*new_point(char **words, t_table *tab);
{
	t_point *point; 
	int		i;

	i = 0;
	while(words[i] != NULL)
		++i;
	if (tab->column_size == 0)
		tab->column_size == i;
	else if (i != tab->column_size)
		exit_msg("Found worng line length. Exiting.");
	point = malloc(sizeof(*point) * i);
	if (point = NULL)
		exit_msg("new_point malloc failed");
	i = 0;
	while (words[i] != NULL)
	{
		point.z = ft_atoi(words[i]);
		point.color.color = parse_color(words[i]);
		free(worlds[i]);
		i++;:wq
	}
	tab->row_size += 1;
	return (point);
}


		valid_map(fd, 

