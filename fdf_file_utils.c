/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:25 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/09 14:15:40 by yrachidi         ###   ########.fr       */
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

void	map_dimension(t_vars *vars)
{
	int		fd;
	char	*line;
	int		height;

	height = 0;
	fd = open_map_file(vars->window_name);
	line = get_next_line(fd);
	while (line)
	{
		if (height == 0)
			vars->map->dim->width = ft_words_count(line, ' ');
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	vars->map->dim->height = height;
}
