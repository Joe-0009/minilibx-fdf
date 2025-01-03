#include "fdf.h"

void	put_pixel(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = vars->img.addr + (y * vars->img.line_length + x
				* (vars->img.bits_per_pixel / 8));
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

	fraction = 0.05;
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

void	main_draw(t_vars *vars, t_point **points, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width - 1)
		{
			draw_line(vars, points[i][j], points[i][j + 1]);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < map->height - 1)
	{
		j = 0;
		while (j < map->width)
		{
			draw_line(vars, points[i][j], points[i + 1][j]);
			j++;
		}
		i++;
	}
}
