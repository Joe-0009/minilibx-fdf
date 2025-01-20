/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:14:02 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/19 17:33:04 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	float	scale_x;
	float	scale_y;
	float	height_factor;

	max_projected_width = map->dim.width + map->dim.height;
	height_factor = calculate_height_factor(map);
	scale_x = (WIDTH / (max_projected_width));
	scale_y = (HEIGHT / (max_projected_width));
	if (scale_x < scale_y)
		map->scale.base = scale_x;
	else
		map->scale.base = scale_y;
	map->scale.z_scale = map->scale.base * height_factor;
}
