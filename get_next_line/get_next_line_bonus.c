/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:41:25 by yrachidi          #+#    #+#             */
/*   Updated: 2024/12/04 18:30:05 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_free(char **buffer)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

char	*get_after(char *buffer)
{
	char	*line_location;
	char	*after;
	size_t	len;

	line_location = ft_strchr(buffer, '\n');
	if (!line_location)
		return (NULL);
	line_location++;
	len = ft_strlen(line_location);
	after = ft_calloc(len + 1, 1);
	if (!after)
		return (ft_free(&buffer), NULL);
	ft_memcpy(after, line_location, len);
	return (after);
}

char	*get_before(char *buffer)
{
	char	*before;
	int		i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	before = ft_calloc(i + 1, 1);
	if (!before)
		return (NULL);
	ft_memcpy(before, buffer, i);
	return (before);
}

char	*get_full_line(int fd, char *rbuf)
{
	int		return_bytes;
	char	*buffer;
	char	*tmp;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (ft_free(&rbuf), NULL);
	while (1)
	{
		return_bytes = read(fd, buffer, BUFFER_SIZE);
		if (return_bytes < 0)
			return (ft_free(&buffer), ft_free(&rbuf), NULL);
		if (return_bytes == 0)
			break ;
		buffer[return_bytes] = '\0';
		tmp = ft_strjoin(rbuf, buffer);
		ft_free(&rbuf);
		rbuf = tmp;
		if (!rbuf)
			return (ft_free(&buffer), NULL);
		if (ft_strchr(rbuf, '\n'))
			break ;
	}
	ft_free(&buffer);
	return (rbuf);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;
	char 		*remaining;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || fd >= MAX_FD)
		return (NULL);
	buffer[fd] = get_full_line(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	if (buffer[fd] && !*buffer[fd])
	{
		ft_free(&buffer[fd]);
		return (NULL);
	}
	if (ft_strchr(buffer[fd], '\n'))
	{
		line = get_before(buffer[fd]);
		remaining = get_after(buffer[fd]);
		ft_free(&buffer[fd]);
		buffer[fd] = remaining;
		return (line);
	}
	line = buffer[fd];
	buffer[fd] = NULL;
	return (line);
}
