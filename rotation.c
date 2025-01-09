
#include "fdf.h"


void rotate_x(t_point *a, float angle)
{
    int prev_y;
    int prev_z;

    prev_y = a->y;
    prev_z = a->z;
    a->y = prev_y * cos(angle) - prev_z * sin(angle);
    a->z = prev_y * sin(angle) + prev_z * cos(angle);
}

void rotate_y(t_point *a, float angle)
{
    int prev_x;
    int prev_z;

    prev_x = a->x;
    prev_z = a->z;
    a->x = prev_x * cos(angle) + prev_z * sin(angle);
    a->z = -prev_x * sin(angle) + prev_z * cos(angle);
}

void rotate_z(t_point *a, float angle)
{
    int prev_x;
    int prev_y;

    prev_x = a->x;
    prev_y = a->y;
    a->x = prev_x * cos(angle) - prev_y * sin(angle);
    a->y = prev_x * sin(angle) + prev_y * cos(angle);
}

void iso_point(t_point *a, float angle)
{
    int prev_x;
    int prev_y;

    prev_x = a->x;
    prev_y = a->y;
    a->x = (prev_x - prev_y) * cos(angle);
    a->y = -a->z + (prev_x + prev_y) * sin(angle);
}

void	apply_rotation(t_vars *vars, float angle, void(f)(t_point *, float))
{
	int	i;
	int	j;

	if (!vars->points || !vars->map)
		return ;
	i = 0;
	while (i < vars->map->dim.height)
	{
		j = 0;
		while (j < vars->map->dim.width)
		{
			f(&vars->points[i][j], angle);
			j++;
		}
		i++;
	}
}

