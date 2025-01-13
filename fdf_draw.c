/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:00 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/13 13:33:09 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = vars->img->addr + (y * vars->img->line_length + x
				* (vars->img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	interpolate_color(int color1, int color2, float fraction)
{
	int	red;
	int	green;
	int	blue;

	red = ((1 - fraction) * ((color1 >> 16) & 0xFF)) + (fraction
			* ((color2 >> 16) & 0xFF));
	green = ((1 - fraction) * ((color1 >> 8) & 0xFF)) + (fraction
			* ((color2 >> 8) & 0xFF));
	blue = ((1 - fraction) * (color1 & 0xFF)) + (fraction * (color2 & 0xFF));
	return ((red << 16) | (green << 8) | blue);
}

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
