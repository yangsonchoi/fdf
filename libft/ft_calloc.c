/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 02:09:21 by yachoi            #+#    #+#             */
/*   Updated: 2022/02/06 02:09:22 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*tmp;

	tmp = malloc(nelem * elsize);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, (nelem * elsize));
	return (tmp);
}
