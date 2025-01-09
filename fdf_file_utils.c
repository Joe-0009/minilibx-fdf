/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:25 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/09 14:59:13 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_map_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(0);
	return (fd);
}

t_map	map_dimension(char *file_name)
{
	t_map	map;
	int		fd;
	char	*line;
	int		height;

	height = 0;
	fd = open_map_file(file_name);
	line = get_next_line(fd);
	while (line)
	{
		if (height == 0)
			map.dim->width = ft_words_count(line, ' ');
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map.dim->height = height;
	return (map);
}
