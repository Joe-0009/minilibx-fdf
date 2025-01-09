/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:00 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/09 13:18:54 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_horizontal_lines(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map->dim.height)
	{
		j = 0;
		while (j < vars->map->dim.width - 1)
		{
			draw_line(vars, vars->points[i][j], vars->points[i][j + 1]);
			j++;
		}
		i++;
	}
}

static void	draw_vertical_lines(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map->dim.height - 1)
	{
		j = 0;
		while (j < vars->map->dim.width)
		{
			draw_line(vars, vars->points[i][j], vars->points[i + 1][j]);
			j++;
		}
		i++;
	}
}

void	main_draw(t_vars *vars)
{
	draw_horizontal_lines(vars);
	draw_vertical_lines(vars);
}