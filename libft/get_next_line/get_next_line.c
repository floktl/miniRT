/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fl.keitelgmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:40:04 by fkeitel           #+#    #+#             */
/*   Updated: 2025/08/25 15:12:10 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	grow_if_needed(char **buf, int *end)
{
	char	*new_buf;

	if (*end == 0)
		return (0);
	new_buf = double_bufsize_fill_with_null(*buf);
	if (new_buf == NULL)
		return (-1);
	free(*buf);
	*buf = new_buf;
	return (0);
}

static int	read_once(int fd, char **buf, int *end, int *read_bytes)
{
	*read_bytes = read(fd, *buf + *end, BUFFER_SIZE);
	if (*read_bytes < 0)
		return (-1);
	*end += *read_bytes;
	(*buf)[*end] = '\0';
	return (0);
}

int	read_buf(int fd, char **buf, int *end)
{
	int	read_bytes;

	read_bytes = 1;
	if (ft_check_if_newline(*buf) != NULL)
		return (0);
	while (read_bytes > 0 || *buf == NULL)
	{
		if (grow_if_needed(buf, end) < 0)
			return (-1);
		if (read_once(fd, buf, end, &read_bytes) < 0)
			return (-1);
		if (ft_check_if_newline(*buf))
			break ;
	}
	return (0);
}

static char	*reset_and_null(char **buf, int *i)
{
	free(*buf);
	*buf = NULL;
	*i = 0;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	static int	i = 0;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (reset_and_null(&buf, &i));
	if (!buf)
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	if (read_buf(fd, &buf, &i) == -1 || extract_line(&line, &buf, &i) == NULL)
		return (reset_and_null(&buf, &i));
	if (i == 0)
	{
		free(buf);
		buf = NULL;
	}
	return (line);
}
