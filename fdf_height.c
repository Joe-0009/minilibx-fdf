/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_height.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:59 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/07 15:50:25 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calculate_color(int height, t_height_range *range)
{
	float	height_percent;

	if (height == 0)
		return (0x0000FF);
	height_percent = (float)(height - range->min) / (range->max - range->min
			+ 0.1);
	return (0xFFFFFF - (int)(height_percent * 0x00FFFF));
}

static void	process_height(char *str, t_height_range *height)
{
	int	current_height;

	current_height = ft_atoi(str);
	if (current_height < height->min)
		height->min = current_height;
	if (current_height > height->max)
		height->max = current_height;
}

void	find_height_range(char *file_name, t_map *map)
{
	int		fd;
	char	*line;
	char	**split;
	char	**color_split;
	int		i;

	map->height.min = INT_MAX;
	map->height.max = INT_MIN;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i = -1;
		split = ft_split(line, ' ');
		while (split[++i])
		{
			color_split = ft_split(split[i], ',');
			process_height(color_split[0], &map->height);
			ft_free_strs(color_split);
		}
		ft_free_strs(split);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

float	calculate_height_factor(t_map *map)
{
	float	height_range;
	float	height_factor;

	height_range = map->height.max - map->height.min;
	if (height_range <= 0)
		return (1.0);
	if (height_range > map->dim.width)
		height_factor = (float)map->dim.width / height_range;
	else if (height_range < map->dim.width / 4)
		height_factor = 2.0;
	else
		height_factor = 1.0;
	return (height_factor);
}

void	calculate_scale(t_map *map)
{
	float	max_projected_width;
	float	height_range;
	float	scale_x;
	float	scale_y;
	float	height_factor;

	max_projected_width = map->dim.width + map->dim.height;
	height_range = map->height.max - map->height.min;
	height_factor = calculate_height_factor(map);
	scale_x = (WIDTH / (max_projected_width * 1.5));
	scale_y = (HEIGHT / ((max_projected_width * sin(0.523599)) + (height_range
					* height_factor)));
	if (scale_x < scale_y)
		map->scale.base = scale_x;
	else
		map->scale.base = scale_y;
	map->scale.base *= 1.1;
	map->scale.z_scale = map->scale.base * height_factor;
	map->scale.iso_angle = 0.523599;
}
