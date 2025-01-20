/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:25 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/20 11:10:09 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_map_file(t_vars *vars)
{
	int	fd;

	fd = open(vars->window_name, O_RDONLY);
	if (fd < 0)
	{
		cleanup_all(vars);
		ft_error();
	}
	return (fd);
}

void	cleanup_gnl(int fd)
{
	char	*dummy;

	dummy = get_next_line(fd);
	while (dummy)
	{
		free(dummy);
		dummy = get_next_line(fd);
	}
}

static void	map_init(t_vars *vars)
{
	vars->map->dim.width = 0;
	vars->map->dim.height = 0;
	vars->map->scale.zoom_factor = 1.1;
	vars->map->scale.projection = 0;
	vars->map->scale.base = 0;
	vars->map->scale.z_scale = 0;
	vars->map->center.x = 0;
	vars->map->center.y = 0;
	vars->map->center.offset_x = 0;
	vars->map->center.offset_y = 0;
	vars->map->height.min = INT_MAX;
	vars->map->height.max = INT_MIN;
}

void	map_dimension(t_vars *vars)
{
	int		fd;
	char	*line;
	int		height;
	int		width;

	fd = open_map_file(vars);
	width = INT_MIN;
	map_init(vars);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		width = ft_words_count(line, ' ');
		if (width > vars->map->dim.width)
			vars->map->dim.width = width;
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	vars->map->dim.height = height;
}
