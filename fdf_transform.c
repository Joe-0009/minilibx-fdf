#include "fdf.h"

void	iso_point(t_point *a)
{
	int	prev_x;
	int	prev_y;

	prev_x = a->x;
	prev_y = a->y;
	// Isometric transformation
	a->x = (prev_x - prev_y) * cos(0.523599) + WIDTH / 2;         
		// cos(30 degrees)
	a->y = -a->z + (prev_x + prev_y) * sin(0.523599) + HEIGHT / 2;
		// sin(30 degrees)
}

void	iso_points(t_point **points, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			iso_point(&points[i][j]);
			j++;
		}
		i++;
	}
}
