/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:15:14 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/09 12:41:40 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_low_slope(t_vars *vars, int dx, int dy, t_point *a,
		t_point *b)
{
	int		i;
	int		p;
	float	fraction;

	i = -1;
	p = 2 * abs(dy) - abs(dx);
	put_pixel(vars, a->x, a->y, a->color);
	while (++i < abs(dx))
	{
		fraction = (float)i / abs(dx);
		if (dx > 0)
			a->x += 1;
		else
			a->x -= 1;
		if (p < 0)
			p = p + 2 * abs(dy);
		else
		{
			if (dy > 0)
				a->y += 1;
			else
				a->y -= 1;
			p = p + 2 * abs(dy) - 2 * abs(dx);
		}
		put_pixel(vars, a->x, a->y, interpolate_color(a->color, b->color,
				fraction));
	}
}

void	draw_line_high_slope(t_vars *vars, int dx, int dy, t_point *a,
		t_point *b)
{
	int		p;
	int		i;
	float	fraction;

	i = -1;
	p = 2 * abs(dx) - abs(dy);
	put_pixel(vars, a->x, a->y, a->color);
	while (++i < abs(dy))
	{
		fraction = (float)i / abs(dy);
		if (dy > 0)
			a->y += 1;
		else
			a->y -= 1;
		if (p < 0)
			p = p + 2 * abs(dx);
		else
		{
			if (dx > 0)
				a->x += 1;
			else
				a->x -= 1;
			p = p + 2 * abs(dx) - 2 * abs(dy);
		}
		put_pixel(vars, a->x, a->y, interpolate_color(a->color, b->color,
				fraction));
	}
}

void	draw_line(t_vars *vars, t_point a, t_point b)
{
	int	dx;
	int	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (abs(dx) > abs(dy))
		draw_line_low_slope(vars, dx, dy, &a, &b);
	else
		draw_line_high_slope(vars, dx, dy, &a, &b);
}