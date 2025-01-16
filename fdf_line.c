/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:24:25 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/16 18:37:50 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	plot_low_slope_points(t_line_params *line, int p)
{
	if (p < 0)
		p = p + 2 * abs(line->dy);
	else
	{
		if (line->dy > 0)
			line->start->y += 1;
		else
			line->start->y -= 1;
		p = p + 2 * abs(line->dy) - 2 * abs(line->dx);
	}
	return (p);
}

void	draw_line_low_slope(t_vars *vars, t_line_params *line)
{
	int		i;
	int		p;
	float	fraction;

	i = -1;
	p = 2 * abs(line->dy) - abs(line->dx);
	put_pixel(vars, line->start->x, line->start->y, line->start->color);
	while (++i < abs(line->dx))
	{
		fraction = (float)i / abs(line->dx);
		if (line->dx > 0)
			line->start->x += 1;
		else
			line->start->x -= 1;
		p = plot_low_slope_points(line, p);
		put_pixel(vars, line->start->x, line->start->y,
			interpolate_color(line->start->color, line->end->color, fraction));
	}
}

static int	plot_high_slope_points(t_line_params *line, int p)
{
	if (p < 0)
		p = p + 2 * abs(line->dx);
	else
	{
		if (line->dx > 0)
			line->start->x += 1;
		else
			line->start->x -= 1;
		p = p + 2 * abs(line->dx) - 2 * abs(line->dy);
	}
	return (p);
}

void	draw_line_high_slope(t_vars *vars, t_line_params *line)
{
	int		i;
	int		p;
	float	fraction;

	i = -1;
	p = 2 * abs(line->dx) - abs(line->dy);
	put_pixel(vars, line->start->x, line->start->y, line->start->color);
	while (++i < abs(line->dy))
	{
		fraction = (float)i / abs(line->dy);
		if (line->dy > 0)
			line->start->y += 1;
		else
			line->start->y -= 1;
		p = plot_high_slope_points(line, p);
		put_pixel(vars, line->start->x, line->start->y,
			interpolate_color(line->start->color, line->end->color, fraction));
	}
}

void	draw_line(t_vars *vars, t_point a, t_point b)
{
	t_line_params	line;

	line.dx = b.x - a.x;
	line.dy = b.y - a.y;
	line.start = &a;
	line.end = &b;
	if (abs(line.dx) > abs(line.dy))
		draw_line_low_slope(vars, &line);
	else
		draw_line_high_slope(vars, &line);
}
