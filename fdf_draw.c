/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:00 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/06 14:14:01 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_horizontal_lines(t_vars *vars, t_point **points, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->dim.height)
	{
		j = 0;
		while (j < map->dim.width - 1)
		{
			draw_line(vars, points[i][j], points[i][j + 1]);
			j++;
		}
		i++;
	}
}

static void	draw_vertical_lines(t_vars *vars, t_point **points, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->dim.height - 1)
	{
		j = 0;
		while (j < map->dim.width)
		{
			draw_line(vars, points[i][j], points[i + 1][j]);
			j++;
		}
		i++;
	}
}

void	main_draw(t_vars *vars, t_point **points, t_map *map)
{
	draw_horizontal_lines(vars, points, map);
	draw_vertical_lines(vars, points, map);
}
