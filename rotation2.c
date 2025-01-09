#include "fdf.h"



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