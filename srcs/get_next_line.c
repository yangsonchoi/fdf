/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:53:02 by yachoi            #+#    #+#             */
/*   Updated: 2022/04/12 17:10:38 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include "../libft/libft.h"

static char	*ft_read_line(int fd, char *stt_str);
static char	*ft_stt_strjoin(char *stt_str, char *buf);
static char	*ft_cut_result(char *stt_str);
static char	*ft_new_stt_str(char *stt_str);

char	*get_next_line(int fd)
{
	char		*result;
	static char	*stt_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stt_str = ft_read_line(fd, stt_str);
	if (stt_str == NULL)
		return (NULL);
	result = ft_cut_result(stt_str);
	stt_str = ft_new_stt_str(stt_str);
	return (result);
}

static char	*ft_read_line(int fd, char *stt_str)
{
	char	*buf;
	int		read_len;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	while (ft_strchr(stt_str, '\n') == 0)
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len == -1)
		{
			free(buf);
			return (NULL);
		}
		if (read_len == 0)
		{
			free(buf);
			return (stt_str);
		}
		buf[read_len] = '\0';
		stt_str = ft_stt_strjoin(stt_str, buf);
	}
	free(buf);
	return (stt_str);
}

static char	*ft_stt_strjoin(char *stt_str, char *buf)
{
	char	*str;

	if (stt_str == NULL)
	{
		stt_str = (char *)malloc(1 * sizeof(char));
		if (stt_str == NULL)
			return (NULL);
		stt_str[0] = '\0';
	}
	str = ft_strjoin(stt_str, buf);
	free(stt_str);
	stt_str = NULL;
	return (str);
}

static char	*ft_cut_result(char *stt_str)
{
	int		len;
	char	*str;

	if (stt_str[0] == '\0')
		return (NULL);
	len = 0;
	while (stt_str[len] && stt_str[len] != '\n')
		len++;
	if (stt_str[len] == '\n')
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, stt_str, len + 1);
	return (str);
}

static char	*ft_new_stt_str(char *stt_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (stt_str[i] && stt_str[i] != '\n')
		i++;
	if (stt_str[i] == '\0')
	{
		free(stt_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(stt_str) - i + 1));
	if (str == NULL)
		return (NULL);
	i++;
	j = 0;
	while (stt_str[i])
		str[j++] = stt_str[i++];
	str[j] = '\0';
	free(stt_str);
	stt_str = NULL;
	return (str);
}
