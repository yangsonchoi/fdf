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
#include <unistd.h>
#include "parse.h"
#include "../libft/libft.h"

void	exit_msg(const char *str)
{
	ft_putstr_fd((char *)str, STDERR_FILENO);
	exit(EXIT_FAILURE);
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
