/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:25 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/13 14:49:15 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_map_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error();
	return (fd);
}

static void	map_init(t_map *map)
{
	map->dim.width = 0;
	map->dim.height = 0;
	map->scale.zoom_factor = 1.1;
	map->scale.projection = ISO;
	map->scale.iso_angle = 0.523599;
	map->scale.base = 0;
	map->scale.z_scale = 0;
	map->center.x = 0;
	map->center.y = 0;
	map->center.offset_x = 0;
	map->center.offset_y = 0;
	map->height.min = INT_MAX;
	map->height.max = INT_MIN;
}

t_map	map_dimension(t_vars *vars)
{
	t_map	map;
	int		fd;
	char	*line;
	int		height;
	int		width;

	width = INT_MIN;
	map_init(&map);
	height = 0;
	fd = open_map_file(vars->window_name);
	line = get_next_line(fd);
	while (line)
	{
		width = ft_words_count(line, ' ');
		if (width > map.dim.width)
			map.dim.width = width;
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map.dim.height = height;
	return (map);
}
